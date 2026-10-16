/* The command list of system packet kind 13 (system_command.h). */
#include "system_command.h"

#include "autoload_2/network.h"
#include "clean.h"
#include "main/library_overlay.h"
#include "main/session.h"
#include "main/session_net.h"

#define SHARE_BLOCK 4          /* Session_GetSendBlock(session, 4): where system packets are built */
#define SYSTEM_RUN_COMMANDS 13 /* the system packet kind of a command list */

#define COMMAND_ENTRIES 8     /* the entries of data_021d13e4 opcode 1 carries */
#define COMMAND_ENTRY_SIZE 19 /* status (1), object (12), word 0x20 (4) and halfword 0x24 (2) */

/* An entry of data_021d13e4 (0x2c bytes, func_0207b9d0). */
typedef struct SystemCommandEntry {
    u8 unk_00;
    u8 status; /* 0x01: func_020794d4 sets it, func_020794d8 reads it */
    u8 unk_02[2];
    u8 object[12]; /* 0x04: an item object, func_020794d0 */
    u8 unk_10[0x10];
    u32 unk_20; /* 0x20 */
    u16 unk_24; /* 0x24 */
    u8 unk_26[6];
} SystemCommandEntry;
static_assert(offsetof(SystemCommandEntry, object) == 0x04, "object");
static_assert(offsetof(SystemCommandEntry, unk_20) == 0x20, "unk_20");
static_assert(offsetof(SystemCommandEntry, unk_24) == 0x24, "unk_24");
static_assert(sizeof(SystemCommandEntry) == 0x2c, "size");

/* An item object (12 bytes): made empty by func_0209bd80 (no item 0xfff1, type 0x16 = none),
 * its item at 8 (func_0209bb70) and type at 0xa (func_0209bc40). */
typedef struct SystemCommandObject {
    u32 unk_00;
    u32 unk_04;
    u16 item; /* 0x08 */
    u8 type;  /* 0x0a */
    u8 unk_0b;
} SystemCommandObject;
static_assert(sizeof(SystemCommandObject) == 12, "size");

extern NetSession *data_020ccf94;                   /* the session */
extern SystemCommandWriter *const data_020ccf98[];  /* the section writers, by opcode */
extern SystemCommandHandler *const data_020ccfa0[]; /* the section handlers, by opcode */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

extern SystemCommandEntry *func_0207b9d0(int index); /* entry `index` of data_021d13e4; NULL from 8 */
extern void func_020794d4(SystemCommandEntry *entry, u8 status);
extern u8 func_020794d8(SystemCommandEntry *entry);  /* entry->status */
extern u8 *func_020794d0(SystemCommandEntry *entry); /* &entry->object */
extern void func_0209bd80(SystemCommandObject *object);
extern void func_0209bd7c(SystemCommandObject *object); /* does nothing */
extern int func_0209bc40(SystemCommandObject *object);  /* its type */
extern u16 *func_0209bb70(SystemCommandObject *object); /* &object->item */
/* Sets an object's type and item, and the low 5 bits of its byte 0xb. */
extern void func_0209bd30(u8 *object, u8 type, u16 *item, u8 low_bits);

/* func_02077638: hands each section of the list to the handler of its opcode.
 * QUIRK: the lengths are trusted: a list whose sections do not add up to `length` runs on past
 * its end (the count wraps).
 * REQUIRES: every opcode is below SYSTEM_COMMAND_OPCODES (data_020ccfa0 holds two handlers). */
void SystemCommand_RunList(u8 *list, u32 length)
{
    while (length != 0) {
        u8 header[SYSTEM_COMMAND_HEADER_SIZE];
        u16 size;
        u8 opcode;

        MI_CpuCopy8(list, header, SYSTEM_COMMAND_HEADER_SIZE);
        list += SYSTEM_COMMAND_HEADER_SIZE;
        length -= SYSTEM_COMMAND_HEADER_SIZE;
        MI_CpuCopy8(header, &size, 2);
        MI_CpuCopy8(&header[2], &opcode, 1);

        data_020ccfa0[opcode](list, size);
        list += size;
        length -= size;
    }
}
CLEAN_AS(func_02077638, SystemCommand_RunList)

/* func_02077690: builds a command list in the share block (kind 13 and one section per opcode
 * that wrote something); 0 when the network cannot send, else 1. `slot` goes to each writer.
 * LibraryOverlay_RequireAny stops the game unless a network library overlay is loaded. */
int SystemCommand_BuildList(int slot)
{
    LibraryOverlay_RequireAny();
    if (!Net_CanSend()) {
        return 0;
    }

    NetSession *session = data_020ccf94;
    Session_ClearShareLength(session);
    SessionNet_WriteSystemHeader(Session_GetSendBlock(session, SHARE_BLOCK), 0, SYSTEM_RUN_COMMANDS);
    Session_SetShareLength(session, 1);

    for (int opcode = 0; opcode < SYSTEM_COMMAND_OPCODES; opcode++) {
        /* The header's room is kept, the writer appends the data, then the header is filled in
         * or, with no data, given back. */
        u32 start = Session_GetShareLength(session);
        u8 *header = Session_GetSendBlock(session, SHARE_BLOCK) + start;
        Session_SetShareLength(session, (int) (start + SYSTEM_COMMAND_HEADER_SIZE));

        data_020ccf98[opcode](slot);

        u32 end = Session_GetShareLength(session);
        if (end <= start + SYSTEM_COMMAND_HEADER_SIZE) {
            Session_SetShareLength(session, (int) start);
        } else {
            u16 size = (u16) (end - start - SYSTEM_COMMAND_HEADER_SIZE); /* QUIRK: 16 bits */
            u8 bytes[SYSTEM_COMMAND_HEADER_SIZE];
            MI_CpuCopy8(&size, bytes, 2);
            bytes[2] = (u8) opcode;
            MI_CpuCopy8(bytes, header, SYSTEM_COMMAND_HEADER_SIZE);
        }
    }
    return 1;
}
CLEAN_AS(func_02077690, SystemCommand_BuildList)

/* func_02077744: the handler of opcode 1: the eight entries of data_021d13e4 from `data`, 19
 * bytes each (written by SystemCommand_WriteEntries): the status byte, the object (of which only its type
 * and item are taken, the low bits of byte 0xb cleared), the word 0x20 and the halfword 0x24.
 * `length` is not read. */
void SystemCommand_ReadEntries(u8 *data, u16 length)
{
    (void) length;
    SystemCommandObject object;

    func_0209bd80(&object);
    for (int i = 0; i < COMMAND_ENTRIES; i++) {
        SystemCommandEntry *entry = func_0207b9d0(i);
        u8 status;
        u32 word;
        u16 half;

        MI_CpuCopy8(data, &status, 1);
        func_020794d4(entry, status);

        MI_CpuCopy8(data + 1, &object, sizeof(object));
        u8 *dst = func_020794d0(entry);
        u8 type = (u8) func_0209bc40(&object);
        u16 *item = func_0209bb70(&object);
        func_0209bd30(dst, type, item, 0);

        MI_CpuCopy8(data + 13, &word, 4);
        entry->unk_20 = word;
        MI_CpuCopy8(data + 17, &half, 2);
        entry->unk_24 = half;

        data += COMMAND_ENTRY_SIZE;
    }
    func_0209bd7c(&object);
}
CLEAN_AS(func_02077744, SystemCommand_ReadEntries)

/* func_020777ec: the handler of opcode 0; it does nothing. */
void SystemCommand_ReadNothing(u8 *data, u16 length)
{
    (void) data;
    (void) length;
}
CLEAN_AS(func_020777ec, SystemCommand_ReadNothing)

/* func_020777f0: the writer of opcode 1: appends the eight entries of data_021d13e4 to the
 * share block, 19 bytes each: the status byte, the object, the word 0x20 and the halfword
 * 0x24. `slot` is not read.
 * REQUIRES: func_0207b9d0 gives an entry for every index below 8, as it does. For a missing
 * one the ROM writes status 3 and still reads the other fields through the null pointer. */
void SystemCommand_WriteEntries(int slot)
{
    (void) slot;
    NetSession *session = data_020ccf94;

    for (int i = 0; i < COMMAND_ENTRIES; i++) {
        SystemCommandEntry *entry = func_0207b9d0(i);
        u8 status = entry != NULL ? func_020794d8(entry) : 3;
        Session_AppendShareData(session, &status, 1);
        Session_AppendShareData(session, func_020794d0(entry), sizeof(SystemCommandObject));
        u32 word = entry->unk_20;
        Session_AppendShareData(session, &word, 4);
        u16 half = entry->unk_24;
        Session_AppendShareData(session, &half, 2);
    }
}
CLEAN_AS(func_020777f0, SystemCommand_WriteEntries)

/* func_02077864: the writer of opcode 0; it appends nothing, so the list has no section 0. */
void SystemCommand_WriteNothing(int slot)
{
    (void) slot;
}
CLEAN_AS(func_02077864, SystemCommand_WriteNothing)
