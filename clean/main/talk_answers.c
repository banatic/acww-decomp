/* The answers a talk offers (talk_answers.h). */
#include "talk_answers.h"

#include <string.h>

#include "clean.h"
#include "select_bmg.h"
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

/* The byte a cleared answer's message index and unk_70 take (the message files' "none"). */
extern u8 data_021f43ec;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern int func_02064328(char *buffer, const char *format, ...); /* sprintf */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* An answer's constructor and destructor, handed to the array helpers: the game's own. */
extern void *func_020ab804(void *answer);
extern void *func_020ab7e8(void *answer);

/* The path an answer's text is read from: /script/<language>/select/<file>.bmg. */
#define TALK_ANSWERS_PATH_SIZE 0x40

/* func_020ab53c: the first answer's text. */
u8 *TalkAnswers_FirstText(TalkAnswers *answers)
{
    return (u8 *) TalkAnswers_Text(TalkAnswers_Answer(answers, 0));
}
CLEAN_AS(func_020ab53c, TalkAnswers_FirstText)

/* func_020ab550: answer `index`. Nothing checks the index; the address is computed for any. */
TalkAnswer *TalkAnswers_Answer(TalkAnswers *answers, int index)
{
    return (TalkAnswer *) ((uintptr_t) answers + (uintptr_t) index * sizeof(TalkAnswer));
}
CLEAN_AS(func_020ab550, TalkAnswers_Answer)

/* func_020ab558: all five answers cleared, none offered, and B picks none. */
void TalkAnswers_ClearAnswers(TalkAnswers *answers)
{
    for (unsigned int i = 0; i < TALK_ANSWERS_MAX; i++) {
        TalkAnswers_ClearAnswer(&answers->answers[i]);
    }
    answers->count = 0;
    answers->cancel = -1;
}
CLEAN_AS(func_020ab558, TalkAnswers_ClearAnswers)

/* func_020ab58c: no answer picked, and the copy of the pick cleared. */
void TalkAnswers_ClearPick(TalkAnswers *answers)
{
    answers->picked = -1;
    answers->picked_70 = data_021f43ec;
    MI_CpuFill8(answers->picked_name, 0, TALK_ANSWERS_NAME_SIZE);
    TextBase_Clear(answers->picked_text);
    Block020a8248_Clear(&answers->picked_record);
    answers->picked_step = 0;
}
CLEAN_AS(func_020ab58c, TalkAnswers_ClearPick)

/* func_020ab5e4: the pick, then the answers cleared. */
void TalkAnswers_Clear(TalkAnswers *answers)
{
    TalkAnswers_ClearPick(answers);
    TalkAnswers_ClearAnswers(answers);
}
CLEAN_AS(func_020ab5e4, TalkAnswers_Clear)

/* func_020ab5f8: the texts of the answers offered read from their message files. */
void TalkAnswers_LoadTexts(TalkAnswers *answers)
{
    for (int i = 0; i < (int) answers->count; i++) {
        TalkAnswers_LoadAnswerText(&answers->answers[i]);
    }
}
CLEAN_AS(func_020ab5f8, TalkAnswers_LoadTexts)

/* func_020ab628: answer `index` set: its message (the byte at `message`), its message file
 * (entry `file` of TalkAnswers_Style's table), its unk_70 (the byte at `unk_70`), its sound
 * kind and, unless `name` is NULL, its name. Its text is not read here
 * (TalkAnswers_LoadTexts). */
void TalkAnswers_Set(TalkAnswers *answers, int index, const u8 *message, int file, const u8 *unk_70, const char *name,
                     int sound_kind)
{
    TalkAnswer *answer = &answers->answers[index];
    TalkAnswers_SetMessage(answer, message);
    TalkAnswers_SetFile(answer, (int) TalkAnswers_Style((unsigned int) file));
    TalkAnswers_Set70(answer, unk_70);
    TalkAnswers_SetSoundKind(answer, (u32) sound_kind);
    if (name != NULL) {
        TalkAnswers_SetName(answer, name);
    }
}
CLEAN_AS(func_020ab628, TalkAnswers_Set)

/* func_020ab670: everything cleared, then `count` answers offered and B picking `cancel`. */
void TalkAnswers_Reset(TalkAnswers *answers, int count, int cancel)
{
    TalkAnswers_Clear(answers);
    answers->count = (u32) count;
    answers->cancel = cancel;
}
CLEAN_AS(func_020ab670, TalkAnswers_Reset)

/* func_020ab694: the destructor: the pick's record and text, then the five answers (last
 * first). */
TalkAnswers *TalkAnswers_Destruct(TalkAnswers *answers)
{
    Block020a8248_Destruct(&answers->picked_record);
    SelectBmgText_Destruct((SelectBmgText *) answers->picked_text);
    __cxa_vec_cleanup(answers->answers, TALK_ANSWERS_MAX, sizeof(TalkAnswer), (void (*)(void *))(uintptr_t) func_020ab7e8);
    return answers;
}
CLEAN_AS(func_020ab694, TalkAnswers_Destruct)

/* func_020ab6c8: the constructor: the five answers, the pick's text and record, then all
 * cleared. */
TalkAnswers *TalkAnswers_Construct(TalkAnswers *answers)
{
    __cxa_vec_ctor(answers->answers, TALK_ANSWERS_MAX, sizeof(TalkAnswer), (void (*)(void *))(uintptr_t) func_020ab804,
                   (void (*)(void *))(uintptr_t) func_020ab7e8);
    answers->picked_70 = data_021f43ec;
    SelectBmgText_Construct((SelectBmgText *) answers->picked_text);
    Block020a8248_Construct(&answers->picked_record);
    TalkAnswers_Clear(answers);
    return answers;
}
CLEAN_AS(func_020ab6c8, TalkAnswers_Construct)

/* func_020ab71c: the answer's text read from its message file, /script/KOR/select/<file>.bmg
 * (the answer's `style` word is the address of the file's name, "select" or "select2"), and
 * the message's entry kept in its record. */
void TalkAnswers_LoadAnswerText(TalkAnswer *answer)
{
    char path[TALK_ANSWERS_PATH_SIZE];
    const char *language = "KOR";
    func_02064328(path, "/script/%s/select/%s.bmg", language, (const char *) (uintptr_t) answer->style);
    SelectBmg_LoadText((SelectBmgText *) answer->text, path, &answer->unk_00, &answer->record);
}
CLEAN_AS(func_020ab71c, TalkAnswers_LoadAnswerText)

/* func_020ab750 */
void TalkAnswers_SetSoundKind(TalkAnswer *answer, u32 sound_kind)
{
    answer->sound_kind = sound_kind;
}
CLEAN_AS(func_020ab750, TalkAnswers_SetSoundKind)

/* func_020ab758: the name, at most 0x19 characters, always ended. */
void TalkAnswers_SetName(TalkAnswer *answer, const char *name)
{
    answer->name[TALK_ANSWERS_NAME_SIZE - 1] = '\0';
    strncpy(answer->name, name, TALK_ANSWERS_NAME_SIZE - 1);
}
CLEAN_AS(func_020ab758, TalkAnswers_SetName)

/* func_020ab76c: unk_70 from the byte at `value`. */
void TalkAnswers_Set70(TalkAnswer *answer, const u8 *value)
{
    answer->unk_70 = *value;
}
CLEAN_AS(func_020ab76c, TalkAnswers_Set70)

/* func_020ab774: the message file (the address of its name). */
void TalkAnswers_SetFile(TalkAnswer *answer, int file)
{
    answer->style = (u32) file;
}
CLEAN_AS(func_020ab774, TalkAnswers_SetFile)

/* func_020ab778: the message, from the byte at `message`. */
void TalkAnswers_SetMessage(TalkAnswer *answer, const u8 *message)
{
    answer->unk_00 = *message;
}
CLEAN_AS(func_020ab778, TalkAnswers_SetMessage)

/* func_020ab780 */
u32 TalkAnswers_SoundKind(TalkAnswer *answer)
{
    return answer->sound_kind;
}
CLEAN_AS(func_020ab780, TalkAnswers_SoundKind)

/* func_020ab788 */
u8 *TalkAnswers_Weight(TalkAnswer *answer)
{
    return &answer->weight;
}
CLEAN_AS(func_020ab788, TalkAnswers_Weight)

/* func_020ab78c */
Block020a8248 *TalkAnswers_Record(TalkAnswer *answer)
{
    return &answer->record;
}
CLEAN_AS(func_020ab78c, TalkAnswers_Record)

/* func_020ab790 */
char *TalkAnswers_Name(TalkAnswer *answer)
{
    return answer->name;
}
CLEAN_AS(func_020ab790, TalkAnswers_Name)

/* func_020ab794 */
u8 *TalkAnswers_Answer70(TalkAnswer *answer)
{
    return &answer->unk_70;
}
CLEAN_AS(func_020ab794, TalkAnswers_Answer70)

/* func_020ab798 */
TextBase *TalkAnswers_Text(TalkAnswer *answer)
{
    return (TextBase *) answer->text;
}
CLEAN_AS(func_020ab798, TalkAnswers_Text)

/* func_020ab79c: the answer cleared: no message, no file, an empty text, name and record, no
 * weight, the default sound. */
void TalkAnswers_ClearAnswer(TalkAnswer *answer)
{
    answer->unk_00 = data_021f43ec;
    answer->style = 0;
    TextBase_Clear(answer->text);
    Block020a8248_Clear(&answer->record);
    answer->unk_70 = data_021f43ec;
    MI_CpuFill8(answer->name, 0, TALK_ANSWERS_NAME_SIZE);
    answer->weight = 0;
    answer->sound_kind = TALK_ANSWER_SOUND_DEFAULT;
}
CLEAN_AS(func_020ab79c, TalkAnswers_ClearAnswer)

/* func_020ab7e8: an answer's destructor: its record, then its text. */
TalkAnswer *TalkAnswers_DestructAnswer(TalkAnswer *answer)
{
    Block020a8248_Destruct(&answer->record);
    SelectBmgText_Destruct((SelectBmgText *) answer->text);
    return answer;
}
CLEAN_AS(func_020ab7e8, TalkAnswers_DestructAnswer)

/* func_020ab804: an answer's constructor: its text and record built, then cleared. */
TalkAnswer *TalkAnswers_ConstructAnswer(TalkAnswer *answer)
{
    answer->unk_00 = data_021f43ec;
    SelectBmgText_Construct((SelectBmgText *) answer->text);
    Block020a8248_Construct(&answer->record);
    answer->unk_70 = data_021f43ec;
    TalkAnswers_ClearAnswer(answer);
    return answer;
}
CLEAN_AS(func_020ab804, TalkAnswers_ConstructAnswer)
