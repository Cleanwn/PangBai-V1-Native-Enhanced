#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedOrientationDataNode : CSyncDataNodeFrequent
{
public:
	bool m_HasDesiredHeadingX; //000C1
	bool m_HasDesiredHeadingY; //000C2
	float m_DesiredHeadingX;   //0x00C4
	float m_DesiredHeadingY;   //0x00C8
};
static_assert(sizeof(CPedOrientationDataNode) == 0xD0);