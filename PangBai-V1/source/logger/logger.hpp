#pragma once

#include <thread>
#include <memory>
#include <shared_mutex>
#include <consoleapi2.h>
#include <vector>
#include <ostream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace MdayS
{
    enum log_levels
    {
        INFO = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
        WARNING = FOREGROUND_RED | FOREGROUND_GREEN,
        DEBUG = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        RED_ERROR = FOREGROUND_RED
    };

    class logger
    {
    public:
        explicit logger();
        ~logger() noexcept;

        void log(std::string log, log_levels type = log_levels::INFO);
        void lua_log(std::string log, log_levels type = log_levels::INFO, std::string lua_name = "lua log");
        void log_notitle(std::string log, log_levels type = log_levels::INFO);

        std::string get_log_level_string(log_levels type) const;
        std::istream& get_input();

        void make_logger();
        void destroy_logger();

        void make_exception_handler();
        void destroy_exception_handler();

        void log_now(std::string message, log_levels type);

        template<typename T, typename... Args>
        void insert(log_levels type, T&& t, Args&&... args) {
            std::ostringstream oss;
            oss << std::forward<T>(t);
            (oss << ... << std::forward<Args>(args));
            std::string s = oss.str();
            log_now(s, type);
        }

        struct contents {
            contents(const std::string& message, log_levels type)
            {
                m_message = message;
                m_type = type;
            }

            std::string m_message;
            log_levels m_type;
        };

        std::vector<contents>& get_logs()
        {
            return m_logged;
        }

    private:
        std::mutex m_mutex;
        std::ifstream m_input;
        std::ofstream m_file;
        std::ofstream m_console;
        std::vector<contents> m_logged;

        PVOID m_exception_handler;
    };
    inline logger g_logger{};

    inline std::string TO_HEX_TO_UPPER(uint64_t x) {
        \
            std::ostringstream stream;
        stream << std::hex << std::uppercase << x;
        return stream.str();
    }
}