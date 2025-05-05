#include "pch.h"
#include "ticks.hpp"
#include "fiber/script_mgr.hpp"
#include "gui/gui.hpp"

namespace MdayS::ticks
{
	void menu_tick()
	{
		while (true)
		{
			g_gui.tick();
			g_script_mgr.yield();
		}
	}
}