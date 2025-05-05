#include "pch.h"
#include "patterns/patterns.hpp"
#include "script_global.hpp"

namespace MdayS
{
    void* script_global::get() const
    {
        return g_patterns.m_script_globals[m_Index >> 0x12 & 0x3F] + (m_Index & 0x3FFFF);
    }

    bool script_global::can_access() const
    {
        return g_patterns.m_script_globals && (m_Index >> 0x12 & 0x3F) < 0x40 && g_patterns.m_script_globals[m_Index >> 0x12 & 0x3F];
    }
}