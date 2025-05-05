#include "pch.h"
#include "pattern.hpp"
#include <logger/logger.hpp>

#include "xor_.hpp"

#include <Psapi.h>
#include <sstream>
#include <optional>
#include <minmax.h>

namespace MdayS
{
    std::vector<std::optional<uint8_t>> parse_ida_signature(const char* sig) {
        std::vector<std::optional<uint8_t>> bytes;
        std::stringstream ss(sig);

        while (!ss.eof()) {
            std::string byte_str;
            ss >> byte_str;

            if (byte_str == "?" || byte_str == "??") {
                bytes.push_back(std::nullopt);
                continue;
            }

            if (byte_str.length() != 2) {
                throw std::runtime_error("Invalid byte in IDA signature: " + byte_str);
            }

            char* end;
            long value = strtol(byte_str.c_str(), &end, 16);

            if (*end != '\0') {
                throw std::runtime_error("Invalid byte in IDA signature: " + byte_str);
            }

            bytes.push_back(static_cast<uint8_t>(value));
        }

        return bytes;
    }


	pattern::pattern(_module module) :
		m_module(module), m_result(0)
	{
        m_module_handle = m_module.get_handle();

		if (m_module_handle == nullptr) {
			throw std::runtime_error(r_(xorstr_("Could not find module: ")) + m_module_name);
		}

		MODULEINFO mi = { 0 };

		if (!GetModuleInformation(GetCurrentProcess(), m_module_handle, &mi, sizeof(mi))) {
			throw std::runtime_error(r_(xorstr_("Could not get module information")));
		}
		m_module_size = mi.SizeOfImage;
	}

    pattern::~pattern(){}

    pattern& pattern::scan_all_now(const char* sig_name, const char* ida_sig)
    {
        auto signature = parse_ida_signature(ida_sig);

        std::uintptr_t base_address = reinterpret_cast<std::uintptr_t>(m_module_handle);

        std::size_t sig_size = signature.size();
        std::uintptr_t end_address = base_address + m_module_size - sig_size;

        std::array<int, 256> bad_char;
        for (int i = 0; i < 256; ++i) {
            bad_char[i] = sig_size;
        }
        for (int i = 0; i < sig_size - 1; ++i) {
            if (signature[i].has_value()) {
                bad_char[signature[i].value()] = sig_size - i - 1;
            }
            else {
                for (int j = 0; j < 256; ++j) {
                    bad_char[j] = min(bad_char[j], sig_size - i - 1);
                }
            }
        }

        std::uintptr_t i = base_address + sig_size - 1;
        while (i < end_address) {
            int j = sig_size - 1;
            while (j >= 0) {
                if (signature[j].has_value() && signature[j].value() != *reinterpret_cast<uint8_t*>(i - sig_size + j + 1))
                    break;
                --j;
            }
            if (j < 0) {
                m_result = handle(i - sig_size + 1);
                //g_logger.insert(log_levels::INFO, "Found pattern ", sig_name);
                m_all_result.push_back(m_result);
            }
            i += max(bad_char[*reinterpret_cast<uint8_t*>(i)], static_cast<int>(sig_size - j - 1));
        }

        if (!m_all_result.empty()) {
            return *this;
        }
        else {
            //g_logger.insert(log_levels::WARNING, "Failed to scan pattern ", sig_name);
            return *this;
        }
    }


    pattern& pattern::scan_now(const char* sig_name, const char* ida_sig)
    {
        auto signature = parse_ida_signature(ida_sig);

        std::uintptr_t base_address = reinterpret_cast<std::uintptr_t>(m_module_handle);

        std::size_t sig_size = signature.size();
        std::uintptr_t end_address = base_address + m_module_size - sig_size;

        std::array<int, 256> bad_char;
        for (int i = 0; i < 256; ++i) {
            bad_char[i] = sig_size;
        }
        for (int i = 0; i < sig_size - 1; ++i) {
            if (signature[i].has_value()) {
                bad_char[signature[i].value()] = sig_size - i - 1;
            }
            else {
                for (int j = 0; j < 256; ++j) {
                    bad_char[j] = min(bad_char[j], sig_size - i - 1);
                }
            }
        }

        std::uintptr_t i = base_address + sig_size - 1;
        while (i < end_address) {
            int j = sig_size - 1;
            while (j >= 0) {
                if (signature[j].has_value() && signature[j].value() != *reinterpret_cast<uint8_t*>(i - sig_size + j + 1))
                    break;
                --j;
            }
            if (j < 0) {
                m_result = handle(i - sig_size + 1);
               // g_logger.insert(log_levels::INFO, "Found pattern ", sig_name);
                return *this;
            }
            i += max(bad_char[*reinterpret_cast<uint8_t*>(i)], static_cast<int>(sig_size - j - 1));
        }

       // g_logger.insert(log_levels::WARNING, "Failed to scan pattern ", sig_name);
        
        m_result = handle(0); // Null it out

        return *this;
    }

    handle pattern::get_result()
    {
        return m_result;
    }

    std::vector<handle> pattern::get_all_results()
    {
        return m_all_result;
    }


    offset::offset(uint64_t offset, _module module) :
        m_offset(offset), m_module(module)
    {
        m_module_handle = m_module.get_handle();    
    }

    offset::~offset() {}

    handle& offset::get_result()
    {
        auto addr = (uintptr_t)m_module_handle + m_offset;
        m_result = handle(addr);

        return m_result;
    }

    uintptr_t& offset::get_address()
    {
        auto addr = (uintptr_t)m_module_handle + m_offset;
        return addr;
    }

    static inline constexpr std::optional<uint8_t> ToHex(char const c)
    {
        switch (c)
        {
        case '0': return static_cast<uint8_t>(0x0);
        case '1': return static_cast<uint8_t>(0x1);
        case '2': return static_cast<uint8_t>(0x2);
        case '3': return static_cast<uint8_t>(0x3);
        case '4': return static_cast<uint8_t>(0x4);
        case '5': return static_cast<uint8_t>(0x5);
        case '6': return static_cast<uint8_t>(0x6);
        case '7': return static_cast<uint8_t>(0x7);
        case '8': return static_cast<uint8_t>(0x8);
        case '9': return static_cast<uint8_t>(0x9);
        case 'a': return static_cast<uint8_t>(0xa);
        case 'b': return static_cast<uint8_t>(0xb);
        case 'c': return static_cast<uint8_t>(0xc);
        case 'd': return static_cast<uint8_t>(0xd);
        case 'e': return static_cast<uint8_t>(0xe);
        case 'f': return static_cast<uint8_t>(0xf);
        case 'A': return static_cast<uint8_t>(0xA);
        case 'B': return static_cast<uint8_t>(0xB);
        case 'C': return static_cast<uint8_t>(0xC);
        case 'D': return static_cast<uint8_t>(0xD);
        case 'E': return static_cast<uint8_t>(0xE);
        case 'F': return static_cast<uint8_t>(0xF);
        default: return std::nullopt;
        }
    }

    SimplePattern::SimplePattern(std::string_view ida_sig)
    {
        const auto size_minus_one = ida_sig.size() - 1;
        m_Bytes.reserve(size_minus_one / 2);
        for (size_t i = 0; i != size_minus_one; ++i)
        {
            if (ida_sig[i] == ' ')
                continue;
            if (ida_sig[i] != '?')
            {
                auto c1 = ToHex(ida_sig[i]);
                auto c2 = ToHex(ida_sig[i + 1]);
                if (c1 && c2)
                {
                    m_Bytes.emplace_back(static_cast<uint8_t>((*c1 * 0x10) + *c2));
                }
            }
            else
            {
                m_Bytes.push_back({});
            }
        }
    }
}