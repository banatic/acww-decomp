/* A villager's house: its files and models, its checks of the villager and the talk at its
 * closed door (villager_house.h). */
#include "villager_house.h"

#include <stdint.h>

#include "autoload_2/heap.h" /* Heap, Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "house_files.h"
#include "itcm/vector.h"         /* Vec_Add */
#include "main/actor.h"          /* Actor_Spawn */
#include "main/npc_id.h"         /* NpcId, NpcId_Personality, NpcId_FormatName */
#include "main/session.h"        /* NetSession, Session_IsSlotTaken */
#include "main/trivial_object.h" /* TrivialObject_Destruct */
#include "main/animated_model.h"
#include "main/c_library.h"
#include "main/frame_ctrl.h"
#include "main/link_scene.h"
#include "main/message_receiver.h"
#include "main/model_anim.h"
#include "main/model_object.h"
#include "main/player_id.h"
#include "main/scene_query.h"
#include "main/talk_object.h"
#include "main/town_villager.h"
#include "main/villager_data.h"
#include "main/villager_roster.h"
#include "main/villager_status.h"
#include "ov009/scene_actor_life.h"

static_assert(offsetof(VillagerHouse, position) == 0x5c, "position");
static_assert(offsetof(VillagerHouse, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(VillagerHouse, message) == 0x10a, "receiver byte 0x1e");
static_assert(offsetof(VillagerHouse, link) == 0x12c, "link");
static_assert(offsetof(VillagerHouse, code) == 0x136, "code");
static_assert(offsetof(VillagerHouse, model_object) == 0x13c, "model object");
static_assert(offsetof(VillagerHouse, model) == 0x198, "model");
static_assert(offsetof(VillagerHouse, matrix) == 0x1a0, "model object matrix");
static_assert(offsetof(VillagerHouse, flags_235) == 0x235, "flags 0x235");
static_assert(offsetof(VillagerHouse, flags) == 0x236, "flags");
static_assert(offsetof(VillagerHouse, message_set) == 0x237, "message set");
static_assert(offsetof(VillagerHouse, x_model) == 0x2b4, "X model");
static_assert(offsetof(VillagerHouse, x_anim) == 0x36c, "X animation");
static_assert(sizeof(VillagerHouse) == 0x38c, "the size VillagerHouse_New allocates");
static_assert(offsetof(VillagerHouseModel, resource) == 0x5c, "model resource");
static_assert(offsetof(VillagerHouseModel, matrix) == 0x64, "model matrix");
static_assert(sizeof(VillagerHouseModel) == 0xb8, "model object");
static_assert(offsetof(VillagerHouseAnim, frame) == 0x08, "anim frame");
static_assert(offsetof(VillagerHouseAnim, target) == 0x18, "anim target");
static_assert(sizeof(VillagerHouseAnim) == 0x20, "anim");

#define VILLAGER_HOUSE_RECEIVER_OFFSET 0xec
#define VILLAGER_HOUSE_VILLAGERS 8
#define VILLAGER_HOUSE_VILLAGER_PROFILE 0x18 /* the villager it makes */
#define VILLAGER_HOUSE_LOOK_MASK 0x1f        /* the bits of the look byte that count */
#define VILLAGER_HOUSE_KIND_SHIFT 2          /* the look's kind is above its variant */
#define VILLAGER_HOUSE_VARIANT_MASK 3
#define VILLAGER_HOUSE_ONE 0x1000 /* normal speed, 20.12 fixed point */

#define VILLAGER_HOUSE_FIRST_CODE 0x5001
#define VILLAGER_HOUSE_LAST_CODE 0x5008
#define VILLAGER_HOUSE_MESSAGE_GONE 6 /* when func_0207f1d4 says there is no villager */
#define VILLAGER_HOUSE_STATUS_AWAY 2  /* the status for which the session's slots are looked at */
#define VILLAGER_HOUSE_SESSION_SLOTS 4

/* The eight villagers (0x7ec bytes each). */
extern u8 data_021e5a2c[];
/* "obj_etc_closed" and "obj_etc_error", the names the receiver gets. */
extern const char data_ov003_02239064[];
extern const char data_ov003_02239074[];
/* The door's message by the villager's personality: the first table and the second. */
extern const u8 data_ov003_0223664c[];
extern const u8 data_ov003_02236644[];
/* The session of the wireless play. */
extern NetSession *data_020ccf94;

/* Overlay 3's set of house textures and animations (data_ov003_0223cea0, HouseTextures of
 * house_files.h, which HouseFiles_Textures gives) and its set from "/str/npcHsX.arc"
 * (data_ov003_0223ce80, HouseXFiles, which HouseFiles_XFiles gives). */
typedef HouseXFiles VillagerHouseXFiles;

/* The paths and the model name, in overlay 3's buffers, and their formats:
 * "/str/npcHs/%d/%s%c.nsbtx", "/str/npcHs/%d/%s%c.arc" and "obj_house%d_%d". */
extern char data_ov003_0223c970[];
extern char data_ov003_0223c948[];
extern char data_ov003_0223c914[];
extern const char data_ov003_02239084[];
extern const char data_ov003_022390a0[];
extern const char data_ov003_022390b8[];

/* The houses by villager index. */
extern VillagerHouse *data_ov003_0223c928[VILLAGER_HOUSE_VILLAGERS];
/* VillagerHouse_Init's static: where the villager stands from the house, its guard and its
 * record of the C++ runtime's list of statics to destroy. */
extern Vec3 data_ov003_0223c908;
extern u32 data_ov003_0223c8f8;
extern u8 data_ov003_0223c8fc[];
extern void __register_global_object(void *object, void *destruct, void *record);

/* Main's heap the X model's animation is bound with. */
extern Heap *data_021c9b1c;
/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_02238f28[];
extern const u8 data_ov003_02238fec[];

extern int NNS_G3dBindMdlTex(void *model, void *texture);
extern int NNS_G3dBindMdlPltt(void *model, void *texture);

typedef struct VillagerHouseText {
    u8 bytes[0x24];
} VillagerHouseText;

/* The villager's index from the special character's code, -1 when it is not a villager's. */
static int villager_house_index(const VillagerHouse *house)
{
    unsigned int code = house->code;
    if (code >= VILLAGER_HOUSE_FIRST_CODE && code <= VILLAGER_HOUSE_LAST_CODE) {
        return (int) code - VILLAGER_HOUSE_FIRST_CODE;
    }
    return -1;
}

/* Whether the villager's status is 0 or 3 to 7.
 * QUIRK: the status is asked for again for each value compared. */
static int villager_house_status_refuses(void *villager)
{
    return VillagerStatus_Get(villager) == 0 || VillagerStatus_Get(villager) == 3 || VillagerStatus_Get(villager) == 4 ||
           VillagerStatus_Get(villager) == 5 || VillagerStatus_Get(villager) == 6 || VillagerStatus_Get(villager) == 7;
}

/* func_ov003_0221d2a8 (vtable slot 0x98): always 1. */
int VillagerHouse_Slot98(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221d2a8, VillagerHouse_Slot98)

/* func_ov003_0221d2ac (vtable slot 0x90): always 1. */
int VillagerHouse_Slot90(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221d2ac, VillagerHouse_Slot90)

/* func_ov003_0221d2b0 (vtable slot 0x9c): 0 by day (6:00 to 18:00). At night 1 when there is
 * no such villager; else 0 when func_0207f1d4 says no or the status is 0 or 3 to 7; for status
 * 2 whether one of the four session slots taken names this villager in its link state; else
 * 1. */
int VillagerHouse_Slot9C(VillagerHouse *house)
{
    int index = villager_house_index(house);
    if (SceneActor_IsNight((SceneActor *) house) == 0) {
        return 0;
    }
    void *villager = VillagerRoster_At((VillagerTown *) data_021e5a2c, index);
    if (villager == NULL) {
        return 1;
    }
    if (VillagerStatus_Exists(villager) == 0) {
        return 0;
    }
    if (villager_house_status_refuses(villager)) {
        return 0;
    }
    if (VillagerStatus_Get(villager) != VILLAGER_HOUSE_STATUS_AWAY) {
        return 1;
    }
    NetSession *session = data_020ccf94;
    for (int slot = 0; slot < VILLAGER_HOUSE_SESSION_SLOTS; slot++) {
        if (Session_IsSlotTaken(session, slot) != 0) {
            u8 link_state[3];
            LinkScene_GlobalPlace(slot, &link_state[0], &link_state[1], &link_state[2]);
            if (index == SceneQuery_IndexIn11(link_state[0])) {
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_0221d2b0, VillagerHouse_Slot9C)

/* func_ov003_0221d3a4 (vtable slot 0x8c): whether there is such a villager, func_0207f1d4 says
 * yes and its status is neither 0 nor 3 to 7. */
int VillagerHouse_Slot8C(VillagerHouse *house)
{
    void *villager = VillagerRoster_At((VillagerTown *) data_021e5a2c, villager_house_index(house));
    if (villager == NULL) {
        return 0;
    }
    if (VillagerStatus_Exists(villager) == 0) {
        return 0;
    }
    if (villager_house_status_refuses(villager)) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov003_0221d3a4, VillagerHouse_Slot8C)

/* func_ov003_0221d43c (vtable slot 0x78, before a talk): names the receiver "obj_etc_closed"
 * and picks its message: VILLAGER_HOUSE_MESSAGE_GONE when func_0207f1d4 says there is no
 * villager; with VILLAGER_HOUSE_FLAG_ERROR the receiver is renamed "obj_etc_error" with
 * message 0; else, when the villager has an NpcId, the message of its personality from the
 * first table, or the second when message_set is nonzero (otherwise the message stays). The
 * villager's name goes to the link as line 0. */
void VillagerHouse_PrepareTalk(VillagerHouse *house)
{
    void *villager = VillagerRoster_At((VillagerTown *) data_021e5a2c, villager_house_index(house));
    MessageReceiver_SetName((MessageReceiver *) &house->receiver_vtable, data_ov003_02239064);
    if (VillagerStatus_Exists(villager) == 0) {
        house->message = VILLAGER_HOUSE_MESSAGE_GONE;
    } else if (house->flags & VILLAGER_HOUSE_FLAG_ERROR) {
        MessageReceiver_SetName((MessageReceiver *) &house->receiver_vtable, data_ov003_02239074);
        house->message = 0;
    } else {
        NpcId *npc = TownVillager_NpcId(villager);
        if (npc != NULL) {
            if (house->message_set == 0) {
                house->message = data_ov003_0223664c[NpcId_Personality(npc)];
            } else {
                house->message = data_ov003_02236644[NpcId_Personality(npc)];
            }
        }
    }

    VillagerHouseText text;
    PlayerIdText_Construct((PlayerIdText *) &text);
    NpcId_FormatName(TownVillager_NpcId(villager), (char *) text.bytes);
    TalkObject_SetPart(house->link, 0, (TextBase *) &text);
    PlayerIdText_Destruct((PlayerIdText *) &text);
}
CLEAN_AS(func_ov003_0221d43c, VillagerHouse_PrepareTalk)

/* func_ov003_0221d530 (vtable slot 0x68, overlay 9's second animation file): reads the joint
 * animation "/str/obj_house_o.nsbca" of overlay 3's house set and drops it.
 * QUIRK: declared without a result; in the ROM the animation is still in r0 when it returns, so
 * the caller of the slot gets it. The same holds for VillagerHouse_GetAnimI. */
void VillagerHouse_GetAnimO(void)
{
    HouseTextures_AnimO(HouseFiles_Textures());
}
CLEAN_AS(func_ov003_0221d530, VillagerHouse_GetAnimO)

/* func_ov003_0221d544 (vtable slot 0x64, overlay 9's first animation file): reads the joint
 * animation "/str/obj_house_i.nsbca" of overlay 3's house set and drops it. */
void VillagerHouse_GetAnimI(void)
{
    HouseTextures_AnimI(HouseFiles_Textures());
}
CLEAN_AS(func_ov003_0221d544, VillagerHouse_GetAnimI)

/* func_ov003_0221d558 (vtable slot 0xac, the path of a second texture): none. */
int VillagerHouse_LtTexturePath(void)
{
    return 0;
}
CLEAN_AS(func_ov003_0221d558, VillagerHouse_LtTexturePath)

/* func_ov003_0221d55c (vtable slot 0xa8): the path of the house's texture,
 * "/str/npcHs/<kind>/obj_house<kind>_<variant><letter>.nsbtx", in overlay 3's buffer.
 * REQUIRES: as VillagerHouse_Look. */
char *VillagerHouse_TexturePath(VillagerHouse *house)
{
    int look = VillagerHouse_Look(house);
    char *name = VillagerHouse_ModelName(house);
    int letter = HouseFiles_SeasonLetter();
    CLib_SPrintf(data_ov003_0223c970, data_ov003_02239084, look >> VILLAGER_HOUSE_KIND_SHIFT, name, letter);
    return data_ov003_0223c970;
}
CLEAN_AS(func_ov003_0221d55c, VillagerHouse_TexturePath)

/* func_ov003_0221d594 (vtable slot 0xa4): the path of the house's archive,
 * "/str/npcHs/<kind>/obj_house<kind>_<variant><letter>.arc", in overlay 3's buffer.
 * REQUIRES: as VillagerHouse_Look. */
char *VillagerHouse_ArchivePath(VillagerHouse *house)
{
    int look = VillagerHouse_Look(house);
    char *name = VillagerHouse_ModelName(house);
    int letter = HouseFiles_SeasonLetter();
    CLib_SPrintf(data_ov003_0223c948, data_ov003_022390a0, look >> VILLAGER_HOUSE_KIND_SHIFT, name, letter);
    return data_ov003_0223c948;
}
CLEAN_AS(func_ov003_0221d594, VillagerHouse_ArchivePath)

/* func_ov003_0221d5cc: the house's name, "obj_house<kind>_<variant>", in overlay 3's buffer.
 * REQUIRES: as VillagerHouse_Look. */
char *VillagerHouse_ModelName(VillagerHouse *house)
{
    int look = VillagerHouse_Look(house);
    CLib_SPrintf(data_ov003_0223c914, data_ov003_022390b8, look >> VILLAGER_HOUSE_KIND_SHIFT,
                 look & VILLAGER_HOUSE_VARIANT_MASK);
    return data_ov003_0223c914;
}
CLEAN_AS(func_ov003_0221d5cc, VillagerHouse_ModelName)

/* The villager's house look byte, as func_02080b64 gives it. */
static const u8 *villager_house_look_byte(const VillagerHouse *house)
{
    return VillagerData_Room(VillagerRoster_At((VillagerTown *) data_021e5a2c, villager_house_index(house)));
}

/* func_ov003_0221d5f4: the variant of the villager's house look (0 to 3).
 * REQUIRES: as VillagerHouse_Look. */
u8 VillagerHouse_Variant(VillagerHouse *house)
{
    return (u8) (*villager_house_look_byte(house) & VILLAGER_HOUSE_VARIANT_MASK);
}
CLEAN_AS(func_ov003_0221d5f4, VillagerHouse_Variant)

/* func_ov003_0221d64c: the villager's house look (0 to 31): its kind times 4 plus its variant.
 * REQUIRES: the code is a villager's and the villager has a look byte (func_02080b64 gives
 * one); otherwise the original reads the byte at address 0. */
u8 VillagerHouse_Look(VillagerHouse *house)
{
    return (u8) (*villager_house_look_byte(house) & VILLAGER_HOUSE_LOOK_MASK);
}
CLEAN_AS(func_ov003_0221d64c, VillagerHouse_Look)

/* func_ov003_0221d69c (vtable slot 0x0c, leaving the scene): overlay 3 forgets the house;
 * always 1.
 * REQUIRES: the code is a villager's; otherwise the word before the table is cleared. */
int VillagerHouse_Leave(VillagerHouse *house)
{
    data_ov003_0223c928[villager_house_index(house)] = NULL;
    return 1;
}
CLEAN_AS(func_ov003_0221d69c, VillagerHouse_Leave)

/* func_ov003_0221d6dc (vtable slot 0x24): draws the X model while the X archive is loaded;
 * always 1. */
int VillagerHouse_Draw(VillagerHouse *house)
{
    if (HouseXFiles_Loaded(HouseFiles_XFiles())) {
        AnimatedModel_Draw((AnimatedModel *) &house->x_model, 0);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221d6dc, VillagerHouse_Draw)

/* func_ov003_0221d704 (vtable slot 0x18, its update): while the X archive is loaded, the X
 * model takes the house's placement and, unless bit 0 of the flags at 0x235 is set, its
 * animation goes on and its frame is written where it goes; always 1.
 * REQUIRES: the X model's animation was bound (VillagerHouse_Init), so it has a target. */
int VillagerHouse_Update(VillagerHouse *house)
{
    if (HouseXFiles_Loaded(HouseFiles_XFiles())) {
        house->x_model.matrix = house->matrix;
        if (!(house->flags_235 & 1)) {
            FrameCtrl_Step((FrameCtrl *) &house->x_anim);
            *house->x_anim.target = house->x_anim.frame;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_0221d704, VillagerHouse_Update)

/* func_ov003_0221d76c (vtable slot 0x70, setting it up): makes the villager (profile 0x18, its
 * index as the group, the house as the parent) at the house's position moved by (-2, 1, 2)
 * units, and overlay 3 keeps the house by the villager's index. The house texture and the light
 * texture of its variant are bound to its model (the light one with its palettes), each when
 * the set has it. While the X archive is loaded, the X model of the look's kind is set up and
 * gets the archive's texture and palettes; when the animation binds to it, "obj_x_deco" plays
 * on it (mode 0, normal speed) and the X model takes the house's placement. Always 1.
 * REQUIRES: as VillagerHouse_Look; and while the archive is loaded, the look's kind is below 5
 * (the archive's last model), or a NULL model gets the textures. */
int VillagerHouse_Init(VillagerHouse *house)
{
    int index = villager_house_index(house);
    if ((data_ov003_0223c8f8 & 1) == 0) {
        data_ov003_0223c908.x = -0x2000;
        data_ov003_0223c908.y = 0x1000;
        data_ov003_0223c908.z = 0x2000;
        __register_global_object(&data_ov003_0223c908, (void *) TrivialObject_Destruct, data_ov003_0223c8fc);
        data_ov003_0223c8f8 |= 1;
    }
    Vec3 point;
    Vec_Add(&point, &house->position, &data_ov003_0223c908);
    Actor_Spawn(VILLAGER_HOUSE_VILLAGER_PROFILE, index, &point, NULL, house);
    data_ov003_0223c928[index] = house;

    int variant = VillagerHouse_Variant(house);
    void *house_texture = HouseTextures_House(HouseFiles_Textures(), variant);
    void *light_texture = HouseTextures_Light(HouseFiles_Textures(), variant);
    void *model = house->model;
    if (house_texture != NULL) {
        NNS_G3dBindMdlTex(model, house_texture);
    }
    if (light_texture != NULL) {
        NNS_G3dBindMdlTex(model, light_texture);
        NNS_G3dBindMdlPltt(model, light_texture);
    }

    if (!HouseXFiles_Loaded(HouseFiles_XFiles())) {
        return 1;
    }
    unsigned int kind = (unsigned int) VillagerHouse_Look(house) >> VILLAGER_HOUSE_KIND_SHIFT;
    if (!ModelObject_SetModel((ModelObject *) &house->x_model, HouseXFiles_Model(HouseFiles_XFiles(), kind), NULL)) {
        return 1;
    }
    void *x_model = HouseXFiles_Model(HouseFiles_XFiles(), kind);
    NNS_G3dBindMdlTex(x_model, (void *) (uintptr_t) HouseXFiles_Texture(HouseFiles_XFiles()));
    x_model = HouseXFiles_Model(HouseFiles_XFiles(), kind);
    NNS_G3dBindMdlPltt(x_model, (void *) (uintptr_t) HouseXFiles_Texture(HouseFiles_XFiles()));
    if (ModelAnim_AllocMaterialAnim((ModelAnim *) &house->x_anim, house->x_model.resource, data_021c9b1c)) {
        void *deco = (void *) (uintptr_t) HouseXFiles_Deco(HouseFiles_XFiles());
        void *texture = (void *) (uintptr_t) HouseXFiles_Texture(HouseFiles_XFiles());
        ModelAnim_StartTextured((ModelAnim *) &house->x_anim, deco, texture, 0, VILLAGER_HOUSE_ONE, 0);
        ModelAnim_Attach((ModelAnim *) &house->x_anim, ModelObject_RenderObject((ModelObject *) &house->x_model));
        house->x_model.matrix = house->matrix;
    }
    return 1;
}
CLEAN_AS(func_ov003_0221d76c, VillagerHouse_Init)

/* The vtables set back, the X model's animation and the X model destroyed, then overlay 9's
 * destructor. */
static void villager_house_destroy_parts(VillagerHouse *house)
{
    house->vtable = data_ov003_02238f28;
    house->receiver_vtable = data_ov003_02238fec;
    ModelAnim_DestructComplete((ModelAnim *) &house->x_anim);
    AnimatedModel_DestructComplete((AnimatedModel *) &house->x_model);
    SceneActor_Destruct((SceneActor *) house);
}

/* func_ov003_0221d93c (vtable slot 0x44, the deleting destructor): the destructor's work, then
 * the memory freed. */
VillagerHouse *VillagerHouse_DestroyAndFree(VillagerHouse *house)
{
    villager_house_destroy_parts(house);
    Heap_FreeAux(house);
    return house;
}
CLEAN_AS(func_ov003_0221d93c, VillagerHouse_DestroyAndFree)

/* func_ov003_0221d980 (vtable slot 0x40): the destructor. */
VillagerHouse *VillagerHouse_Destroy(VillagerHouse *house)
{
    villager_house_destroy_parts(house);
    return house;
}
CLEAN_AS(func_ov003_0221d980, VillagerHouse_Destroy)

/* func_ov003_0221d9c0: the constructor: overlay 9's, the vtables, the X model's and its
 * animation's; then overlay 3 forgets every house.
 * QUIRK: each house made clears the whole table of houses, not only its own place; the houses
 * made before it are kept again only by their set-up (VillagerHouse_Init). */
VillagerHouse *VillagerHouse_Construct(VillagerHouse *house)
{
    SceneActor_ConstructBase((SceneActor *) house);
    house->vtable = data_ov003_02238f28;
    house->receiver_vtable = data_ov003_02238fec;
    AnimatedModel_Construct((AnimatedModel *) &house->x_model);
    ModelAnim_Construct((ModelAnim *) &house->x_anim);
    for (int i = 0; i < VILLAGER_HOUSE_VILLAGERS; i++) {
        data_ov003_0223c928[i] = NULL;
    }
    return house;
}
CLEAN_AS(func_ov003_0221d9c0, VillagerHouse_Construct)

/* func_ov003_0221da10 (the house's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void VillagerHouse_New(void)
{
    VillagerHouse *house = Heap_AllocAuxZeroed(sizeof(VillagerHouse));
    if (house != NULL) {
        VillagerHouse_Construct(house);
    }
}
CLEAN_AS(func_ov003_0221da10, VillagerHouse_New)

/* ---- The receiver vtable's thunks: each finds the house around `receiver`. */

static VillagerHouse *villager_house_from_receiver(void *receiver)
{
    return (VillagerHouse *) (void *) ((u8 *) receiver - VILLAGER_HOUSE_RECEIVER_OFFSET);
}

/* _ZThn236_N18Obj_ov003_02238f28D0Ev: VillagerHouse_DestroyAndFree. */
VillagerHouse *VillagerHouse_ReceiverDestroyAndFree(void *receiver)
{
    return VillagerHouse_DestroyAndFree(villager_house_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238f28D0Ev, VillagerHouse_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_02238f28D1Ev: VillagerHouse_Destroy. */
VillagerHouse *VillagerHouse_ReceiverDestroy(void *receiver)
{
    return VillagerHouse_Destroy(villager_house_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238f28D1Ev, VillagerHouse_ReceiverDestroy)
