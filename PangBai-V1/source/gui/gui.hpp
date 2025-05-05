#pragma once

namespace MdayS
{
	class gui
	{
	public:
		void tick();
		void make_gui();
		void configure_gui();
	};
	inline gui g_gui;
}