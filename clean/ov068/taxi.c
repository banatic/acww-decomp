/* The taxi of overlay 68 (taxi.h). */
#include "taxi.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/frame_ctrl.h"
#include "main/g3d_resource.h"
#include "main/model_object.h"
#include "main/sound.h"
#include "ov004/member_pointer.h"

static_assert(offsetof(RmoObject, body) == 0xec, "body");
static_assert(offsetof(RmoObject, body_model) == 0x1a4, "body model");
static_assert(sizeof(RmoObject) == 0x290, "RmoObject size");
static_assert(sizeof(ModelAnim) == 0x20, "ModelAnim size");
static_assert(offsetof(Taxi, material_anim) == 0x290, "material anim");
static_assert(offsetof(Taxi, texture_anim) == 0x2b0, "texture anim");
static_assert(offsetof(Taxi, figure) == 0x2d0, "figure");
static_assert(offsetof(Taxi, figure_model) == 0x388, "figure model");
static_assert(offsetof(Taxi, figure_texture) == 0x42c, "figure texture");
static_assert(offsetof(Taxi, figure_plays) == 0x430, "figure plays");
static_assert(offsetof(Taxi, handle) == 0x434, "handle");
static_assert(offsetof(Taxi, handle_model) == 0x4ec, "handle model");
static_assert(offsetof(Taxi, handle_texture) == 0x590, "handle texture");
static_assert(offsetof(Taxi, state) == 0x594, "state");
static_assert(offsetof(Taxi, frames) == 0x598, "frames");
static_assert(offsetof(Taxi, alpha) == 0x59a, "alpha");
static_assert(offsetof(Taxi, materials) == 0x59c, "materials");
static_assert(sizeof(Taxi) == 0x5a4, "the size func_ov068_02273904 allocates");

#define TAXI_ONE 0x1000 /* normal speed, 20.12 fixed point */
#define TAXI_LOOP 0     /* FrameCtrlFlags: the animation starts over at its end */
#define TAXI_ONCE FRAME_CTRL_ONCE
#define TAXI_RAIN_ALPHA 31 /* the rain materials' alpha in state 0 */
#define TAXI_RAIN_STEP 3   /* state 1: frames per step of the alpha */
#define TAXI_SOUND_A 0x884 /* the sounds that run while it exists */
#define TAXI_SOUND_B 0x885
#define TAXI_SOUND_FRAME_0 0x886 /* at frame 0 of the car's animation */
#define TAXI_SOUND_FRAME_1C 0x887
#define TAXI_SOUND_FRAME 0x1c
#define TAXI_SOUND_FADE 1

/* Overlay 51's speaker's animations and the handle's animation for each. */
#define TAXI_SPEAKER_ANIM_0 0xfb
#define TAXI_SPEAKER_ANIM_1 0x8d
#define TAXI_SPEAKER_ANIM_2 0x8e
#define TAXI_SPEAKER_ANIM_3 0x8f
#define TAXI_SPEAKER_ANIM_4 0x90
#define TAXI_SPEAKER_ANIM_5 0x91

/* The model command whose hook it sets (NitroSystem's NNS_G3D_SBC_MAT), run at timing B. */
#define TAXI_COMMAND_MAT 4
#define TAXI_TIMING_B 2

/* The state of the model being drawn (NitroSystem's NNSG3dRS), as ov004/museum_display.h
 * describes it. */
typedef struct TaxiRenderState {
    const u8 *command; /* the command being run: byte 1 is its material */
    void *render_object;
    u32 flags;
    u32 hooks[0x20]; /* the address of each command's hook, 0 for none */
    u8 hook_timings[0x20];
} TaxiRenderState;

/* The model being drawn (NitroSystem's NNSG3dRenderObj): its user word is the taxi, set by
 * ModelObject_SetInitHook in Taxi_Start. */
typedef struct TaxiRenderObject {
    u8 unk_00[0x2c];
    Taxi *user; /* 0x2c */
} TaxiRenderObject;

static_assert(offsetof(TaxiRenderState, hooks) == 0x0c, "hooks");
static_assert(offsetof(TaxiRenderState, hook_timings) == 0x8c, "hook timings");

/* The class's vtable. */
extern const u8 data_ov068_022778f4[];

/* The one that exists, NULL for none. */
extern Taxi *data_ov068_022787fc;

/* "obj_taxi", "obj_taxi_fig" and "obj_taxi_hdl", the archives; "m_rainA", "m_rainB" and
 * "m_splash", the rain materials. */
extern const char data_ov068_0227795c[], data_ov068_02277968[], data_ov068_02277978[];
extern const char data_ov068_02277988[], data_ov068_02277990[], data_ov068_02277998[];

extern Heap *data_021c9b24;

/* The state tables (ov004/member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov068_02278804;
extern MemberPointer data_ov068_02278808[TAXI_STATES];
extern const MemberPointer data_ov068_022778bc, data_ov068_022778ac, data_ov068_022778b4;
extern u32 data_ov068_02278800;
extern MemberPointer data_ov068_02278820[TAXI_STATES];
extern const MemberPointer data_ov068_022778a4, data_ov068_022778cc, data_ov068_022778c4;

/* The RMO family's base class and holders (ov004/rmo_object.h): loading the body's archive and
 * another archive into a part, releasing them, the joint, material and texture animations of an
 * index (NULL for none), the constructor and destructor and those of the holders. */
extern int func_ov004_0222c5c8(RmoObject *object, const char *name);
extern int func_ov004_0222c62c(const char *name, RmoAnimatedModel *model, RmoModel *source, RmoTexture *texture);
extern void func_ov004_0222c598(RmoObject *object);
extern void func_ov004_0222c5b4(RmoModel *source, RmoTexture *texture);
extern const u8 *func_ov004_0222c3c4(RmoModel *model, int index);
extern const u8 *func_ov004_0222c3b4(RmoModel *model, int index);
extern const u8 *func_ov004_0222c3a4(RmoModel *model, int index);
extern RmoObject *func_ov004_0222c87c(RmoObject *object);
extern RmoObject *func_ov004_0222c7a0(RmoObject *object);
extern RmoModel *func_ov004_0222c548(RmoModel *model);
extern RmoModel *func_ov004_0222c538(RmoModel *model);
extern void func_ov004_0222c398(RmoTexture *texture);
extern void func_ov004_0222c394(RmoTexture *texture);

/* Overlay 51's speaker: its animation's number, and its frame. */
extern int func_ov051_02260474(void);
extern unsigned int func_ov051_02260490(void);

extern void NNS_G3dMdlSetMdlAlpha(u8 *model, int material, u8 alpha);

/* The hooks are the game's functions: their addresses go to the model. */
extern void func_ov068_022738d8(TaxiRenderState *state);
extern void func_ov068_022738e8(TaxiRenderState *state);

static AnimatedModel *animated(RmoAnimatedModel *model)
{
    return (AnimatedModel *) (void *) model;
}

/* func_ov068_02272fe8: the animation `anim` of `source` started on `model` unless the model
 * plays it already. */
void Taxi_PlayPartAnim(Taxi *self, int anim, RmoAnimatedModel *model, RmoModel *source, u8 flags, fx32 speed, u16 start,
                       u16 frames)
{
    (void) self;
    if (AnimatedModel_AnimFile(animated(model)) != func_ov004_0222c3c4(source, anim)) {
        AnimatedModel_Start(animated(model), func_ov004_0222c3c4(source, anim), flags, speed, start, frames);
    }
}
CLEAN_AS(func_ov068_02272fe8, Taxi_PlayPartAnim)

/* func_ov068_0227302c (what Taxi_MaterialHook calls for each material drawn): nothing. */
void Taxi_OnMaterial(void) {}
CLEAN_AS(func_ov068_0227302c, Taxi_OnMaterial)

/* func_ov068_02273030: the figure's first animation played once from its start, and stepped
 * from now on; 1, or 0 without a taxi. */
int Taxi_StartFigure(void)
{
    Taxi *self = data_ov068_022787fc;
    if (self == NULL) {
        return 0;
    }
    self->figure_plays = 1;
    AnimatedModel_Start(animated(&self->figure), func_ov004_0222c3c4(&self->figure_model, 0), TAXI_ONCE, TAXI_ONE, 0, 0);
    return 1;
}
CLEAN_AS(func_ov068_02273030, Taxi_StartFigure)

/* func_ov068_02273088: state 1 (the rain ends) and whether it was taken; 1 without a taxi. */
int Taxi_StopRain(void)
{
    Taxi *self = data_ov068_022787fc;
    if (self != NULL) {
        return Taxi_SetState(self, 1);
    }
    return 1;
}
CLEAN_AS(func_ov068_02273088, Taxi_StopRain)

/* func_ov068_022730a8 (update of state 2) */
void Taxi_UpdateDry(void) {}
CLEAN_AS(func_ov068_022730a8, Taxi_UpdateDry)

/* func_ov068_022730ac (entry of state 2): alpha 0, the car's animations played once. */
int Taxi_EnterDry(Taxi *self)
{
    self->alpha = 0;
    Taxi_RestartCar(self, TAXI_ONCE);
    return 1;
}
CLEAN_AS(func_ov068_022730ac, Taxi_EnterDry)

/* func_ov068_022730c8 (update of state 1): the car's sounds; every third frame, while the alpha
 * is not below 0, it goes down by one, and at 0 state 2 follows. */
void Taxi_UpdateRainEnds(Taxi *self)
{
    Taxi_PlaySounds(self);
    if (self->frames % TAXI_RAIN_STEP == 0 && self->alpha >= 0) {
        self->alpha--;
        if (self->alpha == 0) {
            Taxi_SetState(self, 2);
        }
    }
    self->frames++;
}
CLEAN_AS(func_ov068_022730c8, Taxi_UpdateRainEnds)

/* func_ov068_02273144 (entry of state 1): the car's animations looping. */
int Taxi_EnterRainEnds(Taxi *self)
{
    Taxi_RestartCar(self, TAXI_LOOP);
    return 1;
}
CLEAN_AS(func_ov068_02273144, Taxi_EnterRainEnds)

/* func_ov068_02273158 (update of state 0, and part of state 1's): sound 0x886 when the car's
 * animation passes frame 0, else sound 0x887 when it passes frame 0x1c. */
void Taxi_PlaySounds(Taxi *self)
{
    if (FrameCtrl_Passed(&self->base.body.frames, 0)) {
        SoundSys_PlaySe(TAXI_SOUND_FRAME_0);
    } else if (FrameCtrl_Passed(&self->base.body.frames, TAXI_SOUND_FRAME)) {
        SoundSys_PlaySe(TAXI_SOUND_FRAME_1C);
    }
}
CLEAN_AS(func_ov068_02273158, Taxi_PlaySounds)

/* func_ov068_02273198 (entry of state 0): alpha 31, the car's animations looping. */
int Taxi_EnterRain(Taxi *self)
{
    self->alpha = TAXI_RAIN_ALPHA;
    Taxi_RestartCar(self, TAXI_LOOP);
    return 1;
}
CLEAN_AS(func_ov068_02273198, Taxi_EnterRain)

/* func_ov068_022731b4: the update of its state runs (through a table filled once). States 3
 * and above do nothing. */
void Taxi_UpdateState(Taxi *self)
{
    static const MemberPointer *const updates[TAXI_STATES] = {
        &data_ov068_022778bc, /* Taxi_PlaySounds */
        &data_ov068_022778ac, /* Taxi_UpdateRainEnds */
        &data_ov068_022778b4, /* Taxi_UpdateDry */
    };
    MemberTable_InitOnce(&data_ov068_02278804, data_ov068_02278808, updates, TAXI_STATES);
    /* REQUIRES: state >= 0 (the entries set 0 to 2); the ROM's signed test lets a negative one
     * index before the table */
    if (self->state >= 0 && self->state < TAXI_STATES) {
        MemberPointer_CallVoid(&data_ov068_02278808[self->state], self);
    }
}
CLEAN_AS(func_ov068_022731b4, Taxi_UpdateState)

/* func_ov068_02273230: enters `state` if its entry (through a table filled once) agrees;
 * whether it did. States 3 and above do not exist. */
int Taxi_SetState(Taxi *self, int state)
{
    static const MemberPointer *const entries[TAXI_STATES] = {
        &data_ov068_022778a4, /* Taxi_EnterRain */
        &data_ov068_022778cc, /* Taxi_EnterRainEnds */
        &data_ov068_022778c4, /* Taxi_EnterDry */
    };
    MemberTable_InitOnce(&data_ov068_02278800, data_ov068_02278820, entries, TAXI_STATES);
    /* REQUIRES: state >= 0 (the game passes 0 to 2); the ROM's signed test lets a negative one
     * index before the table */
    if (state >= 0 && state < TAXI_STATES && MemberPointer_CallInt(&data_ov068_02278820[state], self) != 0) {
        self->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov068_02273230, Taxi_SetState)

/* func_ov068_022732bc: the car's first joint animation and its first material animation
 * started again with `flags` at the whole frames each is at. */
void Taxi_RestartCar(Taxi *self, int flags)
{
    AnimatedModel *body = animated(&self->base.body);
    const u8 *joints = func_ov004_0222c3c4(&self->base.body_model, 0);
    AnimatedModel_Start(body, joints, flags, TAXI_ONE, (u16) ((u32) self->base.body.frames.frame >> 12), 0);
    ModelRenderObject *render = ModelObject_RenderObject(&body->object);
    const u8 *materials = func_ov004_0222c3b4(&self->base.body_model, 0);
    ModelAnim_Restart(&self->material_anim, render, materials, flags, TAXI_ONE,
                      (u16) ((u32) self->material_anim.ctrl.frame >> 12));
}
CLEAN_AS(func_ov068_022732bc, Taxi_RestartCar)

/* An animation file started looping (or once) on a part that can take it. */
static void start_part(RmoAnimatedModel *model, RmoModel *source, int flags)
{
    if (func_ov004_0222c3c4(source, 0) != NULL && AnimatedModel_LoadAnim(animated(model), data_021c9b24) != 0) {
        AnimatedModel_Start(animated(model), func_ov004_0222c3c4(source, 0), flags, TAXI_ONE, 0, 0);
        AnimatedModel_Attach(animated(model));
    }
}

/* One of the car's material or texture animations started looping when the car has it and
 * it can be allocated, then attached to the car's render object. */
static void start_material_anim(Taxi *self, ModelAnim *anim, const u8 *(*get)(RmoModel *model, int index))
{
    if (get(&self->base.body_model, 0) != NULL &&
        ModelAnim_AllocMaterialAnim(anim, self->base.body.object.model, data_021c9b24) != 0) {
        ModelAnim_Start(anim, get(&self->base.body_model, 0), TAXI_LOOP, TAXI_ONE, 0);
        ModelAnim_Attach(anim, ModelObject_RenderObject(&self->base.body.object));
    }
}

/* func_ov068_02273338: the archives loaded: the car's ("obj_taxi"), with its first joint,
 * texture and material animations looping; the figure's, with its first animation played once;
 * the handle's, with its first animation looping. */
void Taxi_Load(Taxi *self)
{
    func_ov004_0222c5c8(&self->base, data_ov068_0227795c);
    start_part(&self->base.body, &self->base.body_model, TAXI_LOOP);
    start_material_anim(self, &self->texture_anim, func_ov004_0222c3a4);
    start_material_anim(self, &self->material_anim, func_ov004_0222c3b4);
    func_ov004_0222c62c(data_ov068_02277968, &self->figure, &self->figure_model, &self->figure_texture);
    start_part(&self->figure, &self->figure_model, TAXI_ONCE);
    func_ov004_0222c62c(data_ov068_02277978, &self->handle, &self->handle_model, &self->handle_texture);
    start_part(&self->handle, &self->handle_model, TAXI_LOOP);
}
CLEAN_AS(func_ov068_02273338, Taxi_Load)

/* func_ov068_02273510 (vtable slot 0x0c): no taxi any more, the three archives released and
 * its two sounds stopped. */
int Taxi_Release(Taxi *self)
{
    data_ov068_022787fc = NULL;
    func_ov004_0222c598(&self->base);
    func_ov004_0222c5b4(&self->figure_model, &self->figure_texture);
    func_ov004_0222c5b4(&self->handle_model, &self->handle_texture);
    SoundSys_StopSound(TAXI_SOUND_A, TAXI_SOUND_FADE);
    SoundSys_StopSound(TAXI_SOUND_B, TAXI_SOUND_FADE);
    return 1;
}
CLEAN_AS(func_ov068_02273510, Taxi_Release)

/* func_ov068_0227356c (vtable slot 0x24): the car, the figure and the handle drawn. */
int Taxi_Draw(Taxi *self)
{
    AnimatedModel_Draw(animated(&self->base.body), NULL);
    AnimatedModel_Draw(animated(&self->figure), NULL);
    AnimatedModel_Draw(animated(&self->handle), NULL);
    return 1;
}
CLEAN_AS(func_ov068_0227356c, Taxi_Draw)

/* The handle's animation for overlay 51's speaker's animation; 0 for any other. */
static int handle_anim(int speaker_anim)
{
    switch (speaker_anim) {
        case TAXI_SPEAKER_ANIM_1:
            return 1;
        case TAXI_SPEAKER_ANIM_2:
            return 2;
        case TAXI_SPEAKER_ANIM_3:
            return 3;
        case TAXI_SPEAKER_ANIM_4:
            return 4;
        case TAXI_SPEAKER_ANIM_5:
            return 5;
        case TAXI_SPEAKER_ANIM_0:
        default:
            return 0;
    }
}

/* func_ov068_0227359c (vtable slot 0x18): its state's update; the car's texture animation, its
 * joint animation and its material animation step (the animations' frames written to their
 * objects); the figure's once it plays; the handle takes the animation matching overlay 51's
 * speaker's and steps; the rain materials take its alpha. Always 1. */
int Taxi_Update(Taxi *self)
{
    Taxi_UpdateState(self);
    FrameCtrl_Step(&self->texture_anim.ctrl);
    self->texture_anim.anim->frame = self->texture_anim.ctrl.frame;
    AnimatedModel_StepFrames(animated(&self->base.body));
    FrameCtrl_Step(&self->material_anim.ctrl);
    self->material_anim.anim->frame = self->material_anim.ctrl.frame;
    if (self->figure_plays != 0) {
        AnimatedModel_StepFrames(animated(&self->figure));
    }
    int speaker_anim = func_ov051_02260474();
    /* QUIRK: the speaker's frame is asked for and not used */
    (void) func_ov051_02260490();
    Taxi_PlayPartAnim(self, handle_anim(speaker_anim), &self->handle, &self->handle_model, TAXI_LOOP, TAXI_ONE, 0, 0);
    AnimatedModel_StepFrames(animated(&self->handle));
    u8 *model = self->base.body.object.model;
    NNS_G3dMdlSetMdlAlpha(model, self->materials[0], (u8) self->alpha);
    NNS_G3dMdlSetMdlAlpha(model, self->materials[1], (u8) self->alpha);
    NNS_G3dMdlSetMdlAlpha(model, self->materials[2], (u8) self->alpha);
    return 1;
}
CLEAN_AS(func_ov068_0227359c, Taxi_Update)

/* func_ov068_022736d8 (vtable slot 0x00): it becomes the taxi, its archives are loaded, the
 * hook run before each draw of the car is set (the game's func_ov068_022738d8), the rain
 * materials looked up, state 0 entered and its two sounds started. */
int Taxi_Start(Taxi *self)
{
    data_ov068_022787fc = self;
    Taxi_Load(self);
    ModelObject_SetInitHook(&self->base.body.object, (void *) func_ov068_022738d8, self);
    u8 *model = self->base.body.object.model;
    self->materials[0] = (s16) G3dRes_MaterialIndex(model, data_ov068_02277988);
    self->materials[1] = (s16) G3dRes_MaterialIndex(model, data_ov068_02277990);
    self->materials[2] = (s16) G3dRes_MaterialIndex(model, data_ov068_02277998);
    Taxi_SetState(self, 0);
    SoundSys_StartOnHandle38(TAXI_SOUND_A);
    SoundSys_StartOnHandle38(TAXI_SOUND_B);
    return 1;
}
CLEAN_AS(func_ov068_022736d8, Taxi_Start)

/* The holders taken down, last first, then the RMO family's destructor. */
static void destruct_parts(Taxi *self)
{
    self->base.actor.vtable = data_ov068_022778f4;
    func_ov004_0222c394(&self->handle_texture);
    func_ov004_0222c538(&self->handle_model);
    AnimatedModel_DestructComplete(animated(&self->handle));
    func_ov004_0222c394(&self->figure_texture);
    func_ov004_0222c538(&self->figure_model);
    AnimatedModel_DestructComplete(animated(&self->figure));
    ModelAnim_DestructComplete(&self->texture_anim);
    ModelAnim_DestructComplete(&self->material_anim);
    func_ov004_0222c7a0(&self->base);
}

/* func_ov068_02273764 (vtable slot 0x44): taken down and freed. */
Taxi *Taxi_Delete(Taxi *self)
{
    destruct_parts(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov068_02273764, Taxi_Delete)

/* func_ov068_022737e4 (vtable slot 0x40) */
Taxi *Taxi_Destruct(Taxi *self)
{
    destruct_parts(self);
    return self;
}
CLEAN_AS(func_ov068_022737e4, Taxi_Destruct)

/* func_ov068_02273860: the RMO family's constructor, the vtable, then the holders. */
Taxi *Taxi_Construct(Taxi *self)
{
    func_ov004_0222c87c(&self->base);
    self->base.actor.vtable = data_ov068_022778f4;
    ModelAnim_Construct(&self->material_anim);
    ModelAnim_Construct(&self->texture_anim);
    AnimatedModel_Construct(animated(&self->figure));
    func_ov004_0222c548(&self->figure_model);
    func_ov004_0222c398(&self->figure_texture);
    AnimatedModel_Construct(animated(&self->handle));
    func_ov004_0222c548(&self->handle_model);
    func_ov004_0222c398(&self->handle_texture);
    return self;
}
CLEAN_AS(func_ov068_02273860, Taxi_Construct)

/* func_ov068_022738d8 (run before each draw of the car): the materials' hook (the game's
 * func_ov068_022738e8) set, run at timing B. */
void Taxi_SetModelHooks(TaxiRenderState *state)
{
    state->hooks[TAXI_COMMAND_MAT] = (u32) (uintptr_t) func_ov068_022738e8;
    state->hook_timings[TAXI_COMMAND_MAT] = TAXI_TIMING_B;
}
CLEAN_AS(func_ov068_022738d8, Taxi_SetModelHooks)

/* func_ov068_022738e8 (the materials' hook Taxi_SetModelHooks sets): for a model with a taxi,
 * Taxi_OnMaterial.
 * QUIRK: the ROM hands Taxi_OnMaterial the taxi and the material (the command's byte 1), which
 * it ignores.
 * QUIRK: the code is assembly that leaves the model's user word (the taxi, or NULL) in its
 * result register; NitroSystem does not read it, and it is returned here as the word it is. */
const Taxi *Taxi_MaterialHook(TaxiRenderState *state)
{
    const Taxi *self = ((const TaxiRenderObject *) state->render_object)->user;
    if (self != NULL) {
        Taxi_OnMaterial();
    }
    return self;
}
CLEAN_AS(func_ov068_022738e8, Taxi_MaterialHook)
