// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "xor_.hpp"
#include "hooking/hooks.hpp"
#include "gui/variable.hpp"
#include "gui/gui.hpp"
#include "tick/ticks.hpp"
#include "file.hpp"
#include "fiber/script.hpp"
#include "fiber/script_mgr.hpp"
#include "gui/widgets/keyboard.hpp"

namespace MdayS//请注意，将所有代码进入MdayS命名空间
{
    static HANDLE main_thread_handle{};
    static HINSTANCE dll_module{};

    DWORD __stdcall main_thread(void*)
    {

        g_logger.make_exception_handler();
        g_logger.make_logger();//初始化log日志，若不初始化则不会弹控制台
        g_logger.log_notitle(xorstr_(
            "\n"
            "    **    **  *****       *   **      **  ********\n"
            "    ***  ***  **   **    ***   **    **   **      \n"
            "    ** ** **  **    **  ** **    ****     ********\n"
            "    **    **  **   **  *******    **            **\n"
            "    **    **  *****   **     **   **      ********\n"
            "\n"
        ));//自行更改

        g_patterns.make_scan();
        g_logger.log(xorstr_("初始化特征码成功"));

        g_hooking.create_hooks();
        g_logger.log(xorstr_("初始化挂钩函数成功"));

        g_script_mgr.add_script(std::make_unique<script>(&ticks::menu_tick));

        g_gui.configure_gui();
        g_gui.make_gui();
        g_logger.log(xorstr_("加载配置成功"));

        while (g_running)
        {
            if (IsKeyPressed(VK_DELETE))//如果在游戏内按下DELETE则卸载本辅助
            {
                g_running = false;
            }
        }

        g_script_mgr.remove_all_scripts();

        g_patterns.restore_scan();

        g_hooking.remove_hooks();

        g_logger.destroy_exception_handler();
        g_logger.destroy_logger();

        CloseHandle(main_thread_handle);
        FreeLibraryAndExitThread(dll_module, 0);

        return true;
    }
}

BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {

        if (hModule)
            DisableThreadLibraryCalls(hModule);

        MdayS::main_thread_handle = CreateThread(nullptr, 0, MdayS::main_thread, nullptr, 0, nullptr);
        MdayS::dll_module = hModule;
    }

    return TRUE;
}