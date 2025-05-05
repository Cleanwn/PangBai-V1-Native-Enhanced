#pragma once
#include "pch.h"
#include "logger/logger.hpp"
#include "script.hpp"
#include <optional>

namespace MdayS
{
	script::script(std::function<void()> callback) :
		m_callback(callback),
		m_done(false),
		m_child_fiber(0),
		m_main_fiber(0),
		m_wake_time(std::nullopt)
	{
		m_child_fiber = CreateFiber(
			0,
			[](void* param) {
				auto this_script = static_cast<script*>(param);
				this_script->m_callback();
				this_script->m_done = true;
				SwitchToFiber(this_script->m_main_fiber);
			},
			this);
	}

	script::~script()
	{
		if (m_child_fiber)
			DeleteFiber(m_child_fiber);
	}

	void script::tick()
	{
		m_main_fiber = GetCurrentFiber();
		if (!m_wake_time.has_value() || m_wake_time.value() <= std::chrono::high_resolution_clock::now())
		{
			SwitchToFiber(m_child_fiber);
		}
	}

	void script::yield(std::optional<std::chrono::high_resolution_clock::duration> time)
	{
		if (time.has_value())
		{
			m_wake_time = std::chrono::high_resolution_clock::now() + time.value();
		}
		else
		{
			m_wake_time = std::nullopt;
		}

		SwitchToFiber(m_main_fiber);
	}
}
