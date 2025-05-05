#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CGroup;
class CPed;
struct CGroupMember
{
	std::int16_t m_ObjectId;
	CPed* m_Ped; // this isn't serialized
};
static_assert(sizeof(CGroupMember) == 0x10);

// this node is kinda sus, need to check if the fields are in the right order
class CPlayerPedGroupDataNode : CSyncDataNodeInfrequent
{
public:
	char m_unused[0x10];		   // 0xC0
	CGroup* m_Group;			   // 0xD0 (not serialized)
	CGroupMember m_Members[7];	   // 0xD8
	CGroupMember m_Leader;         // 0x148
	char m_unused2[8];             // 0x158
	float m_MaxSeparation;         // 0x160
	char m_unused3[0xC];           // 0x164
	int m_PopType;                 // 0x170
	bool m_NeedsGroupEventScan;    // 0x175
	char m_unused4[6];             // 0x176
	int m_FormationType;           // 0x17C
	float m_FormationDistance;     // 0x180
	char m_unused5[0xC];           // 0x184
};
static_assert(sizeof(CPlayerPedGroupDataNode) == 0x190);