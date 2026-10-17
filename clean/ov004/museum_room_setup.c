/* The processes that set up the scenes with obj_etc_museum spots (museum_room_setup.h). */
#include "museum_room_setup.h"

#include "autoload_2/heap.h" /* Heap_AllocAuxZeroed, Heap_FreeAux */
#include "clean.h"
#include "etc_museum.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/furniture_info.h"
#include "main/museum_record.h"
#include "main/scene_query.h"

static_assert(sizeof(MuseumSetup) == 0x50, "the process");
static_assert(sizeof(MuseumSetupSpot) == 0x1c, "a spot");
static_assert(offsetof(MuseumSetupSpot, kind) == 0x19, "a spot's kind");
static_assert(sizeof(MuseumSetupRow) == 0xc, "a row");

/* What class 82 puts in place of a missing group A item whose furniture shape is 0. */
#define MUSEUM_SETUP_STAND_IN 0x4a54

/* The vtables: classes 83, 82 and 81, and the scene class of autoload_2. */
extern const u32 data_ov004_022566d8[];
extern const u32 data_ov004_02256780[];
extern const u32 data_ov004_0225672c[];
extern const u32 data_020da13c[];

/* The spots of each scene. */
extern MuseumSetupRow data_ov004_0224b868[MUSEUM_SETUP_ROWS];

/* The scene's map, and the museum's record. */
extern AcreMap *data_021c80bc;
extern MuseumRecord data_021f38f8;

/* Class 82's two item codes: function-local statics of the game's, built and registered for
 * destruction (with func_020051b0) the first time, a guard bit each. */
extern u16 data_ov004_0225f538; /* MUSEUM_SETUP_STAND_IN */
extern u16 data_ov004_0225f534; /* the empty tile */
extern u32 data_ov004_0225f53c;
extern u32 data_ov004_0225f540;
extern u8 data_ov004_0225f754[];
extern u8 data_ov004_0225f634[];

extern void __register_global_object(void *object, void *destruct, void *record);
/* The destructor of an item code (TrivialObject_DestructItemCode), as the game registers it. */
extern void func_020051b0(void *item);

/* A spot's position (the spot itself). */
extern Vec3 *func_ov004_02245554(const MuseumSetupSpot *spot);

/* func_ov004_022451c0 (class 83's slot 18): nothing to set up. */
int MuseumSetupPlain_SetUpScene(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022451c0, MuseumSetupPlain_SetUpScene)

/* func_ov004_022451c4 (class 83's slot 17): the destructor, and the process freed. */
MuseumSetup *MuseumSetupPlain_DestructFree(MuseumSetup *self)
{
    self->base.vtable = data_ov004_022566d8;
    MuseumSetup_DestructBase(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_022451c4, MuseumSetupPlain_DestructFree)

/* func_ov004_022451e4 (class 83's slot 16): the destructor. */
MuseumSetup *MuseumSetupPlain_Destruct(MuseumSetup *self)
{
    self->base.vtable = data_ov004_022566d8;
    MuseumSetup_DestructBase(self);
    return self;
}
CLEAN_AS(func_ov004_022451e4, MuseumSetupPlain_Destruct)

/* func_ov004_022451fc: class 83's constructor. */
MuseumSetup *MuseumSetupPlain_Construct(MuseumSetup *self)
{
    MuseumSetup_ConstructBase(self);
    self->base.vtable = data_ov004_022566d8;
    return self;
}
CLEAN_AS(func_ov004_022451fc, MuseumSetupPlain_Construct)

/* func_ov004_02245214 (class 83's profile): a process of class 83 from the auxiliary heap. */
void MuseumSetupPlain_New(void)
{
    MuseumSetup *self = Heap_AllocAuxZeroed(sizeof(MuseumSetup));
    if (self == NULL) {
        return;
    }
    MuseumSetupPlain_Construct(self);
}
CLEAN_AS(func_ov004_02245214, MuseumSetupPlain_New)

/* Class 82's two item codes, built and registered the first time. */
static void MuseumSetupGroupA_init_codes(void)
{
    if ((data_ov004_0225f53c & 1) == 0) {
        data_ov004_0225f538 = MUSEUM_SETUP_STAND_IN;
        __register_global_object(&data_ov004_0225f538, (void *) (uintptr_t) func_020051b0, data_ov004_0225f754);
        data_ov004_0225f53c |= 1;
    }
    if ((data_ov004_0225f540 & 1) == 0) {
        data_ov004_0225f534 = ACRE_MAP_ITEM_NONE;
        __register_global_object(&data_ov004_0225f534, (void *) (uintptr_t) func_020051b0, data_ov004_0225f634);
        data_ov004_0225f540 |= 1;
    }
}

/* func_ov004_0224522c (class 82's slot 18): each tile of the scene's acre (0, 0), row by row,
 * holding an item of the museum record's group A that nobody has given gets item 0x4a54 when
 * the item's furniture shape is 0, else the empty tile. */
int MuseumSetupGroupA_ClearMissing(void)
{
    AcreMap *map = data_021c80bc;
    for (int z = 0; z < 16; z++) {
        for (int x = 0; x < 16; x++) {
            u16 *item = AcreTile_ItemInAcre(map, 0, 0, x, z, 0);
            if (item == NULL || *item < MUSEUM_A_FIRST || *item > MUSEUM_A_LAST) {
                continue;
            }
            if (MuseumRecord_IsGiven(&data_021f38f8, item)) {
                continue;
            }
            MuseumSetupGroupA_init_codes();
            u16 code;
            if (FurnitureInfo_ItemShape(item) == 0) {
                code = data_ov004_0225f538;
            } else {
                code = data_ov004_0225f534;
            }
            AcreTile_SetItemInAcre(map, &code, 0, 0, x, z, 0);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_0224522c, MuseumSetupGroupA_ClearMissing)

/* func_ov004_02245358 (class 82's slot 17): the destructor, and the process freed. */
MuseumSetup *MuseumSetupGroupA_DestructFree(MuseumSetup *self)
{
    self->base.vtable = data_ov004_02256780;
    MuseumSetup_DestructBase(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_02245358, MuseumSetupGroupA_DestructFree)

/* func_ov004_02245378 (class 82's slot 16): the destructor. */
MuseumSetup *MuseumSetupGroupA_Destruct(MuseumSetup *self)
{
    self->base.vtable = data_ov004_02256780;
    MuseumSetup_DestructBase(self);
    return self;
}
CLEAN_AS(func_ov004_02245378, MuseumSetupGroupA_Destruct)

/* func_ov004_02245390: class 82's constructor. */
MuseumSetup *MuseumSetupGroupA_Construct(MuseumSetup *self)
{
    MuseumSetup_ConstructBase(self);
    self->base.vtable = data_ov004_02256780;
    return self;
}
CLEAN_AS(func_ov004_02245390, MuseumSetupGroupA_Construct)

/* func_ov004_022453a8 (class 82's profile): a process of class 82 from the auxiliary heap. */
void MuseumSetupGroupA_New(void)
{
    MuseumSetup *self = Heap_AllocAuxZeroed(sizeof(MuseumSetup));
    if (self == NULL) {
        return;
    }
    MuseumSetupGroupA_Construct(self);
}
CLEAN_AS(func_ov004_022453a8, MuseumSetupGroupA_New)

/* func_ov004_022453c0: the current scene's obj_etc_museum spots made, from the first row of
 * data_ov004_0224b868 for that scene. */
void MuseumSetup_SpawnSpots(void)
{
    int scene = SceneQuery_Current();
    for (u32 i = 0; i < MUSEUM_SETUP_ROWS; i++) {
        MuseumSetupRow *row = &data_ov004_0224b868[i];
        if (scene != row->scene) {
            continue;
        }
        u32 count = row->count;
        for (u32 j = 0; j < count; j++) {
            const MuseumSetupSpot *spot = &row->spots[j];
            /* Each value is read by its own call, in this order. */
            int kind = MuseumSetupSpot_Kind(spot);
            Vec3 *position = func_ov004_02245554(spot);
            int yaw = MuseumSetupSpot_Yaw(spot);
            int face_angle = (int) MuseumSetupSpot_FaceAngle(spot);
            s16 complete_message = MuseumSetupSpot_CompleteMessage(spot);
            const u8 *exhibits = (const u8 *) (uintptr_t) MuseumSetupSpot_Exhibits(spot);
            int spots = MuseumSetupSpot_Count(spot);
            EtcMuseum_Spawn(kind, position, yaw, face_angle, complete_message, exhibits, spots);
        }
        break;
    }
}
CLEAN_AS(func_ov004_022453c0, MuseumSetup_SpawnSpots)

/* func_ov004_02245454 (slot 6): the execution is done at once. */
int MuseumSetup_Execute(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02245454, MuseumSetup_Execute)

/* func_ov004_02245458 (class 81's slot 18): nothing to set up. */
int MuseumSetup_SetUpScene(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02245458, MuseumSetup_SetUpScene)

/* func_ov004_0224545c (slot 0): the creation: the scene's spots, then the class's own set-up
 * (slot 18); done at once. */
int MuseumSetup_Create(MuseumSetup *self)
{
    MuseumSetup_SpawnSpots();
    ((void (*)(MuseumSetup *))(uintptr_t) self->base.vtable[MUSEUM_SETUP_SLOT_SCENE])(self);
    return 1;
}
CLEAN_AS(func_ov004_0224545c, MuseumSetup_Create)

/* func_ov004_02245474: class 81's destructor, as the derived classes' call it. */
MuseumSetup *MuseumSetup_DestructBase(MuseumSetup *self)
{
    self->base.vtable = data_ov004_0225672c;
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_ov004_02245474, MuseumSetup_DestructBase)

/* func_ov004_02245494 (class 81's slot 17): the destructor, and the process freed. */
MuseumSetup *MuseumSetup_DestructFree(MuseumSetup *self)
{
    self->base.vtable = data_ov004_0225672c;
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_02245494, MuseumSetup_DestructFree)

/* func_ov004_022454bc (class 81's slot 16): the destructor. */
MuseumSetup *MuseumSetup_Destruct(MuseumSetup *self)
{
    self->base.vtable = data_ov004_0225672c;
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_ov004_022454bc, MuseumSetup_Destruct)

/* func_ov004_022454dc: class 81's constructor, as its profile calls it. */
MuseumSetup *MuseumSetup_Construct(MuseumSetup *self)
{
    Process_Construct(&self->base);
    self->base.vtable = data_020da13c;
    self->base.vtable = data_ov004_0225672c;
    return self;
}
CLEAN_AS(func_ov004_022454dc, MuseumSetup_Construct)

/* func_ov004_022454fc: class 81's constructor, as the derived classes' call it. */
MuseumSetup *MuseumSetup_ConstructBase(MuseumSetup *self)
{
    Process_Construct(&self->base);
    self->base.vtable = data_020da13c;
    self->base.vtable = data_ov004_0225672c;
    return self;
}
CLEAN_AS(func_ov004_022454fc, MuseumSetup_ConstructBase)

/* func_ov004_0224551c (class 81's profile): a process of class 81 from the auxiliary heap. */
void MuseumSetup_New(void)
{
    MuseumSetup *self = Heap_AllocAuxZeroed(sizeof(MuseumSetup));
    if (self == NULL) {
        return;
    }
    MuseumSetup_Construct(self);
}
CLEAN_AS(func_ov004_0224551c, MuseumSetup_New)

/* func_ov004_02245534 */
unsigned char MuseumSetupSpot_Count(const MuseumSetupSpot *spot)
{
    return spot->count;
}
CLEAN_AS(func_ov004_02245534, MuseumSetupSpot_Count)

/* func_ov004_02245538 */
u32 MuseumSetupSpot_Exhibits(const MuseumSetupSpot *spot)
{
    return (u32) (uintptr_t) spot->exhibits;
}
CLEAN_AS(func_ov004_02245538, MuseumSetupSpot_Exhibits)

/* func_ov004_0224553c */
short MuseumSetupSpot_CompleteMessage(const MuseumSetupSpot *spot)
{
    return spot->complete_message;
}
CLEAN_AS(func_ov004_0224553c, MuseumSetupSpot_CompleteMessage)

/* func_ov004_02245544 */
unsigned char MuseumSetupSpot_Kind(const MuseumSetupSpot *spot)
{
    return spot->kind;
}
CLEAN_AS(func_ov004_02245544, MuseumSetupSpot_Kind)

/* func_ov004_02245548 */
u32 MuseumSetupSpot_FaceAngle(const MuseumSetupSpot *spot)
{
    return spot->face_angle;
}
CLEAN_AS(func_ov004_02245548, MuseumSetupSpot_FaceAngle)

/* func_ov004_0224554c */
int MuseumSetupSpot_Yaw(const MuseumSetupSpot *spot)
{
    return spot->yaw;
}
CLEAN_AS(func_ov004_0224554c, MuseumSetupSpot_Yaw)
