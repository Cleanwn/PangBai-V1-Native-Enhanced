#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

enum eVehicleGadgetType : uint32_t
{
    FORKS,
    SEARCH_LIGHT,
    PICK_UP_ROPE_WITH_HOOK,
    PICK_UP_ROPE_WITH_MAGNET,
    DIGGER_ARM,
    HANDLER_FRAME,
    BOMB_BAY,
};

struct CVehicleGadgetData
{
    eVehicleGadgetType m_Type; //0x0000
    uint8_t m_Data[94]; //0x0004
}; //Size: 0x64
static_assert(sizeof(CVehicleGadgetData) == 0x64);

class CVehicleGadgetDataNode : CSyncDataNodeFrequent
{
public:
    bool m_HasParentOffset; //0x00C0
    char pad_00C1[15]; //0x00C1
    uint32_t m_ParentOffsetX; //0x00D0
    uint32_t m_ParentOffsetY; //0x00D4
    uint32_t m_ParentOffsetZ; //0x00D8
    uint32_t m_ParentOffsetW; //0x00DC
    uint32_t m_GadgetCount; //0x00E0
    CVehicleGadgetData m_GadgetData[2]; //0x00E4
}; //Size: 0x01AC
static_assert(sizeof(CVehicleGadgetDataNode) == 0x1B0);