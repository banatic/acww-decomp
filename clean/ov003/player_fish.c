/* The fish each player has on the line or in hand (fish_shadow.h). */
#include "fish_shadow.h"

#include "autoload_2/fx_math.h" /* Math_Atan2 */
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "field_actor.h" /* FieldActorBlock48, FieldActor_OffsetMatrix */
#include "main/actor.h"  /* Vec_YawTo */
#include "main/creature_table.h"
#include "main/effect_system.h"
#include "main/fish_disp.h"
#include "main/globe.h"
#include "main/player_actor_ops.h"
#include "main/session.h"
#include "main/session_players.h"
#include "ov004/member_pointer.h"

/* A size class's numbers (data_ov003_0223c014, eight rows of 0x14 bytes); the shadow's scale
 * is read here. */
typedef struct PlayerFishSize {
    u8 unk_00[0x0e];
    u8 scale_x; /* 0x0e: in percent */
    u8 scale_z; /* 0x0f */
    u8 unk_10[4];
} PlayerFishSize;
static_assert(sizeof(PlayerFishSize) == 0x14, "PlayerFishSize");

/* The reach of the rods by the second number of a fish's kind (CreatureTableInfo.unk_01): the
 * first byte, in tenths of a unit; the first rod's table is read here. */
typedef struct PlayerFishRange {
    u8 reach;
    u8 pad_01;
    s16 angle;
} PlayerFishRange;

typedef struct PlayerFishRodRanges {
    const PlayerFishRange *ranges;
    const void *unk_04;
} PlayerFishRodRanges;

#define PLAYER_FISH_SIZES 8
#define PLAYER_FISH_SCALE 0x1333 /* 1.2 */
#define PLAYER_FISH_SWIM_FRAMES 30
#define PLAYER_FISH_SWIM_MAX_STEP 0x214
#define PLAYER_FISH_ARC_FRAMES 20
#define PLAYER_FISH_ARC_HEIGHT 0x14cd
#define PLAYER_FISH_ARC_BACK_DROP 0x1800
#define PLAYER_FISH_HOLD_OFFSET 0x4cd /* how far towards the fish the hold point is moved */
#define PLAYER_FISH_HAND_OFFSET 0x800
#define PLAYER_FISH_VOLUME 0x7f

/* The method at slot 0x5c (word 23) of an actor's vtable: its hold point written to `out`
 * (not 0), or 0 when it has none. */
typedef int (*PlayerFishHoldPointFn)(Actor *actor, Vec3 *out);
#define PLAYER_FISH_SLOT_HOLD_POINT 23

typedef void (*PlayerFishStateFn)(void *self, int player);

extern PlayerFish data_ov003_0225f4dc[PLAYER_FISH_COUNT];
extern FishShadow data_ov003_0225f76c[FISH_SHADOW_COUNT];
/* Each state's step function, member functions of a player's fish. */
extern MemberPointer data_ov003_0225f138[5];
extern const PlayerFishSize data_ov003_0223c014[PLAYER_FISH_SIZES];
extern const PlayerFishRodRanges data_ov003_0223bf00[2];
extern const CreatureTableInfo data_020cb784[];
extern NetSession *data_020ccf94;
extern s32 data_020c904c; /* the water's surface height */
extern const fx16 FX_SinCosTable_[4096 * 2];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
/* The overlay's: the throw towards a point ahead of the player (func_ov003_0222a960), a
 * point moved `distance` along `angle` (func_ov003_0222be78), the arc's end reached
 * (func_ov003_0222796c), the fish's model past its first frame (func_ov003_0222a88c), a fish's
 * scale (func_ov003_0222aaa0), the shadows near a point fleeing it (func_ov003_02228400), and
 * the player's line in the water (func_ov003_0222c364, func_ov003_0222c1f4, func_ov003_0222c1bc). */
extern int func_ov003_0222a960(int player, int arrive);
extern void func_ov003_0222be78(Vec3 *position, int distance, u16 angle);
extern int func_ov003_0222796c(const Vec3 *position, const Vec3 *from, const Vec3 *to);
extern int func_ov003_0222a88c(PlayerFish *self, int player);
extern void func_ov003_0222aaa0(Vec3 *scale, int kind);
extern int func_ov003_02228400(const Vec3 *point, int reach);
extern int func_ov003_0222c364(int player);
extern Vec3 *func_ov003_0222c1f4(int player);
extern int func_ov003_0222c1bc(int player);

/* Player `player`'s fish, the address computed as the original does, without a bound. */
static PlayerFish *player_fish_at(int player)
{
    return (PlayerFish *) (uintptr_t) ((u32) (uintptr_t) data_ov003_0225f4dc + (u32) player * sizeof(PlayerFish));
}

/* Shadow `index`, without a bound. */
static FishShadow *player_fish_shadow(int index)
{
    return (FishShadow *) (uintptr_t) ((u32) (uintptr_t) data_ov003_0225f76c + (u32) index * sizeof(FishShadow));
}

/* Kind `kind`'s details, without a bound. */
static const CreatureTableInfo *player_fish_creature(int kind)
{
    return (const CreatureTableInfo *) (uintptr_t) ((u32) (uintptr_t) data_020cb784 + (u32) kind * sizeof(CreatureTableInfo));
}

/* The ROM's signed division (_s32_div_f): a divisor of 0 gives the numerator back, and
 * -0x80000000 / -1 gives -0x80000000. */
static int player_fish_div(int numerator, int divisor)
{
    if (divisor == 0) {
        return numerator;
    }
    if (divisor == -1) {
        return (int) (0u - (u32) numerator);
    }
    return numerator / divisor;
}

static void player_fish_set_scale(PlayerFish *self, fx32 scale)
{
    self->scale.x = scale;
    self->scale.y = scale;
    self->scale.z = scale;
}

/* func_ov003_02228ec4: the destructor. */
PlayerFish *PlayerFish_Destruct(PlayerFish *self)
{
    SoundEmitterClass_DestructBaseB((SoundEmitterObject *) self->emitter);
    return self;
}
CLEAN_AS(func_ov003_02228ec4, PlayerFish_Destruct)

/* func_ov003_02228ed4: the constructor: idle, no model, effect or shadow, a scale of 1.2 and a
 * position of (1.0, 1.0, 1.0). */
PlayerFish *PlayerFish_Construct(PlayerFish *self)
{
    SoundEmitterClass_ConstructBaseB((SoundEmitterObject *) self->emitter);
    self->state = PLAYER_FISH_IDLE;
    self->model = -1;
    self->mode = 0;
    self->shadow = PLAYER_FISH_NO_SHADOW;
    self->arrived = 0;
    self->frames = 0;
    player_fish_set_scale(self, PLAYER_FISH_SCALE);
    self->splash = 0;
    self->rotation[0] = 0;
    self->rotation[1] = 0;
    self->rotation[2] = 0;
    self->effect = -1;
    self->unk_a0 = 0;
    self->position.x = 0x1000;
    self->position.y = 0x1000;
    self->position.z = 0x1000;
    return self;
}
CLEAN_AS(func_ov003_02228ed4, PlayerFish_Construct)

/* Ends the fish when `ok` is 0. */
static int player_fish_end_unless(PlayerFish *fish, int ok)
{
    if (!ok) {
        fish->state = PLAYER_FISH_END;
        return 0;
    }
    return 1;
}

/* func_ov003_02229100: another console's player's fish display state 2 (that player threw the
 * fish back, func_ov003_0222a960): a shown fish is thrown, an idle one starts and is thrown
 * (state PLAYER_FISH_TAKE), a waiting one is shown and thrown. A throw that fails ends it (0). */
int PlayerFish_OnRemoteState2(FishShadowProcess *self, unsigned int player)
{
    (void) self;
    if (player >= PLAYER_FISH_COUNT) {
        return 0;
    }
    PlayerFish *fish = &data_ov003_0225f4dc[player];
    int state = fish->state;
    if (state == PLAYER_FISH_SHOW) {
        return player_fish_end_unless(fish, func_ov003_0222a960((int) player, 0));
    }
    if (state == PLAYER_FISH_IDLE) {
        return player_fish_end_unless(fish, func_ov003_0222a960((int) player, 1));
    }
    if (state == PLAYER_FISH_WAIT) {
        fish->state = PLAYER_FISH_SHOW;
        return player_fish_end_unless(fish, func_ov003_0222a960((int) player, 0));
    }
    return 1;
}
CLEAN_AS(func_ov003_02229100, PlayerFish_OnRemoteState2)

/* func_ov003_02229184: an idle fish of `player` starts as another console's player's catch of
 * kind `kind` at `point` (PLAYER_FISH_REMOTE); whether it did. */
int PlayerFish_StartRemote(FishShadowProcess *self, unsigned int player, int kind, const Vec3 *point)
{
    (void) self;
    if (player >= PLAYER_FISH_COUNT) {
        return 0;
    }
    PlayerFish *fish = &data_ov003_0225f4dc[player];
    if (fish->state != PLAYER_FISH_IDLE) {
        return 0;
    }
    fish->point_a = *point;
    fish->kind = kind;
    fish->state = PLAYER_FISH_TAKE;
    fish->mode = PLAYER_FISH_REMOTE;
    return 1;
}
CLEAN_AS(func_ov003_02229184, PlayerFish_StartRemote)

/* func_ov003_022291c8: another console's player's fish display state 1: the fish ends. */
int PlayerFish_OnRemoteState1(FishShadowProcess *self, unsigned int player)
{
    (void) self;
    if (player >= PLAYER_FISH_COUNT) {
        return 0;
    }
    data_ov003_0225f4dc[player].state = PLAYER_FISH_END;
    return 1;
}
CLEAN_AS(func_ov003_022291c8, PlayerFish_OnRemoteState1)

/* func_ov003_022291e4: another console's player's fish display state 0: with the point it
 * keeps (none: nothing), the fish starts as that player's catch of its kind at the point
 * (at the surface height -1.2) and the display state is set to 3; else the fish ends.
 * QUIRK: the fish ended is looked up without a check of the player number. */
void PlayerFish_OnRemoteState0(FishShadowProcess *self, int player)
{
    int kind = FishDisp_PlayerKind((u8) player);
    int x;
    int z;
    if (FishDisp_PlayerPoint(&x, &z, (u8) player)) {
        Vec3 point = {x, -0x1333, z};
        if (PlayerFish_StartRemote(self, (u8) player, kind, &point)) {
            FishDisp_SetPlayerState((u8) player, 3, -1, 0, 0);
        } else {
            player_fish_at(player)->state = PLAYER_FISH_END;
        }
    }
}
CLEAN_AS(func_ov003_022291e4, PlayerFish_OnRemoteState0)

/* func_ov003_0222924c: in a session, each other console's player's fish follows its fish
 * display state (an unknown player, state 9, is taken as 1): 0 starts it; 6 starts it already
 * in the hand; 1 ends it and 2 throws it (PlayerFish_OnRemoteState2), the display state then
 * set to 8 (none), or the fish ended when that fails. */
void PlayerFish_Sync(FishShadowProcess *self)
{
    NetSession *session = data_020ccf94;
    for (int i = 0; i < PLAYER_FISH_COUNT; i++) {
        if (Session_IsLocalSlot(session, i)) {
            continue;
        }
        int state = FishDisp_PlayerState((u8) i);
        if (state == FISH_DISP_PLAYER_INVALID) {
            state = 1;
        }
        switch (state) {
            case 0:
                PlayerFish_OnRemoteState0(self, i);
                break;
            case 6:
                data_ov003_0225f4dc[i].arrived = 1;
                PlayerFish_OnRemoteState0(self, i);
                break;
            case 1:
                if (PlayerFish_OnRemoteState1(self, (u8) i)) {
                    FishDisp_SetPlayerState((u8) i, FISH_DISP_PLAYER_NONE, -1, 0, 0);
                } else {
                    data_ov003_0225f4dc[i].state = PLAYER_FISH_END;
                }
                break;
            case 2:
                if (PlayerFish_OnRemoteState2(self, (u8) i)) {
                    FishDisp_SetPlayerState((u8) i, FISH_DISP_PLAYER_NONE, -1, 0, 0);
                } else {
                    data_ov003_0225f4dc[i].state = PLAYER_FISH_END;
                }
                break;
        }
    }
}
CLEAN_AS(func_ov003_0222924c, PlayerFish_Sync)

/* func_ov003_0222933c: where the fish hangs from `actor`: the actor's hold point (vtable slot
 * 23) moved 0.3 towards the fish, or the actor's position when it has none. */
void PlayerFish_HoldPoint(PlayerFish *self, Actor *actor, Vec3 *out)
{
    const u32 *vtable = (const u32 *) actor->vtable;
    if (((PlayerFishHoldPointFn) (uintptr_t) vtable[PLAYER_FISH_SLOT_HOLD_POINT])(actor, out) == 0) {
        *out = actor->position;
    } else {
        u16 angle = (u16) Math_Atan2(self->position.x - out->x, self->position.z - out->z);
        int index = 2 * (angle >> 4);
        out->x += FX_MulFunc(PLAYER_FISH_HOLD_OFFSET, FX_SinCosTable_[index]);
        out->z += FX_MulFunc(PLAYER_FISH_HOLD_OFFSET, FX_SinCosTable_[index + 1]);
    }
}
CLEAN_AS(func_ov003_0222933c, PlayerFish_HoldPoint)

/* func_ov003_022293b0: the shadow swims away from the player at `player_position`: turned away
 * from it at the first frame, moved (frame + 2) / 32 a frame up to 0x214, the effect following
 * it on the surface, and the fish ended after 30 frames. */
int PlayerFish_Swim(PlayerFish *self, const Vec3 *player_position)
{
    int frame = self->frames;
    int step = (int) ((u32) (frame + 2) << 7);
    if (frame == 0) {
        self->rotation[1] = Vec_YawTo(player_position, &self->position);
    } else if (frame >= PLAYER_FISH_SWIM_FRAMES) {
        self->state = PLAYER_FISH_END;
    }
    if (step > PLAYER_FISH_SWIM_MAX_STEP) {
        step = PLAYER_FISH_SWIM_MAX_STEP;
    }
    func_ov003_0222be78(&self->position, step, (u16) self->rotation[1]);
    self->frames++;
    Vec3 at = self->position;
    at.y = data_020c904c;
    EffectSystem_MoveHandle(self->effect, &at, NULL, NULL);
    return 1;
}
CLEAN_AS(func_ov003_022293b0, PlayerFish_Swim)

/* func_ov003_02229428: frame `frame` of an arc of `frames` frames from `from` that rises
 * `to->y` and peaks about `height` up while it covers the distance across to `to`: the height
 * set from the start's, and the position moved a `frames`th of that distance towards `to`.
 * 0 (nothing) once `frame` reaches `frames`.
 * QUIRK: the divisions are the ROM's (a divisor of 0 gives the numerator back). */
int PlayerFish_ArcStep(Vec3 *position, const Vec3 *from, const Vec3 *to, int frame, int height, int frames)
{
    if (frames <= frame) {
        return 0;
    }
    int rise = to->y;
    int frames_sq = frames * frames;
    int gravity = player_fish_div((int) ((u32) (height - (rise >> 1)) << 3), frames_sq);
    int distance = Vec_DistanceXZ(from, to);
    int yaw = Vec_YawTo(from, to);
    int speed = player_fish_div(rise + ((gravity * frames_sq) >> 1), frames);
    position->y = from->y + (frame * speed - ((frame * frame * gravity) >> 1));
    func_ov003_0222be78(position, player_fish_div(distance, frames), (u16) yaw);
    return 1;
}
CLEAN_AS(func_ov003_02229428, PlayerFish_ArcStep)

/* func_ov003_022294b4: a frame of the arc between the fish's points (`back`: from point_b to
 * point_a 1.5 lower, PLAYER_FISH_ARC_BACK; else from point_a to point_b): once the fish is at
 * or past the end (func_ov003_0222796c), or the arc is over, it ends in the water (`splash`).
 * QUIRK: the arc back's rise is point_a's height less 1.5 rather than a difference of heights
 * as the other arc's is. */
void PlayerFish_StepArc(PlayerFish *self, int back)
{
    Vec3 from;
    Vec3 to;
    if (back) {
        from = self->point_b;
        to = self->point_a;
        to.y = self->point_a.y - PLAYER_FISH_ARC_BACK_DROP;
    } else {
        from = self->point_a;
        to = self->point_b;
        to.y = self->point_b.y - self->point_a.y;
    }
    Vec3 at = self->position;
    Vec3 check_from = from;
    Vec3 check_to = to;
    if (func_ov003_0222796c(&at, &check_from, &check_to)) {
        self->state = PLAYER_FISH_END;
        self->splash = 1;
    } else {
        Vec3 arc_from = from;
        Vec3 arc_to = to;
        if (PlayerFish_ArcStep(&self->position, &arc_from, &arc_to, self->frames, PLAYER_FISH_ARC_HEIGHT,
                               PLAYER_FISH_ARC_FRAMES) == 0) {
            self->state = PLAYER_FISH_END;
            self->splash = 1;
        }
        self->frames++;
    }
}
CLEAN_AS(func_ov003_022294b4, PlayerFish_StepArc)

/* func_ov003_02229590: the fish lands in the water: it becomes the shadow (kind 0x3b) at the
 * surface, scaled by its size class, starting again (PLAYER_FISH_TAKE) to swim away
 * (PLAYER_FISH_SWIM). A splash and a wake that follows it (kept in `effect`) at its size, and
 * the size's sound (0x7e2-0x7e4); none for a size of 8 or more. The shadows within the first
 * rod's reach for the kind flee the point (func_ov003_02228400), unless the player is another
 * console's in a session.
 * QUIRK: the kind's row is read without a bound. */
void PlayerFish_Splash(PlayerFish *self, int player)
{
    static const u8 splash_kinds[PLAYER_FISH_SIZES] = {0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x19, 0x18};
    static const u8 wake_kinds[PLAYER_FISH_SIZES] = {0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x21, 0x20};
    static const u16 sounds[PLAYER_FISH_SIZES] = {0x7e2, 0x7e2, 0x7e2, 0x7e3, 0x7e3, 0x7e4, 0x7e4, 0x7e3};
    self->state = PLAYER_FISH_TAKE;
    self->splash = 0;
    const CreatureTableInfo *info = player_fish_creature(self->kind);
    int size = info->offset_class;
    self->scale.x = (data_ov003_0223c014[size].scale_x << 12) / 100;
    self->scale.y = 0x1000;
    self->scale.z = (data_ov003_0223c014[size].scale_z << 12) / 100;
    self->position.y = data_020c904c;
    self->kind = PLAYER_FISH_KIND_SHADOW;
    Vec3 at = self->position;
    if (size < PLAYER_FISH_SIZES) {
        EffectSystem_StartKind(splash_kinds[size], &at, NULL, NULL);
        self->effect = EffectSystem_StartKind(wake_kinds[size], &at, NULL, NULL);
        SoundEmitter_PlayB((SoundEmitter *) self->emitter, sounds[size], PLAYER_FISH_VOLUME, 0);
    }
    self->mode = PLAYER_FISH_SWIM;
    NetSession *session = data_020ccf94;
    if (!Session_IsLinked(session) || Session_IsLocalSlot(session, player)) {
        int reach = (data_ov003_0223bf00[0].ranges[info->unk_01].reach << 12) / 10;
        func_ov003_02228400(&at, reach);
    }
}
CLEAN_AS(func_ov003_02229590, PlayerFish_Splash)

/* func_ov003_022297f0: the fish ends: its model given back and the fish idle with nothing kept,
 * its effect ended; when it ended in the water the shadow then swims away (PlayerFish_Splash). */
void PlayerFish_End(PlayerFish *self, int player)
{
    FishDisp_ReleaseModel(self->model);
    self->model = -1;
    self->state = PLAYER_FISH_IDLE;
    self->shadow = PLAYER_FISH_NO_SHADOW;
    self->arrived = 0;
    self->unk_a0 = 0;
    self->frames = 0;
    player_fish_set_scale(self, PLAYER_FISH_SCALE);
    self->rotation[0] = 0;
    self->rotation[1] = 0;
    self->rotation[2] = 0;
    EffectSystem_EndHandle(self->effect);
    self->effect = -1;
    if (self->splash) {
        PlayerFish_Splash(self, player);
    }
}
CLEAN_AS(func_ov003_022297f0, PlayerFish_End)

/* func_ov003_02229874: the shadow the fish was (none: 0) forgets its float, player and hook.
 * QUIRK: the float is not told (FishingFloat_SetFish is not called), and the shadow is looked up
 * without a bound. */
int PlayerFish_LetShadowGo(PlayerFish *self)
{
    int index = self->shadow;
    if (index == PLAYER_FISH_NO_SHADOW) {
        return 0;
    }
    FishShadow *shadow = player_fish_shadow(index);
    if (shadow->fishing_float != NULL) {
        shadow->fishing_float = NULL;
    }
    shadow->player = FISH_SHADOW_NO_PLAYER;
    shadow->hooked = 0;
    shadow->hook_state = 0;
    return 1;
}
CLEAN_AS(func_ov003_02229874, PlayerFish_LetShadowGo)

/* func_ov003_022298c4: PLAYER_FISH_END: a fish caught here (PLAYER_FISH_HOOKED) or thrown back
 * (PLAYER_FISH_ARC_BACK) lets go of its shadow; then it ends. */
int PlayerFish_StepEnd(PlayerFish *self, int player)
{
    if (self->mode == PLAYER_FISH_HOOKED || self->mode == PLAYER_FISH_ARC_BACK) {
        PlayerFish_LetShadowGo(self);
    }
    PlayerFish_End(self, player);
    return 1;
}
CLEAN_AS(func_ov003_022298c4, PlayerFish_StepEnd)

/* The fish flies to `actor`'s hold point (FishingFloat_Fly, easing down); on arriving it keeps
 * the point in point_b. */
static void player_fish_fly_to_hand(PlayerFish *self, Actor *actor)
{
    Vec3 hold;
    PlayerFish_HoldPoint(self, actor, &hold);
    Vec3 target = hold;
    if (FishingFloat_Fly(&target, self->gravity, &self->position, &self->speed, 1)) {
        self->arrived = 1;
        self->point_b = hold;
    }
}

/* The point of the player's hand block (PlayerActorOps_CopyBlock698) moved by `offset` along it
 * (none: NULL) and unbent from the globe. */
static Vec3 player_fish_hand(int player, const Vec3 *offset)
{
    FieldActorBlock48 block;
    PlayerActorOps_CopyBlock698(&block, player);
    FieldActorBlock48 moved = block;
    FieldActor_OffsetMatrix(&moved, offset);
    Vec3 hand;
    hand.x = (fx32) moved.words[9];
    hand.y = (fx32) moved.words[10];
    hand.z = (fx32) moved.words[11];
    Globe_Unbend(&hand, &hand);
    return hand;
}

/* func_ov003_022298f0: PLAYER_FISH_REMOTE's frame: without the player's actor the fish ends
 * (0). It flies to the actor's hold point, then stays at the point of the player's hand. */
int PlayerFish_FollowRemote(PlayerFish *self, int player)
{
    Actor *actor = (Actor *) (uintptr_t) SessionPlayers_ActorHandle(player);
    if (actor == NULL) {
        self->state = PLAYER_FISH_END;
        return 0;
    }
    if (self->arrived == 0) {
        player_fish_fly_to_hand(self, actor);
    } else {
        func_ov003_0222a88c(self, player);
        Vec3 hand = player_fish_hand(player, NULL);
        self->position = hand;
        self->point_b = hand;
    }
    return 1;
}
CLEAN_AS(func_ov003_022298f0, PlayerFish_FollowRemote)

/* func_ov003_022299b8: PLAYER_FISH_HOOKED's frame: the fish flies to the hold point of the
 * player's actor (none: it ends, 0); once there it only looks at its model's first frame
 * while unk_a0 is clear (else 0). */
int PlayerFish_FollowLocal(PlayerFish *self, int player)
{
    if (self->arrived == 0) {
        Actor *actor = (Actor *) (uintptr_t) SessionPlayers_ActorHandle(player);
        if (actor == NULL) {
            self->state = PLAYER_FISH_END;
            return 0;
        }
        player_fish_fly_to_hand(self, actor);
        return 1;
    }
    if (self->unk_a0 == 0) {
        func_ov003_0222a88c(self, player);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_022299b8, PlayerFish_FollowLocal)

/* func_ov003_02229a38: PLAYER_FISH_SHOW: the fish moved by its mode, then its model shown
 * (animated; with its sound in the player's hand; the swimming shadow fading out over 30
 * frames). Without the player's actor while swimming it ends (0). */
int PlayerFish_StepShow(PlayerFish *self, int player)
{
    int alpha = PLAYER_FISH_SWIM_FRAMES;
    u8 play_sound = 0;
    switch (self->mode) {
        case PLAYER_FISH_HOOKED:
            PlayerFish_FollowLocal(self, player);
            play_sound = 1;
            break;
        case PLAYER_FISH_REMOTE:
            PlayerFish_FollowRemote(self, player);
            play_sound = 1;
            break;
        case PLAYER_FISH_ARC_BACK:
            PlayerFish_StepArc(self, 1);
            break;
        case PLAYER_FISH_ARC:
            PlayerFish_StepArc(self, 0);
            break;
        case PLAYER_FISH_SWIM: {
            Actor *actor = SessionPlayers_ActorOf(player);
            if (actor == NULL) {
                self->state = PLAYER_FISH_END;
                return 0;
            }
            PlayerFish_Swim(self, &actor->position);
            alpha -= self->frames;
            if (alpha < 1) {
                alpha = 1;
            }
            break;
        }
    }
    FishDisp_ShowModel(self->model, self->kind, &self->position, &self->scale, self->rotation[0], self->rotation[1],
                       self->rotation[2], 1, play_sound, (u32) alpha);
    return 1;
}
CLEAN_AS(func_ov003_02229a38, PlayerFish_StepShow)

/* Whether an actor is out of sight (far, and not drawn). */
static int player_fish_actor_hidden(const Actor *actor)
{
    return (actor->cull_flags & ACTOR_CULL_FAR) != 0 && (actor->cull_flags & ACTOR_CULL_SKIP_DRAW) != 0;
}

/* func_ov003_02229ae0: PLAYER_FISH_WAIT: while the player's actor is out of sight the fish
 * stays at the actor's position (0); then it is in the hand and shown (1). Without the actor it
 * ends (0). */
int PlayerFish_StepWait(PlayerFish *self, int player)
{
    Actor *actor = (Actor *) (uintptr_t) SessionPlayers_ActorHandle(player);
    if (actor == NULL) {
        self->state = PLAYER_FISH_END;
        return 0;
    }
    if (player_fish_actor_hidden(actor)) {
        self->position = actor->position;
        self->point_b = actor->position;
        return 0;
    }
    self->arrived = 1;
    self->state = PLAYER_FISH_SHOW;
    return 1;
}
CLEAN_AS(func_ov003_02229ae0, PlayerFish_StepWait)

/* func_ov003_02229b54: the flight from point_a to the player's hand (0.5 along the hand block)
 * set up (FishingFloat_Arc, arc 3), the fish at point_a. Without the player (0-3) or its actor
 * the fish ends (0). */
int PlayerFish_StartArc(PlayerFish *self, unsigned int player)
{
    if (player >= PLAYER_FISH_COUNT) {
        self->state = PLAYER_FISH_END;
        return 0;
    }
    if (SessionPlayers_ActorHandle((int) player) == 0) {
        self->state = PLAYER_FISH_END;
        return 0;
    }
    Vec3 offset = {PLAYER_FISH_HAND_OFFSET, 0, 0};
    Vec3 hand = player_fish_hand((int) player, &offset);
    Vec3 start = self->point_a;
    FishingFloat_Arc(&hand, &start, &self->gravity, &self->speed, 3);
    self->position = self->point_a;
    return 1;
}
CLEAN_AS(func_ov003_02229b54, PlayerFish_StartArc)

/* func_ov003_02229c04: PLAYER_FISH_TAKE: a model taken (none while it has one: 0), the fish
 * scaled for its kind unless it is the swimming shadow, its flight set up for a catch, then
 * shown (or waiting while another console's player is out of sight). */
int PlayerFish_StepTake(PlayerFish *self, int player)
{
    if (self->model != -1) {
        return 0;
    }
    self->model = FishDisp_TakeModel();
    if (self->mode != PLAYER_FISH_SWIM) {
        func_ov003_0222aaa0(&self->scale, self->kind);
    }
    if (self->mode == PLAYER_FISH_HOOKED) {
        if (PlayerFish_StartArc(self, (unsigned int) player) == 0) {
            return 0;
        }
    } else if (self->mode == PLAYER_FISH_REMOTE) {
        if (PlayerFish_StartArc(self, (unsigned int) player) == 0) {
            return 0;
        }
        Actor *actor = SessionPlayers_ActorOf(player);
        if (actor != NULL && player_fish_actor_hidden(actor)) {
            self->state = PLAYER_FISH_WAIT;
            return 1;
        }
    }
    self->state = PLAYER_FISH_SHOW;
    return 1;
}
CLEAN_AS(func_ov003_02229c04, PlayerFish_StepTake)

/* func_ov003_02229ca4: PLAYER_FISH_IDLE: nothing. */
int PlayerFish_StepIdle(void)
{
    return 1;
}
CLEAN_AS(func_ov003_02229ca4, PlayerFish_StepIdle)

/* State `state`'s step function, the address computed without a bound. */
static const MemberPointer *player_fish_step(int state)
{
    return (const MemberPointer *) (uintptr_t) ((u32) (uintptr_t) data_ov003_0225f138 + (u32) state * sizeof(MemberPointer));
}

/* func_ov003_02229ca8: a player's fish's frame. While the player's line is in the water
 * (func_ov003_0222c364) the emitter follows the line's point and plays sound 0x7e0 for its
 * state 1, or 0x7e1 and effect 0x15 on the surface for state 2; else it follows the fish. Then
 * its state's step (data_ov003_0225f138) when it has one; another console's player's fish that
 * ended sets that player's fish display state to 8 (none). */
void PlayerFish_Update(PlayerFish *self, int player)
{
    SoundEmitter *emitter = (SoundEmitter *) self->emitter;
    if (func_ov003_0222c364(player)) {
        Vec3 at = *func_ov003_0222c1f4(player);
        Vec3 water = at;
        SoundEmitter_UpdateAtB(emitter, &at);
        if (func_ov003_0222c1bc(player) == 1) {
            SoundEmitter_PlayB(emitter, 0x7e0, PLAYER_FISH_VOLUME, 0);
        } else if (func_ov003_0222c1bc(player) == 2) {
            SoundEmitter_PlayB(emitter, 0x7e1, PLAYER_FISH_VOLUME, 0);
            water.y = data_020c904c;
            EffectSystem_StartKind(0x15, &water, NULL, NULL);
        }
    } else {
        Vec3 at = self->position;
        SoundEmitter_UpdateAtB(emitter, &at);
    }
    const MemberPointer *step = player_fish_step(self->state);
    if (step->function != 0) {
        void *object = MemberPointer_Object(step, self);
        ((PlayerFishStateFn) (uintptr_t) MemberPointer_Code(step, object))(object, player);
    }
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) && Session_IsLocalSlot(session, player) == 0 && self->state == PLAYER_FISH_END) {
        FishDisp_SetPlayerState((unsigned int) player, FISH_DISP_PLAYER_NONE, -1, 0, 0);
    }
}
CLEAN_AS(func_ov003_02229ca8, PlayerFish_Update)

#include "main/collision_query.h" /* CollisionQuery_FindWaterAhead */

/* The kinds that are not fish (fish_disp.h): they are not thrown back. */
#define PLAYER_FISH_JUNK_FIRST 0x38
#define PLAYER_FISH_JUNK_LAST 0x3a
#define PLAYER_FISH_KINDS 0x3b
#define PLAYER_FISH_MESSAGE 0x2a /* player message 42 (FishDisp_HandleMessage) */
#define PLAYER_FISH_THROW_REACH 0x7800
#define PLAYER_FISH_THROW_RADIUS 0x2000
#define PLAYER_FISH_THROW_STEPS 12

/* A size class's row (data_ov003_0223c014) from its byte 0x12, the fish's scale in percent. */
extern const u8 data_ov003_0223c026[];
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* The fish's destructor, handed to __cxa_vec_cleanup: the game's symbol (PlayerFish_Destruct). */
extern void func_ov003_02228ec4(void *fish);

/* Message 42 with the one byte `state` (1: the fish is in the hand, 2: thrown back). */
static void player_fish_send(u8 state)
{
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, &state, 1);
    Session_EndMessage(session, PLAYER_FISH_MESSAGE, 4);
}

/* func_ov003_0222a7bc: the fish turned to be thrown back towards `yaw`, by its kind: most turn
 * a quarter about z and take the yaw (plus a quarter) about x; the kinds 0xa, 0xb and 0x2d-0x30
 * turn a half about z (less one unit) and a quarter about x with the yaw reversed about y; 0xf
 * turns 3/8 about z and a quarter about x; 0x35 and 0x36 a quarter about x; 0x23-0x25 only take
 * the yaw about y.
 * QUIRK: most kinds take the yaw about x, not y. */
void PlayerFish_TurnForThrow(PlayerFish *self, int yaw, int kind)
{
    switch (kind) {
        case 0xa:
        case 0xb:
        case 0x2d:
        case 0x2e:
        case 0x2f:
        case 0x30:
            self->rotation[2] = (s16) (self->rotation[2] + 0x7fff);
            self->rotation[1] = (s16) -yaw;
            self->rotation[0] = (s16) (self->rotation[0] + 0x4000);
            break;
        case 0xf:
            self->rotation[2] = (s16) (self->rotation[2] + 0x6000);
            self->rotation[1] = (s16) yaw;
            self->rotation[0] = (s16) (self->rotation[0] + 0x4000);
            break;
        case 0x23:
        case 0x24:
        case 0x25:
            self->rotation[1] = (s16) yaw;
            break;
        case 0x35:
        case 0x36:
            self->rotation[0] = (s16) (self->rotation[0] + 0x4000);
            self->rotation[1] = (s16) yaw;
            break;
        default:
            self->rotation[2] = (s16) (self->rotation[2] + 0x4000);
            self->rotation[0] = (s16) (yaw + 0x4000);
            break;
    }
}
CLEAN_AS(func_ov003_0222a7bc, PlayerFish_TurnForThrow)

/* func_ov003_0222a88c: whether the fish's model is past its first frame. */
int PlayerFish_ModelPastFirst(PlayerFish *self, int player)
{
    (void) player;
    return FishDisp_ModelPassedFrame(self->model, 1) != 0;
}
CLEAN_AS(func_ov003_0222a88c, PlayerFish_ModelPastFirst)

/* func_ov003_0222a8a8: player `player`'s (0-3) fish, shown or waiting, tells the other consoles
 * once that it is in the hand (message 42 with byte 1); whether it did now. */
int PlayerFish_AnnounceHeld(int player)
{
    if (player < 0 || player >= PLAYER_FISH_COUNT) {
        return 0;
    }
    PlayerFish *fish = &data_ov003_0225f4dc[player];
    if (fish->state != PLAYER_FISH_SHOW && fish->state != PLAYER_FISH_WAIT) {
        return 0;
    }
    if (fish->unk_a0 != 0) {
        return 0;
    }
    player_fish_send(1);
    fish->unk_a0 = 1;
    return 1;
}
CLEAN_AS(func_ov003_0222a8a8, PlayerFish_AnnounceHeld)

/* func_ov003_0222a918: player `player`'s fish's position.
 * QUIRK: for a player outside 0-3 it is player 0's fish's. */
Vec3 *PlayerFish_PositionOf(int player)
{
    if (player < 0 || player >= PLAYER_FISH_COUNT) {
        return &data_ov003_0225f4dc[0].position;
    }
    return &data_ov003_0225f4dc[player].position;
}
CLEAN_AS(func_ov003_0222a918, PlayerFish_PositionOf)

/* func_ov003_0222a938: whether player `player`'s fish is doing anything (not idle); 1 for a
 * player outside 0-3. */
int PlayerFish_IsBusy(int player)
{
    if (player < 0 || player >= PLAYER_FISH_COUNT) {
        return 1;
    }
    return data_ov003_0225f4dc[player].state != PLAYER_FISH_IDLE;
}
CLEAN_AS(func_ov003_0222a938, PlayerFish_IsBusy)

/* func_ov003_0222a960: player `player`'s (0-3) fish is thrown back into the water from the
 * hand (PLAYER_FISH_ARC_BACK): it flies back towards where it came from, to the first water up
 * to 7.5 ahead of the player (CollisionQuery_FindWaterAhead; else where it came from), turned
 * for its kind; `start` also starts it (PLAYER_FISH_TAKE). In a session, the player at this
 * console tells the other consoles (message 42 with byte 2). Something that is not a fish
 * (0x38-0x3a) only ends, when not to be started. 0 for another player or one without an actor,
 * else 1. */
int PlayerFish_ThrowBack(int player, int start)
{
    if (player < 0 || player > 3) {
        return 0;
    }
    Actor *actor = SessionPlayers_ActorOf(player);
    if (actor == NULL) {
        return 0;
    }
    PlayerFish *fish = &data_ov003_0225f4dc[player];
    int kind = fish->kind;
    if (kind >= PLAYER_FISH_JUNK_FIRST && kind <= PLAYER_FISH_JUNK_LAST) {
        if (!start) {
            fish->state = PLAYER_FISH_END;
        }
        return 1;
    }
    int yaw = Vec_YawTo(&fish->point_b, &fish->point_a);
    Vec3 water;
    if (CollisionQuery_FindWaterAhead(&water, &actor->position, yaw, PLAYER_FISH_THROW_REACH, PLAYER_FISH_THROW_RADIUS,
                                      PLAYER_FISH_THROW_STEPS)) {
        fish->point_a = water;
    }
    PlayerFish_TurnForThrow(fish, yaw, kind);
    if (start) {
        fish->state = PLAYER_FISH_TAKE;
    }
    fish->mode = PLAYER_FISH_ARC_BACK;
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) && Session_IsLocalSlot(session, player)) {
        player_fish_send(2);
    }
    return 1;
}
CLEAN_AS(func_ov003_0222a960, PlayerFish_ThrowBack)

/* func_ov003_0222aa50: the fish of the player shadow `shadow` is hooked by (none, or no shadow:
 * 0) placed at `at` with the scale `scale`; 1.
 * QUIRK: the player number is not checked. */
int PlayerFish_PlaceForShadow(FishShadow *shadow, Vec3 *at, Vec3 *scale)
{
    if (shadow == NULL || shadow->player == FISH_SHADOW_NO_PLAYER) {
        return 0;
    }
    PlayerFish *fish = player_fish_at(shadow->player);
    fish->position = *at;
    fish->scale = *scale;
    return 1;
}
CLEAN_AS(func_ov003_0222aa50, PlayerFish_PlaceForShadow)

/* func_ov003_0222aaa0: the scale of a fish of kind `kind` (0-0x3a; 1.0 for another): its size
 * class's percentage (byte 0x12 of data_ov003_0223c014's row).
 * QUIRK: the size class is not checked. */
void PlayerFish_KindScale(Vec3 *out, int kind)
{
    if (kind < 0 || kind >= PLAYER_FISH_KINDS) {
        out->x = 0x1000;
        out->y = 0x1000;
        out->z = 0x1000;
        return;
    }
    u32 size = player_fish_creature(kind)->offset_class;
    int percent = *(const u8 *) (uintptr_t) ((u32) (uintptr_t) data_ov003_0223c026 + size * 0x14);
    fx32 scale = (percent << 12) / 100;
    out->x = scale;
    out->y = scale;
    out->z = scale;
}
CLEAN_AS(func_ov003_0222aaa0, PlayerFish_KindScale)

/* func_ov003_0222aae8: the fish of the player shadow `shadow` is hooked by ends (the float's
 * FishingFloat_LetFishGo); 0 without a shadow or player.
 * QUIRK: the player number is not checked. */
int PlayerFish_EndForShadow(FishShadow *shadow)
{
    if (shadow == NULL || shadow->player == FISH_SHADOW_NO_PLAYER) {
        return 0;
    }
    player_fish_at(shadow->player)->state = PLAYER_FISH_END;
    return 1;
}
CLEAN_AS(func_ov003_0222aae8, PlayerFish_EndForShadow)

/* func_ov003_0222ab14: whether the fish of the player shadow `shadow` is hooked by has reached
 * the hand (the float's FishingFloat_FishFlag80); 0 without a shadow or player.
 * QUIRK: the player number is not checked. */
int PlayerFish_ArrivedForShadow(FishShadow *shadow)
{
    if (shadow == NULL || shadow->player == FISH_SHADOW_NO_PLAYER) {
        return 0;
    }
    return player_fish_at(shadow->player)->arrived != 0;
}
CLEAN_AS(func_ov003_0222ab14, PlayerFish_ArrivedForShadow)

/* func_ov003_0222c474 (registered at the overlay's start): the four players' fish destroyed. */
void PlayerFish_DestroyAll(void *object)
{
    (void) object;
    __cxa_vec_cleanup(data_ov003_0225f4dc, PLAYER_FISH_COUNT, sizeof(PlayerFish), func_ov003_02228ec4);
}
CLEAN_AS(func_ov003_0222c474, PlayerFish_DestroyAll)
