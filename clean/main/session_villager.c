/* Session messages that change one of the town's villagers (session_villager.h). */
#include "session_villager.h"

#include "clean.h"
#include "main/packed_bytes.h"
#include "main/session.h"
#include "actor_table.h"
#include "villager_status.h"

#define VILLAGERS 8 /* the town's villagers (data_021e5a2c) */

/* The handlers of session_message.c the messages are for. */
#define HANDLER_MEMORY_TAKE 54
#define HANDLER_MEMORY_UPDATE 55
#define HANDLER_ENTRY_BYTE_6D 56
#define HANDLER_ENTRY_BYTE_6C 57
#define HANDLER_VILLAGER_ITEM_7D2 58
#define HANDLER_VILLAGER_ITEMS_7B0 59
#define HANDLER_OBJECT_CHANGE 60
#define HANDLER_VILLAGER_OBJECT 61
#define HANDLER_ENTRY_ITEM 62
#define HANDLER_VILLAGER_OBJECT_ITEM 63
#define MESSAGE_KIND 4

#define VILLAGER_ITEMS 4               /* the items from 0x7b0 */
#define ITEMS_SIZE 9                   /* the payload of message 59 */
#define ITEM_SIZE 3                    /* the payload of messages 58 and 63 */
#define SESSION_VILLAGER_OBJECT_SIZE 4 /* the payload of message 61 */
#define CHANGE_SIZE 2                  /* the payload of message 60 */
#define ENTRY_ITEM_SIZE 3              /* the payload of message 62 */

/* The items SessionVillager_SendClothesByIndex sends (and handler 58 takes). */
#define VILLAGER_ITEM_FIRST 0x11a8
#define VILLAGER_ITEM_LAST 0x12a7

extern NetSession *data_020ccf94; /* the session */

/* Whether a message is to be sent for the villager: the session is linked and the villager is
 * one of the town's; its index in `index`. */
static int should_send(u8 *villager, int *index)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return 0;
    }
    *index = VillagerStatus_Index(villager);
    return ActorTable_IsKindESlot(*index) != 0;
}

/* Sends `size` bytes of `payload` to handler `handler`. */
static void send_message(const void *payload, int size, u32 handler)
{
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, payload, size);
    Session_EndMessage(session, handler, MESSAGE_KIND);
}

/* ---- Message 59: the four items from 0x7b0 */

/* func_020782d8: sends the villager's four items (`items`, its item 0x7b0). */
void SessionVillager_SendItems(u8 *villager, const u16 *items)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendItemsByIndex(index, items);
    }
}
CLEAN_AS(func_020782d8, SessionVillager_SendItems)

/* func_02078310: sends the four items of villager `index`; nothing when `items` is NULL. */
void SessionVillager_SendItemsByIndex(int index, const u16 *items)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    if (items == NULL) {
        return;
    }
    u8 payload[12];
    SessionVillager_PackItems(payload, (char) index, items);
    send_message(payload, ITEMS_SIZE, HANDLER_VILLAGER_ITEMS_7B0);
}
CLEAN_AS(func_02078310, SessionVillager_SendItemsByIndex)

/* func_0207835c: the villager's index (byte 8) and its four items. */
void SessionVillager_UnpackItems(u32 *index, u16 *items, const u8 *bytes)
{
    *index = bytes[8];
    for (int i = 0; i < VILLAGER_ITEMS; i++) {
        items[i] = PackedBytes_ReadItem(&bytes[2 * i]);
    }
}
CLEAN_AS(func_0207835c, SessionVillager_UnpackItems)

/* func_02078380: the four items, then the villager's index (byte 8). */
void SessionVillager_PackItems(u8 *bytes, char index, const u16 *items)
{
    for (int i = 0; i < VILLAGER_ITEMS; i++) {
        PackedBytes_WriteItem(&bytes[2 * i], items[i]);
    }
    bytes[8] = (u8) index;
}
CLEAN_AS(func_02078380, SessionVillager_PackItems)

/* ---- Message 58: the villager's clothes (0x7d2) */

/* func_020783a8: sends the villager's clothes (`item`, its item 0x7d2). */
void SessionVillager_SendClothes(u8 *villager, const u16 *item)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendClothesByIndex(index, item);
    }
}
CLEAN_AS(func_020783a8, SessionVillager_SendClothes)

/* func_020783e0: sends the clothes of villager `index`, when they are one of 0x11a8-0x12a7. */
void SessionVillager_SendClothesByIndex(int index, const u16 *item)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    if (*item < VILLAGER_ITEM_FIRST || *item > VILLAGER_ITEM_LAST) {
        return;
    }
    u8 payload[4];
    SessionVillager_PackItem(payload, (u8) index, item);
    send_message(payload, ITEM_SIZE, HANDLER_VILLAGER_ITEM_7D2);
}
CLEAN_AS(func_020783e0, SessionVillager_SendClothesByIndex)

/* func_02078448: the villager's index (byte 2) and the item; returns the item. */
u32 SessionVillager_UnpackItem(u32 *index, u16 *item, const u8 *bytes)
{
    *index = bytes[2];
    u16 read = PackedBytes_ReadItem(bytes);
    *item = read;
    return read;
}
CLEAN_AS(func_02078448, SessionVillager_UnpackItem)

/* func_02078460: the item, then the villager's index (byte 2). The item's address goes to
 * PackedBytes_WriteItem as a third argument, which it does not read. */
void SessionVillager_PackItem(u8 *bytes, u8 index, const u16 *item)
{
    PackedBytes_WriteItem(bytes, *item, item);
    bytes[2] = index;
}
CLEAN_AS(func_02078460, SessionVillager_PackItem)

/* ---- Message 63: the item of the villager's object */

/* func_02078478: sends the item of the villager's object (`item`). */
void SessionVillager_SendObjectItem(u8 *villager, const u16 *item)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendObjectItemByIndex((u32) index, item);
    }
}
CLEAN_AS(func_02078478, SessionVillager_SendObjectItem)

/* func_020784b0: sends the item of villager `index`'s object.
 * QUIRK: the payload is 3 bytes, but handler 63 reads 4 (the fourth is not used). */
void SessionVillager_SendObjectItemByIndex(u32 index, const u16 *item)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    u8 payload[4];
    SessionVillager_PackItem(payload, (u8) index, item);
    send_message(payload, ITEM_SIZE, HANDLER_VILLAGER_OBJECT_ITEM);
}
CLEAN_AS(func_020784b0, SessionVillager_SendObjectItemByIndex)

/* ---- Message 61: the villager's object */

/* func_020784f8: sends the villager's object: its kind and item, and the slot of the player it
 * names and a flag. */
void SessionVillager_SendObject(u8 *villager, int kind, const u16 *item, int slot, u8 flag)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendObjectByIndex(index, kind, item, slot, flag);
    }
}
CLEAN_AS(func_020784f8, SessionVillager_SendObject)

/* func_02078540: sends the object of villager `index`; the flag goes as 0 or 1. */
void SessionVillager_SendObjectByIndex(int index, int kind, const u16 *item, int slot, u8 flag)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    u8 payload[SESSION_VILLAGER_OBJECT_SIZE];
    SessionVillager_PackObject(payload, (u32) index, (u8) kind, item, (u32) slot, flag != 0);
    send_message(payload, SESSION_VILLAGER_OBJECT_SIZE, HANDLER_VILLAGER_OBJECT);
}
CLEAN_AS(func_02078540, SessionVillager_SendObjectByIndex)

/* func_020785a4: the villager's index, the slot and the flag from byte 2, the kind (byte 3) and
 * the item (bytes 0-1). */
void SessionVillager_UnpackObject(int *index, u8 *kind, u16 *item, int *slot, u8 *flag, const u8 *bytes)
{
    *index = (bytes[2] >> 4) & 0xf;
    *slot = bytes[2] & 7;
    *flag = (bytes[2] >> 3) & 1;
    *kind = bytes[3];
    *item = PackedBytes_ReadItem(bytes);
}
CLEAN_AS(func_020785a4, SessionVillager_UnpackObject)

/* func_020785dc: byte 2 the villager's index (high nibble), the flag (bit 3) and the slot
 * (bits 0-2), byte 3 the kind, then the item in bytes 0-1. */
void SessionVillager_PackObject(u8 *bytes, u32 index, u8 kind, const u16 *item, u32 slot, u8 flag)
{
    bytes[2] = (u8) (((index << 4) & 0xf0) | ((flag & 1u) << 3) | (slot & 7));
    bytes[3] = kind;
    PackedBytes_WriteItem(bytes, *item);
}
CLEAN_AS(func_020785dc, SessionVillager_PackObject)

/* ---- Message 60: a change to the villager's object */

/* func_0207860c: the object's count (0x2e) becomes `value`. */
void SessionVillager_SendObjectCount(u8 *villager, int value)
{
    SessionVillager_SendObjectChange(villager, value, SESSION_VILLAGER_OBJECT_SET_COUNT);
}
CLEAN_AS(func_0207860c, SessionVillager_SendObjectCount)

/* func_02078618: bit `bit` of the object's flags (0x30) is set, and its count becomes `bit`. */
void SessionVillager_SendObjectFlag(u8 *villager, int bit)
{
    SessionVillager_SendObjectChange(villager, bit, SESSION_VILLAGER_OBJECT_SET_FLAG);
}
CLEAN_AS(func_02078618, SessionVillager_SendObjectFlag)

/* func_02078624: the object's kind (0x2f) becomes `value` (VillagerObject_SetKind). */
void SessionVillager_SendObjectKind(u8 *villager, int value)
{
    SessionVillager_SendObjectChange(villager, value, SESSION_VILLAGER_OBJECT_SET_KIND);
}
CLEAN_AS(func_02078624, SessionVillager_SendObjectKind)

/* func_02078630: operation 2 (func_0209b920), with the value 1, which it does not read. */
void SessionVillager_SendObjectNextStep(u8 *villager)
{
    SessionVillager_SendObjectChange(villager, 1, SESSION_VILLAGER_OBJECT_NEXT_STEP);
}
CLEAN_AS(func_02078630, SessionVillager_SendObjectNextStep)

/* func_0207863c: the object is emptied (func_0209ba7c), with the value 0. */
void SessionVillager_SendObjectClear(u8 *villager)
{
    SessionVillager_SendObjectChange(villager, 0, SESSION_VILLAGER_OBJECT_CLEAR);
}
CLEAN_AS(func_0207863c, SessionVillager_SendObjectClear)

/* func_02078648: the low 5 bits of the object's byte 0xb become `value` (func_0209bb90). */
void SessionVillager_SendObjectByte0b(u8 *villager, int value)
{
    SessionVillager_SendObjectChange(villager, value, SESSION_VILLAGER_OBJECT_SET_BYTE_0B);
}
CLEAN_AS(func_02078648, SessionVillager_SendObjectByte0b)

/* func_02078654: sends operation `operation` (VILLAGER_OBJECT_*) with `value` on the
 * villager's object. */
void SessionVillager_SendObjectChange(u8 *villager, int value, int operation)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendObjectChangeByIndex(index, value, operation);
    }
}
CLEAN_AS(func_02078654, SessionVillager_SendObjectChange)

/* func_0207868c: sends operation `operation` with `value` on the object of villager `index`. */
void SessionVillager_SendObjectChangeByIndex(int index, int value, int operation)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    u8 payload[CHANGE_SIZE];
    SessionVillager_PackObjectChange(payload, (char) index, (char) operation, (char) value);
    send_message(payload, CHANGE_SIZE, HANDLER_OBJECT_CHANGE);
}
CLEAN_AS(func_0207868c, SessionVillager_SendObjectChangeByIndex)

/* func_020786d8: the villager's index (high nibble of byte 0), the operation (low nibble) and
 * the value (byte 1), written in that order; each byte is read after the write before it. */
void SessionVillager_UnpackObjectChange(u32 *index, u8 *operation, u8 *value, const u8 *bytes)
{
    *index = (bytes[0] >> 4) & 0xf;
    *operation = bytes[0] & 0xf;
    *value = bytes[1];
}
CLEAN_AS(func_020786d8, SessionVillager_UnpackObjectChange)

/* func_020786f8: byte 0 the low nibbles of the index (high) and the operation (low), byte 1 the
 * value. */
void SessionVillager_PackObjectChange(u8 *bytes, char index, char operation, char value)
{
    bytes[0] = (u8) ((((u32) (u8) index << 4) & 0xf0) | ((u8) operation & 0xfu));
    bytes[1] = (u8) value;
}
CLEAN_AS(func_020786f8, SessionVillager_PackObjectChange)

/* ---- Message 62: the item 0x6a of a villager's memory of a player */

/* func_02078710: sends the item 0x6a (`item`) of the villager's memory `entry`. */
void SessionVillager_SendMemoryItem(u8 *villager, int entry, const u16 *item)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendMemoryItemByIndex(index, entry, item);
    }
}
CLEAN_AS(func_02078710, SessionVillager_SendMemoryItem)

/* func_02078748: sends the item 0x6a of memory `entry` of villager `index`. */
void SessionVillager_SendMemoryItemByIndex(int index, int entry, const u16 *item)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    u8 payload[ENTRY_ITEM_SIZE];
    SessionVillager_PackMemoryItem(payload, index, entry, item);
    send_message(payload, ENTRY_ITEM_SIZE, HANDLER_ENTRY_ITEM);
}
CLEAN_AS(func_02078748, SessionVillager_SendMemoryItemByIndex)

/* func_02078794: the villager's index and the entry (byte 2), then the item (bytes 0-1). */
void SessionVillager_UnpackMemoryItem(u32 *index, u32 *entry, u16 *item, const u8 *bytes)
{
    SessionVillager_UnpackMemory((int *) index, (int *) entry, &bytes[2]);
    *item = PackedBytes_ReadItem(bytes);
}
CLEAN_AS(func_02078794, SessionVillager_UnpackMemoryItem)

/* func_020787b4: the villager's index and the entry into byte 2, then the item into bytes
 * 0-1. */
void SessionVillager_PackMemoryItem(u8 *bytes, int index, int entry, const u16 *item)
{
    SessionVillager_PackMemory(&bytes[2], index, entry);
    PackedBytes_WriteItem(bytes, *item);
}
CLEAN_AS(func_020787b4, SessionVillager_PackMemoryItem)

/* ---- Messages 57 and 56: the fondness (0x6c) and the impression (0x6d) of a villager's memory */

/* Sends the villager's index and the entry (1 byte), then the low byte of `value`. */
static void send_entry_byte(int index, int entry, int value, u32 handler)
{
    u8 byte;
    u8 value_byte = (u8) value;
    SessionVillager_PackMemory(&byte, index, entry);
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, &byte, 1);
    Session_AppendMessage(session, &value_byte, 1);
    Session_EndMessage(session, handler, MESSAGE_KIND);
}

/* func_020787d4: sends the fondness (`value`, byte 0x6c) of the villager's memory `entry`. */
void SessionVillager_SendMemoryFondness(u8 *villager, int entry, int value)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendMemoryFondnessByIndex(index, entry, value);
    }
}
CLEAN_AS(func_020787d4, SessionVillager_SendMemoryFondness)

/* func_0207880c: sends the fondness of memory `entry` of villager `index`. */
void SessionVillager_SendMemoryFondnessByIndex(int index, int entry, int value)
{
    if (Session_IsLinked(data_020ccf94)) {
        send_entry_byte(index, entry, value, HANDLER_ENTRY_BYTE_6C);
    }
}
CLEAN_AS(func_0207880c, SessionVillager_SendMemoryFondnessByIndex)

/* func_02078864: sends the impression (`value`, byte 0x6d) of the villager's memory `entry`. */
void SessionVillager_SendMemoryImpression(u8 *villager, int entry, int value)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendMemoryImpressionByIndex(index, entry, value);
    }
}
CLEAN_AS(func_02078864, SessionVillager_SendMemoryImpression)

/* func_0207889c: sends the impression of memory `entry` of villager `index`. */
void SessionVillager_SendMemoryImpressionByIndex(int index, int entry, int value)
{
    if (Session_IsLinked(data_020ccf94)) {
        send_entry_byte(index, entry, value, HANDLER_ENTRY_BYTE_6D);
    }
}
CLEAN_AS(func_0207889c, SessionVillager_SendMemoryImpressionByIndex)

/* ---- Messages 55 and 54: a villager's memory and the sender's name */

/* Sends the villager's index and the entry (1 byte). */
static void send_entry(int index, int entry, u32 handler)
{
    u8 byte;
    SessionVillager_PackMemory(&byte, index, entry);
    send_message(&byte, 1, handler);
}

/* func_020788f4: the villager's memory `entry` is to be updated for a meeting with this
 * system's player. */
void SessionVillager_SendMemoryUpdate(u8 *villager, int entry)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendMemoryUpdateByIndex(index, entry);
    }
}
CLEAN_AS(func_020788f4, SessionVillager_SendMemoryUpdate)

/* func_0207892c: as SessionVillager_SendMemoryUpdate, for villager `index`. */
void SessionVillager_SendMemoryUpdateByIndex(int index, int entry)
{
    if (Session_IsLinked(data_020ccf94)) {
        send_entry(index, entry, HANDLER_MEMORY_UPDATE);
    }
}
CLEAN_AS(func_0207892c, SessionVillager_SendMemoryUpdateByIndex)

/* func_02078974: the villager's memory `entry` is to be taken for this system's player. */
void SessionVillager_SendMemoryTake(u8 *villager, int entry)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendMemoryTakeByIndex(index, entry);
    }
}
CLEAN_AS(func_02078974, SessionVillager_SendMemoryTake)

/* func_020789ac: as SessionVillager_SendMemoryTake, for villager `index`. */
void SessionVillager_SendMemoryTakeByIndex(int index, int entry)
{
    if (Session_IsLinked(data_020ccf94)) {
        send_entry(index, entry, HANDLER_MEMORY_TAKE);
    }
}
CLEAN_AS(func_020789ac, SessionVillager_SendMemoryTakeByIndex)

/* ---- A villager and one of its entries in one byte */

/* func_020789f4: the villager's index (high nibble) and the entry (low nibble), written in that
 * order; the byte is read again after the first write. */
void SessionVillager_UnpackMemory(int *index, int *entry, const u8 *byte)
{
    *index = (*byte >> 4) & 0xf;
    *entry = *byte & 0xf;
}
CLEAN_AS(func_020789f4, SessionVillager_UnpackMemory)

/* func_02078a0c: the low nibbles of the villager's index (high) and the entry (low). */
void SessionVillager_PackMemory(u8 *byte, int index, int entry)
{
    *byte = (u8) ((((u32) index << 4) & 0xf0) | ((u32) entry & 0xf));
}
CLEAN_AS(func_02078a0c, SessionVillager_PackMemory)
