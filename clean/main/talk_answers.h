/* The answers a talk offers (0x364 bytes, at 0x31c of a talk; func_0206837c returns them):
 * up to five answers of 0x90 bytes, how many there are, the one B picks, and a copy of the
 * answer picked. The talk's windows (talk_windows.h) show them: the choice window as a list
 * (talk_choice_cursor.h), the slider window as the slider's labels (talk_slider.h), where the
 * level picks one of the first four answers by their weights.
 *
 * func_020ab550 returns an answer, func_020ab558 clears them all, func_020ab58c clears the
 * pick; func_020ab780 to func_020ab798 return an answer's fields (or their addresses). */
#ifndef CLEAN_MAIN_TALK_ANSWERS_H
#define CLEAN_MAIN_TALK_ANSWERS_H

#include "block_020a8248.h"
#include "types.h"

#define TALK_ANSWERS_MAX 5
#define TALK_ANSWERS_NAME_SIZE 0x1a
#define TALK_ANSWERS_TEXT_SIZE 0x5c

/* What a pick plays (TalkAnswer.sound_kind, read by TalkChoiceCursor_PlayAnswerSound). */
#define TALK_ANSWER_SOUND_DEFAULT 0
#define TALK_ANSWER_SOUND_1 1
#define TALK_ANSWER_SOUND_2 2
#define TALK_ANSWER_SOUND_3 3

typedef struct TalkAnswer {
    u8 unk_00;                         /* 0x00: data_021f43ec's byte when cleared */
    u8 pad_01[3];                      /* 0x01 */
    u32 style;                         /* 0x04: one of data_020d1de0's entries (TalkAnswers_Style) */
    u8 text[TALK_ANSWERS_TEXT_SIZE];   /* 0x08: its text (an 8-bit text, text_base.h) */
    Block020a8248 record;              /* 0x64 */
    u8 unk_70;                         /* 0x70: data_021f43ec's byte when cleared */
    char name[TALK_ANSWERS_NAME_SIZE]; /* 0x71: up to 0x19 characters */
    u8 weight;                         /* 0x8b: its share of the slider's 16 steps */
    u32 sound_kind;                    /* 0x8c: TALK_ANSWER_SOUND_* */
} TalkAnswer;

typedef struct TalkAnswers {
    TalkAnswer answers[TALK_ANSWERS_MAX]; /* 0x000 */
    u32 count;                            /* 0x2d0 */
    s32 cancel;                           /* 0x2d4: the answer B picks, or -1 */
    s32 picked;                           /* 0x2d8: or -1 while none is */
    /* A copy of the answer picked. */
    u8 picked_70;                             /* 0x2dc: its unk_70 */
    char picked_name[TALK_ANSWERS_NAME_SIZE]; /* 0x2dd */
    u8 pad_2f7;                               /* 0x2f7 */
    u8 picked_text[TALK_ANSWERS_TEXT_SIZE];   /* 0x2f8 */
    Block020a8248 picked_record;              /* 0x354 */
    u32 picked_step;                          /* 0x360: the slider's step (0 to 15) it was picked at */
} TalkAnswers;

u32 TalkAnswers_Style(unsigned int index);
void TalkAnswers_PickByLevel(TalkAnswers *answers, int level);
void TalkAnswers_Pick(TalkAnswers *answers, int index);
void TalkAnswers_SetCancelToLast(TalkAnswers *answers);
void TalkAnswers_SetCount(TalkAnswers *answers, int count);
Block020a8248 *TalkAnswers_PickedRecord(TalkAnswers *answers);
u8 *TalkAnswers_PickedText(TalkAnswers *answers);
char *TalkAnswers_PickedName(TalkAnswers *answers);
u8 *TalkAnswers_Picked70(TalkAnswers *answers);
u32 TalkAnswers_PickedStep(TalkAnswers *answers);
unsigned int TalkAnswers_Picked(TalkAnswers *answers);
int TalkAnswers_Cancel(TalkAnswers *answers);
unsigned int TalkAnswers_Count(TalkAnswers *answers);
u8 *TalkAnswers_FifthText(TalkAnswers *answers);

#endif
