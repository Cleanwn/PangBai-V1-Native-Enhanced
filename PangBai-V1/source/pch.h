#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>
#include <array>
#include <vector>
#include <functional>

#include "logger/logger.hpp"
#include "patterns/patterns.hpp"

#define MENU_PATH "C:\\MdayS"//用于存放配置文件的路径
#define MENU_NAME "MdayS"//菜单名称
#define MENU_VER "1.0"//菜单版本

#pragma execution_character_set("utf-8")//保证编码为UTF8

namespace MdayS
{
#define IS_RELEASE false

	inline bool g_running{ true };
}


#endif //PCH_H
