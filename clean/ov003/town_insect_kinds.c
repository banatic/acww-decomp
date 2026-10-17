/* The start and update functions of the town insects' kinds (town_insect_kinds.h). */
#include "town_insect_kinds.h"

#include "clean.h"
#include "main/field_collision.h"
#include "main/frame_ctrl.h"
#include "main/main_random.h"
#include "main/model_pool.h"
#include "ov003/town_insect_moves.h"

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void NNS_G3dMdlSetMdlAlpha(void *model, int material, int alpha);

/* The behaviours the update functions pass the insect on to. */
extern void func_ov003_02231e24(TownInsect *insect);
extern void func_ov003_022325d4(TownInsect *insect);
extern void func_ov003_022334d8(TownInsect *insect);
extern void func_ov003_02232640(TownInsect *insect);
extern void func_ov003_02231f20(TownInsect *insect);
extern void func_ov003_02232874(TownInsect *insect);
extern void func_ov003_022335cc(TownInsect *insect);
extern void func_ov003_02233674(TownInsect *insect);
extern void func_ov003_02232d30(TownInsect *insect);
extern void func_ov003_0223345c(TownInsect *insect);
extern void func_ov003_022314fc(TownInsect *insect);
extern void func_ov003_02233930(TownInsect *insect);
extern void func_ov003_02234600(TownInsect *insect);
extern void func_ov003_02233d68(TownInsect *insect);
extern void func_ov003_02233890(TownInsect *insect);
extern void func_ov003_022337d8(TownInsect *insect);
extern void func_ov003_02232a44(TownInsect *insect);
/* The box the insect keeps to (its words 0x1b0-0x1c7), set around where it is by its kind. */
extern void func_ov003_02230f88(TownInsect *insect);
/* The insect moved to a side of where it is, at random, and 3.0 up. */
extern void func_ov003_0223108c(TownInsect *insect);

/* An insect that is let go (TOWN_INSECT_ACTION_LET_GO) or hidden keeps its action, its angle
 * about y and its position when it begins. */
static int town_insect_kinds_placed(const TownInsect *insect)
{
    return insect->action != TOWN_INSECT_ACTION_LET_GO && insect->action != TOWN_INSECT_ACTION_HIDDEN;
}

static void town_insect_kinds_fade(TownInsect *insect)
{
    NNS_G3dMdlSetMdlAlpha((void *) (uintptr_t) ModelPoolFiles_Model(&insect->files), 0, 0);
}

/* func_ov003_02230180 (kind 0x38's update). */
void TownInsectKind_Update38(TownInsect *insect)
{
    func_ov003_02231e24(insect);
}
CLEAN_AS(func_ov003_02230180, TownInsectKind_Update38)

/* func_ov003_02230188 (kind 0x38's start): as the leaning kinds' (its default). */
void TownInsectKind_Start38(TownInsect *insect)
{
    TownInsectKind_StartLeaning(insect);
}
CLEAN_AS(func_ov003_02230188, TownInsectKind_Start38)

/* func_ov003_02230190 (kind 0x23's update). */
void TownInsectKind_Update23(TownInsect *insect)
{
    func_ov003_022325d4(insect);
}
CLEAN_AS(func_ov003_02230190, TownInsectKind_Update23)

/* func_ov003_02230198 (kind 0x23's start). */
void TownInsectKind_Start23(TownInsect *insect)
{
    TownInsectKind_Begin(insect, 0, 0x50, 0x50, 0, 0, 0, 0, 3, 0);
}
CLEAN_AS(func_ov003_02230198, TownInsectKind_Start23)

/* func_ov003_022301bc (kinds 0x18 and 0x3b's update). */
void TownInsectKind_Update18(TownInsect *insect)
{
    func_ov003_022334d8(insect);
}
CLEAN_AS(func_ov003_022301bc, TownInsectKind_Update18)

/* func_ov003_022301c4 (kinds 0x18 and 0x3b's start). */
void TownInsectKind_Start18(TownInsect *insect)
{
    TownInsectKind_Begin(insect, 0, 0x50, 0x50, 0, 0, 0, 0, 1, 0);
}
CLEAN_AS(func_ov003_022301c4, TownInsectKind_Start18)

/* func_ov003_022301e8 (kind 0x37's start): its byte 0x24c cleared and its model's animation
 * started over (3 frames, looping, at speed 1.0). */
void TownInsectKind_Start37(TownInsect *insect)
{
    TownInsectKind_Begin(insect, 0, 0x64, 0x50, 0, 0, 0, 0, 5, 0);
    insect->unk_24c = 0;
    FrameCtrl_Init(&insect->model.frames, 3, 0, 0x1000, 0);
}
CLEAN_AS(func_ov003_022301e8, TownInsectKind_Start37)

/* func_ov003_0223022c (kind 0x36's start): its byte 0x24c cleared. */
void TownInsectKind_Start36(TownInsect *insect)
{
    TownInsectKind_Begin(insect, 0, 0x64, 0x5a, 0, 0, 0, 0, 4, 0);
    insect->unk_24c = 0;
}
CLEAN_AS(func_ov003_0223022c, TownInsectKind_Start36)

/* func_ov003_0223025c (kinds 0x36 and 0x37's update). */
void TownInsectKind_Update36(TownInsect *insect)
{
    func_ov003_02232640(insect);
}
CLEAN_AS(func_ov003_0223025c, TownInsectKind_Update36)

/* func_ov003_02230264 (kind 0x35's update). */
void TownInsectKind_Update35(TownInsect *insect)
{
    func_ov003_02231f20(insect);
}
CLEAN_AS(func_ov003_02230264, TownInsectKind_Update35)

/* func_ov003_0223026c (kind 0x35's start): a word 0x244 of 20 times 5-15. Placed, it keeps its x
 * in the word 0x21c, fades out and moves 0.5 back along z; let go or hidden, it turns a quarter
 * turn back about x and its angle about z becomes its angle about y. */
void TownInsectKind_Start35(TownInsect *insect)
{
    short steps = (short) (MainRandom_Below(11) + 5);
    TownInsectKind_Begin(insect, (short) (20 * steps), 0x5a, 0x40, 0, 0, 0x28, 0, 3, 0);
    if (town_insect_kinds_placed(insect)) {
        insect->unk_21c = insect->position.x;
        town_insect_kinds_fade(insect);
        insect->position.z -= 0x7d0;
    } else {
        insect->angle_x = -0x4000;
        insect->angle_z = insect->angle_y;
    }
}
CLEAN_AS(func_ov003_0223026c, TownInsectKind_Start35)

/* func_ov003_0223030c (kind 0x30's update). */
void TownInsectKind_Update30(TownInsect *insect)
{
    func_ov003_02232874(insect);
}
CLEAN_AS(func_ov003_0223030c, TownInsectKind_Update30)

/* func_ov003_02230314 (kind 0x30's start): on the ground; the word 0x21c takes its byte 0x257
 * (8) and the word 0x228 its height. */
void TownInsectKind_Start30(TownInsect *insect)
{
    TownInsectKind_Begin(insect, 0, 0x5a, 0x3c, 0, 0, 0x3c, 0, 8, 1);
    insect->unk_21c = insect->unk_257;
    insect->unk_228 = insect->position.y;
}
CLEAN_AS(func_ov003_02230314, TownInsectKind_Start30)

/* func_ov003_0223035c (kind 0x33's update). */
void TownInsectKind_Update33(TownInsect *insect)
{
    func_ov003_022335cc(insect);
}
CLEAN_AS(func_ov003_0223035c, TownInsectKind_Update33)

/* func_ov003_02230364 (kind 0x33's start): with its box (func_ov003_02230f88). */
void TownInsectKind_Start33(TownInsect *insect)
{
    TownInsectKind_BeginPaced(insect, 0x96, 0x1e, 0x25, 0x12, 0x1000);
    func_ov003_02230f88(insect);
}
CLEAN_AS(func_ov003_02230364, TownInsectKind_Start33)

/* func_ov003_02230390 (kind 0xa's update). */
void TownInsectKind_Update0A(TownInsect *insect)
{
    func_ov003_022335cc(insect);
}
CLEAN_AS(func_ov003_02230390, TownInsectKind_Update0A)

/* func_ov003_02230398 (kind 0xa's start): with its box (func_ov003_02230f88). */
void TownInsectKind_Start0A(TownInsect *insect)
{
    TownInsectKind_BeginPaced(insect, 0xc8, 0x3c, 0x25, 9, 0x1000);
    func_ov003_02230f88(insect);
}
CLEAN_AS(func_ov003_02230398, TownInsectKind_Start0A)

/* func_ov003_022303c4 (kinds 0xb and 0x3a's update). */
void TownInsectKind_Update0B(TownInsect *insect)
{
    func_ov003_02233674(insect);
}
CLEAN_AS(func_ov003_022303c4, TownInsectKind_Update0B)

/* func_ov003_022303cc (kinds 0xb and 0x3a's start): one still shown fades out first; its word
 * 0x21c is cleared. */
void TownInsectKind_Start0B(TownInsect *insect)
{
    if (insect->action == TOWN_INSECT_ACTION_SHOWN) {
        town_insect_kinds_fade(insect);
    }
    TownInsectKind_Begin(insect, 0, 0x5a, 0x3c, 0, 0, 2, 0, 0, 0);
    insect->unk_21c = 0;
}
CLEAN_AS(func_ov003_022303cc, TownInsectKind_Start0B)

/* func_ov003_02230420 (kind 0x31's update). */
void TownInsectKind_Update31(TownInsect *insect)
{
    func_ov003_02232d30(insect);
}
CLEAN_AS(func_ov003_02230420, TownInsectKind_Update31)

/* func_ov003_02230428 (kind 0x1e's update). */
void TownInsectKind_Update1E(TownInsect *insect)
{
    func_ov003_0223345c(insect);
}
CLEAN_AS(func_ov003_02230428, TownInsectKind_Update1E)

/* func_ov003_02230430 (kinds 0x1e and 0x31's start): its timer at 360 (what TownInsect_CountDown
 * runs down); placed, it fades out. */
void TownInsectKind_Start1E(TownInsect *insect)
{
    if (insect->kind == 0x1e) {
        TownInsectKind_Begin(insect, 0, 0x28, 0x50, 0, 0, 0, 0, 4, 0);
    } else {
        TownInsectKind_Begin(insect, 0, 0xdc, 0x3c, 0, 0, 0, 0, 1, 0);
    }
    insect->timer = 360;
    if (town_insect_kinds_placed(insect)) {
        town_insect_kinds_fade(insect);
    }
}
CLEAN_AS(func_ov003_02230430, TownInsectKind_Start1E)

/* func_ov003_022304b0 (kinds 0xe, 0xf, 0x1a and 0x20's start); kinds 0xe and 0xf also start
 * their model's animation again, once and backwards, at frame 1 and a frame count of 0. */
void TownInsectKind_StartInArea(TownInsect *insect)
{
    switch (insect->kind) {
        case 0x1a:
            TownInsectKind_BeginInArea(insect, 0xc8, 0x3c, 4, 0x38e);
            break;
        case 0x20:
            TownInsectKind_BeginInArea(insect, 0x82, 0x3c, 0x10, 0x71c);
            break;
        case 0xe:
        case 0xf:
            TownInsectKind_BeginInArea(insect, 0x96, 0x32, 0x18, 0x71c);
            FrameCtrl_Init(&insect->model.frames, 0, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, 1);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_022304b0, TownInsectKind_StartInArea)

/* func_ov003_02230554 (kinds 0xe, 0xf, 0x1a and 0x20's update). */
void TownInsectKind_UpdateInArea(TownInsect *insect)
{
    func_ov003_022314fc(insect);
}
CLEAN_AS(func_ov003_02230554, TownInsectKind_UpdateInArea)

/* func_ov003_0223055c: begins turned a random way, 14/16 up, with its box (func_ov003_02230f88);
 * unless let go, moved to a random side of where it is (func_ov003_0223108c); the word 0x21c
 * takes `pace`. */
void TownInsectKind_BeginInArea(TownInsect *insect, int reached, int reach, int byte257, s16 pace)
{
    short angle = TownInsectKind_RandomAngle();
    TownInsectKind_Begin(insect, 0, (u8) reached, reach, 0, angle, 0xe, 0, (u8) byte257, 0);
    func_ov003_02230f88(insect);
    if (insect->action != TOWN_INSECT_ACTION_LET_GO) {
        func_ov003_0223108c(insect);
    }
    insect->unk_21c = pace;
}
CLEAN_AS(func_ov003_0223055c, TownInsectKind_BeginInArea)

/* func_ov003_022305b4 (kind 0x19's update). */
void TownInsectKind_Update19(TownInsect *insect)
{
    func_ov003_02233930(insect);
}
CLEAN_AS(func_ov003_022305b4, TownInsectKind_Update19)

/* func_ov003_022305bc (kind 0x19's start): on the ground, with its box, its timer 3 times 0-19. */
void TownInsectKind_Start19(TownInsect *insect)
{
    TownInsectKind_Begin(insect, 0, 0x28, 0x50, 0, 0, 0, 0, 3, 1);
    func_ov003_02230f88(insect);
    insect->timer = (s16) (3 * MainRandom_Below(20));
}
CLEAN_AS(func_ov003_022305bc, TownInsectKind_Start19)

/* func_ov003_022305fc (kinds 0x15-0x17's update). */
void TownInsectKind_UpdateTurned(TownInsect *insect)
{
    func_ov003_02234600(insect);
}
CLEAN_AS(func_ov003_022305fc, TownInsectKind_UpdateTurned)

/* func_ov003_02230604 (kinds 0x15-0x17's start). */
void TownInsectKind_StartTurned(TownInsect *insect)
{
    switch (insect->kind) {
        case 0x15:
            TownInsectKind_BeginTurned(insect, 0xc8, 0x3c, 0x28, 0x14, 1);
            break;
        case 0x16:
            TownInsectKind_BeginTurned(insect, 0xc8, 0x28, 0x2d, 0x1e, 3);
            break;
        case 0x17:
            TownInsectKind_BeginTurned(insect, 0x64, 0x46, 0x32, 0x78, 0x1e);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02230604, TownInsectKind_StartTurned)

/* func_ov003_02230660: begins turned a random way at `height` sixteenths up, with its byte
 * 0x259. */
void TownInsectKind_BeginTurned(TownInsect *insect, int reached, int reach, int height, u8 byte257, u8 byte259)
{
    short angle = TownInsectKind_RandomAngle();
    TownInsectKind_Begin(insect, 0, (u8) reached, reach, 0, angle, height, 0, byte257, 0);
    insect->unk_259 = byte259;
}
CLEAN_AS(func_ov003_02230660, TownInsectKind_BeginTurned)

/* func_ov003_022306a0 (kinds 0xc, 0xd and 0x1b-0x1d's start). */
void TownInsectKind_StartWaiting(TownInsect *insect)
{
    switch (insect->kind) {
        case 0x1d:
        case 0x1b:
            TownInsectKind_BeginWaiting(insect, 0x3c, 0x46, 6, 1);
            break;
        case 0xc:
            TownInsectKind_BeginWaiting(insect, 0x3c, 0x50, 8, 2);
            break;
        case 0xd:
            TownInsectKind_BeginWaiting(insect, 0x3c, 0x50, 8, 3);
            break;
        case 0x1c:
            TownInsectKind_BeginWaiting(insect, 0x3c, 0x46, 8, 1);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_022306a0, TownInsectKind_StartWaiting)

/* func_ov003_0223072c (kinds 0xc, 0xd and 0x1b-0x1d's update). */
void TownInsectKind_UpdateWaiting(TownInsect *insect)
{
    func_ov003_02233d68(insect);
}
CLEAN_AS(func_ov003_0223072c, TownInsectKind_UpdateWaiting)

/* func_ov003_02230734: begins turned a random way with a word 0x244 of 0x3b6, its timer 20 times
 * 2-10, its byte 0x259, and its y 0. */
void TownInsectKind_BeginWaiting(TownInsect *insect, int reached, int reach, int byte257, u8 byte259)
{
    short angle = TownInsectKind_RandomAngle();
    TownInsectKind_Begin(insect, 0x3b6, (u8) reached, reach, 0, angle, 0, 0, (u8) byte257, 0);
    insect->timer = (s16) (20 * (MainRandom_Below(9) + 2));
    insect->unk_259 = byte259;
    insect->position.y = 0;
}
CLEAN_AS(func_ov003_02230734, TownInsectKind_BeginWaiting)

/* func_ov003_02230794 (the start of kinds 9, 0x10-0x14, 0x1f, 0x21, 0x22, 0x24, 0x26-0x2f and
 * 0x34, and of kind 0x38): kind 0x1f also with its byte 0x257 at 1, kind 9 at 0xa with its
 * model's animation started again to play once, kind 0x14 with its byte 0x252 cleared. */
void TownInsectKind_StartLeaning(TownInsect *insect)
{
    switch (insect->kind) {
        case 0x21:
        case 0x22:
        case 0x24:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2a:
        case 0x2b:
        case 0x2c:
        case 0x2d:
        case 0x2e:
        case 0x2f:
        case 0x34:
            TownInsectKind_BeginLeaning(insect, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x1f:
            TownInsectKind_BeginLeaning(insect, 0xfa, 0x50, 0x16, 500);
            insect->unk_257 = 1;
            break;
        case 9: {
            TownInsectKind_BeginLeaning(insect, 0x96, 0x46, 0x18, 1000);
            insect->unk_257 = 0xa;
            /* the whole frames of the frame count, as 16 bits */
            u32 last = ((u32) insect->model.frames.end << 4) >> 16;
            FrameCtrl_Init(&insect->model.frames, last, FRAME_CTRL_ONCE, 0x1000, 0);
            break;
        }
        case 0x14:
            TownInsectKind_BeginLeaning(insect, 0x64, 0x50, 0x19, 1000);
            insect->unk_252 = 0;
            break;
        default:
            TownInsectKind_BeginLeaning(insect, 0x64, 0x50, 0x19, 1000);
            break;
    }
}
CLEAN_AS(func_ov003_02230794, TownInsectKind_StartLeaning)

/* func_ov003_022309b8 (the leaning kinds' update, as kind 0x38's). */
void TownInsectKind_UpdateLeaning(TownInsect *insect)
{
    func_ov003_02231e24(insect);
}
CLEAN_AS(func_ov003_022309b8, TownInsectKind_UpdateLeaning)

/* func_ov003_022309c0: begins leaning 0x3556 about x, turned half a turn about y, `height`
 * sixteenths up and `forward` further along z, with its byte 0x246 set; kind 0x1f let go begins
 * level instead, where it is. */
void TownInsectKind_BeginLeaning(TownInsect *insect, int reached, int reach, int height, int forward)
{
    if (insect->kind == 0x1f && insect->action == TOWN_INSECT_ACTION_LET_GO) {
        TownInsectKind_Begin(insect, 0, (u8) reached, reach, 0, 0, 0, 0, 0, 0);
    } else {
        TownInsectKind_Begin(insect, 0, (u8) reached, reach, 0x3556, -0x8000, height, 0, 0, 0);
        insect->position.z += forward;
        insect->unk_246 = 1;
    }
}
CLEAN_AS(func_ov003_022309c0, TownInsectKind_BeginLeaning)

/* func_ov003_02230a40 (kind 0x32's update). */
void TownInsectKind_Update32(TownInsect *insect)
{
    func_ov003_02233890(insect);
}
CLEAN_AS(func_ov003_02230a40, TownInsectKind_Update32)

/* func_ov003_02230a48 (kind 0x32's start). */
void TownInsectKind_Start32(TownInsect *insect)
{
    TownInsectKind_Begin(insect, 0, 0, 0, 0, 0, 0x19, 0, 0x19, 0);
}
CLEAN_AS(func_ov003_02230a48, TownInsectKind_Start32)

/* func_ov003_02230a6c (kinds 0x25 and 0x39's update). */
void TownInsectKind_Update25(TownInsect *insect)
{
    func_ov003_022337d8(insect);
}
CLEAN_AS(func_ov003_02230a6c, TownInsectKind_Update25)

/* func_ov003_02230a74 (kinds 0x25 and 0x39's start): on the ground, keeping its word 0x21c
 * (kind 0x39's effect started), with its byte 0x252 at 60. */
void TownInsectKind_Start25(TownInsect *insect)
{
    int kept = insect->unk_21c;
    TownInsectKind_Begin(insect, 0, 0x5a, 0x3c, 0, 0, 0x3c, 0, 6, 1);
    insect->unk_21c = kept;
    insect->unk_252 = 0x3c;
}
CLEAN_AS(func_ov003_02230a74, TownInsectKind_Start25)

/* func_ov003_02230ab4 (kind 8's start): turned half a turn about y and by 1 about x, a word 0x244
 * of 0x384, its byte 0x252 at 60, its byte 0x256 at random 0-17, its byte 0x24c set, its word
 * 0x220 cleared; where it begins is kept at 0x1e0, and its animation runs at speed 1.0. */
void TownInsectKind_Start08(TownInsect *insect)
{
    TownInsectKind_Begin(insect, 0x384, 0xc8, 0x28, 1, -0x8000, 0x2f, 0, 0xa, 0);
    insect->unk_252 = 0x3c;
    insect->unk_256 = (u8) MainRandom_Below(0x12);
    insect->unk_24c = 1;
    insect->unk_220 = 0;
    insect->unk_1e0.x = insect->position.x;
    insect->unk_1e0.y = insect->position.y;
    insect->unk_1e0.z = insect->position.z;
    TownInsect_SetAnimSpeed(insect, 0x1000);
}
CLEAN_AS(func_ov003_02230ab4, TownInsectKind_Start08)

/* func_ov003_02230b40 (kind 8's update). */
void TownInsectKind_Update08(TownInsect *insect)
{
    func_ov003_02232a44(insect);
}
CLEAN_AS(func_ov003_02230b40, TownInsectKind_Update08)

/* func_ov003_02230b48 (kinds 0-7's start). */
void TownInsectKind_Start00To07(TownInsect *insect)
{
    switch (insect->kind) {
        case 0:
        case 1:
            TownInsectKind_BeginPaced(insect, 0x64, 0x50, 0x25, 8, 0x119a);
            break;
        case 2:
        case 3:
            TownInsectKind_BeginPaced(insect, 0x50, 0x50, 0x28, 9, 0x1000);
            break;
        case 4:
            TownInsectKind_BeginPaced(insect, 0x3c, 0x50, 0x2f, 0xa, 0xe66);
            break;
        case 5:
            TownInsectKind_BeginPaced(insect, 0x46, 0x50, 0x14, 0xc, 0x1000);
            break;
        case 6:
            TownInsectKind_BeginPaced(insect, 0x64, 0x1e, 0x32, 0xf, 0x1000);
            break;
        case 7:
            TownInsectKind_BeginPaced(insect, 0x3c, 0x50, 0x34, 0xc, 0x1000);
            break;
        default:
            TownInsectKind_BeginPaced(insect, 0x3c, 0x50, 0x2d, 0xa, 0x1000);
            break;
    }
}
CLEAN_AS(func_ov003_02230b48, TownInsectKind_Start00To07)

/* func_ov003_02230c3c: begins turned a random way with a word 0x244 of 20 times 5-7, `height`
 * sixteenths up, its byte 0x252 at 40, its byte 0x256 at random 0-17, its byte 0x24c set, the
 * word 0x21c at `pace` and its timer at 0. */
void TownInsectKind_BeginPaced(TownInsect *insect, int reached, int reach, int height, u8 byte257, int pace)
{
    unsigned int steps = MainRandom_Below(3);
    short angle = TownInsectKind_RandomAngle();
    TownInsectKind_Begin(insect, (short) (20 * (steps + 5)), (u8) reached, reach, 0, angle, height, 0, byte257, 0);
    insect->unk_252 = 0x28;
    insect->unk_256 = (u8) MainRandom_Below(0x12);
    insect->unk_24c = 1;
    insect->unk_21c = pace;
    insect->timer = 0;
}
CLEAN_AS(func_ov003_02230c3c, TownInsectKind_BeginPaced)

/* func_ov003_02230cb8 (kinds 0-7's update). */
void TownInsectKind_Update00To07(TownInsect *insect)
{
    TownInsectMove_Update00To07(insect);
}
CLEAN_AS(func_ov003_02230cb8, TownInsectKind_Update00To07)

/* func_ov003_02230cc0: an angle of 0-8 steps of 0xaaa (15 degrees) either way, at random: 0-8
 * as drawn, 9-15 as 1-7 steps the other way. */
short TownInsectKind_RandomAngle(void)
{
    u8 drawn = (u8) MainRandom_Below(0x10);
    int steps = drawn > 8 ? -(drawn - 8) : drawn;
    return (short) (0xaaa * steps);
}
CLEAN_AS(func_ov003_02230cc0, TownInsectKind_RandomAngle)

/* func_ov003_02230ce8: an insect begins its behaviour. Unless let go or hidden, it is shown,
 * turned to `angle_y`, its point (TownInsect.target) is where it was, and its y becomes `height`
 * sixteenths of 1.0, over the ground's word 0x3c (CollisionGround.limit) when `on_ground`. Then:
 * its angle about x, its byte 0x255 at `reached` (what byte 0x254 must reach), its reach
 * `reach` sixteenths of 1.0, its word 0x21c cleared but for kind 0x23 (its snowball), its byte
 * 0x257, the words 0x23e and 0x236 and the bytes 0x254 and 0x24e cleared, the words 0x228 and
 * 0x220 at its y plus `above`, the word 0x244, and its scale 1.0. */
void TownInsectKind_Begin(TownInsect *insect, short unk_244, u8 reached, int reach, short angle_x, short angle_y, int height,
                          int above, u8 byte257, u8 on_ground)
{
    CollisionGround ground;
    CollisionGround_Init(&ground, &insect->position, 0, 0);
    fx32 y = FX_Div((fx32) ((u32) height << 12), 0x10000);
    fx32 reach_fx = FX_Div((fx32) ((u32) reach << 12), 0x10000);
    if (town_insect_kinds_placed(insect)) {
        insect->action = TOWN_INSECT_ACTION_SHOWN;
        insect->angle_y = angle_y;
        /* a word at a time, as the original copies */
        insect->target.x = insect->position.x;
        insect->target.y = insect->position.y;
        insect->target.z = insect->position.z;
        insect->position.y = on_ground != 0 ? y + ground.limit : y;
    }
    insect->angle_x = angle_x;
    insect->unk_255 = reached;
    insect->reach = reach_fx;
    if (insect->kind != 0x23) {
        insect->unk_21c = 0;
    }
    insect->unk_257 = byte257;
    insect->unk_23e = 0;
    insect->unk_254 = 0;
    insect->unk_228 = insect->position.y + above;
    insect->unk_244 = unk_244;
    insect->scale.x = 0x1000;
    insect->scale.y = 0x1000;
    insect->scale.z = 0x1000;
    insect->unk_220 = insect->unk_228;
    insect->unk_236 = 0;
    insect->unk_24e = 0;
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_ov003_02230ce8, TownInsectKind_Begin)
