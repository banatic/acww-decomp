/* The room object of /roomObj/obj_tailor1 and obj_tailor2 (tailor_object.h). */
#include "tailor_object.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/matrix.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/date_random.h"
#include "main/ease_curve.h"
#include "main/frame_ctrl.h"
#include "main/item_lists.h"
#include "main/item_texture.h"
#include "main/model_object.h"
#include "main/overlay_groups.h"
#include "member_pointer.h"
#include "ov004/rmo_model.h"
#include "ov004/rmo_object_slots.h"
#include "rmo_object_base.h"

static_assert(offsetof(TailorObject, part) == 0x290, "part");
static_assert(offsetof(TailorObject, part_model) == 0x348, "part model");
static_assert(offsetof(TailorObject, part_texture) == 0x3ec, "part texture");
static_assert(offsetof(TailorObject, part.frames.frame) == 0x334, "part frame");

#define TAILOR_OBJECT_FRAME_SHIFT 12 /* frames are 20.12 fixed point */

/* The one that exists, NULL for none. */
extern TailorObject *data_ov004_02258558;

/* func_ov004_0222fd38: the frame the second model's animation is at, as a whole frame cut to 16
 * bits; 0 when none exists. */
int TailorObject_PartFrame(void)
{
    TailorObject *self = data_ov004_02258558;
    if (self != NULL) {
        return (u16) ((u32) self->part.frames.frame >> TAILOR_OBJECT_FRAME_SHIFT);
    }
    return 0;
}
CLEAN_AS(func_ov004_0222fd38, TailorObject_PartFrame)

/* func_ov004_0222fd58: the second model's animation put at whole frame `frame`; nothing when
 * none exists. */
void TailorObject_SetPartFrame(int frame)
{
    TailorObject *self = data_ov004_02258558;
    if (self != NULL) {
        self->part.frames.frame = (fx32) ((u32) frame << TAILOR_OBJECT_FRAME_SHIFT);
    }
}
CLEAN_AS(func_ov004_0222fd58, TailorObject_SetPartFrame)

/* func_ov004_0222fd70: whether one exists with its state byte at 0 or 3. */
int TailorObject_InState0Or3(void)
{
    TailorObject *self = data_ov004_02258558;
    if (self != NULL) {
        u8 state = self->base.unk_24c[0];
        if (state == 3 || state == 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0222fd70, TailorObject_InState0Or3)

/* The rest of its class. */

static_assert(offsetof(TailorObject, part.object.model) == 0x2ec, "part model resource");
static_assert(offsetof(TailorObject, cloth_copy) == 0x3f0, "cloth copy");
static_assert(offsetof(TailorObject, body_anim) == 0x418, "body animation");
static_assert(offsetof(TailorObject, stop_time) == 0x43c, "stop time");
static_assert(sizeof(TailorObject) == 0x440, "the size TailorObject_Create allocates");
static_assert(offsetof(RmoObject, body.frames.speed) == 0x198, "body speed");
static_assert(offsetof(RmoObject, body.object.model) == 0x148, "body model resource");
static_assert(sizeof(DatedRandom) == 0x0c, "DatedRandom size");
static_assert(sizeof(ItemList) == 0x08, "ItemList size");

#define TAILOR_OBJECT_ONE 0x1000 /* normal speed, 20.12 fixed point */
#define TAILOR_OBJECT_LOOP 0     /* FrameCtrlFlags: the animations start over at their end */

/* The vtable slot that enters a state (TailorObject_SetState for this class). */
#define TAILOR_OBJECT_SLOT_SET_STATE 0x60

/* TAILOR_OBJECT_RUNNING: the part's animation turns every 56 whole frames; its sound plays in
 * frames 17 to 52 of each turn. */
#define TAILOR_OBJECT_TURN_FRAMES 0x38
#define TAILOR_OBJECT_SOUND_FIRST 0x11
#define TAILOR_OBJECT_SOUND_LAST 0x34
#define TAILOR_OBJECT_SOUND 0x85e

/* TAILOR_OBJECT_STOPPING: the speed is 1 minus the eased share (EaseCurve_Share) of 40 frames
 * gone, rising and falling over 10 frames each. */
#define TAILOR_OBJECT_STOP_FRAMES 0x28000
#define TAILOR_OBJECT_STOP_EASE 0xa000

/* The cloth: an item of list kind 2, group 0, drawn filtered and turned (ItemLists_Draw); its
 * texture goes over the part's material as texture 0 with palette 0. */
#define TAILOR_OBJECT_CLOTH_KIND 2
#define TAILOR_OBJECT_CLOTH_GROUP 0
#define TAILOR_OBJECT_CLOTH_FILTER 1
#define TAILOR_OBJECT_CLOTH_TURN 1

/* The class's vtable. */
extern const u8 data_ov004_02255538[];

/* The archives: "/roomObj/obj_tailor1.arc" and ".nsbtx", "/roomObj/obj_tailor2.arc" and
 * ".nsbtx"; "w", the part's material the cloth goes on. */
extern const char data_ov004_022555a0[], data_ov004_022555bc[], data_ov004_022555d8[], data_ov004_022555f4[];
extern const char data_ov004_02255610[];

/* The cloth's texture file. */
extern DesignModel data_ov004_022585ac;

/* The scratch matrix the game builds model matrices in. */
extern Mtx43 data_021fbe48;
extern Heap *data_021c9b24;

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02258554;
extern MemberPointer data_ov004_0225856c[TAILOR_OBJECT_STATE_COUNT];
extern const MemberPointer data_ov004_022554e8, data_ov004_022554e0, data_ov004_022554f0, data_ov004_022554f8;
extern u32 data_ov004_0225855c;
extern MemberPointer data_ov004_0225858c[TAILOR_OBJECT_STATE_COUNT];
extern const MemberPointer data_ov004_022554d8, data_ov004_02255510, data_ov004_02255508, data_ov004_02255500;

/* The RMO family's base class and holders (rmo_object.h). */

extern int NNS_G3dBindMdlTex(u8 *model, void *texture);
extern int NNS_G3dBindMdlPltt(u8 *model, void *texture);

static AnimatedModel *TailorObject_body(TailorObject *self)
{
    return (AnimatedModel *) (void *) &self->base.body;
}

static AnimatedModel *TailorObject_part(TailorObject *self)
{
    return (AnimatedModel *) (void *) &self->part;
}

static u8 *TailorObject_state(TailorObject *self)
{
    return &self->base.unk_24c[0];
}

static void *TailorObject_sound_source(TailorObject *self)
{
    return &self->base.unk_24c[4];
}

static Mtx43 *TailorObject_matrix(RmoAnimatedModel *model)
{
    return (Mtx43 *) (void *) model->object.unk_64;
}

/* Vtable slot 0x60 (TailorObject_SetState for this class), called through the vtable. */
static int TailorObject_call_set_state(TailorObject *self, unsigned int state)
{
    const u32 *vtable = self->base.actor.vtable;
    return ((int (*)(TailorObject *, unsigned int))(uintptr_t) vtable[TAILOR_OBJECT_SLOT_SET_STATE / 4])(self, state);
}

/* func_ov004_0222fd94: the one that exists stopping (through vtable slot 0x60); whether it
 * did, 0 when none exists. */
int TailorObject_StopCurrent(void)
{
    TailorObject *self = data_ov004_02258558;
    if (self != NULL) {
        return TailorObject_call_set_state(self, TAILOR_OBJECT_STOPPING);
    }
    return 0;
}
CLEAN_AS(func_ov004_0222fd94, TailorObject_StopCurrent)

/* func_ov004_0222fdb8: the one that exists starting to run (through vtable slot 0x60); whether
 * it did, 0 when none exists. */
int TailorObject_RunCurrent(void)
{
    TailorObject *self = data_ov004_02258558;
    if (self != NULL) {
        return TailorObject_call_set_state(self, TAILOR_OBJECT_STARTING);
    }
    return 0;
}
CLEAN_AS(func_ov004_0222fdb8, TailorObject_RunCurrent)

/* func_ov004_0222fddc (update of TAILOR_OBJECT_STOPPING): the body and its animation slowed
 * down along an eased curve, one frame further each time; idle (through vtable slot 0x60) once
 * their speed is 0. */
void TailorObject_UpdateStopping(TailorObject *self)
{
    fx32 speed = TAILOR_OBJECT_ONE - EaseCurve_Share(self->stop_time, 0, TAILOR_OBJECT_STOP_FRAMES, TAILOR_OBJECT_STOP_EASE,
                                                     TAILOR_OBJECT_STOP_EASE);
    self->base.body.frames.speed = speed;
    self->body_anim.ctrl.speed = speed;
    self->stop_time += TAILOR_OBJECT_ONE;
    if (speed == 0) {
        TailorObject_call_set_state(self, TAILOR_OBJECT_IDLE);
    }
}
CLEAN_AS(func_ov004_0222fddc, TailorObject_UpdateStopping)

/* func_ov004_0222fe38 (entry of TAILOR_OBJECT_STOPPING): the part stands still at once; the
 * slowing down starts from time 0. */
int TailorObject_EnterStopping(TailorObject *self)
{
    self->part.frames.speed = 0;
    self->stop_time = 0;
    return 1;
}
CLEAN_AS(func_ov004_0222fe38, TailorObject_EnterStopping)

/* func_ov004_0222fe50 (update of TAILOR_OBJECT_RUNNING): the part's sound played while its
 * frame is within frames 17 to 52 of a turn of 56 frames, unless func_02070070 answers that
 * main's two values are set. */
void TailorObject_UpdateRunning(TailorObject *self)
{
    /* QUIRK: the whole frame is cut to 16 bits */
    u32 frame = (u16) ((u32) self->part.frames.frame >> TAILOR_OBJECT_FRAME_SHIFT);
    int in_turn = (int) (frame % TAILOR_OBJECT_TURN_FRAMES);
    if (Math_IsBetween(in_turn, TAILOR_OBJECT_SOUND_FIRST, TAILOR_OBJECT_SOUND_LAST) && OverlayGroups_HasOwner() == 0) {
        RmoSound_PlayEx(TailorObject_sound_source(self), TAILOR_OBJECT_SOUND);
    }
}
CLEAN_AS(func_ov004_0222fe50, TailorObject_UpdateRunning)

/* func_ov004_0222fea8 (entry of TAILOR_OBJECT_RUNNING) */
int TailorObject_EnterRunning(TailorObject *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_ov004_0222fea8, TailorObject_EnterRunning)

/* func_ov004_0222feac (update of TAILOR_OBJECT_STARTING): the body and its animation at normal
 * speed, then running (through vtable slot 0x60). */
void TailorObject_UpdateStarting(TailorObject *self)
{
    self->base.body.frames.speed = TAILOR_OBJECT_ONE;
    self->body_anim.ctrl.speed = TAILOR_OBJECT_ONE;
    TailorObject_call_set_state(self, TAILOR_OBJECT_RUNNING);
}
CLEAN_AS(func_ov004_0222feac, TailorObject_UpdateStarting)

/* func_ov004_0222fed4 (entry of TAILOR_OBJECT_STARTING): the part at normal speed. */
int TailorObject_EnterStarting(TailorObject *self)
{
    self->part.frames.speed = TAILOR_OBJECT_ONE;
    self->stop_time = 0;
    return 1;
}
CLEAN_AS(func_ov004_0222fed4, TailorObject_EnterStarting)

/* func_ov004_0222fef0 (update of TAILOR_OBJECT_IDLE): nothing. */
void TailorObject_UpdateIdle(TailorObject *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0222fef0, TailorObject_UpdateIdle)

/* func_ov004_0222fef4 (entry of TAILOR_OBJECT_IDLE) */
int TailorObject_EnterIdle(TailorObject *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_ov004_0222fef4, TailorObject_EnterIdle)

/* _ZN18Obj_ov004_0225553819func_ov004_0222fef8Ev: the state's update, through its table; a
 * state byte of 4 or more runs none. */
void TailorObject_UpdateState(TailorObject *self)
{
    static const MemberPointer *const updates[TAILOR_OBJECT_STATE_COUNT] = {
        &data_ov004_022554e8, /* TailorObject_UpdateIdle */
        &data_ov004_022554e0, /* TailorObject_UpdateStarting */
        &data_ov004_022554f0, /* TailorObject_UpdateRunning */
        &data_ov004_022554f8, /* TailorObject_UpdateStopping */
    };
    MemberTable_InitOnce(&data_ov004_02258554, data_ov004_0225856c, updates, TAILOR_OBJECT_STATE_COUNT);
    u8 state = *TailorObject_state(self);
    if (state < TAILOR_OBJECT_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_0225856c[state], self);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225553819func_ov004_0222fef8Ev, TailorObject_UpdateState)

/* func_ov004_0222ff84 (vtable slot 0x60): enters `state` if its entry (through a table)
 * agrees; whether it did. States 4 and above do not exist. */
int TailorObject_SetState(TailorObject *self, unsigned int state)
{
    static const MemberPointer *const entries[TAILOR_OBJECT_STATE_COUNT] = {
        &data_ov004_022554d8, /* TailorObject_EnterIdle */
        &data_ov004_02255510, /* TailorObject_EnterStarting */
        &data_ov004_02255508, /* TailorObject_EnterRunning */
        &data_ov004_02255500, /* TailorObject_EnterStopping */
    };
    MemberTable_InitOnce(&data_ov004_0225855c, data_ov004_0225858c, entries, TAILOR_OBJECT_STATE_COUNT);
    if (state < TAILOR_OBJECT_STATE_COUNT && MemberPointer_CallInt(&data_ov004_0225858c[state], self) != 0) {
        *TailorObject_state(self) = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0222ff84, TailorObject_SetState)

/* func_ov004_02230020 (vtable slot 0x0c): both archives and the part's textures released; no
 * longer the one that exists. */
int TailorObject_Release(TailorObject *self)
{
    RmoObjectSlots_ReleaseBody(&self->base);
    RmoModel_Release(&self->part_model);
    RmoTexture_Release(&self->part_texture);
    data_ov004_02258558 = NULL;
    return 1;
}
CLEAN_AS(func_ov004_02230020, TailorObject_Release)

/* func_ov004_02230054 (vtable slot 0x24): both models drawn. */
int TailorObject_Draw(TailorObject *self)
{
    AnimatedModel_Draw(TailorObject_body(self), NULL);
    AnimatedModel_Draw(TailorObject_part(self), NULL);
    return 1;
}
CLEAN_AS(func_ov004_02230054, TailorObject_Draw)

/* func_ov004_02230078 (vtable slot 0x18): the animations step (the body's texture animation
 * shows its frame control's frame), both models placed at its position (built in the scratch
 * matrix data_021fbe48), then the state's update. */
int TailorObject_Update(TailorObject *self)
{
    AnimatedModel_StepFrames(TailorObject_body(self));
    AnimatedModel_StepFrames(TailorObject_part(self));
    FrameCtrl_Step(&self->body_anim.ctrl);
    self->body_anim.anim->frame = self->body_anim.ctrl.frame;
    const Vec3 *position = &self->base.actor.position;
    Mtx43_Translation(&data_021fbe48, position->x, position->y, position->z);
    *TailorObject_matrix(&self->base.body) = data_021fbe48;
    *TailorObject_matrix(&self->part) = data_021fbe48;
    TailorObject_UpdateState(self);
    return 1;
}
CLEAN_AS(func_ov004_02230078, TailorObject_Update)

/* func_ov004_022300fc (vtable slot 0x00): becomes the one that exists, loads both archives and
 * binds the part's textures. When the body's archive has a first joint animation the body can
 * take, the body loops it, standing still at its first frame; so does the body's first texture
 * animation when the body takes one, and the part its first joint animation. Then today's cloth
 * is drawn and its texture queued over the part's material "w", and the idle state's entry runs
 * (the state byte stays as the allocation zeroed it).
 * QUIRK: the joint animations are asked for twice. */
int TailorObject_Start(TailorObject *self)
{
    DatedRandom random;
    ItemList list;
    ItemCode cloth;
    u8 *model;

    data_ov004_02258558 = self;
    RmoObjectSlots_Load(&self->base, data_ov004_022555a0, data_ov004_022555bc);
    RmoModel_Load(&self->part_model, data_ov004_022555d8);
    RmoTexture_Load(&self->part_texture, data_ov004_022555f4);
    ModelObject_SetModel(&self->part.object, RmoModel_Model(&self->part_model), NULL);
    model = RmoModel_Model(&self->part_model);
    NNS_G3dBindMdlTex(model, RmoTexture_Texture(&self->part_texture));
    model = RmoModel_Model(&self->part_model);
    NNS_G3dBindMdlPltt(model, RmoTexture_Texture(&self->part_texture));

    if (RmoModel_JointAnim(&self->base.body_model, 0) != NULL &&
        AnimatedModel_LoadAnim(TailorObject_body(self), data_021c9b24) != 0) {
        AnimatedModel_Start(TailorObject_body(self), RmoModel_JointAnim(&self->base.body_model, 0), TAILOR_OBJECT_LOOP,
                            TAILOR_OBJECT_ONE, 0, 0);
        AnimatedModel_Attach(TailorObject_body(self));
        self->base.body.frames.speed = 0;
    }
    if (ModelAnim_AllocMaterialAnim(&self->body_anim, self->base.body.object.model, data_021c9b24) != 0) {
        ModelAnim_Start(&self->body_anim, RmoModel_TextureAnim(&self->base.body_model, 0), TAILOR_OBJECT_LOOP,
                        TAILOR_OBJECT_ONE, 0);
        ModelAnim_Attach(&self->body_anim, ModelObject_RenderObject(&self->base.body.object));
        self->body_anim.ctrl.speed = 0;
    }
    if (RmoModel_JointAnim(&self->part_model, 0) != NULL &&
        AnimatedModel_LoadAnim(TailorObject_part(self), data_021c9b24) != 0) {
        AnimatedModel_Start(TailorObject_part(self), RmoModel_JointAnim(&self->part_model, 0), TAILOR_OBJECT_LOOP,
                            TAILOR_OBJECT_ONE, 0, 0);
        AnimatedModel_Attach(TailorObject_part(self));
        self->part.frames.speed = 0;
    }

    DatedRandom_Construct(&random);
    ItemList_Construct(&list, TAILOR_OBJECT_CLOTH_KIND, TAILOR_OBJECT_CLOTH_GROUP);
    ItemLists_Draw(&cloth, &list, 0, (int) (intptr_t) &random, TAILOR_OBJECT_CLOTH_FILTER, TAILOR_OBJECT_CLOTH_TURN, 0);
    ItemList_Destruct(&list);
    ClothTexture_Load(&data_ov004_022585ac, &cloth, NULL);
    model = self->part.object.model;
    VramCopyMaterial_Queue(&self->cloth_copy, model, data_ov004_02255610, ClothTexture_Textures(&data_ov004_022585ac), 0, 0);
    TailorObject_EnterIdle(self);
    DatedRandom_Destruct(&random);
    return 1;
}
CLEAN_AS(func_ov004_022300fc, TailorObject_Start)

/* The part's holders and the body's animation taken down, then the base class. The cloth's
 * copy task gets no destructor. */
static void TailorObject_destruct(TailorObject *self)
{
    self->base.actor.vtable = data_ov004_02255538;
    ModelAnim_DestructComplete(&self->body_anim);
    RmoTexture_Destruct(&self->part_texture);
    RmoModel_Destruct(&self->part_model);
    AnimatedModel_DestructComplete(TailorObject_part(self));
    RmoObjectSlots_Destruct(&self->base);
}

/* func_ov004_022302f8 (the deleting destructor, vtable slot 0x44) */
TailorObject *TailorObject_Delete(TailorObject *self)
{
    TailorObject_destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_022302f8, TailorObject_Delete)

/* func_ov004_02230348 (the destructor, vtable slot 0x40) */
TailorObject *TailorObject_Destruct(TailorObject *self)
{
    TailorObject_destruct(self);
    return self;
}
CLEAN_AS(func_ov004_02230348, TailorObject_Destruct)

/* func_ov004_02230394 (the constructor). Its state is left as the allocation zeroed it. */
TailorObject *TailorObject_Construct(TailorObject *self)
{
    RmoObjectBase_Construct(&self->base);
    self->base.actor.vtable = data_ov004_02255538;
    AnimatedModel_Construct(TailorObject_part(self));
    RmoModel_Construct(&self->part_model);
    RmoTexture_Construct(&self->part_texture);
    VramCopyMaterial_Construct(&self->cloth_copy);
    ModelAnim_Construct(&self->body_anim);
    return self;
}
CLEAN_AS(func_ov004_02230394, TailorObject_Construct)

/* func_ov004_022303e8: a new one from the room's heap; nothing when it has no room. */
void TailorObject_Create(void)
{
    TailorObject *self = Heap_AllocAuxZeroed(sizeof(TailorObject));
    if (self != NULL) {
        TailorObject_Construct(self);
    }
}
CLEAN_AS(func_ov004_022303e8, TailorObject_Create)
