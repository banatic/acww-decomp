/* The objects of kinds 5, 6 and 7 (sky_visitors.h). */
#include "sky_visitors.h"

#include "cell_anim.h"
#include "clean.h"
#include "event_buildings.h"
#include "event_schedule.h"
#include "sky_resources.h"
#include "sky_shots.h"
#include "state_block.h"
#include "main_random.h"
#include "player_actor_ops.h"
#include "player_actors.h"

static_assert(sizeof(SkyVisitorVars) == 12, "the words at 0x60");

#define SKY_VISITOR_PRIORITY 2
#define SKY_VISITOR_BOTTOM 0xd0000 /* y 208: below the screen */
#define SKY_KIND7_FORWARD_RESOURCE 0x28
#define SKY_KIND7_SWAY 0x8000
#define SKY_KIND7_STEP 0x30a
#define SKY_KIND7_PHASE_STEP (-100)
#define SKY_KIND7_ANIMATION 0x13
#define SKY_KIND7_HIT_ANIMATION 0x14
#define SKY_KIND7_SOUND 0x7fe
#define SKY_KIND7_HIT_SOUND 0x7ff
#define SKY_KIND7_EVENT 0x45
#define SKY_KIND6_SWAY 0x1000
#define SKY_KIND6_STEP 0x385
#define SKY_KIND6_PHASE_STEP 0xfa0
#define SKY_KIND6_ANIMATION 0x16
#define SKY_KIND6_THROWN_ANIMATION 0x17
#define SKY_KIND6_FALL_ANIMATION 0x18
#define SKY_KIND6_HIT_RESOURCE 0x24
#define SKY_KIND6_FALL_RESOURCE 0x25
#define SKY_KIND6_SOUND 0x7fb
#define SKY_KIND6_HIT_SOUND 0x7fc
#define SKY_KIND6_EVENT 0x44
#define SKY_KIND6_STATE_FLAG 9
#define SKY_KIND5_SWAY 0x5000
#define SKY_KIND5_START_SWAY 1000 /* what its set-up hands its path (not the sway of its run) */
#define SKY_KIND5_STEP 0x1ec
#define SKY_KIND5_PHASE_STEP 0x3e8
#define SKY_KIND5_ANIMATION 1
#define SKY_KIND5_HIT_ANIMATION 0
#define SKY_KIND5_SOUND 0x7f7
#define SKY_KIND5_HIT_SOUND 0x7f8

extern SkyObjects data_021f8b48;
extern SkyObjectSlot data_021fa678[]; /* the objects' slots */
extern SkyShotsHit data_021fbaf0;     /* the hit (0x2fa8 of the objects) */
extern const Vec3 data_021fbee8;      /* the origin */
extern StateBlock data_021dc7a8;
extern const fx16 FX_SinCosTable_[4096 * 2];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

static SkyVisitorVars *sky_visitor_vars(SkyObject *object)
{
    return (SkyVisitorVars *) (void *) SkyObject_Body(object)->words;
}

static SkyObjectSlot *sky_visitor_slot(const SkyObject *object)
{
    return (SkyObjectSlot *) ((uintptr_t) data_021fa678 + (u32) object->slot * (u32) sizeof(SkyObjectSlot));
}

/* The side the player's look turns to: 0 for one going east. */
static u8 sky_visitor_side(const SkyObjectBody *body)
{
    return body->forward == 0 ? 1 : 0;
}

/* func_020c048c: kind 7 taken down. */
void SkyKind7_TakeDown(SkyObject *object)
{
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020c048c, SkyKind7_TakeDown)

/* func_020c0494: a frame of kind 7. Crossing, it plays sound 0x7fe as its animation comes to
 * its first frame; when hit its resource moves on by one, the look is started (7) and sound
 * 0x7ff plays. The frame after it takes its second animation, stopped, gives a kind-2 object,
 * shrinks to 0.91 and is thrown sideways and up; a frame later it is restored to 1.1 of that
 * and its animation runs as it drops. Below the screen the look falls (8), event 0x45 is
 * marked for today and it is done. */
void SkyKind7_Run(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyVisitorVars *vars = sky_visitor_vars(object);
    if (vars->state == SKY_VISITOR_CROSSING) {
        if (SkyObjectKinds_Advance(object, SKY_KIND7_STEP, SKY_KIND7_SWAY, SKY_KIND7_PHASE_STEP)) {
            body->state = SKY_OBJECT_DONE;
        } else if (SkyShots_HitsBox(object, 0x1b000, 0x15000, 0)) {
            int resource = body->resource + 1;
            SkySlot_SetResource(sky_visitor_slot(object), (unsigned int) resource);
            body->resource = resource;
            SkyShots_StartLook7(&data_021fbaf0);
            SkyObjectKinds_PlayHeld(object, SKY_KIND7_HIT_SOUND);
            vars->state = SKY_VISITOR_HIT;
            vars->count = 0;
        } else if (CellAnim_Frame(&body->anim) == 0) {
            if (vars->count++ == 0) {
                SkyObjectKinds_PlayHeld(object, SKY_KIND7_SOUND);
            }
        } else {
            vars->count = 0;
        }
    } else if (vars->state == SKY_VISITOR_HIT) {
        body->animation = SKY_KIND7_HIT_ANIMATION;
        SkyObjectKinds_StartAnimation(object);
        CellAnim_Stop(&body->anim);
        body->velocity.x = body->forward != 0 ? 0x3c00 : -0x3c00;
        body->velocity.y = -0x4000;
        body->velocity.z = 0;
        SkyKind7_AddSparkle(&body->position, body->scale_x, body->velocity.x);
        body->scale_x = FX_MulFunc(body->scale_x, 0xe8c);
        body->scale_y = FX_MulFunc(body->scale_y, 0xe8c);
        vars->state = SKY_VISITOR_THROWN;
        vars->count = 0;
    } else if (vars->state == SKY_VISITOR_THROWN) {
        vars->count++;
        if (vars->count >= 1) {
            body->scale_x = FX_MulFunc(body->scale_x, 0x119a);
            body->scale_y = FX_MulFunc(body->scale_y, 0x119a);
            vars->state = SKY_VISITOR_DROPPING;
            vars->count = 0;
            CellAnim_Restart(&body->anim);
        }
    }
    if (vars->state >= SKY_VISITOR_DROPPING) {
        body->velocity.y += 0x59a;
        Vec_Scale(&body->velocity, 0x1000);
        VEC_Add(&body->position, &body->velocity, &body->position);
    }
    if (vars->state >= SKY_VISITOR_DROPPING && body->position.y > SKY_VISITOR_BOTTOM) {
        SkyShots_StartFall8(&data_021fbaf0);
        EventSchedule_MarkToday(SKY_KIND7_EVENT);
        body->state = SKY_OBJECT_DONE;
    }
    if (vars->state >= SKY_VISITOR_HIT) {
        SkyShots_SetHitPoint(&data_021fbaf0, (u32) body->position.x, (u32) body->position.y, (u32) body->scale_x,
                             sky_visitor_side(body));
    }
}
CLEAN_AS(func_020c0494, SkyKind7_Run)

/* func_020c0658: kind 7 set up: on its path (west to east with resource 0x28), its animation
 * and its state cleared. */
void SkyKind7_SetUp(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyVisitorVars *vars = sky_visitor_vars(object);
    SkyObjectKinds_StartPath(object, body->resource == SKY_KIND7_FORWARD_RESOURCE ? 1 : 0, SKY_KIND7_SWAY);
    body->animation = SKY_KIND7_ANIMATION;
    body->priority = SKY_VISITOR_PRIORITY;
    vars->state = SKY_VISITOR_CROSSING;
    vars->count = 0;
}
CLEAN_AS(func_020c0658, SkyKind7_SetUp)

/* func_020c0688: an object of kind 2 added at `at`, of size `scale`, moving sideways at half
 * of `speed`. */
void SkyKind7_AddSparkle(const Vec3 *at, fx32 scale, fx32 speed)
{
    SkyObjectBody *sparkle =
        (SkyObjectBody *) (void *) SkyObjects_Add(&data_021f8b48, SKY_OBJECT_KIND_2, SKY_ENTRY_ANY, at, 0);
    if (sparkle != NULL) {
        sparkle->scale_x = scale;
        sparkle->scale_y = scale;
        sparkle->velocity.x = FX_MulFunc(speed, 0x800);
        sparkle->velocity.y = 0;
        sparkle->velocity.z = 0;
    }
}
CLEAN_AS(func_020c0688, SkyKind7_AddSparkle)

/* func_020c06cc: kind 6 taken down. */
void SkyKind6_TakeDown(SkyObject *object)
{
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020c06cc, SkyKind6_TakeDown)

/* func_020c06d4: a frame of kind 6. Crossing it plays sound 0x7fb; when hit it takes resource
 * 0x24, plays sound 0x7fc and the look is started (4). It is then thrown sideways and up in
 * its animation 0x17, pulled down by 0.5 a frame; when that animation is done it takes resource
 * 0x25 and animation 0x18, starts giving off small objects, and falls with a drift, slowed by
 * drag. Below the screen it marks event 0x44 for today, has object 0x5020 placed at the
 * player's position (the lower first when it went west), the look falls (5) and it is done. */
void SkyKind6_Run(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyVisitorVars *vars = sky_visitor_vars(object);
    switch (vars->state) {
        case SKY_VISITOR_CROSSING:
            if (SkyObjectKinds_Advance(object, SKY_KIND6_STEP, SKY_KIND6_SWAY, SKY_KIND6_PHASE_STEP)) {
                body->state = SKY_OBJECT_DONE;
            } else if (SkyShots_HitsBox(object, 0x1a000, 0xc000, 0x5000)) {
                SkySlot_SetResource(sky_visitor_slot(object), SKY_KIND6_HIT_RESOURCE);
                body->resource = SKY_KIND6_HIT_RESOURCE;
                SkyObjectKinds_PlayHeld(object, SKY_KIND6_HIT_SOUND);
                SkyShots_StartLook4(&data_021fbaf0);
                vars->state = SKY_VISITOR_HIT;
            } else {
                SkyObjectKinds_Play(object, SKY_KIND6_SOUND);
            }
            break;
        case SKY_VISITOR_HIT:
            body->animation = SKY_KIND6_THROWN_ANIMATION;
            SkyObjectKinds_StartAnimation(object);
            body->velocity.x = body->forward != 0 ? 0x2666 : -0x2666;
            body->velocity.y = -0x399a;
            body->velocity.z = 0;
            vars->state = SKY_VISITOR_THROWN;
            break;
        case SKY_VISITOR_THROWN:
            if (CellAnim_IsDone(&body->anim)) {
                SkySlot_SetResource(sky_visitor_slot(object), SKY_KIND6_FALL_RESOURCE);
                body->resource = SKY_KIND6_FALL_RESOURCE;
                vars->state = SKY_VISITOR_TURNING;
                vars->count = 1;
            }
            break;
        case SKY_VISITOR_TURNING:
            body->animation = SKY_KIND6_FALL_ANIMATION;
            SkyObjectKinds_StartAnimation(object);
            vars->state = SKY_VISITOR_FALLING;
            vars->unk_68 = 0;
            break;
        case SKY_VISITOR_FALLING:
            if (body->position.y > SKY_VISITOR_BOTTOM) {
                EventSchedule_MarkToday(SKY_KIND6_EVENT);
                EventBuildings_Place5020(PlayerActorOps_StartPosition(PlayerActors_OwnPlayer()), body->forward == 0 ? 1 : 0);
                SkyShots_StartFall5(&data_021fbaf0);
                body->state = SKY_OBJECT_DONE;
            }
            break;
        default:
            break;
    }
    if (vars->state >= SKY_VISITOR_THROWN) {
        Vec3 pull = data_021fbee8;
        fx32 keep;
        if (vars->state >= SKY_VISITOR_FALLING) {
            pull.x = body->forward != 0 ? 0x19a : -0x19a;
            pull.y = 0x19a;
            keep = 0xfd7;
        } else {
            pull.y = 0x800;
            keep = 0x1000;
        }
        VEC_Add(&body->velocity, &pull, &body->velocity);
        Vec_Scale(&body->velocity, keep);
        VEC_Add(&body->position, &body->velocity, &body->position);
    }
    if (vars->state >= SKY_VISITOR_HIT) {
        SkyShots_SetHitPoint(&data_021fbaf0, (u32) body->position.x, (u32) body->position.y, (u32) body->scale_x,
                             sky_visitor_side(body));
    }
    SkyKind6_Sparkle(object);
}
CLEAN_AS(func_020c06d4, SkyKind6_Run)

/* func_020c08b8: kind 6 set up: on its path, west to east or back at random; flag 9 of the
 * state block set. */
void SkyKind6_SetUp(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyVisitorVars *vars = sky_visitor_vars(object);
    SkyObjectKinds_StartPath(object, MainRandom_Below(2) == 0 ? 1 : 0, SKY_KIND6_SWAY);
    body->animation = SKY_KIND6_ANIMATION;
    body->priority = SKY_VISITOR_PRIORITY;
    StateBlock_SetFlag((u32 *) (void *) &data_021dc7a8, SKY_KIND6_STATE_FLAG);
    vars->state = SKY_VISITOR_CROSSING;
    vars->count = 0;
    vars->unk_68 = 0;
}
CLEAN_AS(func_020c08b8, SkyKind6_SetUp)

/* func_020c08fc: once started, every one or two frames more an object of kind 2 (look 2 or
 * 3) of the object's size, at a random angle and a random distance below 16 pixels (by the
 * object's size) from it. */
void SkyKind6_Sparkle(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyVisitorVars *vars = sky_visitor_vars(object);
    int count = vars->count;
    if (count <= 0) {
        return;
    }
    if (count != 1) {
        vars->count = count - 1;
        return;
    }
    vars->count = (s32) MainRandom_Below(2) + 1;
    u32 look = MainRandom_Below(2) + 2;
    fx32 size = body->scale_x;
    fx32 distance = FX_Div((fx32) (MainRandom_Below(0x10) << 12), size);
    int index = ((u16) MainRandom_Below(0x10000) >> 4) * 2;
    fx32 y = body->position.y + FX_MulFunc(distance, FX_SinCosTable_[index]);
    Vec3 at;
    at.x = body->position.x + FX_MulFunc(distance, FX_SinCosTable_[index + 1]);
    at.y = y;
    at.z = 0;
    SkyObjectBody *sparkle =
        (SkyObjectBody *) (void *) SkyObjects_Add(&data_021f8b48, SKY_OBJECT_KIND_2, SKY_ENTRY_ANY, &at, (int) (look & 0xf));
    if (sparkle != NULL) {
        sparkle->scale_x = size;
        sparkle->scale_y = size;
    }
}
CLEAN_AS(func_020c08fc, SkyKind6_Sparkle)

/* func_020c09a8: kind 5 taken down. */
void SkyKind5_TakeDown(SkyObject *object)
{
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020c09a8, SkyKind5_TakeDown)

/* func_020c09b0: a frame of kind 5. Crossing it plays sound 0x7f7; when hit its resource moves
 * on by one, the look is started (2, with its variant) and sound 0x7f8 plays. Then it takes
 * animation 0 and falls straight down, slowed by drag; below the screen the look drops (3) and
 * it is done. */
void SkyKind5_Run(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyVisitorVars *vars = sky_visitor_vars(object);
    if (vars->state == SKY_VISITOR_CROSSING) {
        if (SkyObjectKinds_Advance(object, SKY_KIND5_STEP, SKY_KIND5_SWAY, SKY_KIND5_PHASE_STEP)) {
            body->state = SKY_OBJECT_DONE;
        } else if (SkyShots_HitsBox(object, 0xe000, 0x1a000, -0x3000)) {
            int resource = body->resource + 1;
            SkySlot_SetResource(sky_visitor_slot(object), (unsigned int) resource);
            body->resource = resource;
            SkyShots_StartLook2(&data_021fbaf0, vars->count != 0 ? 1 : 0);
            SkyObjectKinds_PlayHeld(object, SKY_KIND5_HIT_SOUND);
            vars->state = SKY_VISITOR_HIT;
        } else {
            SkyObjectKinds_Play(object, SKY_KIND5_SOUND);
        }
    } else if (vars->state == SKY_VISITOR_HIT) {
        body->animation = SKY_KIND5_HIT_ANIMATION;
        SkyObjectKinds_StartAnimation(object);
        body->velocity.x = 0;
        body->velocity.y = -0x800;
        body->velocity.z = 0;
        vars->state = SKY_VISITOR_THROWN;
        vars->unk_68 = 0;
    } else {
        body->velocity.y += 0x666;
        body->velocity.y = FX_MulFunc(body->velocity.y, 0xfd7);
        VEC_Add(&body->position, &body->velocity, &body->position);
        if (body->position.y > SKY_VISITOR_BOTTOM) {
            SkyShots_StartDrop3(&data_021fbaf0);
            body->state = SKY_OBJECT_DONE;
        }
    }
    if (vars->state >= SKY_VISITOR_HIT) {
        SkyShots_SetHitPoint(&data_021fbaf0, (u32) body->position.x, (u32) body->position.y, (u32) body->scale_x,
                             sky_visitor_side(body));
    }
}
CLEAN_AS(func_020c09b0, SkyKind5_Run)

/* func_020c0ad4: kind 5 set up: on its path, west to east or back at random; its variant is
 * bit 0 of the parameter. */
void SkyKind5_SetUp(SkyObject *object, int param)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyVisitorVars *vars = sky_visitor_vars(object);
    SkyObjectKinds_StartPath(object, MainRandom_Below(2) == 0 ? 1 : 0, SKY_KIND5_START_SWAY);
    body->animation = SKY_KIND5_ANIMATION;
    body->priority = SKY_VISITOR_PRIORITY;
    vars->state = SKY_VISITOR_CROSSING;
    vars->count = (param & 1) != 0 ? 1 : 0;
    vars->unk_68 = 0;
}
CLEAN_AS(func_020c0ad4, SkyKind5_SetUp)
