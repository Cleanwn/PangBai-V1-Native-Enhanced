 #include "pch.h"
#include "script_mgr.hpp"
#include "script.hpp"
#include <functional>

namespace MdayS
{
	void script_mgr::add_script(std::unique_ptr<script> script)
	{
		std::lock_guard lock(m_mutex);
		m_scripts.push_back(std::move(script));

	}

	void script_mgr::remove_script(std::unique_ptr<script> script)
	{
		m_scripts.erase(std::remove(m_scripts.begin(), m_scripts.end(), std::move(script)), m_scripts.end());
	}

	void script_mgr::remove_all_scripts()
	{
		std::lock_guard lock(m_mutex);
		m_scripts.clear();
	}

	void script_mgr::tick_internal()
	{
		static bool ensure_main_fiber = (ConvertThreadToFiber(nullptr), true);

		std::lock_guard lock(m_mutex);
		
		if (m_scripts.size())
		{
			for (auto const& script : m_scripts)
			{
				script->tick();
			}
		}

	}

	void script_mgr::yield(std::optional<std::chrono::high_resolution_clock::duration> time)
	{
		if (auto Script = static_cast<script*>(GetFiberData()))
			Script->yield(time);
	}
}
