#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

struct CDecorator
{
    uint32_t m_Type;
    uint32_t m_NameHash;
    uint32_t m_Value;
};

class CDynamicEntityGameStateDataNode : CSyncDataNodeInfrequent
{
public:
    uint32_t m_InteriorIndex; // 0x00C0
    bool unk_00C4; // 0x00C4
    bool unk_00C5; // 0x00C5
    uint32_t m_DecorCount; // 0x00C8
    CDecorator m_Decors[10]; // 0x00CC
    char pad[8]; // TODO!
};
static_assert(sizeof(CDynamicEntityGameStateDataNode) == 0x150);