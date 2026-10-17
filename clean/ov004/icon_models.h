/* A process of overlay 4 (class vtable 0x02255bd4 on the Process base) that loads the model set
 * "/fg/icon/icon.nsbmd" (at 0x174) and keeps the model of each of the 0x49 looks of items
 * (ItemInfo_LookModelName) found in it (at 0x50). Only its destructors are written here. */
#ifndef CLEAN_OV004_ICON_MODELS_H
#define CLEAN_OV004_ICON_MODELS_H

#include "autoload_2/process.h"
#include "main/model_object.h"
#include "types.h"

/* The looks of items whose models it keeps. */
#define ICON_MODELS_LOOKS 0x49

typedef struct IconModels {
    Process base;
    ModelObject *models[ICON_MODELS_LOOKS]; /* 0x050 */
    ModelSet set;                           /* 0x174 */
} IconModels;

IconModels *IconModels_Destruct(IconModels *self);
IconModels *IconModels_Delete(IconModels *self);

/* The rest of the class: the process (vtable slots: IconModels_Init, IconModels_Release,
 * IconModels_Update, IconModels_Draw; made by IconModels_Create) also moves and draws the
 * items on their way to the ground (dropped_items.h), and draws the items lying on the town's
 * map round the camera's focus. data_ov004_02258ae4 points to it once it has started. Others
 * draw an item's model (IconModels_DrawItemAt, by item) or a look's (IconModels_DrawLookAt). */
#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "main/acre_map.h"

void IconModels_DrawItemAt(int item, const Vec3 *position, const Vec3 *scale, int x_angle, short y_angle, short z_angle);
void IconModels_DrawLookAt(int look, const Vec3 *position, const Vec3 *scale, int x_angle, short y_angle, short z_angle);
int IconModels_Release(IconModels *self);
int IconModels_Draw(IconModels *self);
void IconModels_DrawMapItems(IconModels *self, AcreMap *map);
void IconModels_DrawItem(IconModels *self, u16 item, const Vec3 *position, const Vec3 *scale, short x_angle, short y_angle,
                         short z_angle);
ModelObject *IconModels_DrawLook(IconModels *self, int look, const Vec3 *position, const Vec3 *scale, short x_angle,
                                 short y_angle, short z_angle);
void IconModels_DrawModel(IconModels *self, ModelObject *model, Mtx43 matrix);
int IconModels_Update(IconModels *self);
int IconModels_Init(IconModels *self);
int IconModels_Load(IconModels *self);
IconModels *IconModels_Create(void);

#endif
