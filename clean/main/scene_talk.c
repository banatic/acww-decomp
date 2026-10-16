/* The turns of a talk between two speakers in a scene (scene_talk.h).
 *
 * REQUIRES: the talk's state at a word-aligned address, as every object of the game is (the
 * ARM9 writes the aligned word at a misaligned address). */
#include "scene_talk.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "ov004/member_pointer.h"
#include "scene_command.h"

/* The scene's parts used here. */
#define SCENE_TALK_TALK 0x40
#define SCENE_TALK_SPEAKING 0x55
#define SCENE_TALK_START_WITH_CAMERA 0xa4
#define SCENE_TALK_STATE 0xac
#define SCENE_TALK_STATES 3

/* The talk's words used here. */
#define SCENE_TALK_TALK_STATE 4
#define SCENE_TALK_TALK_NEXT 8
#define SCENE_TALK_TALK_UNK_14 0x14
#define SCENE_TALK_LINE_SHOWN 5

/* A speaker's parts and vtable slot used here: its position, its talking flag (func_0201a7cc
 * clears it) and its name into a string object. */
#define SCENE_TALK_SPEAKER_POSITION 0x5c
#define SCENE_TALK_SPEAKER_TALKING 0x418
#define SCENE_TALK_SLOT_NAME 0x74

/* The height above a speaker's position the camera aims at. */
#define SCENE_TALK_CAMERA_HEIGHT 0x2000
/* func_0203ad30's answer from which state 2 waits, while func_0203ad88 agrees. */
#define SCENE_TALK_CAMERA_WAIT 0x11

/* A string object (0x24 bytes): built by func_02094fd4, destroyed by func_02094fbc. */
typedef struct SceneTalkText {
    const u8 *vtable;
    u8 unk_04[0x20];
} SceneTalkText;

/* The table of states: a guard word, the table and the constants it is filled from. */
extern u32 data_021c1510;
extern MemberPointer data_021c1684[];
extern const MemberPointer data_020d88f4;
extern const MemberPointer data_020d85f4;
extern const MemberPointer data_020d8604;

extern u8 *func_02015d78(void *scene, int number);
extern int func_0203ad88(void);
extern u8 func_0203ad30(void);
extern int func_0203ae28(Vec3 *at);
extern void func_0201a7cc(void *talking);
extern void *func_02094fd4(SceneTalkText *text);
extern void *func_02094fbc(SceneTalkText *text);
extern int func_0201c250(void *object);
extern void func_020668d8(void *scene, SceneTalkText *text, int a);

static u8 *scene_talk_part(void *scene, u32 offset)
{
    return (u8 *) scene + offset;
}

static s32 *scene_talk_talk(void *scene)
{
    return *(s32 **) scene_talk_part(scene, SCENE_TALK_TALK);
}

/* _ZN12Obj_020d8bd413func_020148a0Ev: the state's function, through its table; its answer, 0
 * from state 3 on. */
int SceneTalk_Run(void *scene)
{
    static const MemberPointer *const states[SCENE_TALK_STATES] = {
        &data_020d88f4, /* SceneTalk_Begin */
        &data_020d85f4, /* SceneTalk_LookAtNext */
        &data_020d8604, /* SceneTalk_PassTurn */
    };
    MemberTable_InitOnce(&data_021c1510, data_021c1684, states, SCENE_TALK_STATES);
    u8 state = *scene_talk_part(scene, SCENE_TALK_STATE);
    if (state < SCENE_TALK_STATES) {
        return MemberPointer_CallInt(&data_021c1684[state], scene);
    }
    return 0;
}
CLEAN_AS(_ZN12Obj_020d8bd413func_020148a0Ev, SceneTalk_Run)

/* func_02014920 (state 2): once the line is shown, and unless the camera still waits
 * (func_0203ad88 agrees and func_0203ad30 gives 0x11 or more): the speaker's talking flag is
 * cleared, the turn passes to the other speaker, whose name (its vtable slot 0x74) goes to the
 * scene as the next line's speaker (func_020668d8, with func_0201c250's answer); the next line
 * is asked for and the state is 3. Whether the turn passed (without the other speaker, the
 * turn passes but nothing else is done). */
int SceneTalk_PassTurn(void *scene)
{
    typedef void (*SceneTalkFill)(void *object, SceneTalkText *text);

    s32 *talk = scene_talk_talk(scene);
    if (talk == NULL || talk[SCENE_TALK_TALK_STATE / 4] != SCENE_TALK_LINE_SHOWN) {
        return 0;
    }
    if (func_0203ad88() != 0 && func_0203ad30() >= SCENE_TALK_CAMERA_WAIT) {
        return 0;
    }
    u8 *speaking = scene_talk_part(scene, SCENE_TALK_SPEAKING);
    u8 *speaker = func_02015d78(scene, *speaking);
    if (speaker != NULL) {
        func_0201a7cc(speaker + SCENE_TALK_SPEAKER_TALKING);
    }
    *speaking = (u8) ((*speaking + 1) & 1);
    u8 *next = func_02015d78(scene, *speaking);
    if (next == NULL) {
        return 0;
    }

    SceneTalkText text;
    func_02094fd4(&text);
    const u8 *vtable = *(const u8 *const *) next;
    u32 fill_name = *(const u32 *) (vtable + SCENE_TALK_SLOT_NAME);
    ((SceneTalkFill) (uintptr_t) fill_name)(next, &text);
    int a = func_0201c250(next);
    func_020668d8(scene, &text, a);
    scene_talk_talk(scene)[SCENE_TALK_TALK_NEXT / 4] = 1;
    *scene_talk_part(scene, SCENE_TALK_STATE) = 3;
    func_02094fbc(&text);
    return 1;
}
CLEAN_AS(func_02014920, SceneTalk_PassTurn)

/* func_020149c4 (state 1): once the line is shown, the camera aims above the speaker after the
 * one speaking (func_0203ae28), when there is one, and the state is 2. The answer is 0. */
int SceneTalk_LookAtNext(void *scene)
{
    s32 *talk = scene_talk_talk(scene);
    if (talk != NULL && talk[SCENE_TALK_TALK_STATE / 4] == SCENE_TALK_LINE_SHOWN) {
        u8 speaking = *scene_talk_part(scene, SCENE_TALK_SPEAKING);
        u8 *next = func_02015d78(scene, (u8) ((speaking + 1) & 1));
        if (next != NULL) {
            Vec3 at = *(const Vec3 *) (next + SCENE_TALK_SPEAKER_POSITION);
            at.y += SCENE_TALK_CAMERA_HEIGHT;
            func_0203ae28(&at);
        }
        *scene_talk_part(scene, SCENE_TALK_STATE) = 2;
    }
    return 0;
}
CLEAN_AS(func_020149c4, SceneTalk_LookAtNext)

/* func_02014a20 (state 0): with a talk, its word 0x14 is 2 and the state 1 when the scene's byte
 * 0xa4 is set, else 2. The answer is 0. */
int SceneTalk_Begin(void *scene)
{
    s32 *talk = scene_talk_talk(scene);
    if (talk != NULL) {
        talk[SCENE_TALK_TALK_UNK_14 / 4] = 2;
        *scene_talk_part(scene, SCENE_TALK_STATE) = *scene_talk_part(scene, SCENE_TALK_START_WITH_CAMERA) != 0 ? 1 : 2;
    }
    return 0;
}
CLEAN_AS(func_02014a20, SceneTalk_Begin)

/* func_02014a44: asks the scene for its talk turns (its command 11, scene_command.h), beginning
 * with the camera on the next speaker when `with_camera` is set. Whether the scene took it. */
int SceneTalk_Request(u8 *scene, u8 with_camera)
{
    if (SceneCommand_Request((SceneCommandScene *) scene, SCENE_COMMAND_TALK_TURNS)) {
        *scene_talk_part(scene, SCENE_TALK_START_WITH_CAMERA) = with_camera;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02014a44, SceneTalk_Request)

/* func_02015a10: the talk turns, beginning with the camera; whether the scene took them is
 * dropped. */
void SceneTalk_RequestWithCamera(int scene)
{
    SceneTalk_Request((u8 *) (uintptr_t) scene, 1);
}
CLEAN_AS(func_02015a10, SceneTalk_RequestWithCamera)
