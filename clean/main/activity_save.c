/* The activity's steps that save the town during a visit and end it (activity_save.h). */
#include "activity_save.h"

#include "acre_map.h"
#include "autoload_2/network.h"
#include "calendar.h"
#include "clean.h"
#include "clock.h"
#include "date_time.h"
#include "library_overlay.h"
#include "paired_town.h"
#include "player_record.h"
#include "player_records.h"
#include "save_stamp.h"
#include "session.h"
#include "session_link.h"
#include "state_block.h"
#include "system_packet.h"
#include "wfc_session.h"

extern NetSession *data_020ccf94;
extern StateBlock data_021dc7a8;
extern SaveStamp data_021f3ba0; /* the state block's part_173f8 */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The activity's card steps (activity_save.h). func_020a2120's part goes in a pointer-sized
 * argument. */
extern int func_020a238c(Activity *activity);
extern int func_020a19c0(int unused, int part);
extern int func_020a2120(Activity *activity, int part);
/* The activity's exchange block copied to this system's (data_021ee418). */
extern void func_020a2468(Activity *activity);
/* This system's player record copied to record 7 (data_020e37f8); the argument is not read. */
extern void func_020a24ac(Activity *activity);
/* This system's player's paired town (paired_town.h) copied to the state block's (0x173e2). */
extern void func_02088368(void);
/* Message 10 and message 11 of "sp_etc_sequence2" given to talk 0; the argument is not read. */
extern void func_020a261c(Activity *activity);
extern void func_020a25e8(Activity *activity);

/* Talk 0 and its state (0 when closed). */
typedef struct ActivitySaveTalk {
    u32 unk_00;
    s32 state;
} ActivitySaveTalk;
extern ActivitySaveTalk *func_020682e0(int index);
/* The library routine the end of the shutdown calls (caution_window.c). */
extern void func_02116a1c(int arg);

/* A session player's record number: given, read and taken away. */
extern void func_020962a4(int player, int number);
extern u8 func_02096284(int player);
extern void func_02096294(int player);

extern void func_0204d0ac(AcreMap *map);
extern void func_02046830(void);

/* The sun level's byte (field_actor_looks.c) and the date kept with it. */
extern u8 *func_0209626c(void);
extern u16 *func_0209627c(void);

#define TO_HOST 1 /* the AID mask of the host */
#define HOST_AID 0
#define STATE_BLOCK_START 2   /* StateBlock_Start's step when the town is taken up again */
#define NO_RECORD 7           /* LeaveSession's record number that changes nothing */
#define PLAYERS_LEFT (-4)     /* Session_OnPlayersChanged: the other players left */
#define SUN_BYTE_BITS_12 0x06 /* bits 1 and 2 of the sun level's byte */
#define SUN_BYTE_BIT_1 0x02
#define SUN_BYTE_BITS_0_4 0x11

/* An ARM shift by a register amount: the low byte counts, and 32 or more gives 0. */
static u32 shift_left(u32 value, int amount)
{
    u32 bits = (u32) amount & 0xff;
    return bits < 32 ? value << bits : 0;
}

/* Whether the link is lost to any of `aids`; the send timeout is raised when it is. */
static int link_lost(int aids)
{
    if (Session_IsLinkLost(aids) != 0) {
        Session_RaiseSendTimeout();
        return 1;
    }
    return 0;
}

/* The other systems' answer: ACTIVITY_ANSWER_NONE while one of them (from slot 3 down) has not
 * answered, ACTIVITY_ANSWER_END when one said so before that, else ACTIVITY_ANSWER_OK. */
static int peers_answer(const Activity *activity)
{
    NetSession *session = data_020ccf94;
    for (int slot = ACTIVITY_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) == 0 || Session_IsLocalSlot(session, slot) != 0) {
            continue;
        }
        if (activity->slot_answer[slot] == ACTIVITY_ANSWER_NONE) {
            return ACTIVITY_ANSWER_NONE;
        }
        if (activity->slot_answer[slot] == ACTIVITY_ANSWER_END) {
            return ACTIVITY_ANSWER_END;
        }
    }
    return ACTIVITY_ANSWER_OK;
}

/* func_020a03e0: a guest's save, in eight steps from `first`: the card checked (on failure to
 * `fail_step`); the state block kept in Activity.block_copy and the card's part read into it;
 * with `with_exchange`, the activity's exchange block put in it; the player record copied to
 * record 7; with `with_exchange`, the paired town the block brings taken by the player
 * (PairedTown_TakeOwn) and copied to the state block; the stamp marked writing and the part
 * written; then the host told (ACTIVITY_ANSWER_OK) and its answer awaited: on
 * ACTIVITY_ANSWER_END to `end_step`, else the answers cleared, the stamp marked written and the
 * part written again (with `restore`, the kept block put back), the host told and its answer
 * awaited once more.
 * QUIRK: a read the card step reports neither done nor failed (a bad sum) is retried for ever. */
int ActivitySave_GuestSteps(Activity *activity, u8 *step, int first, int fail_step, u8 end_step, u8 with_exchange, u8 restore,
                            int aids)
{
    int result;
    int at = *step - first;
    switch (at) {
        case 0:
            if (link_lost(aids)) {
                break;
            }
            result = func_020a238c(activity);
            if (result == 1) {
                *step = (u8) fail_step;
            } else if (result != 3) {
                MI_CpuCopy8(&data_021dc7a8, activity->block_copy, sizeof(StateBlock));
                *step = (u8) (first + 1);
            }
            break;
        case 1:
            if (link_lost(aids)) {
                break;
            }
            result = func_020a19c0((int) (uintptr_t) activity, activity->card_parts & 0xf);
            if (result == 1) {
                *step = (u8) fail_step;
            } else if (result == 0) {
                if (with_exchange) {
                    func_020a2468(activity);
                }
                func_020a24ac(activity);
                if (with_exchange) {
                    PairedTown_TakeOwn(activity);
                    func_02088368();
                }
                SaveStamp_MarkWriting(&data_021f3ba0);
                *step = (u8) (first + 2);
            }
            break;
        case 2:
        case 5:
            if (link_lost(aids)) {
                break;
            }
            result = func_020a2120(activity, activity->card_parts >> 4);
            if (result == 1) {
                *step = (u8) fail_step;
            } else if (result == 0) {
                if (at == 5 && restore) {
                    MI_CpuCopy8(activity->block_copy, &data_021dc7a8, sizeof(StateBlock));
                }
                *step = (u8) (first + at + 1);
            }
            break;
        case 3:
        case 6:
            if (link_lost(aids)) {
                break;
            }
            if (SystemPacket_SendActivityPlayerEF(ACTIVITY_ANSWER_OK, TO_HOST) != 0) {
                *step = (u8) (first + at + 1);
            }
            break;
        case 4:
        case 7:
            if (link_lost(aids)) {
                break;
            }
            if (activity->slot_answer[0] == ACTIVITY_ANSWER_OK) {
                if (at == 4) {
                    Activity_ClearAnswers(activity);
                    SaveStamp_MarkWritten(&data_021f3ba0);
                }
                *step = (u8) (first + at + 1);
            } else if (activity->slot_answer[0] == ACTIVITY_ANSWER_END) {
                *step = end_step;
            }
            break;
        default:
            break;
    }
    return ACTIVITY_STEP_RESULT;
}
CLEAN_AS(func_020a03e0, ActivitySave_GuestSteps)

/* func_020a05e8: the host's save, in seven steps from `first`: the card checked (on failure to
 * `fail_step`); the stamp marked writing and, with `with_exchange`, this system's exchange
 * block and paired town taken from the activity; the part written; the guests' answers
 * awaited (`forced` 0 holds them back, 2 makes them ACTIVITY_ANSWER_END): on
 * ACTIVITY_ANSWER_END to `end_step`, else the answers cleared; then, once the library can send,
 * the guests told (ACTIVITY_ANSWER_OK) and the stamp marked written, the part written again and
 * the answers awaited; at last the guests and the system in `slot` (when below 4) told again. */
int ActivitySave_HostSteps(Activity *activity, u8 *step, int forced, int first, u8 fail_step, u8 end_step, int slot,
                           u8 with_exchange, int aids)
{
    int at = *step;
    int result;
    int answer;
    switch (at - first) {
        case 0:
            if (link_lost(aids)) {
                break;
            }
            result = func_020a238c(activity);
            if (result == 1) {
                *step = fail_step;
            } else if (result != 3) {
                SaveStamp_MarkWriting(&data_021f3ba0);
                if (with_exchange != 0) {
                    func_020a2468(activity);
                    PairedTown_TakeOwn(activity);
                    func_02088368();
                }
                *step = (u8) (first + 1);
            }
            break;
        case 1:
        case 4:
            if (link_lost(aids)) {
                break;
            }
            result = func_020a2120(activity, activity->card_parts >> 4);
            if (result == 1) {
                *step = fail_step;
            } else if (result == 0) {
                *step = (u8) (at + 1);
            }
            break;
        case 2:
            if (link_lost(aids)) {
                break;
            }
            answer = peers_answer(activity);
            if (answer != ACTIVITY_ANSWER_NONE) {
                if (forced == ACTIVITY_ANSWER_NONE) {
                    answer = ACTIVITY_ANSWER_NONE;
                } else if (forced == ACTIVITY_ANSWER_END) {
                    answer = ACTIVITY_ANSWER_END;
                }
            }
            if (answer == ACTIVITY_ANSWER_OK) {
                Activity_ClearAnswers(activity);
                *step = (u8) (first + 3);
            } else if (answer == ACTIVITY_ANSWER_END) {
                *step = end_step;
            }
            break;
        case 3:
            if (link_lost(aids)) {
                break;
            }
            LibraryOverlay_RequireAny();
            if (Net_CanSend() == 0) {
                break;
            }
            if (SystemPacket_SendActivityPlayerEF(ACTIVITY_ANSWER_OK, Session_GetPeerMask()) == 0) {
                break;
            }
            SaveStamp_MarkWritten(&data_021f3ba0);
            *step = (u8) (first + 4);
            break;
        case 5:
            if (link_lost(aids)) {
                break;
            }
            answer = peers_answer(activity);
            if (answer == ACTIVITY_ANSWER_OK) {
                *step = (u8) (first + 6);
            } else if (answer == ACTIVITY_ANSWER_END) {
                *step = end_step;
            }
            break;
        case 6: {
            if (link_lost(aids)) {
                break;
            }
            u16 to = (u16) Session_GetPeerMask();
            if (slot < ACTIVITY_SLOTS) {
                to = (u16) (to | shift_left(1, slot));
            }
            if (SystemPacket_SendActivityPlayerEF(ACTIVITY_ANSWER_OK, to) != 0) {
                *step = (u8) (first + 7);
            }
            break;
        }
        default:
            break;
    }
    return ACTIVITY_STEP_RESULT;
}
CLEAN_AS(func_020a05e8, ActivitySave_HostSteps)

/* Host: whether every guest among `aids` (slots 1-3) has acknowledged (Activity.slot_ack), read
 * with the session's interrupts off; the link is checked against the ones that have not.
 * *lost is set when it is lost to one of them. */
static int guests_acknowledged(const Activity *activity, int aids, int *lost)
{
    int all = 1;
    int missing = 0;
    Session_DisableInterrupts();
    for (int slot = ACTIVITY_SLOTS - 1; slot > 0; slot--) {
        int bit = 1 << slot;
        if ((aids & bit) != 0 && activity->slot_ack[slot] == 0) {
            all = 0;
            missing = (u16) (missing | bit);
        }
    }
    *lost = Session_IsLinkLost(missing);
    Session_EnableInterrupts();
    return all;
}

/* The link status reset and the Wi-Fi Connection's session ended. */
static void end_link(Activity *activity)
{
    Session_ResetLinkStatus();
    WfcSession_End(activity);
}

/* func_020a0848: the steps that end a visit, in two chains run in one call.
 *
 * From `first` (five steps): ACTIVITY_ANSWER_END sent (by the host to `aids`, by a guest to
 * the host) and the library ready to send; the host then waits for every guest's
 * acknowledgement, a guest for the host's answer and its own acknowledgement sent
 * (SystemPacket_SendActivityPlayerF4); the link ended (a guest once the library can send);
 * with `show_message`, message 10 of "sp_etc_sequence2"; then first + 5, the caller's.
 *
 * From `second` (after the first chain's step of this call): ACTIVITY_ANSWER_END sent by the
 * host, an acknowledgement by a guest; the library ready to send; the host waits for every
 * guest's acknowledgement; the link ended; with `show_message`, message 11; then, once talk 0
 * is closed, the library's shutdown routine (func_02116a1c), each call.
 * QUIRK: not every step checks the link against `aids`: the host's waits for the
 * acknowledgements check it only against the guests that have not acknowledged, and the host's
 * fourth step, a guest's third step of the second chain and the message steps not at all. */
int ActivitySave_EndSteps(Activity *activity, u8 *step, int first, int second, int aids, u8 show_message)
{
    int lost;
    switch (*step - first) {
        case 0:
            if (link_lost(aids)) {
                return ACTIVITY_STEP_RESULT;
            }
            if (Net_GetMyAid() == HOST_AID) {
                if (SystemPacket_SendActivityPlayerEF(ACTIVITY_ANSWER_END, aids) != 0) {
                    *step = (u8) (first + 1);
                }
            } else if (SystemPacket_SendActivityPlayerEF(ACTIVITY_ANSWER_END, TO_HOST) != 0) {
                *step = (u8) (first + 1);
            }
            break;
        case 1:
            if (link_lost(aids)) {
                return ACTIVITY_STEP_RESULT;
            }
            LibraryOverlay_RequireAny();
            if (Net_CanSend() != 0) {
                *step = (u8) (first + 2);
            }
            break;
        case 2:
            if (Net_GetMyAid() == HOST_AID) {
                int all = guests_acknowledged(activity, aids, &lost);
                if (lost != 0) {
                    Session_RaiseSendTimeout();
                    return ACTIVITY_STEP_RESULT;
                }
                if (all != 0) {
                    end_link(activity);
                    *step = (u8) (first + 3);
                }
            } else {
                if (link_lost(aids)) {
                    return ACTIVITY_STEP_RESULT;
                }
                if (activity->slot_answer[0] != ACTIVITY_ANSWER_NONE && SystemPacket_SendActivityPlayerF4() != 0) {
                    *step = (u8) (first + 3);
                }
            }
            break;
        case 3:
            if (Net_GetMyAid() == HOST_AID) {
                *step = (u8) (first + 4);
            } else {
                if (link_lost(aids)) {
                    return ACTIVITY_STEP_RESULT;
                }
                LibraryOverlay_RequireAny();
                if (Net_CanSend() != 0) {
                    end_link(activity);
                    *step = (u8) (first + 4);
                }
            }
            break;
        case 4:
            if (show_message != 0) {
                func_020a261c(activity);
            }
            *step = (u8) (first + 5);
            break;
        default:
            break;
    }

    switch (*step - second) {
        case 0:
            if (link_lost(aids)) {
                return ACTIVITY_STEP_RESULT;
            }
            if (Net_GetMyAid() == HOST_AID) {
                if (SystemPacket_SendActivityPlayerEF(ACTIVITY_ANSWER_END, aids) != 0) {
                    *step = (u8) (second + 1);
                }
            } else if (SystemPacket_SendActivityPlayerF4() != 0) {
                *step = (u8) (second + 1);
            }
            break;
        case 1:
            if (link_lost(aids)) {
                return ACTIVITY_STEP_RESULT;
            }
            LibraryOverlay_RequireAny();
            if (Net_CanSend() != 0) {
                *step = (u8) (second + 2);
            }
            break;
        case 2:
            if (Net_GetMyAid() == HOST_AID) {
                int all = guests_acknowledged(activity, aids, &lost);
                if (lost != 0) {
                    Session_RaiseSendTimeout();
                    return ACTIVITY_STEP_RESULT;
                }
                if (all == 0) {
                    break;
                }
            }
            end_link(activity);
            *step = (u8) (second + 3);
            break;
        case 3:
            if (show_message != 0) {
                func_020a25e8(activity);
            }
            *step = (u8) (second + 4);
            break;
        case 4:
            if (func_020682e0(0)->state == 0) {
                func_02116a1c(0);
            }
            break;
        default:
            break;
    }
    return ACTIVITY_STEP_RESULT;
}
CLEAN_AS(func_020a0848, ActivitySave_EndSteps)

/* func_020a1038: this system back to playing alone after a visit. The link ended; with a
 * `record_number` below NO_RECORD, this system's session player gives up its record and becomes
 * player 0 with that record; the session counts one player, every other player gives up its
 * record and the guests' records (4-6) are cleared. Unless `keep_town`, the town is taken up
 * again from the state block (the clock, StateBlock_Start's step 2, the town's map and the
 * rooms) and the sun level's date of player 0's record set: today's when bit 1 or 2 of the sun
 * level's byte is set (bit 1 then also sets bits 0 and 4), else the date kept with the byte
 * (bit 4 then copied to bit 0). With `keep_town`, func_02046830 instead.
 * QUIRK: the record number of this system's player is asked for once and not used. */
void ActivitySave_LeaveSession(Activity *activity, int record_number, int keep_town)
{
    end_link(activity);
    if (record_number < NO_RECORD) {
        NetSession *session = data_020ccf94;
        func_02096294(session->local_player);
        session->local_player = 0;
    }
    NetSession *session = data_020ccf94;
    Session_SetPlayerCount(session, 1);
    if (record_number < NO_RECORD) {
        func_020962a4(session->local_player, record_number);
    }
    int own = session->local_player;
    func_02096284(own);
    for (int player = SESSION_SLOTS - 1; player >= 0; player--) {
        if (player != own) {
            func_02096294(player);
        }
    }
    for (int guest = PLAYER_RECORDS_GUESTS - 1; guest >= 0; guest--) {
        u8 *record = PlayerRecords_Get(guest + PLAYER_RECORD_FIRST_GUEST);
        if (record != NULL) {
            PlayerRecord_Clear(record);
        }
    }
    if (keep_town == 0) {
        Clock_Refresh(NULL);
        StateBlock_Start(&data_021dc7a8, STATE_BLOCK_START);
        StateBlock_FinishStart(&data_021dc7a8);
        if (AcreMap_Town() != 0) {
            AcreMap_SetTownModels((AcreMap *) (uintptr_t) AcreMap_Town());
            AcreMap_LoadTownData((AcreMap *) (uintptr_t) AcreMap_Town());
            func_0204d0ac((AcreMap *) (uintptr_t) AcreMap_Town());
        }
        AcreMap_SetRoomsModels();
        AcreMap_LoadRoomsData();
    } else {
        func_02046830();
    }
    Session_OnPlayersChanged(PLAYERS_LEFT);
    if (keep_town != 0) {
        return;
    }

    int number = func_02096284(0);
    if (number >= NO_RECORD) {
        return;
    }
    u8 *record = PlayerRecords_Get(number);
    u8 *sun = func_0209626c();
    PlayerRecordSunDate date;
    if ((*sun & SUN_BYTE_BITS_12) != 0) {
        DateTime now = {0};
        DateTime_Now(&now);
        date.packed = (u16) ((now.year & 0x7f) | (now.month & 0xf) << 7 | (now.day & 0x1f) << 11);
        if ((*sun & SUN_BYTE_BIT_1) != 0) {
            *sun |= SUN_BYTE_BITS_0_4;
        }
    } else {
        date.packed = *func_0209627c();
        *sun = (u8) (*sun | ((*sun >> 4) & 1));
    }
    PlayerRecord_SetSunDate(record, date);
}
CLEAN_AS(func_020a1038, ActivitySave_LeaveSession)
