#include "pch.h"
#include "hooking/hooks.hpp"
#include "native/native_hooks.hpp"

namespace MdayS
{
	void hooks::init_native_tables(rage::scrProgram* program)
	{
		return get_original<decltype(&hooks::init_native_tables)>("INT")(program);
		if (g_running)
		{
			NativeHooks::RegisterProgram(program);
		}
	}
}