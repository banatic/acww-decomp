/* Session messages that change one of the town's villagers (session_villager.h). */
#include "session_villager.h"

#include "clean.h"
#include "main/packed_bytes.h"
#include "main/session.h"

#define VILLAGERS 8 /* the town's villagers (data_021e5a2c) */

/* The handlers of session_message.c the messages are for. */
#define HANDLER_VILLAGER_ITEM_7D2 58
#define HANDLER_VILLAGER_ITEMS_7B0 59
#define HANDLER_VILLAGER_OBJECT 61
#define HANDLER_VILLAGER_OBJECT_ITEM 63
#define MESSAGE_KIND 4

#define VILLAGER_ITEMS 4 /* the items from 0x7b0 */
#define ITEMS_SIZE 9     /* the payload of message 59 */
#define ITEM_SIZE 3      /* the payload of messages 58 and 63 */
#define OBJECT_SIZE 4    /* the payload of message 61 */

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
