/* The session messages that carry a change to one of the town's villagers (data_021e5a2c,
 * eight of them) to the other systems, and the packing of their payloads, which the handlers
 * of session_message.h unpack:
 *
 *   59  the villager's four items from 0x7b0: the items (2 bytes each), then the villager's
 *       index (byte 8);
 *   58  the villager's item 0x7d2: the item (2 bytes), then the index (byte 2); sent only for
 *       items 0x11a8-0x12a7;
 *   63  the item of the villager's object: the same 3 bytes;
 *   61  the villager's object: the item (2 bytes), the index (high nibble of byte 2), a
 *       player's slot (bits 0-2) and a flag (bit 3), then the object's kind (byte 3).
 *
 * Each is sent, with kind 4, only while the session is linked, and only for a villager of the
 * town (its index, func_0207f294, below eight). */
#ifndef CLEAN_MAIN_SESSION_VILLAGER_H
#define CLEAN_MAIN_SESSION_VILLAGER_H

#include "types.h"

void SessionVillager_SendItems(u8 *villager, const u16 *items);
void SessionVillager_SendItemsByIndex(int index, const u16 *items);
void SessionVillager_UnpackItems(u32 *index, u16 *items, const u8 *bytes);
void SessionVillager_PackItems(u8 *bytes, char index, const u16 *items);
void SessionVillager_SendItem7D2(u8 *villager, const u16 *item);
void SessionVillager_SendItem7D2ByIndex(int index, const u16 *item);
u32 SessionVillager_UnpackItem(u32 *index, u16 *item, const u8 *bytes);
void SessionVillager_PackItem(u8 *bytes, u8 index, const u16 *item);
void SessionVillager_SendObjectItem(u8 *villager, const u16 *item);
void SessionVillager_SendObjectItemByIndex(u32 index, const u16 *item);
void SessionVillager_SendObject(u8 *villager, int kind, const u16 *item, int slot, u8 flag);
void SessionVillager_SendObjectByIndex(int index, int kind, const u16 *item, int slot, u8 flag);
void SessionVillager_UnpackObject(int *index, u8 *kind, u16 *item, int *slot, u8 *flag, const u8 *bytes);
void SessionVillager_PackObject(u8 *bytes, u32 index, u8 kind, const u16 *item, u32 slot, u8 flag);

#endif
