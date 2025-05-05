#pragma once
#include <d3d12.h>
#include <dxgi1_4.h>
#include "types/ped/CPedFactory.hpp"
#include "types/rage/atArray.hpp"
#include "types/script/scrThread.hpp"
#include "types/script/scrProgram.hpp"
#include "types/network/CNetGamePlayer.hpp"

namespace rage
{
	class netEventMgr;
}

class CNetworkObjectMgr;

namespace MdayS
{
	namespace types
	{

	}

	class patterns {
	public:
		patterns() = default;
		~patterns() = default;
		void make_scan();
		void restore_scan();

	public:
		PVOID m_run_script_threads;
		PVOID m_init_native_tables;
		PVOID m_prepare_metric_for_sending;

		rage::scrProgram** m_script_programs;
		rage::atArray<rage::scrThread*>* m_script_threads;

		std::int64_t** m_script_globals;
		std::uint32_t* m_screen_size_x;
		std::uint32_t* m_screen_size_y;

		int* m_be_restart_status;
		bool* m_needs_be_restart;
		bool* m_is_be_banned;
		bool* m_is_session_started;

	}; inline patterns g_patterns;
 }
