#pragma once
#include "MinHook.h"
#include "logger/logger.hpp"
#include "xor_.hpp"

#include <functional>
#include <map>

namespace MdayS
{
    class detour {
    public:
        detour(const char* name, void* ptr, void* detour) : m_name(name), m_ptr(ptr), m_detour(detour), m_status(true)
        {
            if (MH_CreateHook(m_ptr, m_detour, &m_orig) == MH_OK) {
                //g_logger.insert(log_class::GENERAL, "Created hook ", m_name);
            } 
            else {
                m_status = false;
                //g_logger.insert(log_class::FATAL, "Failed to create hook ", m_name);
            }           
        }

        void enable()
        {
            if (m_status && MH_QueueEnableHook(m_ptr) == MH_OK) {
                //g_logger.insert(log_levels::INFO, "Enabled hook ", m_name);
            }
            else {
                m_status = false;
                //g_logger.insert(log_class::FATAL, "Failed to enable hook ", m_name);
            }
        }

        void disable()
        {
            if (m_status) {
                if (MH_QueueDisableHook(m_ptr) == MH_OK) {
                    //g_logger.insert(log_class::GENERAL, "Disabled hook ", m_name);
               
                    if (MH_RemoveHook(m_ptr) == MH_OK) {
                        //g_logger.insert(log_class::GENERAL, "Removed hook ", m_name);
                    }
                    else {
                        m_status = false;
                        //g_logger.insert(log_class::FATAL, "Failed to remove hook ", m_name);
                    }
                }
                else {
                   // g_logger.insert(log_class::FATAL, "Failed to disable hook ", m_name);
                }              
            }
        }

       
        void* get_original() const {
            return m_orig;
        }

    private:
        const char* m_name;

        void* m_ptr;
        void* m_detour;
        void* m_orig;

        bool m_status;
    };

    inline std::map<std::string, std::unique_ptr<detour>> g_hook_map;

    template <typename func>
    static void create_and_enable_hook(const char* name, func original_func, func detour_func) {
        detour* new_hook = new detour(name, reinterpret_cast<void*>(original_func), reinterpret_cast<void*>(detour_func));
        g_hook_map.insert(std::make_pair(name, std::unique_ptr<detour>(new_hook)));
        g_hook_map[name]->enable();
    }

    static void remove_all_hooks()
    {
        for (const auto& [name, detour] : g_hook_map) {
            if (g_hook_map[name]) {
                g_hook_map[name]->disable();
               // g_logger.insert(log_levels::INFO, "Disabled hook ", name);
            }
        }
    }

    static void remove_hook(std::string& name)
    {
        auto it = g_hook_map.find(name);
        if (it != g_hook_map.end()) {
            it->second->disable();
            g_hook_map.erase(it);
        }   
    }

    template<typename function>
    static function get_original(const char* name)
    {
        auto it = g_hook_map.find(name);

        if (it != g_hook_map.end())
        {
            const auto original = it->second->get_original();
            
            return reinterpret_cast<function>(original);
        }

        return nullptr;
    }
}