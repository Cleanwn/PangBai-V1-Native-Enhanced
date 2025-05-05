#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedGameStateDataNode : CSyncDataNodeInfrequent
{
public:
	bool m_WeaponComponentSomething[12]; //0x0C0
	uint32_t m_WeaponComponentHash[12]; //0x0CC
	uint32_t m_GadgetHash[3]; //0x0F8
	uint32_t unk_0104; // 0x0104
	uint32_t unk_0108; // 0x0108
	uint32_t unk_010C; // 0x010C
	float unk_0110; // 0x0110
	float unk_0114; // 0x0114
	float unk_0118; // 0x0118
	bool unk_011C; // 0x011C
	char pad_011D[3]; //0x011D
	uint32_t m_ArrestState; //0x0120
	uint32_t m_DeathState; //0x0124
	uint32_t m_WeaponHash; //0x0128
	uint32_t m_NumWeaponComponents; //0x012C
	uint32_t m_NumEquippedGadgets; //0x0130
	uint32_t m_VehicleSeat; //0x0134
	uint32_t m_ActionModeOverride; //0x0138
	uint32_t unk_013C; // 0x013C
	uint16_t m_VehicleId; //0x0140
	uint16_t m_MountId; //0x0142
	uint16_t m_CustodianId; //0x0144
	uint16_t unk_0146; // 0x0146
	uint8_t new_014C; 
	bool m_TintIndex; //0x0148
	char pad_0149; //0x0149
	uint8_t unk_014A; // 0x014A
	bool m_IsHandcuffed; //0x014B
	bool m_CanPerformArrest; //0x014C
	bool m_CanPerformUncuff; //0x014D
	bool m_CanBeArrested; //0x014E
	bool m_IsInCustody; //0x014F
	char pad_0150; //0x0150
	bool m_WeaponExists; //0x0151
	bool m_WeaponVisible; //0x0152
	bool m_WeaponHasAmmo; //0x0153
	bool m_WeaponAttachLeft; //0x0154
	char pad_0155; //0x0155
	bool m_InSeat; //0x0156
	bool m_InVehicle; //0x0157
	bool m_OnMount; //0x0158
	bool m_HasCustodianOrArrestFlags; //0x0159
	char pad_015A; //0x015A
	bool m_ActionModeEnabled; //0x015B
	bool m_StealthModeEnabled; //0x015C
	bool unk_015D; // 0x015D
	bool unk_015E; // 0x015E
	bool unk_015F; // 0x015F
	bool unk_0160; // 0x0160
	bool unk_0161; // 0x0161
	bool unk_0162; // 0x0162
	bool unk_0163; // 0x0163
	bool unk_0164; // 0x0164
	bool unk_0165; // 0x0165
	bool unk_0166; // 0x0166
	bool unk_0167; // 0x0167
	bool unk_0168; // 0x0168
	bool unk_0169; // 0x0169
	bool unk_016A; // 0x016A
	bool unk_016B; // 0x016B
	bool unk_016C; // 0x016C
	bool unk_016D; // 0x016D
	bool unk_016E; // 0x016E
	bool unk_016F; // 0x016F
	bool unk_0170; // 0x0170
	bool unk_0171; // 0x0171
	bool unk_0172; // 0x0172
}; //Size: 0x0174
static_assert(sizeof(CPedGameStateDataNode) == 0x178);