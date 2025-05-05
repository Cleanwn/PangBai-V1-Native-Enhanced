#pragma once
#include "script.hpp"

namespace MdayS
{
	class script_mgr
	{
	public:
		explicit script_mgr() = default;
		~script_mgr() = default;

		void tick_internal();
		void add_script(std::unique_ptr<script> script);
		void remove_all_scripts();
		void remove_script(std::unique_ptr<script> script);
	public:
		void yield(std::optional<std::chrono::high_resolution_clock::duration> time = std::nullopt);
	private:
		std::recursive_mutex m_mutex;
		std::vector<std::unique_ptr<script>> m_scripts;
	};

	inline script_mgr g_script_mgr;
}
