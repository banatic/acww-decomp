/* The mailbox: its modes and their animations (mailbox.h). */
#include "mailbox.h"

#include <stdint.h>

#include "clean.h"
#include "ov004/member_pointer.h"

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
