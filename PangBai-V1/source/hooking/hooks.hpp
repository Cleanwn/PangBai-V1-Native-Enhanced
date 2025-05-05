#pragma once
#include "detour.hpp"

#define SWAPCHAIN_RESIZE_BUFFERS_VTABLE_INDEX 13
#define SWAPCHAIN_PRESENT_VTABLE_INDEX 8
#define SWAPCHAIN_NUM_FUNCS 19

#include <dxgi.h>

#include "types/network/netEvent.hpp"
#include "types/script/scrProgram.hpp"
#include "types/rage/datBitBuffer.hpp"
#include "types/network/netMessage.hpp"

namespace rage
{
	class netConnectionManager;
	class netArrayHandler;
	class netEvent;
	class scrProgram;
	class netObject;
	class datBitBuffer;
	class JsonSerializer;
	class rlMetric;
}


namespace MdayS::hooks
{
	//Script
	extern bool run_script_threads(int ops_to_execute);
	extern void init_native_tables(rage::scrProgram* program);
}

namespace MdayS
{
	class hooking {
	public:
		hooking() = default;
		~hooking() = default;

		void create_hooks();
		void remove_hooks();
	}; 
	inline hooking g_hooking;
}