#pragma once
#include <cstddef>
#include <type_traits>

namespace MdayS
{
    class script_global
    {
    private:
        std::size_t m_Index;

    public:
        constexpr script_global(std::size_t idx) :
            m_Index(idx)
        {
        }

        constexpr script_global at(std::ptrdiff_t offset) const
        {
            return m_Index + offset;
        }

        constexpr script_global at(std::ptrdiff_t offset, std::size_t size) const
        {
            return m_Index + 1 + offset * size;
        }

        template<typename T>
        inline std::enable_if_t<std::is_pointer_v<T>, T> as() const
        {
            return static_cast<T>(get());
        }

        template<typename T>
        inline std::enable_if_t<std::is_lvalue_reference_v<T>, T> as() const
        {
            return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(get());
        }

        bool can_access() const;

    private:
        void* get() const;

    };

}