/* The handlers of system packets (system_packet.h). */
#include "system_packet.h"

#include "autoload_2/network.h"
#include "clean.h"
#include "main/session.h"

/* The scenes (func_020b65c4) the activity handlers act in. */
#define SCENE_09 9
#define SCENE_0C 12
#define SCENE_0D 13
#define SCENE_2E 46
#define SCENE_2F 47

#define UNLINKED_SLOT 3 /* the link state slot of this system while it has no slot */
#define NO_REQUEST 3    /* NetSession.mode_request without a request */

extern NetSession *data_020ccf94;                  /* the session */
extern SystemPacketHandler *const data_020ccff0[]; /* the handlers, by kind */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

extern u8 func_020b65c4(void);  /* the current scene */
extern u8 *func_020a132c(void); /* the current activity object (data_021f3c3c), or NULL */
extern u8 *func_020984e8(void); /* this system's player record */
extern u8 *func_020989e0(u8 *record);
extern u8 *func_0209847c(int which);
extern void func_020962a4(int a, int b);
extern void func_02077638(u8 *commands, u32 length); /* runs a list of commands */

/* The activity object's setters: the byte at the offset in their name; the per-player ones at
 * that offset plus the player. */
extern void func_020a11b8(u8 *activity, u8 value);              /* 0x101 */
extern void func_020a11e0(u8 player);                           /* 0x100 of the current object */
extern void func_020a1208(u8 *activity, int player, int value); /* 0xf4 + player */
extern void func_020a11f8(u8 *activity, int player, int value); /* 0xfc + player */
extern void func_020a1200(u8 *activity, int player, int value); /* 0xf8 + player */
extern void func_020a1238(u8 *activity, int player, int value); /* 0xef + player */
extern void func_020a125c(u8 *activity, u8 value);              /* 0xd9 */
extern void func_020a1254(u8 *activity, u8 value);              /* 0xda */
extern void func_020a1274(u8 *activity, u8 value);              /* 0xe4 */
extern void func_020a126c(u8 *activity, u8 value);              /* 0xe5 */
extern u8 *func_020a1250(u8 *activity);                         /* its bytes from 0xdc */
extern u8 func_020a245c(u8 *activity);                          /* its byte 0x102 */

extern void func_020a6f74(int slot, int status); /* sets a slot's link status */
extern void func_020a6f54(u32 members);          /* sets the link state's member mask (0x98) */
extern void func_020a6cd4(u32 value);            /* sets the link state's byte 0xc4 */
/* A slot's 3-byte link state entry as two bytes (func_020a7880 makes one, func_020a7870 ends
 * it, func_020a7830 reads it out), and the setter of a slot's entry. */
extern u8 *func_020a7880(u8 *entry);
extern u8 *func_020a7870(u8 *entry);
extern void func_020a7830(const u8 *entry, u8 *byte0, u8 *byte1, u8 *byte2, u32 *fields);
extern void func_020a7394(int slot, int byte0, int byte1, int byte2, int fields);

/* func_02075240
 * REQUIRES: kind < 24 (Session_OnReceived checks). */
void SystemPacket_Dispatch(u8 *payload, u32 length, int sender, int kind)
{
    data_020ccff0[kind](payload, length, sender);
}
CLEAN_AS(func_02075240, SystemPacket_Dispatch)

/* func_02075254 */
void SystemPacket_SetActivityFlag101(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    (void) sender;
    if (func_020b65c4() == SCENE_2E && func_020a132c() != NULL) {
        func_020a11b8(func_020a132c(), 1);
    }
}
CLEAN_AS(func_02075254, SystemPacket_SetActivityFlag101)

/* func_02075278: the payload's offset (4 bytes) and data, written into the block of this
 * system's player record that func_020989e0 gives. */
void SystemPacket_WriteRecordBlock(u8 *payload, u32 length, int sender)
{
    (void) sender;
    u32 offset;
    MI_CpuCopy8(payload, &offset, 4);
    u8 *block = func_020989e0(func_020984e8());
    MI_CpuCopy8(payload + 4, block + offset, length - 4);
}
CLEAN_AS(func_02075278, SystemPacket_WriteRecordBlock)

/* func_020752a8: in scene 46 with an activity: the payload's offset (4 bytes) and data,
 * written into this system's player record, after func_020962a4 is given player 0 and the
 * activity's byte 0x102.
 * QUIRK: the session's local player becomes 0 on the way. */
void SystemPacket_WriteOwnRecord(u8 *payload, u32 length, int sender)
{
    (void) sender;
    if (func_020b65c4() != SCENE_2E) {
        return;
    }
    if (func_020a132c() == NULL) {
        return;
    }
    int offset;
    MI_CpuCopy8(payload, &offset, 4);
    u8 value = func_020a245c(func_020a132c());
    NetSession *session = data_020ccf94;
    session->local_player = 0;
    func_020962a4(session->local_player, value);
    u8 *record = func_020984e8();
    MI_CpuCopy8(payload + 4, record + offset, length - 4);
}
CLEAN_AS(func_020752a8, SystemPacket_WriteOwnRecord)

/* func_02075300 */
void SystemPacket_SetActivityPlayer100(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    func_020a11e0((u8) sender);
}
CLEAN_AS(func_02075300, SystemPacket_SetActivityPlayer100)

/* func_0207530c */
void SystemPacket_SetActivityPlayerF4(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    if (func_020b65c4() == SCENE_2E && func_020a132c() != NULL) {
        func_020a1208(func_020a132c(), sender, 1);
    }
}
CLEAN_AS(func_0207530c, SystemPacket_SetActivityPlayerF4)

/* func_02075334 */
void SystemPacket_SetActivityFlagE5(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    (void) sender;
    if (func_020b65c4() == SCENE_2E && func_020a132c() != NULL) {
        func_020a126c(func_020a132c(), 1);
    }
}
CLEAN_AS(func_02075334, SystemPacket_SetActivityFlagE5)

/* func_02075358 */
void SystemPacket_SetActivityPlayerFC(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    if (func_020b65c4() == SCENE_2E && func_020a132c() != NULL) {
        func_020a11f8(func_020a132c(), sender, 1);
    }
}
CLEAN_AS(func_02075358, SystemPacket_SetActivityPlayerFC)

/* func_02075380 */
void SystemPacket_SetActivityPlayerF8(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    if (func_020b65c4() == SCENE_2E && func_020a132c() != NULL) {
        func_020a1200(func_020a132c(), sender, 1);
    }
}
CLEAN_AS(func_02075380, SystemPacket_SetActivityPlayerF8)

/* func_020753a8: the four slots' link state entries, 2 bytes each. */
void SystemPacket_SetLinkEntries(u8 *payload, u32 length, int sender)
{
    (void) length;
    (void) sender;
    for (u32 slot = 0; slot < 4; slot++) {
        u8 entry[2];
        u8 byte0;
        u8 byte1;
        u8 byte2;
        u32 fields;
        func_020a7880(entry);
        MI_CpuCopy8(payload, entry, 2);
        func_020a7830(entry, &byte0, &byte1, &byte2, &fields);
        func_020a7394((int) slot, byte0, byte1, byte2, (int) fields);
        payload += 2;
        func_020a7870(entry);
    }
}
CLEAN_AS(func_020753a8, SystemPacket_SetLinkEntries)

/* func_02075404: in scene 46 or 9 with an activity: its byte 0xef + player becomes the
 * payload's byte, for the sender's player as the host (AID 0), else for player 0. */
void SystemPacket_SetActivityPlayerEF(u8 *payload, u32 length, int sender)
{
    (void) length;
    if (func_020b65c4() == SCENE_2E || func_020b65c4() == SCENE_09) {
        u8 *activity = func_020a132c();
        if (activity != NULL) {
            if (Net_GetMyAid() == 0) {
                func_020a1238(activity, sender, *payload);
            } else {
                func_020a1238(activity, 0, *payload);
            }
        }
    }
}
CLEAN_AS(func_02075404, SystemPacket_SetActivityPlayerEF)

/* func_02075448 */
void SystemPacket_RunCommands(u8 *payload, u32 length, int sender)
{
    (void) sender;
    func_02077638(payload, length);
}
CLEAN_AS(func_02075448, SystemPacket_RunCommands)

/* func_02075450: the payload's offset (4 bytes) and data, written into the shared records. */
void SystemPacket_WriteSharedRecords(u8 *payload, u32 length, int sender)
{
    (void) sender;
    int offset;
    MI_CpuCopy8(payload, &offset, 4);
    u8 *records = Session_GetRecordTable(data_020ccf94);
    MI_CpuCopy8(payload + 4, records + offset, length - 4);
}
CLEAN_AS(func_02075450, SystemPacket_WriteSharedRecords)

/* func_02075484 */
void SystemPacket_SetActivityFlagE4(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    (void) sender;
    if (func_020b65c4() == SCENE_0D || func_020b65c4() == SCENE_2F) {
        if (func_020a132c() != NULL) {
            func_020a1274(func_020a132c(), 1);
        }
    }
}
CLEAN_AS(func_02075484, SystemPacket_SetActivityFlagE4)

/* func_020754b0: in scene 12 with an activity: the payload's 8 bytes into its bytes from 0xdc,
 * and its flag 0xda set. */
void SystemPacket_SetActivityDataDC(u8 *payload, u32 length, int sender)
{
    (void) length;
    (void) sender;
    if (func_020b65c4() != SCENE_0C) {
        return;
    }
    if (func_020a132c() == NULL) {
        return;
    }
    MI_CpuCopy8(payload, func_020a1250(func_020a132c()), 8);
    func_020a1254(func_020a132c(), 1);
}
CLEAN_AS(func_020754b0, SystemPacket_SetActivityDataDC)

/* func_020754e8 */
void SystemPacket_SetActivityFlagD9(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    (void) sender;
    if (func_020b65c4() == SCENE_0D || func_020b65c4() == SCENE_2F) {
        if (func_020a132c() != NULL) {
            func_020a125c(func_020a132c(), 1);
        }
    }
}
CLEAN_AS(func_020754e8, SystemPacket_SetActivityFlagD9)

/* func_02075514: the payload's byte becomes the mode request, unless one is pending. */
void SystemPacket_RequestMode(u8 *payload, u32 length, int sender)
{
    (void) length;
    (void) sender;
    NetSession *session = data_020ccf94;
    if (Session_GetModeRequest(session) == NO_REQUEST) {
        Session_SetModeRequest(session, *payload);
    }
}
CLEAN_AS(func_02075514, SystemPacket_RequestMode)

/* func_0207553c */
void SystemPacket_SetLinkFlagC4(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    (void) sender;
    func_020a6cd4(1);
}
CLEAN_AS(func_0207553c, SystemPacket_SetLinkFlagC4)

/* func_02075548: from the host to a system without a slot (Session_WriteStatusPacket): its
 * link status (slot 3's) from bits 0-2 and the member slots from bits 4-7. */
void SystemPacket_SetOwnStatus(u8 *payload, u32 length, int sender)
{
    (void) length;
    (void) sender;
    u8 byte = *payload;
    func_020a6f74(UNLINKED_SLOT, byte & 7);
    func_020a6f54((u16) ((byte >> 4) & 0xf));
}
CLEAN_AS(func_02075548, SystemPacket_SetOwnStatus)

/* func_0207556c: the sender's link status becomes the payload's byte. */
void SystemPacket_SetSenderStatus(u8 *payload, u32 length, int sender)
{
    (void) length;
    func_020a6f74(sender, *payload);
}
CLEAN_AS(func_0207556c, SystemPacket_SetSenderStatus)

/* func_0207557c: the payload's offset (4 bytes) and data, written into the block
 * func_0209847c gives for sender + 3; then func_020962a4 is told the sender and that number. */
void SystemPacket_WriteSenderBlock(u8 *payload, u32 length, int sender)
{
    int offset;
    MI_CpuCopy8(payload, &offset, 4);
    int which = sender + 3;
    u8 *record = func_0209847c(which);
    MI_CpuCopy8(payload + 4, record + offset, length - 4);
    func_020962a4(sender, which);
}
CLEAN_AS(func_0207557c, SystemPacket_WriteSenderBlock)
