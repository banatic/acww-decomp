/* Questions the overlays' talks ask (talk_checks.h). */
#include "talk_checks.h"

#include "calendar.h"
#include "clean.h"
#include "daily_bits.h"
#include "date_time.h"
#include "day_events.h"
#include "player_record.h"
#include "player_records.h"
#include "session.h"
#include "talk_answers.h"

/* The slot of the session's leader. */
#define TALK_CHECKS_HOST_SLOT 0
/* The message data each fixed choice is set with. */
#define TALK_CHECKS_CHOICE_DATA 0xff

extern NetSession *data_020ccf94;

/* func_0202e9fc: 1 unless linked with others (Session_IsLinked) with this console in a slot
 * other than the leader's (0). */
int TalkChecks_IsHostOrAlone(void)
{
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) != 0 && Session_IsLocalSlot(session, TALK_CHECKS_HOST_SLOT) == 0) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_0202e9fc, TalkChecks_IsHostOrAlone)

/* func_0202ea28: `*event` marked as the current player's last dated event part reached
 * (DayEvents_SetMark on the record's mark at 0x2427). The first argument is not used. */
void TalkChecks_MarkDayEvent(int unused, const u8 *event)
{
    (void) unused;
    DayEvents_SetMark((DayEventMark *) (void *) PlayerRecord_Field2427(PlayerRecords_Current()), event);
}
CLEAN_AS(func_0202ea28, TalkChecks_MarkDayEvent)

/* func_0202ea40: today's dated event part into `*event` (DayEvents_PlayerHas with the clock's
 * date); whether the player has it and it is of `kind`. The first argument is not used. */
int TalkChecks_TodaysEventOfKind(int unused, u8 *event, int kind)
{
    (void) unused;
    DateTime now = {0};
    DateTime_Now(&now);
    return DayEvents_PlayerHas(now.year, now.month, now.day, event) != 0 && DAY_EVENT_KIND(*event) == kind;
}
CLEAN_AS(func_0202ea40, TalkChecks_TodaysEventOfKind)

/* func_0202ea80: whether daily bit `bit` of the current player is set, setting it after the
 * test when `set` is; 0 without a current player. */
int TalkChecks_TestSetDailyBit(int bit, int set)
{
    u8 *record = PlayerRecords_Current();
    if (record == NULL) {
        return 0;
    }
    DailyBits *bits = (DailyBits *) (void *) PlayerRecord_Field23EC(record);
    int was_set = DailyBits_Test(bits, (u32) bit) != 0;
    if (set != 0) {
        DailyBits_Set(bits, (u32) bit);
    }
    return was_set;
}
CLEAN_AS(func_0202ea80, TalkChecks_TestSetDailyBit)

/* func_0202eac8: the scene's menu (SceneBase_TalkChoices) offers `count` choices, choice i the
 * message `messages[i]` (one byte, on the stack, with the data byte 0xff); `cancel` is the
 * choice for cancelling. The menu is used without a check that the scene has one. */
void TalkChecks_OfferMessages(SceneBase *scene, const u8 *messages, int count, int cancel)
{
    void *menu = (void *) (uintptr_t) SceneBase_TalkChoices(scene);
    TalkAnswers_Reset(menu, count, cancel);
    for (int i = 0; i < count; i++) {
        u8 choice[2];
        choice[0] = messages[i];
        choice[1] = TALK_CHECKS_CHOICE_DATA;
        TalkAnswers_Set(menu, i, &choice[0], 0, &choice[1], 0, 0);
    }
    TalkAnswers_LoadTexts(menu);
}
CLEAN_AS(func_0202eac8, TalkChecks_OfferMessages)
