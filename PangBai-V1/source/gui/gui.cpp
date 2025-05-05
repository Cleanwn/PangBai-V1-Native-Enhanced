#include "pch.h"
#include "gui.hpp"
#include "native/natives.hpp"
#include "widgets/widgets.hpp"
#include "gta/script/script_global.hpp"
#include "gui/variable.hpp"

namespace MdayS
{
	void gui::tick()
	{
		widgets::Checks::controlls();

		switch (widgets::Settings::currentMenu) {

		case mainmenu:
		{
			widgets::add_title("MdayS");
			widgets::add_submenus("自我", self);
			widgets::add_submenus("其他", Misc);
			widgets::add_submenus("世界", World);
			widgets::add_submenus("设置", settings);
			if (widgets::add_button("ceshi"))
			{
				g_logger.log("45454");
			}
		}
		break;
		}
		widgets::end();
	}

	void gui::make_gui()
	{
		//在界面首次加载时候，加载一些配置
	}

	void gui::configure_gui()
	{
		//在界面首次加载时候，初始化一些变量

	}
}