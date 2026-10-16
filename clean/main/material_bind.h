/* A texture and a palette of a texture resource bound to one material of a model (a C++ class
 * of main without a vtable, kept on the stack while it is used): the reference picks the
 * material of a model resource (NNSG3dResMdl) by index or name, then binding a texture of a
 * texture resource (NNSG3dResTex, g3d_resource.h) that is in VRAM writes its address, format
 * and size into every material the model binds to the same texture name as the one picked
 * (the model's texture-to-material dictionary), and binding a palette writes its address into
 * every material bound to the same palette name. The dictionary entry is then marked bound.
 *
 * Overlay 4's room objects (the TV, the design furniture) show pictures with it. */
#ifndef CLEAN_MAIN_MATERIAL_BIND_H
#define CLEAN_MAIN_MATERIAL_BIND_H

#include "main/g3d_resource.h"
#include "types.h"

/* MaterialBind.material when no material is picked. */
#define MATERIAL_BIND_NONE (-1)

typedef struct MaterialBind {
    u8 *model;   /* 0x00: the model resource (NNSG3dResMdl) */
    s8 material; /* 0x04: the material's index, MATERIAL_BIND_NONE for none */
    u8 pad_05[3];
} MaterialBind;

int MaterialBind_BindByIndex(u8 *model, const char *material, G3dResTex *tex, int texture, int palette);
int MaterialBind_BindByName(u8 *model, const char *material, G3dResTex *tex, const char *texture, const char *palette);
s8 MaterialBind_Material(const MaterialBind *bind);
int MaterialBind_SetPalette(MaterialBind *bind, G3dResTex *tex, int palette);
int MaterialBind_SetPaletteByName(MaterialBind *bind, G3dResTex *tex, const char *palette);
int MaterialBind_SetTexture(MaterialBind *bind, G3dResTex *tex, int texture);
int MaterialBind_SetTextureByName(MaterialBind *bind, G3dResTex *tex, const char *texture);
int MaterialBind_Set(MaterialBind *bind, G3dResTex *tex, int texture, int palette);
int MaterialBind_SetByName(MaterialBind *bind, G3dResTex *tex, const char *texture, const char *palette);
void MaterialBind_Reset(MaterialBind *bind);
int MaterialBind_Pick(MaterialBind *bind, u8 *model, int material);
int MaterialBind_PickByName(MaterialBind *bind, u8 *model, const char *material);
int MaterialBind_IsPicked(const MaterialBind *bind);
void MaterialBind_Destruct(MaterialBind *bind);
MaterialBind *MaterialBind_Construct(MaterialBind *bind);

#endif
