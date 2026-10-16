/* The handlers of session messages (session_message.h). */
#include "session_message.h"

#include "clean.h"
#include "main/session.h"
#include "main/session_link.h"

/* The scene (func_020b65c4) the activity handlers act in. */
#define SCENE_2E 46

#define NO_ITEM 0xfff1 /* an empty item */

/* The item ids SessionMessage_SetVillagerItem7D2 and SessionMessage_SetVillagerObjectItem take. */
#define VILLAGER_ITEM_FIRST 0x11a8
#define VILLAGER_ITEM_LAST 0x12a7
#define OBJECT0_ITEM_FIRST 0x12b0 /* for an object of type 0 */
#define OBJECT0_ITEM_LAST 0x12e7
#define OBJECT1_ITEM_FIRST 0x12e8 /* for an object of type 1 */
#define OBJECT1_ITEM_LAST 0x131f

typedef void SessionMessageHandler(int size, int kind, u8 scene, u32 slot);

extern NetSession *data_020ccf94;                    /* the session */
extern SessionMessageHandler *const data_020cd0dc[]; /* the handlers, by number */
extern u8 data_021e5a2c[];                           /* the villagers (0x7ec bytes each) */
extern const char data_021dc7aa[];

extern u8 func_020b65c4(void);  /* the current scene */
extern u8 *func_020a132c(void); /* the current activity object (data_021f3c3c), or NULL */

/* The activity object's setters: the byte at the offset in their name plus the slot. */
extern void func_020a1240(u8 *activity, int slot, int value); /* 0xeb + slot */
extern void func_020a1248(u8 *activity, int slot, int value); /* 0xe7 + slot */
extern void func_020a1208(u8 *activity, int slot, int value); /* 0xf4 + slot */
extern void func_020a1264(u8 *activity, u8 value);            /* 0xe6 */
extern void func_020a1210(u8 value);                          /* 0xf3 of the current activity */

/* The link state (data_021f4320) and its parts. */
extern void func_020a6f74(int slot, int status); /* sets a slot's link status */
extern void func_020a6f20(int slot, int value);  /* its word 0xa8 + 4 * slot */
extern void func_020a6f10(int value);            /* its word 0xa4 */
extern void func_020a6f34(int value);            /* through func_020a5bf8 */
extern void func_020a6e8c(int slot, int value);  /* its byte 0x68 + slot */
extern void func_020a6e7c(int slot);             /* its word 0x74 */
extern void func_020a6e6c(int value);            /* its byte 0x7c */
extern void func_020a6db0(void);                 /* takes in a received category 15 bundle */
extern void func_020a7380(int slot, u8 value);   /* its word 0x2c + 4 * slot */
extern void func_020a7408(int slot, u8 value);   /* the first free pair from 0x0c takes both */
/* A link state entry as two bytes: made (func_020a7880, func_020a7820), ended (func_020a7870,
 * func_020a7810), and read out (func_020a7830 the three bytes and the fields set,
 * func_020a77dc also the slot it is for). */
extern u8 *func_020a7880(u8 *entry);
extern u8 *func_020a7870(u8 *entry);
extern u8 *func_020a7820(u8 *entry);
extern u8 *func_020a7810(u8 *entry);
extern void func_020a7830(const u8 *entry, u8 *byte0, u8 *byte1, u8 *byte2, u32 *fields);
extern void func_020a77dc(const u8 *entry, int *slot, u8 *byte0, u8 *byte1, u8 *byte2, int *fields);
extern void func_020a7394(int slot, int byte0, int byte1, int byte2, int fields); /* the 3-byte entries */
extern void func_020a7360(int slot, u8 byte0, u8 byte1, u8 byte2, int fields);    /* the entries from 0x3c */
/* A status byte, split by func_020a7684 into bits 0-2, 5-7 and 3-4. */
extern void func_020a76cc(u8 *byte);
extern void func_020a76c8(u8 *byte);
extern void func_020a7684(const u8 *byte, int *low, int *high, int *middle);
/* A one-byte value: made (func_020a7948), ended (func_020a7944), copied (func_020a7938). */
extern void func_020a7948(u8 *value);
extern void func_020a7944(u8 *value);
extern void func_020a7938(const u8 *src, u8 *dst);

/* Town items: an item record is the item (2 bytes), a source byte (the scene in bits 0-5 and a
 * flag in bits 6-7, func_02077a34) and the x and y (signed bytes). */
extern u16 func_02077898(const u8 *bytes); /* a little-endian u16 */
extern void func_02077a34(const u8 *source, u8 *scene, u8 *flag);
extern int func_0205fa84(u8 *record); /* puts an item record on the town map */
/* Puts an item on the town map here, or sends it on as message 19. */
extern void func_0205f9d4(int x, int y, int scene, int item, int flag);

/* The two halves of message 53 and its answer 52 (func_0209d57c, func_0209d4c0). */
extern void func_0209d498(const u8 *answer);
extern void func_0209d484(const u8 *request, int slot);

/* The villagers. A payload byte names a villager in its high nibble and an entry of it in its
 * low one (func_020789f4); the other unpackers read the same way. */
extern u8 *func_0207cec0(u8 *villagers, int index); /* a villager, NULL when there is none */
extern u8 *func_020807c0(u8 *villager, int index);  /* villager + 0x80 * index, or NULL */
extern void func_020789f4(int *villager, int *entry, const u8 *byte);
extern u32 func_02078448(u32 *villager, u16 *item, const u8 *bytes);
extern void func_0207835c(u32 *villager, u16 *items, const u8 *bytes);
extern void func_020786d8(u32 *villager, u8 *operation, u8 *value, const u8 *bytes);
extern void func_020785a4(int *villager, u8 *kind, u16 *item, int *slot, u8 *flag, const u8 *bytes);
extern void func_02078794(u32 *villager, u32 *entry, u16 *item, const u8 *bytes);
extern void func_02080cd8(u8 *villager, const u16 *item); /* its item 0x7d2 */
extern u16 *func_0207dfd4(u8 *villager, u32 index);       /* its item 0x7b0 + 2 * index, NULL from 4 */
extern u8 *func_0207f1c8(u8 *villager);                   /* villager + 0x734 */
extern u8 *func_0209b5e8(u8 *part);                       /* part + 0x24: the villager's object */
extern int func_0207f270(u8 *villager);
extern u8 *func_020794d0(int value); /* value + 4 */
/* The villager's object: its type (byte 0xa, func_0209bc40) and whether it is in use
 * (func_0209bd44); func_0209b91c returns its argument. */
extern u8 *func_0209b91c(u8 *object);
extern int func_0209bd44(u8 *object);
extern int func_0209bc40(u8 *object);
extern u16 *func_0209b8c4(u8 *object); /* its item 0x2c */
extern void func_0209bb90(u8 *object, int value);
extern void func_0209ba7c(u8 *object);
extern void func_0209b920(u8 *object);
extern void func_0209b8a4(u8 *object, u8 value);
extern void func_0209b890(u8 *object, int bit);
extern void func_0209bd5c(u8 *object); /* empties one */
extern void func_0209b9cc(u8 *object, int kind, u16 *item, u8 *name, int flag);
/* An entry of a villager. */
extern int func_02081edc(u8 *entry);
extern void func_02081ac0(u8 *entry, const u16 *item); /* its item 0x6a */
extern void func_02081d18(u8 *entry, int value);       /* its byte 0x6c */
extern void func_02081a80(u8 *entry, u8 value);        /* its byte 0x6d */
extern void func_02081e14(u8 *entry, u8 *name, const char *text, u8 *date);
extern int func_02081e94(u8 *entry, u8 *name, const char *text, u8 *date);

extern u8 *func_020984fc(int slot);   /* the player record at a session slot */
extern u8 *func_02099870(u8 *record); /* where its name is */

/* func_02076168: hands a message to handler `handler` with its payload as the read cursor.
 * REQUIRES: a handler that the table holds. */
void SessionMessage_Dispatch(int handler, const u8 *payload, int size, int kind, u8 scene, u32 slot)
{
    Session_SetReadCursor(data_020ccf94, payload);
    data_020cd0dc[handler](size, kind, scene, slot);
}
CLEAN_AS(func_02076168, SessionMessage_Dispatch)

/* func_02076540: the sender's link status becomes the payload's byte. */
void SessionMessage_SetSenderStatus(u32 size, u32 kind, u32 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 status;
    Session_ReadMessage(data_020ccf94, &status, 1);
    func_020a6f74((int) slot, status);
}
CLEAN_AS(func_02076540, SessionMessage_SetSenderStatus)

/* func_02076518: this system's link status becomes the payload's byte. */
void SessionMessage_SetOwnStatus(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    u8 status;
    Session_ReadMessage(session, &status, 1);
    func_020a6f74(session->local_slot, status);
}
CLEAN_AS(func_02076518, SessionMessage_SetOwnStatus)

/* func_020764f0 */
void SessionMessage_SetActivityPlayerEB(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    if (func_020b65c4() != SCENE_2E) {
        return;
    }
    if (func_020a132c() != NULL) {
        func_020a1240(func_020a132c(), (int) slot, 1);
    }
}
CLEAN_AS(func_020764f0, SessionMessage_SetActivityPlayerEB)

/* func_020764cc
 * QUIRK: asks for the activity a second time and does not use the answer; func_020a1210 finds
 * it itself. */
void SessionMessage_SetActivityFlagF3(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    if (func_020b65c4() == SCENE_2E && func_020a132c() != NULL) {
        func_020a132c();
        func_020a1210(1);
    }
}
CLEAN_AS(func_020764cc, SessionMessage_SetActivityFlagF3)

/* func_020764a4 */
void SessionMessage_SetActivityPlayerE7(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    if (func_020b65c4() == SCENE_2E && func_020a132c() != NULL) {
        func_020a1248(func_020a132c(), slot, 1);
    }
}
CLEAN_AS(func_020764a4, SessionMessage_SetActivityPlayerE7)

/* func_02076480: the player in the slot the payload's byte gives leaves. */
void SessionMessage_RemovePlayer(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u8 leaving;
    Session_ReadMessage(data_020ccf94, &leaving, 1);
    Session_RemovePlayer(leaving);
}
CLEAN_AS(func_02076480, SessionMessage_RemovePlayer)

/* func_02076458 */
void SessionMessage_SetActivityPlayerF4(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    if (func_020b65c4() == SCENE_2E && func_020a132c() != NULL) {
        func_020a1208(func_020a132c(), slot, 1);
    }
}
CLEAN_AS(func_02076458, SessionMessage_SetActivityPlayerF4)

/* func_02076434 */
void SessionMessage_SetActivityFlagE6(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    if (func_020b65c4() == SCENE_2E && func_020a132c() != NULL) {
        func_020a1264(func_020a132c(), 1);
    }
}
CLEAN_AS(func_02076434, SessionMessage_SetActivityFlagE6)

/* func_020763f4: the sender's slot and the payload's byte go into the link state's first free
 * pair. */
void SessionMessage_AddLinkPair(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 value[2];
    func_020a7948(value);
    Session_ReadMessage(data_020ccf94, value, 1);
    func_020a7938(&value[0], &value[1]);
    func_020a7408(slot, value[1]);
    func_020a7944(value);
}
CLEAN_AS(func_020763f4, SessionMessage_AddLinkPair)

/* func_0207639c: a link state entry (2 bytes) with the slot it is for. */
void SessionMessage_SetLinkEntry(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u8 entry[2];
    int entry_slot;
    u8 byte0;
    u8 byte1;
    u8 byte2;
    int fields;
    func_020a7820(entry);
    Session_ReadMessage(data_020ccf94, entry, 2);
    func_020a77dc(entry, &entry_slot, &byte0, &byte1, &byte2, &fields);
    func_020a7394(entry_slot, byte0, byte1, byte2, fields);
    func_020a7810(entry);
}
CLEAN_AS(func_0207639c, SessionMessage_SetLinkEntry)

/* func_02076374: the sender's word 0x2c of the link state becomes the payload's byte. */
void SessionMessage_SetLinkWord2C(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 value;
    Session_ReadMessage(data_020ccf94, &value, 1);
    func_020a7380(slot, value);
}
CLEAN_AS(func_02076374, SessionMessage_SetLinkWord2C)

/* func_0207631c: the sender's entry from 0x3c of the link state, from 2 bytes. */
void SessionMessage_SetLinkEntry3C(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 entry[2];
    u8 byte0;
    u8 byte1;
    u8 byte2;
    u32 fields;
    func_020a7880(entry);
    Session_ReadMessage(data_020ccf94, entry, 2);
    func_020a7830(entry, &byte0, &byte1, &byte2, &fields);
    func_020a7360(slot, byte0, byte1, byte2, (int) fields);
    func_020a7870(entry);
}
CLEAN_AS(func_0207631c, SessionMessage_SetLinkEntry3C)

/* func_020762b8: a byte whose bits 0-2 go to the link state's word for the sender's slot (for
 * this system's slot when the sender is slot 0), bits 5-7 to func_020a6f10 and bits 3-4 to
 * func_020a6f34, each of those two only when below 4. */
void SessionMessage_SetLinkStatusBits(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 byte;
    int low;
    int high;
    int middle;
    func_020a76cc(&byte);
    NetSession *session = data_020ccf94;
    Session_ReadMessage(session, &byte, 1);
    func_020a7684(&byte, &low, &high, &middle);
    if (slot == 0) {
        func_020a6f20(session->local_slot, low);
    } else {
        func_020a6f20(slot, low);
    }
    if (high < 4) {
        func_020a6f10(high);
    }
    if (middle < 4) {
        func_020a6f34(middle);
    }
    func_020a76c8(&byte);
}
CLEAN_AS(func_020762b8, SessionMessage_SetLinkStatusBits)

/* func_020762ac */
void SessionMessage_SetLinkSlotFlag68(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    func_020a6e8c((int) slot, 1);
}
CLEAN_AS(func_020762ac, SessionMessage_SetLinkSlotFlag68)

/* func_020762a0: the link state's word 0x74 becomes the sender's slot. */
void SessionMessage_SetLinkWord74(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    func_020a6e7c((int) slot);
}
CLEAN_AS(func_020762a0, SessionMessage_SetLinkWord74)

/* func_0207626c: the category 15 bundle, read whole into its buffer, then taken in. */
void SessionMessage_ReceiveBundle15(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    Session_ReadMessage(session, Session_GetBundle15Buffer(session), size);
    Session_SetBundle15Length(session, size);
    func_020a6db0();
}
CLEAN_AS(func_0207626c, SessionMessage_ReceiveBundle15)

/* func_0207623c: the category 16 bundle, read whole into its buffer. */
void SessionMessage_ReceiveBundle16(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    Session_ReadMessage(session, Session_GetBundle16Buffer(session), size);
    Session_SetBundle16Length(session, size);
}
CLEAN_AS(func_0207623c, SessionMessage_ReceiveBundle16)

/* func_02076230 */
void SessionMessage_SetLinkFlag7C(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    func_020a6e6c(1);
}
CLEAN_AS(func_02076230, SessionMessage_SetLinkFlag7C)

/* func_020761fc: item records (5 bytes each) put on the town map. */
void SessionMessage_PlaceTownItems(u32 size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    for (u32 done = 0; done < size; done += 5) {
        u8 record[5];
        Session_ReadMessage(session, record, 5);
        func_0205fa84(record);
    }
}
CLEAN_AS(func_020761fc, SessionMessage_PlaceTownItems)

/* func_02076198: item records (5 bytes each), each put on the town map here or sent on
 * (func_0205f9d4). */
void SessionMessage_RelayTownItems(u32 size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    for (u32 done = 0; done < size; done += 5) {
        u8 record[5];
        u8 item_scene;
        u8 flag;
        Session_ReadMessage(session, record, 5);
        u16 item = func_02077898(record);
        func_02077a34(&record[2], &item_scene, &flag);
        func_0205f9d4((s8) record[3], (s8) record[4], item_scene, item, flag != 0 ? 1 : 0);
    }
}
CLEAN_AS(func_02076198, SessionMessage_RelayTownItems)

/* func_02076aa0: the answer (a byte) to message 53. */
void SessionMessage_ReceiveAnswer(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u8 answer;
    Session_ReadMessage(data_020ccf94, &answer, 1);
    func_0209d498(&answer);
}
CLEAN_AS(func_02076aa0, SessionMessage_ReceiveAnswer)

/* func_02076a78: the request (a byte) of message 53, with the sender's slot. */
void SessionMessage_ReceiveRequest(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 request;
    Session_ReadMessage(data_020ccf94, &request, 1);
    func_0209d484(&request, (int) slot);
}
CLEAN_AS(func_02076a78, SessionMessage_ReceiveRequest)

/* The entry of a villager that a payload byte names, or NULL. */
static u8 *session_message_villager_entry(const u8 *byte)
{
    int villager;
    int entry;
    func_020789f4(&villager, &entry, byte);
    u8 *record = func_0207cec0(data_021e5a2c, villager);
    if (record == NULL) {
        return NULL;
    }
    return func_020807c0(record, entry);
}

/* func_02076a18: the entry the payload names gets the sender's name (func_02081e94).
 * REQUIRES: size <= 4 (the payload is one byte, func_020789ac); the original reads it into a
 * 4-byte variable. */
void SessionMessage_SetVillagerEntrySender(int size, int kind, int scene, int slot)
{
    (void) kind;
    (void) scene;
    u8 bytes[4];
    Session_ReadMessage(data_020ccf94, bytes, size);
    u8 *entry = session_message_villager_entry(bytes);
    if (entry != NULL) {
        u8 *name = func_02099870(func_020984fc(slot));
        func_02081e94(entry, name, data_021dc7aa, NULL);
    }
}
CLEAN_AS(func_02076a18, SessionMessage_SetVillagerEntrySender)

/* func_020769b8: the entry the payload names is filled with the sender's name
 * (func_02081e14).
 * REQUIRES: size <= 4 (the payload is one byte, func_0207892c); the original reads it into a
 * 4-byte variable. */
void SessionMessage_FillVillagerEntry(int size, int kind, int scene, int slot)
{
    (void) kind;
    (void) scene;
    u8 bytes[4];
    Session_ReadMessage(data_020ccf94, bytes, size);
    u8 *entry = session_message_villager_entry(bytes);
    if (entry != NULL) {
        u8 *name = func_02099870(func_020984fc(slot));
        func_02081e14(entry, name, data_021dc7aa, NULL);
    }
}
CLEAN_AS(func_020769b8, SessionMessage_FillVillagerEntry)

/* func_0207695c: the entry the first byte names gets the second byte as its byte 0x6d; the
 * second byte is read only when the entry exists. */
void SessionMessage_SetVillagerEntryByte6D(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    u8 bytes[2];
    Session_ReadMessage(session, &bytes[0], 1);
    u8 *entry = session_message_villager_entry(&bytes[0]);
    if (entry != NULL) {
        Session_ReadMessage(session, &bytes[1], 1);
        func_02081a80(entry, bytes[1]);
    }
}
CLEAN_AS(func_0207695c, SessionMessage_SetVillagerEntryByte6D)

/* func_02076900: as SessionMessage_SetVillagerEntryByte6D, for the byte 0x6c.
 * QUIRK: the value is passed as a signed byte. */
void SessionMessage_SetVillagerEntryByte6C(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    u8 bytes[2];
    Session_ReadMessage(session, &bytes[0], 1);
    u8 *entry = session_message_villager_entry(&bytes[0]);
    if (entry != NULL) {
        Session_ReadMessage(session, &bytes[1], 1);
        func_02081d18(entry, (s8) bytes[1]);
    }
}
CLEAN_AS(func_02076900, SessionMessage_SetVillagerEntryByte6C)

/* func_020765cc: an item (2 bytes) and a villager (byte 2): the villager's item 0x7d2 becomes
 * it when it is one of 0x11a8-0x12a7 (func_020783e0 sends only those). */
void SessionMessage_SetVillagerItem7D2(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u16 item = NO_ITEM;
    u8 bytes[3];
    u32 index;
    Session_ReadMessage(data_020ccf94, bytes, 3);
    func_02078448(&index, &item, bytes);
    u8 *villager = func_0207cec0(data_021e5a2c, (int) index);
    if (villager != NULL && item >= VILLAGER_ITEM_FIRST && item <= VILLAGER_ITEM_LAST) {
        func_02080cd8(villager, &item);
    }
}
CLEAN_AS(func_020765cc, SessionMessage_SetVillagerItem7D2)

/* func_02076568: four items (2 bytes each) and a villager (byte 8): the villager's items from
 * 0x7b0. */
void SessionMessage_SetVillagerItems7B0(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u16 items[4] = {NO_ITEM, NO_ITEM, NO_ITEM, NO_ITEM};
    u8 bytes[9];
    u32 index;
    Session_ReadMessage(data_020ccf94, bytes, 9);
    func_0207835c(&index, items, bytes);
    u8 *villager = func_0207cec0(data_021e5a2c, (int) index);
    if (villager == NULL) {
        return;
    }
    for (u32 i = 0; i < 4; i++) {
        u16 *slot_item = func_0207dfd4(villager, i);
        if (slot_item != NULL) {
            *slot_item = items[i];
        }
    }
}
CLEAN_AS(func_02076568, SessionMessage_SetVillagerItems7B0)

/* func_020767ac: a villager (high nibble of byte 0), an operation on its object (low nibble)
 * and a value (byte 1): 0 func_0209bb90, 1 func_0209ba7c, 2 func_0209b920, 3 func_0209b8a4,
 * 4 func_0209b890 and then as 5, 5 the object's byte 0x2e; all but 1 only while the object
 * is in use.
 * QUIRK: operation 4 goes on into operation 5. */
void SessionMessage_ChangeVillagerObject(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u8 operation = 6;
    u8 value = 0;
    u8 bytes[2];
    u32 index;
    Session_ReadMessage(data_020ccf94, bytes, 2);
    func_020786d8(&index, &operation, &value, bytes);
    u8 *villager = func_0207cec0(data_021e5a2c, (int) index);
    if (villager == NULL) {
        return;
    }
    u8 *object = func_0209b5e8(func_0207f1c8(villager));
    switch (operation) {
        case 0:
            if (func_0209bd44(func_0209b91c(object)) != 0) {
                func_0209bb90(func_0209b91c(object), value);
            }
            break;
        case 1:
            func_0209ba7c(object);
            break;
        case 2:
            if (func_0209bd44(func_0209b91c(object)) != 0) {
                func_0209b920(object);
            }
            break;
        case 3:
            if (func_0209bd44(func_0209b91c(object)) != 0) {
                func_0209b8a4(object, value);
            }
            break;
        case 4:
            if (func_0209bd44(func_0209b91c(object)) != 0) {
                func_0209b890(object, value);
            }
            /* fall through */
        case 5:
            if (func_0209bd44(func_0209b91c(object)) != 0) {
                object[0x2e] = value;
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020767ac, SessionMessage_ChangeVillagerObject)

/* func_020766f8: an item (bytes 0-1), a villager (high nibble of byte 2), a slot (bits 0-2) and
 * a flag (bit 3), and a kind (byte 3): the object the villager's func_0207f270 gives is
 * emptied, then the villager's object takes the item and kind (func_0209b9cc) with the name of
 * the player in that slot, when the slot is below 4 and has one. */
void SessionMessage_SetVillagerObject(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u8 object_kind = 0x16;
    u16 item = NO_ITEM;
    int player_slot = 4;
    u8 flag = 0;
    u8 bytes[4];
    int index;
    Session_ReadMessage(data_020ccf94, bytes, 4);
    func_020785a4(&index, &object_kind, &item, &player_slot, &flag, bytes);
    u8 *villager = func_0207cec0(data_021e5a2c, index);
    if (villager == NULL) {
        return;
    }
    u8 *object = func_0209b5e8(func_0207f1c8(villager));
    int flagged = flag != 0;
    func_0209bd5c(func_020794d0(func_0207f270(villager)));
    u8 *name = NULL;
    if (player_slot < 4) {
        u8 *record = func_020984fc(player_slot);
        if (record != NULL) {
            name = func_02099870(record);
        }
    }
    func_0209b9cc(object, object_kind, &item, name, flagged);
}
CLEAN_AS(func_020766f8, SessionMessage_SetVillagerObject)

/* func_0207689c: an item (bytes 0-1) and a villager and entry (byte 2): the entry's item 0x6a,
 * when func_02081edc allows. */
void SessionMessage_SetVillagerEntryItem(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u16 item = NO_ITEM;
    u8 bytes[3];
    u32 index;
    u32 entry_index;
    Session_ReadMessage(data_020ccf94, bytes, 3);
    func_02078794(&index, &entry_index, &item, bytes);
    u8 *villager = func_0207cec0(data_021e5a2c, (int) index);
    if (villager == NULL) {
        return;
    }
    u8 *entry = func_020807c0(villager, (int) entry_index);
    if (entry != NULL && func_02081edc(entry) != 0) {
        func_02081ac0(entry, &item);
    }
}
CLEAN_AS(func_0207689c, SessionMessage_SetVillagerEntryItem)

/* func_02076638: an item (bytes 0-1) and a villager (byte 2; byte 3 is read and not used):
 * the item of the villager's object in use (0x2c) becomes it when it fits the object's type:
 * 0x12b0-0x12e7 for type 0, 0x12e8-0x131f for type 1. */
void SessionMessage_SetVillagerObjectItem(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u16 item = NO_ITEM;
    u8 bytes[4];
    u32 index;
    Session_ReadMessage(data_020ccf94, bytes, 4);
    func_02078448(&index, &item, bytes);
    u8 *villager = func_0207cec0(data_021e5a2c, (int) index);
    if (villager == NULL) {
        return;
    }
    u8 *object = func_0209b5e8(func_0207f1c8(villager));
    u8 *in_use = func_0209b91c(object);
    if (func_0209bd44(in_use) == 0) {
        return;
    }
    int fits = func_0209bc40(in_use) == 0 && item >= OBJECT0_ITEM_FIRST && item <= OBJECT0_ITEM_LAST;
    if (!fits) {
        if (func_0209bc40(in_use) != 1) {
            return;
        }
        if (item < OBJECT1_ITEM_FIRST || item > OBJECT1_ITEM_LAST) {
            return;
        }
    }
    *func_0209b8c4(object) = item;
}
CLEAN_AS(func_02076638, SessionMessage_SetVillagerObjectItem)
