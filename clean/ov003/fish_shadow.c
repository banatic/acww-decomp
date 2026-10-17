/* The fish shadows of the town's water, their fin and their process (fish_shadow.h). */
#include "fish_shadow.h"

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "autoload_2/heap.h"     /* Heap_FreeAux */
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "main/actor.h"       /* Vec_YawTo */
#include "main/actor_table.h" /* Position_Tile */
#include "main/creature_table.h"
#include "main/effect_system.h"
#include "main/fish_disp.h"
#include "main/packed_bytes.h"
#include "main/player_actor_ops.h"
#include "main/rom_file.h"
#include "main/session.h"
#include "main/unit_type_info.h"
#include "ov004/member_pointer.h"

static_assert(sizeof(FishShadowSense) == 4, "FishShadowSense");
static_assert(sizeof(FishShadowModel) == 0xb8, "FishShadowModel");
static_assert(offsetof(FishShadow, source) == 0x40 && offsetof(FishShadow, contacts) == 0x4c, "FishShadow");
static_assert(offsetof(FishShadow, slot) == 0x7c && offsetof(FishShadow, state) == 0x80, "FishShadow");
static_assert(offsetof(FishShadow, unk_84) == 0x84 && offsetof(FishShadow, position) == 0x120, "FishShadow");
static_assert(offsetof(FishShadow, yaw) == 0x138 && offsetof(FishShadow, unk_140) == 0x140, "FishShadow");
static_assert(offsetof(FishShadow, model) == 0x144 && offsetof(FishShadow, group_state) == 0x1fc, "FishShadow");
static_assert(offsetof(FishShadow, behaviour) == 0x200 && offsetof(FishShadow, effect) == 0x204, "FishShadow");
static_assert(offsetof(FishShadow, tile_x) == 0x208 && offsetof(FishShadow, respawn) == 0x212, "FishShadow");
static_assert(offsetof(FishShadow, last_position) == 0x218 && offsetof(FishShadow, hook_state) == 0x224, "FishShadow");
static_assert(offsetof(FishShadow, player) == 0x227 && offsetof(FishShadow, fishing_float) == 0x22c, "FishShadow");
static_assert(offsetof(FishShadow, hooked) == 0x23c && offsetof(FishShadow, timer) == 0x244, "FishShadow");
static_assert(offsetof(FishShadow, sense) == 0x248 && sizeof(FishShadow) == 0x24c, "FishShadow");
static_assert(offsetof(FishFin, files) == 0x08 && offsetof(FishFin, model) == 0x58, "FishFin");
static_assert(offsetof(FishFin, anim) == 0x11c && sizeof(FishFin) == 0x13c, "FishFin");
static_assert(offsetof(FishShadowProcess, shadows) == 0x50 && offsetof(FishShadowProcess, fin) == 0x68, "process");
static_assert(offsetof(FishShadowProcess, shadow_file) == 0x80 && offsetof(FishShadowProcess, unk_84) == 0x84, "process");
static_assert(sizeof(PlayerFish) == 0xa4, "PlayerFish");

/* A size class's numbers (data_ov003_0223c014, eight rows of 0x14 bytes). */
typedef struct FishShadowSize {
    u8 reach;      /* 0x00: how near the float must be to startle it, in hundredths of a unit */
    u8 unk_01[13]; /* 0x01 */
    u8 scale_x;    /* 0x0e: the shadow's scale, in percent */
    u8 scale_z;    /* 0x0f */
    u16 radius;    /* 0x10: how far ahead the ground is looked at, in hundredths */
    u8 unk_12[2];  /* 0x12 */
} FishShadowSize;
static_assert(sizeof(FishShadowSize) == 0x14, "FishShadowSize");

/* How near and how straight ahead a float must be for a bite, by the second number of the
 * fish's kind (CreatureTableInfo.unk_01). */
typedef struct FishBiteRange {
    u8 reach; /* in tenths of a unit */
    u8 pad_01;
    s16 angle; /* the most the yaw to the float may differ from the fish's */
} FishBiteRange;

/* The ranges for the two rods (items 0x1374 and 0x1375). */
typedef struct FishRodRanges {
    const FishBiteRange *ranges;
    const void *unk_04;
} FishRodRanges;

#define FISH_SHADOW_ROD 0x1374
#define FISH_SHADOW_GOLDEN_ROD 0x1375
#define FISH_SHADOW_SIZES 8
#define FISH_SHADOW_SURFACE_Y (-0x1333) /* the height the ground ahead is looked at */
#define FISH_SHADOW_ALARM_MAX 200
#define FISH_SHADOW_SENSE_RANGE 0x8000 /* 8.0 */
#define FISH_SHADOW_SOUND 0x82f
#define FISH_SHADOW_SPLASH_FRAMES 10
#define FISH_SHADOW_THIS_CONSOLE 4 /* main's player number for the player at this console */
#define FISH_SHADOW_MESSAGE 0x2a   /* player message 42 (FishDisp_HandleMessage) */

extern FishShadow data_ov003_0225f76c[FISH_SHADOW_COUNT];
extern FishFin data_ov003_0225f220;
extern PlayerFish data_ov003_0225f4dc[PLAYER_FISH_COUNT];
/* Each state's entry and update functions, member functions of the process. */
extern MemberPointer data_ov003_0225f1d0[FISH_SHADOW_STATES][2];
/* Frames since a float landed (FishShadow_NoteSplash), counted down. */
extern u16 data_ov003_0225f0b8;
extern const FishShadowSize data_ov003_0223c014[FISH_SHADOW_SIZES];
extern const FishRodRanges data_ov003_0223bf00[2];
extern const CreatureTableInfo data_020cb784[];
extern NetSession *data_020ccf94;
extern Heap *data_021fbe94;
/* The shadow's model file's path, and the pools' names "fish_sdw" and "fish_fin". */
extern const char *data_ov003_0223bdac;
extern char data_ov003_0223c0b4[];
extern char data_ov003_0223c0c0[];
/* Vtables: the process's and its base class's, the fin animation's, and the sound source's
 * base class's and its own. */
extern const u32 data_ov003_0223bfcc[];
extern const u32 data_020da13c[];
extern const u32 data_ov003_0223c0d4[];
extern const u32 data_0213efe8[];
extern const u32 data_0213f020[];
extern const fx16 FX_SinCosTable_[4096 * 2];

/* The pools' heaps, handed to ModelPool_Create (the game's own functions). */
extern int func_0205c960(int size, int heapword);
extern void func_0205c944(void);
extern int func_0205c92c(int size, int heapword);
extern void func_0205c910(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
/* The shadow's model set up from the file in an entry of the pool (func_ov003_02227778), the
 * respawn countdown (func_ov003_022279d8), a random number in [lo, hi) and one of either sign
 * (func_ov003_0222793c, func_ov003_0222791c), whether a player runs (func_ov003_02228018),
 * whether `b` is in the box around `a` (func_ov003_0222799c) and the shadow fleeing a point
 * (func_ov003_02228150). */
extern int func_ov003_02227778(FishShadow *fish, void *file, ModelPool *pool);
extern void func_ov003_022279d8(FishShadow *fish);
extern int func_ov003_0222793c(int lo, int hi);
extern int func_ov003_0222791c(int lo, int hi);
extern int func_ov003_02228018(int player);
extern int func_ov003_0222799c(const Vec3 *a, const Vec3 *b, int dx, int dz_ahead, int dz_behind);
extern int func_ov003_02228150(FishShadow *fish, const Vec3 *from);

typedef void (*FishShadowStateFn)(void *self, FishShadow *fish, int index);

/* Player `player`'s fish, the address computed as the original does, without a bound. */
static PlayerFish *fish_shadow_player_fish(int player)
{
    return (PlayerFish *) (uintptr_t) ((u32) (uintptr_t) data_ov003_0225f4dc + (u32) player * sizeof(PlayerFish));
}

/* Kind `kind`'s details, the address computed without a bound (a kind of -1 reads the row
 * before the table). */
static const CreatureTableInfo *fish_shadow_creature(int kind)
{
    return (const CreatureTableInfo *) (uintptr_t) ((u32) (uintptr_t) data_020cb784 + (u32) kind * sizeof(CreatureTableInfo));
}

/* State `state`'s pair of member functions, the address computed without a bound. */
static MemberPointer *fish_shadow_state_fns(int state)
{
    return (MemberPointer *) (uintptr_t) ((u32) (uintptr_t) data_ov003_0225f1d0 + (u32) state * 2 * sizeof(MemberPointer));
}

static void fish_shadow_call(const MemberPointer *member, FishShadowProcess *self, FishShadow *fish, int index)
{
    void *object = MemberPointer_Object(member, self);
    ((FishShadowStateFn) (uintptr_t) MemberPointer_Code(member, object))(object, fish, index);
}

/* func_ov003_02228a98: state 0's entry: nothing. */
void FishShadow_EnterNone(void) {}
CLEAN_AS(func_ov003_02228a98, FishShadow_EnterNone)

/* func_ov003_02228a9c: shadow `fish` set to state `state` (0-4; nothing for another) and its
 * entry function (data_ov003_0225f1d0) called, when it has one, with the shadow and `index`. */
void FishShadow_SetState(FishShadowProcess *self, int state, FishShadow *fish, int index)
{
    if (state >= 0 && state < FISH_SHADOW_STATES) {
        fish->state = state;
        const MemberPointer *enter = &fish_shadow_state_fns(fish->state)[0];
        if (enter->function != 0) {
            fish_shadow_call(enter, self, fish, index);
        }
    }
}
CLEAN_AS(func_ov003_02228a9c, FishShadow_SetState)

/* func_ov003_02228ae8: a shadow's frame: its emitter and sound source follow it, its state's
 * update function runs when it has one, then its respawn countdown (func_ov003_022279d8). */
void FishShadow_Update(FishShadowProcess *self, FishShadow *fish, int index)
{
    Vec3 at = fish->position;
    SoundEmitter_UpdateAtB((SoundEmitter *) fish->emitter, &at);
    Vec3 source_at = fish->position;
    SoundSource_UpdateAt(&fish->source, &source_at);
    const MemberPointer *update = &fish_shadow_state_fns(fish->state)[1];
    if (update->function != 0) {
        fish_shadow_call(update, self, fish, index);
    }
    func_ov003_022279d8(fish);
}
CLEAN_AS(func_ov003_02228ae8, FishShadow_Update)

/* func_ov003_02228b74 (vtable slot 0): creation: the pools (six shadows, one fin), the
 * shadow's model file loaded, each shadow's model set up from it and the shadow left waiting
 * to be placed in its group, a respawn countdown of 2400 frames plus 400 for each before it,
 * and its sounds stopped. Each other console's player whose fish is shown (fish display state
 * 3) is set to 6, so that it is shown again; the players' fish's sounds are stopped. */
int FishShadow_Create(FishShadowProcess *self)
{
    ModelPool_Create(&self->shadows, FISH_SHADOW_COUNT, 0, 0, 0x800, func_0205c960, func_0205c944, data_ov003_0223c0b4);
    ModelPool_Create(&self->fin, 1, 0x400, 0x80, 0x800, func_0205c92c, func_0205c910, data_ov003_0223c0c0);
    self->shadow_file = RomFile_Load(data_ov003_0223bdac, data_021fbe94, 4, NULL);
    for (int i = 0; i < FISH_SHADOW_COUNT; i++) {
        FishShadow *fish = &data_ov003_0225f76c[i];
        func_ov003_02227778(fish, self->shadow_file, &self->shadows);
        fish->group_state = i < FISH_SHADOW_GROUP_SIZE ? FISH_SHADOW_WAIT_GROUP0 : FISH_SHADOW_WAIT_GROUP1;
        fish->tile_x = i;
        fish->tile_z = 0;
        fish->index = (u8) i;
        fish->respawn = (s16) (i * 400 + 2400);
        SoundEmitter_StopB((SoundEmitter *) fish->emitter);
        SoundSource_Init(&fish->source);
    }
    NetSession *session = data_020ccf94;
    for (int i = 0; i < PLAYER_FISH_COUNT; i++) {
        if (Session_IsLinked(session) && !Session_IsLocalSlot(session, i) && FishDisp_PlayerState((u8) i) == 3) {
            FishDisp_SetPlayerState((u8) i, 6, -1, 0, 0);
        }
        SoundEmitter_StopB((SoundEmitter *) data_ov003_0225f4dc[i].emitter);
    }
    return 1;
}
CLEAN_AS(func_ov003_02228b74, FishShadow_Create)

/* func_ov003_02228cd4: the fin put away: its model's joints detached and the model released,
 * its files and its pool entry given back, and its animation forgotten. */
void FishShadow_ReleaseFin(FishShadowProcess *self)
{
    FishFin *fin = &data_ov003_0225f220;
    fin->state = 0;
    AnimatedModel_DetachJoints((AnimatedModel *) &fin->model);
    ModelObject_Release(&fin->model.object);
    ModelPoolFiles_Release(&fin->files);
    ModelPool_Release(&self->fin, &fin->slot);
    fin->anim.anim = NULL;
    fin->anim.model = NULL;
}
CLEAN_AS(func_ov003_02228cd4, FishShadow_ReleaseFin)

/* func_ov003_02228d1c: the fin starts loading (state 2) in an entry of its pool. */
int FishShadow_TakeFin(FishShadowProcess *self)
{
    FishFin *fin = &data_ov003_0225f220;
    fin->state = 2;
    ModelPool_Take(&self->fin, &fin->slot);
    ModelPoolFiles_Reset(&fin->files);
    return 1;
}
CLEAN_AS(func_ov003_02228d1c, FishShadow_TakeFin)

/* func_ov003_02228d48: shadow `index` (0-5) taken away: no state, its effect ended, waiting to
 * be placed again in its group. A shadow on a float lets go of it (unless its player's fish is
 * being taken, PLAYER_FISH_TAKE) and its hook state is cleared.
 * QUIRK: the player's fish is looked up without a check of the player number. */
void FishShadow_Reset(FishShadowProcess *self, int index)
{
    (void) self;
    if (index < 0 || index >= FISH_SHADOW_COUNT) {
        return;
    }
    FishShadow *fish = &data_ov003_0225f76c[index];
    fish->state = FISH_SHADOW_NONE;
    EffectSystem_EndHandle(fish->effect);
    fish->effect = -1;
    if (fish->group_state == FISH_SHADOW_IN_GROUP0) {
        fish->group_state = FISH_SHADOW_WAIT_GROUP0;
    } else if (fish->group_state == FISH_SHADOW_IN_GROUP1) {
        fish->group_state = FISH_SHADOW_WAIT_GROUP1;
    }
    fish->tile_x = index;
    fish->tile_z = 0;
    FishingFloat *fishing_float = fish->fishing_float;
    if (fishing_float != NULL) {
        if (fish_shadow_player_fish(fish->player)->state != PLAYER_FISH_TAKE) {
            FishingFloat_SetFish(fishing_float, NULL);
            fish->fishing_float = NULL;
            fish->player = FISH_SHADOW_NO_PLAYER;
            fish->hooked = 0;
        }
        fish->hook_state = 0;
    }
}
CLEAN_AS(func_ov003_02228d48, FishShadow_Reset)

/* func_ov003_02228dfc: shadow `index` (0-5) set to state 2; whether it is one. */
int FishShadow_SetState2(FishShadowProcess *self, int index)
{
    (void) self;
    if (index >= 0 && index < FISH_SHADOW_COUNT) {
        data_ov003_0225f76c[index].state = FISH_SHADOW_STATE_2;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_02228dfc, FishShadow_SetState2)

/* The destructor's work: the pools, then the base class's. */
static void fish_shadow_destruct(FishShadowProcess *self)
{
    self->base.vtable = data_ov003_0223bfcc;
    ModelPool_Destruct(&self->fin);
    ModelPool_Destruct(&self->shadows);
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
}

/* func_ov003_02228e20 (vtable slot 17): the destructor, and the process freed. */
FishShadowProcess *FishShadow_DestructFree(FishShadowProcess *self)
{
    fish_shadow_destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov003_02228e20, FishShadow_DestructFree)

/* func_ov003_02228e58 (vtable slot 16): the destructor. */
FishShadowProcess *FishShadow_Destruct(FishShadowProcess *self)
{
    fish_shadow_destruct(self);
    return self;
}
CLEAN_AS(func_ov003_02228e58, FishShadow_Destruct)

/* func_ov003_02228e8c: the constructor: the base class's, then its vtable, the pools and no
 * file. */
FishShadowProcess *FishShadow_Construct(FishShadowProcess *self)
{
    Process_Construct(&self->base);
    self->base.vtable = data_020da13c;
    self->base.vtable = data_ov003_0223bfcc;
    ModelPool_Init(&self->shadows);
    ModelPool_Init(&self->fin);
    self->shadow_file = NULL;
    return self;
}
CLEAN_AS(func_ov003_02228e8c, FishShadow_Construct)

/* func_ov003_02228f44: the sense's destructor: nothing. */
void FishShadowSense_Destruct(FishShadowSense *sense)
{
    (void) sense;
}
CLEAN_AS(func_ov003_02228f44, FishShadowSense_Destruct)

/* func_ov003_02228f48: the sense's constructor: all cleared. */
void FishShadowSense_Construct(FishShadowSense *sense)
{
    sense->alarm = 0;
    sense->sound_frames = 0;
    sense->cooldown = 0;
    sense->mode = FISH_SHADOW_SENSE_FAR;
}
CLEAN_AS(func_ov003_02228f48, FishShadowSense_Construct)

/* func_ov003_02228f54: the fin's destructor (registered for the global object). */
FishFin *FishFin_Destruct(FishFin *fin)
{
    fin->anim.ctrl.vtable = data_ov003_0223c0d4;
    ModelAnim_Destruct(&fin->anim);
    AnimatedModel_DestructComplete((AnimatedModel *) &fin->model);
    ModelPoolFiles_Destruct(&fin->files);
    ModelPoolSlot_Destruct(&fin->slot);
    return fin;
}
CLEAN_AS(func_ov003_02228f54, FishFin_Destruct)

/* func_ov003_02228f8c: the fin's constructor: no state, its files reset. */
FishFin *FishFin_Construct(FishFin *fin)
{
    ModelPoolSlot_Construct(&fin->slot);
    ModelPoolFiles_Construct(&fin->files);
    AnimatedModel_Construct((AnimatedModel *) &fin->model);
    ModelAnim_ConstructBase(&fin->anim);
    fin->anim.ctrl.vtable = data_ov003_0223c0d4;
    fin->state = 0;
    ModelPoolFiles_Reset(&fin->files);
    return fin;
}
CLEAN_AS(func_ov003_02228f8c, FishFin_Construct)

/* func_ov003_02228fd0 (slot 0 of vtable data_ov003_0223c0d4): the fin animation's destructor. */
ModelAnim *FishFinAnim_Destruct(ModelAnim *anim)
{
    anim->ctrl.vtable = data_ov003_0223c0d4;
    ModelAnim_Destruct(anim);
    return anim;
}
CLEAN_AS(func_ov003_02228fd0, FishFinAnim_Destruct)

/* func_ov003_02228fe8: a shadow's destructor (its parts in reverse). */
FishShadow *FishShadow_DestructRecord(FishShadow *fish)
{
    FishShadowSense_Destruct(&fish->sense);
    AnimatedModel_DestructComplete((AnimatedModel *) &fish->model);
    ModelObject_DestructComplete(&fish->unk_84);
    ModelPoolSlot_Destruct(&fish->slot);
    CollisionContacts_Destroy(&fish->contacts);
    SoundEmitterClass_DestructBaseB((SoundEmitterObject *) fish->emitter);
    return fish;
}
CLEAN_AS(func_ov003_02228fe8, FishShadow_DestructRecord)

/* func_ov003_0222902c: a shadow's constructor: its parts, then no kind, state, effect, player
 * or float, and a position of (1.0, 1.0, 1.0). */
FishShadow *FishShadow_ConstructRecord(FishShadow *fish)
{
    SoundEmitterClass_ConstructBaseB((SoundEmitterObject *) fish->emitter);
    /* the sound source's base class's vtable, then its own */
    fish->source.vtable = (const SoundSourceVtable *) data_0213efe8;
    fish->source.vtable = (const SoundSourceVtable *) data_0213f020;
    CollisionContacts_Construct(&fish->contacts);
    ModelPoolSlot_Construct(&fish->slot);
    ModelObject_Construct(&fish->unk_84);
    AnimatedModel_Construct((AnimatedModel *) &fish->model);
    fish->tile_x = 0;
    fish->tile_z = 0;
    FishShadowSense_Construct(&fish->sense);
    fish->kind = -1;
    fish->timer = -1;
    fish->state = FISH_SHADOW_NONE;
    fish->group_state = FISH_SHADOW_NEW;
    fish->unk_201 = 0;
    fish->effect = -1;
    fish->player = FISH_SHADOW_NO_PLAYER;
    fish->fishing_float = NULL;
    fish->hook_state = 0;
    fish->hooked = 0;
    fish->position.x = 0x1000;
    fish->position.y = 0x1000;
    fish->position.z = 0x1000;
    return fish;
}
CLEAN_AS(func_ov003_0222902c, FishShadow_ConstructRecord)

/* func_ov003_02229da4: the shadow's sense cleared. */
void FishShadow_ResetSense(FishShadow *fish)
{
    FishShadowSense_Reset(&fish->sense);
}
CLEAN_AS(func_ov003_02229da4, FishShadow_ResetSense)

/* func_ov003_02229db4: the sense cleared. */
void FishShadowSense_Reset(FishShadowSense *sense)
{
    sense->alarm = 0;
    sense->sound_frames = 0;
    sense->cooldown = 0;
    sense->mode = FISH_SHADOW_SENSE_FAR;
}
CLEAN_AS(func_ov003_02229db4, FishShadowSense_Reset)

/* The alarm one up, at most FISH_SHADOW_ALARM_MAX.
 * QUIRK: it counts in a byte, so 255 would wrap to 0 first (the game keeps it at 200 or less). */
static void fish_shadow_alarm_up(FishShadowSense *sense)
{
    sense->alarm = (u8) (sense->alarm + 1);
    if (sense->alarm >= FISH_SHADOW_ALARM_MAX) {
        sense->alarm = FISH_SHADOW_ALARM_MAX;
    }
}

/* The player at this console's position, NULL when there is none. */
static const Vec3 *fish_shadow_player_position(void)
{
    return PlayerActorOps_StartPosition(0);
}

/* func_ov003_02229dc0: FISH_SHADOW_SENSE_SOUND: sound 0x82f each frame while frames are left,
 * then back to NEAR with a cooldown of 20-79 frames. A running player sets it back to NEAR at
 * once (cooldown 20-39) and raises the alarm; otherwise the alarm goes down. */
void FishShadowSense_StepSound(FishShadowSense *sense, FishShadow *fish)
{
    if (sense->sound_frames != 0) {
        sense->sound_frames--;
        SoundSource_Play(&fish->source, FISH_SHADOW_SOUND);
    } else {
        sense->cooldown = (u8) func_ov003_0222793c(20, 80);
        sense->mode = FISH_SHADOW_SENSE_NEAR;
    }
    if (func_ov003_02228018(0)) {
        sense->cooldown = (u8) func_ov003_0222793c(20, 40);
        sense->mode = FISH_SHADOW_SENSE_NEAR;
        sense->sound_frames = 0;
        fish_shadow_alarm_up(sense);
    } else if (sense->alarm != 0) {
        sense->alarm--;
    }
}
CLEAN_AS(func_ov003_02229dc0, FishShadowSense_StepSound)

/* func_ov003_02229e2c: FISH_SHADOW_SENSE_NEAR: the cooldown counts down; a player 8.0 or more
 * away makes it FAR. Else a running player raises the alarm; otherwise the alarm goes down and,
 * at 150 or less with the cooldown over, the sound plays for 60-139 frames (SOUND). */
void FishShadowSense_StepNear(FishShadowSense *sense, FishShadow *fish)
{
    if (sense->cooldown != 0) {
        sense->cooldown--;
    }
    const Vec3 *player = fish_shadow_player_position();
    if (player != NULL && Vec_DistanceXZ(player, &fish->position) >= FISH_SHADOW_SENSE_RANGE) {
        sense->mode = FISH_SHADOW_SENSE_FAR;
    } else if (func_ov003_02228018(0)) {
        fish_shadow_alarm_up(sense);
    } else {
        if (sense->alarm != 0) {
            sense->alarm--;
        }
        if (sense->alarm <= 150 && sense->cooldown == 0) {
            sense->sound_frames = (u8) func_ov003_0222793c(60, 140);
            sense->mode = FISH_SHADOW_SENSE_SOUND;
        }
    }
}
CLEAN_AS(func_ov003_02229e2c, FishShadowSense_StepNear)

/* func_ov003_02229eac: FISH_SHADOW_SENSE_FAR: the alarm goes down by 3 (to 0 below 10), the
 * cooldown counts down, and a player nearer than 8.0 makes it NEAR.
 * QUIRK: an alarm of 1 or 2 wraps to 254 or 255 rather than going to 0. */
void FishShadowSense_StepFar(FishShadowSense *sense, FishShadow *fish)
{
    if (sense->alarm != 0) {
        sense->alarm = (u8) (sense->alarm - 3);
        if (sense->alarm < 10) {
            sense->alarm = 0;
        }
    }
    if (sense->cooldown != 0) {
        sense->cooldown--;
    }
    const Vec3 *player = fish_shadow_player_position();
    if (player != NULL && Vec_DistanceXZ(player, &fish->position) < FISH_SHADOW_SENSE_RANGE) {
        sense->mode = FISH_SHADOW_SENSE_NEAR;
    }
}
CLEAN_AS(func_ov003_02229eac, FishShadowSense_StepFar)

/* func_ov003_02229f00: the sense's step by its mode (nothing for another). */
void FishShadowSense_Step(FishShadowSense *sense, FishShadow *fish)
{
    switch (sense->mode) {
        case FISH_SHADOW_SENSE_FAR:
            FishShadowSense_StepFar(sense, fish);
            break;
        case FISH_SHADOW_SENSE_NEAR:
            FishShadowSense_StepNear(sense, fish);
            break;
        case FISH_SHADOW_SENSE_SOUND:
            FishShadowSense_StepSound(sense, fish);
            break;
    }
}
CLEAN_AS(func_ov003_02229f00, FishShadowSense_Step)

/* The point `radius` hundredths ahead of the shadow at angle `angle`, at the surface height. */
static Vec3 fish_shadow_point(const FishShadow *fish, u16 angle, int radius)
{
    int index = 2 * (angle >> 4);
    Vec3 point;
    point.x = fish->position.x + FX_SinCosTable_[index] * radius / 100;
    point.y = FISH_SHADOW_SURFACE_Y;
    point.z = fish->position.z + FX_SinCosTable_[index + 1] * radius / 100;
    return point;
}

/* func_ov003_02229f2c: the ground's attribute (CollisionGround.attr) at three points the size
 * class's radius away: 45 degrees to the left of its yaw, 45 degrees to the right and straight
 * ahead. */
void FishShadow_GroundAhead(FishShadow *fish, int *left, int *right, int *ahead)
{
    int yaw = fish->yaw;
    int radius = data_ov003_0223c014[fish->size].radius;
    Vec3 left_point = fish_shadow_point(fish, (u16) (yaw + 0x2000), radius);
    Vec3 right_point = fish_shadow_point(fish, (u16) (yaw - 0x2000), radius);
    Vec3 ahead_point = fish_shadow_point(fish, (u16) yaw, radius);
    CollisionGround left_ground;
    CollisionGround right_ground;
    CollisionGround ahead_ground;
    CollisionGround_Init(&left_ground, &left_point, 0, 0);
    CollisionGround_Init(&right_ground, &right_point, 0, 0);
    CollisionGround_Init(&ahead_ground, &ahead_point, 0, 0);
    *left = left_ground.attr;
    *right = right_ground.attr;
    *ahead = ahead_ground.attr;
    CollisionGround_Destroy(&ahead_ground);
    CollisionGround_Destroy(&right_ground);
    CollisionGround_Destroy(&left_ground);
}
CLEAN_AS(func_ov003_02229f2c, FishShadow_GroundAhead)

/* The attributes the shadows of grounds 0-3 swim over, and those of grounds 5 and 6. */
static int fish_shadow_attr_a(int attr)
{
    return (attr >= 0xb && attr <= 0x12) || attr == 7 || attr == 0x14;
}

static int fish_shadow_attr_b(int attr)
{
    return attr == 8 || attr == 0x17;
}

/* func_ov003_0222a088: 0 when all three points of FishShadow_GroundAhead are of the shadow's
 * water (by its ground: 0-3 the attributes 7, 0xb-0x12 and 0x14; 5 and 6 the attributes 8 and
 * 0x17; any other both sets but 0x17), else 1. */
int FishShadow_IsBlocked(FishShadow *fish)
{
    int left;
    int right;
    int ahead;
    FishShadow_GroundAhead(fish, &left, &right, &ahead);
    switch (fish->ground) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (fish_shadow_attr_a(left) && fish_shadow_attr_a(right) && fish_shadow_attr_a(ahead)) {
                return 0;
            }
            break;
        case 5:
        case 6:
            if (fish_shadow_attr_b(left) && fish_shadow_attr_b(right) && fish_shadow_attr_b(ahead)) {
                return 0;
            }
            break;
        default:
            if ((fish_shadow_attr_a(left) || left == 8) && (fish_shadow_attr_a(right) || right == 8) &&
                (fish_shadow_attr_a(ahead) || ahead == 8)) {
                return 0;
            }
            break;
    }
    return 1;
}
CLEAN_AS(func_ov003_0222a088, FishShadow_IsBlocked)

/* The shadow put back where it was before its last move. */
static void fish_shadow_step_back(FishShadow *fish)
{
    fish->position = fish->last_position;
}

/* func_ov003_0222a16c: the check after a move, by the shadow's ground, with its tile's group
 * (UnitTypeInfo_GroupAt). A result other than 0 tells why it stopped:
 *   grounds 0-3: blocked ahead (1) or on group 1 (3), both stepping back;
 *   grounds 5, 6: at the edge columns 0 (6) or 5 (7); blocked ahead (2) or off group 1 (4),
 *            both stepping back; group 1 behind it (5);
 *   others: on group 2 and blocked ahead (1, stepping back); on group 1 as grounds 5 and 6 do
 *            but for 4; on any other group (1, stepping back). */
int FishShadow_CheckMove(FishShadow *fish)
{
    int ret = 0;
    int x;
    int z;
    Position_Tile(&x, &z, (const Position *) &fish->position);
    switch (fish->ground) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (FishShadow_IsBlocked(fish) != 0) {
                fish_shadow_step_back(fish);
                ret = 1;
            } else if (UnitTypeInfo_GroupAt(x, z) == 1) {
                fish_shadow_step_back(fish);
                ret = 3;
            }
            break;
        case 5:
        case 6: {
            int column = FishShadow_EdgeColumn(fish);
            if (column == 0) {
                ret = 6;
            } else if (column == 1) {
                ret = 7;
            } else if (FishShadow_IsBlocked(fish) != 0) {
                fish_shadow_step_back(fish);
                ret = 2;
            } else if (UnitTypeInfo_GroupAt(x, z) != 1) {
                fish_shadow_step_back(fish);
                ret = 4;
            } else if (FishShadow_IsWaterBehind(fish) != 0) {
                ret = 5;
            }
            break;
        }
        default:
            if (UnitTypeInfo_GroupAt(x, z) == 2) {
                if (FishShadow_IsBlocked(fish) != 0) {
                    fish_shadow_step_back(fish);
                    ret = 1;
                }
            } else if (UnitTypeInfo_GroupAt(x, z) == 1) {
                int column = FishShadow_EdgeColumn(fish);
                if (column == 0) {
                    ret = 6;
                } else if (column == 1) {
                    ret = 7;
                } else if (FishShadow_IsBlocked(fish) != 0) {
                    fish_shadow_step_back(fish);
                    ret = 2;
                } else if (FishShadow_IsWaterBehind(fish) != 0) {
                    ret = 5;
                }
            } else {
                fish_shadow_step_back(fish);
                ret = 1;
            }
            break;
    }
    return ret;
}
CLEAN_AS(func_ov003_0222a16c, FishShadow_CheckMove)

/* func_ov003_0222a330: whether the tile 2.0 behind the shadow (towards -z) is of group 1. */
int FishShadow_IsWaterBehind(FishShadow *fish)
{
    Vec3 behind = fish->position;
    behind.z -= 0x2000;
    int x;
    int z;
    Position_Tile(&x, &z, (const Position *) &behind);
    return UnitTypeInfo_GroupAt(x, z) == 1;
}
CLEAN_AS(func_ov003_0222a330, FishShadow_IsWaterBehind)

/* func_ov003_0222a378: which column of acres (32.0 wide) the shadow is in: 0 for the first,
 * 1 for column 5, 2 for any other. */
int FishShadow_EdgeColumn(FishShadow *fish)
{
    int column = fish->position.x >> 17;
    if (column == 0) {
        return 0;
    }
    if (column == 5) {
        return 1;
    }
    return 2;
}
CLEAN_AS(func_ov003_0222a378, FishShadow_EdgeColumn)

/* func_ov003_0222a398: the shadow lets go of the float it is on (none: 0): the float told, the
 * player and float forgotten and the hook state FISH_SHADOW_HOOK_DROPPED. */
int FishShadow_DropLine(FishShadow *fish)
{
    FishingFloat *fishing_float = fish->fishing_float;
    if (fishing_float == NULL) {
        return 0;
    }
    fish->unk_23d = 0;
    fish->player = FISH_SHADOW_NO_PLAYER;
    FishingFloat_SetFish(fishing_float, NULL);
    fish->fishing_float = NULL;
    fish->hooked = 0;
    fish->hook_state = FISH_SHADOW_HOOK_DROPPED;
    fish->unk_13c = 0;
    return 1;
}
CLEAN_AS(func_ov003_0222a398, FishShadow_DropLine)

/* The splash at a size class (effect kinds 0x12-0x19); none for a size of 8 or more. */
static void fish_shadow_splash(int size, const Vec3 *at)
{
    static const u8 kinds[FISH_SHADOW_SIZES] = {0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x19, 0x18};
    if (size < FISH_SHADOW_SIZES) {
        EffectSystem_StartKind(kinds[size], at, NULL, NULL);
    }
}

/* func_ov003_0222a3ec: the shadow caught by its player (none: 0): its alpha set to 1, its
 * player's fish set to take a model and fly from the shadow's position to the player's hand
 * (PLAYER_FISH_HOOKED) with the shadow's kind and number `index`, a splash at its size, and
 * message 42 sent: byte 0 (state 0), the kind and the point packed in five bytes.
 * QUIRK: the player's fish is looked up without a check of the player number. */
int FishShadow_Catch(FishShadow *fish, int index)
{
    u8 message[12];
    fish->alpha = 1;
    int player = fish->player;
    if (player == FISH_SHADOW_NO_PLAYER) {
        return 0;
    }
    PlayerFish *caught = fish_shadow_player_fish(player);
    caught->state = PLAYER_FISH_TAKE;
    caught->mode = PLAYER_FISH_HOOKED;
    caught->point_a = fish->position;
    caught->shadow = (s8) index;
    int kind = fish->kind;
    caught->kind = kind;
    Vec3 at = fish->position;
    fish_shadow_splash(fish->size, &at);
    message[0] = 0;
    message[1] = (u8) kind;
    PackedBytes_PackPoint(&message[7], fish->position.x, fish->position.z);
    MI_CpuCopy8(&message[7], &message[2], 5);
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, message, 7);
    Session_EndMessage(session, FISH_SHADOW_MESSAGE, 4);
    return 1;
}
CLEAN_AS(func_ov003_0222a3ec, FishShadow_Catch)

/* func_ov003_0222a544: the frames since a float landed counted down. */
void FishShadow_TickSplash(void)
{
    if (data_ov003_0225f0b8 != 0) {
        data_ov003_0225f0b8--;
    }
}
CLEAN_AS(func_ov003_0222a544, FishShadow_TickSplash)

/* func_ov003_0222a558: whether a float landed in the last frames. */
int FishShadow_SplashRecent(void)
{
    return data_ov003_0225f0b8 != 0;
}
CLEAN_AS(func_ov003_0222a558, FishShadow_SplashRecent)

/* func_ov003_0222a56c: a float landed (the float's step calls it). */
void FishShadow_NoteSplash(void)
{
    data_ov003_0225f0b8 = FISH_SHADOW_SPLASH_FRAMES;
}
CLEAN_AS(func_ov003_0222a56c, FishShadow_NoteSplash)

/* func_ov003_0222a578: whether the float of entry 0 (FishingFloat_FloatingOf) is in reach of a
 * fish of kind `kind` at `point` facing `yaw`, for `player` holding a rod (0x1374) or the other
 * rod (0x1375; anything else: 0): within the box of the kind's reach (func_ov003_0222799c) and
 * at most its angle off the fish's yaw.
 * QUIRK: the kind's row is read without a bound (a kind of -1 reads before the table). */
int FishShadow_InBiteRange(const Vec3 *point, int yaw, int player, int kind)
{
    FishingFloat *fishing_float = (FishingFloat *) (uintptr_t) FishingFloat_FloatingOf(0);
    if (fishing_float == NULL) {
        return 0;
    }
    u16 held[4] = {0, 0, 0, 0};
    PlayerActorOps_HeldItem(held, player);
    int rod;
    if (held[0] == FISH_SHADOW_ROD) {
        rod = 0;
    } else if (held[0] == FISH_SHADOW_GOLDEN_ROD) {
        rod = 1;
    } else {
        return 0;
    }
    const Vec3 *float_at = &fishing_float->position;
    const FishBiteRange *range = &data_ov003_0223bf00[rod].ranges[fish_shadow_creature(kind)->unk_01];
    int reach = (range->reach << 12) / 10;
    if (func_ov003_0222799c(point, float_at, reach, reach, reach) != 0 &&
        Math_AbsDiff16(Vec_YawTo(point, float_at), yaw) <= range->angle) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0222a578, FishShadow_InBiteRange)

/* func_ov003_0222a634: the shadow tries to bite the float of entry 0, when that float is the
 * player's at this console (in a session; else player 0) and no other shadow is on that
 * player's line. In reach (FishShadow_InBiteRange), a float that landed in the last frames
 * within the size class's reach startles it (it turns by a random 0x5000-0x7fff either way);
 * else it is hooked: the player and float kept and the float told. Whether it was hooked; the
 * landing's frames are counted down whenever no other shadow is on the line. */
int FishShadow_TryBite(FishShadow *fish)
{
    int ret = 0;
    FishingFloat *fishing_float = (FishingFloat *) (uintptr_t) FishingFloat_FloatingOf(0);
    if (fishing_float == NULL) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    int player;
    if (Session_IsLinked(session)) {
        if (fishing_float->player < 0) {
            return 0;
        }
        player = session->local_slot;
        if (fishing_float->player != player) {
            return 0;
        }
    } else {
        player = 0;
    }
    for (int i = 0; i < FISH_SHADOW_COUNT; i++) {
        FishShadow *other = &data_ov003_0225f76c[i];
        if (other != fish && player == other->player) {
            return 0;
        }
    }
    Vec3 at = fish->position;
    if (FishShadow_InBiteRange(&at, fish->yaw, player, fish->kind)) {
        int reach = (data_ov003_0223c014[fish->size].reach << 12) / 100;
        Vec3 float_at = fishing_float->position;
        if (FishShadow_SplashRecent() && func_ov003_0222799c(&fish->position, &float_at, reach, reach, reach)) {
            if (fish->behaviour != FISH_SHADOW_STARTLED) {
                fish->behaviour = FISH_SHADOW_STARTLED;
            }
            fish->yaw = (s16) (fish->yaw + (s16) func_ov003_0222791c(0x5000, 0x7fff));
            fish->unk_140 = 0x14;
        } else {
            fish->player = (s8) player;
            fish->fishing_float = fishing_float;
            FishingFloat_SetFish(fishing_float, (u8 *) fish);
            ret = 1;
            fish->hooked = 1;
        }
    }
    FishShadow_TickSplash();
    return ret;
}
CLEAN_AS(func_ov003_0222a634, FishShadow_TryBite)

/* func_ov003_0222a784: the shadow (none: 0) flees from the player at this console
 * (func_ov003_02228150); whether it did. */
int FishShadow_FleeFromPlayer(FishShadow *fish)
{
    if (fish == NULL) {
        return 0;
    }
    const Vec3 *from = PlayerActorOps_StartPosition(FISH_SHADOW_THIS_CONSOLE);
    if (from == NULL) {
        return 0;
    }
    return func_ov003_02228150(fish, from) != 0;
}
CLEAN_AS(func_ov003_0222a784, FishShadow_FleeFromPlayer)

extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* A shadow's destructor, handed to __cxa_vec_cleanup: the game's symbol
 * (FishShadow_DestructRecord). */
extern void func_ov003_02228fe8(void *fish);

/* func_ov003_0222c41c: a new process (0x88 bytes, cleared), constructed; NULL when there is no
 * memory. */
FishShadowProcess *FishShadow_New(void)
{
    FishShadowProcess *self = Heap_AllocAuxZeroed(sizeof(FishShadowProcess));
    if (self != NULL) {
        self = FishShadow_Construct(self);
    }
    return self;
}
CLEAN_AS(func_ov003_0222c41c, FishShadow_New)

/* func_ov003_0222c434 (slot 1 of vtable data_ov003_0223c0d4): the fin animation destroyed and
 * freed. */
ModelAnim *FishFinAnim_DestructDelete(ModelAnim *anim)
{
    anim->ctrl.vtable = data_ov003_0223c0d4;
    ModelAnim_Destruct(anim);
    Heap_OperatorDeleteB(anim);
    return anim;
}
CLEAN_AS(func_ov003_0222c434, FishFinAnim_DestructDelete)

/* func_ov003_0222c494 (registered at the overlay's start): the six shadows destroyed. */
void FishShadow_DestroyAll(void *object)
{
    (void) object;
    __cxa_vec_cleanup(data_ov003_0225f76c, FISH_SHADOW_COUNT, sizeof(FishShadow), func_ov003_02228fe8);
}
CLEAN_AS(func_ov003_0222c494, FishShadow_DestroyAll)

/* func_ov003_0222c414: the destructor of the global object at data_ov003_0225f0b4, registered
 * at the overlay's start: nothing. */
void FishShadowGlobal0225f0b4_Destruct(void *object)
{
    (void) object;
}
CLEAN_AS(func_ov003_0222c414, FishShadowGlobal0225f0b4_Destruct)

/* func_ov003_0222c418: that object's constructor, handed the field's acre map (data_021c80bc):
 * nothing. */
void FishShadowGlobal0225f0b4_Construct(void *object, int map)
{
    (void) object;
    (void) map;
}
CLEAN_AS(func_ov003_0222c418, FishShadowGlobal0225f0b4_Construct)
