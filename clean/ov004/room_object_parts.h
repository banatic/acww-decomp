/* Small parts of overlay 4's room objects (room_object.h), each a member the constructor
 * RoomObject_Construct builds and the destructor RoomObject_DestructBase takes down:
 *
 * - a switch (0x740): a value the object's class shows (0 or 1), with a wanted value that
 *   touching the object toggles and that is applied when the class is ready; it is kept in the
 *   town's map record for the object's cell;
 * - two nodes of the object's model (0x742), the ones named "kh_j" and "km_j";
 * - a glow (0x748): a material of the model whose emission colour fades towards white, and in
 *   some derived classes a set of three of them;
 * - a mount (0x17c): the object another object stands on, by its index among the room's
 *   objects, with the position and angle relative to it;
 * - the animations of the object's model files (at 0x44 in the member at 0x6cc), in pairs. */
#ifndef CLEAN_OV004_ROOM_OBJECT_PARTS_H
#define CLEAN_OV004_ROOM_OBJECT_PARTS_H

#include "types.h"

#include "autoload_2/approach.h" /* Vec3 */

struct RoomObject;

/* The switch: `shown` is what the object shows, `wanted` what it will show. */
typedef struct Switch {
    u8 shown;
    u8 wanted;
} Switch;

/* Two node indexes of the model (-1 when it has no such node), and whether either was found. */
typedef struct NodePair {
    s8 nodes[2];
    u8 found;
} NodePair;

/* A model resource (NitroSDK's NNSG3dResMdl): only its material count is read here. */
typedef struct G3dModel {
    u8 unk_00[0x18];
    u8 material_count;
} G3dModel;

/* A level that moves towards a target by a speed, or flashes through a table of 11 levels
 * after a wait of 5 frames (Fader_Run runs it, Fader_Switch sets it). */
typedef struct Fader {
    fx32 level;
    fx32 target;
    fx32 speed;
    s32 flashing;
    u16 flash_step;
    u16 flash_wait;
} Fader;

/* A material of `model` that glows by the fader's level (-1 when it has none). */
typedef struct Glow {
    Fader fader;
    s8 material;
    u8 unk_15[3];
    G3dModel *model;
} Glow;

/* Three glows, on the materials named "mn_m", "mn_m0" and "mn_m1"; `bound` when any of them was
 * found. */
typedef struct GlowSet {
    Glow glows[3];
    u8 bound;
} GlowSet;

/* The object this one stands on: its index among the room's objects (-1 for none), this
 * object's angle relative to it and its position in that object's space. */
typedef struct Mount {
    s16 parent;
    s16 angle;
    Vec3 offset;
} Mount;

/* The animations of the object's model files, each in two variants (the files "...0" and
 * "...1" of the furniture's archive, furniture_model.c), and a copy of its texture file, which
 * func_021077e8 reads. The comments say who uses them. */
typedef struct AnimSet {
    u32 anim_00[2]; /* joints ("bca"); applied to the model at 0x538 (AnimatedModel_Start) */
    u32 anim_08[2]; /* material colours ("bma"); given to the animation at 0x7c4 */
    u32 anim_10[2]; /* visibility ("bva"); given to the animation at 0x824 */
    u32 anim_18[2]; /* texture coordinates ("bta"); given to the animation at 0x7e4 */
    u32 anim_20[2]; /* texture patterns ("btp"); given to the animation at 0x804 */
    u32 file_28;    /* the copy of the texture file, when one is kept */
} AnimSet;

void Switch_Set(Switch *sw, u8 value, int pending);
void Switch_Toggle(Switch *sw, int pending);
int Switch_IsPending(const Switch *sw);
u8 Switch_Value(const Switch *sw);
void Switch_Save(const Switch *sw, struct RoomObject *object);
int Switch_Apply(Switch *sw, struct RoomObject *object);
void Switch_Load(Switch *sw, struct RoomObject *object);
void Switch_Destruct(Switch *sw);
void Switch_Construct(Switch *sw);

void NodePair_Set(NodePair *pair, s8 first, s8 second);
void NodePair_Destruct(NodePair *pair);
void NodePair_Construct(NodePair *pair);

void GlowSet_Update(GlowSet *set);
int GlowSet_Switch(GlowSet *set, int on, int fade, int flash);
int GlowSet_Bind(GlowSet *set, G3dModel *model, int on);
GlowSet *GlowSet_Destruct(GlowSet *set);
GlowSet *GlowSet_Construct(GlowSet *set);
int Glow_BaseColour(void);
void Glow_Update(Glow *glow);
int Glow_Switch(Glow *glow, int on, int fade, int flash);
int Glow_Bind(Glow *glow, G3dModel *model, const char *name, int on);
int Glow_Destruct(Glow *glow);
Glow *Glow_Construct(Glow *glow);

int Mount_Locate(int *parent, Vec3 *offset, s16 *angle, int x, int y, s16 facing);
int Mount_AttachAt(Mount *mount, int x, int y, int facing);
int Mount_Set(Mount *mount, int parent, const Vec3 *offset, int angle);
int Mount_Angle(const Mount *mount);
Vec3 *Mount_Offset(Mount *mount);
int Mount_Parent(const Mount *mount);
int Mount_IsSet(const Mount *mount);
void Mount_Destruct(Mount *mount);
void Mount_Construct(Mount *mount);

int AnimSet_File28(const AnimSet *set);
int AnimSet_Anim20(const AnimSet *set, int variant);
int AnimSet_Anim18(const AnimSet *set, int variant);
int AnimSet_Anim10(const AnimSet *set, int variant);
int AnimSet_Anim08(const AnimSet *set, int variant);
int AnimSet_Anim00(const AnimSet *set, int variant);
void AnimSet_SetFile28(AnimSet *set, u32 file);
void AnimSet_SetAnim20(AnimSet *set, u32 anim, int variant);
void AnimSet_SetAnim18(AnimSet *set, u32 anim, int variant);
void AnimSet_SetAnim10(AnimSet *set, u32 anim, int variant);
void AnimSet_SetAnim08(AnimSet *set, u32 anim, int variant);
void AnimSet_SetAnim00(AnimSet *set, u32 anim, int variant);
void AnimSet_Destruct(AnimSet *set);
void AnimSet_Construct(AnimSet *set);

#endif
