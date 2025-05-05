#pragma once
#include <future>

//Handle class from BigBaseV2

namespace MdayS
{

    class handle {
    public:
        handle() = default;
        explicit handle(uintptr_t address) : m_address(address) {}

        template <typename T>
        T as() const {
            return reinterpret_cast<T>(m_address);
        }

        handle add(uintptr_t offset) const {
            if (m_address != 0)
            {
                return handle(m_address + offset);
            }

            return *this;
        }

        handle sub(uintptr_t offset) const {
            if (m_address != 0)
            {
                return handle(m_address - offset);
            }

            return *this;
        }

        handle rip() const {
            if (m_address != 0)
            {
                auto offset = *as<int32_t*>();
                return add(offset + sizeof(int32_t));
            }

            return *this;
        }

        uintptr_t get_address()
        {
            return m_address;
        }

    private:
        uintptr_t m_address = 0;
    };


    class _module {
    public:
        _module(const char* module) : m_module(module) 
        {
            m_module_handle = GetModuleHandleA(m_module);
        }

        handle get_export(const char* func)
        {
            return handle((std::uintptr_t)GetProcAddress(m_module_handle, func));
        }

        HMODULE get_handle()
        {
            return m_module_handle;
        }

    private:
        const char* m_module;
        HMODULE m_module_handle;
    };

	class pattern {
	public:
		explicit pattern(_module module);
		~pattern() noexcept;

        pattern& scan_now(const char* sig_name, const char* ida_sig);
        pattern& scan_all_now(const char* sig_name, const char* ida_sig);

        handle get_result();
        std::vector<handle> get_all_results();
	private:
		std::string m_module_name;
        _module m_module;
		size_t m_module_size;
        HMODULE m_module_handle;
        handle m_result;
        std::vector<handle> m_all_result;
    };

    class offset {
    public:
        explicit offset(uint64_t offset, _module module = "GTA5_Enhanced.exe");
        ~offset() noexcept;

        handle& get_result();
        uintptr_t& get_address();
    private:
        uint64_t m_offset;
        _module m_module;
        handle m_result;
        HMODULE m_module_handle;
        uintptr_t m_address;
    };

    class SimplePattern
    {
    public:
        SimplePattern(std::string_view ida_sig);
        inline SimplePattern(const char* ida_sig) :
            SimplePattern(std::string_view(ida_sig))
        {
        }

        inline SimplePattern(SimplePattern&& other) :
            m_Bytes(other.m_Bytes)
        {
        }

        inline SimplePattern(const SimplePattern& other) :
            m_Bytes(other.m_Bytes)
        {
        }

        std::vector<std::optional<uint8_t>> m_Bytes;
    };
}