/* The answers a talk offers (talk_answers.h). */
#include "talk_answers.h"

#include <string.h>

#include "clean.h"
#include "text_base.h" /* TextBase_Copy */

static_assert(offsetof(TalkAnswer, record) == 0x64, "talk answer");
static_assert(offsetof(TalkAnswer, weight) == 0x8b, "talk answer");
static_assert(sizeof(TalkAnswer) == 0x90, "talk answer");
static_assert(offsetof(TalkAnswers, count) == 0x2d0, "talk answers");
static_assert(offsetof(TalkAnswers, picked_name) == 0x2dd, "talk answers");
static_assert(offsetof(TalkAnswers, picked_text) == 0x2f8, "talk answers");
static_assert(offsetof(TalkAnswers, picked_record) == 0x354, "talk answers");
static_assert(sizeof(TalkAnswers) == 0x364, "talk answers");

/* The slider's level, 0 to 0x1000, in 16 steps. */
#define TALK_ANSWERS_STEP_SHIFT 8
#define TALK_ANSWERS_STEP_MAX 15
/* The answers the slider's weights pick from; the last of them when the weights run out. */
#define TALK_ANSWERS_WEIGHED 4

/* Two entries (data structures of the game the answers' style word points to). */
extern u32 data_020d1de0[];

/* An answer's fields: its unk_70, its name, its text, its record (the addresses). */
extern u8 *func_020ab794(TalkAnswer *answer);
extern char *func_020ab790(TalkAnswer *answer);
extern TextBase *func_020ab798(TalkAnswer *answer);
extern void *func_020ab78c(TalkAnswer *answer);
extern u8 *func_020ab788(TalkAnswer *answer);
extern TalkAnswer *func_020ab550(TalkAnswers *answers, int index);

/* func_020ab39c: entry `index` of data_020d1de0 (an answer's style; the table has two). */
u32 TalkAnswers_Style(unsigned int index)
{
    return data_020d1de0[index];
}
CLEAN_AS(func_020ab39c, TalkAnswers_Style)

/* func_020ab3a8: the answer the slider's level (0 to 0x1000) picks. The level is cut into 16
 * steps (the top level counts as the last step); the first four answers share the steps by
 * their weights, in order, the first whose running total passes the step being picked (the
 * fourth when none does). The pick keeps its unk_70, its record and the step, not its name or
 * text.
 * QUIRK: the step is the level's bits 8 to 11 as an arithmetic shift of the level shifted left
 * by 4, so levels beyond 0x0fffffff wrap. */
void TalkAnswers_PickByLevel(TalkAnswers *answers, int level)
{
    int step = (int) ((uint32_t) level << 4) >> (TALK_ANSWERS_STEP_SHIFT + 4);
    if (step > TALK_ANSWERS_STEP_MAX) {
        step = TALK_ANSWERS_STEP_MAX;
    }

    int index = TALK_ANSWERS_WEIGHED - 1;
    int total = 0;
    for (unsigned int i = 0; i < TALK_ANSWERS_WEIGHED; i++) {
        total += *func_020ab788(&answers->answers[i]);
        if (step < total) {
            index = (int) i;
            break;
        }
    }

    TalkAnswer *answer = &answers->answers[index];
    answers->picked = index;
    answers->picked_70 = *func_020ab794(answer);
    Block020a8248_Copy(&answers->picked_record, Block020a8248_Self(func_020ab78c(answer)));
    answers->picked_step = (u32) step;
}
CLEAN_AS(func_020ab3a8, TalkAnswers_PickByLevel)

/* func_020ab42c: answer `index` picked: its index, unk_70, text, name (at most 0x19
 * characters, always ended) and record kept. */
void TalkAnswers_Pick(TalkAnswers *answers, int index)
{
    TalkAnswer *answer = &answers->answers[index];
    answers->picked = index;
    answers->picked_70 = *func_020ab794(answer);
    TextBase_Copy((TextBase *) answers->picked_text, func_020ab798(answer));
    const char *name = func_020ab790(answer);
    answers->picked_name[TALK_ANSWERS_NAME_SIZE - 1] = '\0';
    strncpy(answers->picked_name, name, TALK_ANSWERS_NAME_SIZE - 1);
    Block020a8248_Copy(&answers->picked_record, Block020a8248_Self(func_020ab78c(answer)));
}
CLEAN_AS(func_020ab42c, TalkAnswers_Pick)

/* func_020ab4a8: B picks the last answer. */
void TalkAnswers_SetCancelToLast(TalkAnswers *answers)
{
    answers->cancel = (s32) (answers->count - 1);
}
CLEAN_AS(func_020ab4a8, TalkAnswers_SetCancelToLast)

/* func_020ab4bc */
void TalkAnswers_SetCount(TalkAnswers *answers, int count)
{
    answers->count = (u32) count;
}
CLEAN_AS(func_020ab4bc, TalkAnswers_SetCount)

/* func_020ab4c8 */
Block020a8248 *TalkAnswers_PickedRecord(TalkAnswers *answers)
{
    return &answers->picked_record;
}
CLEAN_AS(func_020ab4c8, TalkAnswers_PickedRecord)

/* func_020ab4d4 */
u8 *TalkAnswers_PickedText(TalkAnswers *answers)
{
    return answers->picked_text;
}
CLEAN_AS(func_020ab4d4, TalkAnswers_PickedText)

/* func_020ab4e0 */
char *TalkAnswers_PickedName(TalkAnswers *answers)
{
    return answers->picked_name;
}
CLEAN_AS(func_020ab4e0, TalkAnswers_PickedName)

/* func_020ab4ec */
u8 *TalkAnswers_Picked70(TalkAnswers *answers)
{
    return &answers->picked_70;
}
CLEAN_AS(func_020ab4ec, TalkAnswers_Picked70)

/* func_020ab4f8 */
u32 TalkAnswers_PickedStep(TalkAnswers *answers)
{
    return answers->picked_step;
}
CLEAN_AS(func_020ab4f8, TalkAnswers_PickedStep)

/* func_020ab504: the answer picked, -1 (as unsigned) while none is. */
unsigned int TalkAnswers_Picked(TalkAnswers *answers)
{
    return (unsigned int) answers->picked;
}
CLEAN_AS(func_020ab504, TalkAnswers_Picked)

/* func_020ab510 */
int TalkAnswers_Cancel(TalkAnswers *answers)
{
    return answers->cancel;
}
CLEAN_AS(func_020ab510, TalkAnswers_Cancel)

/* func_020ab51c */
unsigned int TalkAnswers_Count(TalkAnswers *answers)
{
    return answers->count;
}
CLEAN_AS(func_020ab51c, TalkAnswers_Count)

/* func_020ab528: the fifth answer's text. */
u8 *TalkAnswers_FifthText(TalkAnswers *answers)
{
    return (u8 *) func_020ab798(func_020ab550(answers, 4));
}
CLEAN_AS(func_020ab528, TalkAnswers_FifthText)
