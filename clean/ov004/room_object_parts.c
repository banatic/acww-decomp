/* The small parts of the room objects (room_object_parts.h). */
#include "room_object_parts.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "room_object.h"
#include "main/acre_tile.h"
#include "main/fader.h"
#include "main/g3d_resource.h"
#include "main/room_cells.h"
#include "main/scene_query.h"
#include "room_object_body.h"
#include "room_object_methods.h"
#include "room_objects.h"

static_assert(sizeof(Switch) == 2, "switch");
static_assert(sizeof(NodePair) == 3, "node pair");
static_assert(sizeof(Fader) == 0x14, "fader");
static_assert(offsetof(Glow, material) == 0x14, "glow material");
static_assert(offsetof(Glow, model) == 0x18, "glow model");
static_assert(sizeof(Glow) == 0x1c, "glow");
static_assert(offsetof(GlowSet, bound) == 0x54, "glow set flag");
static_assert(offsetof(G3dModel, material_count) == 0x18, "material count");
static_assert(offsetof(Mount, offset) == 4, "mount offset");
static_assert(sizeof(Mount) == 0x10, "mount");
static_assert(offsetof(AnimSet, file_28) == 0x28, "anim set file");

/* An arithmetic shift right, for negative values too. */
static s32 shift_right(s32 value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* ---- The switch (0x740) ---- */

/* func_ov004_0220d280: `value` as the wanted value; unless `pending`, also as the shown one. */
void Switch_Set(Switch *sw, u8 value, int pending)
{
    if (pending) {
        sw->wanted = value;
    } else {
        sw->shown = value;
        sw->wanted = sw->shown;
    }
}
CLEAN_AS(func_ov004_0220d280, Switch_Set)

/* func_ov004_0220d290: the wanted value turned over (0 and 1 swap; any odd value gives 0, any
 * even one 1). */
void Switch_Toggle(Switch *sw, int pending)
{
    u8 value = (u8) ((sw->wanted + 1) & 1);
    Switch_Set(sw, value, pending);
}
CLEAN_AS(func_ov004_0220d290, Switch_Toggle)

/* func_ov004_0220d2a8: whether the wanted value is not shown yet. */
int Switch_IsPending(const Switch *sw)
{
    return sw->shown != sw->wanted;
}
CLEAN_AS(func_ov004_0220d2a8, Switch_IsPending)

/* func_ov004_0220d2b8 */
u8 Switch_Value(const Switch *sw)
{
    return sw->wanted;
}
CLEAN_AS(func_ov004_0220d2b8, Switch_Value)

/* func_ov004_0220d2bc: the wanted value into the town's map record of the object's cell
 * (RoomCells_SetSwitch, for its layer), unless RoomObject_Unk76CIs2 says the object is not to be kept
 * there or it has no cell. */
void Switch_Save(const Switch *sw, RoomObject *object)
{
    if (RoomObject_Unk76CIs2(object) == 0) {
        int x;
        int y;
        if (RoomObject_FindVariantCell(object, &x, &y, 0, 0) != 0) {
            RoomCells_SetSwitch(x, y, object->unk_288, sw->wanted, SceneQuery_Current());
        }
    }
}
CLEAN_AS(func_ov004_0220d2bc, Switch_Save)

/* func_ov004_0220d300: shows the wanted value and returns it; when RoomObject_Unk76CIs2 says
 * otherwise, leaves it pending and returns what that said. */
int Switch_Apply(Switch *sw, RoomObject *object)
{
    int held = RoomObject_Unk76CIs2(object);
    if (held == 0) {
        sw->shown = sw->wanted;
        return sw->shown;
    }
    return held;
}
CLEAN_AS(func_ov004_0220d300, Switch_Apply)

/* func_ov004_0220d318: the value to start with, shown at once: when unk_76C is 1 or 2, on if
 * unk_78D is 0; otherwise what the town's map record of the object's cell says (off when it has
 * no cell). */
void Switch_Load(Switch *sw, RoomObject *object)
{
    int value = 0;
    if (object->unk_76C == 1 || RoomObject_Unk76CIs2(object) != 0) {
        value = object->unk_78D == 0;
    } else {
        int x;
        int y;
        if (RoomObject_FindVariantCell(object, &x, &y, 0, 0) != 0) {
            value = RoomCells_GetSwitch(x, y, object->unk_288, SceneQuery_Current());
        }
    }
    /* QUIRK: the record's answer is kept in a byte. */
    Switch_Set(sw, (u8) value, 0);
}
CLEAN_AS(func_ov004_0220d318, Switch_Load)

/* func_ov004_0220d388 */
void Switch_Destruct(Switch *sw)
{
    (void) sw;
}
CLEAN_AS(func_ov004_0220d388, Switch_Destruct)

/* func_ov004_0220d38c: off. */
void Switch_Construct(Switch *sw)
{
    sw->wanted = 0;
    sw->shown = 0;
}
CLEAN_AS(func_ov004_0220d38c, Switch_Construct)

/* ---- The two nodes (0x742) ---- */

/* func_ov004_0220d398: the two indexes; `found` is set when either is a node, and left as it
 * was otherwise. */
void NodePair_Set(NodePair *pair, s8 first, s8 second)
{
    pair->nodes[0] = first;
    pair->nodes[1] = second;
    if (pair->nodes[0] != -1 || pair->nodes[1] != -1) {
        pair->found = 1;
    }
}
CLEAN_AS(func_ov004_0220d398, NodePair_Set)

/* func_ov004_0220d3b4 */
void NodePair_Destruct(NodePair *pair)
{
    (void) pair;
}
CLEAN_AS(func_ov004_0220d3b4, NodePair_Destruct)

/* func_ov004_0220d3b8: no nodes. */
void NodePair_Construct(NodePair *pair)
{
    pair->nodes[1] = -1;
    pair->nodes[0] = -1;
    pair->found = 0;
}
CLEAN_AS(func_ov004_0220d3b8, NodePair_Construct)

/* ---- The glows (0x748, and sets of three in derived classes) ---- */

#define WHITE_COMPONENT (31 << 12)  /* a colour component's maximum, in 20.12 fixed point */
#define G3D_MATERIAL_EMISSION 0x400 /* the material flag NNSi_G3dModifyMatFlag turns */

/* The names of a set's three materials ("mn_m", "mn_m0" and "mn_m1"). */
extern const char *const data_ov004_0224fdf8[3];

/* NitroSDK's G3D global state; the word at 0x18 holds the material colours, the ambient one
 * (5 bits each of red, green and blue) in its high half. */
extern const u32 data_027e0148[];

extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern int func_ov004_0220d258(int glow);
extern char *func_ov004_0220d268(char *glow);

extern void NNSi_G3dModifyMatFlag(G3dModel *model, int on, int flag);
extern void NNS_G3dMdlSetMdlEmi(G3dModel *model, int material, int colour);

/* func_ov004_0220d030: each glow's frame, once the set is bound. */
void GlowSet_Update(GlowSet *set)
{
    if (set->bound != 0) {
        for (int i = 0; i < 3; i++) {
            Glow_Update(&set->glows[i]);
        }
    }
}
CLEAN_AS(func_ov004_0220d030, GlowSet_Update)

/* func_ov004_0220d058: each glow on or off, once the set is bound; whether any said so. */
int GlowSet_Switch(GlowSet *set, int on, int fade, int flash)
{
    int any = 0;
    if (set->bound != 0) {
        for (int i = 0; i < 3; i++) {
            any = (any | Glow_Switch(&set->glows[i], on, fade, flash)) != 0;
        }
    }
    return any;
}
CLEAN_AS(func_ov004_0220d058, GlowSet_Switch)

/* func_ov004_0220d0a0: the three glows on the model's materials "mn_m", "mn_m0" and "mn_m1";
 * whether any is there. */
int GlowSet_Bind(GlowSet *set, G3dModel *model, int on)
{
    set->bound = 0;
    for (unsigned int i = 0; i < 3; i++) {
        set->bound = (set->bound | Glow_Bind(&set->glows[i], model, data_ov004_0224fdf8[i], on)) != 0;
    }
    return set->bound;
}
CLEAN_AS(func_ov004_0220d0a0, GlowSet_Bind)

/* func_ov004_0220d0f4: the three glows destroyed by the C++ runtime. */
GlowSet *GlowSet_Destruct(GlowSet *set)
{
    __cxa_vec_cleanup(set, 3, sizeof(Glow), (void (*)(void *)) func_ov004_0220d258);
    return set;
}
CLEAN_AS(func_ov004_0220d0f4, GlowSet_Destruct)

/* func_ov004_0220d110: the three glows built by the C++ runtime; not bound. */
GlowSet *GlowSet_Construct(GlowSet *set)
{
    __cxa_vec_ctor(set, 3, sizeof(Glow), (void (*)(void *)) func_ov004_0220d268, (void (*)(void *)) func_ov004_0220d258);
    set->bound = 0;
    return set;
}
CLEAN_AS(func_ov004_0220d110, GlowSet_Construct)

/* func_ov004_0220d140: the colour the glow starts from, the scene's ambient material colour. */
int Glow_BaseColour(void)
{
    return (int) (data_027e0148[6] >> 16);
}
CLEAN_AS(func_ov004_0220d140, Glow_BaseColour)

/* func_ov004_0220d150: the fader's frame; while its level is not 0, the glowing material's
 * emission is the base colour brought towards white by the level (blue, red, then green) and the
 * other materials' emission the base colour; at level 0 the emission is turned off. */
void Glow_Update(Glow *glow)
{
    if (glow->material == -1) {
        return;
    }
    Fader_Run(&glow->fader);
    int level = Fader_Level(&glow->fader);
    if (level == 0) {
        NNSi_G3dModifyMatFlag(glow->model, 0, G3D_MATERIAL_EMISSION);
        return;
    }
    NNSi_G3dModifyMatFlag(glow->model, 1, G3D_MATERIAL_EMISSION);
    int base = Glow_BaseColour();
    int blue = Fader_Mix(level, ((base >> 10) & 0x1f) << 12, WHITE_COMPONENT);
    int red = Fader_Mix(level, (base & 0x1f) << 12, WHITE_COMPONENT);
    int green = Fader_Mix(level, ((base >> 5) & 0x1f) << 12, WHITE_COMPONENT);
    /* QUIRK: the components are not clamped; the sum is cut to 16 bits. */
    u32 bits = ((u32) shift_right(blue, 12) << 10) | (u32) shift_right(red, 12) | ((u32) shift_right(green, 12) << 5);
    int lit = (u16) bits;
    for (int i = 0; i < glow->model->material_count; i++) {
        NNS_G3dMdlSetMdlEmi(glow->model, i, i == glow->material ? lit : base);
    }
}
CLEAN_AS(func_ov004_0220d150, Glow_Update)

/* func_ov004_0220d208: the glow on or off, faded or at once, flashing when it comes on; at the
 * fader's speed 0x800. Whether the fader started to fade. */
int Glow_Switch(Glow *glow, int on, int fade, int flash)
{
    return Fader_Switch(&glow->fader, on, fade, flash, 0x800);
}
CLEAN_AS(func_ov004_0220d208, Glow_Switch)

/* func_ov004_0220d220: the glow on the model's material `name`, on or off at once; whether the
 * model has it. Without a model nothing changes. */
int Glow_Bind(Glow *glow, G3dModel *model, const char *name, int on)
{
    if (model != NULL) {
        glow->material = (s8) G3dRes_MaterialIndex((const u8 *) model, name);
        if (glow->material != -1) {
            Fader_Set(&glow->fader, on);
            glow->model = model;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0220d220, Glow_Bind)

/* func_ov004_0220d258: returns the glow's address. */
int Glow_Destruct(Glow *glow)
{
    Fader_Destruct(&glow->fader);
    return (int) (uintptr_t) glow;
}
CLEAN_AS(func_ov004_0220d258, Glow_Destruct)

/* func_ov004_0220d268: off, on no material. */
Glow *Glow_Construct(Glow *glow)
{
    Fader_Construct(&glow->fader);
    glow->material = -1;
    glow->model = NULL;
    return glow;
}
CLEAN_AS(func_ov004_0220d268, Glow_Construct)

/* ---- The mount (0x17c) ---- */

#define MOUNT_PARENTS 28 /* the parent indexes kept */

/* The scratch matrix RoomObject_BuildMatrix builds an object's matrix into. */
extern Mtx43 data_021fbe48;

extern int MTX_Inverse43(const Mtx43 *mtx, Mtx43 *inverse);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);

/* func_ov004_0220d3c8: the object on the floor (layer 0) at cell (x, y), as a parent: its index
 * among the room's objects, the top of the cell's centre in its space, and `facing` relative to
 * its angle. Whether there is one (with an index). */
int Mount_Locate(int *parent, Vec3 *offset, s16 *angle, int x, int y, s16 facing)
{
    RoomObject *below = RoomObjects_GridObjectAt(RoomObjects_Grid(), x, y, 0);
    int index = RoomObjects_IndexOf(RoomObjects_Table(), below);
    if (below == NULL || index == -1) {
        return 0;
    }
    Vec3 centre;
    AcreTile_TileCentre(&centre, (unsigned int) x, (unsigned int) y);
    centre.y = below->top_height;
    RoomObject_BuildMatrix(below, NULL, 0);
    MTX_Inverse43(&data_021fbe48, &data_021fbe48);
    Vec3 local;
    MTX_MultVec43(&centre, &data_021fbe48, &local);
    *parent = index;
    *offset = local;
    *angle = (s16) (facing - below->angle);
    return 1;
}
CLEAN_AS(func_ov004_0220d3c8, Mount_Locate)

/* func_ov004_0220d45c: the mount on the object at cell (x, y), if there is one; whether it was
 * set. */
int Mount_AttachAt(Mount *mount, int x, int y, int facing)
{
    int parent;
    Vec3 offset;
    s16 angle;
    /* QUIRK: the facing is passed on cut to 16 bits. */
    if (Mount_Locate(&parent, &offset, &angle, x, y, (s16) facing) != 0) {
        return Mount_Set(mount, parent, &offset, angle);
    }
    return 0;
}
CLEAN_AS(func_ov004_0220d45c, Mount_AttachAt)

/* func_ov004_0220d494: the parent, offset and angle, for parent indexes 0-27; whether they were
 * set. */
int Mount_Set(Mount *mount, int parent, const Vec3 *offset, int angle)
{
    if (parent >= 0 && parent < MOUNT_PARENTS) {
        mount->parent = (s16) parent;
        mount->offset = *offset;
        mount->angle = (s16) angle;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0220d494, Mount_Set)

/* func_ov004_0220d4b4 */
int Mount_Angle(const Mount *mount)
{
    return mount->angle;
}
CLEAN_AS(func_ov004_0220d4b4, Mount_Angle)

/* func_ov004_0220d4bc */
Vec3 *Mount_Offset(Mount *mount)
{
    return &mount->offset;
}
CLEAN_AS(func_ov004_0220d4bc, Mount_Offset)

/* func_ov004_0220d4c0 */
int Mount_Parent(const Mount *mount)
{
    return mount->parent;
}
CLEAN_AS(func_ov004_0220d4c0, Mount_Parent)

/* func_ov004_0220d4c8 */
int Mount_IsSet(const Mount *mount)
{
    return mount->parent != -1;
}
CLEAN_AS(func_ov004_0220d4c8, Mount_IsSet)

/* func_ov004_0220d4d8 */
void Mount_Destruct(Mount *mount)
{
    (void) mount;
}
CLEAN_AS(func_ov004_0220d4d8, Mount_Destruct)

/* func_ov004_0220d4dc: no parent. */
void Mount_Construct(Mount *mount)
{
    mount->parent = -1;
    mount->offset.x = 0;
    mount->offset.y = 0;
    mount->offset.z = 0;
    mount->angle = 0;
}
CLEAN_AS(func_ov004_0220d4dc, Mount_Construct)

/* ---- The model files' animations ---- */

extern unsigned int func_021077e8(unsigned int *file);

/* func_ov004_0220d9bc: what func_021077e8 reads from the file at 0x28, or 0 without one. */
int AnimSet_File28(const AnimSet *set)
{
    if (set->file_28 != 0) {
        return (int) func_021077e8((unsigned int *) (uintptr_t) set->file_28);
    }
    return 0;
}
CLEAN_AS(func_ov004_0220d9bc, AnimSet_File28)

/* func_ov004_0220d9d4; the variant is taken modulo 2, as in the four below. */
int AnimSet_Anim20(const AnimSet *set, int variant)
{
    return (int) set->anim_20[variant & 1];
}
CLEAN_AS(func_ov004_0220d9d4, AnimSet_Anim20)

/* func_ov004_0220d9e0 */
int AnimSet_Anim18(const AnimSet *set, int variant)
{
    return (int) set->anim_18[variant & 1];
}
CLEAN_AS(func_ov004_0220d9e0, AnimSet_Anim18)

/* func_ov004_0220d9ec */
int AnimSet_Anim10(const AnimSet *set, int variant)
{
    return (int) set->anim_10[variant & 1];
}
CLEAN_AS(func_ov004_0220d9ec, AnimSet_Anim10)

/* func_ov004_0220d9f8 */
int AnimSet_Anim08(const AnimSet *set, int variant)
{
    return (int) set->anim_08[variant & 1];
}
CLEAN_AS(func_ov004_0220d9f8, AnimSet_Anim08)

/* func_ov004_0220da04 */
int AnimSet_Anim00(const AnimSet *set, int variant)
{
    return (int) set->anim_00[variant & 1];
}
CLEAN_AS(func_ov004_0220da04, AnimSet_Anim00)

/* func_ov004_0220da10 */
void AnimSet_SetFile28(AnimSet *set, u32 file)
{
    set->file_28 = file;
}
CLEAN_AS(func_ov004_0220da10, AnimSet_SetFile28)

/* func_ov004_0220da14; the variant is taken modulo 2, as in the four below. */
void AnimSet_SetAnim20(AnimSet *set, u32 anim, int variant)
{
    set->anim_20[variant & 1] = anim;
}
CLEAN_AS(func_ov004_0220da14, AnimSet_SetAnim20)

/* func_ov004_0220da20 */
void AnimSet_SetAnim18(AnimSet *set, u32 anim, int variant)
{
    set->anim_18[variant & 1] = anim;
}
CLEAN_AS(func_ov004_0220da20, AnimSet_SetAnim18)

/* func_ov004_0220da2c */
void AnimSet_SetAnim10(AnimSet *set, u32 anim, int variant)
{
    set->anim_10[variant & 1] = anim;
}
CLEAN_AS(func_ov004_0220da2c, AnimSet_SetAnim10)

/* func_ov004_0220da38 */
void AnimSet_SetAnim08(AnimSet *set, u32 anim, int variant)
{
    set->anim_08[variant & 1] = anim;
}
CLEAN_AS(func_ov004_0220da38, AnimSet_SetAnim08)

/* func_ov004_0220da44 */
void AnimSet_SetAnim00(AnimSet *set, u32 anim, int variant)
{
    set->anim_00[variant & 1] = anim;
}
CLEAN_AS(func_ov004_0220da44, AnimSet_SetAnim00)

/* func_ov004_0220da50 */
void AnimSet_Destruct(AnimSet *set)
{
    (void) set;
}
CLEAN_AS(func_ov004_0220da50, AnimSet_Destruct)

/* func_ov004_0220da54: no animations and no texture copy.
 * BUG: the visibility animations (anim_10) are left as they were. */
void AnimSet_Construct(AnimSet *set)
{
    set->file_28 = 0;
    for (int i = 0; i < 2; i++) {
        set->anim_00[i] = 0;
        set->anim_08[i] = 0;
#ifdef BUGFIX
        set->anim_10[i] = 0;
#endif
        set->anim_18[i] = 0;
        set->anim_20[i] = 0;
    }
}
CLEAN_AS(func_ov004_0220da54, AnimSet_Construct)
