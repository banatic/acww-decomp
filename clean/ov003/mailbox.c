/* The mailbox: its modes and their animations (mailbox.h). */
#include "mailbox.h"

#include <stdint.h>

#include "clean.h"
#include "ov004/member_pointer.h"

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "autoload_2/heap.h"     /* Heap, Heap_FreeAux, Heap_AllocAuxZeroed */
#include "autoload_2/matrix.h"   /* Mtx43, Mtx43_Translate */
#include "autoload_2/vector.h"   /* Vec3, Vec_DistanceXZ */
#include "main/collision_query.h"
#include "main/globe.h"
#include "main/group_params.h"
#include "main/letter.h"
#include "main/mail.h"
#include "main/model_anim.h"
#include "main/model_object.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_object_base.h"
#include "main/scene_query.h"
#include "main/session.h"
#include "main/touch_pick_shapes.h"
#include "main/town_objects.h" /* TownObjects_SetActorMode, SceneActor */
#include "ov003/field_actor.h"

static_assert(offsetof(Mailbox, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(Mailbox, mode) == 0x134, "mode");
static_assert(offsetof(Mailbox, code) == 0x136, "code");
static_assert(offsetof(Mailbox, model_object) == 0x13c, "model object");
static_assert(offsetof(Mailbox, model_frames) == 0x1d8, "model frames");
static_assert(offsetof(Mailbox, sound) == 0x238, "sound");
static_assert(offsetof(Mailbox, state) == 0x2b4, "state");
static_assert(offsetof(Mailbox, pattern) == 0x2b8, "pattern");
static_assert(offsetof(Mailbox, moves_on) == 0x2f4, "moves on");
static_assert(sizeof(Mailbox) == 0x2f8, "the size its allocator gets");
static_assert(offsetof(MailboxAnim, frame) == 0x08, "anim frame");
static_assert(offsetof(MailboxAnim, target) == 0x18, "anim target");
static_assert(sizeof(MailboxAnim) == 0x20, "anim");
static_assert(offsetof(MailboxAnimFile, frames) == 0x04, "anim file frames");

#define MAILBOX_ONE 0x1000 /* normal speed, 20.12 fixed point */
/* The modes of the joint animations: from the first frame on, or from the last frame back. */
#define MAILBOX_PLAY_FORWARD 1
#define MAILBOX_PLAY_BACKWARD 3
/* The modes of the texture pattern animation in MAILBOX_EMPTY and MAILBOX_FULL. */
#define MAILBOX_PATTERN_EMPTY 1
#define MAILBOX_PATTERN_FULL 0
#define MAILBOX_PATTERN_SOUND_FRAME 18
/* Sounds. */
#define MAILBOX_SE_PATTERN 0x7de
#define MAILBOX_SE_OPEN 0x819
#define MAILBOX_SE_CLOSE 0x81a
#define MAILBOX_SE_EMPTY 0x81b
/* Overlay 9's vtable slots of its two animation files. */
#define MAILBOX_SLOT_ANIM_A 0x64
#define MAILBOX_SLOT_ANIM_B 0x68

/* The mode tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov003_0223c9dc;
extern MemberPointer data_ov003_0223ca68[MAILBOX_MODES];
extern const MemberPointer data_ov003_022393ec, data_ov003_02239414, data_ov003_02239424, data_ov003_022393ac,
    data_ov003_022393dc, data_ov003_022393f4, data_ov003_02239464;
extern u32 data_ov003_0223c9d8;
extern MemberPointer data_ov003_0223ca30[MAILBOX_MODES];
extern const MemberPointer data_ov003_022393fc, data_ov003_0223940c, data_ov003_0223945c, data_ov003_02239454,
    data_ov003_022393c4, data_ov003_022393bc, data_ov003_022393b4;

/* Sets `mode` through vtable slot 0x6c (when a wireless flag of main is clear) and, in a
 * session with others, tells them; whether it was set. */
extern int func_020b2800(Mailbox *mailbox, unsigned int mode);
/* Main's mode of the special character `code`. */
extern int func_020b30e8(unsigned int code, unsigned char mode);
/* Lets the scene go on. */
extern int func_0203e020(Mailbox *mailbox);
/* The byte at 0x2f4, and the number of filled entries of the player's ten (0 while that byte is
 * clear). */
extern u8 func_ov003_0221e6a0(Mailbox *mailbox);
extern int func_ov003_0221e6ac(Mailbox *mailbox);
/* The model object's joint animation: played from `file` by `mode` and `speed` from `frame`,
 * advanced, and whether it is at its end (on its frame control); the model object's render
 * object. */
extern void func_02055060(void *model_object, const MailboxAnimFile *file, int mode, int speed, u16 frame, u16 a5);
extern void func_02055124(void *model_object);
extern int func_02056f94(void *frames);
extern void *func_02055e00(void *model_object);
/* An animation: advanced, whether it is at `frame`, and playing `file` on a render object by
 * `mode` and `speed` from `frame`. */
extern void func_02056ffc(MailboxAnim *anim);
extern int func_02056f28(MailboxAnim *anim, int frame);
extern void func_02056440(MailboxAnim *anim, void *render_object, void *file, int mode, int speed, u16 frame);
/* Overlay 9's scene actor: its animation file `index` (0 to 3), and the sound effect `id` on its
 * sound source. */
extern void *func_ov009_02264cf8(Mailbox *mailbox, unsigned int index);
extern void func_ov009_02262ef0(void *sound, int id);

/* Joint animation A or B: what vtable slot 0x64 or 0x68 gives. */
static const MailboxAnimFile *mailbox_anim_file(Mailbox *mailbox, unsigned int slot)
{
    typedef const MailboxAnimFile *(*MailboxAnimSlot)(Mailbox *mailbox);

    u32 code = *(const u32 *) ((const u8 *) mailbox->vtable + slot);
    return ((MailboxAnimSlot) (uintptr_t) code)(mailbox);
}

/* Plays joint animation A or B from its last frame by `mode`. Its slot is asked twice: once for
 * the number of frames, once for the file. */
static void mailbox_play_from_end(Mailbox *mailbox, unsigned int slot, int mode)
{
    const MailboxAnimFile *counted = mailbox_anim_file(mailbox, slot);
    const MailboxAnimFile *file = mailbox_anim_file(mailbox, slot);
    func_02055060(mailbox->model_object, file, mode, MAILBOX_ONE, (u16) (counted->frames - 1), 0);
}

/* The pattern animation goes on and its frame is written where it goes.
 * REQUIRES: the pattern is bound (it has a target). */
static void mailbox_advance_pattern(Mailbox *mailbox)
{
    func_02056ffc(&mailbox->pattern);
    *mailbox->pattern.target = mailbox->pattern.frame;
}

/* Whether the mode may move on: the byte at 0x2f4 is set and the joint animation is at its
 * end. */
static int mailbox_anim_done(Mailbox *mailbox)
{
    return func_ov003_0221e6a0(mailbox) != 0 && func_02056f94(mailbox->model_frames) != 0;
}

/* func_ov003_0221de58 (run of MAILBOX_EMPTYING): moves on to MAILBOX_EMPTY once A is at its
 * end, else A goes on; then the pattern goes on. */
void Mailbox_RunEmptying(Mailbox *mailbox)
{
    if (mailbox_anim_done(mailbox)) {
        func_020b2800(mailbox, MAILBOX_EMPTY);
    } else {
        func_02055124(mailbox->model_object);
    }
    mailbox_advance_pattern(mailbox);
}
CLEAN_AS(func_ov003_0221de58, Mailbox_RunEmptying)

/* func_ov003_0221deb0 (entry of MAILBOX_EMPTYING): A from its last frame in mode 3, and sound
 * 0x81b. */
int Mailbox_EnterEmptying(Mailbox *mailbox)
{
    mailbox_play_from_end(mailbox, MAILBOX_SLOT_ANIM_A, MAILBOX_PLAY_BACKWARD);
    func_ov009_02262ef0(mailbox->sound, MAILBOX_SE_EMPTY);
    return 1;
}
CLEAN_AS(func_ov003_0221deb0, Mailbox_EnterEmptying)

/* func_ov003_0221df08 (run of MAILBOX_CLOSING): once B is at its end, moves on to MAILBOX_FULL
 * while there are letters, else to MAILBOX_EMPTYING; until then B goes on. Then the pattern
 * goes on. */
void Mailbox_RunClosing(Mailbox *mailbox)
{
    if (mailbox_anim_done(mailbox)) {
        if (!func_ov003_0221e6ac(mailbox)) {
            func_020b2800(mailbox, MAILBOX_EMPTYING);
        } else {
            func_020b2800(mailbox, MAILBOX_FULL);
        }
    } else {
        func_02055124(mailbox->model_object);
    }
    mailbox_advance_pattern(mailbox);
}
CLEAN_AS(func_ov003_0221df08, Mailbox_RunClosing)

/* func_ov003_0221df74 (entry of MAILBOX_CLOSING): B from its last frame in mode 3, and sound
 * 0x81a. */
int Mailbox_EnterClosing(Mailbox *mailbox)
{
    mailbox_play_from_end(mailbox, MAILBOX_SLOT_ANIM_B, MAILBOX_PLAY_BACKWARD);
    func_ov009_02262ef0(mailbox->sound, MAILBOX_SE_CLOSE);
    return 1;
}
CLEAN_AS(func_ov003_0221df74, Mailbox_EnterClosing)

/* func_ov003_0221dfcc (run of MAILBOX_OPEN): the pattern goes on. */
void Mailbox_RunOpen(Mailbox *mailbox)
{
    mailbox_advance_pattern(mailbox);
}
CLEAN_AS(func_ov003_0221dfcc, Mailbox_RunOpen)

/* func_ov003_0221dff4 (entry of MAILBOX_OPEN): B held at its last frame (mode 1). */
int Mailbox_EnterOpen(Mailbox *mailbox)
{
    mailbox_play_from_end(mailbox, MAILBOX_SLOT_ANIM_B, MAILBOX_PLAY_FORWARD);
    return 1;
}
CLEAN_AS(func_ov003_0221dff4, Mailbox_EnterOpen)

/* func_ov003_0221e038 (run of MAILBOX_OPENING): B and the pattern go on; once B is at its end it
 * moves on to MAILBOX_OPEN. */
void Mailbox_RunOpening(Mailbox *mailbox)
{
    func_02055124(mailbox->model_object);
    mailbox_advance_pattern(mailbox);
    if (mailbox_anim_done(mailbox)) {
        func_020b2800(mailbox, MAILBOX_OPEN);
    }
}
CLEAN_AS(func_ov003_0221e038, Mailbox_RunOpening)

/* func_ov003_0221e090 (entry of MAILBOX_OPENING): B from its start (mode 1), and sound 0x819. */
int Mailbox_EnterOpening(Mailbox *mailbox)
{
    func_02055060(mailbox->model_object, mailbox_anim_file(mailbox, MAILBOX_SLOT_ANIM_B), MAILBOX_PLAY_FORWARD, MAILBOX_ONE, 0,
                  0);
    func_ov009_02262ef0(mailbox->sound, MAILBOX_SE_OPEN);
    return 1;
}
CLEAN_AS(func_ov003_0221e090, Mailbox_EnterOpening)

/* func_ov003_0221e0d4 (run of MAILBOX_FULL): the pattern goes on. */
void Mailbox_RunFull(Mailbox *mailbox)
{
    mailbox_advance_pattern(mailbox);
}
CLEAN_AS(func_ov003_0221e0d4, Mailbox_RunFull)

/* func_ov003_0221e0fc (entry of MAILBOX_FULL): A held at its last frame (mode 1), and the
 * pattern (overlay 9's animation file 0) from its start in mode 0 on the model's render
 * object. */
int Mailbox_EnterFull(Mailbox *mailbox)
{
    mailbox_play_from_end(mailbox, MAILBOX_SLOT_ANIM_A, MAILBOX_PLAY_FORWARD);
    void *render_object = func_02055e00(mailbox->model_object);
    void *file = func_ov009_02264cf8(mailbox, 0);
    func_02056440(&mailbox->pattern, render_object, file, MAILBOX_PATTERN_FULL, MAILBOX_ONE, 0);
    return 1;
}
CLEAN_AS(func_ov003_0221e0fc, Mailbox_EnterFull)

/* func_ov003_0221e16c (run of MAILBOX_ARRIVING): moves on to MAILBOX_FULL once A is at its end,
 * else A goes on. */
void Mailbox_RunArriving(Mailbox *mailbox)
{
    if (mailbox_anim_done(mailbox)) {
        func_020b2800(mailbox, MAILBOX_FULL);
        return;
    }
    func_02055124(mailbox->model_object);
}
CLEAN_AS(func_ov003_0221e16c, Mailbox_RunArriving)

/* func_ov003_0221e1a4 (entry of MAILBOX_ARRIVING): A from its start (mode 1). */
int Mailbox_EnterArriving(Mailbox *mailbox)
{
    func_02055060(mailbox->model_object, mailbox_anim_file(mailbox, MAILBOX_SLOT_ANIM_A), MAILBOX_PLAY_FORWARD, MAILBOX_ONE, 0,
                  0);
    return 1;
}
CLEAN_AS(func_ov003_0221e1a4, Mailbox_EnterArriving)

/* func_ov003_0221e1d8 (run of MAILBOX_EMPTY): moves on to MAILBOX_ARRIVING once there are
 * letters. */
void Mailbox_RunEmpty(Mailbox *mailbox)
{
    if (func_ov003_0221e6ac(mailbox)) {
        func_020b2800(mailbox, MAILBOX_ARRIVING);
    }
}
CLEAN_AS(func_ov003_0221e1d8, Mailbox_RunEmpty)

/* func_ov003_0221e1f4 (entry of MAILBOX_EMPTY): A from its start (mode 1), and the pattern
 * (overlay 9's animation file 0) from its start in mode 1 on the model's render object. */
int Mailbox_EnterEmpty(Mailbox *mailbox)
{
    func_02055060(mailbox->model_object, mailbox_anim_file(mailbox, MAILBOX_SLOT_ANIM_A), MAILBOX_PLAY_FORWARD, MAILBOX_ONE, 0,
                  0);
    void *render_object = func_02055e00(mailbox->model_object);
    void *file = func_ov009_02264cf8(mailbox, 0);
    func_02056440(&mailbox->pattern, render_object, file, MAILBOX_PATTERN_EMPTY, MAILBOX_ONE, 0);
    return 1;
}
CLEAN_AS(func_ov003_0221e1f4, Mailbox_EnterEmpty)

/* func_ov003_0221e254 (vtable slot 0x74): the mode's run, through its table; then sound 0x7de
 * when the pattern is at its frame 18. */
void Mailbox_RunMode(Mailbox *mailbox)
{
    static const MemberPointer *const runs[MAILBOX_MODES] = {
        &data_ov003_022393ec, /* Mailbox_RunEmpty */
        &data_ov003_02239414, /* Mailbox_RunArriving */
        &data_ov003_02239424, /* Mailbox_RunFull */
        &data_ov003_022393ac, /* Mailbox_RunOpening */
        &data_ov003_022393dc, /* Mailbox_RunOpen */
        &data_ov003_022393f4, /* Mailbox_RunClosing */
        &data_ov003_02239464, /* Mailbox_RunEmptying */
    };
    MemberTable_InitOnce(&data_ov003_0223c9dc, data_ov003_0223ca68, runs, MAILBOX_MODES);
    if (mailbox->mode < MAILBOX_MODES) {
        MemberPointer_CallVoid(&data_ov003_0223ca68[mailbox->mode], mailbox);
    }
    if (func_02056f28(&mailbox->pattern, MAILBOX_PATTERN_SOUND_FRAME)) {
        func_ov009_02262ef0(mailbox->sound, MAILBOX_SE_PATTERN);
    }
}
CLEAN_AS(func_ov003_0221e254, Mailbox_RunMode)

/* func_ov003_0221e32c (vtable slot 0x6c): enters `mode` if its entry (through a table) agrees
 * and main takes it as the special character's mode; whether it did. */
int Mailbox_SetMode(Mailbox *mailbox, unsigned int mode)
{
    static const MemberPointer *const entries[MAILBOX_MODES] = {
        &data_ov003_022393fc, /* Mailbox_EnterEmpty */
        &data_ov003_0223940c, /* Mailbox_EnterArriving */
        &data_ov003_0223945c, /* Mailbox_EnterFull */
        &data_ov003_02239454, /* Mailbox_EnterOpening */
        &data_ov003_022393c4, /* Mailbox_EnterOpen */
        &data_ov003_022393bc, /* Mailbox_EnterClosing */
        &data_ov003_022393b4, /* Mailbox_EnterEmptying */
    };
    MemberTable_InitOnce(&data_ov003_0223c9d8, data_ov003_0223ca30, entries, MAILBOX_MODES);
    if (mode >= MAILBOX_MODES) {
        return 0;
    }
    if (MemberPointer_CallInt(&data_ov003_0223ca30[mode], mailbox) == 0) {
        return 0;
    }
    if (func_020b30e8(mailbox->code, (unsigned char) mode) == 0) {
        return 0;
    }
    mailbox->mode = (u8) mode;
    return 1;
}
CLEAN_AS(func_ov003_0221e32c, Mailbox_SetMode)

/* func_ov003_0221e404 (run of the other machine's state 4, whose entry moves the mode on to
 * MAILBOX_CLOSING): lets the scene go on once the mode is MAILBOX_EMPTY or MAILBOX_FULL. */
void Mailbox_RunClose(Mailbox *mailbox)
{
    if (mailbox->mode == MAILBOX_EMPTY || mailbox->mode == MAILBOX_FULL) {
        func_0203e020(mailbox);
    }
}
CLEAN_AS(func_ov003_0221e404, Mailbox_RunClose)

/* The other machine (enum MailboxState), its set-up, its drawing and its life. */

static_assert(offsetof(Mailbox, state) == 0x2b4, "other machine's state");
static_assert(offsetof(SceneActor, position) == 0x5c, "actor position");
static_assert(offsetof(SceneActor, yaw) == 0x8e, "actor yaw");
static_assert(offsetof(SceneActor, code) == 0x136, "actor code");
static_assert(offsetof(SceneActor, model) == 0x198, "actor model");
static_assert(sizeof(ModelAnim) == sizeof(MailboxAnim), "the pattern is main's animation");
static_assert(sizeof(TouchPickSphere) == sizeof(((Mailbox *) NULL)->unk_2D8), "touch sphere");

#define MAILBOX_RECEIVER_OFFSET 0xec
/* The scene events of vtable slot 0x4c. */
#define MAILBOX_EVENT_CHECK 0
#define MAILBOX_EVENT_CHECK_AGAIN 1
#define MAILBOX_EVENT_IDLE 8
/* The mode of group 9 that shows the letters. */
#define MAILBOX_LETTERS_MODE 0x27
/* FieldActor_PlayerRequestState6BOr6C's choice of state 0x6c. */
#define MAILBOX_PLAYER_STATE_6C 2
/* Where the player is asked to go: 2.0 along z from the mailbox. */
#define MAILBOX_APPROACH_Z 0x2000
/* How near (about 2.2) and how squarely the player must stand to check it. */
#define MAILBOX_ACT_DISTANCE 0x2333
#define MAILBOX_ACT_ANGLE 0x1200
/* The point of the ground the model is placed at: 2.0 along x and 1.0 back along z from its
 * position; the matrix is then moved back by as much. */
#define MAILBOX_MODEL_X 0x2000
#define MAILBOX_MODEL_Z 0x1000
/* The touch sphere: 1.0 above its position, of radius 1.0 and kind 7. */
#define MAILBOX_SPHERE_HEIGHT 0x1000
#define MAILBOX_SPHERE_RADIUS 0x1000
#define MAILBOX_SPHERE_KIND 7
/* The flags its texture pattern animation is started with when it is set up. */
#define MAILBOX_PATTERN_SETUP_FLAGS 1
/* The vtable slot that sets its mode (Mailbox_SetMode for this class). */
#define MAILBOX_SLOT_SET_MODE 0x6c

/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_0223948c[];
extern const u8 data_ov003_02239550[];
/* The other machine's tables (member_pointer.h): their guards, the tables and their
 * constants. */
extern u32 data_ov003_0223c9c4;
extern MemberPointer data_ov003_0223ca08[MAILBOX_STATES];
extern const MemberPointer data_ov003_0223941c, data_ov003_022393cc, data_ov003_022393d4, data_ov003_02239404,
    data_ov003_022393e4;
extern u32 data_ov003_0223c9b8;
extern MemberPointer data_ov003_0223c9e0[MAILBOX_STATES];
extern const MemberPointer data_ov003_0223942c, data_ov003_0223944c, data_ov003_02239444, data_ov003_0223943c,
    data_ov003_02239434;
/* A matrix of main's the model's matrix is moved in. */
extern Mtx43 data_021fbe48;
/* The heap its pattern's animation object comes from. */
extern Heap *data_021c9b1c;
extern NetSession *data_020ccf94;
/* Overlay 9's scene actor: its model's matrix built from its placement (the point at 0xc4 and
 * the turn about y at 0xd0), its destructor and its constructor. */
extern void func_ov009_022648a4(Mailbox *mailbox, Mtx43 *matrix);
extern void *func_ov009_0226539c(Mailbox *mailbox);
extern void *func_ov009_0226552c(Mailbox *mailbox);
/* Its index in overlay 3's table of 32 scene actors (data_ov003_0223cef0), -1 when it is not
 * there. */
extern int func_ov003_02220150(Mailbox *mailbox);

/* The point and the turn overlay 9 builds the model's matrix from (bytes 0xc4 to 0xd1 of the
 * scene actor). */
typedef struct MailboxPlacement {
    Vec3 point;
    u16 turn;
} MailboxPlacement;

#define MAILBOX_PLACEMENT_OFFSET 0xc4

/* The mailbox as overlay 9's scene actor, which it is derived from. */
static SceneActor *mailbox_actor(Mailbox *mailbox)
{
    return (SceneActor *) (void *) mailbox;
}

static MailboxPlacement *mailbox_placement(Mailbox *mailbox)
{
    return (MailboxPlacement *) (void *) ((u8 *) mailbox + MAILBOX_PLACEMENT_OFFSET);
}

/* The pattern as main's animation object, and the touch sphere at 0x2d8. */
static ModelAnim *mailbox_pattern(Mailbox *mailbox)
{
    return (ModelAnim *) (void *) &mailbox->pattern;
}

static TouchPickSphere *mailbox_sphere(Mailbox *mailbox)
{
    return (TouchPickSphere *) (void *) mailbox->unk_2D8;
}

/* Sets the mode through vtable slot 0x6c. */
static void mailbox_set_mode_slot(Mailbox *mailbox, int mode)
{
    typedef int (*MailboxSetModeSlot)(Mailbox *mailbox, int mode);

    u32 code = *(const u32 *) ((const u8 *) mailbox->vtable + MAILBOX_SLOT_SET_MODE);
    ((MailboxSetModeSlot) (uintptr_t) code)(mailbox, mode);
}

/* Copies a matrix two words at a time, in the order the original does. */
static void mailbox_copy_matrix(Mtx43 *dst, const Mtx43 *src)
{
    const fx32 *from = &src->m[0][0];
    fx32 *to = &dst->m[0][0];
    for (int i = 0; i < 12; i += 2) {
        fx32 first = from[i];
        fx32 second = from[i + 1];
        to[i] = first;
        to[i + 1] = second;
    }
}

/* func_ov003_0221e424 (entry of MAILBOX_STATE_CLOSE): moves the mode on to MAILBOX_CLOSING;
 * always 1. */
int Mailbox_EnterClose(Mailbox *mailbox)
{
    TownObjects_SetActorMode(mailbox_actor(mailbox), MAILBOX_CLOSING);
    return 1;
}
CLEAN_AS(func_ov003_0221e424, Mailbox_EnterClose)

/* _ZN18Obj_ov003_0223948c19func_ov003_0221e438Ev (run of MAILBOX_STATE_READING): once main can
 * open a screen again, asks for player state 0x6c and moves to MAILBOX_STATE_CLOSE when it was
 * queued. */
void Mailbox_RunReading(Mailbox *mailbox)
{
    if (GroupParams_CanOpen() && FieldActor_PlayerRequestState6BOr6C(MAILBOX_PLAYER_STATE_6C)) {
        Mailbox_SetState(mailbox, MAILBOX_STATE_CLOSE);
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223948c19func_ov003_0221e438Ev, Mailbox_RunReading)

/* func_ov003_0221e45c (entry of MAILBOX_STATE_READING): always 1. */
int Mailbox_EnterReading(Mailbox *mailbox)
{
    (void) mailbox;
    return 1;
}
CLEAN_AS(func_ov003_0221e45c, Mailbox_EnterReading)

/* _ZN18Obj_ov003_0223948c19func_ov003_0221e460Ev (run of MAILBOX_STATE_LETTERS): on to
 * MAILBOX_STATE_READING; whether it got there. */
int Mailbox_RunLetters(Mailbox *mailbox)
{
    return Mailbox_SetState(mailbox, MAILBOX_STATE_READING);
}
CLEAN_AS(_ZN18Obj_ov003_0223948c19func_ov003_0221e460Ev, Mailbox_RunLetters)

/* func_ov003_0221e46c (entry of MAILBOX_STATE_LETTERS): whether main agreed to open group 9 in
 * mode 0x27. */
int Mailbox_EnterLetters(Mailbox *mailbox)
{
    (void) mailbox;
    return GroupParams_Open(MAILBOX_LETTERS_MODE) != 0;
}
CLEAN_AS(func_ov003_0221e46c, Mailbox_EnterLetters)

/* _ZN18Obj_ov003_0223948c19func_ov003_0221e488Ev (run of MAILBOX_STATE_APPROACH): once the mode
 * is MAILBOX_OPEN, on to MAILBOX_STATE_LETTERS. */
void Mailbox_RunApproach(Mailbox *mailbox)
{
    if (mailbox->mode == MAILBOX_OPEN) {
        Mailbox_SetState(mailbox, MAILBOX_STATE_LETTERS);
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223948c19func_ov003_0221e488Ev, Mailbox_RunApproach)

/* func_ov003_0221e4a4 (entry of MAILBOX_STATE_APPROACH): asks the player of this console to go
 * to the point 2.0 along z from the mailbox, at the floor's height (player state 0x6a); when
 * that was queued the mode moves on to MAILBOX_OPENING. Always 1. */
int Mailbox_EnterApproach(Mailbox *mailbox)
{
    SceneActor *actor = mailbox_actor(mailbox);
    Vec3 point;
    point.x = actor->position.x;
    point.y = CollisionQuery_FloorHeight(0);
    point.z = actor->position.z + MAILBOX_APPROACH_Z;
    if (FieldActor_PlayerRequestState6A(&point)) {
        TownObjects_SetActorMode(actor, MAILBOX_OPENING);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221e4a4, Mailbox_EnterApproach)

/* func_ov003_0221e4e0 (run of MAILBOX_STATE_IDLE) */
void Mailbox_RunIdle(void) {}
CLEAN_AS(func_ov003_0221e4e0, Mailbox_RunIdle)

/* func_ov003_0221e4e4 (entry of MAILBOX_STATE_IDLE): always 1. */
int Mailbox_EnterIdle(Mailbox *mailbox)
{
    (void) mailbox;
    return 1;
}
CLEAN_AS(func_ov003_0221e4e4, Mailbox_EnterIdle)

/* func_ov003_0221e4e8: the other machine's run, through its table.
 * REQUIRES: the state is not negative (Mailbox_SetState only sets 0 to 4). */
void Mailbox_RunState(Mailbox *mailbox)
{
    static const MemberPointer *const runs[MAILBOX_STATES] = {
        &data_ov003_0223941c, /* Mailbox_RunIdle */
        &data_ov003_022393cc, /* Mailbox_RunApproach */
        &data_ov003_022393d4, /* Mailbox_RunLetters */
        &data_ov003_02239404, /* Mailbox_RunReading */
        &data_ov003_022393e4, /* Mailbox_RunClose */
    };
    MemberTable_InitOnce(&data_ov003_0223c9c4, data_ov003_0223ca08, runs, MAILBOX_STATES);
    if (mailbox->state < MAILBOX_STATES) {
        MemberPointer_CallVoid(&data_ov003_0223ca08[mailbox->state], mailbox);
    }
}
CLEAN_AS(func_ov003_0221e4e8, Mailbox_RunState)

/* _ZN18Obj_ov003_0223948c19func_ov003_0221e580Ei: enters `state` of the other machine if its
 * entry (through a table) agrees; whether it did. States 5 and above do not exist.
 * REQUIRES: `state` is not negative. */
int Mailbox_SetState(Mailbox *mailbox, int state)
{
    static const MemberPointer *const entries[MAILBOX_STATES] = {
        &data_ov003_0223942c, /* Mailbox_EnterIdle */
        &data_ov003_0223944c, /* Mailbox_EnterApproach */
        &data_ov003_02239444, /* Mailbox_EnterLetters */
        &data_ov003_0223943c, /* Mailbox_EnterReading */
        &data_ov003_02239434, /* Mailbox_EnterClose */
    };
    MemberTable_InitOnce(&data_ov003_0223c9b8, data_ov003_0223c9e0, entries, MAILBOX_STATES);
    if (state < MAILBOX_STATES && MemberPointer_CallInt(&data_ov003_0223c9e0[state], mailbox) != 0) {
        mailbox->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(_ZN18Obj_ov003_0223948c19func_ov003_0221e580Ei, Mailbox_SetState)

/* func_ov003_0221e628 (vtable slot 0xb8): the model's matrix. Overlay 9 builds it at the point
 * of the bent ground (Globe_BendFar) under 2.0 along x and 1.0 back along z from the position,
 * turned by what the bending gives; the matrix is then moved back by (-2.0, 0, 1.0) in the
 * model's own axes, in main's matrix data_021fbe48. Always 1. */
int Mailbox_ModelMatrix(Mailbox *mailbox, Mtx43 *matrix)
{
    SceneActor *actor = mailbox_actor(mailbox);
    MailboxPlacement *placement = mailbox_placement(mailbox);
    Vec3 point;
    point.x = actor->position.x + MAILBOX_MODEL_X;
    point.y = 0;
    point.z = actor->position.z - MAILBOX_MODEL_Z;
    placement->turn = (u16) Globe_BendFar(&placement->point, &point);
    func_ov009_022648a4(mailbox, matrix);
    mailbox_copy_matrix(&data_021fbe48, matrix);
    Mtx43_Translate(&data_021fbe48, -MAILBOX_MODEL_X, 0, MAILBOX_MODEL_Z);
    mailbox_copy_matrix(matrix, &data_021fbe48);
    return 1;
}
CLEAN_AS(func_ov003_0221e628, Mailbox_ModelMatrix)

/* func_ov003_0221e6a0: whether its modes move on (the byte at 0x2f4). */
u8 Mailbox_MovesOn(Mailbox *mailbox)
{
    return mailbox->moves_on;
}
CLEAN_AS(func_ov003_0221e6a0, Mailbox_MovesOn)

/* func_ov003_0221e6ac: the number of letters in the mailbox of this console's player (those of
 * its ten whose state is not 0); 0 while the modes do not move on or when the player has no
 * mailbox. */
int Mailbox_CountLetters(Mailbox *mailbox)
{
    if (Mailbox_MovesOn(mailbox) == 0) {
        return 0;
    }
    MailBox *box = PlayerRecord_Mailbox(PlayerRecords_Current());
    if (box == NULL) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < MAILBOX_LETTERS; i++) {
        MailLetter *letter = MailBox_Letter(box, i);
        if (letter != NULL && Letter_State((const Letter *) (const void *) letter) != 0) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_ov003_0221e6ac, Mailbox_CountLetters)

/* _ZN18Obj_ov003_0223948c19func_ov003_0221e6f0Ei (vtable slot 0x4c): the scene's events: 0 and
 * 1 start a check (MAILBOX_STATE_APPROACH), 8 makes it idle; others do nothing. */
void Mailbox_OnSceneEvent(Mailbox *mailbox, int event)
{
    switch (event) {
        case MAILBOX_EVENT_CHECK:
        case MAILBOX_EVENT_CHECK_AGAIN:
            Mailbox_SetState(mailbox, MAILBOX_STATE_APPROACH);
            break;
        case MAILBOX_EVENT_IDLE:
            Mailbox_SetState(mailbox, MAILBOX_STATE_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223948c19func_ov003_0221e6f0Ei, Mailbox_OnSceneEvent)

/* func_ov003_0221e718 (vtable slot 0x48): whether `other` (the player of this console) may
 * check it: its modes move on, it is MAILBOX_FULL, and `other` stands within about 2.2 of it
 * in the ground plane facing it (its yaw within 0x1200 of the mailbox's turned half round).
 * SceneObjectBase_ClearApproach runs on it first in any case. */
int Mailbox_MayAct(Mailbox *mailbox, SceneObjectBase *other)
{
    SceneActor *actor = mailbox_actor(mailbox);
    SceneObjectBase_ClearApproach((SceneObjectBase *) (void *) mailbox);
    if (Mailbox_MovesOn(mailbox) == 0) {
        return 0;
    }
    return mailbox->mode == MAILBOX_FULL && other != NULL &&
           Vec_DistanceXZ(&other->position, &actor->position) < MAILBOX_ACT_DISTANCE &&
           Math_AbsDiff16((s16) (actor->yaw + 0x8000), other->yaw) < MAILBOX_ACT_ANGLE;
}
CLEAN_AS(func_ov003_0221e718, Mailbox_MayAct)

/* func_ov003_0221e788 (vtable slot 0xb0): its drawing does not draw the model; always 0. */
int Mailbox_DrawsModel(void)
{
    return 0;
}
CLEAN_AS(func_ov003_0221e788, Mailbox_DrawsModel)

/* func_ov003_0221e78c (vtable slot 0x18, its update): the other machine's run, then the touch
 * sphere is added to the field's touch pick for this frame; always 1. */
int Mailbox_Update(Mailbox *mailbox)
{
    Mailbox_RunState(mailbox);
    TouchPick_AddSphere((TouchPick *) (intptr_t) SceneQuery_FieldObject(), mailbox_sphere(mailbox));
    return 1;
}
CLEAN_AS(func_ov003_0221e78c, Mailbox_Update)

/* func_ov003_0221e7ac (vtable slot 0x70, setting it up): when overlay 9 has its animation file
 * 0 and a material animation object could be allocated for the model, the pattern starts from
 * that file and is attached to the model's render object. The touch sphere is set 1.0 above
 * its position, with its index in overlay 3's table of actors. Its modes move on only in scene
 * 0 and when this console is slot 0 of a linked session or plays alone. Then the other machine
 * is idle and the mode (vtable slot 0x6c) MAILBOX_EMPTY when the modes move on, else the one
 * main recorded for its code. Always 1. */
int Mailbox_SetUp(Mailbox *mailbox)
{
    SceneActor *actor = mailbox_actor(mailbox);
    ModelAnim *pattern = mailbox_pattern(mailbox);
    if (func_ov009_02264cf8(mailbox, 0) != NULL && ModelAnim_AllocMaterialAnim(pattern, actor->model, data_021c9b1c) != 0) {
        ModelAnim_Start(pattern, func_ov009_02264cf8(mailbox, 0), MAILBOX_PATTERN_SETUP_FLAGS, MAILBOX_ONE, 0);
        ModelAnim_Attach(pattern, ModelObject_RenderObject((ModelObject *) (void *) mailbox->model_object));
    }

    u8 index = (u8) func_ov003_02220150(mailbox);
    Vec3 centre = actor->position;
    centre.y += MAILBOX_SPHERE_HEIGHT;
    TouchPick_SetSphereAndAdd((TouchPick *) (intptr_t) SceneQuery_FieldObject(), mailbox_sphere(mailbox), &centre,
                              MAILBOX_SPHERE_RADIUS, MAILBOX_SPHERE_KIND, index);

    mailbox->moves_on = 1;
    if (!SceneQuery_CurrentIs0()) {
        mailbox->moves_on = 0;
    } else {
        NetSession *session = data_020ccf94;
        if (Session_IsLinked(session) && !Session_IsLocalSlot(session, 0)) {
            mailbox->moves_on = 0;
        }
    }

    Mailbox_SetState(mailbox, MAILBOX_STATE_IDLE);
    if (Mailbox_MovesOn(mailbox)) {
        mailbox_set_mode_slot(mailbox, MAILBOX_EMPTY);
    } else {
        mailbox_set_mode_slot(mailbox, TownObjects_RecordedMode(actor->code));
    }
    return 1;
}
CLEAN_AS(func_ov003_0221e7ac, Mailbox_SetUp)

/* The vtables set back, the touch sphere and the pattern destroyed, then overlay 9's
 * destructor. */
static void mailbox_destroy_parts(Mailbox *mailbox)
{
    mailbox->vtable = data_ov003_0223948c;
    mailbox->receiver_vtable = data_ov003_02239550;
    TouchPickSphere_Destruct2(mailbox_sphere(mailbox));
    ModelAnim_DestructComplete(mailbox_pattern(mailbox));
    func_ov009_0226539c(mailbox);
}

/* func_ov003_0221e8c4 (vtable slot 0x44, the deleting destructor): the destructor's work, then
 * the memory freed. */
Mailbox *Mailbox_DestroyAndFree(Mailbox *mailbox)
{
    mailbox_destroy_parts(mailbox);
    Heap_FreeAux(mailbox);
    return mailbox;
}
CLEAN_AS(func_ov003_0221e8c4, Mailbox_DestroyAndFree)

/* func_ov003_0221e908 (vtable slot 0x40): the destructor, without freeing. */
Mailbox *Mailbox_Destroy(Mailbox *mailbox)
{
    mailbox_destroy_parts(mailbox);
    return mailbox;
}
CLEAN_AS(func_ov003_0221e908, Mailbox_Destroy)

/* func_ov003_0221e948: the constructor: overlay 9's, the vtables, then the pattern and the
 * touch sphere. */
Mailbox *Mailbox_Construct(Mailbox *mailbox)
{
    func_ov009_0226552c(mailbox);
    mailbox->vtable = data_ov003_0223948c;
    mailbox->receiver_vtable = data_ov003_02239550;
    ModelAnim_Construct(mailbox_pattern(mailbox));
    TouchPickSphere_Construct(mailbox_sphere(mailbox));
    return mailbox;
}
CLEAN_AS(func_ov003_0221e948, Mailbox_Construct)

/* func_ov003_0221e984 (the class's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void Mailbox_New(void)
{
    Mailbox *mailbox = Heap_AllocAuxZeroed(sizeof(Mailbox));
    if (mailbox != NULL) {
        Mailbox_Construct(mailbox);
    }
}
CLEAN_AS(func_ov003_0221e984, Mailbox_New)

/* The mailbox around its receiver part, as the receiver vtable's thunks find it. */
static Mailbox *mailbox_from_receiver(void *receiver)
{
    return (Mailbox *) (void *) ((u8 *) receiver - MAILBOX_RECEIVER_OFFSET);
}

/* _ZThn236_N18Obj_ov003_0223948cD0Ev (receiver slot 0x04): Mailbox_DestroyAndFree. */
Mailbox *Mailbox_ReceiverDestroyAndFree(void *receiver)
{
    return Mailbox_DestroyAndFree(mailbox_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_0223948cD0Ev, Mailbox_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_0223948cD1Ev (receiver slot 0x00): Mailbox_Destroy. */
Mailbox *Mailbox_ReceiverDestroy(void *receiver)
{
    return Mailbox_Destroy(mailbox_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_0223948cD1Ev, Mailbox_ReceiverDestroy)
