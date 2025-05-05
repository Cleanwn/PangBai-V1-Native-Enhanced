#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPlayerCreationDataNode : CProjectBaseSyncDataNode
{
public:
    uint32_t m_ModelHash; //0x00C0
    uint32_t m_NumScars; //0x00C4
    char unk_struct_0xC8[192]; //0x00C8
    uint32_t unk_0188; //0x0188
    char pad_018C[4]; //0x018C
    char m_scar_struct[176]; //0x0190
    bool unk_0240; //0x0240
    char pad_0241[19]; //0x0241
}; //Size: 0x0254
static_assert(sizeof(CPlayerCreationDataNode) == 0x258);