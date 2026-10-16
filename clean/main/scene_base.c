/* The scene base class (vtable 0x020d8bd4, scene_base.h).
 *
 * REQUIRES: the scene and its speakers at word-aligned addresses, as every object of the game
 * is (the ARM9 reads an aligned word at a misaligned address). */
#include "scene_base.h"

#include "actor.h"
#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "npc_id.h"
#include "scene_command.h"

static_assert(offsetof(SceneBase, talk) == 0x40, "SceneBase layout");
static_assert(offsetof(SceneBase, motion_arg) == 0x48, "SceneBase layout");
static_assert(offsetof(SceneBase, speakers) == 0x4c, "SceneBase layout");
static_assert(offsetof(SceneBase, focus) == 0x54, "SceneBase layout");
static_assert(offsetof(SceneBase, speaking) == 0x55, "SceneBase layout");
static_assert(offsetof(SceneBase, talk_style) == 0x5c, "SceneBase layout");
static_assert(offsetof(SceneBase, holding) == 0x60, "SceneBase layout");
static_assert(offsetof(SceneBase, command) == 0x64, "SceneBase layout");
static_assert(offsetof(SceneBase, item) == 0x7e, "SceneBase layout");

/* The class's vtable. */
extern const u8 data_020d8bd4[];

/* The scene's vtable slots called here. */
#define SCENE_BASE_SLOT_RESET 0x08       /* SceneBase_Reset by default */
#define SCENE_BASE_SLOT_TALK_STYLE 0x38  /* SceneBase_FocusTalkStyle by default */
#define SCENE_BASE_SLOT_LOOK_FIRST 0x50  /* SceneBase_LookAtFirst by default */
#define SCENE_BASE_SLOT_LOOK_SECOND 0x58 /* SceneBase_LookAtSecond by default */
#define SCENE_BASE_SLOT_BEFORE_STEP 0x80 /* SceneBase_Nothing80 by default */

/* A speaker's parts (a scene object of class 0x020d8c64) used here: its position, the code of
 * the person it is (func_020823e8 classes it), its look request (func_0201ad18), its motion
 * (scene_action.h), the scene it talks in (func_0201c274) and its vtable slot 0x8c (nothing
 * in class 0x020d8c64, func_0201c248). */
#define SCENE_BASE_SPEAKER_POSITION 0x5c
#define SCENE_BASE_SPEAKER_CODE 0xea
#define SCENE_BASE_SPEAKER_LOOK 0x3b0
#define SCENE_BASE_SPEAKER_MOTION 0x564
#define SCENE_BASE_SLOT_SPEAKER_JOINED 0x8c

/* What func_0201ad18 looks at: an object (kind 2) or a field actor by number (kind 4). */
#define SCENE_BASE_LOOK_OBJECT 2
#define SCENE_BASE_LOOK_ACTOR 4

/* The motion that turns an object to an angle, the priority it is set with, and the motion a
 * talking speaker has (scene_action.h). */
#define SCENE_BASE_MOTION_TURN 3
#define SCENE_BASE_MOTION_TURN_PRIORITY 2
#define SCENE_BASE_MOTION_TALK 8
#define SCENE_BASE_MOTION_TALK_PRIORITY 2

/* The scene in which the player's field actor is numbered by data_021f3c1c, and the field
 * actor of the player (func_02096718(4), as in pockets_screen.c). */
#define SCENE_BASE_SCENE_2F 0x2f
#define SCENE_BASE_PLAYER_ACTOR 4
/* The player's field actor's angle func_02095518's turn of the head is relative to. */
#define SCENE_BASE_PLAYER_ANGLE 0x8e

/* What SceneBase_SpeakingKind answers without a speaker. */
#define SCENE_BASE_NO_KIND 5

/* The command the scene starts with (scene_command.h), and the item code for none. */
#define SCENE_BASE_NO_COMMAND 12
#define SCENE_BASE_NO_ITEM 0xfff1

/* The message of "st_general" PutCount appends, and the kinds of value func_020683b4 takes. */
#define SCENE_BASE_COUNT_UNIT_MESSAGE 0x1c
#define SCENE_BASE_TEXT_KIND_PLAIN 7
#define SCENE_BASE_TEXT_KIND_LABEL 0

/* The last word every motion is set with, and what looks start from (func_0201ad18's
 * offset). */
extern u16 data_020c80f8;
extern Vec3 data_021fbee8;
/* "st_general", the name of a message archive. */
extern const char data_020d8d0c[];

extern unsigned int func_0201c274(void *object);
extern int func_0201c314(void *from, void *to);
extern void *func_0201c2c8(void *object, void *target);
extern int func_02019d0c(void *motion, int kind, int priority, int a, int b, s16 c, s16 angle, int d, int e, u16 f, u16 g);
extern int func_02019e00(void *motion);
extern int func_02019c90(void *motion, int priority, int style, int g);
extern void func_0201ad18(void *look, u8 kind, int priority, int object, const Vec3 *offset, int actor, int a, u8 b);
extern u8 func_020b65c4(void);
extern u8 func_020a13d0(void);
extern int func_020952ec(void);
extern int func_02095794(int actor);
extern int func_02095518(int a, int angle, int actor);
extern int func_02095a8c(int angle, int actor);
extern void func_02095eec(int on, int actor);
extern int func_02096190(int actor);
extern int func_020823e8(void *code);
extern unsigned int func_0206837c(void *talk);

/* The talk's slots, and the text objects put into them. */
extern int func_020683e4(void *talk, int slot, const void *bytes, unsigned int size);
extern void func_020683b4(void *talk, int slot, void *text, int kind);
extern void func_02068404(void *talk, int slot, void *text);
extern void *func_02062f90(void *text, const void *item);
extern void *func_02062f4c(void *text);
extern void *func_02094fd4(void *text);
extern void *func_02094fbc(void *text);
extern void *func_02095074(void *from, void *text);
extern void *func_020641c8(void *text);
extern void func_02064210(unsigned int from, void *text);
extern void *func_020641b0(void *text);
extern void *func_020a8228(void *text);
extern void *func_020a8210(void *text);
extern int func_020b44a4(void *text, int value);
extern int func_020b44bc(void *text, void *value);
extern void *func_020b5630(void *text);
extern void *func_020b5618(void *text);
extern int func_020b4508(void *text, int value, int format);
extern int func_020b45d0(void *text, int value, int format, int a, int b, u8 c);
extern int func_020b4a20(void *text, u8 *message, const char *archive);
extern int func_020a89dc(void *text, void *other);

/* The message receiver (Base_02066994): its constructor, destructor and slot 0x08. */
extern void *func_02066a30(void *receiver);
extern void *func_02066994(void *receiver);
extern void _ZN13Base_0206699417vfunc_02066994_08Ev(void *receiver);

/* The text objects, as stack space for the game's constructors. */
typedef struct SceneBaseText {
    u32 words[0x20 / 4];
} SceneBaseText;
typedef struct SceneBaseItemText {
    u32 words[0x28 / 4];
} SceneBaseItemText;
typedef struct SceneBaseNumberText {
    u32 words[0x44 / 4];
} SceneBaseNumberText;
typedef struct SceneBaseLabel {
    u32 words[0x60 / 4];
} SceneBaseLabel;

static u32 scene_base_slot(const void *object, u32 slot)
{
    const u8 *vtable = *(const u8 *const *) object;
    return *(const u32 *) (vtable + slot);
}

static void scene_base_call(void *object, u32 slot)
{
    typedef void (*SceneBaseMethod)(void *object);
    ((SceneBaseMethod) (uintptr_t) scene_base_slot(object, slot))(object);
}

static u8 *scene_base_speaker(SceneBase *scene, int number)
{
    return (u8 *) (uintptr_t) SceneBase_Speaker(scene, number);
}

/* A speaker turns to face `target`: the scene's slot `look_slot` (the focus looks at the
 * target), the speaker's own scene told the talking style 0, then the speaker's motion of
 * kind 3 to the angle from it to the target. */
static void scene_base_speaker_faces(SceneBase *scene, u8 *speaker, u8 *target, u32 look_slot)
{
    typedef int (*SceneBaseTalkStyle)(void *scene, int style);

    unsigned int own_scene = func_0201c274(speaker);
    int angle = func_0201c314(speaker, target);
    scene_base_call(scene, look_slot);
    if (own_scene != 0) {
        void *own = (void *) (uintptr_t) own_scene;
        ((SceneBaseTalkStyle) (uintptr_t) scene_base_slot(own, SCENE_BASE_SLOT_TALK_STYLE))(own, 0);
    }
    func_02019d0c(speaker + SCENE_BASE_SPEAKER_MOTION, SCENE_BASE_MOTION_TURN, SCENE_BASE_MOTION_TURN_PRIORITY, 0, 0, 0,
                  (s16) angle, 0, 0, data_020c80f8, 0);
}

/* func_02015a1c (slot 0x5c): the focus turns to face the second speaker: the first speaker
 * (scene_base_speaker_faces) or the player (SceneBase_PlayerFaces). Nothing without a second
 * speaker, or with the second as the focus. */
void SceneBase_FaceSecond(SceneBase *scene)
{
    u8 *second = scene_base_speaker(scene, 1);
    if (second == NULL) {
        return;
    }
    switch (scene->focus) {
        case SCENE_BASE_FOCUS_FIRST: {
            u8 *first = scene_base_speaker(scene, scene->focus);
            if (first != NULL) {
                scene_base_speaker_faces(scene, first, second, SCENE_BASE_SLOT_LOOK_SECOND);
            }
            break;
        }
        case SCENE_BASE_FOCUS_PLAYER:
            SceneBase_PlayerFaces(scene, second);
            break;
    }
}
CLEAN_AS(func_02015a1c, SceneBase_FaceSecond)

/* func_02015aac (slot 0x58): the focus looks at the second speaker: the first speaker by its
 * look request, the player by SceneBase_PlayerLooksAt. */
void SceneBase_LookAtSecond(SceneBase *scene)
{
    u8 *second = scene_base_speaker(scene, 1);
    if (second == NULL) {
        return;
    }
    switch (scene->focus) {
        case SCENE_BASE_FOCUS_FIRST: {
            u8 *first = scene_base_speaker(scene, scene->focus);
            if (first != NULL) {
                func_0201ad18(first + SCENE_BASE_SPEAKER_LOOK, SCENE_BASE_LOOK_OBJECT, 0, (int) (uintptr_t) second,
                              &data_021fbee8, 4, 0, 0);
            }
            break;
        }
        case SCENE_BASE_FOCUS_PLAYER:
            SceneBase_PlayerLooksAt(scene, second);
            break;
    }
}
CLEAN_AS(func_02015aac, SceneBase_LookAtSecond)

/* func_02015b0c (slot 0x54): as SceneBase_FaceSecond, toward the first speaker: the second
 * speaker or the player turns. */
void SceneBase_FaceFirst(SceneBase *scene)
{
    u8 *first = scene_base_speaker(scene, 0);
    if (first == NULL) {
        return;
    }
    switch (scene->focus) {
        case SCENE_BASE_FOCUS_SECOND: {
            u8 *second = scene_base_speaker(scene, scene->focus);
            if (second != NULL) {
                scene_base_speaker_faces(scene, second, first, SCENE_BASE_SLOT_LOOK_FIRST);
            }
            break;
        }
        case SCENE_BASE_FOCUS_PLAYER:
            SceneBase_PlayerFaces(scene, first);
            break;
    }
}
CLEAN_AS(func_02015b0c, SceneBase_FaceFirst)

/* func_02015b9c (slot 0x50): as SceneBase_LookAtSecond, at the first speaker. */
void SceneBase_LookAtFirst(SceneBase *scene)
{
    u8 *first = scene_base_speaker(scene, 0);
    if (first == NULL) {
        return;
    }
    switch (scene->focus) {
        case SCENE_BASE_FOCUS_SECOND: {
            u8 *second = scene_base_speaker(scene, scene->focus);
            if (second != NULL) {
                func_0201ad18(second + SCENE_BASE_SPEAKER_LOOK, SCENE_BASE_LOOK_OBJECT, 0, (int) (uintptr_t) first,
                              &data_021fbee8, 4, 0, 0);
            }
            break;
        }
        case SCENE_BASE_FOCUS_PLAYER:
            SceneBase_PlayerLooksAt(scene, first);
            break;
    }
}
CLEAN_AS(func_02015b9c, SceneBase_LookAtFirst)

/* func_02015bfc: the player turns to face `speaker`: its head straight (func_02095518 with 0),
 * its body to the angle from its position (func_02095794) to the speaker's (func_02095a8c),
 * then func_02095eec(1). Nothing when the player's field actor is missing. */
void SceneBase_PlayerFaces(SceneBase *scene, u8 *speaker)
{
    (void) scene;
    int actor = SceneBase_PlayerActorId();
    int position = func_02095794(actor);
    if (position != 0) {
        int angle = Vec_YawTo((const Vec3 *) (uintptr_t) position, (const Vec3 *) (speaker + SCENE_BASE_SPEAKER_POSITION));
        func_02095518(0, 0, actor);
        func_02095a8c(angle, actor);
        func_02095eec(1, actor);
    }
}
CLEAN_AS(func_02015bfc, SceneBase_PlayerFaces)

/* func_02015c3c: the player looks at `speaker`: its head turns (func_02095518) by the angle
 * from its position to the speaker's, less its own angle (the half-word at 0x8e of the
 * player's field actor, func_02096190(4)), cut to 16 bits. The answer is func_02095518's, or 0
 * when the player's field actor is missing.
 *
 * REQUIRES: func_02096190(4) gives an object whenever func_02095794 does (the ROM would read
 * near address 0 otherwise). */
int SceneBase_PlayerLooksAt(SceneBase *scene, u8 *speaker)
{
    (void) scene;
    int actor = SceneBase_PlayerActorId();
    int position = func_02095794(actor);
    if (position == 0) {
        return 0;
    }
    int angle = Vec_YawTo((const Vec3 *) (uintptr_t) position, (const Vec3 *) (speaker + SCENE_BASE_SPEAKER_POSITION));
    const u8 *player = (const u8 *) (uintptr_t) func_02096190(SCENE_BASE_PLAYER_ACTOR);
    s16 own = *(const s16 *) (player + SCENE_BASE_PLAYER_ANGLE);
    return func_02095518(0, (s16) (angle - own), actor);
}
CLEAN_AS(func_02015c3c, SceneBase_PlayerLooksAt)

/* func_02015c7c (slot 0x4c): the focus speaker turns to face the player: its own scene told
 * the talking style 0, a look at the player's field actor, then the motion of kind 3 to the
 * angle func_0201c2c8 gives toward the player. */
void SceneBase_FacePlayer(SceneBase *scene)
{
    typedef int (*SceneBaseTalkStyle)(void *scene, int style);

    u8 *speaker = scene_base_speaker(scene, scene->focus);
    if (speaker == NULL) {
        return;
    }
    unsigned int own_scene = func_0201c274(speaker);
    int actor = SceneBase_PlayerActorId();
    void *angle = func_0201c2c8(speaker, (void *) (uintptr_t) actor);
    if (own_scene != 0) {
        void *own = (void *) (uintptr_t) own_scene;
        ((SceneBaseTalkStyle) (uintptr_t) scene_base_slot(own, SCENE_BASE_SLOT_TALK_STYLE))(own, 0);
    }
    func_0201ad18(speaker + SCENE_BASE_SPEAKER_LOOK, SCENE_BASE_LOOK_ACTOR, 0, 0, &data_021fbee8, actor, 0, 0);
    func_02019d0c(speaker + SCENE_BASE_SPEAKER_MOTION, SCENE_BASE_MOTION_TURN, SCENE_BASE_MOTION_TURN_PRIORITY, 0, 0, 0,
                  (s16) (uintptr_t) angle, 0, 0, data_020c80f8, 0);
}
CLEAN_AS(func_02015c7c, SceneBase_FacePlayer)

/* func_02015d04 (slot 0x48): the focus speaker looks at the player's field actor. */
void SceneBase_LookAtPlayer(SceneBase *scene)
{
    u8 *speaker = scene_base_speaker(scene, scene->focus);
    if (speaker != NULL) {
        int actor = SceneBase_PlayerActorId();
        func_0201ad18(speaker + SCENE_BASE_SPEAKER_LOOK, SCENE_BASE_LOOK_ACTOR, 0, 0, &data_021fbee8, actor, 0, 0);
    }
}
CLEAN_AS(func_02015d04, SceneBase_LookAtPlayer)

/* func_02015d44: the number of the player's field actor: in scene 0x2f the byte
 * data_021f3c1c (func_020a13d0), elsewhere func_020952ec. */
int SceneBase_PlayerActorId(void)
{
    if (func_020b65c4() == SCENE_BASE_SCENE_2F) {
        return func_020a13d0();
    }
    return func_020952ec();
}
CLEAN_AS(func_02015d44, SceneBase_PlayerActorId)

/* func_02015d60: the number of the speaker whose turn it is. */
u8 SceneBase_Speaking(const SceneBase *scene)
{
    return scene->speaking;
}
CLEAN_AS(func_02015d60, SceneBase_Speaking)

/* func_02015d68: the speaker whose turn it is, or 0. */
int SceneBase_SpeakingSpeaker(SceneBase *scene)
{
    return (int) SceneBase_SpeakerOf(scene, scene->speaking);
}
CLEAN_AS(func_02015d68, SceneBase_SpeakingSpeaker)

/* func_02015d78: speaker `number` (0 or 1), or 0 for another number. */
unsigned int SceneBase_SpeakerOf(SceneBase *scene, int number)
{
    if (number == 0 || number == 1) {
        return (unsigned int) (uintptr_t) scene->speakers[number];
    }
    return 0;
}
CLEAN_AS(func_02015d78, SceneBase_SpeakerOf)

/* func_02015d90: the focus speaker, or 0 when the focus is the player. */
int SceneBase_FocusSpeaker(SceneBase *scene)
{
    return SceneBase_Speaker(scene, scene->focus);
}
CLEAN_AS(func_02015d90, SceneBase_FocusSpeaker)

/* func_02015da0: speaker `number` (0 or 1), or 0 for another number. */
int SceneBase_Speaker(SceneBase *scene, int number)
{
    if (number == 0 || number == 1) {
        return (int) (uintptr_t) scene->speakers[number];
    }
    return 0;
}
CLEAN_AS(func_02015da0, SceneBase_Speaker)

/* func_02015db8 (slot 0x44): the focus is the second speaker. */
void SceneBase_FocusSecond(SceneBase *scene)
{
    scene->focus = SCENE_BASE_FOCUS_SECOND;
}
CLEAN_AS(func_02015db8, SceneBase_FocusSecond)

/* func_02015dc0 (slot 0x40): the focus is the first speaker. */
void SceneBase_FocusFirst(SceneBase *scene)
{
    scene->focus = SCENE_BASE_FOCUS_FIRST;
}
CLEAN_AS(func_02015dc0, SceneBase_FocusFirst)

/* func_02015dc8 (slot 0x3c): the focus is the player. */
void SceneBase_FocusPlayer(SceneBase *scene)
{
    scene->focus = SCENE_BASE_FOCUS_PLAYER;
}
CLEAN_AS(func_02015dc8, SceneBase_FocusPlayer)

/* func_02015dd0 (slot 0x34): nothing. */
void SceneBase_Nothing34(void) {}
CLEAN_AS(func_02015dd0, SceneBase_Nothing34)

/* func_02015dd4: puts `size` bytes at `bytes` into the talk's slot `slot` (func_020683e4) and
 * gives its answer. The last argument is not used. */
int SceneBase_PutBytes(SceneBase *scene, int slot, const void *bytes, int size, const void *unused)
{
    (void) unused;
    return func_020683e4(scene->talk, slot, bytes, (unsigned int) size);
}
CLEAN_AS(func_02015dd4, SceneBase_PutBytes)

/* func_02015de4: puts the name of the item at `item` (func_02062f90) into the talk's slot
 * `slot`, as a value of kind `kind` (func_020683b4). */
void SceneBase_PutItemName(SceneBase *scene, int item, int slot, int kind)
{
    SceneBaseItemText text;
    func_02062f90(&text, (const void *) (uintptr_t) item);
    func_020683b4(scene->talk, slot, &text, kind);
    func_02062f4c(&text);
}
CLEAN_AS(func_02015de4, SceneBase_PutItemName)

/* func_02015e10: puts the name of the person `npc` (NpcId_FormatName) into the talk's slot
 * `slot`. */
void SceneBase_PutNpcName(SceneBase *scene, const void *npc, int slot)
{
    SceneBaseText text;
    func_02094fd4(&text);
    NpcId_FormatName((const NpcId *) npc, (char *) &text);
    func_02068404(scene->talk, slot, &text);
    func_02094fbc(&text);
}
CLEAN_AS(func_02015e10, SceneBase_PutNpcName)

/* func_02015e40: puts the six characters at 0x10 of `from` (func_02095074) into the talk's
 * slot `slot`. */
void SceneBase_PutNameAt10(SceneBase *scene, void *from, int slot)
{
    SceneBaseText text;
    func_02094fd4(&text);
    func_02095074(from, &text);
    func_02068404(scene->talk, slot, &text);
    func_02094fbc(&text);
}
CLEAN_AS(func_02015e40, SceneBase_PutNameAt10)

/* func_02015e70: puts the six characters at 2 of `from` (func_02064210) into the talk's slot
 * `slot`. QUIRK: the answer is that of the text's destructor, the address of the text on
 * this function's own stack, which no caller uses. */
void *SceneBase_PutNameAt2(SceneBase *scene, unsigned int from, unsigned int slot)
{
    SceneBaseText text;
    func_020641c8(&text);
    func_02064210(from, &text);
    func_02068404(scene->talk, (int) slot, &text);
    return func_020641b0(&text);
}
CLEAN_AS(func_02015e70, SceneBase_PutNameAt2)

/* func_02015ea0: puts the number `value` (func_020b44a4) into the talk's slot `slot`. */
void SceneBase_PutNumber(SceneBase *scene, int value, int slot)
{
    SceneBaseLabel text;
    func_020a8228(&text);
    func_020b44a4(&text, value);
    func_02068404(scene->talk, slot, &text);
    func_020a8210(&text);
}
CLEAN_AS(func_02015ea0, SceneBase_PutNumber)

/* func_02015ed0: as SceneBase_PutNumber through func_020b44bc (which does what func_020b44a4
 * does). */
void SceneBase_PutNumberAlt(SceneBase *scene, void *value, int slot)
{
    SceneBaseLabel text;
    func_020a8228(&text);
    func_020b44bc(&text, value);
    func_02068404(scene->talk, slot, &text);
    func_020a8210(&text);
}
CLEAN_AS(func_02015ed0, SceneBase_PutNumberAlt)

/* func_02015f00: puts the fixed-point number `value` (func_020b4508, in `format`) into the
 * talk's slot `slot`; nothing for a negative value. The last argument is not used. */
void SceneBase_PutDecimal(SceneBase *scene, int value, int slot, int format, int unused)
{
    (void) unused;
    if (value < 0) {
        return;
    }
    SceneBaseNumberText text;
    func_020b5630(&text);
    func_020b4508(&text, value, format);
    func_02068404(scene->talk, slot, &text);
    func_020b5618(&text);
}
CLEAN_AS(func_02015f00, SceneBase_PutDecimal)

/* func_02015f38: puts the number `value` (func_020b45d0) into the talk's slot `slot`, as a
 * value of kind 7, or with `with_unit` followed by message 0x1c of "st_general" as a value of
 * kind 0 (func_020683b4); nothing for a negative value. */
void SceneBase_PutCount(SceneBase *scene, int value, int slot, int format, u8 with_unit, int a, int b)
{
    if (value < 0) {
        return;
    }
    SceneBaseNumberText text;
    int kind = SCENE_BASE_TEXT_KIND_PLAIN;
    func_020b5630(&text);
    func_020b45d0(&text, value, format, a, b, 0);
    if (with_unit != 0) {
        SceneBaseLabel unit;
        u8 message = SCENE_BASE_COUNT_UNIT_MESSAGE;
        func_020a8228(&unit);
        func_020b4a20(&unit, &message, data_020d8d0c);
        func_020a89dc(&text, &unit);
        kind = SCENE_BASE_TEXT_KIND_LABEL;
        func_020a8210(&unit);
    }
    func_020683b4(scene->talk, slot, &text, kind);
    func_020b5618(&text);
}
CLEAN_AS(func_02015f38, SceneBase_PutCount)

/* func_02015fb0: puts the number `value` (func_020b45d0) into the talk's slot `slot`; nothing
 * for a negative value. */
void SceneBase_PutValue(SceneBase *scene, int value, int slot, int format, int a, int b)
{
    if (value < 0) {
        return;
    }
    SceneBaseNumberText text;
    func_020b5630(&text);
    func_020b45d0(&text, value, format, a, b, 0);
    func_02068404(scene->talk, slot, &text);
    func_020b5618(&text);
}
CLEAN_AS(func_02015fb0, SceneBase_PutValue)

/* func_02015ff4: whether command 3 or 4 holds the first speaker's motion (byte 0x60 is 1). */
int SceneBase_IsHolding(const SceneBase *scene)
{
    return scene->holding == 1;
}
CLEAN_AS(func_02015ff4, SceneBase_IsHolding)

/* func_02016004 */
void SceneBase_ClearHolding(SceneBase *scene)
{
    scene->holding = 0;
}
CLEAN_AS(func_02016004, SceneBase_ClearHolding)

/* func_0201600c */
void SceneBase_SetHolding(SceneBase *scene)
{
    scene->holding = 1;
}
CLEAN_AS(func_0201600c, SceneBase_SetHolding)

/* func_02016014 (slot 0x38): SceneBase_SetSpeakerTalkStyle for the focus. */
int SceneBase_FocusTalkStyle(SceneBase *scene, int style)
{
    return SceneBase_SetSpeakerTalkStyle(scene, style, scene->focus);
}
CLEAN_AS(func_02016014, SceneBase_FocusTalkStyle)

/* func_02016024: speaker `speaker` takes the talking motion (kind 8, func_02019c90) in `style`,
 * kept as the talking style of the scene the speaker talks in (func_0201c274). Answers 0
 * without the speaker or its scene; 1 while that scene holds a motion (SceneBase_IsHolding);
 * 8 when the speaker already talks in that style; else func_02019c90's answer. */
int SceneBase_SetSpeakerTalkStyle(SceneBase *scene, int style, int speaker)
{
    u8 *object = scene_base_speaker(scene, speaker);
    if (object == NULL) {
        return 0;
    }
    SceneBase *own = (SceneBase *) (uintptr_t) func_0201c274(object);
    if (own == NULL) {
        return 0;
    }
    int holding = SceneBase_IsHolding(own);
    if (holding != 0) {
        return holding;
    }
    void *motion = object + SCENE_BASE_SPEAKER_MOTION;
    if (own->talk_style == style && func_02019e00(motion) == SCENE_BASE_MOTION_TALK) {
        return SCENE_BASE_MOTION_TALK;
    }
    int result = func_02019c90(motion, SCENE_BASE_MOTION_TALK_PRIORITY, (u8) style, data_020c80f8);
    own->talk_style = style;
    return result;
}
CLEAN_AS(func_02016024, SceneBase_SetSpeakerTalkStyle)

/* func_0201607c (slot 0x6c): the kind func_020823e8 gives the person (its code at 0xea) of
 * the speaker whose turn it is, or 5 without one. */
int SceneBase_SpeakingKind(SceneBase *scene)
{
    if (scene->speaking == 0 || scene->speaking == 1) {
        u8 *speaker = scene->speakers[scene->speaking];
        if (speaker != NULL) {
            return func_020823e8(speaker + SCENE_BASE_SPEAKER_CODE);
        }
    }
    return SCENE_BASE_NO_KIND;
}
CLEAN_AS(func_0201607c, SceneBase_SpeakingKind)

/* func_020160b4: the talk's part at 0x31c (func_0206837c; the player's choice is at 0x2d8 in
 * it), or 0 without a talk. */
int SceneBase_TalkChoices(SceneBase *scene)
{
    if (scene->talk == NULL) {
        return 0;
    }
    return (int) func_0206837c(scene->talk);
}
CLEAN_AS(func_020160b4, SceneBase_TalkChoices)

/* func_020160d0 */
void SceneBase_SetFirstSpeaker(SceneBase *scene, u8 *speaker)
{
    scene->speakers[0] = speaker;
}
CLEAN_AS(func_020160d0, SceneBase_SetFirstSpeaker)

/* func_020160d4 */
int SceneBase_SecondSpeaker(SceneBase *scene)
{
    return (int) (uintptr_t) scene->speakers[1];
}
CLEAN_AS(func_020160d4, SceneBase_SecondSpeaker)

/* func_020160d8: sets the second speaker; when it talks in a scene (func_0201c274), that scene
 * is reset (its slot 0x08) and the speaker's slot 0x8c is called.
 *
 * QUIRK: the second speaker is read again after the reset, which clears it when the speaker
 * talks in this very scene. */
void SceneBase_SetSecondSpeaker(SceneBase *scene, u8 *speaker)
{
    scene->speakers[1] = speaker;
    if (scene->speakers[1] == NULL) {
        return;
    }
    unsigned int own_scene = func_0201c274(scene->speakers[1]);
    if (own_scene == 0) {
        return;
    }
    scene_base_call((void *) (uintptr_t) own_scene, SCENE_BASE_SLOT_RESET);
    scene_base_call(scene->speakers[1], SCENE_BASE_SLOT_SPEAKER_JOINED);
}
CLEAN_AS(func_020160d8, SceneBase_SetSecondSpeaker)

/* gt2GetIncomingBufferSize (0x02016104, misnamed in the symbols): the word at 0x48 the
 * commands' motions take (scene_command.h). */
int SceneBase_MotionArg(SceneBase *scene)
{
    return scene->motion_arg;
}
CLEAN_AS(gt2GetIncomingBufferSize, SceneBase_MotionArg)

/* func_02016108 */
void SceneBase_SetMotionArg(SceneBase *scene, int value)
{
    scene->motion_arg = value;
}
CLEAN_AS(func_02016108, SceneBase_SetMotionArg)

/* func_0201610c (slot 0x7c): nothing. */
void SceneBase_Nothing7c(void *scene)
{
    (void) scene;
}
CLEAN_AS(func_0201610c, SceneBase_Nothing7c)

/* func_02016110: the scene's step: its slot 0x80, then the step of its command
 * (SceneCommand_Run). */
void SceneBase_Update(SceneBase *scene)
{
    scene_base_call(scene, SCENE_BASE_SLOT_BEFORE_STEP);
    SceneCommand_Run((SceneCommandScene *) (void *) scene);
}
CLEAN_AS(func_02016110, SceneBase_Update)

/* func_02016128 (slot 0x80): nothing. */
void SceneBase_Nothing80(void *scene)
{
    (void) scene;
}
CLEAN_AS(func_02016128, SceneBase_Nothing80)

/* func_0201612c (slot 0x08): resets the scene: the receiver's reset, then the motion word,
 * the second speaker, the focus, the speaking number, the talking style and the holding flag
 * are cleared and the commands start again (SceneCommand_Init).
 *
 * QUIRK: the first speaker is kept. */
void SceneBase_Reset(SceneBase *scene)
{
    _ZN13Base_0206699417vfunc_02066994_08Ev(scene);
    scene->motion_arg = 0;
    scene->speakers[1] = NULL;
    scene->focus = SCENE_BASE_FOCUS_FIRST;
    scene->speaking = 0;
    scene->talk_style = 0;
    SceneBase_ClearHolding(scene);
    SceneCommand_Init((SceneCommandScene *) (void *) scene);
}
CLEAN_AS(func_0201612c, SceneBase_Reset)

/* func_0201615c: the destructor, as SceneBase_Destruct (a second copy of it). Returns the
 * scene. */
void *SceneBase_DestructBody(void *scene)
{
    *(const u8 **) scene = data_020d8bd4;
    func_02066994(scene);
    return scene;
}
CLEAN_AS(func_0201615c, SceneBase_DestructBody)

/* func_02016174 (slot 0x04): the destructor that also frees the scene's memory. Returns the
 * scene. */
void *SceneBase_DestructDelete(SceneBase *scene)
{
    scene->vtable = data_020d8bd4;
    func_02066994(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_02016174, SceneBase_DestructDelete)

/* func_02016194 (slot 0x00): the destructor: the receiver's (func_02066994), which has no
 * members of the scene's own to destroy. Returns the scene. */
void *SceneBase_Destruct(void *scene)
{
    *(const u8 **) scene = data_020d8bd4;
    func_02066994(scene);
    return scene;
}
CLEAN_AS(func_02016194, SceneBase_Destruct)

/* func_020161ac: the constructor: the receiver's (func_02066a30), then no item, no motion
 * word, no speakers, the talking style 0, no command, and the commands' start
 * (SceneCommand_Init). Returns the scene. */
SceneBase *SceneBase_Construct(SceneBase *scene)
{
    func_02066a30(scene);
    scene->vtable = data_020d8bd4;
    scene->item = SCENE_BASE_NO_ITEM;
    scene->motion_arg = 0;
    scene->speakers[0] = NULL;
    scene->speakers[1] = NULL;
    scene->talk_style = 0;
    scene->command = SCENE_BASE_NO_COMMAND;
    SceneCommand_Init((SceneCommandScene *) (void *) scene);
    return scene;
}
CLEAN_AS(func_020161ac, SceneBase_Construct)
