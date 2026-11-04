/* The session messages that carry a change to one of the town's villagers (data_021e5a2c,
 * eight of them) to the other systems, and the packing of their payloads, which the handlers
 * of session_message.h unpack:
 *
 *   59  the villager's four items from 0x7b0: the items (2 bytes each), then the villager's
 *       index (byte 8);
 *   58  the villager's clothes (0x7d2): the item (2 bytes), then the index (byte 2); sent only for
 *       items 0x11a8-0x12a7;
 *   63  the item of the villager's object: the same 3 bytes;
 *   61  the villager's object: the item (2 bytes), the index (high nibble of byte 2), a
 *       player's slot (bits 0-2) and a flag (bit 3), then the object's kind (byte 3);
 *   60  a change to the villager's object (villager_object.h): the index (high nibble of
 *       byte 0), the operation (low nibble, VILLAGER_OBJECT_*) and a value (byte 1);
 *   62  the item 0x6a of one of the villager's memories of a player (villager_memories.h):
 *       the item (2 bytes), then the index (high nibble of byte 2) and the memory (low nibble);
 *   57  the memory's fondness (0x6c): the index and memory (byte 0, as in 62), then the value;
 *   56  the memory's impression (0x6d): the same 2 bytes;
 *   55  the memory is filled with the sender's name: the index and memory (1 byte);
 *   54  the memory gets the sender's name: the same byte.
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
void SessionVillager_SendClothes(u8 *villager, const u16 *item);
void SessionVillager_SendClothesByIndex(int index, const u16 *item);
u32 SessionVillager_UnpackItem(u32 *index, u16 *item, const u8 *bytes);
void SessionVillager_PackItem(u8 *bytes, u8 index, const u16 *item);
void SessionVillager_SendObjectItem(u8 *villager, const u16 *item);
void SessionVillager_SendObjectItemByIndex(u32 index, const u16 *item);
void SessionVillager_SendObject(u8 *villager, int kind, const u16 *item, int slot, u8 flag);
void SessionVillager_SendObjectByIndex(int index, int kind, const u16 *item, int slot, u8 flag);
void SessionVillager_UnpackObject(int *index, u8 *kind, u16 *item, int *slot, u8 *flag, const u8 *bytes);
void SessionVillager_PackObject(u8 *bytes, u32 index, u8 kind, const u16 *item, u32 slot, u8 flag);

/* The operations of message 60 on the villager's object (SessionMessage_ChangeVillagerObject). */
enum {
    VILLAGER_OBJECT_SET_BYTE_0B = 0, /* func_0209bb90: the low 5 bits of its byte 0xb */
    VILLAGER_OBJECT_CLEAR = 1,       /* func_0209ba7c: emptied */
    VILLAGER_OBJECT_NEXT_STEP = 2,   /* func_0209b920, VillagerObject_NextStep */
    VILLAGER_OBJECT_SET_KIND = 3,    /* func_0209b8a4, VillagerObject_SetKind: its kind (0x2f) */
    VILLAGER_OBJECT_SET_FLAG = 4,    /* func_0209b890, VillagerObject_SetFlag (0x30), then as VILLAGER_OBJECT_SET_COUNT */
    VILLAGER_OBJECT_SET_COUNT = 5    /* its count (0x2e) */
};

void SessionVillager_SendObjectCount(u8 *villager, int value);
void SessionVillager_SendObjectFlag(u8 *villager, int bit);
void SessionVillager_SendObjectKind(u8 *villager, int value);
void SessionVillager_SendObjectNextStep(u8 *villager);
void SessionVillager_SendObjectClear(u8 *villager);
void SessionVillager_SendObjectByte0B(u8 *villager, int value);
void SessionVillager_SendObjectChange(u8 *villager, int value, int operation);
void SessionVillager_SendObjectChangeByIndex(int index, int value, int operation);
void SessionVillager_UnpackObjectChange(u32 *index, u8 *operation, u8 *value, const u8 *bytes);
void SessionVillager_PackObjectChange(u8 *bytes, char index, char operation, char value);

void SessionVillager_SendMemoryItem(u8 *villager, int entry, const u16 *item);
void SessionVillager_SendMemoryItemByIndex(int index, int entry, const u16 *item);
void SessionVillager_UnpackMemoryItem(u32 *index, u32 *entry, u16 *item, const u8 *bytes);
void SessionVillager_PackMemoryItem(u8 *bytes, int index, int entry, const u16 *item);
void SessionVillager_SendMemoryFondness(u8 *villager, int entry, int value);
void SessionVillager_SendMemoryFondnessByIndex(int index, int entry, int value);
void SessionVillager_SendMemoryImpression(u8 *villager, int entry, int value);
void SessionVillager_SendMemoryImpressionByIndex(int index, int entry, int value);
void SessionVillager_SendMemoryFill(u8 *villager, int entry);
void SessionVillager_SendMemoryFillByIndex(int index, int entry);
void SessionVillager_SendMemorySender(u8 *villager, int entry);
void SessionVillager_SendMemorySenderByIndex(int index, int entry);
void SessionVillager_UnpackMemory(int *index, int *entry, const u8 *byte);
void SessionVillager_PackMemory(u8 *byte, int index, int entry);

#endif
