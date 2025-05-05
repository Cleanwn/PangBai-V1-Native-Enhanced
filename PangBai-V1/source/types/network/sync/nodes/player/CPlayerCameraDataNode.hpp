#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPlayerCameraDataNode : CSyncDataNodeFrequent
{
public:
	float m_FreeCamPosX; //0x00C0
	float m_FreeCamPosY; //0x00C4
	float m_FreeCamPosZ; //0x00C8
	char pad_00CC[4]; //0x00CC
	float m_LockOnTargetOffsetX; //0x00D0
	float m_LockOnTargetOffsetY; //0x00D4
	char pad_00D8[40]; //0x00D8
	float m_CameraX; //0x0100
	float m_CameraZ; //0x0104
	int16_t m_FreeAimLockedOnTarget; //0x0108
	bool m_FreeCam; //0x010A
	char pad_010B[2]; //0x010B
	bool m_HasPositionOffset; //0x010D
	char pad_010E[1]; //0x010E
	bool m_IsLongRangeTarget; //0x010F
	char pad_0110[48]; //0x0110
}; //Size: 0x0140
static_assert(sizeof(CPlayerCameraDataNode) == 0x140);