/* Session messages that change one of the town's villagers (session_villager.h). */
#include "session_villager.h"

#include "clean.h"
#include "main/packed_bytes.h"
#include "main/session.h"

#define VILLAGERS 8 /* the town's villagers (data_021e5a2c) */

/* The handlers of session_message.c the messages are for. */
#define HANDLER_ENTRY_SENDER 54
#define HANDLER_ENTRY_FILL 55
#define HANDLER_ENTRY_BYTE_6D 56
#define HANDLER_ENTRY_BYTE_6C 57
#define HANDLER_VILLAGER_ITEM_7D2 58
#define HANDLER_VILLAGER_ITEMS_7B0 59
#define HANDLER_OBJECT_CHANGE 60
#define HANDLER_VILLAGER_OBJECT 61
#define HANDLER_ENTRY_ITEM 62
#define HANDLER_VILLAGER_OBJECT_ITEM 63
#define MESSAGE_KIND 4

#define VILLAGER_ITEMS 4  /* the items from 0x7b0 */
#define ITEMS_SIZE 9      /* the payload of message 59 */
#define ITEM_SIZE 3       /* the payload of messages 58 and 63 */
#define OBJECT_SIZE 4     /* the payload of message 61 */
#define CHANGE_SIZE 2     /* the payload of message 60 */
#define ENTRY_ITEM_SIZE 3 /* the payload of message 62 */

/* The items SessionVillager_SendItem7D2ByIndex sends (and handler 58 takes). */
#define VILLAGER_ITEM_FIRST 0x11a8
#define VILLAGER_ITEM_LAST 0x12a7

extern NetSession *data_020ccf94; /* the session */

/* The villager's index among the town's villagers, -1 when it is none of them. */
extern int func_0207f294(u8 *villager);
/* Whether a number is below eight (one of the town's villagers). */
extern int func_0207cf74(int index);

/* Whether a message is to be sent for the villager: the session is linked and the villager is
 * one of the town's; its index in `index`. */
static int should_send(u8 *villager, int *index)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return 0;
    }
    *index = func_0207f294(villager);
    return func_0207cf74(*index) != 0;
}

/* Sends `size` bytes of `payload` to handler `handler`. */
static void send(const void *payload, int size, u32 handler)
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
    send(payload, ITEMS_SIZE, HANDLER_VILLAGER_ITEMS_7B0);
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

/* ---- Message 58: the item 0x7d2 */

/* func_020783a8: sends the villager's item 0x7d2 (`item`). */
void SessionVillager_SendItem7D2(u8 *villager, const u16 *item)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendItem7D2ByIndex(index, item);
    }
}
CLEAN_AS(func_020783a8, SessionVillager_SendItem7D2)

/* func_020783e0: sends the item 0x7d2 of villager `index`, when it is one of 0x11a8-0x12a7. */
void SessionVillager_SendItem7D2ByIndex(int index, const u16 *item)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    if (*item < VILLAGER_ITEM_FIRST || *item > VILLAGER_ITEM_LAST) {
        return;
    }
    u8 payload[4];
    SessionVillager_PackItem(payload, (u8) index, item);
    send(payload, ITEM_SIZE, HANDLER_VILLAGER_ITEM_7D2);
}
CLEAN_AS(func_020783e0, SessionVillager_SendItem7D2ByIndex)

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
    send(payload, ITEM_SIZE, HANDLER_VILLAGER_OBJECT_ITEM);
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
    u8 payload[OBJECT_SIZE];
    SessionVillager_PackObject(payload, (u32) index, (u8) kind, item, (u32) slot, flag != 0);
    send(payload, OBJECT_SIZE, HANDLER_VILLAGER_OBJECT);
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

/* func_0207860c: the object's byte 0x2e becomes `value`. */
void SessionVillager_SendObjectByte2E(u8 *villager, int value)
{
    SessionVillager_SendObjectChange(villager, value, VILLAGER_OBJECT_SET_BYTE_2E);
}
CLEAN_AS(func_0207860c, SessionVillager_SendObjectByte2E)

/* func_02078618: bit `bit` of the object's byte 0x30 is set, and its byte 0x2e becomes `bit`. */
void SessionVillager_SendObjectBit30(u8 *villager, int bit)
{
    SessionVillager_SendObjectChange(villager, bit, VILLAGER_OBJECT_SET_BIT_30);
}
CLEAN_AS(func_02078618, SessionVillager_SendObjectBit30)

/* func_02078624: the object's byte 0x2f becomes `value` (func_0209b8a4). */
void SessionVillager_SendObjectByte2F(u8 *villager, int value)
{
    SessionVillager_SendObjectChange(villager, value, VILLAGER_OBJECT_SET_BYTE_2F);
}
CLEAN_AS(func_02078624, SessionVillager_SendObjectByte2F)

/* func_02078630: operation 2 (func_0209b920), with the value 1, which it does not read. */
void SessionVillager_SendObjectOp2(u8 *villager)
{
    SessionVillager_SendObjectChange(villager, 1, VILLAGER_OBJECT_OP_2);
}
CLEAN_AS(func_02078630, SessionVillager_SendObjectOp2)

/* func_0207863c: the object is emptied (func_0209ba7c), with the value 0. */
void SessionVillager_SendObjectClear(u8 *villager)
{
    SessionVillager_SendObjectChange(villager, 0, VILLAGER_OBJECT_CLEAR);
}
CLEAN_AS(func_0207863c, SessionVillager_SendObjectClear)

/* func_02078648: the low 5 bits of the object's byte 0xb become `value` (func_0209bb90). */
void SessionVillager_SendObjectByte0B(u8 *villager, int value)
{
    SessionVillager_SendObjectChange(villager, value, VILLAGER_OBJECT_SET_BYTE_0B);
}
CLEAN_AS(func_02078648, SessionVillager_SendObjectByte0B)

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
    send(payload, CHANGE_SIZE, HANDLER_OBJECT_CHANGE);
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

/* ---- Message 62: the item 0x6a of a villager's entry */

/* func_02078710: sends the item 0x6a (`item`) of the villager's entry `entry`. */
void SessionVillager_SendEntryItem(u8 *villager, int entry, const u16 *item)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendEntryItemByIndex(index, entry, item);
    }
}
CLEAN_AS(func_02078710, SessionVillager_SendEntryItem)

/* func_02078748: sends the item 0x6a of entry `entry` of villager `index`. */
void SessionVillager_SendEntryItemByIndex(int index, int entry, const u16 *item)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    u8 payload[ENTRY_ITEM_SIZE];
    SessionVillager_PackEntryItem(payload, index, entry, item);
    send(payload, ENTRY_ITEM_SIZE, HANDLER_ENTRY_ITEM);
}
CLEAN_AS(func_02078748, SessionVillager_SendEntryItemByIndex)

/* func_02078794: the villager's index and the entry (byte 2), then the item (bytes 0-1). */
void SessionVillager_UnpackEntryItem(u32 *index, u32 *entry, u16 *item, const u8 *bytes)
{
    SessionVillager_UnpackEntry((int *) index, (int *) entry, &bytes[2]);
    *item = PackedBytes_ReadItem(bytes);
}
CLEAN_AS(func_02078794, SessionVillager_UnpackEntryItem)

/* func_020787b4: the villager's index and the entry into byte 2, then the item into bytes
 * 0-1. */
void SessionVillager_PackEntryItem(u8 *bytes, int index, int entry, const u16 *item)
{
    SessionVillager_PackEntry(&bytes[2], index, entry);
    PackedBytes_WriteItem(bytes, *item);
}
CLEAN_AS(func_020787b4, SessionVillager_PackEntryItem)

/* ---- Messages 57 and 56: the bytes 0x6c and 0x6d of a villager's entry */

/* Sends the villager's index and the entry (1 byte), then the low byte of `value`. */
static void send_entry_byte(int index, int entry, int value, u32 handler)
{
    u8 byte;
    u8 value_byte = (u8) value;
    SessionVillager_PackEntry(&byte, index, entry);
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, &byte, 1);
    Session_AppendMessage(session, &value_byte, 1);
    Session_EndMessage(session, handler, MESSAGE_KIND);
}

/* func_020787d4: sends the byte 0x6c (`value`) of the villager's entry `entry`. */
void SessionVillager_SendEntryByte6C(u8 *villager, int entry, int value)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendEntryByte6CByIndex(index, entry, value);
    }
}
CLEAN_AS(func_020787d4, SessionVillager_SendEntryByte6C)

/* func_0207880c: sends the byte 0x6c of entry `entry` of villager `index`. */
void SessionVillager_SendEntryByte6CByIndex(int index, int entry, int value)
{
    if (Session_IsLinked(data_020ccf94)) {
        send_entry_byte(index, entry, value, HANDLER_ENTRY_BYTE_6C);
    }
}
CLEAN_AS(func_0207880c, SessionVillager_SendEntryByte6CByIndex)

/* func_02078864: sends the byte 0x6d (`value`) of the villager's entry `entry`. */
void SessionVillager_SendEntryByte6D(u8 *villager, int entry, int value)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendEntryByte6DByIndex(index, entry, value);
    }
}
CLEAN_AS(func_02078864, SessionVillager_SendEntryByte6D)

/* func_0207889c: sends the byte 0x6d of entry `entry` of villager `index`. */
void SessionVillager_SendEntryByte6DByIndex(int index, int entry, int value)
{
    if (Session_IsLinked(data_020ccf94)) {
        send_entry_byte(index, entry, value, HANDLER_ENTRY_BYTE_6D);
    }
}
CLEAN_AS(func_0207889c, SessionVillager_SendEntryByte6DByIndex)

/* ---- Messages 55 and 54: a villager's entry and the sender's name */

/* Sends the villager's index and the entry (1 byte). */
static void send_entry(int index, int entry, u32 handler)
{
    u8 byte;
    SessionVillager_PackEntry(&byte, index, entry);
    send(&byte, 1, handler);
}

/* func_020788f4: the villager's entry `entry` is to be filled with this system's name. */
void SessionVillager_SendEntryFill(u8 *villager, int entry)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendEntryFillByIndex(index, entry);
    }
}
CLEAN_AS(func_020788f4, SessionVillager_SendEntryFill)

/* func_0207892c: as SessionVillager_SendEntryFill, for villager `index`. */
void SessionVillager_SendEntryFillByIndex(int index, int entry)
{
    if (Session_IsLinked(data_020ccf94)) {
        send_entry(index, entry, HANDLER_ENTRY_FILL);
    }
}
CLEAN_AS(func_0207892c, SessionVillager_SendEntryFillByIndex)

/* func_02078974: the villager's entry `entry` is to get this system's name. */
void SessionVillager_SendEntrySender(u8 *villager, int entry)
{
    int index;
    if (should_send(villager, &index)) {
        SessionVillager_SendEntrySenderByIndex(index, entry);
    }
}
CLEAN_AS(func_02078974, SessionVillager_SendEntrySender)

/* func_020789ac: as SessionVillager_SendEntrySender, for villager `index`. */
void SessionVillager_SendEntrySenderByIndex(int index, int entry)
{
    if (Session_IsLinked(data_020ccf94)) {
        send_entry(index, entry, HANDLER_ENTRY_SENDER);
    }
}
CLEAN_AS(func_020789ac, SessionVillager_SendEntrySenderByIndex)

/* ---- A villager and one of its entries in one byte */

/* func_020789f4: the villager's index (high nibble) and the entry (low nibble), written in that
 * order; the byte is read again after the first write. */
void SessionVillager_UnpackEntry(int *index, int *entry, const u8 *byte)
{
    *index = (*byte >> 4) & 0xf;
    *entry = *byte & 0xf;
}
CLEAN_AS(func_020789f4, SessionVillager_UnpackEntry)

/* func_02078a0c: the low nibbles of the villager's index (high) and the entry (low). */
void SessionVillager_PackEntry(u8 *byte, int index, int entry)
{
    *byte = (u8) ((((u32) index << 4) & 0xf0) | ((u32) entry & 0xf));
}
CLEAN_AS(func_02078a0c, SessionVillager_PackEntry)
