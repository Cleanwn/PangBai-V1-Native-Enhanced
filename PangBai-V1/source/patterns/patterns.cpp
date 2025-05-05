#include "pch.h"
#include "patterns.hpp"

#include "scanner/pattern.hpp"
#include "logger/logger.hpp"

#include "xor_.hpp"

static int m_region_code_index;

namespace MdayS
{
	void patch_byte(PVOID address, const unsigned char* bytes, int numBytes) {
		DWORD oldProtect;
		VirtualProtect(address, numBytes, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(address, bytes, numBytes);
		VirtualProtect(address, numBytes, oldProtect, &oldProtect);
	}

	void patterns::restore_scan()
	{

	}

	void patterns::make_scan()
	{
		auto gta5 = pattern("GTA5_Enhanced.exe");
		
		m_script_threads = gta5.scan_now(xorstr_("ST"), xorstr_("48 8B 05 ? ? ? ? 48 89 34 F8 48 FF C7 48 39 FB 75 97"))
			.get_result().add(3).rip().as<rage::atArray<rage::scrThread*>*>();

		m_script_globals = gta5.scan_now(xorstr_("SG"), xorstr_("48 8B 8E B8 00 00 00 48 8D 15 ? ? ? ? 49 89 D8"))
			.get_result().add(7).add(3).rip().as<std::int64_t**>();

		m_init_native_tables = gta5.scan_now(xorstr_("INT"), xorstr_("EB 2A 0F 1F 40 00 48 8B 54 17 10"))
			.get_result().sub(0x2A).as<PVOID>();

		m_prepare_metric_for_sending = gta5.scan_now(xorstr_("PMFS"), xorstr_("48 89 F9 FF 50 20 48 8D 15"))
			.get_result().sub(0x26).as<PVOID>();

		m_script_programs = gta5.scan_now(xorstr_("SP"), xorstr_("48 C7 84 C8 D8 00 00 00 00 00 00 00"))
			.get_result().add(0x13).add(3).rip().add(0xD8).as<rage::scrProgram**>();

		m_is_session_started = gta5.scan_now(xorstr_("ISS"), xorstr_("0F B6 05 ? ? ? ? 0A 05 ? ? ? ? 75 2A"))
			.get_result().add(3).rip().as<bool*>();

		m_run_script_threads = gta5.scan_now(xorstr_("RST"), xorstr_("BE 40 5D C6 00"))
			.get_result().sub(0xA).as<PVOID>();

		{
			static auto ptr = gta5.scan_now(xorstr_("BED"), xorstr_("48 C7 05 ? ? ? ? 00 00 00 00 E8 ? ? ? ? 48 89 C1 E8 ? ? ? ? E8 ? ? ? ? BD 0A 00 00 00"))
				.get_result();
			m_be_restart_status = ptr.add(3).rip().add(8).add(4).as<int*>();
			m_needs_be_restart = ptr.add(3).rip().add(8).add(4).add(8).as<bool*>();
			m_is_be_banned = ptr.add(3).rip().add(8).add(4).add(8).add(4).as<bool*>();
		}

		{
			static auto ptr = gta5.scan_now(xorstr_("SS"), xorstr_("75 39 0F 57 C0 F3 0F 2A 05"))
				.get_result();
			m_screen_size_x = ptr.add(0x5).add(4).rip().as<std::uint32_t*>();
			m_screen_size_y = ptr.add(0x1E).add(4).rip().as<std::uint32_t*>();
		}
	}

}
