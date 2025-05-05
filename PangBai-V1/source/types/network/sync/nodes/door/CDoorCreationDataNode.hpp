#pragma once
#include <cstdint>
#include "types/rage/vector.hpp"
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CDoorCreationDataNode : CProjectBaseSyncDataNode
{
public:
  uint32_t m_ModelHash; //0x00C0
  char pad_00C4[12]; //0x00C4
  rage::fvector3 m_Position; //0x00D0
  char pad_00E0[8]; //0x00E0
  bool m_IsScriptDoor; //0x00E8
  bool m_PlayerWantsControl; //0x00E9
}; //Size: 0x00EC
static_assert(sizeof(CDoorCreationDataNode) == 0xF0);
