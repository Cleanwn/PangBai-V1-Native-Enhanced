#include "pch.h"
#include "script_local.hpp"

namespace MdayS
{
	void* script_local::get() const
	{
		return reinterpret_cast<uintptr_t*>((uintptr_t)m_StackPtr + (m_Index * sizeof(uintptr_t)));
	}
}