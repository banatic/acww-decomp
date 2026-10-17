/* The process of the items' icon models (icon_models.h). */
#include "icon_models.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(IconModels, set) == 0x174, "icon models set");

/* The class and the process base's. */
extern const u32 data_ov004_02255bd4[];
extern const u32 data_020da13c[];

/* The model set taken down, then the base. */
static void IconModels_destruct_members(IconModels *self)
{
    self->base.vtable = data_ov004_02255bd4;
    ModelSet_Destruct(&self->set);
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
}

/* func_ov004_02233508 (the destructor, vtable slot 0x40) */
IconModels *IconModels_Destruct(IconModels *self)
{
    IconModels_destruct_members(self);
    return self;
}
CLEAN_AS(func_ov004_02233508, IconModels_Destruct)

/* func_ov004_02233538 (the deleting destructor, vtable slot 0x44) */
IconModels *IconModels_Delete(IconModels *self)
{
    IconModels_destruct_members(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_02233538, IconModels_Delete)

/* The rest of the class (icon_models.h). */
#include <stdint.h>
#include <string.h>

#include "dropped_items.h"
#include "main/acre_tile.h"
#include "main/globe.h"
#include "main/item_info.h"
#include "main/item_traits.h"
#include "main/scene_lights.h"
#include "main/town_day.h"

static_assert(sizeof(IconModels) == 0x184, "icon models");

/* The process once started, the items on their way to the ground, the file of the models. */
extern IconModels *data_ov004_02258ae4;
extern DroppedItem data_ov004_02258af4[DROPPED_ITEMS];
extern const char data_ov004_02255c1c[];

extern AcreMap *data_021c80bc;   /* the town's map, or null */
extern void *data_021c67a4;      /* the field camera, or null */
extern const Vec3 data_021c67d0; /* the point it looks at */
extern Mtx43 data_021fbe48;      /* the matrix being built */

extern void NNS_G3dMdlSetMdlEmi(u8 *model, int material, unsigned short colour);

/* The height of what stands where `point` is in the room, else of its floor. */
extern int func_ov004_0223c5a4(const Vec3 *point);

#define ICON_MODELS_ONE 0x1000
#define ICON_MODELS_TILE 0x2000
/* The tiles drawn round the focus: 8 each way. */
#define ICON_MODELS_REACH 8
/* The item kind drawn on the map: kind 1 (the top four bits). */
#define ICON_MODELS_MAP_KIND 1

/* func_ov004_02233b10: the model of `item` drawn at `position` and `scale`, turned by the
 * angles; nothing before the process has started. */
void IconModels_DrawItemAt(int item, const Vec3 *position, const Vec3 *scale, int x_angle, short y_angle, short z_angle)
{
    IconModels *self = data_ov004_02258ae4;
    if (self == NULL) {
        return;
    }
    IconModels_DrawItem(self, (u16) item, position, scale, (short) x_angle, y_angle, z_angle);
}
CLEAN_AS(func_ov004_02233b10, IconModels_DrawItemAt)

/* func_ov004_02233b5c: the same for the model of a look. */
void IconModels_DrawLookAt(int look, const Vec3 *position, const Vec3 *scale, int x_angle, short y_angle, short z_angle)
{
    IconModels *self = data_ov004_02258ae4;
    if (self == NULL) {
        return;
    }
    IconModels_DrawLook(self, look, position, scale, (short) x_angle, y_angle, z_angle);
}
CLEAN_AS(func_ov004_02233b5c, IconModels_DrawLookAt)

/* func_ov004_02233c20 (the process's release): the models let go and the items on their way
 * finished. */
int IconModels_Release(IconModels *self)
{
    ModelSet_Release(&self->set);
    DroppedItems_Release(data_ov004_02258af4);
    return 1;
}
CLEAN_AS(func_ov004_02233c20, IconModels_Release)

/* func_ov004_02233c44 (the process's draw): with the town's map and the camera, the items on
 * the map, then those on their way. */
int IconModels_Draw(IconModels *self)
{
    AcreMap *map = data_021c80bc;
    if (map != NULL && data_021c67a4 != NULL) {
        IconModels_DrawMapItems(self, map);
        DroppedItems_Draw(data_ov004_02258af4);
    }
    return 1;
}
CLEAN_AS(func_ov004_02233c44, IconModels_Draw)

/* An item lying at the tile centre `at` on `layer`, drawn on what stands there when it is of
 * the kind drawn on the map. */
static void IconModels_draw_tile_item(IconModels *self, AcreMap *map, const Vec3 *at, int layer)
{
    u16 *code = AcreTile_ItemAt(map, at, layer);
    if (code == NULL || ((*code & 0xf000) >> 12) != ICON_MODELS_MAP_KIND) {
        return;
    }
    Vec3 position;
    position.y = at->y + func_ov004_0223c5a4(at);
    position.x = at->x;
    position.z = at->z;
    Vec3 scale = {ICON_MODELS_ONE, ICON_MODELS_ONE, ICON_MODELS_ONE};
    IconModels_DrawItem(self, *code, &position, &scale, 0, 0, 0);
}

/* func_ov004_02233c78: the items of kind 1 lying on both layers of the 17 by 17 tiles round the
 * camera's focus, rows from the far end in z, each from the far end in x.
 * QUIRK: each row bends the matrix for its first tile, which IconModels_DrawItem builds again
 * from the start. */
void IconModels_DrawMapItems(IconModels *self, AcreMap *map)
{
    if (data_021c67a4 == NULL) {
        return;
    }
    Vec3 focus = data_021c67d0;
    Vec3 centre;
    AcreTile_SnapToTileCentre(&centre, &focus);
    Vec3 row = {centre.x + ICON_MODELS_REACH * ICON_MODELS_TILE, 0, centre.z + ICON_MODELS_REACH * ICON_MODELS_TILE};
    for (int i = ICON_MODELS_REACH; i >= -ICON_MODELS_REACH; i--) {
        Vec3 at;
        AcreTile_SnapToTileCentre(&at, &row);
        Vec3 bent;
        int angle = Globe_BendFar(&bent, &at);
        Mtx43_Translation(&data_021fbe48, bent.x, bent.y, bent.z);
        Mtx43_RotateX(&data_021fbe48, angle);
        for (int j = ICON_MODELS_REACH; j >= -ICON_MODELS_REACH; j--) {
            IconModels_draw_tile_item(self, map, &at, 0);
            IconModels_draw_tile_item(self, map, &at, 1);
            at.x -= ICON_MODELS_TILE;
        }
        row.z -= ICON_MODELS_TILE;
    }
}
CLEAN_AS(func_ov004_02233c78, IconModels_DrawMapItems)

/* func_ov004_02233dc0: the model of `item`'s look (ItemTraits_Unk07) drawn. */
void IconModels_DrawItem(IconModels *self, u16 item, const Vec3 *position, const Vec3 *scale, short x_angle, short y_angle,
                         short z_angle)
{
    u16 code = item;
    Vec3 at = *position;
    Vec3 size = *scale;
    int look = ItemTraits_Unk07(&code);
    IconModels_DrawLook(self, look, &at, &size, x_angle, y_angle, z_angle);
}
CLEAN_AS(func_ov004_02233dc0, IconModels_DrawItem)

/* func_ov004_02233e18: the model of `look` drawn (when there is one) at `position` bent onto
 * the ground, turned by the ground's angle and the three angles, at `scale`; the model.
 * REQUIRES: look < ICON_MODELS_LOOKS (ItemTraits_Unk07 gives no other). */
ModelObject *IconModels_DrawLook(IconModels *self, int look, const Vec3 *position, const Vec3 *scale, short x_angle,
                                 short y_angle, short z_angle)
{
    ModelObject *model = self->models[look];
    Vec3 bent;
    int angle = Globe_BendFar(&bent, position);
    Mtx43_Translation(&data_021fbe48, bent.x, bent.y, bent.z);
    Mtx43_RotateX(&data_021fbe48, angle);
    Mtx43_RotateZYX(&data_021fbe48, x_angle, y_angle, z_angle);
    Mtx43_Scale(&data_021fbe48, scale->x, scale->y, scale->z);
    IconModels_DrawModel(self, model, data_021fbe48);
    return model;
}
CLEAN_AS(func_ov004_02233e18, IconModels_DrawLook)

/* func_ov004_02233eb8: a model drawn with `matrix` as its base matrix, then its first
 * material's emission set to the scene's light colour. */
void IconModels_DrawModel(IconModels *self, ModelObject *model, Mtx43 matrix)
{
    (void) self;
    if (model == NULL) {
        return;
    }
    memcpy(model->unk_64, &matrix, sizeof matrix);
    ModelObject_DrawShapes(model, NULL);
    u16 colour = (u16) SceneLights_EmissionColour();
    NNS_G3dMdlSetMdlEmi(model->model, 0, colour);
}
CLEAN_AS(func_ov004_02233eb8, IconModels_DrawModel)

/* func_ov004_02233f00 (the process's update): the items on their way moved. */
int IconModels_Update(IconModels *self)
{
    (void) self;
    DroppedItems_Update(data_ov004_02258af4);
    return 1;
}
CLEAN_AS(func_ov004_02233f00, IconModels_Update)

/* func_ov004_02233f18 (the process's init): once the models are loaded, the town's day is
 * summarized, the process becomes the one others draw with, and the places of the items on
 * their way are freed.
 * QUIRK: the summary's result is not used. */
int IconModels_Init(IconModels *self)
{
    if (!IconModels_Load(self)) {
        return 0;
    }
    TownDay_Summarize();
    data_ov004_02258ae4 = self;
    DroppedItems_Reset(data_ov004_02258af4);
    return 1;
}
CLEAN_AS(func_ov004_02233f18, IconModels_Init)

/* func_ov004_02233f4c: the model set "/fg/icon/icon.nsbmd" loaded, and the model of each look
 * found in it; whether it loaded. */
int IconModels_Load(IconModels *self)
{
    if (!ModelSet_Load(&self->set, data_ov004_02255c1c, NULL)) {
        return 0;
    }
    for (int look = 0; look < ICON_MODELS_LOOKS; look++) {
        self->models[look] = ModelSet_Find(&self->set, ItemInfo_LookModelName(look, 0));
    }
    return 1;
}
CLEAN_AS(func_ov004_02233f4c, IconModels_Load)

/* func_ov004_02233f9c (the class's create): the process from the auxiliary heap, zeroed and
 * constructed: the process base, then the class, and its model set. */
IconModels *IconModels_Create(void)
{
    IconModels *self = Heap_AllocAuxZeroed(sizeof(IconModels));
    if (self != NULL) {
        Process_Construct(&self->base);
        self->base.vtable = data_020da13c;
        self->base.vtable = data_ov004_02255bd4;
        ModelSet_Construct(&self->set);
    }
    return self;
}
CLEAN_AS(func_ov004_02233f9c, IconModels_Create)
