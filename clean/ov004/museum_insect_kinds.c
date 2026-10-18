/* Some kinds of the museum's insects (museum_insect_kinds.h). */
#include "museum_insect_kinds.h"

#include "clean.h"
#include "main/animated_model.h"
#include "main/frame_ctrl.h"
#include "main/main_random.h"
#include "main/model_pool.h"
#include "museum_insect_motions.h"

/* The motions shared by several kinds are in museum_insect_motions.h. */

extern void NNS_G3dMdlSetMdlAlpha(int model, int material, int alpha);

/* The rest an insect starts in, in frames: 20 times a random count from `low`, `count`
 * values. */
static s16 rest_frames(int count, int low)
{
    return (s16) (20 * ((int) MainRandom_Below(count) + low));
}

/* The bounds most kinds of the second room keep within. */
static void InsectKind_room_bounds(MuseumInsect *insect)
{
    int low[2] = {0x104, 0xc2};
    int high[2] = {0x1be, 0x15a};
    InsectMotion_SetBounds(insect, low, high);
}

/* A rest of 20-120 frames awake, 100-680 asleep. */
static s16 InsectKind_pair_rest(const MuseumInsect *insect)
{
    return insect->awake ? rest_frames(6, 1) : rest_frames(30, 5);
}

/* func_ov004_02240124 (kinds 35 and 56's frame) */
void InsectKind_Frame35(MuseumInsect *insect)
{
    InsectMotion_UpdatePartners(insect);
}
CLEAN_AS(func_ov004_02240124, InsectKind_Frame35)

/* func_ov004_0224012c (kinds 35 and 56's initialiser): kind 35 decides for both: one time in
 * two (a draw above 50 of 100) both go to mode 4 for 80-240 frames; else both rest 40-80
 * frames (three times that asleep) and kind 35's animation stops. Kind 56 only stops its
 * animation when at rest.
 * REQUIRES: kind 56 is shown with kind 35 (InsectRoom_AddGivenInsects adds it). */
void InsectKind_Init35(MuseumInsect *insect)
{
    if (insect->kind == MUSEUM_INSECT_WITH_PARTNER) {
        MuseumInsect *partner = InsectRoom_FindPartner();
        if (MainRandom_Below(100) > 50) {
            int frames = rest_frames(9, 4);
            insect->timer = frames;
            partner->timer = frames;
            insect->mode = MUSEUM_INSECT_MODE_4;
            partner->mode = MUSEUM_INSECT_MODE_4;
        } else {
            int frames = rest_frames(3, 2);
            if (!insect->awake) {
                frames = (s16) (3 * frames);
            }
            insect->timer = frames;
            partner->timer = frames;
            insect->model.frames.speed = 0;
            insect->mode = MUSEUM_INSECT_MODE_REST;
            partner->mode = MUSEUM_INSECT_MODE_REST;
        }
    } else if (insect->mode == MUSEUM_INSECT_MODE_REST) {
        insect->model.frames.speed = 0;
    }
}
CLEAN_AS(func_ov004_0224012c, InsectKind_Init35)

/* func_ov004_022401c8 (kind 24's frame): nothing. */
void InsectKind_Frame24(void) {}
CLEAN_AS(func_ov004_022401c8, InsectKind_Frame24)

/* func_ov004_022401cc (kind 24's initialiser): its motion started; asleep, the word at 0x10 of
 * its base animation (its frame control's speed) becomes 0x666. The awake byte, or 0x666. */
int InsectKind_Init24(MuseumInsect *insect)
{
    InsectMotion_Start(insect, 0x28, 0x1e, 0, 0, 0, 0xf);
    if (insect->awake == 0) {
        insect->anim.ctrl.speed = 0x666;
        return 0x666;
    }
    return insect->awake;
}
CLEAN_AS(func_ov004_022401cc, InsectKind_Init24)

/* func_ov004_02240200 (kind 48's frame) */
void InsectKind_Frame48(MuseumInsect *insect)
{
    InsectMotion_UpdateJumper(insect);
}
CLEAN_AS(func_ov004_02240200, InsectKind_Frame48)

/* func_ov004_02240208 (kind 48's initialiser): its motion started, and 10-39 frames to go. */
void InsectKind_Init48(MuseumInsect *insect)
{
    InsectMotion_Start(insect, 0x28, 0x1e, 0, 0, 0, 0xf);
    insect->timer = (s16) MainRandom_Below(30) + 10;
}
CLEAN_AS(func_ov004_02240208, InsectKind_Init48)

/* func_ov004_0224023c (kind 11's frame) */
void InsectKind_Frame11(MuseumInsect *insect)
{
    InsectMotion_UpdateHoverer(insect);
}
CLEAN_AS(func_ov004_0224023c, InsectKind_Frame11)

/* func_ov004_02240244 (kind 11's initialiser) */
void InsectKind_Init11(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x5a, 0x3c);
}
CLEAN_AS(func_ov004_02240244, InsectKind_Init11)

/* func_ov004_02240250 (kind 55's initialiser): its motion started at a random yaw, its
 * animation's frames set to three, the room's bounds, and a rest. */
void InsectKind_Init55(MuseumInsect *insect)
{
    short yaw = InsectMotion_RandomYaw();
    InsectMotion_Start(insect, 0x50, 0x50, 0, yaw, 0, 5);
    insect->unk_170 = 0;
    FrameCtrl_Init(&insect->model.frames, 3, 0, 0x1000, 0);
    InsectKind_room_bounds(insect);
    insect->timer = InsectKind_pair_rest(insect);
}
CLEAN_AS(func_ov004_02240250, InsectKind_Init55)

/* func_ov004_022402f4 (kind 54's initialiser): its motion started at a random yaw; with kind
 * 55 shown both are paired and kept within a smaller part of the room, else it rests within
 * the room's bounds. */
void InsectKind_Init54(MuseumInsect *insect)
{
    InsectMotion_Start(insect, 0x50, 0x50, 0, InsectMotion_RandomYaw(), 0, 5);
    insect->unk_170 = 0;
    MuseumInsect *other = InsectRoom_FindPairSecond();
    if (other != NULL) {
        insect->paired = 1;
        other->paired = 1;
        int low[2] = {0x110, 0x10c};
        int high[2] = {0x14c, 0x148};
        InsectMotion_SetBounds(insect, low, high);
    } else {
        insect->timer = InsectKind_pair_rest(insect);
        InsectKind_room_bounds(insect);
    }
}
CLEAN_AS(func_ov004_022402f4, InsectKind_Init54)

/* func_ov004_022403c4 (kinds 54 and 55's frame) */
void InsectKind_FramePair(MuseumInsect *insect)
{
    InsectMotion_UpdatePair(insect);
}
CLEAN_AS(func_ov004_022403c4, InsectKind_FramePair)

/* func_ov004_022403cc (kind 53's frame) */
void InsectKind_Frame53(MuseumInsect *insect)
{
    InsectMotion_UpdateKind53(insect);
}
CLEAN_AS(func_ov004_022403cc, InsectKind_Frame53)

/* func_ov004_022403d4 (kind 53's initialiser): its motion started, its x noted at 0x4c. */
void InsectKind_Init53(MuseumInsect *insect)
{
    InsectMotion_Start(insect, 0x5a, 0x40, 0, 0, 0, 0xf);
    insect->unk_4c = insect->position.x;
}
CLEAN_AS(func_ov004_022403d4, InsectKind_Init53)

/* func_ov004_02240400 (kind 51's frame) */
void InsectKind_Frame51(MuseumInsect *insect)
{
    InsectMotion_UpdateFlier(insect);
}
CLEAN_AS(func_ov004_02240400, InsectKind_Frame51)

/* func_ov004_02240408 (kind 51's initialiser): its motion started, its anchor its position at
 * the height 0xb00. */
void InsectKind_Init51(MuseumInsect *insect)
{
    InsectKind_StartAtHeight(insect, 0x1e, 0x14, 0x28, 0xf, 0x1000);
    insect->unk_4c = 0x71c;
    insect->anchor = insect->position;
    insect->anchor.y = 0xb00;
}
CLEAN_AS(func_ov004_02240408, InsectKind_Init51)

/* func_ov004_02240454 (kind 10's frame) */
void InsectKind_Frame10(MuseumInsect *insect)
{
    InsectMotion_UpdateFlier(insect);
}
CLEAN_AS(func_ov004_02240454, InsectKind_Frame10)

/* func_ov004_0224045c (kind 10's initialiser) */
void InsectKind_Init10(MuseumInsect *insect)
{
    InsectKind_StartAtHeight(insect, 0x78, 0x3c, 0x25, 8, 0x1000);
    InsectMotion_BoundAroundPosition(insect);
}
CLEAN_AS(func_ov004_0224045c, InsectKind_Init10)

/* func_ov004_02240488 (kind 49's frame) */
void InsectKind_Frame49(MuseumInsect *insect)
{
    InsectMotion_UpdateVisitor(insect);
}
CLEAN_AS(func_ov004_02240488, InsectKind_Frame49)

/* func_ov004_02240490 (kind 49's initialiser): one of five places drawn (noted at 0x4c) and
 * taken, the byte at 0x170 set one time in two, its motion started; then one time in two
 * mode 4 for 80-240 frames, else a rest of 40-80. */
void InsectKind_Init49(MuseumInsect *insect)
{
    int place = (u8) MainRandom_Below(5);
    insect->unk_170 = MainRandom_Below(100) > 50 ? 0 : 1;
    insect->unk_4c = place;
    InsectMotion_Start(insect, 0x50, 0x50, 0, 0, 0, 1);
    InsectMotion_PlaceOf(&insect->position, (unsigned int) place);
    InsectMotion_NextPlace(insect);
    insect->unk_50 = 0;
    if (MainRandom_Below(100) > 50) {
        insect->timer = 20 * ((int) MainRandom_Below(9) + 4);
        insect->mode = MUSEUM_INSECT_MODE_4;
    } else {
        insect->timer = 20 * ((int) MainRandom_Below(3) + 2);
        insect->mode = MUSEUM_INSECT_MODE_REST;
    }
}
CLEAN_AS(func_ov004_02240490, InsectKind_Init49)

/* func_ov004_02240538 (kind 30's frame) */
void InsectKind_Frame30(MuseumInsect *insect)
{
    InsectMotion_UpdateBurrower(insect);
}
CLEAN_AS(func_ov004_02240538, InsectKind_Frame30)

/* func_ov004_02240540 (kind 30's initialiser): its motion started, its model made fully
 * transparent, and its bounds. */
void InsectKind_Init30(MuseumInsect *insect)
{
    InsectMotion_Start(insect, 0xc8, 0x3c, 0, 0, 0, 0);
    NNS_G3dMdlSetMdlAlpha(ModelPoolFiles_Model(&insect->files), 0, 0);
    int low[2] = {0xa6, 0x106};
    int high[2] = {0xfc, 0x150};
    InsectMotion_SetBounds(insect, low, high);
}
CLEAN_AS(func_ov004_02240540, InsectKind_Init30)

/* The motions' own fields. */
static_assert(offsetof(MuseumInsect, unk_54) == 0x54, "insect 0x54");
static_assert(offsetof(MuseumInsect, unk_98) == 0x98, "insect 0x98");
static_assert(offsetof(MuseumInsect, distance) == 0xa4, "insect distance");
static_assert(offsetof(MuseumInsect, unk_a8) == 0xa8, "insect height");
static_assert(offsetof(MuseumInsect, unk_ae) == 0xae, "insect 0xae");
static_assert(offsetof(MuseumInsect, unk_16a) == 0x16a, "insect 0x16a");
static_assert(offsetof(MuseumInsect, timer) == 0x174, "insect timer");

extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* The ROM's signed division (_s32_div_f): a divisor of 0 gives the numerator back. */
static int InsectKind_div(int numerator, int divisor)
{
    if (divisor == 0) {
        return numerator;
    }
    if (divisor == -1) {
        return (int) (0u - (u32) numerator);
    }
    return numerator / divisor;
}

/* A whole number of units in 20.12 fixed point. */
static fx32 InsectKind_fx(int whole)
{
    return (fx32) ((u32) whole << 12);
}

/* The start of kinds 14, 15, 26 and 32: their motion at a random yaw, the bounds of 0x900 either
 * way of their x and from 0x200 below to 0x500 above their z (InsectMotion_BoundAroundPosition), and
 * `word_4c` at 0x4c. */
static void InsectKind_start_boxed(MuseumInsect *insect, short a, int b, int f, int word_4c)
{
    short yaw = InsectMotion_RandomYaw();
    InsectMotion_Start(insect, a, b, 0, yaw, 0, f);
    InsectMotion_BoundAroundPosition(insect);
    insect->unk_4c = word_4c;
}

/* func_ov004_02240594 (kind 15's initialiser) */
void InsectKind_Init15(MuseumInsect *insect)
{
    InsectKind_start_boxed(insect, 0xa0, 0x46, 0x20, 0x71c);
}
CLEAN_AS(func_ov004_02240594, InsectKind_Init15)

/* func_ov004_022405c8 (kind 14's initialiser) */
void InsectKind_Init14(MuseumInsect *insect)
{
    InsectKind_start_boxed(insect, 0xa0, 0x3c, 0x20, 0x71c);
}
CLEAN_AS(func_ov004_022405c8, InsectKind_Init14)

/* func_ov004_022405fc (kind 32's initialiser) */
void InsectKind_Init32(MuseumInsect *insect)
{
    InsectKind_start_boxed(insect, 0x50, 0x3c, 0x20, 0x71c);
}
CLEAN_AS(func_ov004_022405fc, InsectKind_Init32)

/* func_ov004_02240630 (kind 26's initialiser) */
void InsectKind_Init26(MuseumInsect *insect)
{
    InsectKind_start_boxed(insect, 0xc8, 0x3c, 1, 0x38e);
}
CLEAN_AS(func_ov004_02240630, InsectKind_Init26)

/* func_ov004_02240664 (kinds 14, 15, 26 and 32's frame) */
void InsectKind_Frame14(MuseumInsect *insect)
{
    InsectMotion_UpdateDrifter(insect);
}
CLEAN_AS(func_ov004_02240664, InsectKind_Frame14)

/* func_ov004_0224066c (kind 25's frame) */
void InsectKind_Frame25(MuseumInsect *insect)
{
    InsectMotion_UpdateDasher(insect);
}
CLEAN_AS(func_ov004_0224066c, InsectKind_Frame25)

/* func_ov004_02240674 (kind 25's initialiser): its motion started, its bounds, and 0x98 set to
 * the product of two draws: one below 20, then one below 3 awake or 15 asleep.
 * QUIRK: a product of two random numbers, not 20 times one. */
void InsectKind_Init25(MuseumInsect *insect)
{
    InsectMotion_Start(insect, 0x28, 0x50, 0, 0, 0, 1);
    int low[2] = {0x62, 0x11a};
    int high[2] = {0x92, 0x13e};
    InsectMotion_SetBounds(insect, low, high);
    unsigned int first = MainRandom_Below(20);
    unsigned int second = MainRandom_Below(insect->awake ? 3 : 15);
    insect->unk_98 = (s16) (u16) (second * first);
}
CLEAN_AS(func_ov004_02240674, InsectKind_Init25)

/* One time in two (a draw above 50 of 100) the insect is moved to another spot. */
static void InsectKind_maybe_move(MuseumInsect *insect, fx32 x, fx32 y, fx32 z)
{
    if (MainRandom_Below(100) > 50) {
        insect->position.x = x;
        insect->position.y = y;
        insect->position.z = z;
    }
}

/* func_ov004_022406ec (kind 23's initialiser) */
void InsectKind_Init23(MuseumInsect *insect)
{
    InsectKind_maybe_move(insect, 0x12b00, 0x1a00, 0xda00);
    InsectKind_StartAnchored(insect, 0x64, 0x28, 0x32, 0x78, 0x1e, 0x266);
}
CLEAN_AS(func_ov004_022406ec, InsectKind_Init23)

/* func_ov004_02240740 (kind 22's initialiser) */
void InsectKind_Init22(MuseumInsect *insect)
{
    InsectKind_maybe_move(insect, 0x16600, 0x1400, 0x14200);
    InsectKind_StartAnchored(insect, 0xc8, 0x28, 0x2d, 0x1e, 3, 0x19a);
}
CLEAN_AS(func_ov004_02240740, InsectKind_Init22)

/* func_ov004_02240794 (kind 21's initialiser) */
void InsectKind_Init21(MuseumInsect *insect)
{
    InsectKind_maybe_move(insect, 0x1a600, 0x1400, 0x13c00);
    InsectKind_StartAnchored(insect, 0xc8, 0x3c, 0x28, 0x14, 1, 0xcd);
}
CLEAN_AS(func_ov004_02240794, InsectKind_Init21)

/* func_ov004_022407e4 (kinds 21-23's start): their motion at a random yaw and `height` above
 * their position, its last word 0x1000 / `divisor`, the distance they move, `word_4c` at 0x4c
 * and their anchor at their position. Awake, one time in two they wait 100 frames; else 0xae
 * is set.
 * QUIRK: the division is the ROM's, so a divisor of 0 gives 0x1000. */
void InsectKind_StartAnchored(MuseumInsect *insect, int a, int b, int height, u8 divisor, u8 distance, int word_4c)
{
    short yaw = InsectMotion_RandomYaw();
    InsectMotion_Start(insect, (short) a, b, 0, yaw, height, InsectKind_div(0x1000, divisor));
    insect->distance = distance;
    insect->unk_4c = word_4c;
    insect->anchor = insect->position;
    if (insect->awake && MainRandom_Below(100) > 50) {
        insect->timer = 100;
    } else {
        insect->unk_ae = 1;
    }
}
CLEAN_AS(func_ov004_022407e4, InsectKind_StartAnchored)

/* func_ov004_0224086c (kinds 21-23's frame) */
void InsectKind_Frame21(MuseumInsect *insect)
{
    InsectMotion_UpdateDarter(insect);
}
CLEAN_AS(func_ov004_0224086c, InsectKind_Frame21)

/* func_ov004_02240874 (kind 52's frame) */
void InsectKind_Frame52(MuseumInsect *insect)
{
    InsectMotion_UpdateHopper(insect);
}
CLEAN_AS(func_ov004_02240874, InsectKind_Frame52)

/* func_ov004_0224087c (kind 52's initialiser): its motion started at a random yaw, a rest of
 * 60-240 frames, and 0x98 cleared. */
void InsectKind_Init52(MuseumInsect *insect)
{
    InsectMotion_Start(insect, 0x3c, 0x46, 0, InsectMotion_RandomYaw(), 0, 0x26);
    insect->timer = 20 * ((int) MainRandom_Below(10) + 3);
    insect->unk_98 = 0;
}
CLEAN_AS(func_ov004_0224087c, InsectKind_Init52)

/* func_ov004_022408bc (kind 28's initialiser) */
void InsectKind_Init28(MuseumInsect *insect)
{
    InsectKind_StartFacing(insect, 0x3c, 0x46, 8, 1);
    InsectKind_room_bounds(insect);
}
CLEAN_AS(func_ov004_022408bc, InsectKind_Init28)

/* func_ov004_02240900 (kind 13's initialiser) */
void InsectKind_Init13(MuseumInsect *insect)
{
    InsectKind_StartFacing(insect, 0x3c, 0x50, 8, 3);
    InsectKind_room_bounds(insect);
}
CLEAN_AS(func_ov004_02240900, InsectKind_Init13)

/* func_ov004_02240944 (kind 12's initialiser) */
void InsectKind_Init12(MuseumInsect *insect)
{
    InsectKind_StartFacing(insect, 0x3c, 0x50, 8, 2);
    InsectKind_room_bounds(insect);
}
CLEAN_AS(func_ov004_02240944, InsectKind_Init12)

/* func_ov004_02240988 (kind 27's initialiser) */
void InsectKind_Init27(MuseumInsect *insect)
{
    InsectKind_StartFacing(insect, 0x3c, 0x46, 6, 1);
    InsectKind_room_bounds(insect);
}
CLEAN_AS(func_ov004_02240988, InsectKind_Init27)

/* func_ov004_022409cc (kind 29's initialiser): the same as kind 27's. */
void InsectKind_Init29(MuseumInsect *insect)
{
    InsectKind_StartFacing(insect, 0x3c, 0x46, 6, 1);
    InsectKind_room_bounds(insect);
}
CLEAN_AS(func_ov004_022409cc, InsectKind_Init29)

/* func_ov004_02240a10 (kinds 12, 13 and 27-29's frame) */
void InsectKind_Frame12(MuseumInsect *insect)
{
    InsectMotion_UpdateGlider(insect);
}
CLEAN_AS(func_ov004_02240a10, InsectKind_Frame12)

/* func_ov004_02240a18 (kinds 12, 13 and 27-29's start): their motion at a random yaw, its last
 * word 0x1000 / `divisor`, 0x98 set to 40-200 frames, and the distance they move.
 * QUIRK: the division is the ROM's, so a divisor of 0 gives 0x1000. */
void InsectKind_StartFacing(MuseumInsect *insect, int a, int b, int divisor, u8 distance)
{
    short yaw = InsectMotion_RandomYaw();
    InsectMotion_Start(insect, (short) a, b, 0, yaw, 0, InsectKind_div(0x1000, divisor));
    insect->unk_98 = (s16) (20 * ((int) MainRandom_Below(9) + 2));
    insect->distance = distance;
}
CLEAN_AS(func_ov004_02240a18, InsectKind_StartFacing)

/* func_ov004_02240a6c (kind 20's initialiser): its motion started, and its animation stopped
 * (the speed of its frames 0).
 * QUIRK: returns 0x15c, the offset of that speed in the insect. */
int InsectKind_Init20(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0xc8, 0x50);
    insect->model.frames.speed = 0;
    return 0x15c;
}
CLEAN_AS(func_ov004_02240a6c, InsectKind_Init20)

/* func_ov004_02240a88 (kind 19's initialiser) */
void InsectKind_Init19(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0xc8, 0x3c);
}
CLEAN_AS(func_ov004_02240a88, InsectKind_Init19)

/* func_ov004_02240a94 (kind 18's initialiser) */
void InsectKind_Init18(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0xc8, 0x3c);
}
CLEAN_AS(func_ov004_02240a94, InsectKind_Init18)

/* func_ov004_02240aa0 (kind 17's initialiser) */
void InsectKind_Init17(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0xc8, 0x3c);
}
CLEAN_AS(func_ov004_02240aa0, InsectKind_Init17)

/* func_ov004_02240aac (kind 16's initialiser) */
void InsectKind_Init16(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0xc8, 0x3c);
}
CLEAN_AS(func_ov004_02240aac, InsectKind_Init16)

/* func_ov004_02240ab8 (kinds 16-20's frame) */
void InsectKind_Frame16(MuseumInsect *insect)
{
    InsectMotion_UpdateWatcher(insect);
}
CLEAN_AS(func_ov004_02240ab8, InsectKind_Frame16)

/* func_ov004_02240ac0 (kind 9's initialiser): its motion started, and its animation played once
 * from the first frame, over as many whole frames as it has now. */
void InsectKind_Init9(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x96, 0x46);
    FrameCtrl_Init(&insect->model.frames, (u16) ((u32) insect->model.frames.end >> 12), FRAME_CTRL_ONCE, 0x1000, 0);
}
CLEAN_AS(func_ov004_02240ac0, InsectKind_Init9)

/* func_ov004_02240afc (kind 31's initialiser) */
void InsectKind_Init31(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x28, 0x78);
}
CLEAN_AS(func_ov004_02240afc, InsectKind_Init31)

/* func_ov004_02240b08 (kind 36's initialiser) */
void InsectKind_Init36(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x5a, 0x3c);
}
CLEAN_AS(func_ov004_02240b08, InsectKind_Init36)

/* func_ov004_02240b14 (kind 34's initialiser) */
void InsectKind_Init34(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x5a, 0x3c);
}
CLEAN_AS(func_ov004_02240b14, InsectKind_Init34)

/* func_ov004_02240b20 (kind 43's initialiser) */
void InsectKind_Init43(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x82, 0x3c);
}
CLEAN_AS(func_ov004_02240b20, InsectKind_Init43)

/* func_ov004_02240b2c (kind 39's initialiser) */
void InsectKind_Init39(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x82, 0x3c);
}
CLEAN_AS(func_ov004_02240b2c, InsectKind_Init39)

/* func_ov004_02240b38 (kind 33's initialiser) */
void InsectKind_Init33(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x82, 0x3c);
}
CLEAN_AS(func_ov004_02240b38, InsectKind_Init33)

/* func_ov004_02240b44 (kind 38's initialiser) */
void InsectKind_Init38(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x82, 0x3c);
}
CLEAN_AS(func_ov004_02240b44, InsectKind_Init38)

/* func_ov004_02240b50 (kind 42's initialiser) */
void InsectKind_Init42(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x5a, 0x3c);
}
CLEAN_AS(func_ov004_02240b50, InsectKind_Init42)

/* func_ov004_02240b5c (kind 41's initialiser) */
void InsectKind_Init41(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x64, 0x3c);
}
CLEAN_AS(func_ov004_02240b5c, InsectKind_Init41)

/* func_ov004_02240b68 (kind 40's initialiser) */
void InsectKind_Init40(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x64, 0x3c);
}
CLEAN_AS(func_ov004_02240b68, InsectKind_Init40)

/* func_ov004_02240b74 (kind 44's initialiser) */
void InsectKind_Init44(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x64, 0x3c);
}
CLEAN_AS(func_ov004_02240b74, InsectKind_Init44)

/* func_ov004_02240b80 (kind 45's initialiser) */
void InsectKind_Init45(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x5a, 0x3c);
}
CLEAN_AS(func_ov004_02240b80, InsectKind_Init45)

/* func_ov004_02240b8c (kind 46's initialiser) */
void InsectKind_Init46(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x5a, 0x3c);
}
CLEAN_AS(func_ov004_02240b8c, InsectKind_Init46)

/* func_ov004_02240b98 (kind 47's initialiser) */
void InsectKind_Init47(MuseumInsect *insect)
{
    InsectKind_StartTilted(insect, 0x5a, 0x3c);
}
CLEAN_AS(func_ov004_02240b98, InsectKind_Init47)

/* func_ov004_02240ba4 (the frame of kinds 9, 31 and 33-47 but 35 and 37) */
void InsectKind_Frame9(MuseumInsect *insect)
{
    InsectMotion_UpdateHoverer(insect);
}
CLEAN_AS(func_ov004_02240ba4, InsectKind_Frame9)

/* func_ov004_02240bac (the start of kinds 9, 11, 16-20, 31 and 33-47 but 35 and 37): their
 * motion pitched 0x3556 (75 degrees) and turned half round (yaw 0x8000), and 0x50 cleared. 0. */
int InsectKind_StartTilted(MuseumInsect *insect, int a, int b)
{
    InsectMotion_Start(insect, (short) a, b, 0x3556, -0x8000, 0, 0);
    insect->unk_50 = 0;
    return 0;
}
CLEAN_AS(func_ov004_02240bac, InsectKind_StartTilted)

/* func_ov004_02240bd8 (kind 50's frame) */
void InsectKind_Frame50(MuseumInsect *insect)
{
    InsectMotion_UpdateFollower(insect);
}
CLEAN_AS(func_ov004_02240bd8, InsectKind_Frame50)

/* func_ov004_02240be0 (kind 50's initialiser): its motion started; its result. */
int InsectKind_Init50(MuseumInsect *insect)
{
    return InsectMotion_Start(insect, 0, 0, 0, 0, 0, 0xb);
}
CLEAN_AS(func_ov004_02240be0, InsectKind_Init50)

/* func_ov004_02240bfc (kind 37's frame) */
void InsectKind_Frame37(MuseumInsect *insect)
{
    InsectMotion_UpdateFlutterer(insect);
}
CLEAN_AS(func_ov004_02240bfc, InsectKind_Frame37)

/* func_ov004_02240c04 (kind 37's initialiser): awake, it is moved to another spot, its motion
 * started, 0x50 set to 60 and its bounds; asleep, its motion is started where it is, pitched
 * 0x3556 with yaw 0x6000. */
void InsectKind_Init37(MuseumInsect *insect)
{
    if (insect->awake) {
        insect->position.x = 0x7a00;
        insect->position.y = 0x2d00;
        insect->position.z = 0x12c00;
        InsectMotion_Start(insect, 0x5a, 0x50, 0, 0, 0, 4);
        insect->unk_50 = 0x3c;
        int low[2] = {0, 0xac};
        int high[2] = {0x96, 0x1ac};
        InsectMotion_SetBounds(insect, low, high);
    } else {
        InsectMotion_Start(insect, 0x5a, 0x50, 0x3556, 0x6000, 0, 4);
    }
}
CLEAN_AS(func_ov004_02240c04, InsectKind_Init37)

/* func_ov004_02240c94 (kind 8's initialiser): its motion started (pitch 1, turned half round)
 * and pitched 0x2aa8 when asleep; 0x50 set to 60, 0x16a to a draw below 18, 0x170 set, 0x54
 * cleared and its anchor at its position; asleep, its animation's 8 frames played once. */
void InsectKind_Init8(MuseumInsect *insect)
{
    InsectMotion_Start(insect, 0x96, 0x28, 1, -0x8000, 0, 9);
    if (!insect->awake) {
        insect->pitch = 0x2aa8;
    }
    insect->unk_50 = 0x3c;
    insect->unk_16a = (u8) MainRandom_Below(18);
    insect->unk_170 = 1;
    insect->unk_54 = 0;
    insect->anchor = insect->position;
    if (!insect->awake) {
        FrameCtrl_Init(&insect->model.frames, 8, FRAME_CTRL_ONCE, 0x1000, 0);
    }
}
CLEAN_AS(func_ov004_02240c94, InsectKind_Init8)

/* func_ov004_02240d34 (kind 8's frame) */
void InsectKind_Frame8(MuseumInsect *insect)
{
    InsectMotion_UpdateHovering(insect);
}
CLEAN_AS(func_ov004_02240d34, InsectKind_Frame8)

/* func_ov004_02240d3c (kind 7's initialiser) */
void InsectKind_Init7(MuseumInsect *insect)
{
    InsectKind_StartAtHeight(insect, 0xc8, 0x50, 0x2d, 8, 0x1000);
}
CLEAN_AS(func_ov004_02240d3c, InsectKind_Init7)

/* func_ov004_02240d5c (kind 6's initialiser) */
void InsectKind_Init6(MuseumInsect *insect)
{
    InsectKind_StartAtHeight(insect, 0xc8, 0x50, 0x2d, 15, 0x1000);
}
CLEAN_AS(func_ov004_02240d5c, InsectKind_Init6)

/* func_ov004_02240d7c (kind 5's initialiser) */
void InsectKind_Init5(MuseumInsect *insect)
{
    InsectKind_StartAtHeight(insect, 0xc8, 0x50, 0x14, 9, 0x1000);
}
CLEAN_AS(func_ov004_02240d7c, InsectKind_Init5)

/* func_ov004_02240d9c (kind 4's initialiser) */
void InsectKind_Init4(MuseumInsect *insect)
{
    InsectKind_StartAtHeight(insect, 0xc8, 0x50, 0x2d, 7, 0xe66);
}
CLEAN_AS(func_ov004_02240d9c, InsectKind_Init4)

/* func_ov004_02240dbc (kind 3's initialiser) */
void InsectKind_Init3(MuseumInsect *insect)
{
    InsectKind_StartAtHeight(insect, 0xc8, 0x50, 0x28, 7, 0x1000);
}
CLEAN_AS(func_ov004_02240dbc, InsectKind_Init3)

/* func_ov004_02240ddc (kind 2's initialiser) */
void InsectKind_Init2(MuseumInsect *insect)
{
    InsectKind_StartAtHeight(insect, 0xc8, 0x50, 0x28, 7, 0x1000);
}
CLEAN_AS(func_ov004_02240ddc, InsectKind_Init2)

/* func_ov004_02240dfc (kind 1's initialiser) */
void InsectKind_Init1(MuseumInsect *insect)
{
    InsectKind_StartAtHeight(insect, 0xc8, 0x50, 0x25, 6, 0x119a);
}
CLEAN_AS(func_ov004_02240dfc, InsectKind_Init1)

/* func_ov004_02240e1c (kind 0's initialiser) */
void InsectKind_Init0(MuseumInsect *insect)
{
    InsectKind_StartAtHeight(insect, 0xc8, 0x50, 0x25, 6, 0x119a);
}
CLEAN_AS(func_ov004_02240e1c, InsectKind_Init0)

/* func_ov004_02240e3c (the start of kinds 0-7, 10 and 51): their anchor at their position, their
 * motion started, 0x50 set to 40, a rest of 320-500 frames, 0x16a a draw below 18, 0x170 set,
 * `word_4c` at 0x4c, 0x98 cleared, and the height they move at `height` + 8 sixteenths. Asleep
 * they go to mode 6 and play their animation's 17 frames once from frame 9, but for kinds 10
 * and 51, which are set at frame 0. */
void InsectKind_StartAtHeight(MuseumInsect *insect, int a, int b, int height, int f, int word_4c)
{
    fx32 level = FX_MulFunc(FX_MulFunc(InsectKind_fx(height + 8), 0x1000), 0x100);
    insect->anchor = insect->position;
    InsectMotion_Start(insect, (short) a, b, 0, 0, 0, f);
    insect->unk_50 = 0x28;
    insect->timer = 20 * ((int) MainRandom_Below(10) + 16);
    insect->unk_16a = (u8) MainRandom_Below(18);
    insect->unk_170 = 1;
    insect->unk_4c = word_4c;
    insect->unk_98 = 0;
    insect->unk_a8 = level;
    insect->unk_54 = level;
    if (!insect->awake) {
        insect->mode = 6;
        if (insect->kind != 10 && insect->kind != 51) {
            FrameCtrl_Init(&insect->model.frames, 17, FRAME_CTRL_ONCE, 0x1000, 9);
        } else {
            AnimatedModel_SetFrame((AnimatedModel *) (void *) &insect->model, 0);
        }
    }
}
CLEAN_AS(func_ov004_02240e3c, InsectKind_StartAtHeight)

/* func_ov004_02240f24 (kinds 0-7's frame) */
void InsectKind_Frame0(MuseumInsect *insect)
{
    InsectMotion_UpdateFlapper(insect);
}
CLEAN_AS(func_ov004_02240f24, InsectKind_Frame0)
