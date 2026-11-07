/* The command list of system packet kind 13 (system_command.h). */
#include "system_command.h"

#include "autoload_2/network.h"
#include "clean.h"
#include "main/library_overlay.h"
#include "main/session.h"
#include "main/session_net.h"
#include "villager_errand.h"
#include "villager_state.h"
#include "villager_town.h"

#define SHARE_BLOCK 4          /* Session_GetSendBlock(session, 4): where system packets are built */
#define SYSTEM_RUN_COMMANDS 13 /* the system packet kind of a command list */

/* The villagers' states (villager_state.h, the entries of data_021d13e4) opcode 1 carries, and
 * what it carries of each: the place (1), the errand (12, VillagerErrand), the room score (4) and its flags (2). */
#define COMMAND_ENTRIES 8
#define COMMAND_ENTRY_SIZE 19

static_assert(sizeof(VillagerErrand) == 12, "size");

extern NetSession *data_020ccf94;                   /* the session */
extern SystemCommandWriter *const data_020ccf98[];  /* the section writers, by opcode */
extern SystemCommandHandler *const data_020ccfa0[]; /* the section handlers, by opcode */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

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

/* func_02077744: the handler of opcode 1: the eight villagers' states from `data`, 19 bytes
 * each (written by SystemCommand_WriteVillagerStates): the place, the errand (of which only its
 * type and item are taken, the low bits of byte 0xb cleared), the room score and its flags.
 * `length` is not read. */
void SystemCommand_ReadVillagerStates(u8 *data, u16 length)
{
    (void) length;
    VillagerErrand errand;

    VillagerErrand_Construct(&errand);
    for (int i = 0; i < COMMAND_ENTRIES; i++) {
        VillagerState *entry = VillagerTown_StateAt(i);
        u8 place;
        u32 word;
        u16 half;

        MI_CpuCopy8(data, &place, 1);
        VillagerState_SetPlace(entry, place);

        MI_CpuCopy8(data + 1, &errand, sizeof(errand));
        u8 *dst = VillagerState_Errand(entry);
        u8 type = (u8) VillagerErrand_Type(&errand);
        u16 *item = VillagerErrand_Item(&errand);
        VillagerErrand_Set((VillagerErrand *) (void *) dst, type, item, 0);

        MI_CpuCopy8(data + 13, &word, 4);
        entry->room_score = word;
        MI_CpuCopy8(data + 17, &half, 2);
        entry->room_score_flags = half;

        data += COMMAND_ENTRY_SIZE;
    }
    VillagerErrand_Destruct(&errand);
}
CLEAN_AS(func_02077744, SystemCommand_ReadVillagerStates)

/* func_020777ec: the handler of opcode 0; it does nothing. */
void SystemCommand_ReadNothing(u8 *data, u16 length)
{
    (void) data;
    (void) length;
}
CLEAN_AS(func_020777ec, SystemCommand_ReadNothing)

/* func_020777f0: the writer of opcode 1: appends the eight villagers' states to the share
 * block, 19 bytes each: the place (3 for a missing state), the errand, the room score and its
 * flags. `slot` is not read.
 * REQUIRES: func_0207b9d0 gives an entry for every index below 8, as it does. For a missing
 * one the ROM writes place 3 and still reads the other fields through the null pointer. */
void SystemCommand_WriteVillagerStates(int slot)
{
    (void) slot;
    NetSession *session = data_020ccf94;

    for (int i = 0; i < COMMAND_ENTRIES; i++) {
        VillagerState *entry = VillagerTown_StateAt(i);
        u8 place = entry != NULL ? VillagerState_LinkedPlace(entry) : 3;
        Session_AppendShareData(session, &place, 1);
        Session_AppendShareData(session, VillagerState_Errand(entry), sizeof(VillagerErrand));
        u32 word = entry->room_score;
        Session_AppendShareData(session, &word, 4);
        u16 half = entry->room_score_flags;
        Session_AppendShareData(session, &half, 2);
    }
}
CLEAN_AS(func_020777f0, SystemCommand_WriteVillagerStates)

/* func_02077864: the writer of opcode 0; it appends nothing, so the list has no section 0. */
void SystemCommand_WriteNothing(int slot)
{
    (void) slot;
}
CLEAN_AS(func_02077864, SystemCommand_WriteNothing)
