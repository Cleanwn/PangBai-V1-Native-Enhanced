#include "pch.h"
#include "logger.hpp"

#include "file.hpp"

namespace MdayS
{
    logger::logger()
        : m_file("")
    {

    }

    void logger::make_logger()
    {
        std::string path;

        if (file.exists("logs\\log.txt") && file.exists("logs\\old logs")) {

            file.move_file(file.get_file("logs\\log.txt"),
                file.get_file("logs\\Old logs\\") + "" + file.get_timestamp() + ".txt");
        }
        else
        {
            file.create_folder("logs");
            file.create_folder("logs\\old logs");
        }

        path = file.get_file("logs\\") + "log.txt";

        try
        {
            m_file.open(path.c_str(), std::ios_base::out | std::ios_base::app);
        }
        catch (std::ios_base::failure const& e)
        {
            log(e.what(), INFO);
        }

        if (!AttachConsole(GetCurrentProcessId()))
            AllocConsole();
        SetConsoleTitleA(xorstr_(MENU_NAME));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);

        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);

        HWND hwnd = GetConsoleWindow();

        SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        SetLayeredWindowAttributes(hwnd, 0, (255 * 95) / 100, LWA_ALPHA);
        HMENU hMenu = GetSystemMenu(hwnd, FALSE);

        m_console.open("CONOUT$");
        m_input.open("CONIN$");
    }

    logger::~logger()
    {
        FreeConsole();
    }

    void logger::destroy_logger()
    {
        FreeConsole();
        m_console.close();
        m_input.close();
    }

    std::string logger::get_log_level_string(log_levels type) const
    {
        switch (type)
        {
        case log_levels::INFO:
            return "INFO";
        case log_levels::WARNING:
            return "WARNING";
        case log_levels::DEBUG:
            return "DEBUG";
        case log_levels::RED_ERROR:
            return "ERROR";
        default:
            return "NONE";
        }
    }

    void logger::log(std::string log, log_levels type)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        auto tm = std::localtime(&time);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), type);

        std::ostringstream prefix{};
        prefix << "[" << file.get_timestamp_narrow() << "] " << MENU_NAME << " [" << get_log_level_string(type) << "] ";
        std::string message = prefix.str() + log;
        m_file << message << std::endl;
        m_console << message << std::endl;
    }

    void logger::lua_log(std::string log, log_levels type, std::string lua_name)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        auto tm = std::localtime(&time);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), type);

        std::ostringstream prefix{};
        prefix << "[" << file.get_timestamp_narrow() << "] " << MENU_NAME << " [" << lua_name << "] ";
        std::string message = prefix.str() + log;
        m_file << message << std::endl;
        m_console << message << std::endl;
    }

    void logger::log_notitle(std::string log, log_levels type)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        auto tm = std::localtime(&time);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), type);

        std::ostringstream prefix{};
        std::string message = prefix.str() + log;
        m_console << message << std::endl;
    }

    std::istream& logger::get_input()
    {
        return m_input;
    }

    void logger::log_now(std::string message, log_levels type) {

        if (type == log_levels::DEBUG)
            return;

        const auto& get_type_string = [&](log_levels t) {
            switch (t) {
            case log_levels::INFO:
                return r_(xorstr_(MENU_NAME" [INFO] "));
            case log_levels::WARNING:
                return r_(xorstr_(MENU_NAME" [WARNING] "));
            case log_levels::RED_ERROR:
                return r_(xorstr_(MENU_NAME" [ERROR] "));
            }

            return x_("");
            };


        const contents ctx{ "[" + file.get_timestamp_narrow() + "] " + get_type_string(type) + message, type };

        m_logged.push_back(ctx);

        m_file << ctx.m_message << std::endl;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)ctx.m_type);

        m_console << ctx.m_message << std::endl;
    }

}