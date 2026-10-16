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
 *       player's slot (bits 0-2) and a flag (bit 3), then the object's kind (byte 3);
 *   60  a change to the villager's object: the index (high nibble of byte 0), the operation
 *       (low nibble, VILLAGER_OBJECT_*) and a value (byte 1);
 *   62  the item 0x6a of one of the villager's entries (func_020807c0): the item (2 bytes),
 *       then the index (high nibble of byte 2) and the entry (low nibble);
 *   57  the entry's byte 0x6c: the index and entry (byte 0, as in 62), then the value;
 *   56  the entry's byte 0x6d: the same 2 bytes;
 *   55  the entry is filled with the sender's name: the index and entry (1 byte);
 *   54  the entry gets the sender's name: the same byte.
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

/* The operations of message 60 on the villager's object (SessionMessage_ChangeVillagerObject). */
enum {
    VILLAGER_OBJECT_SET_BYTE_0B = 0, /* func_0209bb90: the low 5 bits of its byte 0xb */
    VILLAGER_OBJECT_CLEAR = 1,       /* func_0209ba7c: emptied */
    VILLAGER_OBJECT_OP_2 = 2,        /* func_0209b920 */
    VILLAGER_OBJECT_SET_BYTE_2F = 3, /* func_0209b8a4 */
    VILLAGER_OBJECT_SET_BIT_30 = 4,  /* func_0209b890, then as VILLAGER_OBJECT_SET_BYTE_2E */
    VILLAGER_OBJECT_SET_BYTE_2E = 5  /* its byte 0x2e */
};

void SessionVillager_SendObjectByte2E(u8 *villager, int value);
void SessionVillager_SendObjectBit30(u8 *villager, int bit);
void SessionVillager_SendObjectByte2F(u8 *villager, int value);
void SessionVillager_SendObjectOp2(u8 *villager);
void SessionVillager_SendObjectClear(u8 *villager);
void SessionVillager_SendObjectByte0B(u8 *villager, int value);
void SessionVillager_SendObjectChange(u8 *villager, int value, int operation);
void SessionVillager_SendObjectChangeByIndex(int index, int value, int operation);
void SessionVillager_UnpackObjectChange(u32 *index, u8 *operation, u8 *value, const u8 *bytes);
void SessionVillager_PackObjectChange(u8 *bytes, char index, char operation, char value);

void SessionVillager_SendEntryItem(u8 *villager, int entry, const u16 *item);
void SessionVillager_SendEntryItemByIndex(int index, int entry, const u16 *item);
void SessionVillager_UnpackEntryItem(u32 *index, u32 *entry, u16 *item, const u8 *bytes);
void SessionVillager_PackEntryItem(u8 *bytes, int index, int entry, const u16 *item);
void SessionVillager_SendEntryByte6C(u8 *villager, int entry, int value);
void SessionVillager_SendEntryByte6CByIndex(int index, int entry, int value);
void SessionVillager_SendEntryByte6D(u8 *villager, int entry, int value);
void SessionVillager_SendEntryByte6DByIndex(int index, int entry, int value);
void SessionVillager_SendEntryFill(u8 *villager, int entry);
void SessionVillager_SendEntryFillByIndex(int index, int entry);
void SessionVillager_SendEntrySender(u8 *villager, int entry);
void SessionVillager_SendEntrySenderByIndex(int index, int entry);
void SessionVillager_UnpackEntry(int *index, int *entry, const u8 *byte);
void SessionVillager_PackEntry(u8 *byte, int index, int entry);

#endif
