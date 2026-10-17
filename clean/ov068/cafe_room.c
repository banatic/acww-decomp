/* The room object of "obj_ms_cafe" and "obj_cf_chr" (cafe_room.h). */
#include "cafe_room.h"

#include "clean.h"
#include "main/animated_model.h"
#include "ov004/member_pointer.h"

static_assert(sizeof(RmoObject) == 0x290, "RmoObject size");
static_assert(offsetof(CafeRoom, alpha) == 0x290, "alpha");
static_assert(offsetof(CafeRoom, target_alpha) == 0x294, "target alpha");
static_assert(offsetof(CafeRoom, has_chr) == 0x298, "has chr");
static_assert(offsetof(CafeRoom, chr) == 0x29c, "chr");
static_assert(offsetof(CafeRoom, chr_model) == 0x354, "chr model");
static_assert(offsetof(CafeRoom, chr_texture) == 0x3f8, "chr texture");

#define CAFE_ROOM_MODE 0x24c /* u8, in the RMO object's unk_24c */

/* The one that exists, NULL for none. */
extern CafeRoom *data_ov068_022788b0;

/* The modes' updates and entries (function-local statics filled once), their guards and
 * constants. */
extern u32 data_ov068_02278890;
extern MemberPointer data_ov068_022788c4[CAFE_ROOM_MODES];
extern const MemberPointer data_ov068_02277efc, data_ov068_02277f14;
extern u32 data_ov068_022788a0;
extern MemberPointer data_ov068_022788b4[CAFE_ROOM_MODES];
extern const MemberPointer data_ov068_02277f04, data_ov068_02277f0c;

/* The RMO family's release of the body's archive and of another part's, and the shared value
 * a mode is told to (a no-op answering 0 without one). */
extern void func_ov004_0222c598(RmoObject *object);
extern void func_ov004_0222c5b4(RmoModel *source, RmoTexture *texture);
extern int func_ov004_0222c558(RmoObject *object, u32 value);

static u8 *mode_of(CafeRoom *self)
{
    return (u8 *) self + CAFE_ROOM_MODE;
}

/* func_ov068_02274ee0 (update of mode 1) */
void CafeRoom_UpdateShown(CafeRoom *self)
{
    self->target_alpha = CAFE_ROOM_ALPHA_SHOWN;
}
CLEAN_AS(func_ov068_02274ee0, CafeRoom_UpdateShown)

/* func_ov068_02274eec (entry of mode 1) */
int CafeRoom_EnterShown(CafeRoom *self)
{
    self->target_alpha = CAFE_ROOM_ALPHA_SHOWN;
    return 1;
}
CLEAN_AS(func_ov068_02274eec, CafeRoom_EnterShown)

/* func_ov068_02274efc (update of mode 0) */
void CafeRoom_UpdateFaded(CafeRoom *self)
{
    self->target_alpha = CAFE_ROOM_ALPHA_FADED;
}
CLEAN_AS(func_ov068_02274efc, CafeRoom_UpdateFaded)

/* func_ov068_02274f08 (entry of mode 0) */
int CafeRoom_EnterFaded(CafeRoom *self)
{
    self->target_alpha = CAFE_ROOM_ALPHA_FADED;
    return 1;
}
CLEAN_AS(func_ov068_02274f08, CafeRoom_EnterFaded)

/* func_ov068_02274f18: the update of its mode (through a table filled once); modes 2 and above
 * do nothing. */
void CafeRoom_UpdateMode(CafeRoom *self)
{
    static const MemberPointer *const updates[CAFE_ROOM_MODES] = {
        &data_ov068_02277efc, /* CafeRoom_UpdateFaded */
        &data_ov068_02277f14, /* CafeRoom_UpdateShown */
    };
    MemberTable_InitOnce(&data_ov068_02278890, data_ov068_022788c4, updates, CAFE_ROOM_MODES);
    u8 mode = *mode_of(self);
    if (mode < CAFE_ROOM_MODES) {
        MemberPointer_CallVoid(&data_ov068_022788c4[mode], self);
    }
}
CLEAN_AS(_ZN18Obj_ov068_02277f3c19func_ov068_02274f18Ev, CafeRoom_UpdateMode)

/* func_ov068_02274f84 (vtable slot 0x60): `mode` taken when its entry (through a table filled
 * once) agrees and the shared value takes it (func_ov004_0222c558); whether it was. Modes 2
 * and above do not exist. */
int CafeRoom_SetMode(CafeRoom *self, unsigned int mode)
{
    static const MemberPointer *const entries[CAFE_ROOM_MODES] = {
        &data_ov068_02277f04, /* CafeRoom_EnterFaded */
        &data_ov068_02277f0c, /* CafeRoom_EnterShown */
    };
    MemberTable_InitOnce(&data_ov068_022788a0, data_ov068_022788b4, entries, CAFE_ROOM_MODES);
    if (mode >= CAFE_ROOM_MODES || MemberPointer_CallInt(&data_ov068_022788b4[mode], self) == 0 ||
        func_ov004_0222c558(&self->base, mode) == 0) {
        return 0;
    }
    *mode_of(self) = (u8) mode;
    return 1;
}
CLEAN_AS(_ZN18Obj_ov068_02277f3c19func_ov068_02274f84Ej, CafeRoom_SetMode)

/* func_ov068_02275010 (vtable slot 0x0c): the body's archive released, and chr's when it was
 * loaded; no room object any more. */
int CafeRoom_Release(CafeRoom *self)
{
    func_ov004_0222c598(&self->base);
    if (self->has_chr != 0) {
        func_ov004_0222c5b4(&self->chr_model, &self->chr_texture);
    }
    data_ov068_022788b0 = NULL;
    return 1;
}
CLEAN_AS(func_ov068_02275010, CafeRoom_Release)

/* func_ov068_0227504c (vtable slot 0x24): the body drawn, and chr when it was loaded. */
int CafeRoom_Draw(CafeRoom *self)
{
    AnimatedModel_Draw((AnimatedModel *) (void *) &self->base.body, NULL);
    if (self->has_chr != 0) {
        AnimatedModel_Draw((AnimatedModel *) (void *) &self->chr, NULL);
    }
    return 1;
}
CLEAN_AS(func_ov068_0227504c, CafeRoom_Draw)
