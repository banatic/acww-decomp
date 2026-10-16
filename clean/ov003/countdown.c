/* The countdown board and its digits (countdown.h). */
#include "countdown.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h" /* Heap, Heap_Alloc, Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "main/actor.h"    /* Actor_Spawn, Actor_Draw */
#include "main/calendar.h" /* DateTime */
#include "main/sound.h"    /* SoundSys_PlaySe */
#include "ov004/member_pointer.h"

static_assert(offsetof(CountdownAnim, frame) == 0x08, "anim frame");
static_assert(offsetof(CountdownAnim, target) == 0x18, "anim target");
static_assert(sizeof(CountdownAnim) == 0x20, "anim");
static_assert(offsetof(CountdownDigit, receiver_vtable) == 0xec, "digit receiver");
static_assert(offsetof(CountdownDigit, model_object) == 0x13c, "digit model object");
static_assert(offsetof(CountdownDigit, model) == 0x198, "digit model");
static_assert(offsetof(CountdownDigit, place) == 0x2b4, "digit place");
static_assert(offsetof(CountdownDigit, anim) == 0x2b8, "digit anim");
static_assert(offsetof(CountdownDigit, running) == 0x2d8, "digit running");
static_assert(offsetof(CountdownDigit, quiet) == 0x2d9, "digit quiet");
static_assert(sizeof(CountdownDigit) == 0x2dc, "the size CountdownDigit_New allocates");
static_assert(offsetof(CountdownBoard, position) == 0x5c, "board position");
static_assert(offsetof(CountdownBoard, receiver_vtable) == 0xec, "board receiver");
static_assert(offsetof(CountdownBoard, mode) == 0x134, "board mode");
static_assert(offsetof(CountdownBoard, code) == 0x136, "board code");
static_assert(offsetof(CountdownBoard, model) == 0x198, "board model");
static_assert(offsetof(CountdownBoard, flags_235) == 0x235, "board flags");
static_assert(offsetof(CountdownBoard, anim) == 0x2b4, "board anim");
static_assert(offsetof(CountdownBoard, material) == 0x2d4, "board material");
static_assert(offsetof(CountdownBoard, alpha) == 0x2d5, "board alpha");
static_assert(offsetof(CountdownBoard, digits) == 0x2d8, "board digits");
static_assert(sizeof(CountdownBoard) == 0x2f0, "the size CountdownBoard_New allocates");
static_assert(offsetof(CountdownRenderObject, board) == 0x2c, "render object user");
static_assert(offsetof(CountdownMaterialResult, polygon_attr) == 0x0c, "polygon attributes");
static_assert(offsetof(CountdownRenderState, hooks) == 0x0c, "hooks");
static_assert(offsetof(CountdownRenderState, hook_timings) == 0x8c, "hook timings");
static_assert(offsetof(CountdownRenderState, material_result) == 0xb0, "material result");

#define COUNTDOWN_RECEIVER_OFFSET 0xec
#define COUNTDOWN_ONE 0x1000       /* normal speed, 20.12 fixed point */
#define COUNTDOWN_ANIM_ONCE 1      /* the digits' animation mode */
#define COUNTDOWN_ANIM_BOARD 0     /* the board's animation mode */
#define COUNTDOWN_NEW_YEAR_MONTH 1 /* January: the countdown is over */
#define COUNTDOWN_SECONDS_PER_DAY 86400
#define COUNTDOWN_SILENT_SCENE 0x2c /* in this scene (func_020b65c4) the digits play no sound */
#define COUNTDOWN_SE_LAST_TEN 0x60  /* each of the last ten seconds */
#define COUNTDOWN_SE_NEW_YEAR 0x61  /* when the month turns to January */
#define COUNTDOWN_SE_LAST_MINUTE                                                                                              \
    0x62 /* at one minute left, and each second of the last minute
                                        * before the last ten */
#define COUNTDOWN_DIGIT_PROFILE 0x26
#define COUNTDOWN_DIGIT_CODE 0x501f
#define COUNTDOWN_ALPHA_OPAQUE 0x1f
#define COUNTDOWN_ALPHA_FADED 1
#define COUNTDOWN_ALPHA_MASK 0x001f0000u
#define COUNTDOWN_ALPHA_SHIFT 16
/* The render state's command whose hook the board sets: materials, after the material. */
#define COUNTDOWN_COMMAND_MATERIAL 4
#define COUNTDOWN_TIMING_AFTER 2
/* The status Actor_Draw gets when the digits are drawn first. */
#define COUNTDOWN_DRAW_STATUS 2
/* The modes the mode tables let through (see CountdownBoard_RunMode). */
#ifdef BUGFIX
#define COUNTDOWN_MODE_LIMIT COUNTDOWN_MODES
#else
#define COUNTDOWN_MODE_LIMIT 3
#endif

/* The vtables: the digit's and the board's, and their receiver parts'. */
extern const u8 data_ov003_02238b10[];
extern const u8 data_ov003_02238bd4[];
extern const u8 data_ov003_02238c54[];
extern const u8 data_ov003_02238d18[];

/* The time left until midnight, worked out by CountdownBoard_Update, and the place of the
 * digit being made (CountdownDigit_Init reads it). */
extern u32 data_ov003_0223c8b8; /* hours */
extern u32 data_ov003_0223c8c0; /* minutes */
extern u32 data_ov003_0223c8bc; /* seconds */
extern u8 data_ov003_0223c8b0;
#define countdown_hours data_ov003_0223c8b8
#define countdown_minutes data_ov003_0223c8c0
#define countdown_seconds data_ov003_0223c8bc
#define countdown_making_place data_ov003_0223c8b0

/* Where the digits stand along x from the board, left to right. */
extern const fx32 data_ov003_0223662c[COUNTDOWN_PLACES];
/* "m_cbs_Adt", the material whose alpha the board sets. */
extern const char data_ov003_02238d90[];
/* Main's heap the digits come from, and their animations are bound with. */
extern Heap *data_021c9b1c;

/* The mode tables (member_pointer.h): their guards, the tables and their constants. Each table
 * has room for three entries but only two are filled; the third stays zero. */
extern u32 data_ov003_0223c8b4;
extern MemberPointer data_ov003_0223c8e0[3];
extern const MemberPointer data_ov003_02238ab8, data_ov003_02238ad0;
extern u32 data_ov003_0223c8c4;
extern MemberPointer data_ov003_0223c8c8[3];
extern const MemberPointer data_ov003_02238ac0, data_ov003_02238ac8;

/* The clock's date and time (DateTime_Now). */
extern void func_0209e474(DateTime *now);
extern u8 func_020b65c4(void);
/* Sets the actor's id word from its profile and `value`. */
extern void func_0203efb0(CountdownDigit *digit, u32 value);
/* An animation: advanced, bound to a model's resource (whether it could), playing `file` by
 * `mode` and `speed` from `frame`, put on a render object, and both at once. */
extern void func_02056ffc(CountdownAnim *anim);
extern int func_0205650c(CountdownAnim *anim, void *model, Heap *heap);
extern void func_02056478(CountdownAnim *anim, void *file, int mode, int speed, u16 frame);
extern void func_020563dc(CountdownAnim *anim, void *render_object);
extern void func_02056440(CountdownAnim *anim, void *render_object, void *file, int mode, int speed, u16 frame);
extern void *func_020565b0(CountdownAnim *anim);
extern void func_020565c8(CountdownAnim *anim);
/* The model object's render object, and the hook it runs before it is drawn (given `user`). */
extern void *func_02055e00(void *model_object);
extern void func_02055dc8(void *model_object, void *hook, void *user);
/* The index of the material `name` of a model. */
extern int func_02057a50(void *model, const char *name);
/* Main's mode of the special character `code`. */
extern int func_020b30e8(u16 code, unsigned int mode);
/* Overlay 9's scene actor: its animation file `index` (0 to 3), its resources, its path
 * slots, the drawing of an actor's model, its destructor and its constructor. */
extern void *func_ov009_02264cf8(void *actor, int index);
extern char *func_ov009_02264884(void *actor);
extern void *func_ov009_02264b64(void *actor);
extern char *func_ov009_02264be0(void *actor);
extern int *func_ov009_02264c10(void *actor);
extern void func_ov009_022632c8(void *actor);
extern void *func_ov009_0226539c(void *actor);
extern void *func_ov009_0226552c(void *actor);
/* The hooks are the game's functions: their addresses go to the model and its render state. */
extern void func_ov003_0221d038(CountdownRenderState *state);
extern void func_ov003_0221d048(CountdownRenderState *state);

/* The place `place` of the time left, kept as the byte a digit keeps; whether `place` is one of
 * the six.
 * QUIRK: of the hours' tens only the lowest bit is kept, so 24 hours left (at midnight) shows
 * as 04. */
static int countdown_place_value(u8 place, u8 *value)
{
    switch (place) {
        case COUNTDOWN_HOUR_TENS:
            *value = (u8) ((countdown_hours / 10) & 1);
            return 1;
        case COUNTDOWN_HOUR_ONES:
            *value = (u8) (countdown_hours % 10);
            return 1;
        case COUNTDOWN_MINUTE_TENS:
            *value = (u8) (countdown_minutes / 10);
            return 1;
        case COUNTDOWN_MINUTE_ONES:
            *value = (u8) (countdown_minutes % 10);
            return 1;
        case COUNTDOWN_SECOND_TENS:
            *value = (u8) (countdown_seconds / 10);
            return 1;
        case COUNTDOWN_SECOND_ONES:
            *value = (u8) (countdown_seconds % 10);
            return 1;
        default:
            return 0;
    }
}

/* func_ov003_0221c720 (digit vtable slot 0xb0): always 0. */
int CountdownDigit_Slot0B0(void)
{
    return 0;
}
CLEAN_AS(func_ov003_0221c720, CountdownDigit_Slot0B0)

/* The sound of a digit that changed, in the last hour outside scene 0x2c: in the last minute
 * the last place plays COUNTDOWN_SE_LAST_TEN for the last ten seconds and
 * COUNTDOWN_SE_LAST_MINUTE before them and at one minute left, unless the digit is quiet. Any
 * change makes it no longer quiet. */
static void countdown_digit_sound(CountdownDigit *digit)
{
    if (countdown_hours != 0 || func_020b65c4() == COUNTDOWN_SILENT_SCENE) {
        return;
    }
    int sound = -1;
    if (countdown_minutes == 1 && countdown_seconds == 0) {
        sound = COUNTDOWN_SE_LAST_MINUTE;
    } else if (countdown_minutes == 0 && countdown_seconds != 0) {
        sound = countdown_seconds <= 10 ? COUNTDOWN_SE_LAST_TEN : COUNTDOWN_SE_LAST_MINUTE;
    }
    if (digit->shown == digit->value) {
        return;
    }
    if (sound != -1 && digit->place == COUNTDOWN_SECOND_ONES && !digit->quiet) {
        SoundSys_PlaySe(sound);
    }
    digit->quiet = 0;
}

/* func_ov003_0221c724: while the digit runs, takes its value from the time left and plays its
 * sound when it changed (countdown_digit_sound); once the month is January it stops running
 * instead. In every case what it shows is remembered. */
void CountdownDigit_Tick(CountdownDigit *digit)
{
    if (digit->running) {
        DateTime now = {0};
        func_0209e474(&now);
        if (now.month == COUNTDOWN_NEW_YEAR_MONTH) {
            digit->running = 0;
        } else {
            countdown_place_value(digit->place, &digit->value);
            countdown_digit_sound(digit);
        }
    }
    digit->shown = digit->value;
}
CLEAN_AS(func_ov003_0221c724, CountdownDigit_Tick)

/* func_ov003_0221c8ac (digit vtable slot 0x18, its update): CountdownDigit_Tick, then its
 * animation 0 is put on the model at the frame of its value; always 1. */
int CountdownDigit_Update(CountdownDigit *digit)
{
    CountdownDigit_Tick(digit);
    void *render_object = func_02055e00(digit->model_object);
    void *file = func_ov009_02264cf8(digit, 0);
    func_02056440(&digit->anim, render_object, file, COUNTDOWN_ANIM_ONCE, COUNTDOWN_ONE, digit->value);
    return 1;
}
CLEAN_AS(func_ov003_0221c8ac, CountdownDigit_Update)

/* func_ov003_0221c8fc (digit vtable slot 0x70, setting it up): takes the place the board is
 * making (countdown_making_place) as its own and in its id word, binds its animation 0 to the
 * model when it can, and starts running. Before January it shows its place's value at once,
 * the seconds' places quiet so that the first change plays no sound. Then
 * CountdownDigit_Tick; always 1. */
int CountdownDigit_Init(CountdownDigit *digit)
{
    digit->place = countdown_making_place;
    digit->value = 0;
    func_0203efb0(digit, digit->place);
    if (func_0205650c(&digit->anim, digit->model, data_021c9b1c) != 0) {
        func_02056478(&digit->anim, func_ov009_02264cf8(digit, 0), COUNTDOWN_ANIM_ONCE, COUNTDOWN_ONE, 0);
        func_020563dc(&digit->anim, func_02055e00(digit->model_object));
    }
    digit->running = 1;
    digit->shown = 0xff;

    DateTime now = {0};
    func_0209e474(&now);
    u8 value;
    if (now.month != COUNTDOWN_NEW_YEAR_MONTH && countdown_place_value(digit->place, &value)) {
        digit->shown = value;
        digit->value = value;
        digit->quiet = digit->place >= COUNTDOWN_SECOND_TENS;
    }
    CountdownDigit_Tick(digit);
    return 1;
}
CLEAN_AS(func_ov003_0221c8fc, CountdownDigit_Init)

/* func_ov003_0221ca98 (the digit's operator delete): nothing; digits are never freed. */
void CountdownDigit_Delete(void *digit)
{
    (void) digit;
}
CLEAN_AS(func_ov003_0221ca98, CountdownDigit_Delete)

/* func_ov003_0221ca9c (the digit's operator new): `size` bytes of main's heap at data_021c9b1c,
 * cleared.
 * REQUIRES: the heap has room. BUG: when it has not, the original clears `size` bytes at
 * address 0. */
int CountdownDigit_Alloc(int size)
{
    void *block = Heap_Alloc(data_021c9b1c, size);
#ifdef BUGFIX
    if (block == NULL) {
        return 0;
    }
#endif
    memset(block, 0, (size_t) size);
    return (int) (uintptr_t) block;
}
CLEAN_AS(func_ov003_0221ca9c, CountdownDigit_Alloc)

/* The digit's vtables set back, its animation destroyed, then overlay 9's destructor. */
static void countdown_digit_destroy_parts(CountdownDigit *digit)
{
    digit->vtable = data_ov003_02238b10;
    digit->receiver_vtable = data_ov003_02238bd4;
    func_020565b0(&digit->anim);
    func_ov009_0226539c(digit);
}

/* func_ov003_0221cac4 (digit vtable slot 0x44, the deleting destructor): the destructor's work,
 * then its operator delete, which frees nothing. */
CountdownDigit *CountdownDigit_DestroyAndFree(CountdownDigit *digit)
{
    countdown_digit_destroy_parts(digit);
    CountdownDigit_Delete(digit);
    return digit;
}
CLEAN_AS(func_ov003_0221cac4, CountdownDigit_DestroyAndFree)

/* func_ov003_0221cafc (digit vtable slot 0x40): the destructor. */
CountdownDigit *CountdownDigit_Destroy(CountdownDigit *digit)
{
    countdown_digit_destroy_parts(digit);
    return digit;
}
CLEAN_AS(func_ov003_0221cafc, CountdownDigit_Destroy)

/* func_ov003_0221cb30: the digit's constructor: overlay 9's, the vtables, then its
 * animation's. */
CountdownDigit *CountdownDigit_Construct(CountdownDigit *digit)
{
    func_ov009_0226552c(digit);
    digit->vtable = data_ov003_02238b10;
    digit->receiver_vtable = data_ov003_02238bd4;
    func_020565c8(&digit->anim);
    return digit;
}
CLEAN_AS(func_ov003_0221cb30, CountdownDigit_Construct)

/* The board's animation goes on, and its frame to where it goes. */
static void countdown_board_animate(CountdownBoard *board)
{
    func_02056ffc(&board->anim);
    *board->anim.target = board->anim.frame;
}

/* Vtable slot 0x6c: CountdownBoard_SetMode for this class. */
static void countdown_board_switch_to(CountdownBoard *board, int mode)
{
    typedef int (*CountdownSetModeSlot)(CountdownBoard *board, int mode);
    u32 slot = *(const u32 *) ((const u8 *) board->vtable + 0x6c);
    ((CountdownSetModeSlot) (uintptr_t) slot)(board, mode);
}

/* func_ov003_0221cb60 (run of COUNTDOWN_OVER): the animation goes on. */
void CountdownBoard_RunOver(CountdownBoard *board)
{
    countdown_board_animate(board);
}
CLEAN_AS(func_ov003_0221cb60, CountdownBoard_RunOver)

/* func_ov003_0221cb88 (entry of COUNTDOWN_OVER): plays animation 1 from its start and fades
 * "m_cbs_Adt"; always 1. */
int CountdownBoard_EnterOver(CountdownBoard *board)
{
    func_02056478(&board->anim, func_ov009_02264cf8(board, 1), COUNTDOWN_ANIM_BOARD, COUNTDOWN_ONE, 0);
    board->alpha = COUNTDOWN_ALPHA_FADED;
    return 1;
}
CLEAN_AS(func_ov003_0221cb88, CountdownBoard_EnterOver)

/* _ZN18Obj_ov003_02238c5419func_ov003_0221cbc0Ev (run of COUNTDOWN_COUNTING): the animation
 * goes on; once the month is January, plays COUNTDOWN_SE_NEW_YEAR and moves to
 * COUNTDOWN_OVER. */
void CountdownBoard_RunCounting(CountdownBoard *board)
{
    countdown_board_animate(board);
    DateTime now = {0};
    func_0209e474(&now);
    if (now.month == COUNTDOWN_NEW_YEAR_MONTH) {
        SoundSys_PlaySe(COUNTDOWN_SE_NEW_YEAR);
        countdown_board_switch_to(board, COUNTDOWN_OVER);
    }
}
CLEAN_AS(_ZN18Obj_ov003_02238c5419func_ov003_0221cbc0Ev, CountdownBoard_RunCounting)

/* func_ov003_0221cc10 (entry of COUNTDOWN_COUNTING): plays animation 0 from its start and makes
 * "m_cbs_Adt" opaque; always 1. */
int CountdownBoard_EnterCounting(CountdownBoard *board)
{
    func_02056478(&board->anim, func_ov009_02264cf8(board, 0), COUNTDOWN_ANIM_BOARD, COUNTDOWN_ONE, 0);
    board->alpha = COUNTDOWN_ALPHA_OPAQUE;
    return 1;
}
CLEAN_AS(func_ov003_0221cc10, CountdownBoard_EnterCounting)

/* func_ov003_0221cc48 (vtable slot 0x74): the mode's run, through its table.
 * BUG: modes up to 2 are let through, but the table has only two entries: mode 2 would call
 * through the zero third entry. Only CountdownBoard_SetMode sets the mode, and the game asks
 * it for 0 and 1. BUGFIX: let modes below 2 through. */
void CountdownBoard_RunMode(CountdownBoard *board)
{
    static const MemberPointer *const runs[COUNTDOWN_MODES] = {
        &data_ov003_02238ab8, /* CountdownBoard_RunCounting */
        &data_ov003_02238ad0, /* CountdownBoard_RunOver */
    };
    MemberTable_InitOnce(&data_ov003_0223c8b4, data_ov003_0223c8e0, runs, COUNTDOWN_MODES);
    if (board->mode < COUNTDOWN_MODE_LIMIT) {
        MemberPointer_CallVoid(&data_ov003_0223c8e0[board->mode], board);
    }
}
CLEAN_AS(func_ov003_0221cc48, CountdownBoard_RunMode)

/* _ZN18Obj_ov003_02238c5419func_ov003_0221ccb4Ej (vtable slot 0x6c): enters `mode` if its entry
 * (through a table) agrees and main takes it as the special character's mode; whether it did.
 * BUG: as in CountdownBoard_RunMode, mode 2 would call through the zero third entry.
 * BUGFIX: let modes below 2 through. */
int CountdownBoard_SetMode(CountdownBoard *board, unsigned int mode)
{
    static const MemberPointer *const entries[COUNTDOWN_MODES] = {
        &data_ov003_02238ac0, /* CountdownBoard_EnterCounting */
        &data_ov003_02238ac8, /* CountdownBoard_EnterOver */
    };
    MemberTable_InitOnce(&data_ov003_0223c8c4, data_ov003_0223c8c8, entries, COUNTDOWN_MODES);
    if (mode >= COUNTDOWN_MODE_LIMIT) {
        return 0;
    }
    if (MemberPointer_CallInt(&data_ov003_0223c8c8[mode], board) == 0) {
        return 0;
    }
    if (func_020b30e8(board->code, mode) == 0) {
        return 0;
    }
    board->mode = (u8) mode;
    return 1;
}
CLEAN_AS(_ZN18Obj_ov003_02238c5419func_ov003_0221ccb4Ej, CountdownBoard_SetMode)

/* func_ov003_0221cd44 (vtable slot 0xac): overlay 9's.
 * QUIRK: declared without a result here; in the ROM it is a tail call, so the caller gets
 * overlay 9's. The same holds for the two slots below. */
void CountdownBoard_LtTexturePath(CountdownBoard *board)
{
    func_ov009_02264b64(board);
}
CLEAN_AS(func_ov003_0221cd44, CountdownBoard_LtTexturePath)

/* func_ov003_0221cd4c (vtable slot 0xa8): overlay 9's. */
void CountdownBoard_TexturePath(CountdownBoard *board)
{
    func_ov009_02264be0(board);
}
CLEAN_AS(func_ov003_0221cd4c, CountdownBoard_TexturePath)

/* func_ov003_0221cd54 (vtable slot 0xa4): overlay 9's. */
void CountdownBoard_ArchivePath(CountdownBoard *board)
{
    func_ov009_02264c10(board);
}
CLEAN_AS(func_ov003_0221cd54, CountdownBoard_ArchivePath)

/* func_ov003_0221cd5c (vtable slot 0x0c, leaving the scene): forgets its digits; always 1. */
int CountdownBoard_Leave(CountdownBoard *board)
{
    for (int i = 0; i < COUNTDOWN_PLACES; i++) {
        board->digits[i] = NULL;
    }
    return 1;
}
CLEAN_AS(func_ov003_0221cd5c, CountdownBoard_Leave)

/* func_ov003_0221cd7c (vtable slot 0x2c, drawing it): with status 2, unless bit 0 of the flags
 * at 0x235 is set, first draws the model of each digit still running
 * (func_ov009_022632c8); then the actor's own drawing. */
void CountdownBoard_Draw(CountdownBoard *board, int status)
{
    if (status == COUNTDOWN_DRAW_STATUS && !(board->flags_235 & 1)) {
        for (int i = 0; i < COUNTDOWN_PLACES; i++) {
            CountdownDigit *digit = board->digits[i];
            if (digit != NULL && digit->running) {
                func_ov009_022632c8(digit);
            }
        }
    }
    Actor_Draw((Actor *) (void *) board, status);
}
CLEAN_AS(func_ov003_0221cd7c, CountdownBoard_Draw)

/* func_ov003_0221cdcc (vtable slot 0x18, its update): the time left until midnight by the
 * clock, as hours, minutes and seconds, for the digits; always 1.
 * QUIRK: the words are written as the original works them out: the seconds word first holds
 * the whole time left, then what is left after the hours, then after the minutes. */
int CountdownBoard_Update(void)
{
    DateTime now = {0};
    func_0209e474(&now);
    int elapsed = now.minute * 60 + now.hour * 3600 + now.second;
    countdown_seconds = (u32) (COUNTDOWN_SECONDS_PER_DAY - elapsed);
    countdown_hours = countdown_seconds / 3600;
    countdown_seconds -= countdown_hours * 3600;
    countdown_minutes = countdown_seconds / 60;
    countdown_seconds -= countdown_minutes * 60;
    return 1;
}
CLEAN_AS(func_ov003_0221cdcc, CountdownBoard_Update)

/* func_ov003_0221ce40 (vtable slot 0x70, setting it up): works out the time left (vtable slot
 * 0x18), makes the six digits 2.3125 units above it and 0.3125 along z, each told its place
 * through countdown_making_place, hooks its model (func_ov003_0221d038), finds "m_cbs_Adt",
 * binds its animation 0 to the model when it can, and enters COUNTDOWN_OVER in January, else
 * COUNTDOWN_COUNTING (vtable slot 0x6c); always 1. */
int CountdownBoard_Init(CountdownBoard *board)
{
    typedef int (*CountdownUpdateSlot)(CountdownBoard *board);

    func_ov009_02264884(board);
    u32 update = *(const u32 *) ((const u8 *) board->vtable + 0x18);
    ((CountdownUpdateSlot) (uintptr_t) update)(board);

    for (int i = 0; i < COUNTDOWN_PLACES; i++) {
        Vec3 point;
        point.x = board->position.x + data_ov003_0223662c[i];
        point.y = board->position.y + 0x2500;
        point.z = board->position.z + 0x500;
        countdown_making_place = (u8) i;
        int digit = Actor_Spawn(COUNTDOWN_DIGIT_PROFILE, COUNTDOWN_DIGIT_CODE, &point, NULL, NULL);
        board->digits[i] = (CountdownDigit *) (uintptr_t) (u32) digit;
    }

    func_02055dc8(board->model_object, (void *) func_ov003_0221d038, board);
    board->material = (s8) func_02057a50(board->model, data_ov003_02238d90);
    if (func_0205650c(&board->anim, board->model, data_021c9b1c) != 0) {
        func_02056478(&board->anim, func_ov009_02264cf8(board, 0), COUNTDOWN_ANIM_BOARD, COUNTDOWN_ONE, 0);
        func_020563dc(&board->anim, func_02055e00(board->model_object));
    }

    DateTime now = {0};
    func_0209e474(&now);
    if (now.month == COUNTDOWN_NEW_YEAR_MONTH) {
        countdown_board_switch_to(board, COUNTDOWN_OVER);
    } else {
        countdown_board_switch_to(board, COUNTDOWN_COUNTING);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221ce40, CountdownBoard_Init)

/* The board's vtables set back, its animation destroyed, then overlay 9's destructor. */
static void countdown_board_destroy_parts(CountdownBoard *board)
{
    board->vtable = data_ov003_02238c54;
    board->receiver_vtable = data_ov003_02238d18;
    func_020565b0(&board->anim);
    func_ov009_0226539c(board);
}

/* func_ov003_0221cf54 (vtable slot 0x44, the deleting destructor): the destructor's work, then
 * the memory freed. */
CountdownBoard *CountdownBoard_DestroyAndFree(CountdownBoard *board)
{
    countdown_board_destroy_parts(board);
    Heap_FreeAux(board);
    return board;
}
CLEAN_AS(func_ov003_0221cf54, CountdownBoard_DestroyAndFree)

/* func_ov003_0221cf8c (vtable slot 0x40): the destructor. */
CountdownBoard *CountdownBoard_Destroy(CountdownBoard *board)
{
    countdown_board_destroy_parts(board);
    return board;
}
CLEAN_AS(func_ov003_0221cf8c, CountdownBoard_Destroy)

/* func_ov003_0221cfc0: the board's constructor: overlay 9's, the vtables, its animation's; no
 * material yet. */
CountdownBoard *CountdownBoard_Construct(CountdownBoard *board)
{
    func_ov009_0226552c(board);
    board->vtable = data_ov003_02238c54;
    board->receiver_vtable = data_ov003_02238d18;
    func_020565c8(&board->anim);
    board->material = -1;
    return board;
}
CLEAN_AS(func_ov003_0221cfc0, CountdownBoard_Construct)

/* func_ov003_0221cffc: when `material` is "m_cbs_Adt", draws it with the board's alpha. The
 * alpha bits are cleared and then set, in two writes.
 * QUIRK: the alpha is not masked to 5 bits; the board only sets 1 and 31. */
void CountdownBoard_MaterialHook(CountdownBoard *board, int material, CountdownRenderState *state)
{
    if (material == board->material) {
        state->material_result->polygon_attr &= ~COUNTDOWN_ALPHA_MASK;
        state->material_result->polygon_attr |= (u32) board->alpha << COUNTDOWN_ALPHA_SHIFT;
    }
}
CLEAN_AS(func_ov003_0221cffc, CountdownBoard_MaterialHook)

/* func_ov003_0221d038 (the hook func_02055dc8 is given, run before the model is drawn): sets
 * the materials' hook (after each material) to func_ov003_0221d048. */
void CountdownBoard_SetModelHooks(CountdownRenderState *state)
{
    state->hooks[COUNTDOWN_COMMAND_MATERIAL] = (u32) (uintptr_t) func_ov003_0221d048;
    state->hook_timings[COUNTDOWN_COMMAND_MATERIAL] = COUNTDOWN_TIMING_AFTER;
}
CLEAN_AS(func_ov003_0221d038, CountdownBoard_SetModelHooks)

/* func_ov003_0221d048: a material's hook: CountdownBoard_MaterialHook on the board, when the
 * render object has one. */
void CountdownBoard_RunMaterialHook(CountdownRenderState *state)
{
    CountdownBoard *board = state->render_object->board;
    if (board != NULL) {
        CountdownBoard_MaterialHook(board, state->command[1], state);
    }
}
CLEAN_AS(func_ov003_0221d048, CountdownBoard_RunMaterialHook)

/* func_ov003_0221d064 (the digit's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void CountdownDigit_New(void)
{
    CountdownDigit *digit = (CountdownDigit *) (uintptr_t) (u32) CountdownDigit_Alloc(sizeof(CountdownDigit));
    if (digit != NULL) {
        CountdownDigit_Construct(digit);
    }
}
CLEAN_AS(func_ov003_0221d064, CountdownDigit_New)

/* func_ov003_0221d080 (the board's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void CountdownBoard_New(void)
{
    CountdownBoard *board = Heap_AllocAuxZeroed(sizeof(CountdownBoard));
    if (board != NULL) {
        CountdownBoard_Construct(board);
    }
}
CLEAN_AS(func_ov003_0221d080, CountdownBoard_New)

/* ---- The receiver vtables' thunks: each finds the object around `receiver`. */

static CountdownBoard *countdown_board_from_receiver(void *receiver)
{
    return (CountdownBoard *) (void *) ((u8 *) receiver - COUNTDOWN_RECEIVER_OFFSET);
}

static CountdownDigit *countdown_digit_from_receiver(void *receiver)
{
    return (CountdownDigit *) (void *) ((u8 *) receiver - COUNTDOWN_RECEIVER_OFFSET);
}

/* _ZThn236_N18Obj_ov003_02238c54D0Ev: CountdownBoard_DestroyAndFree. */
CountdownBoard *CountdownBoard_ReceiverDestroyAndFree(void *receiver)
{
    return CountdownBoard_DestroyAndFree(countdown_board_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238c54D0Ev, CountdownBoard_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_02238c54D1Ev: CountdownBoard_Destroy. */
CountdownBoard *CountdownBoard_ReceiverDestroy(void *receiver)
{
    return CountdownBoard_Destroy(countdown_board_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238c54D1Ev, CountdownBoard_ReceiverDestroy)

/* _ZThn236_N18Obj_ov003_02238b10D0Ev: CountdownDigit_DestroyAndFree. */
CountdownDigit *CountdownDigit_ReceiverDestroyAndFree(void *receiver)
{
    return CountdownDigit_DestroyAndFree(countdown_digit_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238b10D0Ev, CountdownDigit_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_02238b10D1Ev: CountdownDigit_Destroy. */
CountdownDigit *CountdownDigit_ReceiverDestroy(void *receiver)
{
    return CountdownDigit_Destroy(countdown_digit_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238b10D1Ev, CountdownDigit_ReceiverDestroy)
