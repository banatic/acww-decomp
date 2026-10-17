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

#endif
