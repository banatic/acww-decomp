/* Overlay 3's part of the field actor (field_actor.h). */
#include "field_actor.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "autoload_2/fx_math.h" /* Math_Atan2 */
#include "autoload_2/input.h"   /* PadState */
#include "clean.h"
#include "main/calendar.h"     /* DateTime */
#include "main/group_params.h" /* GroupParams_CanOpen, GroupParams_C4CIs1 */

static_assert(offsetof(FieldActor, position) == 0x5c, "position");
static_assert(offsetof(FieldActor, yaw) == 0x8e, "yaw");
static_assert(offsetof(FieldActor, unk_098) == 0x98, "0x98");
static_assert(offsetof(FieldActor, unk_140) == 0x140, "0x140");
static_assert(offsetof(FieldActor, unk_144) == 0x144, "0x144");
static_assert(offsetof(FieldActor, unk_148) == 0x148, "0x148");
static_assert(offsetof(FieldActor, aim_point) == 0x158, "aim point");
static_assert(offsetof(FieldActor, other) == 0x168, "other");
static_assert(offsetof(FieldActor, other_result) == 0x16c, "other result");
static_assert(offsetof(FieldActor, aim_mode) == 0x170, "aim mode");
static_assert(offsetof(FieldActor, other_kind) == 0x1d2, "other kind");
static_assert(offsetof(FieldActor, has_other) == 0x200, "has other");
static_assert(offsetof(FieldActor, anim) == 0x2d0, "animation");
static_assert(offsetof(FieldActor, anim.frame) == 0x2d8, "animation frame");
static_assert(offsetof(FieldActor, head_pitch) == 0x45c, "head");
static_assert(offsetof(FieldActor, held) == 0x5a0, "held");
static_assert(offsetof(FieldActor, unk_62C) == 0x62c, "0x62c");
static_assert(offsetof(FieldActor, unk_68C) == 0x68c, "0x68c");
static_assert(offsetof(FieldActor, flags) == 0x6ec, "flags");
static_assert(offsetof(FieldActor, start_position) == 0x6f4, "start position");
static_assert(offsetof(FieldActor, animation) == 0x704, "animation");
static_assert(offsetof(FieldActor, work) == 0x7d4, "work");
static_assert(offsetof(FieldActor, work.effect.count) == 0x7d8, "work count");
static_assert(offsetof(FieldActor, state) == 0x7f0, "state");
static_assert(offsetof(FieldActor, unk_7F8) == 0x7f8, "0x7f8");
static_assert(offsetof(FieldActor, next_state) == 0x7fc, "next state");
static_assert(offsetof(FieldActor, player) == 0x800, "player");
static_assert(offsetof(FieldActor, target) == 0x80c, "target");
static_assert(offsetof(FieldActor, unk_814) == 0x814, "0x814");
static_assert(offsetof(FieldActor, unk_818) == 0x818, "0x818");
static_assert(offsetof(FieldActor, unk_822) == 0x822, "0x822");
static_assert(offsetof(FieldActor, unk_830) == 0x830, "0x830");
static_assert(offsetof(FieldActor, front_tile) == 0x8d0, "front tile");
static_assert(offsetof(FieldActor, tile) == 0x8d8, "tile");
static_assert(offsetof(FieldActor, pending_tile) == 0x8e0, "pending tile");
static_assert(offsetof(FieldActor, saved) == 0x8f0, "saved");
static_assert(offsetof(FieldActor, receiver_unk_1E) == 0x10a, "receiver 0x1e");
static_assert(offsetof(FieldActor, link) == 0x12c, "link");
static_assert(offsetof(FieldActor, unk_234) == 0x234, "0x234");
static_assert(offsetof(FieldActor, anim.speed) == 0x2e0, "animation speed");
static_assert(offsetof(FieldActor, anim.flags) == 0x2e4, "animation flags");
static_assert(offsetof(FieldActor, effect_point) == 0x6e0, "effect point");
static_assert(offsetof(FieldActor, unk_70D) == 0x70d, "0x70d");
static_assert(offsetof(FieldActor, work.s74.move_angle) == 0x7e8, "state 0x74 angle");
static_assert(offsetof(FieldActor, work.s74.effect) == 0x7ec, "state 0x74 effect");
static_assert(offsetof(FieldActor, work.s73.effect) == 0x7dc, "state 0x73 effect");
static_assert(offsetof(FieldActor, work.s71.done) == 0x7d8, "state 0x71 done");
static_assert(offsetof(FieldActor, work.s6d.kind) == 0x7d8, "state 0x6d kind");
static_assert(offsetof(FieldActor, unk_8E8) == 0x8e8, "0x8e8");
static_assert(offsetof(FieldActor, unk_C84) == 0xc84, "0xc84");
static_assert(offsetof(FieldActor, work.s69.yaw) == 0x7d6, "state 0x69 yaw");
static_assert(offsetof(FieldActor, work.s69.tile_x) == 0x7d8, "state 0x69 tile");
static_assert(offsetof(FieldActor, work.s69.then_77) == 0x7e0, "state 0x69 flags");
static_assert(offsetof(FieldActor, work.s68.yaw) == 0x7dc, "state 0x68 yaw");
static_assert(offsetof(FieldActor, work.s68.count) == 0x7de, "state 0x68 count");
static_assert(offsetof(FieldActor, work.s68.then_69) == 0x7e0, "state 0x68 flags");
static_assert(offsetof(FieldActor, work.s67.point) == 0x7d8, "state 0x67 point");
static_assert(offsetof(FieldActor, work.s66.yaw) == 0x7e0, "state 0x66 yaw");
static_assert(offsetof(FieldActor, work.s66.next) == 0x7e3, "state 0x66 next");
static_assert(offsetof(FieldActor, unk_8F8) == 0x8f8, "0x8f8");
static_assert(sizeof(XZArgs) == 0xc, "XZ arguments");
static_assert(sizeof(FieldActorWork) == 0x1c, "work");
static_assert(sizeof(StateRequest) == 0x1c, "request");

/* The held item code of nothing. */
#define ITEM_NONE 0xfff1

/* An object that answers a query about an item in vtable slot 24 (offset 0x60). */
typedef struct GameObject {
    const u32 *vtable;
} GameObject;

typedef int (*ItemQuery)(GameObject *object, u16 *item);
typedef void (*FieldActorSlot23)(FieldActor *actor, void *arg);

/* ---- Data */

/* The session; func_02073908 says whether a player number is the one at this console. */
extern void *data_020ccf94;
/* The town map (func_0204f5e0, func_0204f5a8). */
extern void *data_021c80bc;
extern u8 *data_021c526c;
/* Distances ahead of the actor (20.12) for func_0200fa1c. */
extern const fx32 data_ov003_02236608[];
extern const fx32 data_ov003_0223810c;
extern const fx32 data_ov003_02238124;
extern const fx32 data_ov003_02238128;
extern const fx32 data_ov003_02238130;
/* A flag and a point state 0x81 leaves for other code. */
extern u8 data_ov003_02260540;
extern Vec3 data_ov003_02260558;

/* ---- Functions of the game */

/* `out` = `from` moved `*distance` along `*angle`. */
extern void func_0200fa1c(Vec3 *out, FieldActor *actor, const Vec3 *from, const s16 *angle, const fx32 *distance);
/* The point a fixed distance ahead of the actor, and the same snapped to its tile. */
extern void func_0200fa6c(Vec3 *out, FieldActor *actor);
extern void func_0200fa8c(Vec3 *out, FieldActor *actor);
extern int func_0201005c(FieldActor *actor, const Vec3 *point, int range);
extern int func_0200ff28(FieldActor *actor, Vec3 *point, int mode, int tool);
extern int func_0200fd04(FieldActor *actor, Vec3 *point, int mode);
extern int func_0200ffec(FieldActor *actor);
extern int func_0200fbe0(FieldActor *actor);
extern int func_02010004(FieldActor *actor, int tool);
extern int func_020eaa6c(const Vec3 *a, const Vec3 *b);
extern int func_020ea990(const Vec3 *a, const Vec3 *b);
/* The tile a point is on. */
extern void func_0204f818(int *x, int *z, const Vec3 *point);
extern u16 *func_0204f5e0(void *map, int acre_x, int acre_z, int x, int z, int layer);
extern u16 *func_0204f5a8(void *map, const Vec3 *point, int layer);
extern int func_02031614(const Vec3 *point);
extern int func_020ba310(void);
extern void func_020110c4(u16 *item, FieldActor *actor);
extern GameObject *func_02082618(int kind, int id);
extern int func_0200ee0c(FieldActor *actor);
extern u16 *func_02096274(void);
extern u8 *func_0209626c(void);
extern void *func_02011368(FieldActor *actor);
extern void func_0209e474(DateTime *now);
extern int func_0200f86c(FieldActor *actor);
extern int func_020ba4d4(void);
extern void func_020997b4(void *record, u8 level);
extern void func_0200f7ac(FieldActor *actor, void *record, u16 *date);
extern u8 func_020112bc(FieldActor *actor);
extern void func_0200f11c(FieldActor *actor);
extern int func_0200f290(FieldActor *actor, int bit);
extern u32 *func_0200f27c(FieldActor *actor, int bit);
extern void func_0200f268(FieldActor *actor, int bit);
extern int func_0200ea0c(FieldActor *actor, int state);
extern int func_020438dc(int player, int *tile, int mode);
extern void func_0200e854(FieldActor *actor);
extern void func_020448b8(int *tile);
extern int func_0200fdd0(FieldActor *actor, int *tile, int c, int d);
extern int func_020310d0(const Vec3 *point, int *surface, int flags);
extern int func_02010718(FieldActor *actor);
extern u8 func_02008258(FieldActor *actor, int state);
extern int func_0200d1a0(FieldActor *actor, int a, int priority, int arg);
extern int func_02010538(FieldActor *actor);
extern void func_02010f5c(FieldActor *actor);
extern int func_0200f554(FieldActor *actor);
extern int func_0201100c(FieldActor *actor);
extern void func_02010d64(FieldActor *actor);
extern int func_02095518(int pitch, int yaw, int player);
extern int func_02011404(s16 *angle, int target, int a, int b, int c);
extern int func_0200c9a8(FieldActor *actor, int a, int priority, int arg);
extern int func_0200d4e8(FieldActor *actor, int a, int priority, int arg);
extern void func_020109fc(FieldActor *actor, int animation, int a, int b);
extern void func_020109a0(FieldActor *actor, int animation, int a, u16 b);
extern u32 func_0200e92c(StateRequest *request);
extern void func_0200e90c(StateRequest *request, int state, int priority, int arg);
extern int func_0200e894(FieldActor *actor, StateRequest *request);
extern int func_0200e91c(StateRequest *request);
extern int func_02056f94(const FrameCtrl *ctrl);
extern int func_02056f28(const FrameCtrl *ctrl, int frame);
extern int func_020113e0(s16 *angle, int target);
extern void func_020110a0(FieldActor *actor, s16 *yaw);
extern int func_0200f328(FieldActor *actor, int sound);
extern int func_02073908(void *session, int player);
extern int func_0203f7d0(Vec3 *out, const Vec3 *in);
extern int func_020912d4(int kind, Vec3 *position, s16 *angle, int a);
extern void func_02091278(int effect, Vec3 *position, s16 *angle, int a);
extern void func_0209129c(int effect);
extern void *func_020984fc(int player);
extern void func_0209971c(void *record, u16 *item);
extern u16 *func_02099728(void *record);
extern void func_0205eb8c(void *held, u16 *item, int a);
extern void func_0205eae0(void *held, int pose, int a, int b);
extern u8 *func_0205e8e4(void *held);
extern void func_0200f1a4(FieldActor *actor, int a, u16 item);
extern int func_0203b144(void);
extern void func_02036448(void *p);

extern GameObject *func_ov003_02236204(int id);
extern int func_ov003_02217234(FieldActor *actor, int priority, int arg);
extern int func_ov003_02212c58(FieldActor *actor, int priority, int arg);
extern int func_ov003_02214644(FieldActor *actor, int priority, int arg);
extern int func_ov003_02215f00(FieldActor *actor, Vec3 *point, int priority, int arg);
extern int func_ov003_02215ce4(FieldActor *actor, int priority, int arg);
extern void *func_ov003_02217450(FieldActor *actor, int priority, int arg);
extern void func_ov003_02224384(int player, int *tile, int a);
extern int func_ov003_0222a938(int player);
extern Vec3 *func_ov003_0222a918(int player);
extern int func_ov003_0222c364(int player);
extern Vec3 *func_ov003_0222c1f4(int player);
extern int func_ov003_0222c214(int player);

/* What func_02034270 tells of the ground at a point; func_0203423c releases it. */
typedef struct GroundInfo {
    u8 unk_00[0x30];
    int unk_30; /* state 0x56 takes the swing's base as its end where this is 0 */
    int kind;   /* 0x13 makes the splash effects of states 0x73 and 0x75 the other ones */
    u8 unk_38[8];
} GroundInfo;

/* The buttons whose presses push state 0x74 on (autoload_2/input.h). */
#define BUTTON_A 0x0001
#define BUTTON_B 0x0002
#define BUTTON_SELECT 0x0004
#define BUTTON_START 0x0008
#define BUTTON_R 0x0100
#define BUTTON_L 0x0200
#define BUTTON_X 0x0400
#define BUTTON_Y 0x0800

extern PadState data_021fbe40;
extern const s16 FX_SinCosTable_[];
extern u8 data_021c75b8;
/* Distances ahead of the actor (forward, up) for the effects of state 0x71. */
extern const fx32 data_ov003_02238110[];
extern const fx32 data_ov003_02238118[];
/* "obj_etc_player": the receiver's name in state 0x78. */
extern const char data_ov003_02238134[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 VEC_Mag(const Vec3 *v);
/* out = a - b */
extern void func_020eaca0(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern void func_0203ae98(void);
extern void func_02036450(void *p);
extern int func_02099e9c(u16 *item);
extern int func_02095694(int a, int player);
extern void func_0209a050(int slot);
extern int func_ov003_02217c5c(FieldActor *actor, int a, int b, int c, int d, s16 e, int priority, s16 arg);
extern int func_0200faa8(FieldActor *actor, int step);
/* Turns the actor towards yaw 0 by up to `step`; whether it faces that way. */
extern int func_0200faf0(FieldActor *actor, int step);
extern void *func_020984e8(void);
extern void func_02099740(void *record, int a);
extern u32 func_0209984c(void *record);
extern int func_0205dc94(u8 *p, int value);
extern int func_02099020(void *record, u32 bit);
extern void func_02098ff8(void *record, u32 bit);
extern void func_02035624(int a);
extern void func_020356c4(int a, int b, int c, int d);
extern void func_02035638(int a);
extern void func_02035684(int a, int b, int c);
extern void func_02035a70(void *p);
extern void func_02035ac8(void *p);
extern void func_0203ee14(FieldActor *actor, void *receiver);
extern void func_0203ee08(FieldActor *actor, void *receiver);
extern void func_020a8164(void *receiver, const char *name);
extern int func_0203e19c(void);
extern int func_0203e110(void);
extern int func_0203e420(void);
extern int func_02034270(GroundInfo *out, Vec3 *at, int a, int b);
extern void func_0203423c(GroundInfo *info);
extern int func_02091254(int kind, Vec3 *at, int a, int b);
extern int func_ov003_02220b44(int player, Vec3 *at);
extern int func_ov003_02221228(int player, Vec3 *at);
/* The actor's movement: its speed (the word at 0x134) and direction (the halfword at 0x138). */
extern u32 func_0200dc8c(FieldActor *actor);
extern s16 func_0200dc80(FieldActor *actor);
extern void func_0205eac4(void *held, fx32 speed);
extern void func_0200f2a0(FieldActor *actor, int a, Vec3 *at);
extern void func_0200fbc4(FieldActor *actor, fx32 x, fx32 z, int yaw);
/* The point at the middle of a tile. */
extern void func_0204f794(Vec3 *out, u32 x, u32 z);
/* max(value - step, min) */
extern int func_020113a4(int value, int min, int step);
extern void func_0201107c(FieldActor *actor, int *value);
extern void func_020ba2ec(void);
extern void func_02054860(void *p);
extern void func_0200f3e8(FieldActor *actor);
extern int func_0204bcdc(u16 *item);
extern int func_0204bc64(u16 *item);
extern void func_0200f888(FieldActor *actor);
extern void func_0200f95c(FieldActor *actor);
extern u32 func_0204e414(void);
extern int func_0204e108(u32 a, Vec3 *out, int c, int d);
extern int func_0204e08c(u32 a, Vec3 *out, int c, int d);
extern void *func_020b5e10(void);
extern int func_020b63f4(void *dst, u8 a, const Vec3 *at, u32 b, s16 c, u8 d, u8 e);
extern void RtcSendPxiCommand(int command);
extern void func_02056fcc(FrameCtrl *ctrl, u32 frames, u8 flags, fx32 speed, u16 start);
/* Points packed into 20-bit coordinates: x, y and z (y biased by 0x80000) with a nibble, or x and
 * z alone. */
extern void func_02077928(const u8 *packed, fx32 *x, fx32 *y, fx32 *z, u8 *nibble);
extern void func_02077950(u8 *packed, fx32 x, fx32 y, fx32 z, u8 nibble);
extern void func_02077978(const u8 *packed, fx32 *x, fx32 *z);
extern void func_020779b8(u8 *packed, fx32 x, fx32 z);
/* Move the actor towards a point (or a tile's middle); whether it is there. */
extern int func_0200f434(FieldActor *actor, const Vec3 *point);
extern int func_0200f530(FieldActor *actor, const int *tile);
/* Asks for state 0x77 with a yaw. */
extern int func_02008dc0(FieldActor *actor, u16 yaw, int priority, int arg);
/* The middle of the tile a point is on, at the point's height. */
extern void func_0204f7e0(Vec3 *out, const Vec3 *point);
extern void func_ov003_022235d8(int player, int *tile);
extern int func_ov003_02220db4(int player, Vec3 *at);

/* ---- Helpers */

static int add32(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

static int sub32(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

/* The whole frame the animation is on. QUIRK: only the low 16 bits of the frame number. */
static int anim_frame(const FieldActor *actor)
{
    return (int) (((u32) actor->anim.frame >> 12) & 0xffff);
}

static BOOL is_local_player(const FieldActor *actor)
{
    return func_02073908(data_020ccf94, actor->player) != 0;
}

/* The map object on a tile: the acre is the tile over 16, the tile in it the remainder. */
static u16 *map_object_at(int x, int z)
{
    return func_0204f5e0(data_021c80bc, x >> 4, z >> 4, x & 15, z & 15, 0);
}

static BOOL in_range(u16 code, u16 first, u16 last)
{
    return code >= first && code <= last;
}

/* The map objects of families A, B and C and the codes after them (main/map_item.h), except
 * 0x1b: 0x00-0x1a, 0x1c-0x1d and 0x6e-0xa5. */
static BOOL is_family_object(u16 code)
{
    return in_range(code, 0x00, 0x1a) || in_range(code, 0x1c, 0x1d) || in_range(code, 0x6e, 0xa5);
}

/* The growth lines and the codes at their last stage only (main/map_item.h). */
static BOOL is_growth_object(u16 code)
{
    return in_range(code, 0x26, 0x2a) || in_range(code, 0x2f, 0x5b) || in_range(code, 0x5d, 0x61) ||
           in_range(code, 0x66, 0x6d) || in_range(code, 0xc8, 0xcf);
}

/* The four short lines (main/map_item.h). */
static BOOL is_short_line_object(u16 code)
{
    return in_range(code, 0x2b, 0x2e) || in_range(code, 0xff, 0x102) || in_range(code, 0x62, 0x65) ||
           in_range(code, 0xd0, 0xd3);
}

/* Whether a held item code is one of 0x1376 and 0x1377. */
static BOOL is_item_1376(u16 item)
{
    return item == 0x1376 || item == 0x1377;
}

static const Vec3 ORIGIN = {0, 0, 0};

/* Builds a request for `state` and queues it; whether it was queued.
 * BUG: the bytes of the request nothing sets (the two after `arg`, and the payload past
 * `payload_size`) are whatever the stack held, and the queue copies them into the actor. */
static int request_state(FieldActor *actor, int state, int priority, int arg, const u8 *payload, int payload_size)
{
    StateRequest request;

#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    func_0200e92c(&request);
    func_0200e90c(&request, state, priority, arg);
    for (int i = 0; i < payload_size; i++) {
        request.payload[i] = payload[i];
    }
    int queued = func_0200e894(actor, &request);
    func_0200e91c(&request);
    return queued;
}

/* ---- Tools and targets */

/* func_ov003_0220c328: an action on what lies at the tool's point, for func_02010004.
 * FieldActor_TryTargetMode2 comes first; failing that, the point (ahead of the actor at
 * 0x0ccd, or aim_point when it is within range 0xc) is tried with mode 0. Whether an action
 * started. Only the first argument after `actor` is read. */
int FieldActor_TryTarget(FieldActor *actor, int tool, ...)
{
    Vec3 point;

    if (FieldActor_TryTargetMode2(actor, &tool)) {
        return 1;
    }
    if (actor->aim_mode == 1) {
        func_0200fa1c(&point, actor, &actor->position, &actor->yaw, &data_ov003_02238130);
    } else {
        point = actor->aim_point;
        if (!func_0201005c(actor, &point, 0xc)) {
            return 0;
        }
    }
    return func_0200ff28(actor, &point, 0, tool) && func_0200fd04(actor, &point, 0);
}
CLEAN_AS(func_ov003_0220c328, FieldActor_TryTarget)

/* func_ov003_0220c3d0: starts the action of `tool` at `point` (each by queueing its state with
 * priority 6); whether one started. Tools 3, 0 and 10 replace a point at the origin: tool 3
 * with the actor's position, tools 0 and 10 with the tile ahead. Tools 0 and 10 act on the
 * tile ahead when `point` is within 0x2334 and func_0200ff28 finds something there (mode 1);
 * otherwise tool 10 queues its own state and tool 0 does nothing. */
int FieldActor_UseTool(FieldActor *actor, int tool, Vec3 *point)
{
    Vec3 ahead;
    Vec3 tile;

    switch (tool) {
        case 1:
            func_ov003_02212c58(actor, 6, -1);
            return 1;
        case 2:
            func_ov003_02217234(actor, 6, -1);
            return 1;
        case 3:
            if (func_020eaa6c(point, &ORIGIN)) {
                *point = actor->position;
            }
            if (FieldActor_PointsAhead(actor, &ahead, point)) {
                Vec3 copy = ahead;
                func_ov003_02215f00(actor, &copy, 6, -1);
            } else {
                func_ov003_02215ce4(actor, 6, -1);
            }
            return 1;
        case 4:
            func_ov003_02214644(actor, 6, -1);
            return 1;
        case 5:
            FieldActor_RequestState63(actor, 6, -1);
            return 1;
        case 6:
            FieldActor_RequestState64(actor, 6, -1);
            return 1;
        case 7:
            FieldActor_RequestState82(actor, 6, -1);
            return 1;
        case 8:
            FieldActor_RequestState80(actor, 6, -1);
            return 1;
        case 9:
            FieldActor_RequestState81(actor, 6, -1);
            return 1;
        case 0:
        case 10:
            if (func_020eaa6c(point, &ORIGIN)) {
                func_0200fa8c(&tile, actor);
                *point = tile;
            }
            func_0200fa8c(&tile, actor);
            if (func_020ea990(&actor->position, point) < 0x2334 && func_0200ff28(actor, &tile, 1, 0)) {
                int not_kind_1 = func_0200ffec(actor) == 1 ? 0 : 1;
                FieldActor_RequestState68(actor, tile.x, tile.z, not_kind_1, 0, 6, -1);
                return 1;
            }
            if (tool == 10) {
                func_ov003_02217450(actor, 6, -1);
                return 1;
            }
            break;
        default:
            break;
    }
    return 0;
}
CLEAN_AS(func_ov003_0220c3d0, FieldActor_UseTool)

/* func_ov003_0220c57c: what the held tool does this frame, if anything; whether an action
 * started. In order:
 *  - with 0x140 set, the tool's action at the origin;
 *  - when aim_point is out of the tool's range: func_02010004 when 0x144 is 1 or 0x148 is set,
 *    then the last check;
 *  - with 0x144 = 1, FieldActor_TryTargetMode2, then for tools 0, 1, 2 and 10 the action at
 *    aim_point (tool 10 as tool 0) while 0x144 is still set; with 0x144 = 2, tool 4's action;
 *  - with aim_mode 2, tool 5 on a map object of families A, B or C at aim_point;
 *  - with 0x148 set, func_02010004;
 *  - with aim_mode 2: tool 1 at the point ahead towards aim_point (aim_point stands in for it
 *    meanwhile), tool 5 at the origin, tool 3 at aim_point if func_02031614 accepts it;
 *  - last, with no tool, 0x140 set and func_020ba310, state 0x72. */
int FieldActor_TryTool(FieldActor *actor)
{
    int tool = func_0200fbe0(actor);
    Vec3 point;

    if (actor->unk_140 != 0) {
        point = ORIGIN;
        if (FieldActor_UseTool(actor, tool, &point)) {
            return 1;
        }
    }

    if (!func_0201005c(actor, &actor->aim_point, tool)) {
        if ((actor->unk_144 == 1 || actor->unk_148 != 0) && func_02010004(actor, tool)) {
            return 1;
        }
        goto last;
    }

    switch (actor->unk_144) {
        case 1:
            if (FieldActor_TryTargetMode2(actor, &tool)) {
                return 1;
            }
            if ((tool == 2 || tool == 1 || tool == 10 || tool == 0) && actor->unk_144 != 0) {
                point = actor->aim_point;
                if (FieldActor_UseTool(actor, tool == 10 ? 0 : tool, &point)) {
                    return 1;
                }
            }
            break;
        case 2:
            if (tool == 4) {
                point = ORIGIN;
                if (FieldActor_UseTool(actor, tool, &point)) {
                    return 1;
                }
            }
            break;
        default:
            break;
    }

    if (actor->aim_mode == 2 && tool == 5) {
        int x;
        int z;
        func_0204f818(&x, &z, &actor->aim_point);
        u16 *object = map_object_at(x, z);
        if (object != NULL && is_family_object(*object)) {
            point = ORIGIN;
            if (FieldActor_UseTool(actor, tool, &point)) {
                return 1;
            }
        }
    }

    if (actor->unk_148 != 0 && func_02010004(actor, tool)) {
        return 1;
    }
    if (actor->aim_mode != 2) {
        goto last;
    }

    switch (tool) {
        case 1: {
            s16 angle = Math_Atan2(sub32(actor->aim_point.x, actor->start_position.x),
                                   sub32(actor->aim_point.z, actor->start_position.z));
            Vec3 ahead;
            func_0200fa1c(&ahead, actor, &actor->position, &angle, data_ov003_02236608);
            if (!func_0201005c(actor, &ahead, tool)) {
                goto last;
            }
            Vec3 saved = actor->aim_point;
            actor->aim_point = ahead;
            point = ORIGIN;
            int started = FieldActor_UseTool(actor, tool, &point);
            actor->aim_point = saved;
            if (started) {
                return 1;
            }
            goto last;
        }
        case 5:
            point = ORIGIN;
            if (FieldActor_UseTool(actor, tool, &point)) {
                return 1;
            }
            goto last;
        case 3:
            if (!func_02031614(&actor->aim_point)) {
                goto last;
            }
            point = actor->aim_point;
            if (FieldActor_UseTool(actor, tool, &point)) {
                return 1;
            }
            goto last;
        default:
            break;
    }

last:
    if (tool == 0 && actor->unk_140 != 0 && func_020ba310()) {
        FieldActor_RequestState72(actor, 6, -1);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0220c57c, FieldActor_TryTool)

/* func_ov003_0220c934: looks up the object the actor has met (has_other, other_kind,
 * other_id) and records the verdict in other_result: 0 none met, 1 met but not found, 2 found
 * in main's tables (kinds 2 and 3), 3 found among overlay 3's eight (kinds 0x11 and 0x12),
 * 4 a kind 2 or 3 object accepted the held item 0x1376 or 0x1377 (its vtable slot 24 said 1).
 * A found object is kept in `other` unless the held item is 0x1376 or 0x1377. Whether one was
 * met. */
int FieldActor_CheckOther(FieldActor *actor)
{
    actor->other_result = 0;
    if (actor->has_other == 0) {
        return 0;
    }
    actor->other_result = 1;

    int kind = actor->other_kind;
    int id = actor->other_id;
    u16 item;
    func_020110c4(&item, actor);

    switch (kind) {
        case 2:
        case 3: {
            GameObject *object = func_02082618(kind, id);
            if (object != NULL) {
                if (is_item_1376(item)) {
                    ItemQuery query = (ItemQuery) (uintptr_t) object->vtable[24];
                    if (query(object, &item) == 1) {
                        actor->other_result = 4;
                        break;
                    }
                } else {
                    actor->other = object;
                }
                actor->other_result = 2;
            }
            break;
        }
        case 0x11:
        case 0x12: {
            GameObject *object = func_ov003_02236204(id);
            if (object != NULL) {
                if (!is_item_1376(item)) {
                    actor->other = object;
                }
                actor->other_result = 3;
            }
            break;
        }
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_ov003_0220c934, FieldActor_CheckOther)

/* func_ov003_0220ca24: a level from 0 to 7 kept in the player's record that rises by one
 * after 0x4650 frames (five minutes) spent outside from 10:00 to 16:59 between 16 July and
 * 15 September, unless func_020ba4d4 says 3 or more or the held item is in 0x1380-0x13a7; by
 * all appearances the summer tan. The countdown (func_02096274) and the flags
 * (func_0209626c) live outside the actor; nothing happens unless 0x7f8 is set. While flag 0
 * is set, func_0200f86c must return 1 for the update to go on, and the flag is cleared (and
 * flag 4 with it unless func_0200ee0c). On a rise the date goes to func_0200f7ac packed as
 * year (7 bits), month (4 bits) and day (5 bits), and flags 0 and 1 are set, 2 cleared.
 * QUIRK: a level of 255 rises to 0. */
void FieldActor_UpdateSunLevel(FieldActor *actor)
{
    if (actor->unk_7F8 == 0) {
        return;
    }
    BOOL keep_flag_4 = func_0200ee0c(actor) != 0;

    u16 *countdown = func_02096274();
    if (*countdown == 0) {
        *countdown = 1;
    }
    u8 *flags = func_0209626c();
    void *record = func_02011368(actor);

    DateTime now = {0};
    func_0209e474(&now);

    if ((*flags & 1) != 0) {
        if (func_0200f86c(actor) != 1) {
            return;
        }
        *flags &= keep_flag_4 ? 0xfe : 0xee;
    }

    BOOL summer = now.month == 8 || (now.month == 7 && now.day >= 16) || (now.month == 9 && now.day <= 15);
    if (!summer) {
        return;
    }
    if (now.hour < 10 || now.hour >= 17) {
        return;
    }
    if (func_020ba4d4() >= 3) {
        return;
    }
    u16 item;
    func_020110c4(&item, actor);
    if (in_range(item, 0x1380, 0x139f)) {
        return;
    }
    func_020110c4(&item, actor);
    if (in_range(item, 0x13a0, 0x13a7)) {
        return;
    }

    *countdown -= 1;
    if (*countdown != 0) {
        return;
    }
    u16 date = (u16) ((now.year & 0x7f) | (now.month & 0xf) << 7 | (now.day & 0x1f) << 11);
    u8 level = (u8) (func_020112bc(actor) + 1);
    if (level > 7) {
        level = 7;
    }
    func_020997b4(record, level);
    func_0200f7ac(actor, record, &date);
    *countdown = 0x4650;
    *flags &= 0xfb;
    *flags |= 3;
    func_0200f11c(actor);
}
CLEAN_AS(func_ov003_0220ca24, FieldActor_UpdateSunLevel)

/* func_ov003_0220cbb4: with a tile pending (flag 0x16), what func_0200fea0 left in 0x818
 * decides: 1 acts on the tile (state 0x73) and drops it, 2 drops it; dropping it
 * clears flags 0x16 and 0x13. */
void FieldActor_FinishPendingTile(FieldActor *actor)
{
    if (!func_0200f290(actor, FIELD_ACTOR_FLAG_PENDING_TILE)) {
        return;
    }
    switch (actor->unk_818) {
        case 1: {
            int tile[2] = {actor->pending_tile[0], actor->pending_tile[1]};
            FieldActor_RequestState73(actor, tile, 6, -1);
            func_0200f268(actor, FIELD_ACTOR_FLAG_PENDING_TILE);
            func_0200f268(actor, 0x13);
            break;
        }
        case 2:
            func_0200f268(actor, FIELD_ACTOR_FLAG_PENDING_TILE);
            func_0200f268(actor, 0x13);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_0220cbb4, FieldActor_FinishPendingTile)

/* func_ov003_0220cc24: unless flag 11 or 0x16 is set, func_0200ea0c refuses the state or a
 * target is held already, looks for a target on the actor's tile with func_020438dc (mode by
 * tool: 1 -> 2, 2 -> 1, 4 -> 3, 5 -> 4, others 0) and keeps it. A target of kind 0x19 makes the
 * tile pending (func_0200e854, flags 0x16 and 0x13). */
void FieldActor_FindTileTarget(FieldActor *actor)
{
    if (func_0200f290(actor, 11)) {
        return;
    }
    if (func_0200f290(actor, FIELD_ACTOR_FLAG_PENDING_TILE)) {
        return;
    }
    if (!func_0200ea0c(actor, actor->state)) {
        return;
    }
    if (actor->target != -1) {
        return;
    }

    int x = 0;
    int z = 0;
    func_0204f818(&x, &z, &actor->position);

    int mode;
    switch (func_0200fbe0(actor)) {
        case 1:
            mode = 2;
            break;
        case 2:
            mode = 1;
            break;
        case 4:
            mode = 3;
            break;
        case 5:
            mode = 4;
            break;
        default:
            mode = 0;
            break;
    }

    int tile[2] = {x, z};
    actor->target = func_020438dc(actor->player, tile, mode);
    if (actor->target == -1) {
        return;
    }
    if (func_0200ffec(actor) != 0x19) {
        return;
    }
    func_0200e854(actor);
    func_0200f27c(actor, FIELD_ACTOR_FLAG_PENDING_TILE);
    func_0200f27c(actor, 0x13);
    actor->pending_tile[0] = x;
    actor->pending_tile[1] = z;
}
CLEAN_AS(func_ov003_0220cc24, FieldActor_FindTileTarget)

/* func_ov003_0220cd08: when 0x98 is above 0x53f, follows the tile under the actor: a tile
 * other than the last one seen goes to func_020448b8. */
void FieldActor_TrackTile(FieldActor *actor)
{
    if (actor->unk_098 <= 0x53f) {
        return;
    }
    int x = 0;
    int z = 0;
    func_0204f818(&x, &z, &actor->position);
    BOOL same = x == actor->tile[0] && z == actor->tile[1];
    actor->tile[0] = x;
    actor->tile[1] = z;
    if (!same) {
        int tile[2] = {x, z};
        func_020448b8(tile);
    }
}
CLEAN_AS(func_ov003_0220cd08, FieldActor_TrackTile)

/* func_ov003_0220cd84: follows the tile 0x10cd ahead of the actor: on reaching a new one that
 * holds a map object of a growth line (or one at its last stage only), tells
 * func_ov003_02224384. */
void FieldActor_TrackFrontTile(FieldActor *actor)
{
    Vec3 ahead;
    int x = 0;
    int z = 0;

    func_0200fa1c(&ahead, actor, &actor->position, &actor->yaw, &data_ov003_02238128);
    func_0204f818(&x, &z, &ahead);
    BOOL same = x == actor->front_tile[0] && z == actor->front_tile[1];
    actor->front_tile[0] = x;
    actor->front_tile[1] = z;
    if (same) {
        return;
    }
    u16 *object = map_object_at(x, z);
    if (object == NULL || !is_growth_object(*object)) {
        return;
    }
    int tile[2] = {x, z};
    func_ov003_02224384(actor->player, tile, 1);
}
CLEAN_AS(func_ov003_0220cd84, FieldActor_TrackFrontTile)

/* func_ov003_0220ced4: the point 0x6000 ahead of the actor in the direction of `toward` (the
 * way it faces when `toward` is its own position) goes to `ahead`; whether func_02031614
 * accepts both it and the point 0x5000 ahead. */
int FieldActor_PointsAhead(FieldActor *actor, Vec3 *ahead, const Vec3 *toward)
{
    s16 angle;
    Vec3 point;

    if (func_020eaa6c(toward, &actor->position)) {
        angle = actor->yaw;
    } else {
        angle = Math_Atan2(sub32(toward->x, actor->position.x), sub32(toward->z, actor->position.z));
    }
    func_0200fa1c(&point, actor, &actor->position, &angle, &data_ov003_02238124);
    *ahead = point;
    int far_ok = func_02031614(ahead);
    func_0200fa1c(&point, actor, &actor->position, &angle, &data_ov003_0223810c);
    return far_ok && func_02031614(&point);
}
CLEAN_AS(func_ov003_0220ced4, FieldActor_PointsAhead)

/* func_ov003_0220cf68: a verdict 0-9 on the tile of `at` for func_ov003_02212574. With
 * `*check_other`, an object met gives 2 and func_0200fdd0 on the tile (2, 3) may decide
 * (0 -> 7, 1 -> 0, 2 -> 2). Otherwise 0x818 decides: 2 -> 7, 0 -> 0, else 0x814 picks it. */
int FieldActor_ClassifyAt(FieldActor *actor, const Vec3 *at, const u8 *check_other)
{
    int x;
    int z;

    func_0204f818(&x, &z, at);
    if (*check_other) {
        if (FieldActor_CheckOther(actor)) {
            return 2;
        }
        int tile[2] = {x, z};
        switch (func_0200fdd0(actor, tile, 2, 3)) {
            case 0:
                return 7;
            case 1:
                return 0;
            case 2:
                return 2;
            default:
                break;
        }
    }
    if (actor->unk_818 == 2) {
        return 7;
    }
    if (actor->unk_818 == 0) {
        return 0;
    }
    switch (actor->unk_814) {
        case 23:
            return 1;
        case 12:
        case 13:
            return 2;
        case 14:
            return 8;
        case 19:
        case 20:
            return 6;
        case 9:
        case 21:
            return 5;
        case 10:
        case 22:
            return 9;
        case 11:
            return 4;
        default:
            return 3;
    }
}
CLEAN_AS(func_ov003_0220cf68, FieldActor_ClassifyAt)

/* func_ov003_0220d040: a verdict 0-6 on the ground ahead of the actor for
 * func_ov003_02216c9c; its tile goes to `tile` when that is not null. With `*check_other`, an
 * object met gives 4. Ground of a surface other than 4 and 6 gives 4 when 0x1000 or higher,
 * else 1; surface 6 holding a map object of a short line gives 1. Then, with `*check_other`,
 * ground below 0x1000 gives 1 and func_0200fdd0 on the tile (1, `*mode`) may decide (0 -> 5,
 * 1 -> 0, 2 -> 4); otherwise 0x818 decides: 1 lets 0x814 pick it, 2 -> 5, others 0.
 * REQUIRES: func_0204f5a8 finds an object on surface 6 (the ROM reads through its result
 * unchecked). */
int FieldActor_ClassifyAhead(FieldActor *actor, const u8 *check_other, const u8 *mode, int *tile)
{
    Vec3 ahead;
    int x;
    int z;
    int surface;

    if (*check_other != 0 && FieldActor_CheckOther(actor)) {
        return 4;
    }
    func_0200fa6c(&ahead, actor);
    func_0204f818(&x, &z, &ahead);
    if (tile != NULL) {
        tile[0] = x;
        tile[1] = z;
    }

    fx32 height = func_020310d0(&ahead, &surface, 0x19);
    if (surface != 4 && surface != 6) {
        return height >= 0x1000 ? 4 : 1;
    }
    if (surface == 6 && data_021c80bc != NULL) {
        u16 *object = func_0204f5a8(data_021c80bc, &ahead, 0);
        if (is_short_line_object(*object)) {
            return 1;
        }
    }

    if (*check_other != 0) {
        if (height < 0x1000) {
            return 1;
        }
        int pair[2] = {x, z};
        switch (func_0200fdd0(actor, pair, 1, *mode)) {
            case 0:
                return 5;
            case 1:
                return 0;
            case 2:
                return 4;
            default:
                break;
        }
    }

    if (actor->unk_818 == 1) {
        switch (actor->unk_814) {
            case 6:
                return 2;
            case 7:
                return 3;
            case 12:
            case 13:
                return 4;
            case 14:
                return 6;
            default:
                return 1;
        }
    }
    return actor->unk_818 == 2 ? 5 : 0;
}
CLEAN_AS(func_ov003_0220d040, FieldActor_ClassifyAhead)

/* func_ov003_0220d1a8: an action on what lies at the point (ahead of the actor at the first
 * distance of 0x02236608, or aim_point), when it is within range 0xd and func_0200ff28 finds
 * something there for `*tool` (mode 2); whether one started. */
int FieldActor_TryTargetMode2(FieldActor *actor, int *tool)
{
    Vec3 point;

    if (actor->aim_mode == 1) {
        func_0200fa1c(&point, actor, &actor->position, &actor->yaw, data_ov003_02236608);
    } else {
        point = actor->aim_point;
    }
    return func_0201005c(actor, &point, 0xd) && func_0200ff28(actor, &point, 2, *tool) && func_0200fd04(actor, &point, 0);
}
CLEAN_AS(func_ov003_0220d1a8, FieldActor_TryTargetMode2)

/* func_ov003_0220d268: leaves the current state: when func_02010718 is positive, for state 3
 * (func_0200d1a0) after storing the state's next one; otherwise through func_02010538. */
int FieldActor_ResumeMoving(FieldActor *actor)
{
    if (func_02010718(actor) > 0) {
        actor->next_state = func_02008258(actor, actor->state);
        return func_0200d1a0(actor, 0, 1, -1);
    }
    return func_02010538(actor);
}
CLEAN_AS(func_ov003_0220d268, FieldActor_ResumeMoving)

/* ---- State 0x8f: the head follows a target */

/* func_ov003_0220d2a4: state 0x8f's update. */
void FieldActor_UpdateLook(FieldActor *actor)
{
    func_02010f5c(actor);
    if (func_0200f554(actor)) {
        func_0201100c(actor);
    }
    func_02010d64(actor);
    FieldActor_TrackLookTarget(actor);
}
CLEAN_AS(func_ov003_0220d2a4, FieldActor_UpdateLook)

/* func_ov003_0220d2d0: while tracking, turns the head towards the player's target
 * (func_ov003_0222a918) from 0x1b33 above the actor: the pitch held within -0x1000..0x1800, the
 * head reset when the target is more than about 60 degrees to the side. Without a target the
 * head is reset and the actor leaves the state (state 5 or 2, by exit_kind). */
void FieldActor_TrackLookTarget(FieldActor *actor)
{
    if (actor->work.look.track == 0) {
        return;
    }
    int player = actor->player;
    if (func_ov003_0222a938(player)) {
        Vec3 target = *func_ov003_0222a918(player);
        Vec3 head = actor->position;
        head.y = add32(head.y, 0x1b33);

        int yaw = Math_Atan2(sub32(target.x, head.x), sub32(target.z, head.z));
        int distance = func_020ea990(&target, &head);
        int pitch = Math_Atan2(sub32(target.y, head.y), distance);
        if (pitch >= 0x1800) {
            pitch = 0x1800;
        } else if (pitch <= -0x1000) {
            pitch = -0x1000;
        }
        yaw = (s16) (yaw - actor->yaw);
        if ((u16) (yaw + 0x2aaa) >= 0x5554) {
            func_02095518(0, 0, actor->player);
        } else {
            func_02011404(&actor->head_pitch, pitch, 0x400, 0x1770000, 0xc0000);
            func_02011404(&actor->head_yaw, yaw, 0x400, 0x1770000, 0xc0000);
        }
    } else {
        func_02095518(0, 0, actor->player);
        actor->next_state = func_02008258(actor, actor->state);
        if (actor->work.look.exit_kind != 0) {
            func_0200c9a8(actor, 3, 5, -1);
        } else {
            func_0200d4e8(actor, 3, 1, -1);
        }
    }
}
CLEAN_AS(func_ov003_0220d2d0, FieldActor_TrackLookTarget)

/* func_ov003_0220d410: state 0x8f's message handler: asks for state 0x8f again with the saved
 * arguments, priority 6 and `arg`. */
void FieldActor_LookMessage(FieldActor *actor, int arg)
{
    u8 track;
    u8 exit_kind;

    LookArgs_Get(&actor->saved.look, &track, &exit_kind);
    FieldActor_RequestLook(actor, &track, exit_kind, 6, (s16) arg);
}
CLEAN_AS(func_ov003_0220d410, FieldActor_LookMessage)

/* func_ov003_0220d444: entering state 0x8f: the request's two bytes become the state's
 * arguments, and are saved; with exit_kind 0 animation 0 starts. */
void FieldActor_EnterLook(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 track = request->payload[0];
    u8 exit_kind = request->payload[1];

    if (exit_kind == 0) {
        func_020109fc(actor, 0, 3, 3);
    }
    actor->work.look.track = track;
    actor->work.look.exit_kind = exit_kind;
    LookArgs_Set(&actor->saved.look, track, exit_kind);
}
CLEAN_AS(func_ov003_0220d444, FieldActor_EnterLook)

/* func_ov003_0220d484 */
void LookArgs_Get(const LookArgs *args, u8 *track, u8 *exit_kind)
{
    *track = args->track;
    *exit_kind = args->exit_kind;
}
CLEAN_AS(func_ov003_0220d484, LookArgs_Get)

/* func_ov003_0220d490 */
void LookArgs_Set(LookArgs *args, int track, int exit_kind)
{
    args->track = (u8) track;
    args->exit_kind = (u8) exit_kind;
}
CLEAN_AS(func_ov003_0220d490, LookArgs_Set)

/* func_ov003_0220d498: asks for state 0x8f with the two bytes; whether it was queued. */
int FieldActor_RequestLook(FieldActor *actor, const u8 *track, int exit_kind, int priority, s16 arg)
{
    const u8 payload[2] = {*track, (u8) exit_kind};
    return request_state(actor, 0x8f, priority, arg, payload, 2);
}
CLEAN_AS(func_ov003_0220d498, FieldActor_RequestLook)

/* ---- State 0x89 */

/* func_ov003_0220d4dc: state 0x89's update. */
void FieldActor_UpdateState89(FieldActor *actor)
{
    FieldActor_AnimateState89(actor);
    func_02010d64(actor);
    FieldActor_FaceState89Target(actor);
}
CLEAN_AS(func_ov003_0220d4dc, FieldActor_UpdateState89)

/* func_ov003_0220d4f8: once the animation is over, animation 0 starts. Before, while 0x704 is
 * 0: the actor turns towards the player's point of func_ov003_0222c1f4 and the pitch to it
 * (never upwards) goes to func_02095518 for player 4; without one (func_ov003_0222c364) the
 * pitch is reset and the actor leaves for state 5. */
void FieldActor_FaceState89Target(FieldActor *actor)
{
    if (func_02056f94(&actor->anim)) {
        func_020109fc(actor, 0, 3, 3);
        return;
    }
    if (actor->animation != 0) {
        return;
    }
    if (!func_ov003_0222c364(actor->player)) {
        func_02095518(0, 0, 4);
        actor->next_state = func_02008258(actor, actor->state);
        func_0200c9a8(actor, 3, 5, -1);
        return;
    }

    Vec3 target = *func_ov003_0222c1f4(actor->player);
    Vec3 here = actor->position;
    int yaw = Math_Atan2(sub32(target.x, here.x), sub32(target.z, here.z));
    int distance = func_020ea990(&target, &here);
    int pitch = Math_Atan2(sub32(target.y, here.y), distance);
    if (pitch > 0) {
        pitch = 0;
    }
    func_02095518(pitch, 0, 4);
    s16 body = actor->yaw;
    func_020113e0(&body, yaw);
    func_020110a0(actor, &body);
}
CLEAN_AS(func_ov003_0220d4f8, FieldActor_FaceState89Target)

/* func_ov003_0220d5d8: while 0x704 is 0x8f, frames 6 to 25 of the animation set flag 13, call
 * the actor's vtable slot 23 with 0x824 and grow the values at 0x830 from 0 at frame 6 to 1.0
 * at frame 11 (0x333 a frame); frame 25 clears flag 13 and calls func_ov003_0222c214. */
void FieldActor_AnimateState89(FieldActor *actor)
{
    func_02010f5c(actor);
    if (actor->animation != 0x8f) {
        return;
    }
    int frame = anim_frame(actor);
    if (frame < 6 || frame > 25) {
        return;
    }
    func_0200f27c(actor, 13);
    ((FieldActorSlot23) (uintptr_t) actor->vtable[23])(actor, &actor->unk_824);
    actor->unk_822 = 0x1520;
    fx32 value = frame >= 11 ? 0x1000 : (frame - 6) * 0x333;
    actor->unk_830[0] = value;
    actor->unk_830[1] = value;
    actor->unk_830[2] = value;
    if (frame == 25) {
        func_0200f268(actor, 13);
        func_ov003_0222c214(actor->player);
    }
}
CLEAN_AS(func_ov003_0220d5d8, FieldActor_AnimateState89)

/* func_ov003_0220d674: state 0x89's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State89Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState89(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220d674, FieldActor_State89Message)

/* func_ov003_0220d680: entering state 0x89: animation 0x8f and sound 0x4f. */
void FieldActor_EnterState89(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    func_020109a0(actor, 0x8f, 0, 0);
    func_0200f328(actor, 0x4f);
}
CLEAN_AS(func_ov003_0220d680, FieldActor_EnterState89)

/* func_ov003_0220d69c: asks for state 0x89; whether it was queued. */
void *FieldActor_RequestState89(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x89, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220d69c, FieldActor_RequestState89)

/* ---- State 0x82: the held item is used up with effect 0x31 */

/* func_ov003_0220d6d4: state 0x82's update. */
void FieldActor_UpdateState82(FieldActor *actor)
{
    FieldActor_AnimateState82(actor);
    func_0201100c(actor);
    func_02010d64(actor);
    FieldActor_EndState82(actor);
}
CLEAN_AS(func_ov003_0220d6d4, FieldActor_UpdateState82)

/* func_ov003_0220d6f4: at the animation's end the actor leaves for state 2; the player at
 * this console may leave from frame 0x18 on (FieldActor_ResumeMoving). */
void FieldActor_EndState82(FieldActor *actor)
{
    if (func_02056f94(&actor->anim)) {
        actor->next_state = func_02008258(actor, actor->state);
        func_0200d4e8(actor, 3, 1, -1);
    }
    if (is_local_player(actor) && anim_frame(actor) >= 0x18) {
        FieldActor_ResumeMoving(actor);
    }
}
CLEAN_AS(func_ov003_0220d6f4, FieldActor_EndState82)

/* func_ov003_0220d760: effect 0x31 at the point 0x68c (through func_0203f7d0) during frames 14
 * to 24, started on the first; on reaching frame 0x18 the player's held item and what the
 * actor holds become nothing. */
void FieldActor_AnimateState82(FieldActor *actor)
{
    func_02010f5c(actor);
    int frame = anim_frame(actor);
    if (frame >= 14 && frame <= 24) {
        Vec3 at = actor->unk_68C;
        func_0203f7d0(&at, &at);
        if (actor->work.effect.effect == -1) {
            actor->work.effect.effect = func_020912d4(0x31, &at, &actor->yaw, 0);
        } else {
            func_02091278(actor->work.effect.effect, &at, &actor->yaw, 0);
        }
    }
    if (func_02056f28(&actor->anim, 0x18)) {
        void *record = func_020984fc(actor->player);
        u16 none = ITEM_NONE;
        func_0209971c(record, &none);
        u16 held_none = ITEM_NONE;
        func_0205eb8c(actor->held, &held_none, 0);
    }
}
CLEAN_AS(func_ov003_0220d760, FieldActor_AnimateState82)

/* func_ov003_0220d820: for the player at this console the held item goes to func_0200f1a4;
 * the effect ends. */
void FieldActor_FinishState82(FieldActor *actor)
{
    if (is_local_player(actor)) {
        u16 *item = func_02099728(func_020984fc(actor->player));
        if (item != NULL) {
            func_0200f1a4(actor, 3, *item);
        }
    }
    if (actor->work.effect.effect != -1) {
        func_0209129c(actor->work.effect.effect);
    }
}
CLEAN_AS(func_ov003_0220d820, FieldActor_FinishState82)

/* func_ov003_0220d874: state 0x82's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State82Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState82(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220d874, FieldActor_State82Message)

/* func_ov003_0220d880: entering state 0x82: no effect yet, animation 125, the held object in
 * pose 42, sound 0x85d. */
void FieldActor_EnterState82(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    actor->work.effect.effect = -1;
    func_020109a0(actor, 125, 3, 0);
    func_0205eae0(actor->held, 42, 0, 0);
    func_0200f328(actor, 0x85d);
}
CLEAN_AS(func_ov003_0220d880, FieldActor_EnterState82)

/* func_ov003_0220d8bc: asks for state 0x82; whether it was queued. */
void *FieldActor_RequestState82(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x82, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220d8bc, FieldActor_RequestState82)

/* ---- State 0x81: an effect by the held item 0x137f or another */

/* func_ov003_0220d8f4: state 0x81's update. */
void FieldActor_UpdateState81(FieldActor *actor)
{
    FieldActor_AnimateState81(actor);
    func_0201100c(actor);
    func_02010d64(actor);
    FieldActor_EndState81(actor);
}
CLEAN_AS(func_ov003_0220d8f4, FieldActor_UpdateState81)

/* func_ov003_0220d914: each frame the held object's animation is over, `count` and then
 * `count2` run down; when both are 0 the player's held item and what the actor holds become
 * nothing and the actor leaves for state 2. */
void FieldActor_EndState81(FieldActor *actor)
{
    if (!func_02056f94((const FrameCtrl *) (func_0205e8e4(actor->held) + 0x9c))) {
        return;
    }
    u8 *count = &actor->work.effect.count;
    if (*count != 0) {
        (*count)--;
    }
    if (*count != 0) {
        return;
    }
    u8 *count2 = &actor->work.effect.count2;
    if (*count2 != 0) {
        (*count2)--;
    }
    if (*count2 != 0) {
        return;
    }
    void *record = func_020984fc(actor->player);
    u16 none = ITEM_NONE;
    func_0209971c(record, &none);
    u16 held_none = ITEM_NONE;
    func_0205eb8c(actor->held, &held_none, 0);
    actor->next_state = func_02008258(actor, actor->state);
    func_0200d4e8(actor, 9, 1, -1);
}
CLEAN_AS(func_ov003_0220d914, FieldActor_EndState81)

/* func_ov003_0220d9b8: the effect follows the point 0x62c (through func_0203f7d0). Before it
 * exists, `count` counts frames: the 10th plays sound 0x85a (held item 0x137f) or 0x859 and
 * leaves the point ahead of the actor in 0x02260558 with 0x02260540 set; from the 10th on, the
 * effect is started (0x35 for item 0x137f, else 0x36). QUIRK: `count` is a byte; past 255 it
 * wraps to 0 and the wait starts again. */
void FieldActor_AnimateState81(FieldActor *actor)
{
    func_02010f5c(actor);
    Vec3 at = actor->unk_62C;
    func_0203f7d0(&at, &at);

    if (actor->work.effect.effect != -1) {
        func_02091278(actor->work.effect.effect, &at, &actor->yaw, 0);
        return;
    }
    u8 *count = &actor->work.effect.count;
    (*count)++;
    if (*count <= 9) {
        return;
    }
    u16 item;
    if (*count == 10) {
        func_020110c4(&item, actor);
        func_0200f328(actor, item == 0x137f ? 0x85a : 0x859);
        Vec3 ahead;
        func_0200fa6c(&ahead, actor);
        data_ov003_02260540 = 1;
        data_ov003_02260558 = ahead;
    }
    func_020110c4(&item, actor);
    actor->work.effect.effect = func_020912d4(item == 0x137f ? 0x35 : 0x36, &at, &actor->yaw, 0);
}
CLEAN_AS(func_ov003_0220d9b8, FieldActor_AnimateState81)

/* func_ov003_0220daac: for the player at this console the held item goes to func_0200f1a4,
 * then func_0203b144 and func_02036448 run; the effect ends; the point ahead of the actor goes
 * to 0x02260558 with 0x02260540 cleared. */
void FieldActor_FinishState81(FieldActor *actor)
{
    if (is_local_player(actor)) {
        u16 *item = func_02099728(func_020984fc(actor->player));
        if (item != NULL) {
            func_0200f1a4(actor, 3, *item);
        }
        func_0203b144();
        func_02036448(data_021c526c + 0x1c4);
    }
    if (actor->work.effect.effect != -1) {
        func_0209129c(actor->work.effect.effect);
    }
    Vec3 ahead;
    func_0200fa6c(&ahead, actor);
    data_ov003_02260540 = 0;
    data_ov003_02260558 = ahead;
}
CLEAN_AS(func_ov003_0220daac, FieldActor_FinishState81)

/* func_ov003_0220db40: state 0x81's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State81Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState81(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220db40, FieldActor_State81Message)

/* func_ov003_0220db4c: entering state 0x81: no effect yet, `count` from 0, `count2` from 20,
 * animation 0x7c, the held object in pose 0x28; for the player at this console func_0203ae98
 * and func_02036450 run. */
void FieldActor_EnterState81(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    actor->work.effect.effect = -1;
    actor->work.effect.count = 0;
    actor->work.effect.count2 = 20;
    func_020109fc(actor, 0x7c, 9, 0);
    func_0205eae0(actor->held, 0x28, 0, 1);
    if (is_local_player(actor)) {
        func_0203ae98();
        func_02036450(data_021c526c + 0x1c4);
    }
}
CLEAN_AS(func_ov003_0220db4c, FieldActor_EnterState81)

/* func_ov003_0220dbb4: asks for state 0x81; whether it was queued. */
int FieldActor_RequestState81(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x81, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220dbb4, FieldActor_RequestState81)

/* ---- State 0x80: the held item is used up with effect 0x24 */

/* func_ov003_0220dbec: state 0x80's update. */
void FieldActor_UpdateState80(FieldActor *actor)
{
    FieldActor_AnimateState80(actor);
    func_0201100c(actor);
    func_02010d64(actor);
    FieldActor_EndState80(actor);
}
CLEAN_AS(func_ov003_0220dbec, FieldActor_UpdateState80)

/* func_ov003_0220dc0c: at the animation's end the actor moves on. The player at this console
 * who has the item 0x137d (func_02099e9c finds its slot) uses it instead: flag 0 is cleared,
 * the slot goes to func_0209a050 and func_ov003_02217c5c starts the next action. */
void FieldActor_EndState80(FieldActor *actor)
{
    if (!func_02056f94(&actor->anim)) {
        return;
    }
    u16 item = 0x137d;
    actor->next_state = func_02008258(actor, actor->state);
    if (is_local_player(actor)) {
        int slot = func_02099e9c(&item);
        if (slot != -1) {
            func_0200f268(actor, 0);
            func_02095694(0x15, actor->player);
            func_0209a050(slot);
            func_ov003_02217c5c(actor, 2, 2, 0, 0, 0, 6, -1);
            return;
        }
    }
    func_0200d4e8(actor, 3, 1, -1);
}
CLEAN_AS(func_ov003_0220dc0c, FieldActor_EndState80)

/* func_ov003_0220dcb0: on reaching frame 13 the player's held item and what the actor holds
 * become nothing, sound 0x850 plays, effect 0x24 starts at the point 0x68c (through
 * func_0203f7d0) and flag 9 is set. */
void FieldActor_AnimateState80(FieldActor *actor)
{
    func_02010f5c(actor);
    if (!func_02056f28(&actor->anim, 13)) {
        return;
    }
    void *record = func_020984fc(actor->player);
    u16 none = ITEM_NONE;
    func_0209971c(record, &none);
    u16 held_none = ITEM_NONE;
    func_0205eb8c(actor->held, &held_none, 0);
    func_0200f328(actor, 0x850);
    Vec3 at = actor->unk_68C;
    func_0203f7d0(&at, &at);
    func_020912d4(0x24, &at, &actor->yaw, 0);
    func_0200f27c(actor, 9);
}
CLEAN_AS(func_ov003_0220dcb0, FieldActor_AnimateState80)

/* func_ov003_0220dd50: for the player at this console the held item goes to func_0200f1a4. */
void FieldActor_FinishState80(FieldActor *actor)
{
    if (is_local_player(actor)) {
        u16 *item = func_02099728(func_020984fc(actor->player));
        if (item != NULL) {
            func_0200f1a4(actor, 3, *item);
        }
    }
}
CLEAN_AS(func_ov003_0220dd50, FieldActor_FinishState80)

/* func_ov003_0220dd90: state 0x80's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State80Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState80(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220dd90, FieldActor_State80Message)

/* func_ov003_0220dd9c: entering state 0x80: animation 0x7b. */
void FieldActor_EnterState80(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    func_020109a0(actor, 0x7b, 3, 0);
}
CLEAN_AS(func_ov003_0220dd9c, FieldActor_EnterState80)

/* func_ov003_0220ddb0: asks for state 0x80; whether it was queued. */
int FieldActor_RequestState80(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x80, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220ddb0, FieldActor_RequestState80)

/* ---- State 0x78: five animations in a row, then a message under the name "obj_etc_player" */

/* func_ov003_0220dde8: state 0x78's update. */
void FieldActor_UpdateState78(FieldActor *actor)
{
    func_02010f5c(actor);
    func_02010d64(actor);
    FieldActor_RunState78(actor);
}
CLEAN_AS(func_ov003_0220dde8, FieldActor_UpdateState78)

/* func_ov003_0220de04: animations 0x71 to 0x75 follow each other as each ends; during 0x72
 * func_0200faa8 runs (0x3ae), and the start of 0x74 plays sound 0x817 and, when the player's
 * record exists (func_020984e8), marks it (func_02099740, flag 0x19 once flag 0x17 is set) and
 * writes its value plus 0x10 at 0x70d. During 0x75 the actor turns to yaw 0 (func_0200faf0,
 * 0x59a), which on arrival runs func_02035624 and func_020356c4, and `step` goes:
 *   0: the receiver at 0xec is registered (func_0203ee14) as "obj_etc_player", flag 0x11 set,
 *      its byte 0x1e set to 20, the link's request raised and func_0203ae98 run; then as 1;
 *   1: once the link reports itself open, 2;
 *   2: once it is closed, the receiver is released (func_0203ee08), flags 0x11 and 7 cleared,
 *      the actor moves on and func_0203e19c, func_0203b144, func_02035638 and func_02035684 run.
 * REQUIRES: the link is set when `step` is 0 (the ROM writes through it unchecked there). */
void FieldActor_RunState78(FieldActor *actor)
{
    switch (actor->animation) {
        case 0x71:
            if (func_02056f94(&actor->anim)) {
                func_020109a0(actor, 0x72, 0, 0);
            }
            break;
        case 0x72:
            func_0200faa8(actor, 0x3ae);
            if (func_02056f94(&actor->anim)) {
                func_020109a0(actor, 0x73, 0, 0);
            }
            break;
        case 0x73:
            if (func_02056f94(&actor->anim)) {
                func_0200f328(actor, 0x817);
                func_020109a0(actor, 0x74, 0, 0);
                void *record = func_020984e8();
                if (record != NULL) {
                    func_02099740(record, 1);
                    func_0205dc94(actor->unk_70D, (int) (func_0209984c(record) + 0x10));
                    if (func_02099020(record, 0x17)) {
                        func_02098ff8(record, 0x19);
                    }
                }
            }
            break;
        case 0x74:
            if (func_02056f94(&actor->anim)) {
                func_020109a0(actor, 0x75, 0, 0);
            }
            break;
        case 0x75: {
            s16 yaw_before = actor->yaw;
            func_0200faf0(actor, 0x59a);
            if (yaw_before != 0 && actor->yaw == 0) {
                func_02035624(0x19);
                func_020356c4(0xd, 0x40, 0x7f, 1);
            }
            switch (actor->work.step) {
                case 0:
                    actor->work.step = 1;
                    func_0203ee14(actor, actor->receiver);
                    func_0200f27c(actor, 0x11);
                    func_020a8164(actor->receiver, data_ov003_02238134);
                    actor->receiver_unk_1E = 20;
                    actor->link->requested = 1;
                    func_0203ae98();
                    /* fall through */
                case 1:
                    if (actor->link != NULL && actor->link->open != 0) {
                        actor->work.step = 2;
                    }
                    break;
                case 2:
                    if (actor->link != NULL && actor->link->open == 0) {
                        func_0203ee08(actor, actor->receiver);
                        func_0200f268(actor, 0x11);
                        func_0203e19c();
                        actor->next_state = func_02008258(actor, actor->state);
                        func_0200d4e8(actor, 3, 1, -1);
                        func_0200f268(actor, 7);
                        func_0203b144();
                        func_02035638(0x40);
                        func_02035684(0xc, 0xf, 5);
                    }
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov003_0220de04, FieldActor_RunState78)

/* func_ov003_0220e004: state 0x78's message handler: messages are ignored. */
void FieldActor_State78Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_0220e004, FieldActor_State78Message)

/* func_ov003_0220e008: entering state 0x78: animation 0x71, `step` 0, the held object in pose
 * 0x13 with tool 3, flag 0x1a cleared, func_02035638 and func_02035684. */
void FieldActor_EnterState78(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    func_020109a0(actor, 0x71, 3, 0);
    actor->work.step = 0;
    if (func_0200fbe0(actor) == 3) {
        func_0205eae0(actor->held, 0x13, 3, 0);
    }
    func_0200f268(actor, 0x1a);
    func_02035638(0x3f);
    func_02035684(0x19, 0xf, 0);
}
CLEAN_AS(func_ov003_0220e008, FieldActor_EnterState78)

/* func_ov003_0220e05c: asks for state 0x78, setting flag 7 when it is queued; whether it was.
 * BUG: as in request_state, the bytes of the request nothing sets are the stack's. */
int FieldActor_RequestState78(FieldActor *actor, int priority, int arg)
{
    StateRequest request;

#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    func_0200e92c(&request);
    func_0200e90c(&request, 0x78, priority, arg);
    int queued = func_0200e894(actor, &request) != 0;
    if (queued) {
        func_0200f27c(actor, 7);
    }
    func_0200e91c(&request);
    return queued;
}
CLEAN_AS(func_ov003_0220e05c, FieldActor_RequestState78)

/* ---- State 0x75: the end of state 0x74, with a splash */

/* func_ov003_0220e0a8: state 0x75's update. */
void FieldActor_UpdateState75(FieldActor *actor)
{
    func_02010f5c(actor);
    func_02010d64(actor);
    FieldActor_EndState75(actor);
}
CLEAN_AS(func_ov003_0220e0a8, FieldActor_UpdateState75)

/* func_ov003_0220e0c4: at the animation's end the actor moves on (func_0200d4e8 with 3, or 9
 * holding tool 4). */
void FieldActor_EndState75(FieldActor *actor)
{
    if (!func_02056f94(&actor->anim)) {
        return;
    }
    actor->next_state = func_02008258(actor, actor->state);
    func_0200d4e8(actor, func_0200fbe0(actor) == 4 ? 9 : 3, 1, -1);
}
CLEAN_AS(func_ov003_0220e0c4, FieldActor_EndState75)

/* func_ov003_0220e11c: state 0x75's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State75Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState75(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220e11c, FieldActor_State75Message)

/* func_ov003_0220e128: entering state 0x75: animation 0x94 with tools 3, 4 and 10 (the held
 * object in pose 0x12 with tool 4), else 0x93; effect 0x91 at the actor (0x90 unless the
 * ground there is of kind 0x13), flag 9, func_ov003_02220b44 with the position, sound 0x7e9. */
void FieldActor_EnterState75(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    int tool = func_0200fbe0(actor);
    if (tool == 10 || tool == 3 || tool == 4) {
        func_020109a0(actor, 0x94, 3, 0);
        if (func_0200fbe0(actor) == 4) {
            func_0205eae0(actor->held, 0x12, 3, 1);
        }
    } else {
        func_020109a0(actor, 0x93, 3, 0);
    }

    Vec3 at = actor->position;
    GroundInfo ground;
    func_02034270(&ground, &at, 0, 0);
    func_02091254(ground.kind == 0x13 ? 0x91 : 0x90, &at, 0, 0);
    func_0200f27c(actor, 9);
    Vec3 position = actor->position;
    func_ov003_02220b44(actor->player, &position);
    func_0200f328(actor, 0x7e9);
    func_0203423c(&ground);
}
CLEAN_AS(func_ov003_0220e128, FieldActor_EnterState75)

/* func_ov003_0220e1f0: asks for state 0x75; whether it was queued. */
void *FieldActor_RequestState75(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x75, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220e1f0, FieldActor_RequestState75)

/* ---- State 0x74: the pad and the movement push a progress on to state 0x75 */

/* The effect at effect_point: started (kind `kind`) when there is none, else moved there. */
static void follow_effect(FieldActor *actor, int *effect, int kind)
{
    if (*effect == -1) {
        *effect = func_020912d4(kind, &actor->effect_point, NULL, 0);
    } else {
        func_02091278(*effect, &actor->effect_point, NULL, 0);
    }
}

/* A velocity of `speed` in the direction `angle`, on the ground plane. */
static void velocity(Vec3 *out, fx32 speed, u16 angle)
{
    out->y = 0;
    out->x = FX_MulFunc(FX_SinCosTable_[(angle >> 4) * 2], speed);
    out->z = FX_MulFunc(FX_SinCosTable_[(angle >> 4) * 2 + 1], speed);
}

/* An arithmetic shift right by 12 (whole units of a 20.12 value). */
static int whole(fx32 value)
{
    return value < 0 ? ~(~value >> 12) : value >> 12;
}

/* func_ov003_0220e228: state 0x74's update. */
void FieldActor_UpdateState74(FieldActor *actor)
{
    FieldActor_AnimateState74(actor);
    func_02010d64(actor);
    FieldActor_RunState74(actor);
}
CLEAN_AS(func_ov003_0220e228, FieldActor_UpdateState74)

/* func_ov003_0220e244: for the player at this console, each frame's push is the change of the
 * actor's velocity since the frame before (from a length of 0x59a on, scaled so that 0x59a is
 * 25.0) plus 20.0 for each of A, B, X, Y, L, R, START and SELECT pressed, or 2.0 when it is 0.
 * It adds to `progress` (never below 0) and its whole part goes to `effort`; when the actor
 * moves or a button was pressed sound 0x7ef plays. min_anim_speed becomes 0.5 plus
 * 1.75 * 0.65 * progress / 400. Flag 11 or a progress of 400.0 asks for state 0x75. */
void FieldActor_RunState74(FieldActor *actor)
{
    if (!is_local_player(actor)) {
        return;
    }
    State74Work *work = &actor->work.s74;

    Vec3 before;
    velocity(&before, work->move_speed, work->move_angle);
    fx32 speed = (fx32) func_0200dc8c(actor);
    u16 angle = (u16) func_0200dc80(actor);
    Vec3 now;
    velocity(&now, speed, angle);
    work->move_speed = speed;
    work->move_angle = angle;

    Vec3 change;
    func_020eaca0(&change, &before, &now);
    fx32 push = 0;
    if (VEC_Mag(&change) >= 0x59a) {
        push = FX_Div(FX_MulFunc(VEC_Mag(&change), 0x6400), 0x59a);
    }

    static const u16 buttons[] = {BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y, BUTTON_L, BUTTON_R, BUTTON_START, BUTTON_SELECT};
    int bonus = 0;
    for (size_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        if (data_021fbe40.pressed & buttons[i]) {
            bonus += 20;
        }
    }
    push = add32(push, bonus << 12);
    if (push == 0) {
        push = 0x2000;
    }

    work->progress = add32(work->progress, push);
    work->effort = whole(push);
    if (work->progress < 0) {
        work->progress = 0;
    }
    /* The ROM tests the push for 0 here again; it cannot be by now. */
    if (speed != 0 || bonus != 0) {
        func_0200f328(actor, 0x7ef);
    }
    work->min_anim_speed = add32(FX_Div(FX_MulFunc(FX_MulFunc(0x1c00, work->progress), 0xa66), 0x190000), 0x800);

    if (func_0200f290(actor, 11) || work->progress >= 0x190000) {
        FieldActor_RequestState75(actor, 6, -1);
    }
}
CLEAN_AS(func_ov003_0220e244, FieldActor_RunState74)

/* func_ov003_0220e424: the animation speeds up by 1.2 a frame while `effort` is 10 or more,
 * else slows by 0.3, kept within min_anim_speed..2.25 (the held object follows with tool 4);
 * effect 0x4c follows effect_point and func_0200f2a0 runs with the position. */
void FieldActor_AnimateState74(FieldActor *actor)
{
    State74Work *work = &actor->work.s74;

    work->anim_speed = add32(work->anim_speed, work->effort >= 10 ? 0x1333 : -0x4cd);
    if (work->anim_speed > 0x2400) {
        work->anim_speed = 0x2400;
    } else if (work->anim_speed < work->min_anim_speed) {
        work->anim_speed = work->min_anim_speed;
    }
    actor->anim.speed = work->anim_speed;
    if (func_0200fbe0(actor) == 4) {
        func_0205eac4(actor->held, work->anim_speed);
    }
    func_02010f5c(actor);
    follow_effect(actor, &work->effect, 0x4c);
    func_0200f2a0(actor, 0x8a, &actor->position);
}
CLEAN_AS(func_ov003_0220e424, FieldActor_AnimateState74)

/* func_ov003_0220e4d0: leaving state 0x74 for `next`: the effect ends; unless for state 0x75,
 * func_ov003_02220b44 gets the position. */
void FieldActor_ExitState74(FieldActor *actor, int next)
{
    if (actor->work.s74.effect != -1) {
        func_0209129c(actor->work.s74.effect);
    }
    if (next == 0x75) {
        return;
    }
    Vec3 position = actor->position;
    func_ov003_02220b44(actor->player, &position);
}
CLEAN_AS(func_ov003_0220e4d0, FieldActor_ExitState74)

/* func_ov003_0220e518: state 0x74's message handler: in state 0x73 nothing happens, in state
 * 0x74 `arg` is kept at 0xc84, else state 0x74 is asked for (no effect, priority 6, `arg`). */
void FieldActor_State74Message(FieldActor *actor, int arg)
{
    switch (actor->state) {
        case 0x73:
            break;
        case 0x74:
            actor->unk_C84 = (s16) arg;
            break;
        default:
            FieldActor_RequestState74(actor, -1, 6, arg);
            break;
    }
}
CLEAN_AS(func_ov003_0220e518, FieldActor_State74Message)

/* func_ov003_0220e548: entering state 0x74: animation 0x92 at speed 0.5, the work cleared to
 * the actor's movement now, the request's effect kept, flag 9 cleared; with tool 4 the held
 * object in pose 0x11 at speed 0.5. */
void FieldActor_EnterState74(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    State74Work *work = &actor->work.s74;
    int effect;
    memcpy(&effect, request->payload, sizeof(effect));

    func_020109fc(actor, 0x92, 3, 0);
    actor->anim.speed = 0x800;
    work->anim_speed = 0x800;
    work->min_anim_speed = 0x800;
    work->effort = 0;
    work->progress = 0;
    work->move_speed = (fx32) func_0200dc8c(actor);
    work->move_angle = (u16) func_0200dc80(actor);
    work->effect = effect;
    func_0200f268(actor, 9);
    if (func_0200fbe0(actor) == 4) {
        func_0205eae0(actor->held, 0x11, 3, 0);
        func_0205eac4(actor->held, 0x800);
    }
}
CLEAN_AS(func_ov003_0220e548, FieldActor_EnterState74)

/* func_ov003_0220e5c4: asks for state 0x74 carrying an effect handle; whether it was queued. */
int FieldActor_RequestState74(FieldActor *actor, int effect, int priority, int arg)
{
    u8 payload[sizeof(effect)];
    memcpy(payload, &effect, sizeof(effect));
    return request_state(actor, 0x74, priority, arg, payload, (int) sizeof(payload));
}
CLEAN_AS(func_ov003_0220e5c4, FieldActor_RequestState74)

/* ---- State 0x73: the actor steps onto a tile and starts state 0x74 there */

/* func_ov003_0220e600: state 0x73's update. */
void FieldActor_UpdateState73(FieldActor *actor)
{
    FieldActor_AnimateState73(actor);
    FieldActor_RunState73(actor);
}
CLEAN_AS(func_ov003_0220e600, FieldActor_UpdateState73)

/* func_ov003_0220e614: during animation 0x90 the actor moves to the tile's point
 * (func_0200fbc4), and nothing else happens until it is there; then the animation is made to
 * stop at its end. At the end of animation 0x91, state 0x74 is asked for with the effect and
 * flag 9 is set; at the end of the other, animation 0x91 starts with effect 0x8f at the
 * actor (0x8e unless the ground is of kind 0x13), sound 0x7e8, flag 9, func_ov003_02221228
 * with the position, flag 0x12 cleared and, with tool 4, the held object in pose 0x10. */
void FieldActor_RunState73(FieldActor *actor)
{
    if (actor->animation == 0x90) {
        fx32 x = actor->work.s73.x;
        fx32 z = actor->work.s73.z;
        func_0200fbc4(actor, x, z, actor->yaw);
        if (actor->position.x != x || actor->position.z != z) {
            return;
        }
        actor->anim.flags = FRAME_CTRL_ONCE;
    }
    if (!func_02056f94(&actor->anim)) {
        return;
    }
    if (actor->animation == 0x91) {
        FieldActor_RequestState74(actor, actor->work.s73.effect, 6, -1);
        func_0200f27c(actor, 9);
        return;
    }

    func_020109a0(actor, 0x91, 3, 0);
    Vec3 at = actor->position;
    GroundInfo ground;
    func_02034270(&ground, &at, 0, 0);
    func_02091254(ground.kind == 0x13 ? 0x8f : 0x8e, &at, 0, 0);
    func_0200f328(actor, 0x7e8);
    func_0200f27c(actor, 9);
    Vec3 copy = at;
    func_ov003_02221228(actor->player, &copy);
    func_0200f268(actor, 0x12);
    if (func_0200fbe0(actor) == 4) {
        func_0205eae0(actor->held, 0x10, 3, 1);
    }
    func_0203423c(&ground);
}
CLEAN_AS(func_ov003_0220e614, FieldActor_RunState73)

/* func_ov003_0220e738: effect 0x4c follows effect_point and func_0200f2a0 runs with the
 * position. */
void FieldActor_AnimateState73(FieldActor *actor)
{
    func_02010f5c(actor);
    follow_effect(actor, &actor->work.s73.effect, 0x4c);
    func_0200f2a0(actor, 0x8a, &actor->position);
}
CLEAN_AS(func_ov003_0220e738, FieldActor_AnimateState73)

/* func_ov003_0220e788: leaving state 0x73 for `next`: the actor is put on the tile's point.
 * With flag 0x12 set it is cleared, after func_ov003_02221228 with the position when `next`
 * is 0x74 or 0x75; for other states func_ov003_02220b44 gets the position. The effect ends
 * unless state 0x74 takes it over. */
void FieldActor_ExitState73(FieldActor *actor, int next)
{
    actor->position.x = actor->work.s73.x;
    actor->position.z = actor->work.s73.z;
    BOOL continues = next == 0x74 || next == 0x75;

    if (func_0200f290(actor, 0x12)) {
        if (continues) {
            Vec3 position = actor->position;
            func_ov003_02221228(actor->player, &position);
        }
        func_0200f268(actor, 0x12);
    }
    if (!continues) {
        Vec3 position = actor->position;
        func_ov003_02220b44(actor->player, &position);
    }
    if (next != 0x74 && actor->work.s73.effect != -1) {
        func_0209129c(actor->work.s73.effect);
    }
}
CLEAN_AS(func_ov003_0220e788, FieldActor_ExitState73)

/* func_ov003_0220e828: state 0x73's message handler: asks for it again with the saved tile,
 * priority 6 and `arg`. */
void FieldActor_State73Message(FieldActor *actor, int arg)
{
    u8 x;
    u8 z;

    TileArgs_Get(&actor->saved.tile, &x, &z);
    int tile[2] = {x, z};
    FieldActor_RequestState73(actor, tile, 6, arg);
}
CLEAN_AS(func_ov003_0220e828, FieldActor_State73Message)

/* func_ov003_0220e860: entering state 0x73: the request's tile gives the point to reach, no
 * effect yet, animation 0x90 (the held object in pose 0xf with tool 4), the tile is saved and
 * sound 0x7ee plays. */
void FieldActor_EnterState73(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 x = request->payload[0];
    u8 z = request->payload[1];
    Vec3 point;

    func_0204f794(&point, x, z);
    actor->work.s73.x = point.x;
    actor->work.s73.z = point.z;
    actor->work.s73.effect = -1;
    func_020109fc(actor, 0x90, 3, 0);
    if (func_0200fbe0(actor) == 4) {
        func_0205eae0(actor->held, 0xf, 3, 0);
    }
    TileArgs_Set(&actor->saved.tile, x, z);
    func_0200f328(actor, 0x7ee);
}
CLEAN_AS(func_ov003_0220e860, FieldActor_EnterState73)

/* func_ov003_0220e8e0 */
void TileArgs_Get(const TileArgs *args, u8 *x, u8 *z)
{
    *x = args->x;
    *z = args->z;
}
CLEAN_AS(func_ov003_0220e8e0, TileArgs_Get)

/* func_ov003_0220e8ec */
void TileArgs_Set(TileArgs *args, int x, int z)
{
    args->x = (u8) x;
    args->z = (u8) z;
}
CLEAN_AS(func_ov003_0220e8ec, TileArgs_Set)

/* func_ov003_0220e8f4: asks for state 0x73 for a tile (its low bytes); whether it was
 * queued. */
int FieldActor_RequestState73(FieldActor *actor, const int *tile, int priority, int arg)
{
    const u8 payload[2] = {(u8) tile[0], (u8) tile[1]};
    return request_state(actor, 0x73, priority, arg, payload, 2);
}
CLEAN_AS(func_ov003_0220e8f4, FieldActor_RequestState73)

/* ---- State 0x72 */

/* func_ov003_0220e938: state 0x72's update. */
void FieldActor_UpdateState72(FieldActor *actor)
{
    func_02010f5c(actor);
    func_0201100c(actor);
    func_02010d64(actor);
    FieldActor_SlowDown(actor);
    FieldActor_EndState72(actor);
}
CLEAN_AS(func_ov003_0220e938, FieldActor_UpdateState72)

/* func_ov003_0220e960: the actor turns to yaw 0 (func_0200faf0, 0x59a); at the animation's end
 * it moves on, and the player at this console may leave from frame 0x1a on
 * (FieldActor_ResumeMoving). */
void FieldActor_EndState72(FieldActor *actor)
{
    func_0200faf0(actor, 0x59a);
    if (func_02056f94(&actor->anim)) {
        actor->next_state = func_02008258(actor, actor->state);
        func_0200d4e8(actor, 3, 1, -1);
    }
    if (is_local_player(actor) && anim_frame(actor) >= 0x1a) {
        FieldActor_ResumeMoving(actor);
    }
}
CLEAN_AS(func_ov003_0220e960, FieldActor_EndState72)

/* func_ov003_0220e9d8: the word at 0x98, while not 0, comes down by 0x171 a frame to 0
 * (func_0201107c stores it). */
void FieldActor_SlowDown(FieldActor *actor)
{
    if (actor->unk_098 != 0) {
        int value = func_020113a4(actor->unk_098, 0, 0x171);
        func_0201107c(actor, &value);
    }
}
CLEAN_AS(func_ov003_0220e9d8, FieldActor_SlowDown)

/* func_ov003_0220ea04: state 0x72's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State72Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState72(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220ea04, FieldActor_State72Message)

/* func_ov003_0220ea10: entering state 0x72: animation 0x9c; for the player at this console
 * func_020ba2ec runs. */
void FieldActor_EnterState72(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    func_020109a0(actor, 0x9c, 3, 0);
    if (is_local_player(actor)) {
        func_020ba2ec();
    }
}
CLEAN_AS(func_ov003_0220ea10, FieldActor_EnterState72)

/* func_ov003_0220ea40: asks for state 0x72; whether it was queued. */
void *FieldActor_RequestState72(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x72, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220ea40, FieldActor_RequestState72)

/* ---- State 0x71: two animations by the tool held, with effects */

/* func_ov003_0220ea78: state 0x71's update. */
void FieldActor_UpdateState71(FieldActor *actor)
{
    FieldActor_RunState71(actor);
    FieldActor_AnimateState71(actor);
    func_0201100c(actor);
    func_02010d64(actor);
    FieldActor_EndState71(actor);
}
CLEAN_AS(func_ov003_0220ea78, FieldActor_UpdateState71)

/* func_ov003_0220eaa0: until `done`, the word at 0x98 comes down by 0x7b a frame to 0; once it
 * is 0 and the first animation is over, the second starts by the tool: 0x8e for tools 4 (the
 * held object in pose 8), 3 (pose 0x1e) and 10, else 0x8c. For the player at this console the
 * record's flag 0x1a is then set once flag 0x17 is. */
void FieldActor_RunState71(FieldActor *actor)
{
    if (actor->work.s71.done) {
        return;
    }
    int value = func_020113a4(actor->unk_098, 0, 0x7b);
    func_0201107c(actor, &value);
    if (actor->unk_098 != 0) {
        return;
    }
    if (!func_02056f94(&actor->anim)) {
        return;
    }

    switch (actor->work.s71.tool) {
        case 4:
            func_0205eae0(actor->held, 8, 3, 0);
            func_020109a0(actor, 0x8e, 3, 0);
            break;
        case 3:
            func_0205eae0(actor->held, 0x1e, 3, 0);
            func_020109a0(actor, 0x8e, 3, 0);
            break;
        case 10:
            func_020109a0(actor, 0x8e, 3, 0);
            break;
        default:
            func_020109a0(actor, 0x8c, 3, 0);
            break;
    }
    actor->work.s71.done = 1;

    if (!is_local_player(actor)) {
        return;
    }
    void *record = func_020984e8();
    if (record != NULL && func_02099020(record, 0x17)) {
        func_02098ff8(record, 0x1a);
    }
}
CLEAN_AS(func_ov003_0220eaa0, FieldActor_RunState71)

/* func_ov003_0220eb8c: at the end of the second animation the actor moves on and 0x8e8 is set
 * to 60. */
void FieldActor_EndState71(FieldActor *actor)
{
    if (actor->work.s71.done == 1 && func_02056f94(&actor->anim)) {
        actor->next_state = func_02008258(actor, actor->state);
        func_0200d4e8(actor, 3, 1, -1);
        actor->unk_8E8 = 60;
    }
}
CLEAN_AS(func_ov003_0220eb8c, FieldActor_EndState71)

/* func_ov003_0220ebe0: during the first animation: on reaching frame 10 with the item 0x137c
 * held, effect 0x32 at the point 0x68c (through func_0203f7d0; the actor's position while
 * that point is the origin) and func_02095694; on reaching frames 7 and 9, effects 0x39 and
 * 0x37 at points ahead of the actor (0x02238110, 0x02238118), facing its way. */
void FieldActor_AnimateState71(FieldActor *actor)
{
    func_02054860(actor->unk_234);
    s16 yaw = actor->yaw;
    if (actor->work.s71.done) {
        return;
    }

    if (func_02056f28(&actor->anim, 10)) {
        u16 item;
        func_020110c4(&item, actor);
        if (item == 0x137c) {
            Vec3 at;
            if (actor->unk_68C.x == 0 && actor->unk_68C.y == 0 && actor->unk_68C.z == 0) {
                at = actor->position;
            } else {
                at = actor->unk_68C;
                func_0203f7d0(&at, &at);
            }
            func_020912d4(0x32, &at, NULL, 0);
            func_02095694(0, actor->player);
        }
    }

    if (func_02056f28(&actor->anim, 7)) {
        Vec3 ahead;
        func_0200fa1c(&ahead, actor, &actor->position, &yaw, data_ov003_02238110);
        Vec3 at = ahead;
        func_020912d4(0x39, &at, &yaw, 0);
    }
    if (func_02056f28(&actor->anim, 9)) {
        Vec3 ahead;
        func_0200fa1c(&ahead, actor, &actor->position, &yaw, data_ov003_02238118);
        Vec3 at = ahead;
        func_020912d4(0x37, &at, &yaw, 0);
    }
}
CLEAN_AS(func_ov003_0220ebe0, FieldActor_AnimateState71)

/* func_ov003_0220ed24: state 0x71's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State71Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState71(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220ed24, FieldActor_State71Message)

/* func_ov003_0220ed30: entering state 0x71: the tool is kept and the first animation starts
 * by it: 0x8d for tools 4 (the held object in pose 7), 3 (pose 0x1d) and 10, else 0x8b; flag 9
 * is set and sound 0x7db plays. */
void FieldActor_EnterState71(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    int tool = func_0200fbe0(actor);
    actor->work.s71.tool = tool;

    switch (tool) {
        case 4:
            func_0205eae0(actor->held, 7, 2, 1);
            func_020109a0(actor, 0x8d, 2, 0);
            break;
        case 3:
            func_0205eae0(actor->held, 0x1d, 2, 1);
            func_020109a0(actor, 0x8d, 2, 0);
            break;
        case 10:
            func_020109a0(actor, 0x8d, 2, 0);
            break;
        default:
            func_020109a0(actor, 0x8b, 2, 0);
            break;
    }
    actor->work.s71.done = 0;
    func_0200f27c(actor, 9);
    func_0200f328(actor, 0x7db);
}
CLEAN_AS(func_ov003_0220ed30, FieldActor_EnterState71)

/* func_ov003_0220edcc: asks for state 0x71; whether it was queued. */
int FieldActor_RequestState71(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x71, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220edcc, FieldActor_RequestState71)

/* ---- State 0x6e: the actor turns to face yaw 0 */

/* func_ov003_0220ee04: state 0x6e's update. */
void FieldActor_UpdateState6E(FieldActor *actor)
{
    FieldActor_AnimateState6E(actor);
    func_02010d64(actor);
    FieldActor_RunState6E(actor);
}
CLEAN_AS(func_ov003_0220ee04, FieldActor_UpdateState6E)

/* Whether a held item code is nothing; for a code func_0204bcdc accepts, by comparing
 * func_0204bc64 of it and of nothing. */
static BOOL holds_nothing(u16 *item)
{
    if (func_0204bcdc(item)) {
        item[1] = ITEM_NONE;
        int held = func_0204bc64(&item[0]);
        return held == func_0204bc64(&item[1]);
    }
    return item[0] == ITEM_NONE;
}

/* func_ov003_0220ee20: once the animation is over, animation 1 starts and the actor turns to
 * yaw 0 (func_0200faf0, 0x59a); when it faces that way func_02035a70, func_0200f3e8 and
 * func_0203e110 run and the actor moves on: holding an item, through func_ov003_02217c5c,
 * else with func_0200d4e8 (3) and flag 0 set. */
void FieldActor_RunState6E(FieldActor *actor)
{
    if (func_02056f94(&actor->anim)) {
        actor->work.step = 1;
        func_020109fc(actor, 1, 3, 0);
    }
    if (actor->work.step == 0) {
        return;
    }
    if (!func_0200faf0(actor, 0x59a)) {
        return;
    }
    func_02035a70(data_021c526c + 0x2e4);
    func_0200f3e8(actor);
    func_0203e110();
    actor->next_state = func_02008258(actor, actor->state);

    u16 item[2];
    func_020110c4(&item[0], actor);
    if (!holds_nothing(item)) {
        func_ov003_02217c5c(actor, 2, 2, 0, 0, 0, 6, -1);
    } else {
        func_0200d4e8(actor, 3, 1, -1);
        func_0200f27c(actor, 0);
    }
}
CLEAN_AS(func_ov003_0220ee20, FieldActor_RunState6E)

/* func_ov003_0220ef1c: only while the byte 0x021c75b8 is 2: during animation 0x6a frames 0x13,
 * 0x19 and 0x1e run func_0200f888; during any other func_0200f95c runs each frame. */
void FieldActor_AnimateState6E(FieldActor *actor)
{
    if (data_021c75b8 != 2) {
        return;
    }
    func_02010f5c(actor);
    if (actor->animation == 0x6a) {
        int frame = anim_frame(actor);
        if (frame == 0x13 || frame == 0x19 || frame == 0x1e) {
            func_0200f888(actor);
        }
    } else {
        func_0200f95c(actor);
    }
}
CLEAN_AS(func_ov003_0220ef1c, FieldActor_AnimateState6E)

/* func_ov003_0220ef74: state 0x6e's message handler: asks for it again (priority 7, `arg`). */
void FieldActor_State6EMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState6E(actor, 7, arg);
}
CLEAN_AS(func_ov003_0220ef74, FieldActor_State6EMessage)

/* func_ov003_0220ef80: entering state 0x6e: the actor faces yaw -0x8000 (away from yaw 0),
 * flag 0 is cleared, animation 0x6a starts and sound 0x818 plays. */
void FieldActor_EnterState6E(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    actor->work.step = 0;
    s16 yaw = -0x8000;
    func_020110a0(actor, &yaw);
    func_0200f268(actor, 0);
    func_020109a0(actor, 0x6a, 0, 0);
    func_0200f328(actor, 0x818);
}
CLEAN_AS(func_ov003_0220ef80, FieldActor_EnterState6E)

/* func_ov003_0220efc8: asks for state 0x6e; whether it was queued. */
void *FieldActor_RequestState6E(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x6e, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220efc8, FieldActor_RequestState6E)

/* ---- State 0x6d */

/* func_ov003_0220f000: state 0x6d's update. */
void FieldActor_UpdateState6D(FieldActor *actor)
{
    FieldActor_AnimateState6D(actor);
    func_02010d64(actor);
    FieldActor_RunState6D(actor);
}
CLEAN_AS(func_ov003_0220f000, FieldActor_UpdateState6D)

/* func_ov003_0220f01c: on reaching frame 0x2e with `kind` 2 or more, func_02035624 and
 * func_02035ac8 run. Otherwise, on reaching frame 0x2f, for the player at this console, the
 * point func_0204e108 gives (0x2000 further on z for player 0 with a nonzero kind), or
 * func_0204e08c for the other players with a nonzero kind, goes to func_020b63f4 with
 * func_020b5e10's object; with kind 0 the actor's own position goes there once
 * func_0204e108 succeeds. */
void FieldActor_RunState6D(FieldActor *actor)
{
    Vec3 point;

    if (func_02056f28(&actor->anim, 0x2e)) {
        if (actor->work.s6d.kind >= 2) {
            func_02035624(0xc);
            func_02035ac8(data_021c526c + 0x2e4);
        }
        return;
    }
    if (!func_02056f28(&actor->anim, 0x2f)) {
        return;
    }
    u32 source = func_0204e414();
    if (!is_local_player(actor)) {
        return;
    }
    if (actor->work.s6d.kind == 0) {
        if (func_0204e108(source, &point, 0, 0)) {
            func_020b63f4(func_020b5e10(), 0, &actor->position, 0x1b800000, 0, 2, 2);
        }
    } else if (actor->player == 0) {
        if (func_0204e108(source, &point, 0, 0)) {
            point.z = add32(point.z, 0x2000);
            func_020b63f4(func_020b5e10(), 0, &point, 0x1b800000, 0, 2, 2);
        }
    } else {
        if (func_0204e08c(source, &point, 0, 0)) {
            func_020b63f4(func_020b5e10(), 0, &point, 0x1b800000, 0, 2, 2);
        }
    }
}
CLEAN_AS(func_ov003_0220f01c, FieldActor_RunState6D)

/* func_ov003_0220f128: effect 0x34 follows effect_point. */
void FieldActor_AnimateState6D(FieldActor *actor)
{
    func_02010f5c(actor);
    follow_effect(actor, &actor->work.s6d.effect, 0x34);
}
CLEAN_AS(func_ov003_0220f128, FieldActor_AnimateState6D)

/* func_ov003_0220f16c: state 0x6d's message handler: asks for it again with kind 0, priority 7
 * and `arg`. */
void FieldActor_State6DMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState6D(actor, 0, 7, arg);
}
CLEAN_AS(func_ov003_0220f16c, FieldActor_State6DMessage)

/* func_ov003_0220f180: entering state 0x6d with the request's kind: animation 0x69 for tools 3
 * (the held object in pose 0x14), 4 (pose 2) and 10, else 0x68; func_0203e420; effect 0x34 at
 * effect_point. A kind of 2 or more also runs RtcSendPxiCommand(0x51), sound 0x839 (kind 2) or
 * 0x838 and func_02035684. Sound 0x816 plays. */
void FieldActor_EnterState6D(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 kind = request->payload[0];
    int tool = func_0200fbe0(actor);

    if (tool == 3 || tool == 4 || tool == 10) {
        func_020109a0(actor, 0x69, 3, 6);
        if (tool == 3) {
            func_0205eae0(actor->held, 0x14, 3, 1);
        } else if (tool == 4) {
            func_0205eae0(actor->held, 2, 9, 1);
        }
    } else {
        func_020109a0(actor, 0x68, 3, 6);
    }
    func_0203e420();
    actor->work.s6d.effect = func_020912d4(0x34, &actor->effect_point, NULL, 0);
    actor->work.s6d.kind = kind;
    if (kind >= 2) {
        RtcSendPxiCommand(0x51);
        func_0200f328(actor, kind == 2 ? 0x839 : 0x838);
        func_02035684(0xc, 0, 0);
    }
    func_0200f328(actor, 0x816);
}
CLEAN_AS(func_ov003_0220f180, FieldActor_EnterState6D)

/* func_ov003_0220f244: asks for state 0x6d with `kind`; whether it was queued. */
int FieldActor_RequestState6D(FieldActor *actor, char kind, int priority, int arg)
{
    const u8 payload[1] = {(u8) kind};
    return request_state(actor, 0x6d, priority, arg, payload, 1);
}
CLEAN_AS(func_ov003_0220f244, FieldActor_RequestState6D)

/* ---- Requests built in steps: the payload is written by a function of its own */

/* The start of a request for `state` (see request_state, whose BUG applies here too). */
static void begin_request(StateRequest *request, int state, int priority, int arg)
{
#ifdef BUGFIX
    *request = (StateRequest){0};
#endif
    func_0200e92c(request);
    func_0200e90c(request, state, priority, arg);
}

/* Queues a request begun with begin_request; whether it was queued. */
static int finish_request(FieldActor *actor, StateRequest *request)
{
    int queued = func_0200e894(actor, request);
    func_0200e91c(request);
    return queued;
}

/* Copies a point word by word in order x, y, z, as the game does: when `dst` overlaps `src`
 * (never in the game's calls) the words read are then the ones just written. */
static void copy_point(Vec3 *dst, const Vec3 *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

/* The whole number of frames in the animation. QUIRK: only the low 16 bits. */
static u32 anim_frames(const FieldActor *actor)
{
    return ((u32) actor->anim.end >> 12) & 0xffff;
}

/* ---- State 0x6c: animation 0x7a played backwards */

/* func_ov003_0220f280: state 0x6c's update. */
void FieldActor_UpdateState6C(FieldActor *actor)
{
    FieldActor_RunState6C(actor);
    func_02010d64(actor);
}
CLEAN_AS(func_ov003_0220f280, FieldActor_UpdateState6C)

/* func_ov003_0220f294: at the animation's end animation 0 starts, and the actors of the other
 * players note the state after this one (the actor of this console is moved on elsewhere). */
void FieldActor_RunState6C(FieldActor *actor)
{
    func_02010f5c(actor);
    if (func_02056f94(&actor->anim)) {
        func_020109fc(actor, 0, 3, 3);
        if (!is_local_player(actor)) {
            actor->next_state = func_02008258(actor, actor->state);
        }
    }
}
CLEAN_AS(func_ov003_0220f294, FieldActor_RunState6C)

/* func_ov003_0220f2ec: state 0x6c's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State6CMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState6C(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220f2ec, FieldActor_State6CMessage)

/* func_ov003_0220f2f8: entering state 0x6c: animation 0x7a (unless it is already playing) is
 * restarted to play once backwards from its last frame. */
void FieldActor_EnterState6C(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    if (actor->animation != 0x7a) {
        func_020109a0(actor, 0x7a, 3, 0);
    }
    u32 frames = anim_frames(actor);
    func_02056fcc(&actor->anim, frames, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000, (u16) (frames - 1));
}
CLEAN_AS(func_ov003_0220f2f8, FieldActor_EnterState6C)

/* func_ov003_0220f344: asks for state 0x6c; whether it was queued. */
int FieldActor_RequestState6C(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x6c, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220f344, FieldActor_RequestState6C)

/* ---- State 0x6b: an animation held on its last frame */

/* func_ov003_0220f37c: state 0x6b's update. */
void FieldActor_UpdateState6B(FieldActor *actor)
{
    func_02010f5c(actor);
    func_02010d64(actor);
}
CLEAN_AS(func_ov003_0220f37c, FieldActor_UpdateState6B)

/* func_ov003_0220f390: state 0x6b's message handler: asks for it again (priority 6, `arg`). */
void FieldActor_State6BMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState6B(actor, 6, arg);
}
CLEAN_AS(func_ov003_0220f390, FieldActor_State6BMessage)

/* func_ov003_0220f39c: entering state 0x6b: animation 0x7a if it is playing (state 0x6a's),
 * else animation 0x38, is put on its last frame. */
void FieldActor_EnterState6B(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    if (actor->animation != 0x7a) {
        func_020109a0(actor, 0x38, 3, 0);
    }
    actor->anim.frame = (fx32) (((anim_frames(actor) - 1) & 0xffff) << 12);
}
CLEAN_AS(func_ov003_0220f39c, FieldActor_EnterState6B)

/* func_ov003_0220f3d8: asks for state 0x6b; whether it was queued. */
int FieldActor_RequestState6B(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x6b, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0220f3d8, FieldActor_RequestState6B)

/* ---- State 0x6a: animation 0x7a at a point, facing yaw -0x8000; state 0x6b follows */

/* func_ov003_0220f410: state 0x6a's update. */
void FieldActor_UpdateState6A(FieldActor *actor)
{
    FieldActor_PlaceState6A(actor);
    func_02010f5c(actor);
    func_02010d64(actor);
    FieldActor_EndState6A(actor);
}
CLEAN_AS(func_ov003_0220f410, FieldActor_UpdateState6A)

/* func_ov003_0220f430: at the animation's end, asks for state 0x6b. */
void FieldActor_EndState6A(FieldActor *actor)
{
    if (func_02056f94(&actor->anim)) {
        FieldActor_RequestState6B(actor, 6, -1);
    }
}
CLEAN_AS(func_ov003_0220f430, FieldActor_EndState6A)

/* func_ov003_0220f458: the actor is put on the point (x and z), facing yaw -0x8000. */
void FieldActor_PlaceState6A(FieldActor *actor)
{
    func_0200fbc4(actor, actor->work.s6a_point.x, actor->work.s6a_point.z, -0x8000);
}
CLEAN_AS(func_ov003_0220f458, FieldActor_PlaceState6A)

/* func_ov003_0220f478: state 0x6a's message handler: asks for it again with the saved point,
 * priority 6 and `arg`. */
void FieldActor_State6AMessage(FieldActor *actor, int arg)
{
    Vec3 point;

    PackedPoint_Get(actor->saved.packed, &point);
    FieldActor_RequestState6A(actor, point, 6, (s16) arg);
}
CLEAN_AS(func_ov003_0220f478, FieldActor_State6AMessage)

/* func_ov003_0220f4a8: entering state 0x6a: animation 0x7a; the request's point is kept and
 * saved packed. */
void FieldActor_EnterState6A(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    func_020109a0(actor, 0x7a, 3, 0);
    Vec3 point = *(const Vec3 *) (const void *) request->payload;
    State6A_SetPoint(&actor->work.s6a_point, point);
    PackedPoint_Set(actor->saved.packed, &point);
}
CLEAN_AS(func_ov003_0220f4a8, FieldActor_EnterState6A)

/* func_ov003_0220f4f0: unpacks a point packed by PackedPoint_Set (its nibble is dropped). */
void PackedPoint_Get(const u8 *packed, Vec3 *point)
{
    u8 nibble;
    func_02077928(packed, &point->x, &point->y, &point->z, &nibble);
}
CLEAN_AS(func_ov003_0220f4f0, PackedPoint_Get)

/* func_ov003_0220f508: packs a point, with nibble 0. */
void PackedPoint_Set(u8 *packed, const Vec3 *point)
{
    func_02077950(packed, point->x, point->y, point->z, 0);
}
CLEAN_AS(func_ov003_0220f508, PackedPoint_Set)

/* func_ov003_0220f524 */
void State6A_SetPoint(Vec3 *dst, Vec3 value)
{
    *dst = value;
}
CLEAN_AS(func_ov003_0220f524, State6A_SetPoint)

/* func_ov003_0220f538: asks for state 0x6a at a point; whether it was queued (as a pointer). */
void *FieldActor_RequestState6A(FieldActor *actor, Vec3 point, u32 priority, s16 arg)
{
    StateRequest request;

    begin_request(&request, 0x6a, (int) priority, arg);
    State6A_SetRequestPoint((Vec3 *) (void *) request.payload, point);
    return (void *) (intptr_t) finish_request(actor, &request);
}
CLEAN_AS(func_ov003_0220f538, FieldActor_RequestState6A)

/* func_ov003_0220f57c */
void State6A_SetRequestPoint(Vec3 *dst, Vec3 value)
{
    *dst = value;
}
CLEAN_AS(func_ov003_0220f57c, State6A_SetRequestPoint)

/* ---- State 0x69: animation 0x67 turned towards a point; state 0x77 or func_0200d4e8 follows */

/* func_ov003_0220f590: state 0x69's update: the actor of this console turns; another player's
 * actor first walks to the tile's middle and turns once it is there. */
void FieldActor_UpdateState69(FieldActor *actor)
{
    FieldActor_AnimateState69(actor);
    if (is_local_player(actor)) {
        FieldActor_TurnState69(actor);
        func_02010d64(actor);
    } else {
        int tile[2] = {actor->work.s69.tile_x, actor->work.s69.tile_z};
        if (func_0200f530(actor, tile)) {
            FieldActor_TurnState69(actor);
        }
        func_02010d64(actor);
    }
    FieldActor_EndState69(actor);
}
CLEAN_AS(func_ov003_0220f590, FieldActor_UpdateState69)

/* func_ov003_0220f5f8: at the animation's end the actor moves on: to state 0x77 with its yaw
 * when then_77 is set, else through func_0200d4e8. */
void FieldActor_EndState69(FieldActor *actor)
{
    u8 then_77 = actor->work.s69.then_77;

    if (func_02056f94(&actor->anim)) {
        actor->next_state = func_02008258(actor, actor->state);
        if (then_77) {
            func_02008dc0(actor, (u16) actor->yaw, 6, -1);
        } else {
            func_0200d4e8(actor, 3, 1, -1);
        }
    }
}
CLEAN_AS(func_ov003_0220f5f8, FieldActor_EndState69)

/* func_ov003_0220f658: the actor turns towards the work's yaw. */
void FieldActor_TurnState69(FieldActor *actor)
{
    s16 yaw = actor->yaw;
    func_020113e0(&yaw, (s16) actor->work.s69.yaw);
    func_020110a0(actor, &yaw);
}
CLEAN_AS(func_ov003_0220f658, FieldActor_TurnState69)

/* func_ov003_0220f684: on reaching frame 5 the tile goes to func_ov003_02224384 (3), flag 0x12
 * is cleared and flag 9 set. */
void FieldActor_AnimateState69(FieldActor *actor)
{
    func_02010f5c(actor);
    if (!func_02056f28(&actor->anim, 5)) {
        return;
    }
    int tile[2] = {actor->work.s69.tile_x, actor->work.s69.tile_z};
    func_ov003_02224384(actor->player, tile, 3);
    func_0200f268(actor, 0x12);
    func_0200f27c(actor, 9);
}
CLEAN_AS(func_ov003_0220f684, FieldActor_AnimateState69)

/* func_ov003_0220f6d8: state 0x69's message handler does nothing. */
void FieldActor_State69Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_0220f6d8, FieldActor_State69Message)

/* func_ov003_0220f6dc: entering state 0x69: the yaw towards the request's point and the tile it
 * is on are kept with the flags, and animation 0x67 starts. */
void FieldActor_EnterState69(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const XZArgs *args = (const XZArgs *) (const void *) request->payload;
    u8 then_77 = args->then_77;
    u8 then_69 = args->then_69;
    Vec3 target = {args->x, actor->position.y, args->z};
    s16 yaw = Math_Atan2(sub32(target.x, actor->position.x), sub32(target.z, actor->position.z));
    int tile_x = 0;
    int tile_z = 0;

    func_0204f818(&tile_x, &tile_z, &target);
    State69Work_Set(&actor->work.s69, (u16) yaw, (u32) tile_x, (u32) tile_z, then_77, then_69);
    func_020109a0(actor, 0x67, 3, 0);
}
CLEAN_AS(func_ov003_0220f6dc, FieldActor_EnterState69)

/* func_ov003_0220f744 */
void State69Work_Set(State69Work *work, u16 yaw, u32 tile_x, u32 tile_z, u8 then_77, u8 then_69)
{
    work->unk_00 = 0;
    work->yaw = yaw;
    work->tile_x = (int) tile_x;
    work->tile_z = (int) tile_z;
    work->then_77 = then_77;
    work->then_69 = then_69;
}
CLEAN_AS(func_ov003_0220f744, State69Work_Set)

/* func_ov003_0220f768: asks for state 0x69 towards (x, z); whether it was queued. */
int FieldActor_RequestState69(FieldActor *actor, fx32 x, fx32 z, int then_77, u8 then_69, int priority, s16 arg)
{
    StateRequest request;

    begin_request(&request, 0x69, priority, arg);
    XZArgs_Set69((XZArgs *) (void *) request.payload, x, z, (u8) then_77, then_69);
    return finish_request(actor, &request);
}
CLEAN_AS(func_ov003_0220f768, FieldActor_RequestState69)

/* func_ov003_0220f7b8 */
void XZArgs_Set69(XZArgs *args, fx32 x, fx32 z, u8 then_77, u8 then_69)
{
    args->x = x;
    args->z = z;
    args->then_77 = then_77;
    args->then_69 = then_69;
}
CLEAN_AS(func_ov003_0220f7b8, XZArgs_Set69)

/* ---- State 0x68: animation 0x66 turned towards a point; state 0x69 may follow */

/* The tile under the work's point. */
static void state68_tile(const FieldActor *actor, int *tile)
{
    Vec3 at = {actor->work.s68.x, 0, actor->work.s68.z};

    tile[0] = 0;
    tile[1] = 0;
    func_0204f818(&tile[0], &tile[1], &at);
}

/* func_ov003_0220f7cc: state 0x68's update. In the fifth frame the tile goes to
 * func_ov003_02224384 (2), from the seventh on to func_ov003_022235d8 each frame. The actor of
 * this console turns; another player's actor turns only once func_0200f554 says it is in
 * place. */
void FieldActor_UpdateState68(FieldActor *actor)
{
    State68Work *work = &actor->work.s68;
    int tile[2];

    state68_tile(actor, tile);
    if (work->count > 5) {
        int copy[2] = {tile[0], tile[1]};
        func_ov003_022235d8(actor->player, copy);
    } else {
        work->count++;
        if (work->count == 5) {
            int copy[2] = {tile[0], tile[1]};
            func_ov003_02224384(actor->player, copy, 2);
        }
    }
    func_02010f5c(actor);
    if (is_local_player(actor)) {
        FieldActor_TurnState68(actor);
        func_02010d64(actor);
        FieldActor_EndState68Local(actor);
    } else {
        if (func_0200f554(actor)) {
            FieldActor_TurnState68(actor);
        }
        func_02010d64(actor);
        FieldActor_EndState68Remote(actor);
    }
}
CLEAN_AS(func_ov003_0220f7cc, FieldActor_UpdateState68)

/* func_ov003_0220f884: another player's actor: the state after this one is noted, and with
 * then_69 set, state 0x69 is asked for at the animation's end. */
void FieldActor_EndState68Remote(FieldActor *actor)
{
    State68Work *work = &actor->work.s68;

    actor->next_state = func_02008258(actor, actor->state);
    if (work->then_69 && func_02056f94(&actor->anim)) {
        FieldActor_RequestState69(actor, work->x, work->z, work->then_77, 1, 6, -1);
    }
}
CLEAN_AS(func_ov003_0220f884, FieldActor_EndState68Remote)

/* func_ov003_0220f8e0: the actor of this console: with then_69 set, state 0x69 is asked for at
 * the animation's end. Otherwise the word at 0x818 decides: 1 sets then_69 and makes the
 * animation stop at its end, 2 moves on through func_0200d4e8. */
void FieldActor_EndState68Local(FieldActor *actor)
{
    State68Work *work = &actor->work.s68;

    if (work->then_69) {
        if (func_02056f94(&actor->anim)) {
            FieldActor_RequestState69(actor, work->x, work->z, work->then_77, 1, 6, -1);
        }
    } else if (actor->unk_818 == 1) {
        work->then_69 = 1;
        actor->anim.flags = FRAME_CTRL_ONCE;
    } else if (actor->unk_818 == 2) {
        actor->next_state = func_02008258(actor, actor->state);
        func_0200d4e8(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_ov003_0220f8e0, FieldActor_EndState68Local)

/* func_ov003_0220f968: the actor turns towards the work's yaw. */
void FieldActor_TurnState68(FieldActor *actor)
{
    s16 yaw = actor->yaw;
    func_020113e0(&yaw, (s16) actor->work.s68.yaw);
    func_020110a0(actor, &yaw);
}
CLEAN_AS(func_ov003_0220f968, FieldActor_TurnState68)

/* func_ov003_0220f994: leaving state 0x68: another player's actor that leaves before its fifth
 * frame sends the tile to func_ov003_02224384 (2) now. */
void FieldActor_ExitState68(FieldActor *actor)
{
    if (is_local_player(actor)) {
        return;
    }
    if (actor->work.s68.count >= 5) {
        return;
    }
    int tile[2];
    state68_tile(actor, tile);
    int copy[2] = {tile[0], tile[1]};
    func_ov003_02224384(actor->player, copy, 2);
}
CLEAN_AS(func_ov003_0220f994, FieldActor_ExitState68)

/* func_ov003_0220f9f8: state 0x68's message handler: in state 0x68 `arg` is kept at 0xc84;
 * otherwise state 0x68 is asked for again with the saved point and flags, priority 6.
 * BUG: then_77 is taken as the whole flags byte being nonzero, so a request with only then_69
 * set comes back with then_77 set too. */
void FieldActor_State68Message(FieldActor *actor, int arg)
{
    fx32 x;
    fx32 z;
    u8 flags;

    if (actor->state == 0x68) {
        actor->unk_C84 = (s16) arg;
        return;
    }
    PackedXZ_Get(actor->saved.packed, &x, &z, &flags);
#ifdef BUGFIX
    int then_77 = (flags & 0xf) != 0;
#else
    int then_77 = flags != 0;
#endif
    FieldActor_RequestState68(actor, x, z, then_77, (flags >> 4) != 0, 6, (s16) arg);
}
CLEAN_AS(func_ov003_0220f9f8, FieldActor_State68Message)

/* func_ov003_0220fa5c: entering state 0x68: the request's point, the yaw towards it and the
 * flags are kept, the point and flags saved packed; animation 0x66 starts (by func_020109a0
 * when state 0x69 follows, else by func_020109fc) and flag 9 is set. */
void FieldActor_EnterState68(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const XZArgs *args = (const XZArgs *) (const void *) request->payload;
    u8 then_77 = args->then_77;
    u8 then_69 = args->then_69;
    fx32 x = args->x;
    fx32 z = args->z;
    s16 yaw = Math_Atan2(sub32(x, actor->position.x), sub32(z, actor->position.z));

    State68Work_Set(&actor->work.s68, yaw, x, z, then_77, then_69);
    PackedXZ_Set(actor->saved.packed, x, z, (u8) (then_77 | then_69 << 4));
    if (then_69) {
        func_020109a0(actor, 0x66, 3, 0);
    } else {
        func_020109fc(actor, 0x66, 3, 0);
    }
    func_0200f27c(actor, 9);
}
CLEAN_AS(func_ov003_0220fa5c, FieldActor_EnterState68)

/* func_ov003_0220fae4: unpacks x and z and the byte after them. */
void PackedXZ_Get(u8 *packed, fx32 *x, fx32 *z, u8 *flags)
{
    func_02077978(packed, x, z);
    *flags = packed[5];
}
CLEAN_AS(func_ov003_0220fae4, PackedXZ_Get)

/* func_ov003_0220fafc: packs x and z and the byte after them. */
void PackedXZ_Set(u8 *packed, fx32 x, fx32 z, int flags)
{
    func_020779b8(packed, x, z);
    packed[5] = (u8) flags;
}
CLEAN_AS(func_ov003_0220fafc, PackedXZ_Set)

/* func_ov003_0220fb14 */
void State68Work_Set(State68Work *work, int yaw, fx32 x, fx32 z, u8 then_77, u8 then_69)
{
    work->yaw = (u16) yaw;
    work->x = x;
    work->z = z;
    work->then_77 = then_77;
    work->then_69 = then_69;
    work->count = 0;
}
CLEAN_AS(func_ov003_0220fb14, State68Work_Set)

/* func_ov003_0220fb30: asks for state 0x68 towards (x, z); whether it was queued. */
int FieldActor_RequestState68(FieldActor *actor, fx32 x, fx32 z, int then_77, u8 then_69, int priority, s16 arg)
{
    StateRequest request;

    begin_request(&request, 0x68, priority, arg);
    XZArgs_Set68((XZArgs *) (void *) request.payload, x, z, (u8) then_77, then_69);
    return finish_request(actor, &request);
}
CLEAN_AS(func_ov003_0220fb30, FieldActor_RequestState68)

/* func_ov003_0220fb80 */
void XZArgs_Set68(XZArgs *args, fx32 x, fx32 z, u8 then_77, u8 then_69)
{
    args->x = x;
    args->z = z;
    args->then_77 = then_77;
    args->then_69 = then_69;
}
CLEAN_AS(func_ov003_0220fb80, XZArgs_Set68)

/* ---- State 0x67: animation 0x65 walking to a point, with effects */

/* func_ov003_0220fb94: state 0x67's update: the actor walks to the point and turns once
 * there. */
void FieldActor_UpdateState67(FieldActor *actor)
{
    FieldActor_AnimateState67(actor);
    Vec3 point = actor->work.s67.point;
    if (func_0200f434(actor, &point)) {
        FieldActor_TurnState67(actor);
    }
    func_02010d64(actor);
    if (is_local_player(actor)) {
        FieldActor_EndState67Local(actor);
    } else {
        FieldActor_EndState67Remote(actor);
    }
}
CLEAN_AS(func_ov003_0220fb94, FieldActor_UpdateState67)

/* func_ov003_0220fbf8: another player's actor: the state after this one is noted; at the
 * animation's end it moves on through func_0200d4e8. */
void FieldActor_EndState67Remote(FieldActor *actor)
{
    actor->next_state = func_02008258(actor, actor->state);
    if (func_02056f94(&actor->anim)) {
        func_0200d4e8(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_ov003_0220fbf8, FieldActor_EndState67Remote)

/* func_ov003_0220fc34: the actor of this console moves on at the animation's end, and may
 * leave from frame 22 on (FieldActor_ResumeMoving). */
void FieldActor_EndState67Local(FieldActor *actor)
{
    if (func_02056f94(&actor->anim)) {
        actor->next_state = func_02008258(actor, actor->state);
        func_0200d4e8(actor, 3, 1, -1);
    }
    if (anim_frame(actor) >= 22) {
        FieldActor_ResumeMoving(actor);
    }
}
CLEAN_AS(func_ov003_0220fc34, FieldActor_EndState67Local)

/* func_ov003_0220fc88: the actor turns towards the work's yaw. */
void FieldActor_TurnState67(FieldActor *actor)
{
    s16 yaw = actor->yaw;
    func_020113e0(&yaw, actor->work.s67.yaw);
    func_020110a0(actor, &yaw);
}
CLEAN_AS(func_ov003_0220fc88, FieldActor_TurnState67)

/* func_ov003_0220fcb4: during animation 0x65, on reaching frame 3 or 13, effect 0x23 starts at
 * the actor's position and yaw. */
void FieldActor_AnimateState67(FieldActor *actor)
{
    func_02010f5c(actor);
    if (actor->animation == 0x65) {
        if (func_02056f28(&actor->anim, 3) || func_02056f28(&actor->anim, 13)) {
            func_020912d4(0x23, &actor->position, &actor->yaw, 0);
        }
    }
}
CLEAN_AS(func_ov003_0220fcb4, FieldActor_AnimateState67)

/* func_ov003_0220fd00: state 0x67's message handler does nothing. */
void FieldActor_State67Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_0220fd00, FieldActor_State67Message)

/* func_ov003_0220fd04: entering state 0x67: the request's point and the yaw towards it are
 * kept, animation 0x65 starts, the point goes to func_ov003_02220db4, flag 0x1c is cleared,
 * sound 0x7da plays and flag 9 is set. */
void FieldActor_EnterState67(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    Vec3 point = *(const Vec3 *) (const void *) request->payload;
    s16 yaw = Math_Atan2(sub32(point.x, actor->position.x), sub32(point.z, actor->position.z));
    Vec3 copy = point;

    State67Work_Set(&actor->work.s67, yaw, &copy);
    func_020109a0(actor, 0x65, 3, 0);
    copy = point;
    func_ov003_02220db4(actor->player, &copy);
    func_0200f268(actor, 0x1c);
    func_0200f328(actor, 0x7da);
    func_0200f27c(actor, 9);
}
CLEAN_AS(func_ov003_0220fd04, FieldActor_EnterState67)

/* func_ov003_0220fd90 */
void State67Work_Set(State67Work *work, s16 yaw, const Vec3 *point)
{
    work->yaw = yaw;
    copy_point(&work->point, point);
}
CLEAN_AS(func_ov003_0220fd90, State67Work_Set)

/* func_ov003_0220fda0: asks for state 0x67 at the middle of the tile `at` is on (at its
 * height); whether it was queued. */
int FieldActor_RequestState67(FieldActor *actor, const Vec3 *at, int priority, int arg)
{
    StateRequest request;
    Vec3 middle;

    begin_request(&request, 0x67, priority, arg);
    func_0204f7e0(&middle, at);
    Vec3 copy = middle;
    State67_CopyPoint((Vec3 *) (void *) request.payload, &copy);
    return finish_request(actor, &request);
}
CLEAN_AS(func_ov003_0220fda0, FieldActor_RequestState67)

/* func_ov003_0220fdf4 */
void State67_CopyPoint(Vec3 *dst, const Vec3 *src)
{
    copy_point(dst, src);
}
CLEAN_AS(func_ov003_0220fdf4, State67_CopyPoint)

/* ---- State 0x66: animation 0x64 walking to a tile's middle; state 0x67 may follow */

/* func_ov003_0220fe04: state 0x66's update: the actor walks to the point and turns once
 * there. */
void FieldActor_UpdateState66(FieldActor *actor)
{
    func_02010f5c(actor);
    Vec3 point = actor->work.s66.point;
    if (func_0200f434(actor, &point)) {
        FieldActor_TurnState66(actor);
    }
    func_02010d64(actor);
    FieldActor_EndState66(actor);
}
CLEAN_AS(func_ov003_0220fe04, FieldActor_UpdateState66)

/* func_ov003_0220fe4c: for the actor of this console with nothing decided yet, the word at
 * 0x818 decides (1: state 0x67, 2: func_0200d4e8). The first two frames are only counted;
 * after them another player's actor notes the state after this one, and what was decided is
 * done. */
void FieldActor_EndState66(FieldActor *actor)
{
    State66Work *work = &actor->work.s66;

    if (is_local_player(actor) && work->next == 0) {
        if (actor->unk_818 == 1) {
            work->next = 1;
        } else if (actor->unk_818 == 2) {
            work->next = 2;
        }
    }
    if (work->count < 2) {
        work->count++;
        return;
    }
    if (!is_local_player(actor)) {
        actor->next_state = func_02008258(actor, actor->state);
    }
    if (work->next == 1) {
        Vec3 point = work->point;
        FieldActor_RequestState67(actor, &point, 6, -1);
    } else if (work->next == 2) {
        actor->next_state = func_02008258(actor, actor->state);
        func_0200d4e8(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_ov003_0220fe4c, FieldActor_EndState66)

/* func_ov003_0220ff14: the actor turns towards the work's yaw. */
void FieldActor_TurnState66(FieldActor *actor)
{
    s16 yaw = actor->yaw;
    func_020113e0(&yaw, (s16) actor->work.s66.yaw);
    func_020110a0(actor, &yaw);
}
CLEAN_AS(func_ov003_0220ff14, FieldActor_TurnState66)

/* func_ov003_0220ff40: leaving state 0x66 for `next`: flag 0x1c is cleared. Another player's
 * actor leaving for neither state 2 nor 0x67 with the flag set first sends the point to
 * func_ov003_02220db4 (as entering state 0x67 would); with the flag clear nothing is done. */
void FieldActor_ExitState66(FieldActor *actor, int next)
{
    if (!is_local_player(actor) && next != 2 && next != 0x67) {
        if (func_0200f290(actor, 0x1c)) {
            Vec3 point = actor->work.s66.point;
            func_ov003_02220db4(actor->player, &point);
            func_0200f268(actor, 0x1c);
        }
        return;
    }
    func_0200f268(actor, 0x1c);
}
CLEAN_AS(func_ov003_0220ff40, FieldActor_ExitState66)

/* func_ov003_0220ffc0: state 0x66's message handler: in state 0x66 `arg` is kept at 0xc84;
 * otherwise state 0x66 is asked for again for the saved tile (next 0), priority 6. */
void FieldActor_State66Message(FieldActor *actor, int arg)
{
    if (actor->state == 0x66) {
        actor->unk_C84 = (s16) arg;
        return;
    }
    int tile[2] = {0, 0};
    TileArgs_GetInts(&actor->saved.tile, tile);
    int copy[2] = {tile[0], tile[1]};
    FieldActor_RequestState66(actor, copy, 0, 6, (s16) arg);
}
CLEAN_AS(func_ov003_0220ffc0, FieldActor_State66Message)

/* func_ov003_02210010: entering state 0x66: the middle of the request's tile, the yaw towards
 * it and `next` are kept, the tile saved, animation 0x64 starts, and with `next` 1 flag 0x1c is
 * set. */
void FieldActor_EnterState66(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const TileNextArgs *args = (const TileNextArgs *) (const void *) request->payload;
    int x = args->x;
    int z = args->z;
    int next = args->next;
    Vec3 point;

    func_0204f794(&point, (u32) x, (u32) z);
    s16 yaw = Math_Atan2(sub32(point.x, actor->position.x), sub32(point.z, actor->position.z));
    Vec3 copy = point;
    State66Work_Set(&actor->work.s66, (u8) next, (u16) yaw, &copy);
    int tile[2] = {x, z};
    TileArgs_SetInts(&actor->saved.tile, tile);
    func_020109fc(actor, 0x64, 3, 0);
    if (actor->work.s66.next == 1) {
        func_0200f27c(actor, 0x1c);
    }
}
CLEAN_AS(func_ov003_02210010, FieldActor_EnterState66)

/* func_ov003_02210094 */
void TileArgs_GetInts(const TileArgs *args, int *tile)
{
    tile[0] = args->x;
    tile[1] = args->z;
}
CLEAN_AS(func_ov003_02210094, TileArgs_GetInts)

/* func_ov003_022100a0 */
void TileArgs_SetInts(TileArgs *args, const int *tile)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_022100a0, TileArgs_SetInts)

/* func_ov003_022100ac */
void State66Work_Set(State66Work *work, u8 next, u16 yaw, const Vec3 *point)
{
    work->next = next;
    work->count = 0;
    work->yaw = yaw;
    copy_point(&work->point, point);
}
CLEAN_AS(func_ov003_022100ac, State66Work_Set)

/* ---- States 0x66 (request) and 0x65 to 0x5e */

static_assert(offsetof(FieldActor, unk_0C4) == 0xc4, "0xc4");
static_assert(offsetof(FieldActor, unk_0D0) == 0xd0, "0xd0");
static_assert(offsetof(FieldActor, unk_298) == 0x298, "0x298");
static_assert(offsetof(FieldActor, unk_698) == 0x698, "0x698");
static_assert(offsetof(FieldActor, unk_81C) == 0x81c, "0x81c");
static_assert(offsetof(FieldActor, item) == 0x820, "item");
static_assert(offsetof(FieldActor, unk_824) == 0x824, "0x824");
static_assert(offsetof(FieldActor, work.s62.point) == 0x7d8, "state 0x62 point");
static_assert(offsetof(FieldActor, work.s62.yaw) == 0x7e4, "state 0x62 yaw");
static_assert(offsetof(FieldActor, work.s62.kind) == 0x7e6, "state 0x62 kind");
static_assert(offsetof(FieldActor, work.s61.yaw) == 0x7d6, "state 0x61 yaw");
static_assert(offsetof(FieldActor, work.s61.done) == 0x7db, "state 0x61 done");
static_assert(offsetof(FieldActor, work.s5f.step) == 0x7e0, "state 0x5f step");
static_assert(offsetof(FieldActor, work.s5f.kind) == 0x7e1, "state 0x5f kind");
static_assert(offsetof(FieldActor, work.s5e.point) == 0x7d8, "state 0x5e point");
static_assert(offsetof(PointItemArgs, item) == 0xc, "point item args");
static_assert(offsetof(PointItemArgs, kind) == 0xe, "point item args kind");
static_assert(sizeof(PointItemArgs) <= sizeof(((StateRequest *) 0)->payload), "payload");

/* The effect handle state 0x63 keeps (func_020912d4), -1 for none. */
#define STATE63_EFFECT(actor) ((actor)->work.effect.effect)

extern void *func_02010ca4(FieldActor *actor);
extern int func_0203e168(void);
extern void func_020ba35c(int player);
/* The object at 0x5c8 (the end of `held`). */
extern void func_0206026c(void *object, int a);
extern void func_02060428(void *object, Vec3 *at);
/* Some state of a player's actor, as the session knows it; whether it is known. */
extern int func_02096518(u32 *out, int a, int player);
extern int func_02008380(FieldActor *actor, int a, int priority, int arg);
extern int func_ov003_022211bc(int player, Vec3 *at);
extern void func_ov003_02221150(int player, Vec3 *at);
/* Turns the actor towards a yaw. */
extern void func_0200fb34(FieldActor *actor, s16 yaw);
/* An item code packed into two bytes, and read back. */
extern void func_020778b0(u8 *packed, int item);
extern u16 func_02077898(const u8 *packed);
extern int func_02043d18(int player, int a, int b, u16 item);
extern int func_0209a110(u16 *item);
extern int func_0206f6b0(u16 item);
extern void func_0200f650(FieldActor *actor, fx32 value);
extern int func_0203e1c4(void);
extern void *func_02062f90(void *text, u16 *item);
extern void func_020683b4(FieldActorLink *link, int a, void *text, int b);
extern void *func_02062f4c(void *text);
extern int func_02099fe8(void);
extern int func_02030db8(int x, int z);
extern int func_ov003_02221294(int player, Vec3 *at, u8 kind);
extern void func_0200ee40(FieldActor *actor);
extern int func_ov003_02220f40(int player, Vec3 *at, s16 yaw);
extern void func_02079750(Vec3 *position);

/* Starts a request for `state` (func_0200e92c, func_0200e90c); the caller fills the payload and
 * sends it with send_request.
 * BUG: as in request_state, the bytes of the request nothing sets are the stack's. */
static void open_request(StateRequest *request, int state, int priority, int arg)
{
#ifdef BUGFIX
    memset(request, 0, sizeof(*request));
#endif
    func_0200e92c(request);
    func_0200e90c(request, state, priority, arg);
}

/* Queues the request (func_0200e894) and ends it (func_0200e91c); whether it was queued. */
static int send_request(FieldActor *actor, StateRequest *request)
{
    int queued = func_0200e894(actor, request);
    func_0200e91c(request);
    return queued;
}

/* Whether an item code is nothing: for a code func_0204bcdc accepts, by comparing func_0204bc64
 * of it and of ITEM_NONE (held in a temporary); otherwise by the code itself. */
static BOOL item_is_nothing(u16 *item)
{
    if (func_0204bcdc(item)) {
        u16 none = ITEM_NONE;
        int code = func_0204bc64(item);
        return code == func_0204bc64(&none);
    }
    return *item == ITEM_NONE;
}

/* Releases the receiver at 0xec when flag 0x11 says it is registered. */
static void release_receiver(FieldActor *actor)
{
    if (func_0200f290(actor, 0x11)) {
        func_0200f268(actor, 0x11);
        func_0203ee08(actor, actor->receiver);
    }
}

/* Ends a state the usual way: the state after it is noted and func_0200d4e8 (3) moves on. */
static void move_on(FieldActor *actor)
{
    actor->next_state = func_02008258(actor, actor->state);
    func_0200d4e8(actor, 3, 1, -1);
}

/* Ends state 0x63's effect, if any. */
static void end_state63_effect(FieldActor *actor)
{
    if (STATE63_EFFECT(actor) != -1) {
        func_0209129c(STATE63_EFFECT(actor));
        STATE63_EFFECT(actor) = -1;
    }
}

/* func_ov003_022100c4: asks for state 0x66 for a tile and what follows it (State66Work.next);
 * whether it was queued. */
int FieldActor_RequestState66(FieldActor *actor, const int *tile, int next, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x66, priority, arg);
    int copy[2] = {tile[0], tile[1]};
    TileNextArgs_Set((TileNextArgs *) (void *) request.payload, copy, (u8) next);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022100c4, FieldActor_RequestState66)

/* func_ov003_02210114 */
void TileNextArgs_Set(TileNextArgs *args, const int *tile, u8 next)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    args->next = next;
}
CLEAN_AS(func_ov003_02210114, TileNextArgs_Set)

/* ---- State 0x65: animation 0 */

/* func_ov003_02210120: state 0x65's update. */
void FieldActor_UpdateState65(FieldActor *actor)
{
    func_02010f5c(actor);
    func_02010d64(actor);
    func_02010ca4(actor);
}
CLEAN_AS(func_ov003_02210120, FieldActor_UpdateState65)

/* func_ov003_0221013c: state 0x65's message handler: messages are ignored. */
void FieldActor_State65Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_0221013c, FieldActor_State65Message)

/* func_ov003_02210140: entering state 0x65: animation 0 starts. */
void FieldActor_EnterState65(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    func_020109fc(actor, 0, 3, 0);
}
CLEAN_AS(func_ov003_02210140, FieldActor_EnterState65)

/* func_ov003_02210154: asks for state 0x65; whether it was queued. */
int FieldActor_RequestState65(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x65, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_02210154, FieldActor_RequestState65)

/* ---- State 0x64: animation 0x5f with the held object in pose 0x22, then 0x60 */

/* func_ov003_0221018c: state 0x64's update. */
void FieldActor_UpdateState64(FieldActor *actor)
{
    FieldActor_RunState64(actor);
    func_02010d64(actor);
    FieldActor_EndState64(actor);
}
CLEAN_AS(func_ov003_0221018c, FieldActor_UpdateState64)

/* func_ov003_022101a8: once the animation is over animation 0x60 starts; another player's
 * actor notes the state after this one. */
void FieldActor_EndState64(FieldActor *actor)
{
    if (!func_02056f94(&actor->anim)) {
        return;
    }
    func_020109fc(actor, 0x60, 3, 3);
    if (is_local_player(actor)) {
        return;
    }
    actor->next_state = func_02008258(actor, actor->state);
}
CLEAN_AS(func_ov003_022101a8, FieldActor_EndState64)

/* func_ov003_022101fc: the actor turns to yaw 0 (func_0200faa8, 0x400). During animation
 * 0x5f, at a point 0xb00 above and 0x300 beyond (z) where the frame's update began, the frames
 * before 11 run func_0200f2a0 (0x851); on frame 11 the object at 0x5c8 is set up there (9),
 * sounds 0x852 and 0x853 play and flag 9 is set. */
void FieldActor_RunState64(FieldActor *actor)
{
    func_0200faa8(actor, 0x400);
    func_02010f5c(actor);
    if (actor->animation != 0x5f) {
        return;
    }
    Vec3 point = actor->start_position;
    point.y = add32(point.y, 0xb00);
    point.z = add32(point.z, 0x300);
    if (anim_frame(actor) < 11) {
        func_0200f2a0(actor, 0x851, &point);
        return;
    }
    if (func_02056f28(&actor->anim, 11)) {
        void *object = &actor->held[0x28];
        func_0206026c(object, 9);
        func_02060428(object, &point);
        func_0200f328(actor, 0x852);
        func_0200f328(actor, 0x853);
        func_0200f27c(actor, 9);
    }
}
CLEAN_AS(func_ov003_022101fc, FieldActor_RunState64)

/* func_ov003_022102d0: state 0x64's message handler: state 0x64 is asked for again, priority
 * 6. */
void FieldActor_State64Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState64(actor, 6, arg);
}
CLEAN_AS(func_ov003_022102d0, FieldActor_State64Message)

/* func_ov003_022102dc: entering state 0x64: the actor of this console moves on at once when
 * func_0203e168 says no; otherwise func_020ba35c runs for the player, animation 0x5f starts
 * and the held object takes pose 0x22. */
void FieldActor_EnterState64(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    if (is_local_player(actor) && func_0203e168() == 0) {
        move_on(actor);
        return;
    }
    func_020ba35c(actor->player);
    func_020109a0(actor, 0x5f, 3, 0);
    func_0205eae0(actor->held, 0x22, 3, 1);
}
CLEAN_AS(func_ov003_022102dc, FieldActor_EnterState64)

/* func_ov003_02210354: asks for state 0x64; whether it was queued. */
void *FieldActor_RequestState64(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x64, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_02210354, FieldActor_RequestState64)

/* ---- State 0x63: animation 0x61 with effect 0x26 */

/* func_ov003_0221038c: state 0x63's update. */
void FieldActor_UpdateState63(FieldActor *actor)
{
    FieldActor_RunState63(actor);
    func_02010d64(actor);
    func_02010ca4(actor);
    if (is_local_player(actor)) {
        FieldActor_EndState63Local(actor);
    } else {
        FieldActor_EndState63Remote(actor);
    }
}
CLEAN_AS(func_ov003_0221038c, FieldActor_UpdateState63)

/* func_ov003_022103cc: for another player's actor: the state after this one is noted. When the
 * saved flag says the actor at that player's console left the state early and the session
 * reports state 0x63 for the player (func_02096518), state 0x63 is asked for again (the flag
 * kept set) and the effect ends; otherwise the actor moves on once the animation is over. */
void FieldActor_EndState63Remote(FieldActor *actor)
{
    u8 left_early;
    u32 state;

    actor->next_state = func_02008258(actor, actor->state);
    SavedFlag_Get(&actor->saved.left_early, &left_early);
    if (left_early && func_02096518(&state, -1, actor->player) && state == 0x63) {
        FieldActor_RequestState63(actor, 6, -1);
        SavedFlag_Set(&actor->saved.left_early, 1);
        end_state63_effect(actor);
    } else if (func_02056f94(&actor->anim)) {
        func_0200d4e8(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_ov003_022103cc, FieldActor_EndState63Remote)

/* func_ov003_02210474: for the actor of this console: it moves on once the animation is over.
 * The saved flag is cleared, and from frame 0x21 on, when FieldActor_ResumeMoving leaves the
 * state, it is set and the effect ends. */
void FieldActor_EndState63Local(FieldActor *actor)
{
    if (func_02056f94(&actor->anim)) {
        move_on(actor);
    }
    SavedFlag_Set(&actor->saved.left_early, 0);
    if (anim_frame(actor) >= 0x21 && FieldActor_ResumeMoving(actor)) {
        SavedFlag_Set(&actor->saved.left_early, 1);
        end_state63_effect(actor);
    }
}
CLEAN_AS(func_ov003_02210474, FieldActor_EndState63Local)

/* func_ov003_02210504: from frame 5 to 0x23 the effect follows the point at 0x62c (through
 * func_0203f7d0): the first of those frames starts it (0x26, with sound 0x854) and leaves the
 * point ahead of the actor and flag 1 for other code (02260558, 02260540). On frame 0x14
 * func_0200ff28 acts on the point ahead (mode 1, tool 5); on frame 0x23 the effect ends. */
void FieldActor_RunState63(FieldActor *actor)
{
    func_02010f5c(actor);
    int frame = anim_frame(actor);
    if (frame < 5 || frame > 0x23) {
        return;
    }
    Vec3 at = actor->unk_62C;
    func_0203f7d0(&at, &at);
    if (STATE63_EFFECT(actor) == -1) {
        STATE63_EFFECT(actor) = func_020912d4(0x26, &at, &actor->yaw, 0);
        func_0200f328(actor, 0x854);
        Vec3 ahead;
        func_0200fa6c(&ahead, actor);
        data_ov003_02260540 = 1;
        data_ov003_02260558 = ahead;
    } else {
        func_02091278(STATE63_EFFECT(actor), &at, NULL, 0);
    }
    if (frame == 0x14) {
        Vec3 ahead;
        func_0200fa6c(&ahead, actor);
        func_0200ff28(actor, &ahead, 1, 5);
    } else if (frame == 0x23) {
        end_state63_effect(actor);
    }
}
CLEAN_AS(func_ov003_02210504, FieldActor_RunState63)

/* func_ov003_022105ec: leaving state 0x63: the effect ends, and flag 0 and the point ahead of
 * the actor are left for other code (02260540, 02260558).
 * QUIRK: the effect's handle is not reset to -1. */
void FieldActor_ExitState63(FieldActor *actor)
{
    if (STATE63_EFFECT(actor) != -1) {
        func_0209129c(STATE63_EFFECT(actor));
    }
    Vec3 ahead;
    func_0200fa6c(&ahead, actor);
    data_ov003_02260540 = 0;
    data_ov003_02260558 = ahead;
}
CLEAN_AS(func_ov003_022105ec, FieldActor_ExitState63)

/* func_ov003_02210634: state 0x63's message handler: state 0x63 is asked for again, priority
 * 6. */
void FieldActor_State63Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState63(actor, 6, arg);
}
CLEAN_AS(func_ov003_02210634, FieldActor_State63Message)

/* func_ov003_02210640: entering state 0x63: animation 0x61, no effect yet. */
void FieldActor_EnterState63(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    func_020109a0(actor, 0x61, 3, 0);
    STATE63_EFFECT(actor) = -1;
}
CLEAN_AS(func_ov003_02210640, FieldActor_EnterState63)

/* func_ov003_02210660 */
void SavedFlag_Get(const u8 *saved, u8 *value)
{
    *value = *saved;
}
CLEAN_AS(func_ov003_02210660, SavedFlag_Get)

/* func_ov003_02210668 */
void SavedFlag_Set(u8 *saved, int value)
{
    *saved = (u8) value;
}
CLEAN_AS(func_ov003_02210668, SavedFlag_Set)

/* func_ov003_0221066c: asks for state 0x63; whether it was queued. */
int FieldActor_RequestState63(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x63, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0221066c, FieldActor_RequestState63)

/* ---- State 0x62: animation 0x49 then 0x51, acting with an item on a tile */

/* func_ov003_022106a4: state 0x62's update: the actor turns towards the tile and moves to it. */
void FieldActor_UpdateState62(FieldActor *actor)
{
    FieldActor_TurnState62(actor);
    FieldActor_AnimateState62(actor);
    Vec3 point = actor->work.s62.point;
    func_0200f434(actor, &point);
    func_02010d64(actor);
    FieldActor_EndState62(actor);
}
CLEAN_AS(func_ov003_022106a4, FieldActor_UpdateState62)

/* func_ov003_022106e4: when the animation is over: after animation 0x49 comes 0x51; after
 * that the state after this one is noted and the kind decides: 1 func_0200c9a8 (3, priority 5);
 * 3 for the actor of this console, the receiver released (flag 0x11) and func_02008380; any
 * other func_0200d4e8. */
void FieldActor_EndState62(FieldActor *actor)
{
    if (!func_02056f94(&actor->anim)) {
        return;
    }
    if (actor->animation == 0x49) {
        func_020109a0(actor, 0x51, 3, 0);
        return;
    }
    actor->next_state = func_02008258(actor, actor->state);
    u8 kind = actor->work.s62.kind;
    if (kind == 1) {
        func_0200c9a8(actor, 3, 5, -1);
        return;
    }
    if (is_local_player(actor) && kind == 3) {
        release_receiver(actor);
        func_02008380(actor, 3, 1, -1);
    } else {
        func_0200d4e8(actor, 3, 1, -1);
    }
}
CLEAN_AS(func_ov003_022106e4, FieldActor_EndState62)

/* func_ov003_022107ac: except during animation 0x49, by frame: 1 effect 9 at the point (at the
 * actor's yaw); 5 the point goes to func_ov003_022211bc for the actor of this console, or, for
 * another's, to func_ov003_02221150 when the map object there is 0xfc or 0xfd, and flag 0x1c is
 * cleared; 7 sound 0x843 and flag 9; 0x15 effect 0xa at the point.
 * REQUIRES: func_0204f5a8 finds a map object at the point (the ROM reads it unchecked). */
void FieldActor_AnimateState62(FieldActor *actor)
{
    if (actor->animation != 0x49) {
        Vec3 point = actor->work.s62.point;
        s16 yaw = actor->yaw;
        switch (anim_frame(actor)) {
            case 1:
                func_020912d4(9, &point, &yaw, 0);
                break;
            case 5:
                if (is_local_player(actor)) {
                    Vec3 copy = point;
                    func_ov003_022211bc(actor->player, &copy);
                } else {
                    u16 *object = func_0204f5a8(data_021c80bc, &point, 0);
                    if (in_range(*object, 0xfc, 0xfd)) {
                        Vec3 copy = point;
                        func_ov003_02221150(actor->player, &copy);
                    }
                }
                func_0200f268(actor, 0x1c);
                break;
            case 7:
                func_0200f328(actor, 0x843);
                func_0200f27c(actor, 9);
                break;
            case 0x15:
                func_020912d4(0xa, &point, NULL, 0);
                break;
            default:
                break;
        }
    }
    func_02010f5c(actor);
}
CLEAN_AS(func_ov003_022107ac, FieldActor_AnimateState62)

/* func_ov003_022108b0 */
void FieldActor_TurnState62(FieldActor *actor)
{
    func_0200fb34(actor, actor->work.s62.yaw);
}
CLEAN_AS(func_ov003_022108b0, FieldActor_TurnState62)

/* func_ov003_022108c0: leaving state 0x62: another player's actor with flag 0x1c still set
 * sends the point on as frame 5 would have, and the flag is cleared.
 * QUIRK: whose actor it is gets asked a second time, and the answer, always "another's" here,
 * picks func_ov003_02221150 (without the map object check). */
void FieldActor_ExitState62(FieldActor *actor)
{
    if (is_local_player(actor)) {
        return;
    }
    if (!func_0200f290(actor, 0x1c)) {
        return;
    }
    Vec3 point = actor->work.s62.point;
    if (is_local_player(actor)) {
        func_ov003_022211bc(actor->player, &point);
    } else {
        func_ov003_02221150(actor->player, &point);
    }
    func_0200f268(actor, 0x1c);
}
CLEAN_AS(func_ov003_022108c0, FieldActor_ExitState62)

/* func_ov003_0221094c: state 0x62's message handler: messages are ignored. */
void FieldActor_State62Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_0221094c, FieldActor_State62Message)

/* func_ov003_02210950: entering state 0x62: the request's item and kind, the middle of its
 * tile and the yaw towards it are kept. Animation 0x49 starts, unless it is playing already
 * (then 0x51 follows once it is over) or animation 0x4a is (0x51 at once). Flag 0xd is cleared
 * and 0x1c set. */
void FieldActor_EnterState62(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const ItemTileArgs *args = (const ItemTileArgs *) (const void *) request->payload;
    State62Work *work = &actor->work.s62;
    u8 kind = args->kind;
    Vec3 point;

    func_0204f794(&point, args->x, args->z);
    work->item = args->item;
    work->kind = kind;
    work->point = point;
    work->yaw = Math_Atan2(sub32(point.x, actor->position.x), sub32(point.z, actor->position.z));
    if (actor->animation == 0x49) {
        if (func_02056f94(&actor->anim)) {
            func_020109a0(actor, 0x51, 3, 0);
        }
    } else if (actor->animation == 0x4a) {
        func_020109a0(actor, 0x51, 3, 0);
    } else {
        func_020109a0(actor, 0x49, 3, 0);
    }
    func_0200f268(actor, 0xd);
    func_0200f27c(actor, 0x1c);
}
CLEAN_AS(func_ov003_02210950, FieldActor_EnterState62)

/* func_ov003_022109f8: asks for state 0x62 with a kind, a tile and an item; whether it was
 * queued. */
void *FieldActor_RequestState62(FieldActor *actor, u32 kind, const u32 *tile, u16 item, u32 priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x62, (int) priority, arg);
    ItemTileArgs *args = (ItemTileArgs *) (void *) request.payload;
    args->kind = (u8) kind;
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    args->item = item;
    return (void *) (intptr_t) send_request(actor, &request);
}
CLEAN_AS(func_ov003_022109f8, FieldActor_RequestState62)

/* ---- State 0x61: animation 0x49 then 0x4a, turning towards a tile before state 0x62 */

/* func_ov003_02210a44: state 0x61's update. */
void FieldActor_UpdateState61(FieldActor *actor)
{
    FieldActor_TurnState61(actor);
    func_02010f5c(actor);
    func_02010d64(actor);
    FieldActor_EndState61(actor);
}
CLEAN_AS(func_ov003_02210a44, FieldActor_UpdateState61)

/* func_ov003_02210a64: another player's actor only notes the state after this one. The actor of
 * this console marks `done` when the word at 0x818 is 1; when the animation is over animation
 * 0x4a starts, and during it (or at that end) the actor goes on to state 0x62 with the same
 * kind, tile and item, unless the kind is 2 and nothing is done yet. */
void FieldActor_EndState61(FieldActor *actor)
{
    State61Work *work = &actor->work.s61;

    if (!is_local_player(actor)) {
        actor->next_state = func_02008258(actor, actor->state);
        return;
    }
    if (actor->unk_818 == 1) {
        work->done = 1;
    }
    if (func_02056f94(&actor->anim) || actor->animation == 0x4a) {
        if (func_02056f94(&actor->anim)) {
            func_020109fc(actor, 0x4a, 3, 0);
        }
        if (work->kind != 2 || work->done != 0) {
            actor->next_state = func_02008258(actor, actor->state);
            u32 tile[2] = {work->x, work->z};
            FieldActor_RequestState62(actor, work->kind, tile, work->item, 6, -1);
        }
    }
}
CLEAN_AS(func_ov003_02210a64, FieldActor_EndState61)

/* func_ov003_02210b28 */
void FieldActor_TurnState61(FieldActor *actor)
{
    func_0200fb34(actor, actor->work.s61.yaw);
}
CLEAN_AS(func_ov003_02210b28, FieldActor_TurnState61)

/* func_ov003_02210b38: state 0x61's message handler: messages are ignored. */
void FieldActor_State61Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_02210b38, FieldActor_State61Message)

/* func_ov003_02210b3c: entering state 0x61: with kind 2 the actor of this console gets a target
 * from func_02043d18 for its item; another kind turns into 3 during animation 0x6c. The item,
 * the yaw towards the tile's middle, the kind and the tile are kept and saved, animation 0x49
 * starts and flag 0xd is cleared. */
void FieldActor_EnterState61(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const ItemTileArgs *args = (const ItemTileArgs *) (const void *) request->payload;
    State61Work *work = &actor->work.s61;
    int kind = args->kind;
    u8 x = args->x;
    u8 z = args->z;
    Vec3 point;

    func_0204f794(&point, x, z);
    u16 item = args->item;
    if (kind == 2) {
        if (is_local_player(actor)) {
            actor->target = func_02043d18(actor->player, 2, 0, actor->item);
        }
    } else if (actor->animation == 0x6c) {
        kind = 3;
    }
    work->item = item;
    work->x = x;
    work->z = z;
    work->kind = (u8) kind;
    work->done = 0;
    work->yaw = Math_Atan2(sub32(point.x, actor->position.x), sub32(point.z, actor->position.z));
    SavedItemTile_Set(&actor->saved.item_tile, item, (char) x, (char) z, (u8) kind);
    func_020109a0(actor, 0x49, 7, 0);
    func_0200f268(actor, 0xd);
}
CLEAN_AS(func_ov003_02210b3c, FieldActor_EnterState61)

/* func_ov003_02210c08 */
void SavedItemTile_Set(SavedItemTile *saved, int item, char x, char z, u8 kind)
{
    func_020778b0(saved->item, item);
    saved->x = (u8) x;
    saved->z = (u8) z;
    saved->kind = kind;
}
CLEAN_AS(func_ov003_02210c08, SavedItemTile_Set)

/* func_ov003_02210c24: asks for state 0x61 with a kind, a tile and an item; whether it was
 * queued. */
void *FieldActor_RequestState61(FieldActor *actor, u32 kind, const u32 *tile, u16 item, u32 priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x61, (int) priority, arg);
    ItemTileArgs *args = (ItemTileArgs *) (void *) request.payload;
    args->item = item;
    args->kind = (u8) kind;
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    return (void *) (intptr_t) send_request(actor, &request);
}
CLEAN_AS(func_ov003_02210c24, FieldActor_RequestState61)

/* ---- State 0x60: animation 0x50 shrinking the actor, then 0x6c */

/* func_ov003_02210c70: state 0x60's update. */
void FieldActor_UpdateState60(FieldActor *actor)
{
    FieldActor_ScaleState60(actor);
    func_02010d64(actor);
    FieldActor_RunState60(actor);
}
CLEAN_AS(func_ov003_02210c70, FieldActor_UpdateState60)

/* func_ov003_02210c8c: by `step`:
 *   0: once the animation is over the actor moves on, and the actor of this console runs
 *      func_0209a110 on its item;
 *   1: after animation 0x50 animation 0x6c starts. Another player's actor notes the state after
 *      this one and flag 0xd is cleared. The actor of this console follows the word at 0x81c:
 *      at 5 it becomes 6 once func_0206f6b0 accepts the item; at 6, once group 9 can open, it
 *      becomes 0xf and, when GroupParams_C4CIs1, the actor moves on (flag 0xd cleared, the
 *      receiver released, func_0203e19c). Otherwise from 0xf on the receiver is released,
 *      func_0203e19c runs and `step` goes on;
 *   2: once no target is held, state 0x61 (kind 2) is asked for with the tile and the item, and
 *      flag 0xd is cleared. */
void FieldActor_RunState60(FieldActor *actor)
{
    TileStepArgs *work = &actor->work.s60;

    switch (work->step) {
        case 0:
            if (!func_02056f94(&actor->anim)) {
                break;
            }
            move_on(actor);
            if (is_local_player(actor)) {
                func_0209a110(&actor->item);
            }
            break;
        case 1:
            if (actor->animation == 0x50) {
                if (!func_02056f94(&actor->anim)) {
                    break;
                }
                func_020109fc(actor, 0x6c, 3, 3);
            }
            if (!is_local_player(actor)) {
                actor->next_state = func_02008258(actor, actor->state);
                func_0200f268(actor, 0xd);
                break;
            }
            if (actor->unk_81C == 5) {
                if (func_0206f6b0(actor->item)) {
                    actor->unk_81C = 6;
                }
                break;
            }
            if (actor->unk_81C == 6) {
                if (!GroupParams_CanOpen()) {
                    break;
                }
                actor->unk_81C = 0xf;
                if (GroupParams_C4CIs1()) {
                    func_0200f268(actor, 0xd);
                    release_receiver(actor);
                    func_0203e19c();
                    move_on(actor);
                    break;
                }
            } else if (actor->unk_81C < 0xf) {
                break;
            }
            release_receiver(actor);
            func_0203e19c();
            work->step++;
            break;
        case 2: {
            if (actor->target != -1) {
                break;
            }
            u32 tile[2] = {work->x, work->z};
            FieldActor_RequestState61(actor, 2, tile, actor->item, 6, -1);
            func_0200f268(actor, 0xd);
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02210c8c, FieldActor_RunState60)

/* func_ov003_02210e4c: during animation 0x50 the actor shrinks from 1.0 by a sixth per frame
 * (func_0200f650 and the three words at 0x830); at 0 flag 0xd is cleared. Other animations
 * leave it at 0. */
void FieldActor_ScaleState60(FieldActor *actor)
{
    fx32 scale = 0;

    func_02010f5c(actor);
    if (actor->animation == 0x50) {
        scale = 0x1000 - (anim_frame(actor) << 12) / 6;
        if (scale < 0) {
            scale = 0;
            func_0200f268(actor, 13);
        }
    }
    actor->unk_830[0] = scale;
    actor->unk_830[1] = scale;
    actor->unk_830[2] = scale;
    func_0200f650(actor, scale);
}
CLEAN_AS(func_ov003_02210e4c, FieldActor_ScaleState60)

/* func_ov003_02210eb8: state 0x60's message handler: state 0x60 is asked for again with the
 * saved tile and step, priority 6. */
void FieldActor_State60Message(FieldActor *actor, int arg)
{
    u8 x;
    u8 z;
    u8 step;

    TileStepArgs_Get(&actor->saved.tile_step, &x, &z, &step);
    int tile[2] = {x, z};
    FieldActor_RequestState60(actor, tile, step, 6, (s16) arg);
}
CLEAN_AS(func_ov003_02210eb8, FieldActor_State60Message)

/* func_ov003_02210ef8: entering state 0x60: the request's tile and step are kept and saved,
 * animation 0x50 starts and sound 0x4f plays. */
void FieldActor_EnterState60(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const TileStepArgs *args = (const TileStepArgs *) (const void *) request->payload;
    u8 x = args->x;
    u8 z = args->z;
    u8 step = args->step;

    actor->work.s60.step = step;
    actor->work.s60.x = x;
    actor->work.s60.z = z;
    TileStepArgs_Set(&actor->saved.tile_step, x, z, step);
    func_020109a0(actor, 0x50, 3, 0);
    func_0200f328(actor, 0x4f);
}
CLEAN_AS(func_ov003_02210ef8, FieldActor_EnterState60)

/* func_ov003_02210f3c */
void TileStepArgs_Get(const TileStepArgs *args, u8 *x, u8 *z, u8 *step)
{
    *x = args->x;
    *z = args->z;
    *step = args->step;
}
CLEAN_AS(func_ov003_02210f3c, TileStepArgs_Get)

/* func_ov003_02210f50 */
void TileStepArgs_Set(TileStepArgs *args, int x, int z, int step)
{
    args->x = (u8) x;
    args->z = (u8) z;
    args->step = (u8) step;
}
CLEAN_AS(func_ov003_02210f50, TileStepArgs_Set)

/* func_ov003_02210f58: asks for state 0x60 with a tile and the step to start at; whether it was
 * queued. */
int FieldActor_RequestState60(FieldActor *actor, const int *tile, int step, int priority, s16 arg)
{
    const u8 payload[3] = {(u8) tile[0], (u8) tile[1], (u8) step};
    return request_state(actor, 0x60, priority, arg, payload, 3);
}
CLEAN_AS(func_ov003_02210f58, FieldActor_RequestState60)

/* ---- State 0x5f: animation 0x49 or 0x4f acting with an item on a point, then state 0x60 */

/* func_ov003_02210fa0: state 0x5f's update: the actor of this console moves from frame 0x19
 * on (func_0201100c); another player's actor moves to the point. */
void FieldActor_UpdateState5F(FieldActor *actor)
{
    FieldActor_AnimateState5F(actor);
    if (is_local_player(actor)) {
        if (anim_frame(actor) >= 0x19) {
            func_0201100c(actor);
        }
    } else {
        Vec3 point = actor->work.s5f.point;
        func_0200f434(actor, &point);
    }
    func_02010d64(actor);
    FieldActor_RunState5F(actor);
}
CLEAN_AS(func_ov003_02210fa0, FieldActor_UpdateState5F)

/* State 0x60 at the tile of state 0x5f's point, with a step. */
static void request_state60_at_point(FieldActor *actor, int step)
{
    int tile[2] = {0, 0};
    Vec3 point = actor->work.s5f.point;
    func_0204f818(&tile[0], &tile[1], &point);
    FieldActor_RequestState60(actor, tile, step, 6, -1);
}

/* func_ov003_0221100c: animation 0x49 is followed by 0x4f. Otherwise the actor of this console
 * runs func_0203ae98 on frame 0x13; from frame 0x19, once the actor faces yaw 0 (func_0200faf0,
 * 0x400) and the animation is over, another player's actor clears flag 0x12 and notes the state
 * after this one, and the actor of this console goes by `step`:
 *   0: once func_0203e1c4 allows, the receiver at 0xec is registered as "obj_etc_player" (flag
 *      0x11) with byte 0x1e: 0x21 for item 0x136a the first time (record flag 0x27), 0x23 for
 *      item 0x137b the first time (record flag 0x28), else 1 with the item's text handed to
 *      the link (func_02062f90, func_020683b4 kind 7); the link's request is raised, sounds are
 *      set up and the word at 0x81c becomes 10; then 1;
 *   1: once the link reports itself open, 2;
 *   2: when func_02099fe8 gives -1, 3 with the word at 0x81c at 2; else once the link is
 *      closed the receiver is released and state 0x60 is asked for at the point's tile with
 *      step 0;
 *   3: when the word at 0x81c is 0xf or more, 4; else once the link is closed the receiver is
 *      released and state 0x60 is asked for with step 1;
 *   4: once the link is closed and group 9 can open, the receiver is released; then 5;
 *   5: once no target is held, state 0x61 (kind 2) is asked for at the point's tile with the
 *      item.
 * REQUIRES: the link is set when `step` is 0 (the ROM writes through it unchecked there). */
void FieldActor_RunState5F(FieldActor *actor)
{
    State5FWork *work = &actor->work.s5f;

    if (actor->animation == 0x49) {
        if (func_02056f94(&actor->anim)) {
            func_020109a0(actor, 0x4f, 3, 0);
        }
        return;
    }
    int frame = anim_frame(actor);
    if (is_local_player(actor) && func_02056f28(&actor->anim, 0x13)) {
        func_0203ae98();
    }
    if (frame < 0x19) {
        return;
    }
    if (!func_0200faf0(actor, 0x400)) {
        return;
    }
    if (!func_02056f94(&actor->anim)) {
        return;
    }
    if (!is_local_player(actor)) {
        func_0200f268(actor, 0x12);
        actor->next_state = func_02008258(actor, actor->state);
        return;
    }

    switch (work->step) {
        case 0: {
            if (func_0203e1c4() == 0) {
                return;
            }
            work->step = 1;
            func_0203ee14(actor, actor->receiver);
            func_0200f27c(actor, 0x11);
            void *record = func_020984e8();
            func_020a8164(actor->receiver, data_ov003_02238134);
            if (actor->item == 0x136a && !func_02099020(record, 0x27)) {
                actor->receiver_unk_1E = 0x21;
                func_02098ff8(record, 0x27);
            } else if (actor->item == 0x137b && !func_02099020(record, 0x28)) {
                actor->receiver_unk_1E = 0x23;
                func_02098ff8(record, 0x28);
            } else {
                u8 text[0x28];
                actor->receiver_unk_1E = 1;
                func_02062f90(text, &actor->item);
                func_020683b4(actor->link, 0, text, 7);
                func_02062f4c(text);
            }
            actor->link->requested = 1;
            func_02035624(0x12);
            func_02035684(0xc, 0, 1);
            func_020356c4(0xd, 0x39, 0x7f, 1);
            actor->unk_81C = 10;
            break;
        }
        case 1:
            if (actor->link != NULL && actor->link->open != 0) {
                work->step = 2;
            }
            break;
        case 2:
            if (func_02099fe8() == -1) {
                work->step = 3;
                actor->unk_81C = 2;
                break;
            }
            if (actor->link == NULL || actor->link->open != 0) {
                break;
            }
            func_0203ee08(actor, actor->receiver);
            func_0200f268(actor, 0x11);
            func_0203e19c();
            request_state60_at_point(actor, 0);
            func_0203b144();
            break;
        case 3:
            if (actor->unk_81C >= 0xf) {
                work->step = 4;
                break;
            }
            if (actor->link == NULL || actor->link->open != 0) {
                break;
            }
            func_0203ee08(actor, actor->receiver);
            func_0200f268(actor, 0x11);
            request_state60_at_point(actor, 1);
            func_0203b144();
            break;
        case 4:
            if (actor->link == NULL || actor->link->open != 0) {
                break;
            }
            if (!GroupParams_CanOpen()) {
                break;
            }
            func_0203ee08(actor, actor->receiver);
            func_0200f268(actor, 0x11);
            func_0203e19c();
            work->step = 5;
            break;
        case 5: {
            if (actor->target != -1) {
                break;
            }
            int tile[2] = {0, 0};
            Vec3 point = work->point;
            func_0204f818(&tile[0], &tile[1], &point);
            u32 at[2] = {(u32) tile[0], (u32) tile[1]};
            FieldActor_RequestState61(actor, 2, at, actor->item, 6, -1);
            func_0203b144();
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov003_0221100c, FieldActor_RunState5F)

/* func_ov003_0221138c: except during animation 0x49, by frame: 5 effect 6 at the point; 6
 * sound 0x841 and flag 9; 0xc effect 8 at the point, func_02030db8 for its tile, the point and
 * kind to func_ov003_02221294, flag 0xd set and 0x1c cleared. From frame 0x18 on flag 9 is
 * cleared and func_0200ee40 and func_0200f650 (1.0) run with the words at 0xc4 to 0xd0, 0x298
 * and 0x698 kept across them; before it the point at 0x62c goes through func_0203f7d0 into
 * 0x824. */
void FieldActor_AnimateState5F(FieldActor *actor)
{
    func_02010f5c(actor);
    if (actor->animation == 0x49) {
        return;
    }
    Vec3 point = actor->work.s5f.point;
    switch (anim_frame(actor)) {
        case 5:
            func_020912d4(6, &point, NULL, 0);
            break;
        case 6:
            func_0200f328(actor, 0x841);
            func_0200f27c(actor, 9);
            break;
        case 0xc: {
            int x;
            int z;
            func_020912d4(8, &point, NULL, 0);
            func_0204f818(&x, &z, &point);
            func_02030db8(x, z);
            Vec3 copy = point;
            func_ov003_02221294(actor->player, &copy, actor->work.s5f.kind);
            func_0200f27c(actor, 0xd);
            func_0200f268(actor, 0x1c);
            break;
        }
        default:
            break;
    }
    if (anim_frame(actor) >= 0x18) {
        func_0200f268(actor, 9);
        Vec3 kept_0C4 = actor->unk_0C4;
        s16 kept_0D0 = actor->unk_0D0;
        FieldActorBlock48 kept_298 = actor->unk_298;
        FieldActorBlock48 kept_698 = actor->unk_698;
        func_0200ee40(actor);
        func_0200f650(actor, 0x1000);
        actor->unk_0C4 = kept_0C4;
        actor->unk_0D0 = kept_0D0;
        actor->unk_298 = kept_298;
        actor->unk_698 = kept_698;
    } else {
        actor->unk_824 = actor->unk_62C;
        func_0203f7d0(&actor->unk_824, &actor->unk_824);
    }
}
CLEAN_AS(func_ov003_0221138c, FieldActor_AnimateState5F)

/* func_ov003_02211530: leaving state 0x5f for `next`: another player's actor with flag 0x1c
 * still set sends the point and kind on as frame 0xc would have (flags 0x1c and 9 cleared), and
 * leaving for neither state 0x60 nor 0x61 clears flag 0xd. */
void FieldActor_ExitState5F(FieldActor *actor, int next)
{
    if (is_local_player(actor)) {
        return;
    }
    if (func_0200f290(actor, 0x1c)) {
        Vec3 point = actor->work.s5f.point;
        func_ov003_02221294(actor->player, &point, actor->work.s5f.kind);
        func_0200f268(actor, 0x1c);
        func_0200f268(actor, 9);
    }
    if (next != 0x60 && next != 0x61) {
        func_0200f268(actor, 0xd);
    }
}
CLEAN_AS(func_ov003_02211530, FieldActor_ExitState5F)

/* func_ov003_022115a4: state 0x5f's message handler: in state 0 only, state 0x5f is asked for
 * again at the middle of the saved tile with the saved item and kind, priority 6. */
void FieldActor_State5FMessage(FieldActor *actor, int arg)
{
    if (actor->state != 0) {
        return;
    }
    u32 tile[2] = {0, 0};
    u16 item;
    u8 kind;
    SavedItemTile_Get(&actor->saved.item_tile, tile, &item, &kind);
    Vec3 point;
    func_0204f794(&point, tile[0], tile[1]);
    FieldActor_RequestState5F(actor, &point, item, kind, 6, (s16) arg);
}
CLEAN_AS(func_ov003_022115a4, FieldActor_State5FMessage)

/* func_ov003_02211604: entering state 0x5f: the request's point and kind are kept (step 0).
 * Animation 0x4f starts when 0x49 or 0x4a is playing or an item is given, else 0x49. The point
 * at 0x62c goes through func_0203f7d0 into 0x824, the words at 0x830 become 1.0 and flag 0xd is
 * cleared; the point's tile, the actor's item and the kind are saved. With an item given it
 * becomes the actor's item, and on map object 0xfc or 0xfd the animation jumps to its last
 * frame and flag 0xd is set. Without one, when the actor holds nothing or is another player's,
 * the map object's code (ITEM_NONE without one) becomes its item. The actor of this console
 * runs func_02035684 and, with item 0x1549, func_02079750. Then the word at 0x81c is 7 and
 * flag 0x1c is set.
 * REQUIRES: with an item given, func_0204f5e0 finds a map object for the tile (the ROM reads it
 * unchecked there). */
void FieldActor_EnterState5F(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const PointItemArgs *args = (const PointItemArgs *) (const void *) request->payload;
    State5FWork *work = &actor->work.s5f;
    Vec3 point = args->point;
    u16 item = args->item;
    int kind = args->kind;

    work->step = 0;
    work->point = point;
    work->kind = (u8) kind;
    if (actor->animation == 0x49 || actor->animation == 0x4a || !item_is_nothing(&item)) {
        func_020109a0(actor, 0x4f, 3, 0);
    } else {
        func_020109a0(actor, 0x49, 3, 0);
    }
    actor->unk_824 = actor->unk_62C;
    func_0203f7d0(&actor->unk_824, &actor->unk_824);
    actor->unk_830[0] = 0x1000;
    actor->unk_830[1] = 0x1000;
    actor->unk_830[2] = 0x1000;
    func_0200f268(actor, 0xd);

    int tile[2] = {0, 0};
    func_0204f818(&tile[0], &tile[1], &point);
    SavedItemTile_SetTile(&actor->saved.item_tile, tile, actor->item, kind);
    u16 *object = map_object_at(tile[0], tile[1]);
    if (!item_is_nothing(&item)) {
        actor->unk_822 = item;
        actor->item = item;
        if (in_range(*object, 0xfc, 0xfd)) {
            /* QUIRK: the whole frames of the frame count are taken to 16 bits, and none of them
             * wraps to frame 0xffff. */
            u16 frames = (u16) ((u32) actor->anim.end >> 12);
            actor->anim.frame = (fx32) ((u32) (u16) (frames - 1) << 12);
            func_0200f27c(actor, 0xd);
        }
    } else if (item_is_nothing(&actor->item) || !is_local_player(actor)) {
        u16 code = object != NULL ? *object : ITEM_NONE;
        actor->unk_822 = code;
        actor->item = code;
    }
    if (is_local_player(actor)) {
        func_02035684(0x12, 0xf, 0);
        if (actor->item == 0x1549) {
            func_02079750(&actor->position);
        }
    }
    actor->unk_81C = 7;
    func_0200f27c(actor, 0x1c);
}
CLEAN_AS(func_ov003_02211604, FieldActor_EnterState5F)

/* func_ov003_022118b8 */
void SavedItemTile_Get(const SavedItemTile *saved, u32 *tile, u16 *item, u8 *kind)
{
    tile[0] = saved->x;
    tile[1] = saved->z;
    *item = func_02077898(saved->item);
    *kind = saved->kind;
}
CLEAN_AS(func_ov003_022118b8, SavedItemTile_Get)

/* func_ov003_022118d8 */
void SavedItemTile_SetTile(SavedItemTile *saved, const int *tile, int item, int kind)
{
    saved->x = (u8) tile[0];
    saved->z = (u8) tile[1];
    func_020778b0(saved->item, item);
    saved->kind = (u8) kind;
}
CLEAN_AS(func_ov003_022118d8, SavedItemTile_SetTile)

/* func_ov003_022118f8: asks for state 0x5f with a point, an item and a kind; for another
 * player's actor the item at 0x820 and 0x822 is cleared first. Whether it was queued. */
int FieldActor_RequestState5F(FieldActor *actor, const Vec3 *point, int item, int kind, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x5f, priority, arg);
    Vec3 copy = *point;
    PointItemArgs_Set((PointItemArgs *) (void *) request.payload, &copy, (u16) item, (u8) kind);
    if (!is_local_player(actor)) {
        actor->unk_822 = ITEM_NONE;
        actor->item = ITEM_NONE;
    }
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022118f8, FieldActor_RequestState5F)

/* func_ov003_02211980: asks for state 0x5f with a point and a kind and no item; whether it was
 * queued. */
int FieldActor_RequestState5FNoItem(FieldActor *actor, const Vec3 *point, int kind, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x5f, priority, arg);
    Vec3 copy = *point;
    PointItemArgs_Set((PointItemArgs *) (void *) request.payload, &copy, ITEM_NONE, (u8) kind);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02211980, FieldActor_RequestState5FNoItem)

/* func_ov003_022119d8 */
void PointItemArgs_Set(PointItemArgs *args, const Vec3 *point, u16 item, u8 kind)
{
    /* Word by word, x first, as the original copies (it matters only when the two overlap). */
    args->point.x = point->x;
    args->point.y = point->y;
    args->point.z = point->z;
    args->item = item;
    args->kind = kind;
}
CLEAN_AS(func_ov003_022119d8, PointItemArgs_Set)

/* ---- State 0x5e: animation 0x49, then 0x4b or 0x4e, at a point */

/* func_ov003_022119f0: state 0x5e's update: the actor of this console moves (func_0201100c);
 * another player's actor moves to the point. */
void FieldActor_UpdateState5E(FieldActor *actor)
{
    FieldActor_AnimateState5E(actor);
    if (is_local_player(actor)) {
        func_0201100c(actor);
    } else {
        Vec3 point = actor->work.s5e.point;
        func_0200f434(actor, &point);
    }
    func_02010d64(actor);
    FieldActor_EndState5E(actor);
}
CLEAN_AS(func_ov003_022119f0, FieldActor_UpdateState5E)

/* func_ov003_02211a4c: when the animation is over: after animation 0x49 comes 0x4e when the
 * work's flag is set, else 0x4b; after those the actor moves on. */
void FieldActor_EndState5E(FieldActor *actor)
{
    if (!func_02056f94(&actor->anim)) {
        return;
    }
    if (actor->animation == 0x49) {
        if (actor->work.s5e.flag != 0) {
            func_020109a0(actor, 0x4e, 3, 0);
        } else {
            func_020109a0(actor, 0x4b, 3, 0);
        }
    } else {
        move_on(actor);
    }
}
CLEAN_AS(func_ov003_02211a4c, FieldActor_EndState5E)

/* func_ov003_02211ac0: except during animation 0x49, by frame. During animation 0x4b: 2 effect
 * 6 at the point; 5 sound 0x841 and flag 9; 7 effect 7 at the point (at the actor's yaw), the
 * point to func_ov003_02221294 (kind 0), flag 0x1c cleared and func_02030db8 for its tile.
 * During the others: 5 sound 0x85b and flag 9; 12 effect 6; 18 effect 8 (at the yaw); 21 the
 * point and yaw to func_ov003_02220f40, the point to func_ov003_02221294, sound 0x85c and flag
 * 0x1c cleared. */
void FieldActor_AnimateState5E(FieldActor *actor)
{
    if (actor->animation != 0x49) {
        Vec3 point = actor->work.s5e.point;
        s16 yaw = actor->yaw;
        if (actor->animation == 0x4b) {
            switch (anim_frame(actor)) {
                case 2:
                    func_020912d4(6, &point, NULL, 0);
                    break;
                case 5:
                    func_0200f328(actor, 0x841);
                    func_0200f27c(actor, 9);
                    break;
                case 7: {
                    int x;
                    int z;
                    func_020912d4(7, &point, &yaw, 0);
                    Vec3 copy = point;
                    func_ov003_02221294(actor->player, &copy, 0);
                    func_0200f268(actor, 0x1c);
                    func_0204f818(&x, &z, &point);
                    func_02030db8(x, z);
                    break;
                }
                default:
                    break;
            }
        } else {
            switch (anim_frame(actor)) {
                case 5:
                    func_0200f328(actor, 0x85b);
                    func_0200f27c(actor, 9);
                    break;
                case 12:
                    func_020912d4(6, &point, NULL, 0);
                    break;
                case 18:
                    func_020912d4(8, &point, &yaw, 0);
                    break;
                case 21: {
                    Vec3 copy = point;
                    func_ov003_02220f40(actor->player, &copy, actor->yaw);
                    Vec3 copy2 = point;
                    func_ov003_02221294(actor->player, &copy2, 0);
                    func_0200f328(actor, 0x85c);
                    func_0200f268(actor, 0x1c);
                    break;
                }
                default:
                    break;
            }
        }
    }
    func_02010f5c(actor);
}
CLEAN_AS(func_ov003_02211ac0, FieldActor_AnimateState5E)

/* func_ov003_02211c20: leaving state 0x5e: another player's actor with flag 0x1c still set
 * sends the point on as the animation would have (during 0x4b to func_ov003_02221294 only;
 * otherwise first with the yaw to func_ov003_02220f40), and the flag is cleared. */
void FieldActor_ExitState5E(FieldActor *actor)
{
    if (is_local_player(actor)) {
        return;
    }
    if (!func_0200f290(actor, 0x1c)) {
        return;
    }
    Vec3 point = actor->work.s5e.point;
    if (actor->animation == 0x4b) {
        Vec3 copy = point;
        func_ov003_02221294(actor->player, &copy, 0);
    } else {
        Vec3 copy = point;
        func_ov003_02220f40(actor->player, &copy, actor->yaw);
        Vec3 copy2 = point;
        func_ov003_02221294(actor->player, &copy2, 0);
    }
    func_0200f268(actor, 0x1c);
}
CLEAN_AS(func_ov003_02211c20, FieldActor_ExitState5E)

/* func_ov003_02211cbc: state 0x5e's message handler: nothing. */
void FieldActor_State5EMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov003_02211cbc, FieldActor_State5EMessage)

/* func_ov003_02211cc0: entering state 0x5e: the request's flag and point become the work.
 * Coming from animation 0x49 or 0x4a, animation 0x4e (with the flag) or 0x4b follows at once;
 * otherwise animation 0x49 starts. Flag 0x1c is set. */
void FieldActor_EnterState5E(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State5EWork *args = (const State5EWork *) (const void *) request->payload;
    Vec3 point = args->point;

    State5EWork_Set(&actor->work.s5e, (char) args->flag, &point);
    if (actor->animation == 0x49 || actor->animation == 0x4a) {
        if (actor->work.s5e.flag != 0) {
            func_020109a0(actor, 0x4e, 3, 0);
        } else {
            func_020109a0(actor, 0x4b, 3, 0);
        }
    } else {
        func_020109a0(actor, 0x49, 3, 0);
    }
    func_0200f27c(actor, 0x1c);
}
CLEAN_AS(func_ov003_02211cc0, FieldActor_EnterState5E)

/* func_ov003_02211d3c: returns `work`. */
State5EWork *State5EWork_Set(State5EWork *work, char flag, const Vec3 *point)
{
    work->flag = (u8) flag;
    copy_point(&work->point, point);
    return work;
}
CLEAN_AS(func_ov003_02211d3c, State5EWork_Set)

/* func_ov003_02211d4c: asks for state 0x5e with a flag and a point; whether it was queued. */
int FieldActor_RequestState5E(FieldActor *actor, int flag, const Vec3 *point, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x5e, priority, arg);
    Vec3 copy = *point;
    State5EArgs_Set((State5EWork *) (void *) request.payload, (char) flag, &copy);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02211d4c, FieldActor_RequestState5E)

/* func_ov003_02211da0 */
void State5EArgs_Set(State5EWork *args, char flag, const Vec3 *point)
{
    args->flag = (u8) flag;
    copy_point(&args->point, point);
}
CLEAN_AS(func_ov003_02211da0, State5EArgs_Set)

/* ---- State 0x5d: animation 0x4c at a tile, with what was met there */

static_assert(offsetof(FieldActor, unk_14C) == 0x14c, "0x14c");
static_assert(offsetof(FieldActor, unk_1C4) == 0x1c4, "0x1c4");
static_assert(offsetof(FieldActor, work.s59.yaw) == 0x7e0, "state 0x59 yaw");
static_assert(offsetof(FieldActor, work.s59.fixed) == 0x7e2, "state 0x59 fixed");
static_assert(offsetof(FieldActor, work.s5a.has_target) == 0x7d6, "state 0x5a target");
static_assert(offsetof(FieldActor, saved.s5d.other_result) == 0x8f3, "state 0x5d saved");
static_assert(offsetof(FieldActor, saved.s58.angle) == 0x8f2, "state 0x58 angle");
static_assert(sizeof(State59Work) == 0x10, "state 0x59 work");
static_assert(sizeof(State5EWork) <= sizeof(((StateRequest *) 0)->payload), "state 0x5e payload");

/* max(value - 0x9c, min) */
extern int func_02011398(int value, int min);
extern void func_ov003_022241a4(int *tile);
extern int func_ov003_0221abf8(void *object, int flag);
/* Turns the actor towards a point. */
extern void func_02010d88(FieldActor *actor, const Vec3 *point, int a, int b);
extern void func_02089fc8(void *p);
extern int func_0203f8d0(Vec3 *out, Vec3 *in);
extern int func_0206f728(int item);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern int func_020644cc(int range);
extern void func_ov003_0222e6c4(u8 player, int a);
extern void func_ov003_0222eabc(u8 player, int angle);
extern int func_ov003_0222ea84(u8 player);
extern Vec3 *func_ov003_0222e970(u8 player);
/* Moves the block's point (its last three words) by `offset` (none: NULL) along the block. */
extern void func_ov003_02219668(FieldActorBlock48 *block, const Vec3 *offset);
extern int func_ov003_0222d83c(u8 player, s16 *angles, FieldActorBlock48 *block, int a);
/* A halfword packed into two bytes, and read back. */
extern void func_02077910(u8 *packed, int value);
extern s16 func_020778f8(const u8 *packed);

/* The absolute value as the ARM computes it (-0x80000000 stays itself). */
static int abs32(int value)
{
    return value < 0 ? sub32(0, value) : value;
}

/* func_ov003_02211db0: state 0x5d's update. The speed at 0x98 slows by 0x9c a frame, towards 0,
 * and is stored negated. */
void FieldActor_UpdateState5D(FieldActor *actor)
{
    FieldActor_AnimateState5D(actor);
    func_0201100c(actor);
    func_02010d64(actor);
    int speed = sub32(0, func_02011398(abs32(actor->unk_098), 0));
    func_0201107c(actor, &speed);
    FieldActor_EndState5D(actor);
}
CLEAN_AS(func_ov003_02211db0, FieldActor_UpdateState5D)

/* func_ov003_02211df8: at the animation's end the actor moves on. */
void FieldActor_EndState5D(FieldActor *actor)
{
    if (func_02056f94(&actor->anim)) {
        move_on(actor);
    }
}
CLEAN_AS(func_ov003_02211df8, FieldActor_EndState5D)

/* func_ov003_02211e38: on reaching frame 5: with the work's flag, the tile goes to
 * func_ov003_022241a4 and flags 0x12 and 0x1c are cleared; the speed becomes -0x333; on a map
 * object of a growth line ahead the tile ahead goes to func_ov003_02224384 (1); flag 9 is set.
 * Then a sound by what was met (other_result): nothing met (0) gives sound 0x7df when the map
 * object ahead is of kind 0 to 4 (outside 0xe3-0xfb and the growth lines) or of kind 10, 13 or
 * 14, else sound 0x844 and effect 5 0.8 ahead and 0.5 to the side of the actor; an object of
 * main's tables (2) is told the held item (its vtable slot 24) after sound 0x7df; an object of
 * overlay 3 (3) gets func_ov003_0221abf8 for the actor of this console, sound 0x7df when that
 * fails or for another player's actor; 1 gives sound 0x7df. What was met is forgotten. */
void FieldActor_AnimateState5D(FieldActor *actor)
{
    func_02010f5c(actor);
    if (!func_02056f28(&actor->anim, 5)) {
        return;
    }
    const TileFlagArgs *work = &actor->work.s5d;
    if (work->flag != 0) {
        int tile[2] = {work->x, work->z};
        func_ov003_022241a4(tile);
        func_0200f268(actor, 0x12);
        func_0200f268(actor, 0x1c);
    }
    int speed = -0x333;
    func_0201107c(actor, &speed);

    Vec3 ahead;
    int x = 0;
    int z = 0;
    func_0200fa8c(&ahead, actor);
    func_0204f818(&x, &z, &ahead);
    u16 *object = map_object_at(x, z);
    if (object != NULL && is_growth_object(*object)) {
        int tile[2] = {x, z};
        func_ov003_02224384(actor->player, tile, 1);
    }
    func_0200f27c(actor, 9);

    int object_kind = object != NULL ? (*object & 0xf000) >> 12 : 0xf;
    switch (actor->other_result) {
        case 0: {
            BOOL plain = FALSE;
            if (object != NULL) {
                if (object_kind <= 4 && !in_range(*object, 0xe3, 0xfb) && !is_growth_object(*object)) {
                    plain = TRUE;
                } else if (object_kind == 10 || object_kind == 13 || object_kind == 14) {
                    plain = TRUE;
                }
            }
            if (plain) {
                func_0200f328(actor, 0x7df);
                break;
            }
            func_0200f328(actor, 0x844);
            Vec3 at = actor->position;
            s16 angle = actor->yaw;
            int index = ((u16) angle >> 4) * 2;
            fx32 sine = FX_SinCosTable_[index];
            fx32 cosine = FX_SinCosTable_[index + 1];
            fx32 forward_z = FX_MulFunc(cosine, 0xccd);
            fx32 side_z = FX_MulFunc(sine, 0x800);
            fx32 dz = sub32(forward_z, side_z);
            fx32 forward_x = FX_MulFunc(sine, 0xccd);
            fx32 side_x = FX_MulFunc(cosine, 0x800);
            fx32 dx = add32(forward_x, side_x);
            at.x = add32(at.x, dx);
            at.z = add32(at.z, dz);
            angle = (s16) (angle - 0x2000);
            func_020912d4(5, &at, &angle, 0);
            break;
        }
        case 1:
            func_0200f328(actor, 0x7df);
            break;
        case 2:
            func_0200f328(actor, 0x7df);
            if (actor->other != NULL) {
                u16 item;
                func_020110c4(&item, actor);
                GameObject *other = (GameObject *) actor->other;
                ItemQuery query = (ItemQuery) (uintptr_t) other->vtable[24];
                query(other, &item);
            }
            break;
        case 3:
            if (is_local_player(actor) && func_ov003_0221abf8(actor->other, 1)) {
                break;
            }
            func_0200f328(actor, 0x7df);
            break;
        default:
            break;
    }
    actor->other = NULL;
    actor->other_result = 0;
}
CLEAN_AS(func_ov003_02211e38, FieldActor_AnimateState5D)

/* func_ov003_02212158: leaving state 0x5d: another player's actor with flag 0x1c still set does
 * what frame 5 would have (with the work's flag, the tile to func_ov003_022241a4 and flags 0x12
 * and 0x1c cleared). */
void FieldActor_ExitState5D(FieldActor *actor)
{
    if (is_local_player(actor)) {
        return;
    }
    if (!func_0200f290(actor, 0x1c)) {
        return;
    }
    const TileFlagArgs *work = &actor->work.s5d;
    if (work->flag != 0) {
        int tile[2] = {work->x, work->z};
        func_ov003_022241a4(tile);
        func_0200f268(actor, 0x12);
        func_0200f268(actor, 0x1c);
    }
}
CLEAN_AS(func_ov003_02212158, FieldActor_ExitState5D)

/* func_ov003_022121b8: state 0x5d's message handler: the saved verdict on what was met comes
 * back, and without the flag the state is asked for again at the saved tile. */
void FieldActor_State5DMessage(FieldActor *actor, int arg)
{
    u8 flag;
    u8 x;
    u8 z;
    u8 other_result;

    State5DSaved_Get(&actor->saved.s5d, &flag, &x, &z, &other_result);
    actor->other_result = other_result;
    if (flag == 0) {
        int tile[2] = {x, z};
        FieldActor_RequestState5D(actor, 0, tile, 6, (s16) arg);
    }
}
CLEAN_AS(func_ov003_022121b8, FieldActor_State5DMessage)

/* func_ov003_0221220c: entering state 0x5d: the request's tile and flag become the work and
 * are saved with the verdict on what was met; animation 0x4c starts; with the flag, flag 0x1c
 * is set. */
void FieldActor_EnterState5D(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const TileFlagArgs *args = (const TileFlagArgs *) (const void *) request->payload;
    u8 flag = args->flag;
    u8 x = args->x;
    u8 z = args->z;
    u32 tile[2] = {x, z};

    State5DWork_Set(&actor->work.s5d, tile, flag);
    State5DSaved_Set(&actor->saved.s5d, flag, x, z, actor->other_result);
    func_020109a0(actor, 0x4c, 3, 0);
    if (flag != 0) {
        func_0200f27c(actor, 0x1c);
    }
}
CLEAN_AS(func_ov003_0221220c, FieldActor_EnterState5D)

/* func_ov003_02212270 */
void State5DSaved_Get(const State5DSaved *saved, u8 *flag, u8 *x, u8 *z, u8 *other_result)
{
    *flag = saved->flag;
    *x = saved->x;
    *z = saved->z;
    *other_result = saved->other_result;
}
CLEAN_AS(func_ov003_02212270, State5DSaved_Get)

/* func_ov003_0221228c */
void State5DSaved_Set(State5DSaved *saved, u8 flag, u8 x, u8 z, u8 other_result)
{
    saved->flag = flag;
    saved->x = x;
    saved->z = z;
    saved->other_result = other_result;
}
CLEAN_AS(func_ov003_0221228c, State5DSaved_Set)

/* func_ov003_022122a0 */
void State5DWork_Set(TileFlagArgs *work, const u32 *tile, u8 flag)
{
    work->x = (u8) tile[0];
    work->z = (u8) tile[1];
    work->flag = flag;
}
CLEAN_AS(func_ov003_022122a0, State5DWork_Set)

/* func_ov003_022122ac: asks for state 0x5d with a flag and a tile; whether it was queued. */
int FieldActor_RequestState5D(FieldActor *actor, int flag, const int *tile, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x5d, priority, arg);
    u32 copy[2] = {(u32) tile[0], (u32) tile[1]};
    State5DArgs_Set((TileFlagArgs *) (void *) request.payload, copy, (u8) flag);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022122ac, FieldActor_RequestState5D)

/* func_ov003_022122fc */
void State5DArgs_Set(TileFlagArgs *args, const u32 *tile, u8 flag)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    args->flag = flag;
}
CLEAN_AS(func_ov003_022122fc, State5DArgs_Set)

/* ---- State 0x5c: animation 0x5e while the actor slows down */

/* func_ov003_02212308: state 0x5c's update: the speed at 0x98 slows by 0x171 a frame. */
void FieldActor_UpdateState5C(FieldActor *actor)
{
    func_02010f5c(actor);
    func_0201100c(actor);
    func_02010d64(actor);
    int speed = func_020113a4(actor->unk_098, 0, 0x171);
    func_0201107c(actor, &speed);
    FieldActor_EndState5C(actor);
}
CLEAN_AS(func_ov003_02212308, FieldActor_UpdateState5C)

/* func_ov003_02212348: at the animation's end the actor moves on. */
void FieldActor_EndState5C(FieldActor *actor)
{
    if (func_02056f94(&actor->anim)) {
        move_on(actor);
    }
}
CLEAN_AS(func_ov003_02212348, FieldActor_EndState5C)

/* func_ov003_02212388: state 0x5c's message handler: the state is asked for again. */
void FieldActor_State5CMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState5C(actor, 6, arg);
}
CLEAN_AS(func_ov003_02212388, FieldActor_State5CMessage)

/* func_ov003_02212394: entering state 0x5c: animation 0x5e. */
void FieldActor_EnterState5C(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    func_020109a0(actor, 0x5e, 3, 0);
}
CLEAN_AS(func_ov003_02212394, FieldActor_EnterState5C)

/* func_ov003_022123a8: asks for state 0x5c; whether it was queued. */
int FieldActor_RequestState5C(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x5c, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_022123a8, FieldActor_RequestState5C)

/* ---- State 0x5b: animation 0x4d with sound 0x842 */

/* func_ov003_022123e0: state 0x5b's update. */
void FieldActor_UpdateState5B(FieldActor *actor)
{
    FieldActor_AnimateState5B(actor);
    func_02010d64(actor);
    FieldActor_EndState5B(actor);
}
CLEAN_AS(func_ov003_022123e0, FieldActor_UpdateState5B)

/* func_ov003_022123fc: at the animation's end the actor moves on. */
void FieldActor_EndState5B(FieldActor *actor)
{
    if (func_02056f94(&actor->anim)) {
        move_on(actor);
    }
}
CLEAN_AS(func_ov003_022123fc, FieldActor_EndState5B)

/* func_ov003_0221243c: sound 0x842 on reaching frame 5. */
void FieldActor_AnimateState5B(FieldActor *actor)
{
    if (func_02056f28(&actor->anim, 5)) {
        func_0200f328(actor, 0x842);
    }
    func_02010f5c(actor);
}
CLEAN_AS(func_ov003_0221243c, FieldActor_AnimateState5B)

/* func_ov003_0221246c: state 0x5b's message handler: the state is asked for again. */
void FieldActor_State5BMessage(FieldActor *actor, int arg)
{
    FieldActor_RequestState5B(actor, 6, arg);
}
CLEAN_AS(func_ov003_0221246c, FieldActor_State5BMessage)

/* func_ov003_02212478: entering state 0x5b: animation 0x4d. */
void FieldActor_EnterState5B(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    func_020109a0(actor, 0x4d, 3, 0);
}
CLEAN_AS(func_ov003_02212478, FieldActor_EnterState5B)

/* func_ov003_0221248c: asks for state 0x5b; whether it was queued. */
int FieldActor_RequestState5B(FieldActor *actor, int priority, int arg)
{
    return request_state(actor, 0x5b, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0221248c, FieldActor_RequestState5B)

/* ---- State 0x5a: the actor faces a tile and acts on it */

/* func_ov003_022124c4: state 0x5a's update: the speed at 0x98 slows by 0x9c a frame; the actor
 * of this console acts on the work's tile (FieldActor_ActAt), another player's actor notes the
 * state after this one. The actor turns to the tile, and effect 0x2a marks the frame it stops. */
void FieldActor_UpdateState5A(FieldActor *actor)
{
    int speed_before = actor->unk_098;
    int speed = func_02011398(speed_before, 0);
    func_0201107c(actor, &speed);
    func_02010f5c(actor);
    if (is_local_player(actor)) {
        func_0201100c(actor);
        func_02010d64(actor);
        Vec3 zero = {0, 0, 0};
        FieldActor_ActAt(actor, &zero, 0);
    } else {
        if (func_0200f554(actor)) {
            func_0201100c(actor);
        }
        func_02010d64(actor);
        actor->next_state = func_02008258(actor, actor->state);
    }
    FieldActor_FaceState5ATile(actor);
    if (speed_before != 0 && actor->unk_098 == 0) {
        func_020912d4(0x2a, &actor->position, &actor->yaw, 0);
    }
}
CLEAN_AS(func_ov003_022124c4, FieldActor_UpdateState5A)

/* func_ov003_02212574: once the actor has stopped (the speed at 0x98 is 0; else -1), asks for
 * the state FieldActor_ClassifyAt picks for a point and returns that verdict: 1 state 0x5b, 2
 * state 0x5d at the point's tile, 3 and 4 state 0x5e at the point (flag 0 and 1), 5 and 9 state
 * 0x5f at the point (kind 0 and 1), 6 state 0x62 at the tile with no item, 7 state 0x5c, 8
 * state 0x5d with the flag; 0 nothing.
 * With `use_point` the point is `*point` and objects met are checked. Without it (state 0x5a)
 * the point is the middle of the work's tile, and objects met are checked only while no target
 * was known; a target found then is remembered in the work. */
int FieldActor_ActAt(FieldActor *actor, Vec3 *point, u8 use_point)
{
    if (actor->unk_098 != 0) {
        return -1;
    }

    State5AWork *work = &actor->work.s5a;
    BOOL first_look = FALSE;
    Vec3 at;
    if (use_point) {
        copy_point(&at, point);
    } else {
        func_0204f794(&at, work->x, work->z);
        if (work->has_target == 0) {
            first_look = TRUE;
            use_point = 1;
        }
    }

    int verdict = FieldActor_ClassifyAt(actor, &at, &use_point);
    int tile[2] = {0, 0};
    func_0204f818(&tile[0], &tile[1], &at);
    if (first_look && actor->target != -1) {
        work->has_target = 1;
    }

    switch (verdict) {
        case 1:
            FieldActor_RequestState5B(actor, 6, -1);
            break;
        case 2:
        case 8: {
            int copy[2] = {tile[0], tile[1]};
            FieldActor_RequestState5D(actor, verdict == 8, copy, 6, -1);
            break;
        }
        case 3:
        case 4: {
            Vec3 copy = at;
            FieldActor_RequestState5E(actor, verdict == 4, &copy, 6, -1);
            break;
        }
        case 5:
        case 9: {
            Vec3 copy = at;
            FieldActor_RequestState5FNoItem(actor, &copy, verdict == 9, 6, -1);
            break;
        }
        case 6: {
            int x = 0;
            int z = 0;
            func_0204f818(&x, &z, &at);
            u32 copy[2] = {(u32) x, (u32) z};
            FieldActor_RequestState62(actor, 0, copy, ITEM_NONE, 6, -1);
            break;
        }
        case 7:
            FieldActor_RequestState5C(actor, 6, -1);
            break;
        default:
            break;
    }
    return verdict;
}
CLEAN_AS(func_ov003_02212574, FieldActor_ActAt)

/* func_ov003_02212728: the actor turns towards the middle of the work's tile. */
void FieldActor_FaceState5ATile(FieldActor *actor)
{
    Vec3 middle;
    func_0204f794(&middle, actor->work.s5a.x, actor->work.s5a.z);
    func_02010d88(actor, &middle, 0xf33, 0x1000);
    func_02089fc8(actor->unk_1C4);
}
CLEAN_AS(func_ov003_02212728, FieldActor_FaceState5ATile)

/* func_ov003_02212768: state 0x5a's message handler: the state is asked for again at the saved
 * tile. */
void FieldActor_State5AMessage(FieldActor *actor, int arg)
{
    int tile[2] = {0, 0};
    State5ASaved_Get(&actor->saved.tile, tile);
    int copy[2] = {tile[0], tile[1]};
    FieldActor_RequestState5A(actor, copy, 6, arg);
}
CLEAN_AS(func_ov003_02212768, FieldActor_State5AMessage)

/* func_ov003_022127a0: entering state 0x5a: the request's tile becomes the work's and is saved;
 * whether a target is known goes to the work; during animation 0x4a it is set again
 * (func_020109fc). */
void FieldActor_EnterState5A(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const TileArgs *args = (const TileArgs *) (const void *) request->payload;
    int x = args->x;
    int z = args->z;

    int tile[2] = {x, z};
    State5AWork_SetTile(&actor->work.s5a, tile);
    actor->work.s5a.has_target = actor->target != -1;
    int copy[2] = {x, z};
    State5ASaved_Set(&actor->saved.tile, copy);
    if (actor->animation == 0x4a) {
        func_020109fc(actor, 0x4a, 3, 0);
    }
}
CLEAN_AS(func_ov003_022127a0, FieldActor_EnterState5A)

/* func_ov003_0221280c */
void State5ASaved_Get(const TileArgs *saved, int *tile)
{
    tile[0] = saved->x;
    tile[1] = saved->z;
}
CLEAN_AS(func_ov003_0221280c, State5ASaved_Get)

/* func_ov003_02212818 */
void State5ASaved_Set(TileArgs *saved, const int *tile)
{
    saved->x = (u8) tile[0];
    saved->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_02212818, State5ASaved_Set)

/* func_ov003_02212824 */
void State5AWork_SetTile(State5AWork *work, const int *tile)
{
    work->x = (u8) tile[0];
    work->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_02212824, State5AWork_SetTile)

/* func_ov003_02212830: asks for state 0x5a at a tile; whether it was queued. */
void *FieldActor_RequestState5A(FieldActor *actor, const int *tile, int priority, int arg)
{
    StateRequest request;

    open_request(&request, 0x5a, priority, arg);
    int copy[2] = {tile[0], tile[1]};
    State5AArgs_Set((TileArgs *) (void *) request.payload, copy);
    return (void *) (intptr_t) send_request(actor, &request);
}
CLEAN_AS(func_ov003_02212830, FieldActor_RequestState5A)

/* func_ov003_02212878 */
void State5AArgs_Set(TileArgs *args, const int *tile)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
}
CLEAN_AS(func_ov003_02212878, State5AArgs_Set)

/* ---- State 0x59: animation 0x49 then 0x4a while the actor slides to a point */

/* func_ov003_02212884: state 0x59's update: the speed at 0x98 slows by 0x171 a frame. The actor
 * of this console turns to the point (FieldActor_TurnState59) and acts there once stopped
 * (FieldActor_RunState59); another player's actor follows the state it is told
 * (FieldActor_EndState59Remote). Effect 0x2a marks the frame the actor stops. */
void FieldActor_UpdateState59(FieldActor *actor)
{
    int speed_before = actor->unk_098;
    int speed = func_020113a4(speed_before, 0, 0x171);
    func_0201107c(actor, &speed);
    if (is_local_player(actor)) {
        FieldActor_TurnState59(actor);
        func_02010f5c(actor);
        func_0201100c(actor);
        func_02010d64(actor);
        FieldActor_RunState59(actor);
        FieldActor_FaceState59Point(actor);
    } else {
        func_02010f5c(actor);
        if (func_0200f554(actor)) {
            func_0201100c(actor);
        }
        func_02010d64(actor);
        FieldActor_EndState59Remote(actor);
    }
    if (speed_before != 0 && actor->unk_098 == 0) {
        func_020912d4(0x2a, &actor->position, &actor->yaw, 0);
    }
}
CLEAN_AS(func_ov003_02212884, FieldActor_UpdateState59)

/* func_ov003_0221292c: another player's actor notes the state after this one; at the
 * animation's end animation 0x4a is set (func_020109fc). */
void FieldActor_EndState59Remote(FieldActor *actor)
{
    actor->next_state = func_02008258(actor, actor->state);
    if (func_02056f94(&actor->anim)) {
        func_020109fc(actor, 0x4a, 3, 0);
    }
}
CLEAN_AS(func_ov003_0221292c, FieldActor_EndState59Remote)

/* func_ov003_02212968: once animation 0x49 is over (it gives way to 0x4a) or during 0x4a: when
 * the actor has stopped and faces the work's yaw, it acts at the work's point
 * (FieldActor_ActAt); with nothing to do there, state 0x5a follows at the point's tile. */
void FieldActor_RunState59(FieldActor *actor)
{
    State59Work *work = &actor->work.s59;

    if (!func_02056f94(&actor->anim) && actor->animation != 0x4a) {
        return;
    }
    if (actor->animation == 0x49) {
        func_020109fc(actor, 0x4a, 3, 0);
    }
    if (actor->unk_098 != 0) {
        return;
    }
    if (work->yaw != actor->yaw) {
        return;
    }
    Vec3 point = work->point;
    Vec3 copy = point;
    if (FieldActor_ActAt(actor, &copy, 1) != 0) {
        return;
    }
    int tile[2] = {0, 0};
    func_0204f818(&tile[0], &tile[1], &point);
    int tile_copy[2] = {tile[0], tile[1]};
    FieldActor_RequestState5A(actor, tile_copy, 6, -1);
}
CLEAN_AS(func_ov003_02212968, FieldActor_RunState59)

/* func_ov003_02212a14: the actor turns towards the work's point. */
void FieldActor_FaceState59Point(FieldActor *actor)
{
    Vec3 point = actor->work.s59.point;
    func_02010d88(actor, &point, 0xf33, 0x1000);
    func_02089fc8(actor->unk_1C4);
}
CLEAN_AS(func_ov003_02212a14, FieldActor_FaceState59Point)

/* func_ov003_02212a54: the actor turns towards the work's yaw. Once it has stopped while the
 * point is not fixed, the point becomes the tile ahead and the yaw the direction to it from the
 * frame's start position, and the point is fixed. */
void FieldActor_TurnState59(FieldActor *actor)
{
    State59Work *work = &actor->work.s59;
    s16 yaw;

    if (actor->unk_098 == 0 && work->fixed == 0) {
        Vec3 ahead;
        func_0200fa8c(&ahead, actor);
        yaw = Math_Atan2(sub32(ahead.x, actor->start_position.x), sub32(ahead.z, actor->start_position.z));
        work->yaw = yaw;
        work->fixed = 1;
        work->point = ahead;
    } else {
        yaw = work->yaw;
    }
    func_0200fb34(actor, yaw);
}
CLEAN_AS(func_ov003_02212a54, FieldActor_TurnState59)

/* func_ov003_02212ac0: state 0x59's message handler: the state is asked for again with the
 * saved tile and flag. */
void FieldActor_State59Message(FieldActor *actor, int arg)
{
    u8 x;
    u8 z;
    u8 fixed;

    State59Saved_Get(&actor->saved.s59, &x, &z, &fixed);
    FieldActor_RequestState59(actor, &x, &z, &fixed, 6, (s16) arg);
}
CLEAN_AS(func_ov003_02212ac0, FieldActor_State59Message)

/* func_ov003_02212afc: entering state 0x59: the request is saved and animation 0x49 starts. The
 * point is the middle of the request's tile when its flag is set; otherwise it is where the
 * actor's slide ends (0x2000 ahead plus each frame's speed as it slows by 0x171 a frame), at
 * the middle of that tile. The work gets the point, the direction to it from the frame's start
 * position and the flag. */
void FieldActor_EnterState59(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const TileFlagArgs *args = (const TileFlagArgs *) (const void *) request->payload;
    int x = args->x;
    int z = args->z;
    int fixed = args->flag;

    State59Saved_Set(&actor->saved.s59, x, z, fixed);
    func_020109a0(actor, 0x49, 3, 0);
    Vec3 point;
    func_0204f794(&point, (u32) x, (u32) z);
    if (fixed == 0) {
        /* QUIRK: the speed is taken as it is: a negative one adds nothing, and one within 0x171
         * of -0x80000000 wraps round to a large positive one. */
        int speed = actor->unk_098;
        fx32 distance = 0x2000;
        while (speed != 0) {
            speed = sub32(speed, 0x171);
            if (speed > 0) {
                distance = add32(distance, speed);
            } else {
                speed = 0;
            }
        }
        Vec3 end;
        func_0200fa1c(&end, actor, &actor->position, &actor->yaw, &distance);
        point = end;
        func_0204f7e0(&point, &point);
    }
    s16 yaw = Math_Atan2(sub32(point.x, actor->start_position.x), sub32(point.z, actor->start_position.z));
    Vec3 copy = point;
    State59Work_Set(&actor->work.s59, &copy, yaw, (char) fixed);
}
CLEAN_AS(func_ov003_02212afc, FieldActor_EnterState59)

/* func_ov003_02212bd8 */
void State59Saved_Get(const TileFlagArgs *saved, u8 *x, u8 *z, u8 *fixed)
{
    *x = saved->x;
    *z = saved->z;
    *fixed = saved->flag;
}
CLEAN_AS(func_ov003_02212bd8, State59Saved_Get)

/* func_ov003_02212bec */
void State59Saved_Set(TileFlagArgs *saved, int x, int z, int fixed)
{
    saved->x = (u8) x;
    saved->z = (u8) z;
    saved->flag = (u8) fixed;
}
CLEAN_AS(func_ov003_02212bec, State59Saved_Set)

/* func_ov003_02212bf4 */
void State59Work_Set(State59Work *work, const Vec3 *point, s16 yaw, char fixed)
{
    copy_point(&work->point, point);
    work->yaw = yaw;
    work->fixed = (u8) fixed;
    work->unk_0F = 0;
}
CLEAN_AS(func_ov003_02212bf4, State59Work_Set)

/* func_ov003_02212c10: asks for state 0x59 with a tile and a flag; whether it was queued. */
int FieldActor_RequestState59(FieldActor *actor, const u8 *x, const u8 *z, const u8 *fixed, int priority, s16 arg)
{
    StateRequest request;

    open_request(&request, 0x59, priority, arg);
    State59Args_Set((TileFlagArgs *) (void *) request.payload, *x, *z, *fixed);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02212c10, FieldActor_RequestState59)

/* func_ov003_02212c58: asks for state 0x59 at the tile of the point the actor aims at:
 * aim_point with the flag when unk_148 is set, else the point at 0x14c with the flag when
 * unk_144 is nonzero (both at height 0). Whether it was queued. */
int FieldActor_RequestState59AtAim(FieldActor *actor, int priority, int arg)
{
    StateRequest request;
    Vec3 point;
    int fixed;

    open_request(&request, 0x59, priority, arg);
    if (actor->unk_148 != 0) {
        point.x = actor->aim_point.x;
        point.y = 0;
        point.z = actor->aim_point.z;
        fixed = 1;
    } else {
        point.x = actor->unk_14C.x;
        point.y = 0;
        point.z = actor->unk_14C.z;
        fixed = actor->unk_144 != 0;
    }
    int x = 0;
    int z = 0;
    func_0204f818(&x, &z, &point);
    State59Args_Set((TileFlagArgs *) (void *) request.payload, (u8) x, (u8) z, fixed);
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02212c58, FieldActor_RequestState59AtAim)

/* func_ov003_02212d04 */
void State59Args_Set(TileFlagArgs *args, int x, int z, int fixed)
{
    args->x = (u8) x;
    args->z = (u8) z;
    args->flag = (u8) fixed;
}
CLEAN_AS(func_ov003_02212d04, State59Args_Set)

/* ---- State 0x58: animation 0x5d with pose 6, then 0x6c, then the head follows a point */

/* func_ov003_02212d0c: state 0x58's update. */
void FieldActor_UpdateState58(FieldActor *actor)
{
    func_02010f5c(actor);
    func_0200f554(actor);
    func_02010d64(actor);
    FieldActor_RunState58(actor);
}
CLEAN_AS(func_ov003_02212d0c, FieldActor_UpdateState58)

/* Ends state 0x58: the state after it is noted and func_0200d4e8 (6) moves on. */
static void leave_state58(FieldActor *actor)
{
    actor->next_state = func_02008258(actor, actor->state);
    func_0200d4e8(actor, 6, 1, -1);
}

/* func_ov003_02212d2c: state 0x58 by the work's step. Each frame a block (a copy of the one at
 * 0x698) goes through func_ov003_02219668, and unless the frame ends early, to
 * func_ov003_0222d83c with three equal angles (100 falling by 16 a frame over the first six
 * frames of animation 0x5d, else 0) and a flag.
 *   Step 0: at the animation's end func_ov003_0222e6c4 (1), the actor moves on (6), the actor
 *     of this console gives the item 0x12b0 + kind to func_0209a110; the flag is 1.
 *   Step 1: during animation 0x5d, at its end animation 0x6c starts with pose 0 in hand. The
 *     block's point is a point by the actor. The actor of this console waits on the word at
 *     0x81c: at 5 it becomes 6 once func_0206f728 accepts the item; at 6 it becomes 0xf once
 *     func_0206fbc0 says so, and when func_0206fc6c then says so the receiver is released and
 *     the actor moves on (6); from 0xf an angle is drawn (-0x1555 to 0x1554) for
 *     func_ov003_0222eabc and saved, the receiver is released, and step 2 starts with animation
 *     0 (func_020109fc). Another player's actor notes the state after this one and goes to step
 *     2 when the saved step is 2, with the saved angle.
 *   Step 2: while func_ov003_0222ea84 is 3 the head turns to the point func_ov003_0222e970
 *     gives (the pitch at most 0x1800); otherwise the head turns back to 0 and once there the
 *     actor moves on (6). */
void FieldActor_RunState58(FieldActor *actor)
{
    int flag = 0;
    Vec3 beside = actor->position;
    int player = actor->player;

    s16 angle = 0;
    if (actor->animation == 0x5d) {
        u32 frame = (u32) anim_frame(actor);
        if (frame < 6) {
            angle = (s16) (0x64 - (frame << 4));
        }
    }
    s16 angles[3] = {angle, angle, angle};

    FieldActorBlock48 block = actor->unk_698;
    func_ov003_02219668(&block, NULL);

    State58Args *work = &actor->work.s58;
    State58Saved *saved = &actor->saved.s58;
    int item = (u16) (work->kind + 0x12b0);
    switch (work->step) {
        case 0:
            if (!func_02056f94(&actor->anim)) {
                break;
            }
            func_ov003_0222e6c4((u8) actor->player, 1);
            leave_state58(actor);
            if (is_local_player(actor)) {
                u16 code = (u16) item;
                func_0209a110(&code);
            }
            flag = 1;
            break;
        case 1:
            if (actor->animation == 0x5d) {
                if (!func_02056f94(&actor->anim)) {
                    break;
                }
                func_020109fc(actor, 0x6c, 3, 3);
                func_0205eae0(actor->held, 0, 3, 0);
            }
            beside.x = sub32(beside.x, 0x400);
            beside.y = add32(beside.y, 0x1b34);
            beside.z = add32(beside.z, 0x1400);
            func_0203f8d0(&beside, &beside);
            /* The block's last three words are its point. */
            block.words[9] = (u32) beside.x;
            block.words[10] = (u32) beside.y;
            block.words[11] = (u32) beside.z;
            if (is_local_player(actor)) {
                if (actor->unk_81C == 5) {
                    if (func_0206f728(item)) {
                        actor->unk_81C = 6;
                    }
                    break;
                }
                if (actor->unk_81C == 6) {
                    if (!func_0206fbc0()) {
                        break;
                    }
                    actor->unk_81C = 0xf;
                    if (func_0206fc6c()) {
                        release_receiver(actor);
                        func_0203e19c();
                        leave_state58(actor);
                        return;
                    }
                } else if (actor->unk_81C < 0xf) {
                    break;
                }
                int drawn = (s16) sub32(func_020644cc(0x2aaa), 0x1555);
                func_ov003_0222eabc((u8) player, drawn);
                State58Saved_SetAngle(saved, drawn);
                release_receiver(actor);
                func_0203e19c();
                work->step = 2;
                State58Saved_SetStep(saved, 2);
                func_020109fc(actor, 0, 4, 4);
                return;
            }
            actor->next_state = func_02008258(actor, actor->state);
            if (State58Saved_Step(saved) != 2) {
                return;
            }
            func_ov003_0222eabc((u8) player, State58Saved_Angle(saved));
            work->step = 2;
            func_020109fc(actor, 0, 4, 4);
            return;
        case 2: {
            if (func_ov003_0222ea84((u8) player) != 3) {
                if (actor->head_pitch == 0 && actor->head_yaw == 0) {
                    leave_state58(actor);
                    return;
                }
                func_02011404(&actor->head_pitch, 0, 0x400, 0x1770000, 0xc0000);
                func_02011404(&actor->head_yaw, 0, 0x400, 0x1770000, 0xc0000);
                return;
            }
            const Vec3 *target = func_ov003_0222e970((u8) player);
            Vec3 eye = actor->position;
            eye.y = add32(eye.y, 0x1b33);
            int yaw = Math_Atan2(sub32(target->x, eye.x), sub32(target->z, eye.z));
            int pitch = Math_Atan2(sub32(target->y, eye.y), Vec_DistanceXZ(target, &eye));
            actor->head_yaw = (s16) yaw;
            if (pitch >= 0x1800) {
                pitch = 0x1800;
            }
            actor->head_pitch = (s16) pitch;
            return;
        }
        default:
            break;
    }
    func_ov003_0222d83c((u8) player, angles, &block, flag);
}
CLEAN_AS(func_ov003_02212d2c, FieldActor_RunState58)

/* func_ov003_022130c8: leaving state 0x58: the head faces ahead. */
void FieldActor_ExitState58(FieldActor *actor)
{
    actor->head_pitch = 0;
    actor->head_yaw = 0;
}
CLEAN_AS(func_ov003_022130c8, FieldActor_ExitState58)

/* func_ov003_022130dc: state 0x58's message handler: the state is asked for again with the
 * saved kind and step (func_ov003_022131c8). */
void FieldActor_State58Message(FieldActor *actor, int arg)
{
    u8 kind;
    u8 step;
    /* QUIRK: the original reads the saved angle into a one-byte local, its second byte landing
     * past it in the stack frame; it is not used. */
    u16 angle;

    State58Saved_Get(&actor->saved.s58, &kind, &step, &angle);
    FieldActor_RequestState58(actor, (char) kind, (char) step, 6, (s16) arg);
}
CLEAN_AS(func_ov003_022130dc, FieldActor_State58Message)

/* func_ov003_02213114: entering state 0x58: the request's kind and step become the work and are
 * saved with angle 0; animation 0x5d starts with pose 6 in hand, and sound 0x4f. */
void FieldActor_EnterState58(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const State58Args *args = (const State58Args *) (const void *) request->payload;
    u8 kind = args->kind;
    u8 step = args->step;

    actor->work.s58.kind = kind;
    actor->work.s58.step = step;
    State58Saved_Set(&actor->saved.s58, kind, step, 0);
    func_020109a0(actor, 0x5d, 3, 0);
    func_0205eae0(actor->held, 6, 3, 1);
    func_0200f328(actor, 0x4f);
}
CLEAN_AS(func_ov003_02213114, FieldActor_EnterState58)

/* func_ov003_02213168 */
int State58Saved_Angle(const State58Saved *saved)
{
    return func_020778f8(saved->angle);
}
CLEAN_AS(func_ov003_02213168, State58Saved_Angle)

/* func_ov003_02213174 */
int State58Saved_Step(const State58Saved *saved)
{
    return saved->step;
}
CLEAN_AS(func_ov003_02213174, State58Saved_Step)

/* func_ov003_02213178 */
void State58Saved_Get(const State58Saved *saved, u8 *kind, u8 *step, u16 *angle)
{
    *kind = saved->kind;
    *step = (u8) State58Saved_Step(saved);
    *angle = (u16) State58Saved_Angle(saved);
}
CLEAN_AS(func_ov003_02213178, State58Saved_Get)

/* func_ov003_02213198 */
void State58Saved_SetAngle(State58Saved *saved, int angle)
{
    func_02077910(saved->angle, angle);
}
CLEAN_AS(func_ov003_02213198, State58Saved_SetAngle)

/* func_ov003_022131a4 */
void State58Saved_SetStep(State58Saved *saved, int step)
{
    saved->step = (u8) step;
}
CLEAN_AS(func_ov003_022131a4, State58Saved_SetStep)

/* func_ov003_022131a8 */
void State58Saved_Set(State58Saved *saved, u8 kind, int step, int angle)
{
    saved->kind = kind;
    State58Saved_SetStep(saved, step);
    State58Saved_SetAngle(saved, angle);
}
CLEAN_AS(func_ov003_022131a8, State58Saved_Set)

/* func_ov003_022131c8: asks for state 0x58 with a kind and a step; whether it was queued. */
int FieldActor_RequestState58(FieldActor *actor, char kind, char step, int priority, s16 arg)
{
    StateRequest request;
    open_request(&request, 0x58, priority, arg);
    State58Args *args = (State58Args *) (void *) request.payload;
    args->kind = (u8) kind;
    args->step = (u8) step;
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_022131c8, FieldActor_RequestState58)

/* ---- States 0x57 to 0x51: an insect or a fish caught */

static_assert(offsetof(FieldActor, unk_5D0) == 0x5d0, "0x5d0");
static_assert(offsetof(FieldActor, unk_810) == 0x810, "0x810");
static_assert(offsetof(FieldActor, unk_8C4) == 0x8c4, "0x8c4");
static_assert(offsetof(FieldActor, unk_1C4) == 0x1c4, "0x1c4");
static_assert(offsetof(FieldActor, unk_14C) == 0x14c, "0x14c");
static_assert(offsetof(FieldActor, work.s57.unk_04) == 0x7d8, "state 0x57 0x04");
static_assert(offsetof(FieldActor, work.s57.step) == 0x7dd, "state 0x57 step");
static_assert(offsetof(FieldActor, work.s57.unk_0A) == 0x7de, "state 0x57 0x0a");
static_assert(offsetof(FieldActor, work.s56.yaw) == 0x7d6, "state 0x56 yaw");
static_assert(offsetof(FieldActor, work.s56.slot) == 0x7d8, "state 0x56 slot");
static_assert(offsetof(FieldActor, work.s56.tip) == 0x7dc, "state 0x56 tip");
static_assert(offsetof(FieldActor, work.s54.unk_05) == 0x7d9, "state 0x54 0x05");
static_assert(offsetof(FieldActor, saved.s57.angle) == 0x8f4, "state 0x57 angle");
static_assert(offsetof(GroundInfo, unk_30) == 0x30, "ground 0x30");
static_assert(offsetof(GroundInfo, kind) == 0x34, "ground kind");

/* What func_02032adc makes for func_020311bc to test a segment against the scenery, with the
 * ground found at its start (func_02034270); func_02032acc ends it. */
typedef struct SegmentTest {
    u8 unk_00[0x14];
    GroundInfo ground;
} SegmentTest;

static_assert(sizeof(SegmentTest) == 0x54, "segment test");

/* The fish hanging from what the actor holds (func_020604f8). */
typedef struct HookedFish {
    u8 unk_00[0x7e];
    s8 kind; /* the item is 0x12e8 + kind */
    u8 unk_7F[0x1ff - 0x7f];
    u8 size; /* a row of the table at 0x0223c024 */
} HookedFish;

/* Rows of 0x14 bytes; the byte at 2 of each is a size in percent. */
extern const u8 data_ov003_0223c026[];
/* The receivers' names: "obj_etc_getinsect" and "obj_etc_getfish". */
extern const char data_ov003_02238144[];
extern const char data_ov003_02238158[];
/* Distances ahead of the actor (20.12) for func_0200fa1c in state 0x56: 2.85 (a stop at frame 4,
 * twice) and 2.0 (frame 3). */
extern const fx32 data_ov003_02238114;
extern const fx32 data_ov003_0223811c;
extern const fx32 data_ov003_02238120;
/* The `track` byte (1) of the requests for state 0x8f that states 0x55 and 0x54 end with. */
extern const u8 data_ov003_02238100;
extern const u8 data_ov003_02238104;
extern const u8 data_ov003_02238108;
/* The speed (-1049) state 0x52 starts with. */
extern int data_ov003_0223812c;

extern int func_0203cbd0(u16 *item);
extern int func_0203cc1c(void);
extern int func_0203cc38(void);
extern int func_02043368(int a, int *point, u8 *result);
extern void *func_020094a0(FieldActor *actor, u8 a, u8 kind, u8 slot, u32 priority, s16 arg);
extern int func_02043554(int player, int item);
extern int func_0206f6f8(int item, HookedFish *fish);
extern u16 func_0206f6a4(void);
extern HookedFish *func_020604f8(void *line);
extern void func_02060460(void *line);
extern void func_020604fc(void *line, int a);
extern int func_02060474(void *line);
extern void func_02060448(void *line);
extern void func_02079774(Vec3 *position);
extern void func_02079798(Vec3 *position);
extern void func_0208d07c(void *object);
extern void func_0208d09c(void *object);
extern int func_0208b500(void);
extern void func_ov003_0222e898(int kind, int player);
extern int func_020899a8(const Vec3 *from, const Vec3 *to, int radius, u8 *slot, int a);
extern int func_020311bc(SegmentTest *test, Vec3 *a, Vec3 *b, int flags);
extern void *func_02032adc(SegmentTest *test);
extern int func_02032acc(SegmentTest *test);
extern void func_0204489c(int *tile);
extern u8 func_ov003_0222e538(int slot, u8 player);
extern int func_ov003_0222e5fc(u8 slot);
extern int func_ov003_0222e3a4(u8 slot);
extern int func_ov003_0222f458(Vec3 *out, int slot);
extern int func_ov003_0222f490(int slot);
extern int func_ov003_0222aa50(HookedFish *fish, Vec3 *at, Vec3 *scale);
extern void func_ov003_0222aaa0(Vec3 *scale, int kind);
extern int func_ov003_0222a8a8(int player);
extern int func_02008c40(FieldActor *actor, int priority, int arg);
extern void *func_ov003_02215624(FieldActor *actor, u32 flag, int priority, int arg);
extern void func_ov003_02215620(u8 *work, int flag);
extern void func_ov003_0221561c(u8 *saved, int flag);

/* The ROM's signed division (_s32_div_f): a divisor of 0 gives the numerator back, and
 * -0x80000000 / -1 gives -0x80000000. */
static int div_s32(int numerator, int divisor)
{
    if (divisor == 0) {
        return numerator;
    }
    if (divisor == -1) {
        return sub32(0, numerator);
    }
    return numerator / divisor;
}

/* What hangs from the held item: the last word of `held`. */
static void *held_line(FieldActor *actor)
{
    return &actor->held[0x28];
}

/* Animation frame `frame` was reached (func_02056f28). */
static BOOL anim_passed(FieldActor *actor, int frame)
{
    return func_02056f28(&actor->anim, frame) != 0;
}

static BOOL anim_done(FieldActor *actor)
{
    return func_02056f94(&actor->anim) != 0;
}

/* The point of a block (its last three words). */
static Vec3 block_point(const FieldActorBlock48 *block)
{
    Vec3 point = {(fx32) block->words[9], (fx32) block->words[10], (fx32) block->words[11]};
    return point;
}

/* Whether the link of the receiver is up and what it opened is closed. */
static BOOL link_closed(const FieldActor *actor)
{
    return actor->link != NULL && actor->link->open == 0;
}

/* Releases the receiver without testing flag 0x11 first. */
static void close_receiver(FieldActor *actor)
{
    func_0203ee08(actor, actor->receiver);
    func_0200f268(actor, 0x11);
}

/* The items 0x1320 to 0x1322: kinds 0x38 to 0x3a past the fish of 0x12e8 to 0x131f. */
static BOOL is_item_1320(u16 item)
{
    return item >= 0x1320 && item <= 0x1322;
}

/* The work of states 0x57 and 0x54 that func_0200ee40 would rewrite. */
typedef struct KeptAcrossEE40 {
    Vec3 unk_0C4;
    s16 unk_0D0;
    FieldActorBlock48 unk_298;
    FieldActorBlock48 unk_698;
} KeptAcrossEE40;

static void keep_across_ee40(const FieldActor *actor, KeptAcrossEE40 *kept)
{
    kept->unk_0C4 = actor->unk_0C4;
    kept->unk_0D0 = actor->unk_0D0;
    kept->unk_298 = actor->unk_298;
    kept->unk_698 = actor->unk_698;
}

static void restore_after_ee40(FieldActor *actor, const KeptAcrossEE40 *kept)
{
    actor->unk_0C4 = kept->unk_0C4;
    actor->unk_0D0 = kept->unk_0D0;
    actor->unk_298 = kept->unk_298;
    actor->unk_698 = kept->unk_698;
}

/* ---- State 0x57: the insect caught is shown */

/* func_ov003_0221320c: state 0x57's update: func_0200ee40 runs between func_02010f5c and the
 * others, with the points and blocks it would change kept. */
void FieldActor_UpdateState57(FieldActor *actor)
{
    KeptAcrossEE40 kept;

    func_02010f5c(actor);
    keep_across_ee40(actor, &kept);
    func_0200ee40(actor);
    func_0200f554(actor);
    func_02010d64(actor);
    FieldActor_RunState57(actor);
    restore_after_ee40(actor, &kept);
}
CLEAN_AS(func_ov003_0221320c, FieldActor_UpdateState57)

/* func_ov003_022132bc: state 0x57 by the work's step. In mode 0 the actor holds still
 * (func_0200faf0). On the first frame the actor of this console goes to step 1 and another
 * player's to step 9 (telling func_ov003_0222e5fc the slot); kinds 0x18, 0x30, 0x32 and 0x33
 * get effect 0x25 at the block's point; func_ov003_0222e898 learns the kind.
 * Each frame the block at 0x698 is moved by an offset that grows over the end of animation 0x5c
 * (from frame 0x24) and the effect follows its point. Unless the frame ends early, the block
 * goes to func_ov003_0222d83c with three equal values: 0 before frame 0x17 of animation 0x5c,
 * then rising by 10 a frame to 100.
 *   Another player's actor notes the state after this one, and when its step is below 6 or 9
 *   and the saved step is 6, takes the saved angle (func_ov003_0222eabc), starts animation 0
 *   and goes to step 7.
 *   Step 1: once func_0203e1c4 says so the receiver is registered under "obj_etc_getinsect"
 *     with the item 0x12b0 + kind, its link is asked for, and the sounds are set; step 2.
 *   Step 2: once the link is open: step 8 (0x81c = 0xd) when func_0203cc1c says so and it did
 *     not on entering, else step 3 (0x81c = 8).
 *   Step 3: with func_02099fe8 at -1, step 4 (0x81c = 0) when func_02043368 accepts, else step
 *     5 (0x81c = 1). Otherwise once the link closes the receiver is released and state 0x58
 *     is asked for at step 0.
 *   Step 4: from 0x81c = 0xf on step 5; otherwise once the link closes the receiver is
 *     released and state 0x58 is asked for at step 1.
 *   Step 5: once the link closes the effect ends, an angle is drawn (-0x1555 to 0x1554) for
 *     func_ov003_0222eabc and saved, the receiver is released, animation 0 starts and the
 *     step (6) is saved.
 *   Step 6: while func_ov003_0222ea84 is 3 the head turns to the point func_ov003_0222e970
 *     gives (the pitch at most 0x1800); otherwise the head turns back to 0, and once there the
 *     actor moves on by its mode (in mode 2 the actor of this console first releases the
 *     receiver).
 *   Step 7: waits for func_ov003_0222ea84 to be 3 or 0, then step 6.
 *   Step 8: once the link closes the receiver is released and func_020094a0 runs. */
void FieldActor_RunState57(FieldActor *actor)
{
    State57Work *work = &actor->work.s57;
    State57Saved *saved = &actor->saved.s57;
    int mode = work->mode;
    int kind = work->kind;

    if (mode == 0) {
        func_0200faf0(actor, 0x400);
    }
    int player = actor->player;
    if (work->step == 0) {
        if (func_02073908(data_020ccf94, player)) {
            work->step = 1;
        } else {
            work->step = 9;
            if (work->slot != 0xff) {
                func_ov003_0222e5fc(work->slot);
            }
        }
        if (kind == 0x18 || kind == 0x30 || kind == 0x32 || kind == 0x33) {
            FieldActorBlock48 start = actor->unk_698;
            func_ov003_02219668(&start, NULL);
            Vec3 at = block_point(&start);
            func_0203f7d0(&at, &at);
            work->effect = func_020912d4(0x25, &at, NULL, 0);
        }
        func_ov003_0222e898(kind, (u8) player);
    }

    FieldActorBlock48 block = actor->unk_698;
    Vec3 offset = {0x4cd, 0, 0};
    if (actor->animation != 0x5c) {
        offset.x = 0x800;
        offset.y = 0x19a;
        offset.z = -0x19a;
    } else {
        int frame = anim_frame(actor);
        if (frame >= 0x24) {
            /* QUIRK: on the last frame of a 0x24-frame animation the divisor is 0, which the
             * ROM's division answers with the numerator. */
            int d = div_s32((frame - 0x23) * 0x19a, (int) anim_frames(actor) - 0x24);
            offset.x = add32(offset.x, d * 2);
            offset.y = add32(offset.y, d);
            offset.z = sub32(offset.z, d);
        }
    }
    func_ov003_02219668(&block, &offset);
    if (work->effect != -1) {
        Vec3 at = block_point(&block);
        func_0203f7d0(&at, &at);
        func_02091278(work->effect, &at, NULL, 0);
    }

    s16 values[3] = {0, 0, 0};
    if (anim_frame(actor) < 0x17 && actor->animation == 0x5c) {
        func_ov003_0222d83c((u8) player, values, &block, 0);
        return;
    }
    if (!is_local_player(actor)) {
        actor->next_state = func_02008258(actor, actor->state);
        if (work->step < 6 || work->step == 9) {
            if (State57Saved_Step(saved) == 6) {
                func_ov003_0222eabc((u8) player, State57Saved_Angle(saved));
                func_020109fc(actor, 0, 3, 3);
                work->step = 7;
            }
        }
    }
    s16 value = 100;
    if (actor->animation == 0x5c) {
        u32 frame = (u32) anim_frame(actor);
        if (frame <= 0x21) {
            value = (s16) ((frame - 0x17) * 10);
            if (value >= 100) {
                value = 100;
            }
        }
    }
    values[0] = values[1] = values[2] = value;

    switch (work->step) {
        case 1: {
            if (!func_0203e1c4()) {
                break;
            }
            work->step = 2;
            func_0203ee14(actor, actor->receiver);
            func_0200f27c(actor, 0x11);
            func_020a8164(actor->receiver, data_ov003_02238144);
            actor->receiver_unk_1E = (u8) kind;
            u16 item = (u16) (kind + 0x12b0);
            func_0203cbd0(&item);
            actor->link->requested = 1;
            func_0203ae98();
            if (func_0200f290(actor, 0x1a)) {
                func_02035638(0x3f);
                func_0200f268(actor, 0x1a);
            }
            func_02035624(0x12);
            func_02035684(0xc, 0, 0xe);
            func_020356c4(0xd, 0x39, 0x7f, 1);
            break;
        }
        case 2:
            if (actor->link == NULL || actor->link->open == 0) {
                break;
            }
            if (func_0203cc1c() && work->unk_0A == 0) {
                work->step = 8;
                actor->unk_81C = 0xd;
            } else {
                work->step = 3;
                actor->unk_81C = 8;
            }
            break;
        case 3:
            if (func_02099fe8() == -1) {
                int point[2] = {0, 0};
                if (func_02043368(0x10, point, NULL)) {
                    work->step = 4;
                    actor->unk_81C = 0;
                } else {
                    work->step = 5;
                    actor->unk_81C = 1;
                }
                return;
            }
            if (!link_closed(actor)) {
                break;
            }
            close_receiver(actor);
            func_0203e19c();
            FieldActor_RequestState58(actor, (char) kind, 0, 6, -1);
            func_0203b144();
            break;
        case 4:
            if (actor->unk_81C >= 0xf) {
                work->step = 5;
                break;
            }
            if (!link_closed(actor)) {
                break;
            }
            close_receiver(actor);
            FieldActor_RequestState58(actor, (char) kind, 1, 6, -1);
            func_0203b144();
            break;
        case 5: {
            if (!link_closed(actor)) {
                break;
            }
            if (work->effect != -1) {
                func_0209129c(work->effect);
            }
            int angle = (s16) sub32(func_020644cc(0x2aaa), 0x1555);
            func_ov003_0222eabc((u8) player, angle);
            State57Saved_SetAngle(saved, angle);
            close_receiver(actor);
            func_0203e19c();
            func_020109fc(actor, 0, 3, 3);
            work->step = 6;
            State57Saved_SetStep(saved, 6);
            func_0203b144();
            return;
        }
        case 6: {
            if (func_ov003_0222ea84((u8) player) != 3) {
                if (actor->head_pitch != 0 || actor->head_yaw != 0) {
                    func_02011404(&actor->head_pitch, 0, 0x400, 0x1770000, 0xc0000);
                    func_02011404(&actor->head_yaw, 0, 0x400, 0x1770000, 0xc0000);
                    return;
                }
                actor->next_state = func_02008258(actor, actor->state);
                switch (mode) {
                    case 2:
                        if (is_local_player(actor)) {
                            release_receiver(actor);
                            func_0203e19c();
                        }
                        func_0200d4e8(actor, 3, 1, -1);
                        return;
                    case 0:
                    case 3:
                        func_0200d4e8(actor, 3, 1, -1);
                        return;
                    case 1:
                        func_0200c9a8(actor, 3, 5, -1);
                        return;
                    default:
                        return;
                }
            }
            const Vec3 *target = func_ov003_0222e970((u8) player);
            Vec3 eye = actor->position;
            eye.y = add32(eye.y, 0x1b33);
            int yaw = Math_Atan2(sub32(target->x, eye.x), sub32(target->z, eye.z));
            int pitch = Math_Atan2(sub32(target->y, eye.y), func_020ea990(target, &eye));
            if (pitch >= 0x1800) {
                pitch = 0x1800;
            }
            yaw = (s16) (yaw - actor->yaw);
            func_02011404(&actor->head_pitch, pitch, 0x400, 0x1770000, 0xc0000);
            func_02011404(&actor->head_yaw, yaw, 0x400, 0x1770000, 0xc0000);
            return;
        }
        case 7: {
            int ready = func_ov003_0222ea84((u8) player);
            if (ready == 3 || ready == 0) {
                work->step = 6;
            }
            return;
        }
        case 8:
            if (!link_closed(actor)) {
                break;
            }
            close_receiver(actor);
            func_0203e19c();
            func_020094a0(actor, 0, (u8) kind, work->slot, 6, -1);
            return;
        default:
            break;
    }
    func_ov003_0222d83c((u8) player, values, &block, 0);
}
CLEAN_AS(func_ov003_022132bc, FieldActor_RunState57)

/* func_ov003_02213914: leaving state 0x57: the effect ends and the head faces ahead. */
void FieldActor_ExitState57(FieldActor *actor)
{
    if (actor->work.s57.effect != -1) {
        func_0209129c(actor->work.s57.effect);
    }
    actor->head_pitch = 0;
    actor->head_yaw = 0;
}
CLEAN_AS(func_ov003_02213914, FieldActor_ExitState57)

/* func_ov003_02213944: state 0x57's message handler: the state is asked for again with the
 * saved mode, slot and kind. */
void FieldActor_State57Message(FieldActor *actor, int arg)
{
    u8 step;
    u8 slot;
    u8 kind;
    u8 mode;
    /* QUIRK: the original reads the saved angle into a one-byte local, its second byte landing
     * past it in the stack frame; it is not used. */
    u16 angle;

    State57Saved_Get(&actor->saved.s57, &step, &slot, &kind, &mode, &angle);
    FieldActor_RequestState57(actor, mode, slot, kind, 6, (s16) arg);
}
CLEAN_AS(func_ov003_02213944, FieldActor_State57Message)

/* func_ov003_02213988: entering state 0x57 with the request's slot, kind and mode. Mode 0 (the
 * insect is caught here) starts animation 0x5c with pose 5 in hand at step 0; for the actor of
 * this console sound 0x12 starts and func_0208d07c and func_02079774 note the catch. Mode 3
 * waits at step 3 (0x81c = 8); the others wait at step 7, mode 2 taken for any mode while
 * animation 0x6c plays (which then gives way to animation 0). The actor of this console saves
 * the step, slot, kind and mode (as requested) with angle 0. */
void FieldActor_EnterState57(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 slot = request->payload[0];
    u8 kind = request->payload[1];
    u8 mode = request->payload[2];
    State57Work *work = &actor->work.s57;

    if (mode == 0) {
        func_020109a0(actor, 0x5c, 3, 0);
        func_0205eae0(actor->held, 5, 3, 1);
    }
    work->slot = slot;
    work->kind = kind;
    work->mode = mode;
    work->unk_04 = 0x39;
    work->unk_0A = (u8) func_0203cc1c();
    if (mode == 0) {
        if (is_local_player(actor)) {
            func_02035684(0x12, 0, 0);
            func_0208d07c((void *) (uintptr_t) func_0208b500());
            func_02079774(&actor->position);
        }
        work->step = 0;
    } else if (mode == 3) {
        work->step = 3;
        work->unk_04 = 0x3b;
        actor->unk_81C = 8;
    } else {
        if (actor->animation == 0x6c) {
            work->mode = 2;
            func_020109fc(actor, 0, 3, 3);
        }
        work->step = 7;
    }
    work->effect = -1;
    if (is_local_player(actor)) {
        State57Saved_Set(&actor->saved.s57, work->step, slot, kind, mode, 0);
    }
}
CLEAN_AS(func_ov003_02213988, FieldActor_EnterState57)

/* func_ov003_02213a80 */
int State57Saved_Angle(const State57Saved *saved)
{
    return func_020778f8(saved->angle);
}
CLEAN_AS(func_ov003_02213a80, State57Saved_Angle)

/* func_ov003_02213a8c */
int State57Saved_Step(const State57Saved *saved)
{
    return saved->step;
}
CLEAN_AS(func_ov003_02213a8c, State57Saved_Step)

/* func_ov003_02213a90 */
void State57Saved_Get(const State57Saved *saved, u8 *step, u8 *slot, u8 *kind, u8 *mode, u16 *angle)
{
    *step = saved->step;
    *slot = saved->slot;
    *kind = saved->kind;
    *mode = saved->mode;
    *angle = (u16) State57Saved_Angle(saved);
}
CLEAN_AS(func_ov003_02213a90, State57Saved_Get)

/* func_ov003_02213ab4 */
void State57Saved_SetAngle(State57Saved *saved, int angle)
{
    func_02077910(saved->angle, angle);
}
CLEAN_AS(func_ov003_02213ab4, State57Saved_SetAngle)

/* func_ov003_02213ac0 */
void State57Saved_SetStep(State57Saved *saved, int step)
{
    saved->step = (u8) step;
}
CLEAN_AS(func_ov003_02213ac0, State57Saved_SetStep)

/* func_ov003_02213ac4 */
void State57Saved_Set(State57Saved *saved, u8 step, u8 slot, u8 kind, u8 mode, s16 angle)
{
    saved->step = step;
    saved->slot = slot;
    saved->kind = kind;
    saved->mode = mode;
    State57Saved_SetAngle(saved, angle);
}
CLEAN_AS(func_ov003_02213ac4, State57Saved_Set)

/* func_ov003_02213ae4: asks for state 0x57 with a mode, a slot and a kind; whether it was
 * queued. */
void *FieldActor_RequestState57(FieldActor *actor, u8 mode, u8 slot, u8 kind, u32 priority, s16 arg)
{
    StateRequest request;
    open_request(&request, 0x57, (int) priority, arg);
    request.payload[0] = slot;
    request.payload[1] = kind;
    request.payload[2] = mode;
    return (void *) (intptr_t) send_request(actor, &request);
}
CLEAN_AS(func_ov003_02213ae4, FieldActor_RequestState57)

/* ---- State 0x56: a swing of the held item, animation 0x5b */

/* func_ov003_02213b28: state 0x56's update. The actor of this console faces the request's yaw
 * and sweeps; another player's actor only checks what the swing hits. Then both slow down,
 * end the swing when it is over and turn towards the point ahead, and the tip of what the actor
 * holds is noted. */
void FieldActor_UpdateState56(FieldActor *actor)
{
    if (is_local_player(actor)) {
        FieldActor_FaceState56(actor);
        FieldActor_SweepState56(actor);
        FieldActor_AnimateState56(actor);
        func_0201100c(actor);
    } else {
        FieldActor_SweepState56Remote(actor);
        FieldActor_AnimateState56(actor);
        if (func_0200f554(actor)) {
            func_0201100c(actor);
        }
    }
    func_02010d64(actor);
    FieldActor_SlowState56(actor);
    FieldActor_EndState56(actor);
    FieldActor_TurnState56(actor);

    Vec3 tip = actor->unk_62C;
    Vec3 out;
    func_0203f7d0(&out, &tip);
    actor->work.s56.tip = out;
}
CLEAN_AS(func_ov003_02213b28, FieldActor_UpdateState56)

/* func_ov003_02213bf0: once the animation is over or stopped: with something caught, state 0x57
 * is asked for (mode 0) with the slot and the kind func_ov003_0222e5fc gives for it when
 * func_ov003_0222e538 answers 0, or forgotten when it answers 1; slot 0xff asks with kind 0x30.
 * With nothing caught, once the held item's animation (at 0x9c in it) is over the state after
 * this one is noted and the actor of this console moves on (9). */
void FieldActor_EndState56(FieldActor *actor)
{
    if (!anim_done(actor) && actor->anim.speed != 0) {
        return;
    }
    State56Work *work = &actor->work.s56;
    if (work->caught) {
        u8 slot = work->slot;
        if (slot == 0xff) {
            FieldActor_RequestState57(actor, 0, slot, 0x30, 6, -1);
            return;
        }
        u8 answer = func_ov003_0222e538(slot, (u8) actor->player);
        if (answer == 0) {
            u8 kind = (u8) func_ov003_0222e5fc(slot);
            FieldActor_RequestState57(actor, 0, slot, kind, 6, -1);
        } else if (answer == 1) {
            work->caught = 0;
        }
        return;
    }
    const FrameCtrl *held_anim = (const FrameCtrl *) (const void *) (func_0205e8e4(actor->held) + 0x9c);
    if (func_02056f94(held_anim)) {
        actor->next_state = func_02008258(actor, actor->state);
        if (is_local_player(actor)) {
            func_0200d4e8(actor, 9, 1, -1);
        }
    }
}
CLEAN_AS(func_ov003_02213bf0, FieldActor_EndState56)

/* func_ov003_02213cd0: the speed at 0x98 slows by 0x171 a frame towards 0; effect 0x2b marks the
 * actor's stop. */
void FieldActor_SlowState56(FieldActor *actor)
{
    if (actor->unk_098 == 0) {
        return;
    }
    int speed = func_020113a4(actor->unk_098, 0, 0x171);
    func_0201107c(actor, &speed);
    if (actor->unk_098 != 0) {
        return;
    }
    func_020912d4(0x2b, &actor->position, &actor->yaw, 0);
}
CLEAN_AS(func_ov003_02213cd0, FieldActor_SlowState56)

/* func_ov003_02213d18: another player's swing, from frame 3 while it moves: unless it hits at
 * frame 4, the line from the swing's base to its tip is traced. */
void FieldActor_SweepState56Remote(FieldActor *actor)
{
    if (actor->anim.speed == 0) {
        return;
    }
    if (anim_frame(actor) < 3) {
        return;
    }
    if (FieldActor_HitState56(actor)) {
        return;
    }
    Vec3 at = actor->unk_68C;
    func_0203f7d0(&at, &at);
    Vec3 sweep = at;
    Vec3 base;
    Vec3 tip;
    FieldActor_State56Points(actor, &sweep, &base, &tip);
    Vec3 from = at;
    FieldActor_TraceState56(actor, &from, &base, &tip);
}
CLEAN_AS(func_ov003_02213d18, FieldActor_SweepState56Remote)

/* Stops the swing: flag 9, sound 0x846, the animation stops and the held item takes pose 4. */
static void stop_state56(FieldActor *actor)
{
    func_0200f27c(actor, 9);
    func_0200f328(actor, 0x846);
    actor->anim.speed = 0;
    func_0205eae0(actor->held, 4, 3, 1);
}

/* func_ov003_02213da0: tests the segment between `to` and `at` (func_020311bc). When it hits, the
 * swing stops, and at frame 5 the tile at `to` goes to func_0204489c; that counts as a hit
 * before frame 5. Otherwise at frame 5 another player's actor takes `from` as `to` and stops
 * when the ground there (func_02034270) has 0 at 0x30; failing that, and always for the actor
 * of this console, effect 0xb marks `from`, flag 9 is set and the held item takes pose 4
 * without the stop. Whether a hit counted. */
int FieldActor_TraceState56(FieldActor *actor, Vec3 *at, Vec3 *from, Vec3 *to)
{
    SegmentTest test;
    BOOL hit;

    func_02032adc(&test);
    if (func_020311bc(&test, to, at, 0x1b)) {
        hit = TRUE;
    } else {
        if (!anim_passed(actor, 5)) {
            func_02032acc(&test);
            return 0;
        }
        hit = FALSE;
        if (!is_local_player(actor)) {
            func_02034270(&test.ground, from, 0, 0);
            if (test.ground.unk_30 == 0) {
                copy_point(to, from);
                hit = TRUE;
            }
            func_0203423c(&test.ground);
        }
    }
    if (hit) {
        stop_state56(actor);
        if (anim_passed(actor, 5)) {
            int x = 0;
            int z = 0;
            func_0204f818(&x, &z, to);
            int tile[2] = {x, z};
            func_0204489c(tile);
        }
        if (anim_frame(actor) <= 4) {
            func_02032acc(&test);
            return 1;
        }
    } else {
        func_020912d4(0xb, from, NULL, 0);
        func_0200f27c(actor, 9);
        func_0205eae0(actor->held, 4, 3, 1);
    }
    func_02032acc(&test);
    return 0;
}
CLEAN_AS(func_ov003_02213da0, FieldActor_TraceState56)

/* func_ov003_02213ec0: at frame 4 the swing stops when FieldActor_CheckOther meets an object or
 * the ground 2.85 ahead is high (func_020310d0 at least 0x400); whether it stopped. */
int FieldActor_HitState56(FieldActor *actor)
{
    if (!anim_passed(actor, 4)) {
        return 0;
    }
    if (!FieldActor_CheckOther(actor)) {
        Vec3 ahead;
        int surface;
        func_0200fa1c(&ahead, actor, &actor->position, &actor->yaw, &data_ov003_02238114);
        if (func_020310d0(&ahead, &surface, 0x19) < 0x400) {
            return 0;
        }
    }
    stop_state56(actor);
    return 1;
}
CLEAN_AS(func_ov003_02213ec0, FieldActor_HitState56)

/* func_ov003_02213f74: whether a swing stopped at `hit` still reaches the insect at `insect`.
 * Always on map objects 0x1b and 0x89 at `hit`. With the insect's flag set, when the insect's z
 * lies between the actor's and `hit`'s (the actor's side included). Otherwise by the directions
 * from the actor, each folded to 0-0x8000 (func_020e8b4c): equal ones compare by z as above;
 * the insect's above 0x4000 with `hit`'s beyond it, or `hit`'s below 0x4000 and not beyond the
 * insect's, reach; else the insect is reached when the squared distance to `hit` less its part
 * along the insect's direction is at least 0x900000. */
int FieldActor_State56Reaches(FieldActor *actor, const Vec3 *hit, const Vec3 *insect, const u8 *insect_flag)
{
    Vec3 here = actor->position;

    const u16 *object = func_0204f5a8(data_021c80bc, hit, 0);
    if (object != NULL && (*object == 0x1b || *object == 0x89)) {
        return 1;
    }
    if (*insect_flag == 0) {
        int a1 = Math_Atan2(sub32(insect->x, here.x), sub32(insect->z, here.z));
        int a2 = Math_Atan2(sub32(hit->x, here.x), sub32(hit->z, here.z));
        /* QUIRK: a fold of 0x8000 is kept as an s16, -0x8000. */
        a1 = (s16) Math_AbsDiff16(a1, 0);
        a2 = (s16) Math_AbsDiff16(a2, 0);
        if (a1 != a2) {
            if ((a1 >= 0x4000 && a2 > a1) || (a2 < 0x4000 && a2 <= a1)) {
                return 1;
            }
            int dx = sub32(hit->x, here.x);
            int dz = sub32(hit->z, here.z);
            int d = (int) ((u32) dx * (u32) dx + (u32) dz * (u32) dz);
            s16 c = FX_SinCosTable_[((u16) (a1 - a2) >> 4) * 2 + 1];
            int t = FX_MulFunc(d, c);
            t = FX_MulFunc(t, c);
            return sub32(d, t) >= 0x900000;
        }
    }
    int z = insect->z;
    return (here.z >= z && z > hit->z) || (here.z <= z && z < hit->z);
}
CLEAN_AS(func_ov003_02213f74, FieldActor_State56Reaches)

/* func_ov003_022140a8: what the swing meets. At frame 4: an object FieldActor_CheckOther meets
 * stops the swing and gives 3 for verdict 4, else 1 with an insect and 2 without; high ground
 * (func_020310d0 at least 0x400) at the tile of the point 2.85 ahead stops it and gives 1 when
 * there is an insect the swing still reaches, else 2. At frame 3, with an insect, high ground
 * at the tile 2.0 ahead gives the same 1 or 2 without stopping. Otherwise 0. */
int FieldActor_ClassifyState56(FieldActor *actor, const u8 *has_insect, const Vec3 *insect, const u8 *insect_flag)
{
    Vec3 ahead;
    int surface;

    if (anim_passed(actor, 4)) {
        if (FieldActor_CheckOther(actor)) {
            stop_state56(actor);
            if (actor->other_result == 4) {
                return 3;
            }
            return *has_insect ? 1 : 2;
        }
        func_0200fa1c(&ahead, actor, &actor->position, &actor->yaw, &data_ov003_0223811c);
        func_0204f7e0(&ahead, &ahead);
        if (func_020310d0(&ahead, &surface, 0x19) >= 0x400) {
            stop_state56(actor);
            if (*has_insect && FieldActor_State56Reaches(actor, &ahead, insect, insect_flag)) {
                return 1;
            }
            return 2;
        }
    } else if (anim_passed(actor, 3)) {
        if (*has_insect) {
            func_0200fa1c(&ahead, actor, &actor->position, &actor->yaw, &data_ov003_02238120);
            func_0204f7e0(&ahead, &ahead);
            if (func_020310d0(&ahead, &surface, 0x19) >= 0x400) {
                return FieldActor_State56Reaches(actor, &ahead, insect, insect_flag) ? 1 : 2;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_022140a8, FieldActor_ClassifyState56)

/* func_ov003_02214200: the points of the swing by the frame, from the actor's position and yaw:
 * `base` starts at the position and `sweep` is the caller's. Frame 3 plays sound 0x845, raises
 * `sweep` by 1.87 and puts `base` 1.9 ahead and 2.3 up; frame 4 puts `sweep` there and `base`
 * 2.65 ahead; frame 5 puts `sweep` 2.65 ahead and `base` 2.5 ahead and 0.4 down. `tip` is the
 * tip of what the actor holds (func_0203f7d0). */
void FieldActor_State56Points(FieldActor *actor, Vec3 *sweep, Vec3 *base, Vec3 *tip)
{
    const Vec3 *position = &actor->position;
    copy_point(base, position);

    int index = ((u16) actor->yaw >> 4) * 2;
    fx32 sin = FX_SinCosTable_[index];
    fx32 cos = FX_SinCosTable_[index + 1];

    switch (anim_frame(actor)) {
        case 3:
            func_0200f328(actor, 0x845);
            sweep->y = add32(sweep->y, 0x1dd3);
            base->x = add32(base->x, FX_MulFunc(sin, 0x1e66));
            base->y = add32(base->y, 0x24cd);
            base->z = add32(base->z, FX_MulFunc(cos, 0x1e66));
            break;
        case 4:
            copy_point(sweep, position);
            sweep->x = add32(sweep->x, FX_MulFunc(sin, 0x1e66));
            sweep->y = add32(sweep->y, 0x24cd);
            sweep->z = add32(sweep->z, FX_MulFunc(cos, 0x1e66));
            base->x = add32(base->x, FX_MulFunc(sin, 0x2a66));
            base->z = add32(base->z, FX_MulFunc(cos, 0x2a66));
            break;
        case 5:
            copy_point(sweep, position);
            sweep->x = add32(sweep->x, FX_MulFunc(sin, 0x2a66));
            sweep->z = add32(sweep->z, FX_MulFunc(cos, 0x2a66));
            base->x = add32(base->x, FX_MulFunc(sin, 0x2800));
            base->y = sub32(base->y, 0x666);
            base->z = add32(base->z, FX_MulFunc(cos, 0x2800));
            break;
        default:
            break;
    }
    Vec3 at = actor->unk_62C;
    func_0203f7d0(&at, &at);
    copy_point(tip, &at);
}
CLEAN_AS(func_ov003_02214200, FieldActor_State56Points)

/* func_ov003_02214384: the swing of the actor of this console, from frame 3 while it moves and
 * until it is over. Before frame 6, until something is caught, func_020899a8 looks for an
 * insect along the sweep (radius 0xa00 with the held item 0x1376, else 0xd1f) and gives its
 * slot; its point (func_ov003_0222f458) moves 0x100 in z when func_ov003_0222f490 flags it.
 * Then by FieldActor_ClassifyState56: 1 catches the insect if func_ov003_0222e3a4 lets it, 2
 * ends here, 3 catches slot 0xff unless something is caught; 0 traces the line, and with an
 * insect found catches it as above when the line hit nothing or the insect lies more than a
 * quarter turn from the tip's direction (func_020e8b4c). A catch plays sound 0x847. */
void FieldActor_SweepState56(FieldActor *actor)
{
    if (actor->anim.speed == 0) {
        return;
    }
    if (anim_done(actor)) {
        return;
    }
    if (anim_frame(actor) < 3) {
        return;
    }

    u8 has_insect = 0;
    u8 insect_flag = 0;
    u8 slot = 0;
    Vec3 insect = {0, 0, 0};

    Vec3 at = actor->unk_68C;
    func_0203f7d0(&at, &at);
    Vec3 sweep = at;
    Vec3 base;
    Vec3 tip;
    FieldActor_State56Points(actor, &sweep, &base, &tip);

    State56Work *work = &actor->work.s56;
    if (work->caught == 0 && anim_frame(actor) < 6) {
        u16 item;
        func_020110c4(&item, actor);
        int radius = item == 0x1376 ? 0xa00 : 0xd1f;
        if (func_020899a8(&sweep, &base, radius, &slot, 0)) {
            has_insect = 1;
            func_ov003_0222f458(&insect, slot);
            insect_flag = (u8) func_ov003_0222f490(slot);
            if (insect_flag) {
                insect.z = add32(insect.z, 0x100);
            }
        }
    }

    switch (FieldActor_ClassifyState56(actor, &has_insect, &insect, &insect_flag)) {
        case 1:
            break;
        case 2:
            return;
        case 3:
            if (work->caught) {
                return;
            }
            work->caught = 1;
            work->slot = 0xff;
            func_0200f328(actor, 0x847);
            return;
        default: {
            Vec3 from = at;
            int traced = FieldActor_TraceState56(actor, &from, &base, &tip);
            if (!has_insect) {
                return;
            }
            int angle = 0x7fff;
            if (traced) {
                angle = Math_Atan2(sub32(insect.x, tip.x), sub32(insect.z, tip.z));
            }
            if (Math_AbsDiff16(angle, 0) <= 0x4000) {
                return;
            }
            break;
        }
    }
    if (func_ov003_0222e3a4(slot)) {
        work->caught = 1;
        work->slot = slot;
        func_0200f328(actor, 0x847);
    }
}
CLEAN_AS(func_ov003_02214384, FieldActor_SweepState56)

/* func_ov003_02214568: the actor turns towards the point ahead of it. */
void FieldActor_TurnState56(FieldActor *actor)
{
    Vec3 ahead;
    func_0200fa6c(&ahead, actor);
    func_02010d88(actor, &ahead, 0x99a, 0x1000);
    func_02089fc8(actor->unk_1C4);
}
CLEAN_AS(func_ov003_02214568, FieldActor_TurnState56)

/* func_ov003_022145a0: the actor faces the request's yaw. */
void FieldActor_FaceState56(FieldActor *actor)
{
    func_0200fb34(actor, actor->work.s56.yaw);
}
CLEAN_AS(func_ov003_022145a0, FieldActor_FaceState56)

/* func_ov003_022145b0: the animation steps; sound 0x848 when it has just ended. */
void FieldActor_AnimateState56(FieldActor *actor)
{
    BOOL was_done = anim_done(actor);
    func_02010f5c(actor);
    if (!was_done && anim_done(actor)) {
        func_0200f328(actor, 0x848);
    }
}
CLEAN_AS(func_ov003_022145b0, FieldActor_AnimateState56)

/* func_ov003_022145f8: state 0x56's message handler: the state is asked for again. */
void FieldActor_State56Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState56(actor, 6, arg);
}
CLEAN_AS(func_ov003_022145f8, FieldActor_State56Message)

/* func_ov003_02214604: entering state 0x56 with the request's yaw: nothing caught, animation
 * 0x5b with pose 3 in hand. */
void FieldActor_EnterState56(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    State56Work *work = &actor->work.s56;
    s16 yaw;
    memcpy(&yaw, request->payload, sizeof(yaw));

    work->caught = 0;
    work->yaw = yaw;
    work->slot = 0xff;
    func_020109a0(actor, 0x5b, 3, 0);
    func_0205eae0(actor->held, 3, 3, 0);
}
CLEAN_AS(func_ov003_02214604, FieldActor_EnterState56)

/* func_ov003_02214644: asks for state 0x56 with a yaw: towards unk_14C from where the frame
 * began when unk_144 is 2, else the actor's own; whether it was queued. */
int FieldActor_RequestState56(FieldActor *actor, int priority, int arg)
{
    StateRequest request;
    s16 yaw;

    open_request(&request, 0x56, priority, arg);
    if (actor->unk_144 == 2) {
        yaw = Math_Atan2(sub32(actor->unk_14C.x, actor->start_position.x), sub32(actor->unk_14C.z, actor->start_position.z));
    } else {
        yaw = actor->yaw;
    }
    memcpy(request.payload, &yaw, sizeof(yaw));
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02214644, FieldActor_RequestState56)

/* ---- State 0x55: the fish caught is put away (animation 0x5a) */

/* func_ov003_022146bc: state 0x55's update. */
void FieldActor_UpdateState55(FieldActor *actor)
{
    func_02010f5c(actor);
    func_0200f554(actor);
    func_02010d64(actor);
    if (is_local_player(actor)) {
        FieldActor_RunState55(actor);
    } else {
        FieldActor_EndState55Remote(actor);
    }
}
CLEAN_AS(func_ov003_022146bc, FieldActor_UpdateState55)

/* func_ov003_022146fc: another player's actor: at the animation's end the state after this one
 * is noted and animation 0x6c starts with pose 0x13 in hand. */
void FieldActor_EndState55Remote(FieldActor *actor)
{
    if (anim_done(actor)) {
        actor->next_state = func_02008258(actor, actor->state);
        func_020109fc(actor, 0x6c, 6, 6);
        func_0205eae0(actor->held, 0x13, 6, 0);
    }
}
CLEAN_AS(func_ov003_022146fc, FieldActor_EndState55Remote)

/* The fish placed at the hand point with its own scale (func_ov003_0222aaa0). */
static void place_fish_default(HookedFish *fish, const Vec3 *hand, Vec3 *scale)
{
    func_ov003_0222aaa0(scale, fish->kind);
    Vec3 at = *hand;
    Vec3 sized = *scale;
    func_ov003_0222aa50(fish, &at, &sized);
}

/* func_ov003_0221474c: state 0x55 for the actor of this console, by the work's step. The fish
 * hangs at the block's point; during the first six frames of animation 0x5a it shrinks from its
 * size (the table's percent of the fish's row, or 1.0 with no fish) to 0, when
 * func_ov003_0222a8a8 runs.
 *   Step 0: at the animation's end the actor moves on (6), gives the fish's item to
 *     func_0209a110, and func_02060460 lets the fish go.
 *   Step 1: after animation 0x5a, animation 0x6c with pose 0x13. The word at 0x81c: at 5 it
 *     becomes 6 once func_0206f6f8 accepts the item; at 6 it becomes 0xf once func_0206fbc0
 *     says so, and when func_0206fc6c then says so the fish is let go (func_020604fc), the
 *     receiver is released and the actor moves on: to state 0x8f when func_0206f6a4 gives a
 *     fish item (0x12e8-0x131f), else (6) at step 2. From 0xf the items 0x1320-0x1322 go to
 *     step 3; others get their own scale back and state 0x8f with step 2 saved. Then
 *     func_02060448 and the receiver is released.
 *   Step 2: the actor moves on (6).
 *   Step 3: waits for func_02043554 to give a value other than -1, then step 2. */
void FieldActor_RunState55(FieldActor *actor)
{
    HookedFish *fish = func_020604f8(held_line(actor));
    int size = 0;
    if (actor->animation == 0x5a) {
        int frame = anim_frame(actor);
        if (frame < 6) {
            if (fish != NULL) {
                int full = (data_ov003_0223c026[fish->size * 0x14] << 12) / 100;
                size = (s16) (full - full * frame / 6);
            } else {
                size = (s16) (0x1000 - 0x2ab * frame);
            }
        }
    }
    Vec3 scale = {size, size, size};
    FieldActorBlock48 block = actor->unk_698;
    func_ov003_02219668(&block, NULL);
    Vec3 hand = block_point(&block);

    u16 item = ITEM_NONE;
    if (fish != NULL) {
        func_0203f7d0(&hand, &hand);
        Vec3 at = hand;
        Vec3 sized = scale;
        func_ov003_0222aa50(fish, &at, &sized);
        item = (u16) (fish->kind + 0x12e8);
        if (size == 0) {
            func_ov003_0222a8a8(actor->player);
        }
    }

    u8 *step = &actor->work.step;
    switch (*step) {
        case 0:
            if (!anim_done(actor)) {
                break;
            }
            actor->next_state = func_02008258(actor, actor->state);
            func_0200d4e8(actor, 6, 1, -1);
            if (is_local_player(actor)) {
                u16 code = item;
                func_0209a110(&code);
            }
            func_02060460(held_line(actor));
            break;
        case 1:
            if (actor->animation == 0x5a) {
                if (!anim_done(actor)) {
                    break;
                }
                func_020109fc(actor, 0x6c, 6, 6);
                func_0205eae0(actor->held, 0x13, 6, 0);
            }
            if (is_local_player(actor)) {
                if (actor->unk_81C == 5) {
                    if (func_0206f6f8(item, fish)) {
                        actor->unk_81C = 6;
                    }
                    break;
                }
                if (actor->unk_81C == 6) {
                    if (!func_0206fbc0()) {
                        break;
                    }
                    actor->unk_81C = 0xf;
                    if (func_0206fc6c()) {
                        func_020604fc(held_line(actor), 0);
                        release_receiver(actor);
                        func_0203e19c();
                        u16 got = func_0206f6a4();
                        actor->next_state = func_02008258(actor, actor->state);
                        if (got >= 0x12e8 && got <= 0x131f) {
                            FieldActor_RequestLook(actor, &data_ov003_02238104, 0, 6, -1);
                            break;
                        }
                        func_0200d4e8(actor, 6, 1, -1);
                        *step = 2;
                        break;
                    }
                } else if (actor->unk_81C < 0xf) {
                    break;
                }
                if (is_item_1320(item)) {
                    *step = 3;
                    if (actor->unk_810 == -1) {
                        actor->unk_810 = func_02043554(actor->player, item);
                        if (actor->unk_810 != -1) {
                            *step = 2;
                        }
                    }
                } else {
                    if (fish != NULL) {
                        place_fish_default(fish, &hand, &scale);
                    }
                    FieldActor_RequestLook(actor, &data_ov003_02238108, 0, 6, -1);
                    State55Saved_SetStep(&actor->saved.step55, 2);
                }
                func_02060448(held_line(actor));
                release_receiver(actor);
                func_0203e19c();
                break;
            }
            actor->next_state = func_02008258(actor, actor->state);
            if (State55Saved_Step(&actor->saved.step55) == 2) {
                if (fish != NULL) {
                    place_fish_default(fish, &hand, &scale);
                }
                func_02060448(held_line(actor));
                *step = 2;
                func_020109fc(actor, 0, 6, 6);
            }
            break;
        case 2:
            actor->next_state = func_02008258(actor, actor->state);
            func_0200d4e8(actor, 6, 1, -1);
            break;
        case 3:
            if (actor->unk_810 == -1) {
                actor->unk_810 = func_02043554(actor->player, item);
                if (actor->unk_810 != -1) {
                    *step = 2;
                }
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_0221474c, FieldActor_RunState55)

/* func_ov003_02214ba0: state 0x55's message handler: the state is asked for again at the saved
 * step. */
void FieldActor_State55Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState55(actor, (char) State55Saved_Step(&actor->saved.step55), 6, arg);
}
CLEAN_AS(func_ov003_02214ba0, FieldActor_State55Message)

/* func_ov003_02214bc8: entering state 0x55 at the request's step (saved too): animation 0x5a and
 * sound 0x4f. */
void FieldActor_EnterState55(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 step = request->payload[0];
    actor->work.step = step;
    State55Saved_SetStep(&actor->saved.step55, step);
    func_020109a0(actor, 0x5a, 3, 3);
    func_0200f328(actor, 0x4f);
}
CLEAN_AS(func_ov003_02214bc8, FieldActor_EnterState55)

/* func_ov003_02214bfc */
int State55Saved_Step(const u8 *saved)
{
    return *saved;
}
CLEAN_AS(func_ov003_02214bfc, State55Saved_Step)

/* func_ov003_02214c00 */
void State55Saved_SetStep(u8 *saved, int step)
{
    *saved = (u8) step;
}
CLEAN_AS(func_ov003_02214c00, State55Saved_SetStep)

/* func_ov003_02214c04: asks for state 0x55 at a step; whether it was queued. */
int FieldActor_RequestState55(FieldActor *actor, char step, int priority, int arg)
{
    StateRequest request;
    open_request(&request, 0x55, priority, arg);
    request.payload[0] = (u8) step;
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02214c04, FieldActor_RequestState55)

/* ---- State 0x54: the fish caught is shown (animation 0x59) */

/* func_ov003_02214c40: state 0x54's update: func_0200ee40 runs between func_02010f5c and the
 * others, with the points and blocks it would change kept. Another player's actor notes the
 * state after this one and holds still. */
void FieldActor_UpdateState54(FieldActor *actor)
{
    KeptAcrossEE40 kept;

    func_02010f5c(actor);
    keep_across_ee40(actor, &kept);
    func_0200ee40(actor);
    func_0200f554(actor);
    func_02010d64(actor);
    if (is_local_player(actor)) {
        FieldActor_RunState54(actor);
    } else {
        actor->next_state = func_02008258(actor, actor->state);
        func_0200faf0(actor, 0x400);
    }
    restore_after_ee40(actor, &kept);
}
CLEAN_AS(func_ov003_02214c40, FieldActor_UpdateState54)

/* func_ov003_02214d2c: state 0x54 for the actor of this console. The actor holds still; the
 * fish hangs, at its own scale, at the block's point moved by an offset that grows over the end
 * of the animation (from frame 0x10; fixed when the mode is not 0). Frame 3 of animation 0x59
 * plays func_0203ae98. Before frame 0x11, in mode 0, steps below 5 wait.
 *   Step 0: once func_0203e1c4 says so the receiver is registered under "obj_etc_getfish" with
 *     the item 0x12e8 + kind (what func_0203cbd0 leaves of it becomes `item`), its link is
 *     asked for, the sounds are set, and step 1 follows at once.
 *   Step 1: once the link is open: step 5 (0x81c = 0xe) when func_0203cc38 says so and it did
 *     not on entering, else step 2 (0x81c = 8).
 *   Step 2: with func_02099fe8 at -1, step 3 when func_02043368 accepts (0x81c = 4 for the items
 *     0x1320-0x1322, else 0), else step 4 (0x81c = 1). Otherwise once the link closes the
 *     receiver is released and state 0x55 is asked for at step 0.
 *   Step 3: from 0x81c = 0xf on: the items 0x1320-0x1322 go to step 6 and on as there, others to
 *     step 4. Before, once the link closes the receiver is released and state 0x55 is asked for
 *     at step 1.
 *   Step 4: once the link closes func_02060448 runs, the receiver is released, the state after
 *     this one is noted and state 0x8f asked for.
 *   Step 5: once the link closes the receiver is released and func_020094a0 runs.
 *   Step 6: waits for func_02043554 to give a value other than -1, then step 4. */
void FieldActor_RunState54(FieldActor *actor)
{
    State54Work *work = &actor->work.s54;

    func_0200faf0(actor, 0x400);
    HookedFish *fish = func_020604f8(held_line(actor));
    if (fish != NULL) {
        FieldActorBlock48 block = actor->unk_698;
        Vec3 scale;
        func_ov003_0222aaa0(&scale, fish->kind);
        Vec3 offset = {0x4cd, 0, 0};
        int frame = anim_frame(actor);
        if (work->mode != 0) {
            offset.x = 0x800;
            offset.y = 0x19a;
            offset.z = -0x19a;
        } else if (frame >= 0x10) {
            /* QUIRK: on the last frame of a 0x10-frame animation the divisor is 0, which the
             * ROM's division answers with the numerator. */
            int d = div_s32((frame - 0xf) * 0x19a, (int) anim_frames(actor) - 0x10);
            offset.x = add32(offset.x, d * 2);
            offset.y = add32(offset.y, d);
            offset.z = sub32(offset.z, d);
        }
        func_ov003_02219668(&block, &offset);
        Vec3 at = block_point(&block);
        func_0203f7d0(&at, &at);
        Vec3 sized = scale;
        func_ov003_0222aa50(fish, &at, &sized);
    }

    if (actor->animation == 0x59 && anim_passed(actor, 3)) {
        func_0203ae98();
    }
    if (anim_frame(actor) < 0x11 && work->step < 5 && work->mode == 0) {
        return;
    }

    switch (work->step) {
        case 0:
            if (func_0203e1c4()) {
                work->step = 1;
                func_0203ee14(actor, actor->receiver);
                func_0200f27c(actor, 0x11);
                func_020a8164(actor->receiver, data_ov003_02238158);
                u8 kind = work->kind;
                actor->receiver_unk_1E = kind;
                u16 code = (u16) (kind + 0x12e8);
                func_0203cbd0(&code);
                actor->unk_822 = code;
                actor->item = actor->unk_822;
                actor->link->requested = 1;
                func_02035624(0x12);
                func_02035684(0xc, 0, 4);
                func_020356c4(0xd, 0x39, 0x7f, 1);
            }
            /* fall through */
        case 1:
            if (actor->link == NULL || actor->link->open == 0) {
                break;
            }
            if (func_0203cc38() && work->unk_05 == 0) {
                work->step = 5;
                actor->unk_81C = 0xe;
                break;
            }
            work->step = 2;
            actor->unk_81C = 8;
            break;
        case 2:
            if (func_02099fe8() == -1) {
                int point[2] = {0, 0};
                if (func_02043368(0x10, point, NULL)) {
                    work->step = 3;
                    actor->unk_81C = is_item_1320(actor->item) ? 4 : 0;
                    break;
                }
                work->step = 4;
                actor->unk_81C = 1;
                break;
            }
            if (!link_closed(actor)) {
                break;
            }
            close_receiver(actor);
            func_0203e19c();
            FieldActor_RequestState55(actor, 0, 6, -1);
            func_0203b144();
            break;
        case 3:
            if (actor->unk_81C >= 0xf) {
                if (!is_item_1320(actor->item)) {
                    work->step = 4;
                    break;
                }
                work->step = 6;
                if (actor->unk_810 != -1) {
                    break;
                }
                actor->unk_810 = func_02043554(actor->player, actor->item);
                if (actor->unk_810 != -1) {
                    work->step = 4;
                }
                break;
            }
            if (!link_closed(actor)) {
                break;
            }
            close_receiver(actor);
            FieldActor_RequestState55(actor, 1, 6, -1);
            func_0203b144();
            break;
        case 4:
            if (!link_closed(actor)) {
                break;
            }
            func_02060448(held_line(actor));
            close_receiver(actor);
            func_0203e19c();
            actor->next_state = func_02008258(actor, actor->state);
            FieldActor_RequestLook(actor, &data_ov003_02238100, 0, 6, -1);
            func_0203b144();
            break;
        case 5:
            if (!link_closed(actor)) {
                break;
            }
            close_receiver(actor);
            func_0203e19c();
            func_020094a0(actor, 1, work->kind, 0, 6, -1);
            break;
        case 6:
            if (actor->unk_810 != -1) {
                break;
            }
            actor->unk_810 = func_02043554(actor->player, actor->item);
            if (actor->unk_810 != -1) {
                work->step = 4;
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_02214d2c, FieldActor_RunState54)

/* func_ov003_02215164: state 0x54's message handler: the state is asked for again with the saved
 * mode. */
void FieldActor_State54Message(FieldActor *actor, int arg)
{
    u8 mode;
    State54Saved_Get(&actor->saved.mode54, &mode);
    FieldActor_RequestState54(actor, (char) mode, 6, arg);
}
CLEAN_AS(func_ov003_02215164, FieldActor_State54Message)

/* func_ov003_02215190: entering state 0x54 with the request's mode (saved too). Mode 0 starts at
 * step 0 with animation 0x59 and pose 0x1c in hand; the actor of this console takes the hooked
 * fish's kind, and for kinds below 0x38 func_02079798 and func_0208d09c note the catch. Other
 * modes start at step 2 (0x81c = 8).
 * REQUIRES: in mode 0 a fish hangs from the held item for the actor of this console (the
 * original reads its kind without a check). */
void FieldActor_EnterState54(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 mode = request->payload[0];
    State54Work *work = &actor->work.s54;

    work->mode = mode;
    work->unk_00 = 0x39;
    work->unk_05 = (u8) func_0203cc38();
    if (mode == 0) {
        if (is_local_player(actor)) {
            s8 kind = func_020604f8(held_line(actor))->kind;
            work->kind = (u8) kind;
            if (kind < 0x38) {
                func_02079798(&actor->position);
                func_0208d09c((void *) (uintptr_t) func_0208b500());
            }
        }
        work->step = 0;
        func_020109a0(actor, 0x59, 3, 0);
        func_0205eae0(actor->held, 0x1c, 3, 1);
    } else {
        work->step = 2;
        work->unk_00 = 0x3a;
        actor->unk_81C = 8;
    }
    State54Saved_Set(&actor->saved.mode54, mode);
}
CLEAN_AS(func_ov003_02215190, FieldActor_EnterState54)

/* func_ov003_02215234 */
void State54Saved_Get(const u8 *saved, u8 *mode)
{
    *mode = *saved;
}
CLEAN_AS(func_ov003_02215234, State54Saved_Get)

/* func_ov003_0221523c */
void State54Saved_Set(u8 *saved, int mode)
{
    *saved = (u8) mode;
}
CLEAN_AS(func_ov003_0221523c, State54Saved_Set)

/* func_ov003_02215240: asks for state 0x54 with a mode; whether it was queued. */
int FieldActor_RequestState54(FieldActor *actor, char mode, int priority, int arg)
{
    StateRequest request;
    open_request(&request, 0x54, priority, arg);
    request.payload[0] = (u8) mode;
    return send_request(actor, &request);
}
CLEAN_AS(func_ov003_02215240, FieldActor_RequestState54)

/* ---- State 0x53: animation 0x58 */

/* func_ov003_0221527c: state 0x53's update. */
void FieldActor_UpdateState53(FieldActor *actor)
{
    func_02010f5c(actor);
    func_0200f554(actor);
    func_02010d64(actor);
    if (is_local_player(actor)) {
        FieldActor_EndState53(actor);
    }
}
CLEAN_AS(func_ov003_0221527c, FieldActor_UpdateState53)

/* func_ov003_022152b4: at the animation's end, once func_02060474 says so of what hangs from the
 * held item, state 0x54 is asked for (mode 0). */
void FieldActor_EndState53(FieldActor *actor)
{
    if (anim_done(actor) && func_02060474(held_line(actor))) {
        FieldActor_RequestState54(actor, 0, 6, -1);
    }
}
CLEAN_AS(func_ov003_022152b4, FieldActor_EndState53)

/* func_ov003_022152ec: state 0x53's message handler: the state is asked for again. */
void FieldActor_State53Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState53(actor, 6, arg);
}
CLEAN_AS(func_ov003_022152ec, FieldActor_State53Message)

/* func_ov003_022152f8: entering state 0x53: animation 0x58 with pose 0x1b in hand, sounds 0x84c
 * and 0x84e, and unk_5D0 kept at unk_8C4. */
void FieldActor_EnterState53(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    func_020109a0(actor, 0x58, 3, 0);
    func_0205eae0(actor->held, 0x1b, 3, 1);
    func_0200f328(actor, 0x84c);
    func_0200f328(actor, 0x84e);
    copy_point(&actor->unk_8C4, &actor->unk_5D0);
}
CLEAN_AS(func_ov003_022152f8, FieldActor_EnterState53)

/* func_ov003_0221535c: asks for state 0x53; whether it was queued. */
void *FieldActor_RequestState53(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x53, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_0221535c, FieldActor_RequestState53)

/* ---- State 0x52: animation 0x57 */

/* func_ov003_02215394: state 0x52's update. The speed at 0x98 slows by 0xc5 a frame towards 0,
 * as a magnitude, and is stored negated. */
void FieldActor_UpdateState52(FieldActor *actor)
{
    func_02010f5c(actor);
    if (func_0200f554(actor)) {
        func_0201100c(actor);
    }
    func_02010d64(actor);
    int speed = sub32(0, func_020113a4(abs32(actor->unk_098), 0, 0xc5));
    func_0201107c(actor, &speed);
    FieldActor_EndState52(actor);
}
CLEAN_AS(func_ov003_02215394, FieldActor_UpdateState52)

/* func_ov003_022153e8: at the animation's end the actor of this console runs func_0203b144, the
 * actor moves on and the held item takes pose 0x13. */
void FieldActor_EndState52(FieldActor *actor)
{
    if (!anim_done(actor)) {
        return;
    }
    if (is_local_player(actor)) {
        func_0203b144();
    }
    move_on(actor);
    func_0205eae0(actor->held, 0x13, 3, 0);
}
CLEAN_AS(func_ov003_022153e8, FieldActor_EndState52)

/* func_ov003_02215454: state 0x52's message handler: the state is asked for again. */
void FieldActor_State52Message(FieldActor *actor, int arg)
{
    FieldActor_RequestState52(actor, 6, arg);
}
CLEAN_AS(func_ov003_02215454, FieldActor_State52Message)

/* func_ov003_02215460: entering state 0x52: the speed at 0x98 starts at -1049 (the word at
 * 0x0223812c), animation 0x57 with pose 0x1a in hand. */
void FieldActor_EnterState52(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    func_0201107c(actor, &data_ov003_0223812c);
    func_020109a0(actor, 0x57, 3, 0);
    func_0205eae0(actor->held, 0x1a, 3, 0);
}
CLEAN_AS(func_ov003_02215460, FieldActor_EnterState52)

/* func_ov003_02215494: asks for state 0x52; whether it was queued. */
void *FieldActor_RequestState52(FieldActor *actor, int priority, int arg)
{
    return (void *) (intptr_t) request_state(actor, 0x52, priority, arg, NULL, 0);
}
CLEAN_AS(func_ov003_02215494, FieldActor_RequestState52)

/* ---- State 0x51: animation 0x56 */

/* func_ov003_022154cc: state 0x51's update. */
void FieldActor_UpdateState51(FieldActor *actor)
{
    func_02010f5c(actor);
    func_0200f554(actor);
    func_02010d64(actor);
    FieldActor_EndState51(actor);
}
CLEAN_AS(func_ov003_022154cc, FieldActor_UpdateState51)

/* func_ov003_022154ec: at the animation's end the state after this one is noted and the actor
 * moves on: func_02008c40 (5) with the request's byte, else func_0200d4e8 (3). The result is
 * theirs, 0 before the end. */
int FieldActor_EndState51(FieldActor *actor)
{
    int done = func_02056f94(&actor->anim);
    if (done == 0) {
        return done;
    }
    actor->next_state = func_02008258(actor, actor->state);
    if (actor->work.s51_flag != 0) {
        return func_02008c40(actor, 5, -1);
    }
    return func_0200d4e8(actor, 3, 1, -1);
}
CLEAN_AS(func_ov003_022154ec, FieldActor_EndState51)

/* func_ov003_02215544: state 0x51's message handler: the state is asked for again with the saved
 * byte (func_ov003_02215624). */
void FieldActor_State51Message(FieldActor *actor, int arg)
{
    u8 flag;
    State51Saved_Get(&actor->saved.flag51, &flag);
    func_ov003_02215624(actor, flag, 6, arg);
}
CLEAN_AS(func_ov003_02215544, FieldActor_State51Message)

/* func_ov003_02215570: entering state 0x51 with the request's byte (kept in the work and saved):
 * animation 0x56 with pose 0x19 in hand, sounds 0x84c and 0x84e, unk_5D0 kept at unk_8C4; the
 * actor of this console runs func_0203b144. */
void FieldActor_EnterState51(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 flag = request->payload[0];

    func_ov003_02215620(&actor->work.s51_flag, flag);
    func_ov003_0221561c(&actor->saved.flag51, flag);
    func_020109a0(actor, 0x56, 3, 0);
    func_0205eae0(actor->held, 0x19, 3, 0);
    func_0200f328(actor, 0x84c);
    func_0200f328(actor, 0x84e);
    copy_point(&actor->unk_8C4, &actor->unk_5D0);
    if (is_local_player(actor)) {
        func_0203b144();
    }
}
CLEAN_AS(func_ov003_02215570, FieldActor_EnterState51)

/* func_ov003_02215614 */
void State51Saved_Get(const u8 *saved, u8 *flag)
{
    *flag = *saved;
}
CLEAN_AS(func_ov003_02215614, State51Saved_Get)
