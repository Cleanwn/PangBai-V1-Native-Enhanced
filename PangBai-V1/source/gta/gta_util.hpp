#pragma once
#include "patterns/patterns.hpp"
#include "native/natives.hpp"

namespace MdayS::gta_util
{
	inline CPed* get_local_ped()
	{
		if (auto ped_factory = *g_patterns.m_ped_factory)
		{
			return ped_factory->m_LocalPed;
		}
		return nullptr;
	}
}