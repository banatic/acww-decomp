/* The activity process (activity.h). */
#include "activity.h"

#include "autoload_2/heap.h" /* Heap_FreeAux */
#include "clean.h"
#include "player_record.h"
#include "player_records.h"
#include "start_menu.h"
#include "system_packet.h"

static_assert(offsetof(Activity, receiver) == 0x54 && offsetof(Activity, state) == 0xa1, "activity");
static_assert(offsetof(Activity, slot_reported) == 0xf8, "activity");

/* Vtables: the process's and its base class's. */
extern const u32 data_020e3ae8[];
extern const u32 data_020da13c[];

extern NetSession *data_020ccf94;

extern const char data_020e3c40[]; /* "sp_etc_sequence2" */
extern const char data_020e3c2c[]; /* "sp_npc_gatekeeper" */

/* The receiver's destructor. */
extern void *func_020a256c(void *receiver);
/* Message `message` of file `name` shown through the activity's receiver in talk 0. */
extern int func_020a1954(Activity *activity, const char *name, int message);
/* The object func_0208d0bc is told 0 and 1 by both talks. */
extern void *func_0208b500(void);
extern void func_0208d0bc(void *object, int a, int b);
/* A slot's scene in the link state table (0x3f above slot 3), and the third byte of its
 * entry. */
extern int func_020a7330(int slot);
extern int func_020a72d0(int slot);

#define PLAYER_FLAG_2 2
#define SEQUENCE2_MESSAGE 7
#define GATEKEEPER_MESSAGE 105
#define SESSION_MODE_1 1

/* func_0209fb74: the destructor. */
Activity *Activity_Destruct(Activity *activity)
{
    activity->process.vtable = data_020e3ae8;
    func_020a256c(activity->receiver);
    activity->process.vtable = data_020da13c;
    Process_Destruct(&activity->process);
    return activity;
}
CLEAN_AS(func_0209fb74, Activity_Destruct)

/* func_0209fba0: the destructor, then the object freed. */
Activity *Activity_DestructFree(Activity *activity)
{
    activity->process.vtable = data_020e3ae8;
    func_020a256c(activity->receiver);
    activity->process.vtable = data_020da13c;
    Process_Destruct(&activity->process);
    Heap_FreeAux(activity);
    return activity;
}
CLEAN_AS(func_0209fba0, Activity_DestructFree)

/* func_020a0244: message 7 of "sp_etc_sequence2" shown and the current player's flag 2
 * cleared; when the start menu's leave choice (StartMenu_LeaveChoice) is set, func_0208d0bc
 * is called and the flag set again. */
void Activity_TalkSequence2(Activity *activity)
{
    func_020a1954(activity, data_020e3c40, SEQUENCE2_MESSAGE);
    PlayerRecord_ClearFlag(PlayerRecords_Current(), PLAYER_FLAG_2);
    if (StartMenu_LeaveChoice() != 0) {
        func_0208d0bc(func_0208b500(), 0, 1);
        PlayerRecord_SetFlag(PlayerRecords_Current(), PLAYER_FLAG_2);
    }
}
CLEAN_AS(func_020a0244, Activity_TalkSequence2)

/* func_020a0284: unless `quiet`, message 105 of "sp_npc_gatekeeper" shown; then the current
 * player's flag 2 cleared and func_0208d0bc called. */
void Activity_TalkGatekeeper(Activity *activity, int quiet)
{
    if (quiet == 0) {
        func_020a1954(activity, data_020e3c2c, GATEKEEPER_MESSAGE);
    }
    PlayerRecord_ClearFlag(PlayerRecords_Current(), PLAYER_FLAG_2);
    func_0208d0bc(func_0208b500(), 0, 1);
}
CLEAN_AS(func_020a0284, Activity_TalkGatekeeper)

/* func_020a02b4: two steps of an exchange from `first`: wait for the session's mode 1, then
 * for system packet 16 to be sent. `activity` is not read. */
void Activity_StepSendReport(Activity *activity, u8 *step, int first)
{
    (void) activity;
    if (*step == first) {
        if (Session_GetMode(data_020ccf94) == SESSION_MODE_1) {
            *step = (u8) (first + 1);
        }
    } else if (*step == first + 1) {
        if (SystemPacket_SendActivityPlayerF8() != 0) {
            *step = (u8) (first + 2);
        }
    }
}
CLEAN_AS(func_020a02b4, Activity_StepSendReport)

/* func_020a02f4: whether every other system in the session has reported (slot_reported). */
int Activity_AllPeersReported(Activity *activity)
{
    NetSession *session = data_020ccf94;
    for (int slot = ACTIVITY_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) != 0 && Session_IsLocalSlot(session, slot) == 0 &&
            activity->slot_reported[slot] == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_020a02f4, Activity_AllPeersReported)

/* func_020a0340: two steps of an exchange from `first`: once every other system in the session
 * is in scene `scene_a` or `scene_b` with the third byte of its link state entry 0, mode 1 is
 * requested; then, once the session is in mode 1, wait for system packet 8 to be sent.
 * `activity` is not read.
 * QUIRK: a slot's scene is read a second time when it is not `scene_a`. */
void Activity_StepRequestMode1(Activity *activity, u8 *step, int first, int scene_a, int scene_b)
{
    (void) activity;
    if (*step == first) {
        NetSession *session = data_020ccf94;
        for (int slot = ACTIVITY_SLOTS - 1; slot >= 0; slot--) {
            if (Session_IsSlotTaken(session, slot) == 0 || Session_IsLocalSlot(session, slot) != 0) {
                continue;
            }
            int in_scene = scene_a == func_020a7330(slot) || scene_b == func_020a7330(slot);
            if (!in_scene || func_020a72d0(slot) != 0) {
                return;
            }
        }
        Session_SetModeRequest(session, SESSION_MODE_1);
        *step = (u8) (first + 1);
    } else if (*step == first + 1 && Session_GetMode(data_020ccf94) == SESSION_MODE_1 && SystemPacket_SendModeRequest() != 0) {
        *step = (u8) (first + 2);
    }
}
CLEAN_AS(func_020a0340, Activity_StepRequestMode1)
