#pragma once
#include "types/rage/vector.hpp"
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

// TODO: verify if this is right
class CObjectCreationDataNode : CProjectBaseSyncDataNode
{
public:
	uint32_t unk_00C0; //0x00C0
	uint32_t unk_00C4; //0x00C4
	uint32_t unk_00C8; //0x00C8
	bool unk_00CC;
	bool unk_00CD;
	uint16_t unk_00D0; //0x00D0
	char pad_0xC2[14]; //0x00D2
	rage::fvector4 m_ObjectOrientation; //0x00E0
	char pad_00E0[30]; //0x00F0
	rage::fvector3 m_ObjectPosition; //0x0110
	char pad_010C[4]; //0x011C
	rage::fvector3 m_DummyPosition; //0x011E
	char pad_011A[16]; //0x012C
	rage::fvector3 m_ScriptGrabPosition; //0x0140
	char pad_013C[8]; //0x013C
	float m_ScriptGrabRadius; //0x0148
	uint32_t m_CreatedBy; //0x014C
	uint32_t m_Model; //0x0150
	uint32_t m_FragGroupIndex; //0x0154
	uint32_t m_OwnershipToken; //0x0158
	uint32_t unk_015C; //0x015C

	// everything after this is probably wrong
	bool m_NoReassign; //0x0160
	bool unk_0161; //0x0161
	bool m_PlayerWantsControl; //0x0162
	bool m_HasInitPhysics; //0x0163
	bool m_ScriptGrabbedFromWorld; //0x0164
	bool m_IsFragObject; //0x0165
	bool m_IsBroken; //0x0166
	bool m_HasExploded; //0x0167
	bool m_KeepRegistered; //0x0168
	bool unk_0169; //0x0169
	bool unk_016A; //0x016A
	bool unk_016B; //0x016B
}; //Size: 0x016C
static_assert(sizeof(CObjectCreationDataNode) == 0x180);