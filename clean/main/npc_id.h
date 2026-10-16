/* A reference to one of the game's villagers (16 bytes): a 14-byte head, the villager's
 * personality and its number.
 *
 * The number picks the villager's name ("st_npc_name", 150 villagers); 0xff is none. The
 * personality is one of six, 6 for none; resource names start with its prefix ("bo_", "ha_",
 * "ko_", "fu_", "ge_", "ta_"), and the first three and the last three form two groups
 * (Personality_Group). The head is copied, cleared and tested by its own functions
 * (func_020642a8 to func_020642fc); a nonzero first halfword marks it as set. */
#ifndef CLEAN_MAIN_NPC_ID_H
#define CLEAN_MAIN_NPC_ID_H

#include "types.h"

#define NPC_COUNT 150
#define NPC_NONE 0xff
#define PERSONALITY_COUNT 6
#define PERSONALITY_NONE 6

typedef struct NpcIdHead {
    u16 id; /* zero: not set */
    u8 data[12];
} NpcIdHead;

typedef struct NpcId {
    NpcIdHead head;
    u8 personality; /* 0x0e */
    u8 number;      /* 0x0f */
} NpcId;

int NpcId_FormatName(const NpcId *npc, char *dst);
int Npc_IsValidNumber(u32 number);
int NpcId_Number(const NpcId *npc);
int NpcId_PersonalityKind(const NpcId *npc);
int Personality_Kind(u32 personality);
int NpcId_FormatResourceName(const NpcId *npc, char *dst, int size, const char *name);
int Personality_FormatResourceName(char *dst, int size, const char *name, int personality);
u32 NpcId_PersonalityGroup(const NpcId *npc);
u32 Personality_Group(u32 personality);
int NpcId_Personality(const NpcId *npc);
void NpcId_Set(NpcId *npc, u8 number, u8 personality, const NpcIdHead *head);
int NpcId_IsValid(const NpcId *npc);
void NpcId_Copy(NpcId *dst, const NpcId *src);
void NpcId_Clear(NpcId *npc);
int NpcId_Destruct(NpcId *npc);
NpcId *NpcId_ConstructCopy(NpcId *npc, const NpcId *src);
int NpcId_Construct(NpcId *npc);
void NpcId_CopyTo(const NpcId *src, NpcId *dst);
void NpcId_Assign(NpcId *npc, const NpcId *src);

#endif
