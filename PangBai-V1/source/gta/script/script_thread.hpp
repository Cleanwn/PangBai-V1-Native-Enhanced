#pragma once
#include "types/rage/atArray.hpp"
#include "types/rage/tlsContext.hpp"
#include "types/script/GtaThread.hpp"
#include "types/script/CGameScriptHandler.hpp"
#include "types/script/CGameScriptId.hpp"
#include "types/script/globals/GlobalPlayerBD.hpp"
#include "patterns/patterns.hpp"
#include "util/joaat.hpp"

namespace MdayS::script_thread
{
	inline rage::scrThread* find_script_thread(joaat_t hash)
	{
		for (auto& thread : *g_patterns.m_script_threads)
		{
			if (thread && thread->m_Context.m_ThreadId && thread->m_ScriptHash == hash)
			{
				return thread;
			}
		}

		return nullptr;
	}

	inline void run_as_script(rage::scrThread* thread, std::function<void()> callback)
	{
		auto og_thread = rage::tlsContext::Get()->m_CurrentScriptThread;
		auto og_running_in_scrthread = rage::tlsContext::Get()->m_ScriptThreadActive;
		rage::tlsContext::Get()->m_CurrentScriptThread = thread;
		rage::tlsContext::Get()->m_ScriptThreadActive = true;
		callback();
		rage::tlsContext::Get()->m_ScriptThreadActive = og_running_in_scrthread;
		rage::tlsContext::Get()->m_CurrentScriptThread = og_thread;
	}
}