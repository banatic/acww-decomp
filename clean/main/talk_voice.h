/* The voice of a talk (class data_020def3c, 0x2c bytes, at 0x1a2c of a talk, talk_object.h):
 * the sounds that go with the characters of a talk's message as they are shown, and whether
 * the speaker's mouth moves.
 *
 * The talk's walker hands it each character it shows (TalkObject_PushVoiceChar), up to two a
 * frame. While the talk shows its message, each frame (TalkVoice_Update) plays the sound of
 * those characters (SoundSys_PlayKeyboardSound with a style from the player's options and a
 * kind from the villager talked to), or sound 0x2c in place of it while no sound mode is set,
 * and tells the talk whether any of them is one the speaker says (its byte 0x1e97, which the
 * scenes read to move the speaker's mouth); punctuation, spaces and newlines are not.
 *
 * The sound mode (`mode`) is set when the talk's window has opened (TalkVoice_Start) and
 * taken back when it closes (TalkVoice_Stop): `forced_mode` when set, else 1 for a talk of
 * kind 3, else the speaker's kind (the receiver's vtable slot 0x6c), and only when the player's options
 * let the speaker be heard. A text of colour 9 switches mode 0 to mode 4 while it lasts. */
#ifndef CLEAN_MAIN_TALK_VOICE_H
#define CLEAN_MAIN_TALK_VOICE_H

#include "types.h"

struct TalkObject;

/* TalkVoice.mode, forced_mode and kind_override when they hold nothing. */
#define TALK_VOICE_NO_MODE 5
#define TALK_VOICE_NO_KIND 7

/* The characters it keeps from one frame to the next. */
#define TALK_VOICE_CHARS 2

typedef struct TalkVoice {
    const u32 *vtable;           /* 0x00: data_020def3c */
    struct TalkObject *talk;     /* 0x04: the talk it belongs to */
    u16 chars[TALK_VOICE_CHARS]; /* 0x08: the characters shown since the last frame */
    u16 unk_0c;                  /* 0x0c: cleared with the characters when asked to */
    u16 pad_0e;
    s32 count;         /* 0x10: of `chars` */
    s32 kind_override; /* 0x14: TALK_VOICE_NO_KIND, or the kind used in place of `kind` */
    s32 kind;          /* 0x18: the talk's kind (TalkVoice_SetKind) */
    u8 unk_1c;         /* 0x1c: set by func_0206741c; no sound while set */
    u8 instant;        /* 0x1d: the text is shown whole at once (tag 1/2); no sound */
    u8 paused;         /* 0x1e: a pause of the text (tag 1/0); the mouth stops */
    u8 pad_1f;
    s32 forced_mode; /* 0x20: TALK_VOICE_NO_MODE, or the mode TalkVoice_Start sets */
    s32 mode;        /* 0x24: the sound mode in use, or TALK_VOICE_NO_MODE */
    s32 colour;      /* 0x28: the colour of the text shown (tag 0xff/0) */
} TalkVoice;

void TalkVoice_Nothing(TalkVoice *voice);
void TalkVoice_FollowColour(TalkVoice *voice);
u8 TalkVoice_VillagerKind(TalkVoice *voice);
u8 TalkVoice_Style(TalkVoice *voice);
void TalkVoice_Stop(TalkVoice *voice);
void TalkVoice_Start(TalkVoice *voice);
void TalkVoice_SetKind(TalkVoice *voice, int kind);
void TalkVoice_Update(TalkVoice *voice);
void TalkVoice_PushChar(TalkVoice *voice, short character);
void TalkVoice_Clear(TalkVoice *voice, int all);
TalkVoice *TalkVoice_DestructDelete(TalkVoice *voice);
void TalkVoice_Destruct(TalkVoice *voice);
TalkVoice *TalkVoice_Construct(TalkVoice *voice, struct TalkObject *talk);

#endif
