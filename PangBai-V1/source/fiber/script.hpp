#pragma once
#include <optional>

namespace MdayS
{
	class script
	{
	public:
		std::function<void()> m_callback;
		bool m_done;
		HANDLE m_child_fiber;
		HANDLE m_main_fiber;
		std::optional<std::chrono::high_resolution_clock::time_point> m_wake_time;

	public:
		explicit script(std::function<void()> callback);
		~script();

		void tick();
		void yield(std::optional<std::chrono::high_resolution_clock::duration> time = std::nullopt);
	};
}
