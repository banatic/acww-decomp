/* The voice of a talk (talk_voice.h). */
#include "talk_voice.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "player_options.h"
#include "scene_sound.h"
#include "sound.h"
#include "talk_object.h"
#include "villager_state.h"
#include "villager_status.h"

static_assert(offsetof(TalkVoice, chars) == 0x08, "voice chars");
static_assert(offsetof(TalkVoice, count) == 0x10, "voice count");
static_assert(offsetof(TalkVoice, unk_1c) == 0x1c, "voice 1c");
static_assert(offsetof(TalkVoice, forced_mode) == 0x20, "voice forced mode");
static_assert(offsetof(TalkVoice, colour) == 0x28, "voice colour");
static_assert(sizeof(TalkVoice) == 0x2c, "voice");

/* The class's vtable: the destructor and the deleting destructor. */
extern const u32 data_020def3c[];
/* "No character" (0). */
extern const u16 data_020cb8f4;
/* The style of the sounds by the player's options' setting (0, 1, 2). */
extern const u8 data_020cce7c[];
/* The kind of the sounds by the villager's state byte 0x18. */
extern const u8 data_020cce88[];

/* A colour of text, and the talk's kind, that change the sound mode. */
#define TALK_VOICE_COLOUR_SWITCH 9
#define TALK_VOICE_COLOUR_MUTE 4
#define TALK_VOICE_KIND_FIXED 3
/* The kinds of talk that take the player's sound setting as it is. */
#define TALK_VOICE_KIND_PLAIN 0
#define TALK_VOICE_KIND_PLAIN2 3
/* The style that plays nothing, and the sound played in place of the characters' while no
 * mode is set. */
#define TALK_VOICE_STYLE_SILENT 2
#define TALK_VOICE_BEEP 0x2c

/* The receiver's vtable slots: the villager talked to (or NULL), and the speaker's kind,
 * which is its sound mode. */
#define TALK_VOICE_SLOT_VILLAGER 0x68
#define TALK_VOICE_SLOT_MODE 0x6c

/* The mode set when it changes and a mode is in use (TalkVoice_FollowColour). */
extern void func_02068b88(TalkVoice *voice, int mode);
/* A sound effect (misnamed: func_020f1fb4 on the sound state). */
extern void RtcSendPxiCommand(int command);

typedef int TalkVoiceSlot(void *receiver);

static int talk_voice_ask_receiver(TalkVoice *voice, u32 slot)
{
    void *receiver = voice->talk->receiver;
    const u8 *vtable = *(const u8 *const *) receiver;
    u32 function = *(const u32 *) (const void *) (vtable + slot);
    return ((TalkVoiceSlot *) (uintptr_t) function)(receiver);
}

/* func_020688dc: nothing. */
void TalkVoice_Nothing(TalkVoice *voice)
{
    (void) voice;
}
CLEAN_AS(func_020688dc, TalkVoice_Nothing)

/* func_020688e0: a text of colour 9 switches mode 0 to mode 4; once it ends, mode 4 goes
 * back to the receiver's mode. */
void TalkVoice_FollowColour(TalkVoice *voice)
{
    int mode = TALK_VOICE_NO_MODE;
    if (voice->mode == 0) {
        if (voice->colour == TALK_VOICE_COLOUR_SWITCH) {
            mode = 4;
        }
    } else if (voice->mode == 4) {
        if (voice->colour != TALK_VOICE_COLOUR_SWITCH) {
            mode = talk_voice_ask_receiver(voice, TALK_VOICE_SLOT_MODE);
        }
    }
    if (mode != TALK_VOICE_NO_MODE) {
        func_02068b88(voice, mode);
    }
}
CLEAN_AS(func_020688e0, TalkVoice_FollowColour)

/* func_02068924: the kind of the sounds: data_020cce88 by the state byte 0x18 of the villager
 * talked to; the table's first without a villager or its state. */
u8 TalkVoice_VillagerKind(TalkVoice *voice)
{
    int index = 0;
    u8 *villager = (u8 *) (uintptr_t) talk_voice_ask_receiver(voice, TALK_VOICE_SLOT_VILLAGER);
    if (villager != NULL) {
        VillagerState *state = VillagerStatus_StateEntry(villager);
        if (state != NULL) {
            index = VillagerState_GetByte18(state);
        }
    }
    return data_020cce88[index];
}
CLEAN_AS(func_02068924, TalkVoice_VillagerKind)

/* func_02068958: the style of the sounds: data_020cce7c by the player's sound setting, where
 * setting 0 counts as 1 for a talk whose kind is neither 0 nor 3 or whose text has colour 4. */
u8 TalkVoice_Style(TalkVoice *voice)
{
    int setting = PlayerOptions_CurrentSetting();
    int kind = voice->kind_override != TALK_VOICE_NO_KIND ? voice->kind_override : voice->kind;
    int index = setting;
    if (kind != TALK_VOICE_KIND_PLAIN && kind != TALK_VOICE_KIND_PLAIN2 && setting == 0) {
        index = 1;
    }
    if (voice->colour == TALK_VOICE_COLOUR_MUTE && setting == 0) {
        index = 1;
    }
    return data_020cce7c[index];
}
CLEAN_AS(func_02068958, TalkVoice_Style)

/* func_0206899c: the sound mode taken back. */
void TalkVoice_Stop(TalkVoice *voice)
{
    if (voice->mode != TALK_VOICE_NO_MODE) {
        SceneSound_Vfunc20();
    }
    voice->mode = TALK_VOICE_NO_MODE;
}
CLEAN_AS(func_0206899c, TalkVoice_Stop)

/* func_020689b4: the sound mode set: the forced one, else (with style 0) 1 for a talk of kind
 * 3 or the receiver's mode; none otherwise. */
void TalkVoice_Start(TalkVoice *voice)
{
    int mode = TALK_VOICE_NO_MODE;
    if (voice->forced_mode != TALK_VOICE_NO_MODE) {
        mode = voice->forced_mode;
    } else if (TalkVoice_Style(voice) == 0) {
        if (voice->kind == TALK_VOICE_KIND_FIXED) {
            mode = 1;
        } else {
            mode = talk_voice_ask_receiver(voice, TALK_VOICE_SLOT_MODE);
        }
    }
    voice->mode = mode;
    if (mode != TALK_VOICE_NO_MODE) {
        SceneSound_SetKeyboardMode(mode);
    }
}
CLEAN_AS(func_020689b4, TalkVoice_Start)

/* func_02068a00 */
void TalkVoice_SetKind(TalkVoice *voice, int kind)
{
    voice->kind = kind;
}
CLEAN_AS(func_02068a00, TalkVoice_SetKind)

/* Characters the speaker does not say: no character, the wide space, the newline, the
 * middle dot, the wide "!" and "?", 0xfe and the wide comma. */
static int talk_voice_is_said(u16 character)
{
    return character != data_020cb8f4 && character != 0x3000 && character != 0x0a && character != 0x30fb &&
           character != 0xff01 && character != 0xff1f && character != 0xfe && character != 0xff0c;
}

/* func_02068a04: each frame while the talk shows its message: the mode follows the text's
 * colour, then (unless no sound is wanted) the characters' sound plays and the talk is told
 * whether the speaker says any of them; a pause stops the mouth.
 * REQUIRES: `count` 0 to 2 (TalkVoice_PushChar keeps it there). */
void TalkVoice_Update(TalkVoice *voice)
{
    TalkVoice_FollowColour(voice);
    TalkVoice_Nothing(voice);
    if (voice->unk_1c == 0 && voice->instant == 0) {
        int style = TalkVoice_Style(voice);
        int kind = TalkVoice_VillagerKind(voice);
        int said = 0;
        if (voice->count >= 1) {
            if (voice->mode == TALK_VOICE_NO_MODE) {
                if (style != TALK_VOICE_STYLE_SILENT) {
                    RtcSendPxiCommand(TALK_VOICE_BEEP);
                }
            } else {
                SoundSys_PlayKeyboardSound(style, kind, voice->chars[0], voice->chars[1]);
            }
        }
        if (voice->colour != TALK_VOICE_COLOUR_MUTE) {
            for (int i = 0; i < voice->count; i++) {
                if (talk_voice_is_said(voice->chars[i])) {
                    said = 1;
                }
            }
        }
        TalkObject_SetVoiced(voice->talk, said);
    }
    if (voice->paused != 0) {
        TalkObject_ClearVoice(voice->talk);
    }
}
CLEAN_AS(func_02068a04, TalkVoice_Update)

/* func_02068ad0: a character shown, kept while there is room for it. */
void TalkVoice_PushChar(TalkVoice *voice, short character)
{
    s32 count = voice->count;
    if (count < TALK_VOICE_CHARS) {
        voice->count = count + 1;
        voice->chars[count] = (u16) character;
    }
}
CLEAN_AS(func_02068ad0, TalkVoice_PushChar)

/* func_02068ae4: the characters cleared (and unk_0c with them when `all`). */
void TalkVoice_Clear(TalkVoice *voice, int all)
{
    u16 none = data_020cb8f4;
    for (int i = 0; i < TALK_VOICE_CHARS; i++) {
        voice->chars[i] = none;
    }
    if (all) {
        voice->unk_0c = none;
    }
    voice->count = 0;
}
CLEAN_AS(func_02068ae4, TalkVoice_Clear)

/* func_02068b0c (vtable slot 1): the destructor, and the object freed. */
TalkVoice *TalkVoice_DestructDelete(TalkVoice *voice)
{
    voice->vtable = data_020def3c;
    Heap_OperatorDeleteB(voice);
    return voice;
}
CLEAN_AS(func_02068b0c, TalkVoice_DestructDelete)

/* func_02068b24 (vtable slot 0): the destructor. */
void TalkVoice_Destruct(TalkVoice *voice)
{
    voice->vtable = data_020def3c;
}
CLEAN_AS(func_02068b24, TalkVoice_Destruct)

/* func_02068b30: the constructor: no kind override, no mode, nothing shown. */
TalkVoice *TalkVoice_Construct(TalkVoice *voice, struct TalkObject *talk)
{
    voice->vtable = data_020def3c;
    voice->talk = talk;
    voice->kind_override = TALK_VOICE_NO_KIND;
    voice->kind = 0;
    voice->unk_1c = 0;
    voice->instant = 0;
    voice->paused = 0;
    voice->forced_mode = TALK_VOICE_NO_MODE;
    voice->mode = TALK_VOICE_NO_MODE;
    voice->colour = 0;
    TalkVoice_Clear(voice, 1);
    return voice;
}
CLEAN_AS(func_02068b30, TalkVoice_Construct)
