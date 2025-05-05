#include "pch.h"
#include "hooking/hooks.hpp"
#include "fiber/script_mgr.hpp"
#include "gta/script/script_thread.hpp"

namespace MdayS
{
	bool hooks::run_script_threads(int ops_to_execute)
	{
		if (g_running)
		{
			auto thread = script_thread::find_script_thread("freemode"_J);
			if (!thread)
				thread = script_thread::find_script_thread("main_persistent"_J);
			if (!thread)
				thread = script_thread::find_script_thread("startup"_J);
			if (thread)
			{
				script_thread::run_as_script(thread, [] {
					g_script_mgr.tick_internal();
					});
			}
		}

		return get_original<decltype(&hooks::run_script_threads)>("RST")(ops_to_execute);
	}
}
