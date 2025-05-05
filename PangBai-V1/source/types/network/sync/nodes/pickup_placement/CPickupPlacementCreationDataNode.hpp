#pragma once
#include "types/rage/vector.hpp"
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPickupPlacementCreationDataNode : CProjectBaseSyncDataNode
{
public:
    bool m_HasPickupData; //0x00C0
    char pad_00C1[15]; //0x00C1
    rage::fvector3 m_PickupPos; //0x00D0
    rage::fvector4 m_PickupOrientation; //0x00E0
    uint32_t m_PickupType; //0x00F0
    uint32_t m_PickupFlags; //0x00F4
    uint32_t m_Amount; //0x00F8
    uint32_t m_CustomModel; //0x00FC
    uint32_t m_CustomRegenerationTime; //0x0100
    uint32_t m_TeamPermits; //0x0104
    uint64_t *unk_struct_0108; //0x0108
}; //Size: 0x0110
static_assert(sizeof(CPickupPlacementCreationDataNode) == 0x110);
