/* The countdown board of overlay 3 and its six digits: a board that shows the time left until
 * midnight as HH:MM:SS, and stops once the clock's month is January. The material
 * "m_cbs_Adt" of its model is drawn opaque while it counts and nearly transparent after.
 *
 * The board (class Obj_ov003_02238c54, vtable 0x02238c54, receiver part 0x02238d18, 0x2f0
 * bytes) works out the time left every frame (vtable slot 0x18) into three words of the
 * overlay that the digits read. Set up (slot 0x70), it makes six digits (profile 0x26) in a row
 * in front of it, and starts in mode 0 or, in January, mode 1. Its mode (overlay 9's byte at
 * 0x134) runs through two tables of member pointers (ov004/member_pointer.h):
 *
 *   0 counting: its animation goes on; once the month is January it plays sound 0x61 and
 *               moves to mode 1. Entering it plays animation 0 and makes "m_cbs_Adt" opaque.
 *   1 over:     its animation goes on. Entering it plays animation 1 and makes "m_cbs_Adt"
 *               nearly transparent (alpha 1).
 *
 * A digit (class Obj_ov003_02238b10, vtable 0x02238b10, receiver part 0x02238bd4, 0x2dc bytes)
 * shows one place of the time left by the frame of its animation. In the last minute, each
 * change of the last place plays a sound: 0x60 for the last ten seconds, else 0x62. Digits come
 * from main's heap at data_021c9b1c and are never freed (their operator delete is empty).
 *
 * Both are derived from overlay 9's scene actor (Obj_ov009_022658dc), which runs the rest. */
#ifndef CLEAN_OV003_COUNTDOWN_H
#define CLEAN_OV003_COUNTDOWN_H

#include "autoload_2/vector.h" /* Vec3 */
#include "types.h"

/* An animation of main (Obj_020dd154, 0x20 bytes; destructor func_020565b0, constructor
 * func_020565c8): `frame` is copied to `target` once it is bound to a model. */
typedef struct CountdownAnim {
    const void *vtable;
    u8 unk_04[4];
    u32 frame; /* in 20.12 fixed point */
    u8 unk_0C[0xc];
    u32 *target;
    u32 unk_1C;
} CountdownAnim;

/* The places of a digit, left to right. */
enum CountdownPlace {
    COUNTDOWN_HOUR_TENS,
    COUNTDOWN_HOUR_ONES,
    COUNTDOWN_MINUTE_TENS,
    COUNTDOWN_MINUTE_ONES,
    COUNTDOWN_SECOND_TENS,
    COUNTDOWN_SECOND_ONES,
    COUNTDOWN_PLACES
};

typedef struct CountdownDigit {
    const void *vtable; /* data_ov003_02238b10 */
    u8 unk_04[0xec - 0x04];
    const void *receiver_vtable; /* data_ov003_02238bd4 */
    u8 unk_F0[0x13c - 0xf0];
    u8 model_object[0x198 - 0x13c]; /* main's model object (Obj_020dd05c) */
    void *model;                    /* the model object's */
    u8 unk_19C[0x2b4 - 0x19c];
    u8 place; /* enum CountdownPlace */
    u8 value; /* what it shows: the frame of its animation */
    u8 shown; /* the value at the end of the last update; 0xff before the first */
    u8 unk_2B7;
    CountdownAnim anim;
    u8 running; /* cleared once the month is January */
    u8 quiet;   /* the next change plays no sound */
    u8 unk_2DA[2];
} CountdownDigit;

/* The board's modes (overlay 9's byte at 0x134). */
enum CountdownMode { COUNTDOWN_COUNTING, COUNTDOWN_OVER, COUNTDOWN_MODES };

typedef struct CountdownBoard {
    const void *vtable; /* data_ov003_02238c54 */
    u8 unk_04[0x5c - 0x04];
    Vec3 position;
    u8 unk_68[0xec - 0x68];
    const void *receiver_vtable; /* data_ov003_02238d18 */
    u8 unk_F0[0x134 - 0xf0];
    u8 mode; /* enum CountdownMode */
    u8 unk_135;
    u16 code; /* the special character's code main keeps the mode under */
    u8 unk_138[0x13c - 0x138];
    u8 model_object[0x198 - 0x13c]; /* main's model object (Obj_020dd05c) */
    void *model;                    /* the model object's */
    u8 unk_19C[0x235 - 0x19c];
    u8 flags_235; /* bit 0: the digits are not drawn */
    u8 unk_236[0x2b4 - 0x236];
    CountdownAnim anim;
    s8 material; /* the index of "m_cbs_Adt" in the model, -1 until set up */
    u8 alpha;    /* the alpha "m_cbs_Adt" is drawn with (0 to 31) */
    u8 unk_2D6[2];
    CountdownDigit *digits[COUNTDOWN_PLACES];
} CountdownBoard;

/* What the model's hooks get: the state of the model being drawn (NitroSystem's NNSG3dRS). */
typedef struct CountdownRenderObject {
    u8 unk_00[0x2c];
    CountdownBoard *board; /* the object func_02055dc8 was given */
} CountdownRenderObject;

typedef struct CountdownMaterialResult {
    u32 flags;
    u32 color0;
    u32 color1;
    u32 polygon_attr; /* bits 16-20: the alpha */
} CountdownMaterialResult;

typedef struct CountdownRenderState {
    const u8 *command; /* the command being run: byte 1 is its material */
    CountdownRenderObject *render_object;
    u32 flags;
    u32 hooks[0x20]; /* the address of each command's hook, 0 for none */
    u8 hook_timings[0x20];
    u8 unk_AC[4];
    CountdownMaterialResult *material_result;
} CountdownRenderState;

int CountdownDigit_Slot0B0(void);
void CountdownDigit_Tick(CountdownDigit *digit);
int CountdownDigit_Update(CountdownDigit *digit);
int CountdownDigit_Init(CountdownDigit *digit);
void CountdownDigit_Delete(void *digit);
int CountdownDigit_Alloc(int size);
CountdownDigit *CountdownDigit_DestroyAndFree(CountdownDigit *digit);
CountdownDigit *CountdownDigit_Destroy(CountdownDigit *digit);
CountdownDigit *CountdownDigit_Construct(CountdownDigit *digit);
void CountdownBoard_RunOver(CountdownBoard *board);
int CountdownBoard_EnterOver(CountdownBoard *board);
void CountdownBoard_RunCounting(CountdownBoard *board);
int CountdownBoard_EnterCounting(CountdownBoard *board);
void CountdownBoard_RunMode(CountdownBoard *board);
int CountdownBoard_SetMode(CountdownBoard *board, unsigned int mode);
void CountdownBoard_LtTexturePath(CountdownBoard *board);
void CountdownBoard_TexturePath(CountdownBoard *board);
void CountdownBoard_ArchivePath(CountdownBoard *board);
int CountdownBoard_Leave(CountdownBoard *board);
void CountdownBoard_Draw(CountdownBoard *board, int status);
int CountdownBoard_Update(void);
int CountdownBoard_Init(CountdownBoard *board);
CountdownBoard *CountdownBoard_DestroyAndFree(CountdownBoard *board);
CountdownBoard *CountdownBoard_Destroy(CountdownBoard *board);
CountdownBoard *CountdownBoard_Construct(CountdownBoard *board);
void CountdownBoard_MaterialHook(CountdownBoard *board, int material, CountdownRenderState *state);
void CountdownBoard_SetModelHooks(CountdownRenderState *state);
void CountdownBoard_RunMaterialHook(CountdownRenderState *state);
void CountdownDigit_New(void);
void CountdownBoard_New(void);
CountdownBoard *CountdownBoard_ReceiverDestroyAndFree(void *receiver);
CountdownBoard *CountdownBoard_ReceiverDestroy(void *receiver);
CountdownDigit *CountdownDigit_ReceiverDestroyAndFree(void *receiver);
CountdownDigit *CountdownDigit_ReceiverDestroy(void *receiver);

#endif
