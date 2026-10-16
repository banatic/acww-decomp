/* Questions the talks of the overlays' scenes ask (villagers' and others'): whether this
 * console leads the session, the player's dated event of today and its mark, the player's
 * daily bits, and a menu of fixed choices. */
#ifndef CLEAN_MAIN_TALK_CHECKS_H
#define CLEAN_MAIN_TALK_CHECKS_H

#include "scene_base.h"
#include "types.h"

int TalkChecks_IsHostOrAlone(void);
void TalkChecks_MarkDayEvent(int unused, const u8 *event);
int TalkChecks_TodaysEventOfKind(int unused, u8 *event, int kind);
int TalkChecks_TestSetDailyBit(int bit, int set);
void TalkChecks_OfferMessages(SceneBase *scene, const u8 *messages, int count, int cancel);

#endif
