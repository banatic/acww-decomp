/* The televisions (tv.h). */
#include "tv.h"

#include <stdint.h>

#include "clean.h"
#include "furniture_model.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_parts.h"

static_assert(offsetof(RoomObject, model_resource) == 0x594, "model resource");
static_assert(offsetof(RoomObject, model_files) == 0x6cc, "model files");
static_assert(offsetof(Tv, state) == 0x844, "state");
static_assert(offsetof(Tv, screen) == 0x848, "screen");
static_assert(offsetof(Tv, heard) == 0x864, "heard");
static_assert(offsetof(Tv, animated_state) == 0x865, "TvAnimated's state");
static_assert(sizeof(Tv) == 0x868, "the size Tv_Create allocates");
static_assert(sizeof(TvAnimated) == 0x868, "the size TvAnimated_Create allocates");

#define TV_SIZE 0x868
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_ONCE 1   /* stop at the end */
#define ANIM_MODE_3 3      /* the animations' mode 3 */
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* Tv's state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257088;
extern MemberPointer data_ov004_022571b4[TV_STATE_COUNT];
extern const MemberPointer data_ov004_02250100, data_ov004_022503f8;
extern u32 data_ov004_02257000;
extern MemberPointer data_ov004_02257184[TV_STATE_COUNT];
extern const MemberPointer data_ov004_02250420, data_ov004_022503d8;

/* TvAnimated's. */
extern u32 data_ov004_02257008;
extern MemberPointer data_ov004_022573cc[TV_ANIMATED_STATE_COUNT];
extern const MemberPointer data_ov004_02250248, data_ov004_02250640, data_ov004_02250390, data_ov004_02250230;
extern u32 data_ov004_0225702c;
extern MemberPointer data_ov004_0225738c[TV_ANIMATED_STATE_COUNT];
extern const MemberPointer data_ov004_02250190, data_ov004_022503c8, data_ov004_022503c0, data_ov004_022503b8;

/* Whether each state shows the object on (for vtable slot 0x74). */
extern const u8 data_ov004_02247674[TV_STATE_COUNT];          /* TV_ON does */
extern const u8 data_ov004_02247694[TV_ANIMATED_STATE_COUNT]; /* TURNING_ON and ON do */

/* The classes' vtables, and their receiver parts'. */
extern const u8 data_ov004_02251438[];
extern const u8 data_ov004_022514e4[];
extern const u8 data_ov004_02250f88[];
extern const u8 data_ov004_02251034[];

/* "tv_m" (the screen's material), "tv.0" and "tv_pl" (its texture and palette when off). */
extern const char data_ov004_022531d8[];
extern const char data_ov004_022531e0[];
extern const char data_ov004_022531e8[];

/* Request a state for the object at the object's cell (only when data_020e54a8 is 1). */
extern int func_0205265c(unsigned int object, int state, int a2, int a3);
/* Whether func_020b6730 says so or the area (func_020b65c4) is 10 or 15. */
extern int func_ov004_0223c10c(void);
/* The picture the screens show (func_ov004_0223a7cc of the member at 0x64 of
 * data_ov004_022595c0; 0 when that is NULL). */
extern int func_ov004_0223b314(void);
/* Gives a material of a model another texture: the one given, or the texture and palette
 * named in a texture file. */
extern int func_02057084(G3dModel *model, const char *material, void *texture, void *a3, int a4);
extern int func_020570d4(G3dModel *model, const char *material, u8 *texture_file, const char *texture, const char *palette);

static unsigned int Tv_address(Tv *tv)
{
    return (unsigned int) (uintptr_t) tv;
}

/* Vtable slot 0x70: the class's EnterState. */
static void Tv_switch_to(Tv *tv, int state)
{
    tv->base.vtable->vfunc_70(&tv->base, state, SLOT_70_VALUE);
}

/* The glow bound to the screen's material, on as the switch is; then the "on" state when the
 * switch is on and func_ov004_0223c10c says no, else the "off" one. */
static void Tv_bind_and_enter(Tv *tv, int on_state, int off_state)
{
    int on = Switch_Value(&tv->base.light_switch);
    Glow_Bind(&tv->screen, tv->base.model_resource, data_ov004_022531d8, on);
    if (Switch_Value(&tv->base.light_switch) != 0 && func_ov004_0223c10c() == 0) {
        Tv_switch_to(tv, on_state);
    } else {
        Tv_switch_to(tv, off_state);
    }
}

/* What every state of TvAnimated sets on entry: the switch (shown at once), the glow towards
 * it and the screen. */
static void TvAnimated_show(TvAnimated *tv, int on)
{
    Switch_Set(&tv->base.base.light_switch, (u8) on, 0);
    Glow_Switch(&tv->base.screen, on, 1, 0);
    Tv_ShowScreen(&tv->base, on);
}

/* func_ov004_02215758 (update of TV_ANIMATED_TURNING_OFF): the switch kept off; at the end of
 * the animations, TV_ANIMATED_OFF. */
void TvAnimated_UpdateTurningOff(TvAnimated *tv)
{
    Switch_Set(&tv->base.base.light_switch, 0, 0);
    if (RoomObject_AdvanceAnims(&tv->base.base) != 0) {
        Tv_switch_to(&tv->base, TV_ANIMATED_OFF);
    }
}
CLEAN_AS(func_ov004_02215758, TvAnimated_UpdateTurningOff)

/* func_ov004_02215788 (entry of TV_ANIMATED_TURNING_OFF): off, the animations of variant 0 in
 * mode 3 from their last frame, and the sound at 4. */
int TvAnimated_EnterTurningOff(TvAnimated *tv)
{
    TvAnimated_show(tv, 0);
    RoomObject_PlayAnimsFromEnd(&tv->base.base, 0, ANIM_MODE_3, ONE);
    RoomObject_PlaySound2(&tv->base.base);
    return 1;
}
CLEAN_AS(func_ov004_02215788, TvAnimated_EnterTurningOff)

/* func_ov004_022157d4 (update of TV_ANIMATED_ON): with a change of the switch pending,
 * requests TV_ANIMATED_TURNING_OFF and gives the answer, else 0. */
int TvAnimated_UpdateOn(TvAnimated *tv)
{
    if (Switch_IsPending(&tv->base.base.light_switch)) {
        return func_0205265c(Tv_address(&tv->base), TV_ANIMATED_TURNING_OFF, SLOT_70_VALUE, 1);
    }
    return 0;
}
CLEAN_AS(func_ov004_022157d4, TvAnimated_UpdateOn)

/* func_ov004_022157fc (entry of TV_ANIMATED_ON): on, the animations of variant 0 once from
 * their last frame (so held there). */
int TvAnimated_EnterOn(TvAnimated *tv)
{
    TvAnimated_show(tv, 1);
    RoomObject_PlayAnimsFromEnd(&tv->base.base, 0, ANIM_MODE_ONCE, ONE);
    return 1;
}
CLEAN_AS(func_ov004_022157fc, TvAnimated_EnterOn)

/* func_ov004_02215844 (update of TV_ANIMATED_TURNING_ON): the switch kept on; at the end of the
 * animations, TV_ANIMATED_ON. */
void TvAnimated_UpdateTurningOn(TvAnimated *tv)
{
    Switch_Set(&tv->base.base.light_switch, 1, 0);
    if (RoomObject_AdvanceAnims(&tv->base.base) != 0) {
        Tv_switch_to(&tv->base, TV_ANIMATED_ON);
    }
}
CLEAN_AS(func_ov004_02215844, TvAnimated_UpdateTurningOn)

/* func_ov004_02215874 (entry of TV_ANIMATED_TURNING_ON): on, the animations of variant 0 once
 * from the start, and the sound at 2. */
int TvAnimated_EnterTurningOn(TvAnimated *tv)
{
    TvAnimated_show(tv, 1);
    RoomObject_PlayAnimsFrom(&tv->base.base, 0, ANIM_MODE_ONCE, ONE, 0);
    RoomObject_PlaySound1(&tv->base.base);
    return 1;
}
CLEAN_AS(func_ov004_02215874, TvAnimated_EnterTurningOn)

/* func_ov004_022158c8 (update of TV_ANIMATED_OFF): with a change of the switch pending,
 * requests TV_ANIMATED_TURNING_ON. */
void TvAnimated_UpdateOff(TvAnimated *tv)
{
    if (Switch_IsPending(&tv->base.base.light_switch)) {
        func_0205265c(Tv_address(&tv->base), TV_ANIMATED_TURNING_ON, SLOT_70_VALUE, 1);
    }
}
CLEAN_AS(func_ov004_022158c8, TvAnimated_UpdateOff)

/* func_ov004_022158f0 (entry of TV_ANIMATED_OFF): off, the animations of variant 0 in mode 3
 * from frame 0. */
int TvAnimated_EnterOff(TvAnimated *tv)
{
    TvAnimated_show(tv, 0);
    RoomObject_PlayAnimsFrom(&tv->base.base, 0, ANIM_MODE_3, ONE, 0);
    return 1;
}
CLEAN_AS(func_ov004_022158f0, TvAnimated_EnterOff)

/* _ZN18Obj_ov004_02250f8819func_ov004_0221593cEv: the state's update, through its table. */
void TvAnimated_UpdateState(TvAnimated *tv)
{
    static const MemberPointer *const updates[TV_ANIMATED_STATE_COUNT] = {
        &data_ov004_02250248, /* TvAnimated_UpdateOff */
        &data_ov004_02250640, /* TvAnimated_UpdateTurningOn */
        &data_ov004_02250390, /* TvAnimated_UpdateOn */
        &data_ov004_02250230, /* TvAnimated_UpdateTurningOff */
    };
    MemberTable_InitOnce(&data_ov004_02257008, data_ov004_022573cc, updates, TV_ANIMATED_STATE_COUNT);
    if (tv->base.animated_state < TV_ANIMATED_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022573cc[tv->base.animated_state], tv);
    }
}
CLEAN_AS(_ZN18Obj_ov004_02250f8819func_ov004_0221593cEv, TvAnimated_UpdateState)

/* func_ov004_022159c8 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 4 and above do not exist. */
int TvAnimated_EnterState(TvAnimated *tv, unsigned int state, int value)
{
    static const MemberPointer *const entries[TV_ANIMATED_STATE_COUNT] = {
        &data_ov004_02250190, /* TvAnimated_EnterOff */
        &data_ov004_022503c8, /* TvAnimated_EnterTurningOn */
        &data_ov004_022503c0, /* TvAnimated_EnterOn */
        &data_ov004_022503b8, /* TvAnimated_EnterTurningOff */
    };
    RoomObject_SetUnk77C(&tv->base.base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_0225702c, data_ov004_0225738c, entries, TV_ANIMATED_STATE_COUNT);
    if (state < TV_ANIMATED_STATE_COUNT && MemberPointer_CallInt(&data_ov004_0225738c[state], tv) != 0) {
        tv->base.animated_state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_022159c8, TvAnimated_EnterState)

/* func_ov004_02215a68 (vtable slot 0x74): whether `state` shows the object on (TURNING_ON and
 * ON do); 0 for a state that does not exist. */
u8 TvAnimated_StateIsOn(TvAnimated *tv, unsigned int state)
{
    (void) tv;
    if (state < TV_ANIMATED_STATE_COUNT) {
        return data_ov004_02247694[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_02215a68, TvAnimated_StateIsOn)

/* func_ov004_02215a7c (vtable slot 0x0c) */
int TvAnimated_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02215a7c, TvAnimated_Vfunc0C)

/* _ZN18Obj_ov004_02250f8819func_ov004_02215a80Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the glow, then the state's update.
 * QUIRK: unlike Tv_Update it leaves `heard` as it is. */
int TvAnimated_Update(TvAnimated *tv)
{
    Glow_Update(&tv->base.screen);
    TvAnimated_UpdateState(tv);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_02250f8819func_ov004_02215a80Ev, TvAnimated_Update)

/* func_ov004_02215aa0 (vtable slot 0x7c, once the model is bound): binds the animations of
 * variant 0 to play once from frame 0, then the glow; TV_ANIMATED_ON when the switch is on and
 * func_ov004_0223c10c says no, else TV_ANIMATED_OFF; done at once. */
int TvAnimated_Start(TvAnimated *tv)
{
    RoomObject_LoadAnims(&tv->base.base, 0, ANIM_MODE_ONCE, ONE, 0);
    Tv_bind_and_enter(&tv->base, TV_ANIMATED_ON, TV_ANIMATED_OFF);
    return 1;
}
CLEAN_AS(func_ov004_02215aa0, TvAnimated_Start)

static void TvAnimated_set_vtables(TvAnimated *tv)
{
    tv->base.base.vtable = (const RoomObjectVtable *) data_ov004_02250f88;
    tv->base.base.receiver_vtable = data_ov004_02251034;
}

/* func_ov004_02215b18 (the deleting destructor, vtable slot 0x44) */
TvAnimated *TvAnimated_Delete(TvAnimated *tv)
{
    TvAnimated_set_vtables(tv);
    Tv_DestroyBase(&tv->base);
    RoomObject_Free(tv);
    return tv;
}
CLEAN_AS(func_ov004_02215b18, TvAnimated_Delete)

/* func_ov004_02215b44 (the destructor, vtable slot 0x40) */
TvAnimated *TvAnimated_Destroy(TvAnimated *tv)
{
    TvAnimated_set_vtables(tv);
    Tv_DestroyBase(&tv->base);
    return tv;
}
CLEAN_AS(func_ov004_02215b44, TvAnimated_Destroy)

/* func_ov004_02215b68 (the constructor): Tv's, then this class's vtables. Its state is left as
 * the allocation zeroed it (TV_ANIMATED_OFF). */
TvAnimated *TvAnimated_Construct(TvAnimated *tv)
{
    Tv_ConstructBase(&tv->base);
    TvAnimated_set_vtables(tv);
    return tv;
}
CLEAN_AS(func_ov004_02215b68, TvAnimated_Construct)

/* func_ov004_02215b8c: a new one from the room's heap; nothing when it has no room. */
void TvAnimated_Create(void)
{
    TvAnimated *tv = RoomObject_Alloc(TV_SIZE);
    if (tv != NULL) {
        TvAnimated_Construct(tv);
    }
}
CLEAN_AS(func_ov004_02215b8c, TvAnimated_Create)

/* func_ov004_02215ba8 (update of TV_ON): with a change of the switch pending, requests TV_OFF
 * and gives the answer, else 0. */
int Tv_UpdateOn(Tv *tv)
{
    if (Switch_IsPending(&tv->base.light_switch)) {
        return func_0205265c(Tv_address(tv), TV_OFF, SLOT_70_VALUE, 1);
    }
    return 0;
}
CLEAN_AS(func_ov004_02215ba8, Tv_UpdateOn)

/* func_ov004_02215bd0 (entry of TV_ON): the sound at 2, the glow towards on, the switch on
 * (shown at once) and the picture on the screen. */
int Tv_EnterOn(Tv *tv)
{
    RoomObject_PlaySound1(&tv->base);
    Glow_Switch(&tv->screen, 1, 1, 0);
    Switch_Set(&tv->base.light_switch, 1, 0);
    Tv_ShowScreen(tv, 1);
    return 1;
}
CLEAN_AS(func_ov004_02215bd0, Tv_EnterOn)

/* func_ov004_02215c0c (update of TV_OFF): with a change of the switch pending, requests
 * TV_ON. */
void Tv_UpdateOff(Tv *tv)
{
    if (Switch_IsPending(&tv->base.light_switch)) {
        func_0205265c(Tv_address(tv), TV_ON, SLOT_70_VALUE, 1);
    }
}
CLEAN_AS(func_ov004_02215c0c, Tv_UpdateOff)

/* func_ov004_02215c34 (entry of TV_OFF): the sound at 4, the glow towards off, the switch off
 * (shown at once) and the screen's own texture. */
int Tv_EnterOff(Tv *tv)
{
    RoomObject_PlaySound2(&tv->base);
    Glow_Switch(&tv->screen, 0, 1, 0);
    Switch_Set(&tv->base.light_switch, 0, 0);
    Tv_ShowScreen(tv, 0);
    return 1;
}
CLEAN_AS(func_ov004_02215c34, Tv_EnterOff)

/* _ZN18Obj_ov004_0225143819func_ov004_02215c70Ev: the state's update, through its table. */
void Tv_UpdateState(Tv *tv)
{
    static const MemberPointer *const updates[TV_STATE_COUNT] = {
        &data_ov004_02250100, /* Tv_UpdateOff */
        &data_ov004_022503f8, /* Tv_UpdateOn */
    };
    MemberTable_InitOnce(&data_ov004_02257088, data_ov004_022571b4, updates, TV_STATE_COUNT);
    if (tv->state < TV_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022571b4[tv->state], tv);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225143819func_ov004_02215c70Ev, Tv_UpdateState)

/* func_ov004_02215cdc (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 2 and above do not exist. */
int Tv_EnterState(Tv *tv, unsigned int state, int value)
{
    static const MemberPointer *const entries[TV_STATE_COUNT] = {
        &data_ov004_02250420, /* Tv_EnterOff */
        &data_ov004_022503d8, /* Tv_EnterOn */
    };
    RoomObject_SetUnk77C(&tv->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02257000, data_ov004_02257184, entries, TV_STATE_COUNT);
    if (state < TV_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02257184[state], tv) != 0) {
        tv->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02215cdc, Tv_EnterState)

/* func_ov004_02215d60 (vtable slot 0x74): whether `state` shows the object on (TV_ON does); 0
 * for a state that does not exist. */
u8 Tv_StateIsOn(Tv *tv, unsigned int state)
{
    (void) tv;
    if (state < TV_STATE_COUNT) {
        return data_ov004_02247674[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_02215d60, Tv_StateIsOn)

/* func_ov004_02215d74: marks this TV as the one heard (func_ov004_0223bdac). */
Tv *Tv_SetHeard(Tv *tv)
{
    tv->heard = 1;
    return tv;
}
CLEAN_AS(func_ov004_02215d74, Tv_SetHeard)

/* func_ov004_02215d80: the screen's material "tv_m" shows the picture of
 * func_ov004_0223b314 when `on`, else the texture "tv.0" with the palette "tv_pl" of the
 * model's texture file; 1. */
int Tv_ShowScreen(Tv *tv, int on)
{
    if (on != 0) {
        G3dModel *model = tv->base.model_resource;
        void *picture = (void *) (uintptr_t) (u32) func_ov004_0223b314();
        func_02057084(model, data_ov004_022531d8, picture, NULL, 0);
    } else {
        G3dModel *model = tv->base.model_resource;
        func_020570d4(model, data_ov004_022531d8, FurnitureModel_Texture(&tv->base.model_files), data_ov004_022531e0,
                      data_ov004_022531e8);
    }
    return 1;
}
CLEAN_AS(func_ov004_02215d80, Tv_ShowScreen)

/* func_ov004_02215ddc (vtable slot 0x0c) */
int Tv_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02215ddc, Tv_Vfunc0C)

/* _ZN18Obj_ov004_0225143819func_ov004_02215de0Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the glow, the state's update, and `heard` cleared for
 * func_ov004_0223bdac to set again. */
int Tv_Update(Tv *tv)
{
    Glow_Update(&tv->screen);
    Tv_UpdateState(tv);
    tv->heard = 0;
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_0225143819func_ov004_02215de0Ev, Tv_Update)

/* func_ov004_02215e08 (vtable slot 0x7c, once the model is bound): binds the glow; TV_ON when
 * the switch is on and func_ov004_0223c10c says no, else TV_OFF; done at once. */
int Tv_Start(Tv *tv)
{
    Tv_bind_and_enter(tv, TV_ON, TV_OFF);
    return 1;
}
CLEAN_AS(func_ov004_02215e08, Tv_Start)

static void Tv_set_vtables(Tv *tv)
{
    tv->base.vtable = (const RoomObjectVtable *) data_ov004_02251438;
    tv->base.receiver_vtable = data_ov004_022514e4;
}

/* Taking a TV down: its vtables, the glow, then the base. */
static Tv *Tv_take_down(Tv *tv)
{
    Tv_set_vtables(tv);
    Glow_Destruct(&tv->screen);
    RoomObject_DestructBase(&tv->base);
    return tv;
}

/* Building one: the base, its vtables, then the glow. Its state is left as the allocation
 * zeroed it (TV_OFF). */
static Tv *Tv_build(Tv *tv)
{
    RoomObject_ConstructBase(&tv->base);
    Tv_set_vtables(tv);
    Glow_Construct(&tv->screen);
    return tv;
}

/* func_ov004_02215e70 (the destructor TvAnimated's call). */
Tv *Tv_DestroyBase(Tv *tv)
{
    return Tv_take_down(tv);
}
CLEAN_AS(func_ov004_02215e70, Tv_DestroyBase)

/* func_ov004_02215ea4 (the deleting destructor, vtable slot 0x44) */
Tv *Tv_Delete(Tv *tv)
{
    Tv_take_down(tv);
    RoomObject_Free(tv);
    return tv;
}
CLEAN_AS(func_ov004_02215ea4, Tv_Delete)

/* func_ov004_02215edc (the destructor, vtable slot 0x40; the same as Tv_DestroyBase) */
Tv *Tv_Destroy(Tv *tv)
{
    return Tv_take_down(tv);
}
CLEAN_AS(func_ov004_02215edc, Tv_Destroy)

/* func_ov004_02215f10 (the constructor Tv_Create calls) */
Tv *Tv_Construct(Tv *tv)
{
    return Tv_build(tv);
}
CLEAN_AS(func_ov004_02215f10, Tv_Construct)

/* func_ov004_02215f40 (the constructor TvAnimated's calls; the same as Tv_Construct) */
Tv *Tv_ConstructBase(Tv *tv)
{
    return Tv_build(tv);
}
CLEAN_AS(func_ov004_02215f40, Tv_ConstructBase)

/* func_ov004_02215f70: a new one from the room's heap; nothing when it has no room. */
void Tv_Create(void)
{
    Tv *tv = RoomObject_Alloc(TV_SIZE);
    if (tv != NULL) {
        Tv_Construct(tv);
    }
}
CLEAN_AS(func_ov004_02215f70, Tv_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters Tv's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static Tv *Tv_from_receiver(void *receiver)
{
    return (Tv *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a83c: the deleting destructor, entered from the receiver part. */
Tv *TvReceiver_Delete(void *receiver)
{
    return Tv_Delete(Tv_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251438D0Ev, TvReceiver_Delete)

/* func_ov004_0221a858: the destructor, entered from the receiver part. */
Tv *TvReceiver_Destroy(void *receiver)
{
    return Tv_Destroy(Tv_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251438D1Ev, TvReceiver_Destroy)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters TvAnimated's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static TvAnimated *TvAnimated_from_receiver(void *receiver)
{
    return (TvAnimated *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a874: the deleting destructor, entered from the receiver part. */
TvAnimated *TvAnimatedReceiver_Delete(void *receiver)
{
    return TvAnimated_Delete(TvAnimated_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02250f88D0Ev, TvAnimatedReceiver_Delete)

/* func_ov004_0221a890: the destructor, entered from the receiver part. */
TvAnimated *TvAnimatedReceiver_Destroy(void *receiver)
{
    return TvAnimated_Destroy(TvAnimated_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02250f88D1Ev, TvAnimatedReceiver_Destroy)
