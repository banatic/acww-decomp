/* Some kinds of the museum's insects (museum_insect_kinds.h). */
#include "museum_insect_kinds.h"

#include "clean.h"
#include "main/frame_ctrl.h"
#include "main/main_random.h"
#include "main/model_pool.h"

/* The motions shared by several kinds. func_ov004_02240f2c starts a motion: the position kept,
 * at rest, its pitch and yaw, its speeds and its height above the position. */
extern int func_ov004_02240f2c(MuseumInsect *insect, short a, int b, short pitch, short yaw, int height, int f);
extern void func_ov004_02240e3c(MuseumInsect *insect, int a, int b, int c, int e, int f);
extern int func_ov004_02240bac(MuseumInsect *insect, int a, int b);
extern void func_ov004_02240fc0(MuseumInsect *insect);
/* The bounds an insect is kept within (MuseumInsect.low and high), from two corners in 1/16
 * units, x then z. */
extern void func_ov004_02241008(MuseumInsect *insect, const int *low, const int *high);
extern void func_ov004_02242df8(Vec3 *position, unsigned int index);
extern void func_ov004_02242e84(MuseumInsect *insect);
/* A random yaw: one of sixteen steps of 0xaaa either way. */
extern short func_ov004_02244f90(void);
/* The frame functions. */
extern void func_ov004_02241f88(MuseumInsect *insect);
extern void func_ov004_02243544(MuseumInsect *insect);
extern void func_ov004_02241894(MuseumInsect *insect);
extern void func_ov004_02242ae4(MuseumInsect *insect);
extern void func_ov004_022419f8(MuseumInsect *insect);
extern void func_ov004_02243694(MuseumInsect *insect);
extern void func_ov004_02243048(MuseumInsect *insect);
extern void func_ov004_022433c8(MuseumInsect *insect);

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
    func_ov004_02241008(insect, low, high);
}

/* A rest of 20-120 frames awake, 100-680 asleep. */
static s16 InsectKind_pair_rest(const MuseumInsect *insect)
{
    return insect->awake ? rest_frames(6, 1) : rest_frames(30, 5);
}

/* func_ov004_02240124 (kinds 35 and 56's frame) */
void InsectKind_Frame35(MuseumInsect *insect)
{
    func_ov004_02241f88(insect);
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
    func_ov004_02240f2c(insect, 0x28, 0x1e, 0, 0, 0, 0xf);
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
    func_ov004_02243544(insect);
}
CLEAN_AS(func_ov004_02240200, InsectKind_Frame48)

/* func_ov004_02240208 (kind 48's initialiser): its motion started, and 10-39 frames to go. */
void InsectKind_Init48(MuseumInsect *insect)
{
    func_ov004_02240f2c(insect, 0x28, 0x1e, 0, 0, 0, 0xf);
    insect->timer = (s16) MainRandom_Below(30) + 10;
}
CLEAN_AS(func_ov004_02240208, InsectKind_Init48)

/* func_ov004_0224023c (kind 11's frame) */
void InsectKind_Frame11(MuseumInsect *insect)
{
    func_ov004_02241894(insect);
}
CLEAN_AS(func_ov004_0224023c, InsectKind_Frame11)

/* func_ov004_02240244 (kind 11's initialiser) */
void InsectKind_Init11(MuseumInsect *insect)
{
    func_ov004_02240bac(insect, 0x5a, 0x3c);
}
CLEAN_AS(func_ov004_02240244, InsectKind_Init11)

/* func_ov004_02240250 (kind 55's initialiser): its motion started at a random yaw, its
 * animation's frames set to three, the room's bounds, and a rest. */
void InsectKind_Init55(MuseumInsect *insect)
{
    short yaw = func_ov004_02244f90();
    func_ov004_02240f2c(insect, 0x50, 0x50, 0, yaw, 0, 5);
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
    func_ov004_02240f2c(insect, 0x50, 0x50, 0, func_ov004_02244f90(), 0, 5);
    insect->unk_170 = 0;
    MuseumInsect *other = InsectRoom_FindPairSecond();
    if (other != NULL) {
        insect->paired = 1;
        other->paired = 1;
        int low[2] = {0x110, 0x10c};
        int high[2] = {0x14c, 0x148};
        func_ov004_02241008(insect, low, high);
    } else {
        insect->timer = InsectKind_pair_rest(insect);
        InsectKind_room_bounds(insect);
    }
}
CLEAN_AS(func_ov004_022402f4, InsectKind_Init54)

/* func_ov004_022403c4 (kinds 54 and 55's frame) */
void InsectKind_FramePair(MuseumInsect *insect)
{
    func_ov004_02242ae4(insect);
}
CLEAN_AS(func_ov004_022403c4, InsectKind_FramePair)

/* func_ov004_022403cc (kind 53's frame) */
void InsectKind_Frame53(MuseumInsect *insect)
{
    func_ov004_022419f8(insect);
}
CLEAN_AS(func_ov004_022403cc, InsectKind_Frame53)

/* func_ov004_022403d4 (kind 53's initialiser): its motion started, its x noted at 0x4c. */
void InsectKind_Init53(MuseumInsect *insect)
{
    func_ov004_02240f2c(insect, 0x5a, 0x40, 0, 0, 0, 0xf);
    insect->unk_4c = insect->position.x;
}
CLEAN_AS(func_ov004_022403d4, InsectKind_Init53)

/* func_ov004_02240400 (kind 51's frame) */
void InsectKind_Frame51(MuseumInsect *insect)
{
    func_ov004_02243694(insect);
}
CLEAN_AS(func_ov004_02240400, InsectKind_Frame51)

/* func_ov004_02240408 (kind 51's initialiser): its motion started, its anchor its position at
 * the height 0xb00. */
void InsectKind_Init51(MuseumInsect *insect)
{
    func_ov004_02240e3c(insect, 0x1e, 0x14, 0x28, 0xf, 0x1000);
    insect->unk_4c = 0x71c;
    insect->anchor = insect->position;
    insect->anchor.y = 0xb00;
}
CLEAN_AS(func_ov004_02240408, InsectKind_Init51)

/* func_ov004_02240454 (kind 10's frame) */
void InsectKind_Frame10(MuseumInsect *insect)
{
    func_ov004_02243694(insect);
}
CLEAN_AS(func_ov004_02240454, InsectKind_Frame10)

/* func_ov004_0224045c (kind 10's initialiser) */
void InsectKind_Init10(MuseumInsect *insect)
{
    func_ov004_02240e3c(insect, 0x78, 0x3c, 0x25, 8, 0x1000);
    func_ov004_02240fc0(insect);
}
CLEAN_AS(func_ov004_0224045c, InsectKind_Init10)

/* func_ov004_02240488 (kind 49's frame) */
void InsectKind_Frame49(MuseumInsect *insect)
{
    func_ov004_02243048(insect);
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
    func_ov004_02240f2c(insect, 0x50, 0x50, 0, 0, 0, 1);
    func_ov004_02242df8(&insect->position, (unsigned int) place);
    func_ov004_02242e84(insect);
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
    func_ov004_022433c8(insect);
}
CLEAN_AS(func_ov004_02240538, InsectKind_Frame30)

/* func_ov004_02240540 (kind 30's initialiser): its motion started, its model made fully
 * transparent, and its bounds. */
void InsectKind_Init30(MuseumInsect *insect)
{
    func_ov004_02240f2c(insect, 0xc8, 0x3c, 0, 0, 0, 0);
    NNS_G3dMdlSetMdlAlpha(ModelPoolFiles_Model(&insect->files), 0, 0);
    int low[2] = {0xa6, 0x106};
    int high[2] = {0xfc, 0x150};
    func_ov004_02241008(insect, low, high);
}
CLEAN_AS(func_ov004_02240540, InsectKind_Init30)
