/* The jobs 0x14 to 0x1f of the activity process (activity_link_jobs.h). */
#include "activity_link_jobs.h"

#include "acre_map.h"
#include "activity_card.h"
#include "activity_save.h"
#include "activity_talk.h"
#include "activity_vars.h"
#include "autoload_2/approach.h"
#include "autoload_2/network.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "clock.h"
#include "constellations.h"
#include "exchange_blocks.h"
#include "library_overlay.h"
#include "mail.h"
#include "paired_town.h"
#include "player_options.h"
#include "player_record.h"
#include "player_records.h"
#include "recent_slots.h"
#include "save_stamp.h"
#include "scene_exit.h"
#include "scene_tables.h"
#include "session.h"
#include "session_link.h"
#include "start_menu.h"
#include "state_block.h"
#include "system_command.h"
#include "system_packet.h"
#include "town_pack.h"
#include "wfc_session.h"

static_assert(offsetof(Activity, unk_bc) == 0xbc && offsetof(Activity, unk_d0) == 0xd0, "activity");
static_assert(offsetof(Activity, unk_d8) == 0xd8 && offsetof(Activity, slot_answer) == 0xef, "activity");
static_assert(offsetof(Activity, unk_10b) == 0x10b && offsetof(Activity, card_parts) == 0x10e, "activity");
static_assert(offsetof(NetSession, local_slot) == 0x64 && offsetof(NetSession, player_count) == 0x6c, "session");
static_assert(offsetof(StateBlock, part_173c0) == 0x173c0 && sizeof(StateBlock) == 0x173fc, "state block");

extern NetSession *data_020ccf94;
extern StateBlock data_021dc7a8;
extern SaveStamp data_021f3ba0; /* the state block's part_173f8 */
/* The slot of the system the activity adds (activity_vars.h). */
extern u8 data_021f3c1c;
/* The state block received from another system (activity_vars.h). */
extern StateBlock *data_021f3c24;
/* The record number a guest's record is kept at (7 while none is set). */
extern u8 data_020e37f8;
/* A byte job 0x14 sets to 1 once it took the entry record's exit. */
extern u8 data_021c75b0;

extern const char data_020e3c40[]; /* "sp_etc_sequence2" */
extern const char data_020e3c54[]; /* "sp_etc_sequence1" */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void DC_FlushAll(void);

/* The activity's job `job` started. */
extern void func_020a4e94(Activity *activity, int job);

/* Talk 0 (activity_talk.h): func_02068c10 on its part at 0x1c, its byte 0x1e93 cleared, and its
 * next message: the number at `message` from the file `name`. */
extern ActivityTalk *func_020682e0(int index);
extern void func_02068358(ActivityTalk *talk);
extern void func_02068434(ActivityTalk *talk);
extern void func_0206844c(ActivityTalk *talk, const u8 *message, const char *name);

/* The link state (data_021f4320): its slot (word 0x94) read and set, its byte 0xc4, a slot's
 * entry reset (func_020a6a74), and a slot's three entry bytes set where bits 0-2 of `mask`
 * say. */
extern u32 func_020a6ed0(void);
extern void func_020a6ec0(int slot);
extern u8 func_020a6cc4(void);
extern void func_020a6c6c(int slot);
extern void func_020a7394(int slot, int a, int b, int c, int mask);

/* An exchange block (0x4 for this system's, data_021ee418) and clearing one (0x950 bytes). */
extern u8 *func_02090040(int slot);
extern void func_02090174(u8 *block);

/* A session player's record number: read and set. */
extern u8 func_02096284(int player);
extern void func_020962a4(int player, int number);
/* A session player's object (a process). */
extern Process *func_020961a8(int player);

/* The object at data_021d351c, and its byte 0x82 set and cleared. */
extern void *func_0208b4f8(void);
extern void func_0208b9b8(void *object);
extern void func_0208b9b0(void *object);

/* Byte 0x173c0 of the state block handed on to data_021cfbbc (player_messages.c). */
extern void func_0206ea3c(u8 *part);
/* Called with data_021f75b0 (func_020bbc90). */
extern void func_020ba37c(void);
/* The town map's own models (activity_save.c), and the end of a session for the host. */
extern void func_0204d0ac(AcreMap *map);
extern void func_02046830(void);
/* Overlay 48: whether this system's player's paired town is not the state block's (it sets it
 * then). */
extern int func_ov048_02262ee8(void);

/* The town name of the state block (StateBlockTown + 2). */
extern u8 *func_020642a4(StateBlockTown *town);

#define TALK_INDEX 0
#define PLAYER_FLAG_2 2
#define STATE_BLOCK_FLAG_12 0x12
#define GUEST_RECORD_FIRST 3 /* a session slot's record number, less this */
#define CARD_PART_LETTERS 2
#define NO_SLOT 4

#define AIDS_HOST 1
#define AIDS_ALL (-1)

enum ActivityLinkMode {
    SESSION_MODE_0 = 0,
    SESSION_MODE_1 = 1,
    SESSION_MODE_2 = 2,
};

enum ActivityLinkConnectMode {
    CONNECT_MODE_0 = 0,
    CONNECT_MODE_2 = 2,
};

enum ActivityLinkStateBlockMode {
    STATE_BLOCK_MODE_5 = 5,
};

/* The messages talk 0 is given. */
enum ActivityLinkMessage {
    SEQUENCE1_WAITING = 35,
    SEQUENCE1_TIMED_OUT = 37,
    SEQUENCE1_LINKED = 38,
    SEQUENCE2_LEFT = 6,
};

#define WAIT_FRAMES 600

/* Fields of the activity these jobs give a meaning to. */
static u8 *record_copy(Activity *activity) /* 0xbc: room for a player record */
{
    return *(u8 **) (void *) activity->unk_bc;
}

static u16 *countdown(Activity *activity) /* 0xd0 */
{
    return (u16 *) (void *) &activity->unk_d0[0];
}

static u16 *member_mask(Activity *activity) /* 0xd2: Session_GetMemberMask when the job began */
{
    return (u16 *) (void *) &activity->unk_d0[2];
}

static int write_part(const Activity *activity)
{
    return activity->card_parts >> 4;
}

/* The link checked: when it is lost the send timeout is raised and 1 given. */
static int link_lost(int aids)
{
    if (Session_IsLinkLost(aids)) {
        Session_RaiseSendTimeout();
        return 1;
    }
    return 0;
}

static int sendable(void)
{
    LibraryOverlay_RequireAny();
    return Net_CanSend();
}

/* Whether no other taken slot of the session owes credits. */
static int no_peer_owes(NetSession *session)
{
    for (int slot = ACTIVITY_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) && !Session_IsLocalSlot(session, slot) &&
            Session_GetOwedCredits(session, slot)) {
            return 0;
        }
    }
    return 1;
}

/* Whether every other taken slot of the session has its byte of `flags` set. */
static int all_peers_set(NetSession *session, const u8 *flags)
{
    for (int slot = ACTIVITY_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) && !Session_IsLocalSlot(session, slot) && !flags[slot]) {
            return 0;
        }
    }
    return 1;
}

/* The slot data_021f3c1c added to the session: its link state entry set, the player count
 * raised, the slot taken and the change told. */
static void add_new_slot(void)
{
    func_020a7394(data_021f3c1c, 0xc, 1, 0, 7);
    NetSession *session = data_020ccf94;
    Session_SetPlayerCount(session, (u8) (session->player_count + 1));
    Session_SetSlotTaken(session, data_021f3c1c, 1);
    Session_OnPlayersChanged(data_021f3c1c);
}

/* The AID bit of the slot data_021f3c1c. */
static u16 new_slot_bit(void)
{
    return (u16) (1 << data_021f3c1c);
}

/* Talk 0 given message `message` of "sp_etc_sequence2" next. */
static void queue_sequence2(u8 message)
{
    func_0206844c(func_020682e0(TALK_INDEX), &message, data_020e3c40);
}

/* func_020a4210: job 0x14 starts: the gatekeeper's end (no message) and a constellation
 * drafted. */
void ActivityLinkJobs_Start14(Activity *activity)
{
    Activity_TalkGatekeeper(activity, 1);
    Constellations_DraftRandom();
}
CLEAN_AS(func_020a4210, ActivityLinkJobs_Start14)

/* func_020a3ea4: job 0x14's steps, with the host's link (AID 1):
 *   0  system packet 7 sent;
 *   1  wait for the slot mask (system packet 0);
 *   2  this system's block sent;
 *   3  once the pack thread is done, wait until a slot of the mask (1-3) has no record;
 *   4  once flag data_021f3c08 is set, session player 4's object deleted;
 *   5  once it is gone, system packet 9 sent;
 *   6  once system packet 10 came: this system's slot and player become its AID, the record of
 *      the player it was copied to that slot's record, the guest record number kept in
 *      data_020e37f8, the session's slots and player count set from the slot mask, the slot's
 *      link entry set, session player 0 given record byte_d7 and this one record slot + 3; the
 *      received state block copied to this system's, its clock offset set from the date and
 *      time of system packet 10, the town's maps loaded, and the session mode 1;
 *   7  system packet 11 sent to the peers;
 *   8  once sendable, the session mode 2 and the entry record's exit 2 taken (overlay 48's
 *      paired town check true) or exit 0, its change argument 3; data_021c75b0 set.
 * QUIRK: step 3 waits while every slot of the mask has a record and goes on once one has none. */
void ActivityLinkJobs_Step14(Activity *activity)
{
    switch (activity->state) {
        case 0:
            if (link_lost(AIDS_HOST) || !SystemPacket_SendLinkFlagC4()) {
                return;
            }
            activity->state = 1;
            return;
        case 1:
            if (link_lost(AIDS_HOST) || activity->slot_mask == 0) {
                return;
            }
            activity->unk_d8 = 0;
            activity->state = 2;
            return;
        case 2:
            if (link_lost(AIDS_HOST) || !SystemPacket_SendOwnBlock(&activity->unk_d8)) {
                return;
            }
            activity->unk_d8 = 0;
            activity->state = 3;
            return;
        case 3: {
            if (link_lost(AIDS_HOST) || !TownPack_IsDone(activity->pack_thread)) {
                return;
            }
            int all_present = 1;
            for (int slot = ACTIVITY_SLOTS - 1; slot >= 0; slot--) {
                if (slot == 0) {
                    continue;
                }
                u16 bit = (u16) (1 << slot);
                if ((activity->slot_mask & bit) == bit && PlayerRecords_Exists(slot + GUEST_RECORD_FIRST) == 0) {
                    all_present = 0;
                    break;
                }
            }
            if (all_present) {
                return;
            }
            activity->state = 4;
            return;
        }
        case 4:
            if (link_lost(AIDS_HOST) || !ActivityVars_Flag3C08()) {
                return;
            }
            Process_RequestDelete(func_020961a8(4));
            activity->state = 5;
            return;
        case 5:
            if (link_lost(AIDS_HOST) || func_020961a8(4) != NULL || !SystemPacket_SendActivityFlagD9()) {
                return;
            }
            activity->state = 6;
            return;
        case 6: {
            if (link_lost(AIDS_HOST) || !activity->flag_da) {
                return;
            }
            int aid = Net_GetMyAid();
            NetSession *session = data_020ccf94;
            session->local_slot = aid;
            MI_CpuCopy8(PlayerRecords_Get(func_02096284(session->local_player)),
                        PlayerRecords_Get(session->local_slot + GUEST_RECORD_FIRST), PLAYER_RECORD_SIZE);
            data_020e37f8 = func_02096284(session->local_player);
            session->local_player = aid;
            u8 count = 0;
            for (int slot = ACTIVITY_SLOTS - 1; slot >= 0; slot--) {
                if (activity->slot_mask & (1 << slot)) {
                    Session_SetSlotTaken(session, slot, 1);
                    count++;
                } else {
                    Session_SetSlotTaken(session, slot, 0);
                }
            }
            Session_SetPlayerCount(session, count);
            func_020a7394(aid, 0xc, 1, 0, 7);
            func_020962a4(0, activity->byte_d7);
            func_020962a4(aid, aid + GUEST_RECORD_FIRST);
            MI_CpuCopy8(data_021f3c24, &data_021dc7a8, sizeof(StateBlock));

            DateTime when;
            MI_CpuCopy8(activity->date_time, &when, sizeof(when));
            int minutes = ClockOffset_MinutesTo(&data_021f3b74, &when);
            MI_CpuCopy8(activity->date_time, &when, sizeof(when));
            s16 seconds = (s16) ClockOffset_SecondsTo(&data_021f3b74, &when);
            data_021f3b74.minutes = minutes;
            data_021f3b74.seconds = seconds;

            if (AcreMap_Town()) {
                AcreMap_SetTownModels((AcreMap *) (uintptr_t) AcreMap_Town());
                AcreMap_LoadTownData((AcreMap *) (uintptr_t) AcreMap_Town());
                func_0204d0ac((AcreMap *) (uintptr_t) AcreMap_Town());
            }
            AcreMap_SetRoomsModels();
            AcreMap_LoadRoomsData();
            Session_OnPlayersChanged(4);
            func_0206ea3c(data_021dc7a8.part_173c0);
            func_020ba37c();
            activity->byte_d6 = 1;
            Session_SetMode(session, SESSION_MODE_1);
            activity->state = 7;
            return;
        }
        case 7:
            if (link_lost(AIDS_HOST) || !SystemPacket_SendActivityFlagE4(Session_GetPeerMask())) {
                return;
            }
            activity->state = 8;
            return;
        case 8:
            if (link_lost(AIDS_HOST) || !sendable()) {
                return;
            }
            Session_SetMode(data_020ccf94, SESSION_MODE_2);
            if (func_ov048_02262ee8()) {
                SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 2);
            } else {
                SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 0);
            }
            SceneExit_SetChangeArg((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 3);
            data_021c75b0 = 1;
            activity->state = 9;
            return;
        default:
            return;
    }
}
CLEAN_AS(func_020a3ea4, ActivityLinkJobs_Step14)

/* func_020a3e74: job 0x15 starts: the gatekeeper's end (no message); with one player in the
 * session, held mail delivered twice, a constellation drafted and the recent slots cleared. */
void ActivityLinkJobs_Start15(Activity *activity)
{
    Activity_TalkGatekeeper(activity, 1);
    if (data_020ccf94->player_count == 1) {
        Mail_DeliverHeld();
        Mail_DeliverHeld();
        Constellations_DraftRandom();
        RecentSlots_Clear();
    }
}
CLEAN_AS(func_020a3e74, ActivityLinkJobs_Start15)

/* func_020a3bc0: job 0x15's steps, for the slot data_021f3c1c (the new one), with the peers'
 * link (and the link state's slot while the new one is added):
 *   0  wait for byte 0xc4 of the link state;
 *   1-2  mode 1 requested once the others are in scene 0xd or 0x2f (Activity_StepRequestMode1);
 *      once done the new slot is added to the session;
 *   3  system packet 0 sent to it; 4  the system command list built for it; 5  the share data
 *      sent to it; 6  system packet 12; 7  system packet 15, then the state block packed;
 *   8  once packed, the cache flushed and the packed block sent (system packet 1);
 *   9  once system packet 9 came, system packet 10 sent to it;
 *   10 once sendable and system packet 11 came, the session mode 2, byte_d6 set and the new
 *      slot pushed on the recent slots. */
void ActivityLinkJobs_Step15(Activity *activity)
{
    switch (activity->state) {
        case 0:
            if (link_lost(Session_GetPeerMask() | (1 << func_020a6ed0())) || !func_020a6cc4()) {
                return;
            }
            activity->state = 1;
            return;
        case 1:
        case 2:
            if (link_lost(Session_GetPeerMask() | (1 << func_020a6ed0()))) {
                return;
            }
            Activity_StepRequestMode1(activity, &activity->state, 1, 0xd, 0x2f);
            if (activity->state <= 2) {
                return;
            }
            add_new_slot();
            return;
        case 3:
            if (link_lost(Session_GetPeerMask()) || !SystemPacket_SendActivityMembers(new_slot_bit())) {
                return;
            }
            activity->state = 4;
            return;
        case 4:
            if (link_lost(Session_GetPeerMask()) || !SystemCommand_BuildList(data_021f3c1c)) {
                return;
            }
            activity->state = 5;
            return;
        case 5:
            if (link_lost(Session_GetPeerMask()) || !SystemPacket_SendShareData(new_slot_bit())) {
                return;
            }
            activity->unk_d8 = 0;
            activity->state = 6;
            return;
        case 6:
            if (link_lost(Session_GetPeerMask()) || !SystemPacket_SendSharedRecords(&activity->unk_d8, new_slot_bit())) {
                return;
            }
            activity->state = 7;
            return;
        case 7:
            if (link_lost(Session_GetPeerMask()) || !SystemPacket_SendLinkEntries(data_021f3c1c)) {
                return;
            }
            TownPack_StartThread(activity->pack_thread, (void *) 1);
            activity->unk_d8 = 0;
            activity->state = 8;
            return;
        case 8:
            if (link_lost(Session_GetPeerMask()) || !TownPack_IsDone(activity->pack_thread)) {
                return;
            }
            DC_FlushAll();
            if (!SystemPacket_SendActivityBuffer(&activity->unk_d8, new_slot_bit())) {
                return;
            }
            activity->state = 9;
            return;
        case 9:
            if (link_lost(Session_GetPeerMask()) || !activity->flag_d9 || !SystemPacket_SendDateTime(new_slot_bit())) {
                return;
            }
            activity->state = 10;
            return;
        case 10:
            if (link_lost(Session_GetPeerMask()) || !sendable() || !activity->flag_e4) {
                return;
            }
            Session_SetMode(data_020ccf94, SESSION_MODE_2);
            activity->byte_d6 = 1;
            RecentSlots_Push(data_021f3c1c);
            activity->state = 11;
            return;
        default:
            return;
    }
}
CLEAN_AS(func_020a3bc0, ActivityLinkJobs_Step15)

/* func_020a3bb4: job 0x16 starts: the gatekeeper's end (no message). */
void ActivityLinkJobs_Start16(Activity *activity)
{
    Activity_TalkGatekeeper(activity, 1);
}
CLEAN_AS(func_020a3bb4, ActivityLinkJobs_Start16)

/* func_020a3abc: job 0x16's steps, with the host's link: once the session is in mode 1 the slot
 * data_021f3c1c added to it; then the sender's block sent to that slot; then, once sendable
 * and system packet 11 came, the session mode 2 and byte_d6 set. */
void ActivityLinkJobs_Step16(Activity *activity)
{
    switch (activity->state) {
        case 0:
            if (link_lost(AIDS_HOST)) {
                return;
            }
            if (Session_GetMode(data_020ccf94) == SESSION_MODE_1) {
                add_new_slot();
                activity->state = 1;
            }
            return;
        case 1:
            if (link_lost(AIDS_HOST)) {
                return;
            }
            if (SystemPacket_SendSenderBlock(&activity->unk_d8, new_slot_bit())) {
                activity->state = 2;
            }
            return;
        case 2:
            if (link_lost(AIDS_HOST)) {
                return;
            }
            if (sendable() && activity->flag_e4) {
                Session_SetMode(data_020ccf94, SESSION_MODE_2);
                activity->byte_d6 = 1;
                activity->state = 3;
            }
            return;
        default:
            return;
    }
}
CLEAN_AS(func_020a3abc, ActivityLinkJobs_Step16)

/* func_020a3a94: job 0x17 starts: the gatekeeper's message 105, the current player's flag 2
 * set, and the link state's slot made this system's. */
void ActivityLinkJobs_Start17(Activity *activity)
{
    Activity_TalkGatekeeper(activity, 0);
    PlayerRecord_SetFlag(PlayerRecords_Current(), PLAYER_FLAG_2);
    func_020a6ec0(data_020ccf94->local_slot);
}
CLEAN_AS(func_020a3a94, ActivityLinkJobs_Start17)

/* func_020a38e0: job 0x17's steps, with the host's link:
 *   0  once talk 0 waits (given 0), the member mask kept;
 *   1-2  this system reports (Activity_StepSendReport);
 *   3  once this system's slot_107 is set, the system's exchange block taken;
 *   4-11  ActivitySave_GuestSteps (fail 0xe, end 0x14, with the exchange, no restore);
 *   12 once no other system owes credits, system packet 17 sent;
 *   13 once system packet 18 came, the session left with the guest record (data_020e37f8, then
 *      7 again), overlay 68 loaded and func_020ba37c called;
 *   14-24  ActivitySave_EndSteps from 0xe;
 * then talk 0 closed and job 8. */
void ActivityLinkJobs_Step17(Activity *activity)
{
    NetSession *session;
    switch (activity->state) {
        case 0:
            if (link_lost(AIDS_HOST) || !ActivityTalk_FinishWaiting(activity, 0)) {
                return;
            }
            *member_mask(activity) = (u16) Session_GetMemberMask();
            activity->state = 1;
            return;
        case 1:
        case 2:
            if (link_lost(AIDS_HOST)) {
                return;
            }
            Activity_StepSendReport(activity, &activity->state, 1);
            return;
        case 3:
            if (link_lost(AIDS_HOST) || !Activity_Slot107(activity, data_020ccf94->local_slot)) {
                return;
            }
            Activity_SystemExchangeBlockToActivity(activity);
            activity->state = 4;
            return;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            ActivitySave_GuestSteps(activity, &activity->state, 4, 0xe, 0x14, 1, 0, AIDS_HOST);
            return;
        case 12:
            if (link_lost(AIDS_HOST)) {
                return;
            }
            session = data_020ccf94;
            if (!no_peer_owes(session) || !SystemPacket_SendActivityPlayerFC()) {
                return;
            }
            activity->state = 13;
            return;
        case 13:
            if (link_lost(AIDS_HOST) || !activity->flag_e5) {
                return;
            }
            ActivitySave_LeaveSession(activity, data_020e37f8, 0);
            data_020e37f8 = 7;
            LibraryOverlay_Switch68();
            func_020ba37c();
            activity->state = 0x19;
            return;
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            ActivitySave_EndSteps(activity, &activity->state, 0xe, 0x14, AIDS_HOST, 1);
            return;
        default:
            ActivityTalk_Close(activity);
            func_020a4e94(activity, 8);
            return;
    }
}
CLEAN_AS(func_020a38e0, ActivityLinkJobs_Step17)

/* func_020a38d4: job 0x18 starts: the gatekeeper's message 105. */
void ActivityLinkJobs_Start18(Activity *activity)
{
    Activity_TalkGatekeeper(activity, 0);
}
CLEAN_AS(func_020a38d4, ActivityLinkJobs_Start18)

/* func_020a35bc: job 0x18's steps, with the peers' link; the leaving slot is the link state's:
 *   0  once talk 0 waits (given 0), the member mask kept, the exchange blocks swapped with a
 *      random one and this system's paired town paired;
 *   1-2  mode 1 requested once the others are in scene 0x2e; 3  wait for all their reports;
 *   4  once the exchange blocks are sent to the guests, the leaving slot's block copied to
 *      the slot whose block it gets and cleared, the activity's taken, and the slot forgotten
 *      by the recent slots;
 *   5-11  ActivitySave_HostSteps (fail 0xf, end 0x15, slot 4, with the exchange);
 *   12 once every other system sent system packet 17 and the leaving one owes no credits,
 *      system packet 18 sent to it;
 *   13 with the link of the others, once sendable or alone: the leaving slot removed, the
 *      session mode 2 and, when linked, message 5/5 with the slot sent;
 *   14 once every other system sent system packet 19, func_020ba37c called and message 7/5
 *      sent; alone, func_02046830;
 *   15-25  ActivitySave_EndSteps from 0xf;
 * then talk 0 closed and job 0xa. */
void ActivityLinkJobs_Step18(Activity *activity)
{
    NetSession *session;
    switch (activity->state) {
        case 0:
            if (link_lost(Session_GetPeerMask()) || !ActivityTalk_FinishWaiting(activity, 0)) {
                return;
            }
            *member_mask(activity) = (u16) Session_GetMemberMask();
            ExchangeBlocks_SwapWithRandom(activity);
            PairedTown_PairOwn(activity);
            activity->state = 1;
            return;
        case 1:
        case 2:
            if (link_lost(Session_GetPeerMask())) {
                return;
            }
            Activity_StepRequestMode1(activity, &activity->state, 1, 0x2e, 0x2e);
            return;
        case 3:
            if (link_lost(Session_GetPeerMask()) || !Activity_AllPeersReported(activity)) {
                return;
            }
            activity->state = 4;
            return;
        case 4: {
            if (link_lost(Session_GetPeerMask()) || !ExchangeBlocks_SendToGuests(activity)) {
                return;
            }
            int leaving = (int) func_020a6ed0();
            int source = Activity_BlockSource(activity, leaving);
            u8 *block = func_02090040(leaving);
            MI_CpuCopy8(block, func_02090040(source), 0x950);
            func_02090174(block);
            Activity_SystemExchangeBlockToActivity(activity);
            RecentSlots_Forget((u8) leaving);
            activity->state = 5;
            return;
        }
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            ActivitySave_HostSteps(activity, &activity->state, 1, 5, 0xf, 0x15, NO_SLOT, 1, Session_GetPeerMask());
            return;
        case 12:
            if (link_lost(Session_GetPeerMask())) {
                return;
            }
            session = data_020ccf94;
            if (!all_peers_set(session, activity->slot_fc) || Session_GetOwedCredits(session, (int) func_020a6ed0())) {
                return;
            }
            if (!SystemPacket_SendActivityFlagE5((u16) (1 << func_020a6ed0()))) {
                return;
            }
            activity->state = 13;
            return;
        case 13:
            if (link_lost(Session_GetPeerMask() ^ (u16) (1 << func_020a6ed0()))) {
                return;
            }
            if (!sendable() && (unsigned int) Net_CountPlayers() > 1) {
                return;
            }
            Session_RemovePlayer((int) func_020a6ed0());
            session = data_020ccf94;
            Session_SetMode(session, SESSION_MODE_2);
            if (Session_IsLinked(session)) {
                u8 slot = (u8) func_020a6ed0();
                session = data_020ccf94;
                Session_BeginMessage(session);
                Session_AppendMessage(session, &slot, 1);
                Session_EndMessage(session, 5, 5);
            }
            activity->state = 14;
            return;
        case 14:
            if (link_lost(Session_GetPeerMask())) {
                return;
            }
            session = data_020ccf94;
            if (!all_peers_set(session, activity->slot_ack)) {
                return;
            }
            func_020ba37c();
            session = data_020ccf94;
            Session_BeginMessage(session);
            Session_EndMessage(session, 7, 5);
            if (session->player_count == 1) {
                func_02046830();
            }
            activity->state = 0x1a;
            return;
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
            ActivitySave_EndSteps(activity, &activity->state, 0xf, 0x15, Session_GetPeerMask(), 1);
            return;
        default:
            ActivityTalk_Close(activity);
            func_020a4e94(activity, 0xa);
            return;
    }
}
CLEAN_AS(func_020a35bc, ActivityLinkJobs_Step18)

/* func_020a35b0: job 0x19 starts: the gatekeeper's message 105. */
void ActivityLinkJobs_Start19(Activity *activity)
{
    Activity_TalkGatekeeper(activity, 0);
}
CLEAN_AS(func_020a35b0, ActivityLinkJobs_Start19)

/* func_020a33e0: job 0x19's steps, with the host's link:
 *   0  once talk 0 waits (given 0), the member mask kept;
 *   1-2  this system reports; 3  once this system's slot_107 is set, the system's exchange
 *      block taken;
 *   4-11  ActivitySave_GuestSteps (fail 0xf, end 0x15, with the exchange, restore);
 *   12 once the link state's slot owes no credits, system packet 17 sent;
 *   13 once sendable and the member mask changed: the link state's slot entry reset, the
 *      session mode 2 and message 6/0 sent;
 *   14 once a session message set flag_e6, func_020ba37c called;
 *   15-25  ActivitySave_EndSteps from 0xf;
 * then talk 0 closed and job 0xa. */
void ActivityLinkJobs_Step19(Activity *activity)
{
    NetSession *session;
    switch (activity->state) {
        case 0:
            if (link_lost(AIDS_HOST) || !ActivityTalk_FinishWaiting(activity, 0)) {
                return;
            }
            *member_mask(activity) = (u16) Session_GetMemberMask();
            activity->state = 1;
            return;
        case 1:
        case 2:
            if (link_lost(AIDS_HOST)) {
                return;
            }
            Activity_StepSendReport(activity, &activity->state, 1);
            return;
        case 3:
            if (link_lost(AIDS_HOST) || !Activity_Slot107(activity, data_020ccf94->local_slot)) {
                return;
            }
            Activity_SystemExchangeBlockToActivity(activity);
            activity->state = 4;
            return;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            ActivitySave_GuestSteps(activity, &activity->state, 4, 0xf, 0x15, 1, 1, AIDS_HOST);
            return;
        case 12:
            if (link_lost(AIDS_HOST)) {
                return;
            }
            if (Session_GetOwedCredits(data_020ccf94, (int) func_020a6ed0()) || !SystemPacket_SendActivityPlayerFC()) {
                return;
            }
            activity->state = 13;
            return;
        case 13:
            if (link_lost(AIDS_HOST) || !sendable()) {
                return;
            }
            if (*member_mask(activity) == (u16) Session_GetMemberMask()) {
                return;
            }
            func_020a6c6c((int) func_020a6ed0());
            session = data_020ccf94;
            Session_SetMode(session, SESSION_MODE_2);
            Session_BeginMessage(session);
            Session_EndMessage(session, 6, 0);
            activity->state = 14;
            return;
        case 14:
            if (link_lost(AIDS_HOST) || !activity->flag_e6) {
                return;
            }
            func_020ba37c();
            activity->state = 0x1a;
            return;
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
            ActivitySave_EndSteps(activity, &activity->state, 0xf, 0x15, AIDS_HOST, 1);
            return;
        default:
            ActivityTalk_Close(activity);
            func_020a4e94(activity, 0xa);
            return;
    }
}
CLEAN_AS(func_020a33e0, ActivityLinkJobs_Step19)

/* func_020a33d8: job 0x1a starts: message 7 of "sp_etc_sequence2" (Activity_TalkSequence2). */
void ActivityLinkJobs_Start1A(Activity *activity)
{
    Activity_TalkSequence2(activity);
}
CLEAN_AS(func_020a33d8, ActivityLinkJobs_Start1A)

/* func_020a3084: job 0x1a's steps, with the peers' link; "leaving" is the start menu's leave
 * choice (StartMenu_LeaveChoice):
 *   0  once talk 0 waits (given 0); leaving, the exchange blocks rotated and all paired;
 *   1-2  mode 1 requested once the others are in scene 0x2e; 3  wait for all their reports;
 *   4  leaving, once the exchange blocks are sent to the guests: this system's block replaced
 *      by the one of the slot it gets (cleared when none), the three others cleared and the
 *      activity's block taken;
 *   5-11  ActivitySave_HostSteps (fail 0x10, end 0x16, slot 4, the exchange when leaving);
 *   12 once sendable: not leaving, the session mode 2 and step 14; leaving, step 13;
 *   13 once every other system sent system packet 17 and none owes credits, system packet 18
 *      sent to the peers;
 *   15 once every other system sent system packet 19 (read with the session's interrupts
 *      off), the session left with record 7 keeping the town, and overlay 68 loaded;
 *   14 message 7/5 sent;
 *   16-26  ActivitySave_EndSteps from 0x10;
 * then talk 0 closed, leaving it is given message 6 of "sp_etc_sequence2" next; job 8. */
void ActivityLinkJobs_Step1A(Activity *activity)
{
    NetSession *session;
    switch (activity->state) {
        case 0:
            if (link_lost(Session_GetPeerMask()) || !ActivityTalk_FinishWaiting(activity, 0)) {
                return;
            }
            if (StartMenu_LeaveChoice()) {
                ExchangeBlocks_Rotate(activity);
                PairedTown_PairAll(activity);
            }
            activity->state = 1;
            return;
        case 1:
        case 2:
            if (link_lost(Session_GetPeerMask())) {
                return;
            }
            Activity_StepRequestMode1(activity, &activity->state, 1, 0x2e, 0x2e);
            return;
        case 3:
            if (link_lost(Session_GetPeerMask()) || !Activity_AllPeersReported(activity)) {
                return;
            }
            activity->state = 4;
            return;
        case 4:
            if (link_lost(Session_GetPeerMask())) {
                return;
            }
            if (StartMenu_LeaveChoice()) {
                if (!ExchangeBlocks_SendToGuests(activity)) {
                    return;
                }
                int source = Activity_BlockSource(activity, 0);
                if (source < NO_SLOT) {
                    u8 *own = func_02090040(0);
                    MI_CpuCopy8(func_02090040(source), own, 0x950);
                } else {
                    func_02090174(func_02090040(0));
                }
                for (int slot = 2; slot >= 0; slot--) {
                    func_02090174(func_02090040(slot + 1));
                }
                Activity_SystemExchangeBlockToActivity(activity);
            }
            activity->state = 5;
            return;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            ActivitySave_HostSteps(activity, &activity->state, 1, 5, 0x10, 0x16, NO_SLOT, StartMenu_LeaveChoice() != 0,
                                   Session_GetPeerMask());
            return;
        case 12:
            if (link_lost(Session_GetPeerMask()) || !sendable()) {
                return;
            }
            if (!StartMenu_LeaveChoice()) {
                Session_SetMode(data_020ccf94, SESSION_MODE_2);
                activity->state = 14;
            } else {
                activity->state = 13;
            }
            return;
        case 14:
            if (link_lost(Session_GetPeerMask())) {
                return;
            }
            session = data_020ccf94;
            Session_BeginMessage(session);
            Session_EndMessage(session, 7, 5);
            activity->state = 0x1b;
            return;
        case 13:
            if (link_lost(Session_GetPeerMask())) {
                return;
            }
            session = data_020ccf94;
            if (!all_peers_set(session, activity->slot_fc) || !no_peer_owes(session)) {
                return;
            }
            if (!SystemPacket_SendActivityFlagE5(Session_GetPeerMask())) {
                return;
            }
            activity->state = 15;
            return;
        case 15: {
            if (link_lost(Session_GetPeerMask())) {
                return;
            }
            Session_DisableInterrupts();
            int all = all_peers_set(data_020ccf94, activity->slot_ack);
            Session_EnableInterrupts();
            if (!all) {
                return;
            }
            ActivitySave_LeaveSession(activity, 7, 1);
            LibraryOverlay_Switch68();
            activity->state = 0x1b;
            return;
        }
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
            ActivitySave_EndSteps(activity, &activity->state, 0x10, 0x16, Session_GetPeerMask(), 1);
            return;
        default:
            ActivityTalk_Close(activity);
            if (StartMenu_LeaveChoice()) {
                queue_sequence2(SEQUENCE2_LEFT);
            }
            func_020a4e94(activity, 8);
            return;
    }
}
CLEAN_AS(func_020a3084, ActivityLinkJobs_Step1A)

/* func_020a307c: job 0x1b starts: message 7 of "sp_etc_sequence2" (Activity_TalkSequence2). */
void ActivityLinkJobs_Start1B(Activity *activity)
{
    Activity_TalkSequence2(activity);
}
CLEAN_AS(func_020a307c, ActivityLinkJobs_Start1B)

/* func_020a2dec: job 0x1b's steps, with the host's link; "leaving" is the start menu's leave
 * choice:
 *   0  once talk 0 waits (given 0); 1-2  this system reports;
 *   3  leaving, once this system's slot_107 is set, the system's exchange block taken;
 *   4-11  ActivitySave_GuestSteps (fail 0x11, end 0x17, the exchange when leaving, restore
 *      when not);
 *   12 once sendable: not leaving step 13, leaving step 14;
 *   13 once a session message set flag_e6, the session mode 2;
 *   14 once no other system owes credits, system packet 17 sent;
 *   15 once system packet 18 came, system packet 19 sent and the connect mode 2;
 *   16 once the connection is updated, the session left with the guest record (then 7
 *      again), and overlay 68 loaded;
 *   17-27  ActivitySave_EndSteps from 0x11;
 * then talk 0 closed; leaving, it is given message 6 of "sp_etc_sequence2" next and job 0x11
 * starts; else job 8. */
void ActivityLinkJobs_Step1B(Activity *activity)
{
    switch (activity->state) {
        case 0:
            if (link_lost(AIDS_HOST) || !ActivityTalk_FinishWaiting(activity, 0)) {
                return;
            }
            activity->state = 1;
            return;
        case 1:
        case 2:
            if (link_lost(AIDS_HOST)) {
                return;
            }
            Activity_StepSendReport(activity, &activity->state, 1);
            return;
        case 3:
            if (link_lost(AIDS_HOST)) {
                return;
            }
            if (StartMenu_LeaveChoice()) {
                if (!Activity_Slot107(activity, data_020ccf94->local_slot)) {
                    return;
                }
                Activity_SystemExchangeBlockToActivity(activity);
            }
            activity->state = 4;
            return;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11: {
            int restore = StartMenu_LeaveChoice() == 0;
            ActivitySave_GuestSteps(activity, &activity->state, 4, 0x11, 0x17, StartMenu_LeaveChoice() != 0, (u8) restore,
                                    AIDS_HOST);
            return;
        }
        case 12:
            if (link_lost(AIDS_HOST) || !sendable()) {
                return;
            }
            activity->state = StartMenu_LeaveChoice() ? 14 : 13;
            return;
        case 13:
            if (link_lost(AIDS_HOST) || !activity->flag_e6) {
                return;
            }
            Session_SetMode(data_020ccf94, SESSION_MODE_2);
            activity->state = 0x1c;
            return;
        case 14:
            if (link_lost(AIDS_HOST) || !no_peer_owes(data_020ccf94) || !SystemPacket_SendActivityPlayerFC()) {
                return;
            }
            activity->state = 15;
            return;
        case 15:
            if (link_lost(AIDS_HOST) || !activity->flag_e5 || !SystemPacket_SendActivityPlayerF4()) {
                return;
            }
            Session_SetConnectMode(data_020ccf94, CONNECT_MODE_2);
            activity->state = 16;
            return;
        case 16:
            LibraryOverlay_RequireAny();
            if (Net_UpdateConnection()) {
                return;
            }
            ActivitySave_LeaveSession(activity, data_020e37f8, 0);
            LibraryOverlay_Switch68();
            data_020e37f8 = 7;
            activity->state = 0x1c;
            return;
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
            ActivitySave_EndSteps(activity, &activity->state, 0x11, 0x17, AIDS_HOST, 1);
            return;
        default:
            ActivityTalk_Close(activity);
            if (StartMenu_LeaveChoice()) {
                queue_sequence2(SEQUENCE2_LEFT);
                func_020a4e94(activity, 0x11);
            } else {
                func_020a4e94(activity, 8);
            }
            return;
    }
}
CLEAN_AS(func_020a2dec, ActivityLinkJobs_Step1B)

/* func_020a2ddc: job 0x1c starts: message 35 of "sp_etc_sequence1". */
void ActivityLinkJobs_Start1C(Activity *activity)
{
    ActivityTalk_Show(activity, data_020e3c54, SEQUENCE1_WAITING);
}
CLEAN_AS(func_020a2ddc, ActivityLinkJobs_Start1C)

/* func_020a2dbc: job 0x1c's step: once talk 0 waits (given 1), overlay 66 loaded and job 0x1d
 * started. */
void ActivityLinkJobs_Step1C(Activity *activity)
{
    if (!ActivityTalk_FinishWaiting(activity, 1)) {
        return;
    }
    LibraryOverlay_Switch66();
    func_020a4e94(activity, 0x1d);
}
CLEAN_AS(func_020a2dbc, ActivityLinkJobs_Step1C)

/* func_020a2d48: job 0x1d starts: a countdown of 600 frames, a session started (mode 1, two
 * players), the host's receive buffers set, and 14 bytes handed to overlay 66
 * (Local_Call02269638): the town's name (12 bytes), whether the state block is not set up,
 * and 1. The first free town record number kept in byte_102. */
void ActivityLinkJobs_Start1D(Activity *activity)
{
    u8 offer[16];

    *countdown(activity) = WAIT_FRAMES;
    Session_Start(1, 2, 0);
    Session_SetHostReceiveBuffers();
    MI_CpuCopy8(func_020642a4(&data_021dc7a8.town), offer, 12);
    offer[13] = 1;
    offer[12] = StateBlock_IsSetUp(&data_021dc7a8) == 0;
    LibraryOverlay_Require66();
    Local_Call02269638(offer, 14);
    activity->byte_102 = (u8) PlayerRecords_FirstFree(data_021dc7a8.players);
}
CLEAN_AS(func_020a2d48, ActivityLinkJobs_Start1D)

/* func_020a2c8c: job 0x1d's step: once system packet 20 named a slot 1-3, talk 0 closed and
 * given message 38 of "sp_etc_sequence1", and job 0. Else, with two players the countdown is
 * reset; with one it counts down (sending nothing meanwhile); with none or at its end the Wi-Fi
 * session ended (then overlay 68), talk 0 given message 37 and closed, and job 0xc. */
void ActivityLinkJobs_Step1D(Activity *activity)
{
    int slot = Activity_CurrentSlot100();
    if (slot > 0 && slot < NO_SLOT) {
        ActivityTalk *talk = func_020682e0(TALK_INDEX);
        func_02068358(talk);
        func_02068434(talk);
        u8 message = SEQUENCE1_LINKED;
        func_0206844c(talk, &message, data_020e3c54);
        func_020a4e94(activity, 0);
        return;
    }
    if (Net_CountPlayers() == 2) {
        *countdown(activity) = 0;
        return;
    }
    int give_up = 0;
    if (Net_CountPlayers() == 1) {
        if (Countdown_Tick16(countdown(activity)) == 0) {
            give_up = 1;
        } else {
            Session_SendNothing();
        }
    } else {
        give_up = 1;
    }
    if (give_up) {
        if (WfcSession_End(activity)) {
            LibraryOverlay_Switch68();
        }
        ActivityTalk *talk = func_020682e0(TALK_INDEX);
        u8 message = SEQUENCE1_TIMED_OUT;
        func_0206844c(talk, &message, data_020e3c54);
        func_02068358(talk);
        func_02068434(talk);
        func_020a4e94(activity, 0xc);
    }
}
CLEAN_AS(func_020a2c8c, ActivityLinkJobs_Step1D)

/* func_020a2c5c: job 0x1e starts at step 0; byte 0x10b says whether the state block is not set
 * up. */
void ActivityLinkJobs_Start1E(Activity *activity)
{
    activity->state = 0;
    activity->unk_10b[0] = StateBlock_IsSetUp(&data_021dc7a8) == 0;
}
CLEAN_AS(func_020a2c5c, ActivityLinkJobs_Start1E)

/* func_020a2948: job 0x1e's steps, with every AID's link, for the slot of system packet 20
 * (Activity_CurrentSlot100):
 *   0  once talk 0 waits (given 0); 1  wait for that slot to be 1-3;
 *   2  once system packet 23 came: a state block not set up is started in mode 5, one set up
 *      gets flag 0x12; the player's options stored;
 *   3  the letters written; 4  the card checked, the stamp marked as being written;
 *   5  the copy to write written;
 *   6  that slot's answer (system packet 14): OK, the stamp marked written, the answer
 *      cleared and the connect mode 2; END, step 0x11;
 *   7  the copy written again; 8  system packet 14 (OK) sent to the slot, the connect mode 0;
 *   9  once the slot is no longer connected, the Wi-Fi session ended (then overlay 68);
 *   10 after a lost link, the copy written (the stamp as being written), the connect mode 0;
 *   11-21  ActivitySave_EndSteps from 0xb;
 * then talk 0 closed and job 0xe. A failed card step goes to step 0xb.
 * REQUIRES: the slot of system packet 20 stays 1-3 from step 1 on (it indexes slot_answer). */
void ActivityLinkJobs_Step1E(Activity *activity)
{
    int result;
    int slot;
    switch (activity->state) {
        case 0:
            if (link_lost(AIDS_ALL)) {
                return;
            }
            if (ActivityTalk_FinishWaiting(activity, 0)) {
                activity->state = 1;
            }
            return;
        case 1:
            if (link_lost(AIDS_ALL)) {
                return;
            }
            slot = Activity_CurrentSlot100();
            if (slot > 0 && slot < NO_SLOT) {
                activity->state = 2;
            }
            return;
        case 2:
            if (link_lost(AIDS_ALL) || !activity->flag_101) {
                return;
            }
            if (activity->unk_10b[0] == 0) {
                StateBlock_Start(&data_021dc7a8, STATE_BLOCK_MODE_5);
                StateBlock_FinishStart(&data_021dc7a8);
            } else {
                StateBlock_SetFlag((u32 *) (void *) &data_021dc7a8, STATE_BLOCK_FLAG_12);
            }
            PlayerOptions_Store();
            activity->state = 3;
            return;
        case 3:
            if (link_lost(AIDS_ALL)) {
                return;
            }
            result = ActivityCard_StepWritePart(activity, CARD_PART_LETTERS);
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 0xb;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 4;
            }
            return;
        case 4:
            if (link_lost(AIDS_ALL)) {
                return;
            }
            result = ActivityCard_StepCheck(activity);
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 0xb;
            } else if (result != ACTIVITY_CARD_BUSY) {
                SaveStamp_MarkWriting(&data_021f3ba0);
                activity->state = 5;
            }
            return;
        case 5:
            if (link_lost(AIDS_ALL)) {
                return;
            }
            result = ActivityCard_StepWritePart(activity, write_part(activity));
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 0xb;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 6;
            }
            return;
        case 6:
            if (link_lost(AIDS_ALL)) {
                return;
            }
            result = activity->slot_answer[Activity_CurrentSlot100()];
            if (result == ACTIVITY_ANSWER_OK) {
                SaveStamp_MarkWritten(&data_021f3ba0);
                activity->slot_answer[Activity_CurrentSlot100()] = ACTIVITY_ANSWER_NONE;
                Session_SetConnectMode(data_020ccf94, CONNECT_MODE_2);
                activity->state = 7;
            } else if (result == ACTIVITY_ANSWER_END) {
                activity->state = 0x11;
            }
            return;
        case 7:
            Session_IsLinkLost(AIDS_ALL);
            result = ActivityCard_StepWritePart(activity, write_part(activity));
            if (result == ACTIVITY_CARD_FAILED) {
                Session_SetConnectMode(data_020ccf94, CONNECT_MODE_0);
                activity->state = 0xb;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 8;
            }
            return;
        case 8:
            if (Session_IsLinkLost(AIDS_ALL)) {
                SaveStamp_MarkWriting(&data_021f3ba0);
                activity->state = 0xa;
            } else if (SystemPacket_SendActivityPlayerEF(ACTIVITY_ANSWER_OK, (u16) (1 << Activity_CurrentSlot100()))) {
                Session_SetConnectMode(data_020ccf94, CONNECT_MODE_0);
                activity->state = 9;
            }
            return;
        case 9:
            if ((Net_GetConnectedMask() & (1 << Activity_CurrentSlot100())) == 0) {
                if (WfcSession_End(activity)) {
                    LibraryOverlay_Switch68();
                }
                activity->state = 0x16;
            }
            return;
        case 10:
            Session_IsLinkLost(AIDS_ALL);
            result = ActivityCard_StepWritePart(activity, write_part(activity));
            if (result == ACTIVITY_CARD_FAILED) {
                Session_SetConnectMode(data_020ccf94, CONNECT_MODE_0);
                activity->state = 0xb;
            } else if (result == ACTIVITY_CARD_DONE) {
                Session_SetConnectMode(data_020ccf94, CONNECT_MODE_0);
                activity->state = 0x11;
            }
            return;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
            ActivitySave_EndSteps(activity, &activity->state, 0xb, 0x11, (u16) (1 << Activity_CurrentSlot100()), 1);
            return;
        default:
            ActivityTalk_Close(activity);
            func_020a4e94(activity, 0xe);
            return;
    }
}
CLEAN_AS(func_020a2948, ActivityLinkJobs_Step1E)

/* func_020a2924: job 0x1f starts at step 0: the current player's flag 2 cleared and the
 * transfer of this system's AID stopped. */
void ActivityLinkJobs_Start1F(Activity *activity)
{
    PlayerRecord_ClearFlag(PlayerRecords_Current(), PLAYER_FLAG_2);
    Session_StopTransfer((u32) Net_GetMyAid());
    activity->state = 0;
}
CLEAN_AS(func_020a2924, ActivityLinkJobs_Start1F)

/* func_020a2650: job 0x1f's steps, with the host's link:
 *   0  system packet 20 sent; 1  this system's record sent (21); 2  the record block (22);
 *   3  system packet 23;
 *   4  once sendable: byte 0x82 of the object at data_021d351c set, the current player's
 *      record kept at 0xbc and cleared, and the player forgotten by the state block;
 *   5  the card checked, then the connect mode 2; 6  the copy to write written;
 *   7  system packet 14 (OK) sent to the host; 8  once sendable, its answer: OK, the connect
 *      mode 0; END, the stamp marked as being written and step 10;
 *   9  the Wi-Fi session ended (then overlay 68), the kept record copied back and byte 0x82
 *      cleared;
 *   10 after a lost link or END, the copy written again, the connect mode 0;
 *   11-21  ActivitySave_EndSteps from 0xb;
 * then job 0. A failed card step goes to step 0xb (connect mode 0 again once it was 2). */
void ActivityLinkJobs_Step1F(Activity *activity)
{
    int result;
    switch (activity->state) {
        case 0:
            if (link_lost(AIDS_HOST) || !SystemPacket_SendActivityPlayer100()) {
                return;
            }
            activity->state = 1;
            return;
        case 1:
            if (link_lost(AIDS_HOST) || !SystemPacket_SendOwnRecord(&activity->unk_d8)) {
                return;
            }
            activity->unk_d8 = 0;
            activity->state = 2;
            return;
        case 2:
            if (link_lost(AIDS_HOST) || !SystemPacket_SendRecordBlock(&activity->unk_d8)) {
                return;
            }
            activity->unk_d8 = 0;
            activity->state = 3;
            return;
        case 3:
            if (link_lost(AIDS_HOST) || !SystemPacket_SendActivityFlag101()) {
                return;
            }
            activity->state = 4;
            return;
        case 4:
            if (link_lost(AIDS_HOST) || !sendable()) {
                return;
            }
            func_0208b9b8(func_0208b4f8());
            MI_CpuCopy8(PlayerRecords_Current(), record_copy(activity), PLAYER_RECORD_SIZE);
            PlayerRecord_Clear(PlayerRecords_Current());
            StateBlock_ForgetPlayer(&data_021dc7a8, PlayerRecords_CurrentNumber());
            activity->state = 5;
            return;
        case 5:
            if (link_lost(AIDS_HOST)) {
                return;
            }
            result = ActivityCard_StepCheck(activity);
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 0xb;
            } else if (result != ACTIVITY_CARD_BUSY) {
                Session_SetConnectMode(data_020ccf94, CONNECT_MODE_2);
                activity->state = 6;
            }
            return;
        case 6:
            Session_IsLinkLost(AIDS_HOST);
            result = ActivityCard_StepWritePart(activity, write_part(activity));
            if (result == ACTIVITY_CARD_FAILED) {
                Session_SetConnectMode(data_020ccf94, CONNECT_MODE_0);
                activity->state = 0xb;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 7;
            }
            return;
        case 7:
            if (Session_IsLinkLost(AIDS_HOST)) {
                SaveStamp_MarkWriting(&data_021f3ba0);
                activity->state = 0xa;
            } else if (SystemPacket_SendActivityPlayerEF(ACTIVITY_ANSWER_OK, 1)) {
                activity->state = 8;
            }
            return;
        case 8:
            if (Session_IsLinkLost(AIDS_HOST)) {
                SaveStamp_MarkWriting(&data_021f3ba0);
                activity->state = 0xa;
                return;
            }
            if (!sendable()) {
                return;
            }
            result = activity->slot_answer[0];
            if (result == ACTIVITY_ANSWER_OK) {
                Session_SetConnectMode(data_020ccf94, CONNECT_MODE_0);
                activity->state = 9;
            } else if (result == ACTIVITY_ANSWER_END) {
                SaveStamp_MarkWriting(&data_021f3ba0);
                activity->state = 0xa;
            }
            return;
        case 9:
            if (WfcSession_End(activity)) {
                LibraryOverlay_Switch68();
            }
            MI_CpuCopy8(record_copy(activity), PlayerRecords_Current(), PLAYER_RECORD_SIZE);
            func_0208b9b0(func_0208b4f8());
            activity->state = 0x16;
            return;
        case 10:
            Session_IsLinkLost(AIDS_HOST);
            result = ActivityCard_StepWritePart(activity, write_part(activity));
            if (result == ACTIVITY_CARD_FAILED) {
                Session_SetConnectMode(data_020ccf94, CONNECT_MODE_0);
                activity->state = 0xb;
            } else if (result == ACTIVITY_CARD_DONE) {
                Session_SetConnectMode(data_020ccf94, CONNECT_MODE_0);
                activity->state = 0x11;
            }
            return;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
            ActivitySave_EndSteps(activity, &activity->state, 0xb, 0x11, AIDS_HOST, 1);
            return;
        default:
            func_020a4e94(activity, 0);
            return;
    }
}
CLEAN_AS(func_020a2650, ActivityLinkJobs_Step1F)
