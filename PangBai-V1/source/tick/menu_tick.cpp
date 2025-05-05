#include "pch.h"
#include "ticks.hpp"
#include "fiber/script_mgr.hpp"
#include "native/native_hooks.hpp"
#include "gui/gui.hpp"

namespace MdayS::ticks
{
	void menu_tick()
	{
		NativeHooks::RunScript();
		while (true)
		{
			g_gui.tick();
			g_script_mgr.yield();
		}
	}
}