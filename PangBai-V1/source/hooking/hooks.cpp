#include "pch.h"
#include "hooks.hpp"
#include "patterns/patterns.hpp"
#include "patterns/scanner/pattern.hpp"
#include <dxgi.h>
#include <dxgi1_2.h>

namespace MdayS
{
	void hooking::create_hooks()
	{
		MH_Initialize();

		create_and_enable_hook("RST", g_patterns.m_run_script_threads, reinterpret_cast<void*>(&hooks::run_script_threads));
		create_and_enable_hook("INT", g_patterns.m_init_native_tables, reinterpret_cast<void*>(&hooks::init_native_tables));

		MH_ApplyQueued();
	}

	void hooking::remove_hooks()
	{
		remove_all_hooks();

		MH_ApplyQueued();
	}
}