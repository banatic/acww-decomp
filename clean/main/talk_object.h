/* A talk (0x1e9c bytes): the message window of the field, through which a receiver (a scene,
 * an object, a menu: Base_02066994, at `receiver`) shows the messages of a message file to
 * the player and takes the player's answers. There are two, at the array data_021cda88 points
 * to (TalkObject_AllocAll and TalkObject_FreeAll, while the talk process lives,
 * talk_process.h); TalkObject_Get gives one.
 *
 * Each frame (TalkObject_Update) a talk runs the step of its state through a table of member
 * functions, enters the state asked for in `next_state` (func_02067108), shakes its window when
 * asked to (TalkObject_Shake), and runs its message window and its choice windows (the
 * states' steps and entries: talk_flow.h). Its parts:
 *
 * - the message window at 0x1c (func_02069128 builds it), with a spinner at its 0x50
 *   (talk_spinner.h) and its place on screen at its 0x74 and 0x78;
 * - the choice windows at 0xb4 (talk_windows.h) and the answers at 0x31c (talk_answers.h);
 * - the label box of the speaker's name at 0x680 (func_020675e0 makes it);
 * - the page at 0x684 (talk_page.h) and the tag walker at 0x13b8 (talk_tags.h);
 * - eleven message parts and four values a message's tags put in (TalkObject_LoadPart,
 *   TalkObject_SetPart, TalkObject_SetValue);
 * - the voice at 0x1a2c (talk_voice.h);
 * - the date and time the talk began (func_02067c20) and their texts, and the texts loaded
 *   from the villager talked to or about (talk_tags.h);
 * - the message to show (its file `name` and its number `message`, TalkObject_SetMessage). */
#ifndef CLEAN_MAIN_TALK_OBJECT_H
#define CLEAN_MAIN_TALK_OBJECT_H

#include "block_020a8248.h"
#include "label_box.h"
#include "mail_text.h"
#include "message_receiver.h"
#include "message_texts.h"
#include "message_walker.h"
#include "player_id.h"
#include "small_texts.h"
#include "talk_answers.h"
#include "talk_page.h"
#include "talk_receiver.h"
#include "talk_tags.h"
#include "talk_voice.h"
#include "talk_windows.h"
#include "town_name.h"
#include "types.h"
#include "villager_memory_text.h"

/* The talks at data_021cda88. */
#define TALK_OBJECT_COUNT 2

/* TalkObject.state: the step run each frame (TalkObject_Update). */
enum TalkObjectState {
    TALK_OBJECT_CLOSED = 0,
    TALK_OBJECT_OPENING = 1, /* the window slides in */
    TALK_OBJECT_WAITING = 2, /* the walk of the message stopped: waiting for the player */
    TALK_OBJECT_WRITING = 3, /* the message is written out and voiced; the player can hurry it */
    TALK_OBJECT_CLOSING = 4, /* the window slides away */
    TALK_OBJECT_GONE = 5,
    TALK_OBJECT_NO_STATE = 6 /* TalkObject.next_state when no state is asked for */
};

#define TALK_OBJECT_PARTS 11
#define TALK_OBJECT_VALUES 4
#define TALK_OBJECT_NAME_SIZE 26

typedef struct TalkObject {
    s32 index;        /* 0x0000: its place at data_021cda88 */
    s32 state;        /* 0x0004: enum TalkObjectState */
    s32 next_state;   /* 0x0008: the state entered on the next frame (func_02067108) */
    s32 slide;        /* 0x000c: the step of the window's slide in or away */
    s32 unk_10;       /* 0x0010: set by func_020676c4 */
    s32 mode;         /* 0x0014: set by the scene commands; 4 keeps the talk for more messages */
    u8 choices_asked; /* 0x0018: the choices open when the walk stops (TalkObject_OpenChoices) */
    u8 pad_19[3];
    u8 window[0x80];   /* 0x001c: the message window */
    s32 window_offset; /* 0x009c: its offset in the slide, the height it is shaken about */
    u16 shake_angle;   /* 0x00a0: a quarter turn more each frame of the shake */
    u16 pad_a2;
    s32 shake_amplitude;                    /* 0x00a4: 20.12 fixed point; the shake ends at 0 */
    s32 shake_fall;                         /* 0x00a8: taken off the amplitude each frame */
    s32 shake_scale_x;                      /* 0x00ac */
    s32 shake_scale_y;                      /* 0x00b0 */
    TalkWindows choice_windows;             /* 0x00b4 */
    TalkAnswers answers;                    /* 0x031c */
    LabelBox *name_box;                     /* 0x0680: the speaker's name, or NULL */
    TalkPage page;                          /* 0x0684 */
    u8 unk_b14[0x8a4];                      /* 0x0b14: built by func_0206d688 */
    TalkTagsWalker walker;                  /* 0x13b8 */
    MessageWalkRun run;                     /* 0x149c */
    TalkReceiver *receiver;                 /* 0x14a8: the receiver shown, or NULL */
    Block020a8248 unk_14ac;                 /* 0x14ac */
    MessagePart parts[TALK_OBJECT_PARTS];   /* 0x14b8 */
    MessagePart values[TALK_OBJECT_VALUES]; /* 0x18ac */
    s32 value_kinds[TALK_OBJECT_VALUES];    /* 0x1a1c */
    TalkVoice voice;                        /* 0x1a2c */
    MailTextParticles particles;            /* 0x1a58 */
    s32 year;                               /* 0x1a64: the date and time the talk began */
    u8 day;                                 /* 0x1a68 */
    u8 month;                               /* 0x1a69 */
    u8 minute;                              /* 0x1a6a */
    u8 hour;                                /* 0x1a6b */
    s32 weekday;                            /* 0x1a6c */
    u32 second;                             /* 0x1a70 */
    s32 part_of_day;                        /* 0x1a74 */
    MessageText46 year_text;                /* 0x1a78 */
    MessagePart month_text;                 /* 0x1ab8 */
    MessageText46 day_text;                 /* 0x1b14 */
    MessagePart weekday_text;               /* 0x1b54 */
    MessageText46 hour_text;                /* 0x1bb0 */
    MessageText46 minute_text;              /* 0x1bf0 */
    MessageText46 second_text;              /* 0x1c30 */
    Label10Text unk_1c70;                   /* 0x1c70 */
    TownNameText town_name;                 /* 0x1c8c */
    PlayerIdText unk_1cac;                  /* 0x1cac */
    PlayerIdText liked_npc;                 /* 0x1ccc */
    PlayerIdText disliked_npc;              /* 0x1cec */
    PlayerIdText random_npc;                /* 0x1d0c */
    PlayerIdText other_player;              /* 0x1d2c */
    MessagePart boom;                       /* 0x1d4c */
    MessagePart impression;                 /* 0x1da8 */
    PlayerIdText nickname;                  /* 0x1e04 */
    Label22Text praise;                     /* 0x1e24 */
    VillagerMemoryLabel memory;             /* 0x1e4c */
    u8 unk_1e74;                            /* 0x1e74 */
    u8 unk_1e75;                            /* 0x1e75 */
    u8 other_colour;                        /* 0x1e76 */
    u8 message;                             /* 0x1e77: the number of the message to show */
    char name[TALK_OBJECT_NAME_SIZE];       /* 0x1e78: its file */
    u8 go_on;                               /* 0x1e92: the talk goes on with `message` */
    u8 held;                                /* 0x1e93: a scene command holds the talk */
    u8 unk_1e94;                            /* 0x1e94 */
    u8 unk_1e95;                            /* 0x1e95 */
    u8 unk_1e96;                            /* 0x1e96 */
    u8 voiced;                              /* 0x1e97: the speaker says the characters shown (the mouth moves) */
    u8 silent;                              /* 0x1e98: no voice, no input and the music kept as it is */
    u8 unk_1e99;                            /* 0x1e99 */
    u8 quiet;                               /* 0x1e9a: no sounds of the window */
    u8 pad_1e9b;
} TalkObject;

void TalkObject_Shake(TalkObject *talk);
int TalkObject_HurryPressed(TalkObject *talk);
int TalkObject_AdvancePressed(TalkObject *talk);
int TalkObject_SwitchInputPressed(TalkObject *talk);
void TalkObject_ApplyInputMode(TalkObject *talk);
void TalkObject_TakeInputMode(TalkObject *talk);
void TalkObject_ColourNamePlate(TalkObject *talk);
void TalkObject_StartShake(TalkObject *talk, s32 amplitude, s32 fall, s32 scale_x, s32 scale_y);
/* The texts of the date and time the talk began, set and returned (MessageText46 or
 * MessagePart). */
void *TalkObject_SecondText(TalkObject *talk);
void *TalkObject_MinuteText(TalkObject *talk);
void *TalkObject_HourText(TalkObject *talk);
void *TalkObject_WeekdayText(TalkObject *talk);
void *TalkObject_DayText(TalkObject *talk);
void *TalkObject_MonthText(TalkObject *talk);
void *TalkObject_YearText(TalkObject *talk);
void TalkObject_ClearVoice(TalkObject *talk);
void TalkObject_SetVoiced(TalkObject *talk, int voiced);
void TalkObject_PushVoiceChar(TalkObject *talk, int character);
int TalkObject_OptionFlagOff(void);
void TalkObject_Draw(TalkObject *talk);
void TalkObject_Update(TalkObject *talk);
void TalkObject_DrawAll(void);
void TalkObject_UpdateAll(void);
void TalkObject_FreeAll(void);
void TalkObject_AllocAll(void);
TalkObject *TalkObject_Get(int index);
void TalkObject_SetQuiet(TalkObject *talk);
void TalkObject_SetUnk1e99(TalkObject *talk);
void TalkObject_SetSilent(TalkObject *talk);
void TalkObject_DetachReceiver(TalkObject *talk);
void TalkObject_AttachReceiver(TalkObject *talk, TalkReceiver *receiver);
void TalkObject_StopSpinner(TalkObject *talk);
void TalkObject_StartSpinner(TalkObject *talk, int sound);
u8 TalkObject_Voiced(TalkObject *talk);
TalkAnswers *TalkObject_Answers(TalkObject *talk);
void TalkObject_OpenChoices(TalkObject *talk, int later);
void TalkObject_SetValue(TalkObject *talk, int index, TextBase *text, int kind);
int TalkObject_LoadPart(TalkObject *talk, int index, const u8 *message, unsigned int name);
void TalkObject_SetPart(TalkObject *talk, int index, TextBase *text);
void TalkObject_StopGoingOn(TalkObject *talk);
void TalkObject_GoOn(TalkObject *talk);
void TalkObject_Release(TalkObject *talk);
void TalkObject_Hold(TalkObject *talk);
void TalkObject_SetMessage(TalkObject *talk, const u8 *message, const char *name);
int TalkObject_SetMessageIfNone(TalkObject *talk, const u8 *message, const char *name);
TalkObject *TalkObject_Destruct(TalkObject *talk);
TalkObject *TalkObject_Construct(TalkObject *talk);

void TalkObject_StartMessage(TalkObject *talk);
void TalkObject_StartGivenMessage(TalkObject *talk);
void TalkObject_LoadMessage(TalkObject *talk);
const char *TalkObject_FileSubfolder(TalkObject *talk, const char *name);
const char *TalkObject_FileFolder(TalkObject *talk, const char *name);
char *TalkObject_MessagePath(TalkObject *talk, const char *name, const char *folder);
void TalkObject_RunAnswerText(TalkObject *talk);
void TalkObject_BeginMessage(TalkObject *talk);
void TalkObject_PlayMessageSound(TalkObject *talk);
void TalkObject_TellAnswer(TalkObject *talk);
void TalkObject_TellMessageEnded(TalkObject *talk);
void TalkObject_TellMessageBegun(TalkObject *talk);
void TalkObject_FreeNameBox(TalkObject *talk);
void TalkObject_MakeNameBox(TalkObject *talk);
void TalkObject_ChangeFondness(TalkObject *talk, int change);
/* The countdown at word 0x10 (unk_10): while the talk waits, it goes on by itself when the
 * countdown reaches 0. */
int TalkObject_AutoAdvanceDue(TalkObject *talk);
void TalkObject_SetAutoAdvance(TalkObject *talk, int frames);
void TalkObject_ClearAutoAdvance(TalkObject *talk);
/* The texts loaded from the villager talked to (or about), and cleared. */
int TalkObject_LoadMemory(TalkObject *talk);
void TalkObject_ClearMemory(TalkObject *talk);
int TalkObject_LoadPraise(TalkObject *talk);
void TalkObject_ClearPraise(TalkObject *talk);
int TalkObject_LoadNickname(TalkObject *talk);
void TalkObject_ClearNickname(TalkObject *talk);
int TalkObject_LoadImpression(TalkObject *talk);
void TalkObject_ClearImpression(TalkObject *talk);
int TalkObject_LoadBoom(TalkObject *talk);
void TalkObject_ClearBoom(TalkObject *talk);
int TalkObject_LoadOtherPlayer(TalkObject *talk);
void TalkObject_ClearOtherPlayer(TalkObject *talk);
int TalkObject_LoadRandomNpc(TalkObject *talk);
void TalkObject_ClearRandomNpc(TalkObject *talk);
int TalkObject_LoadDislikedNpc(TalkObject *talk);
void TalkObject_ClearDislikedNpc(TalkObject *talk);
int TalkObject_LoadLikedNpc(TalkObject *talk);
void TalkObject_ClearLikedNpc(TalkObject *talk);
int TalkObject_LoadPlayerName(TalkObject *talk);
void TalkObject_ClearPlayerName(TalkObject *talk);
int TalkObject_LoadTownName(TalkObject *talk);
void TalkObject_ClearTownName(TalkObject *talk);
int TalkObject_LoadCatchphrase(TalkObject *talk);
void TalkObject_ClearCatchphrase(TalkObject *talk);
void TalkObject_ClearValues(TalkObject *talk);
void TalkObject_ClearParts(TalkObject *talk);
void TalkObject_NoteTime(TalkObject *talk);

#endif
