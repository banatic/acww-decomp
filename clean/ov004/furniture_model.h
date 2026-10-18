/* The model files of a piece of furniture (a room object's member at 0x6cc), found by its
 * number: the texture file "/ftr/<number / 256>/<number % 256 / 16>/<number, 4 hex digits>.nsbtx"
 * and the archive ".arc" beside it, which holds the model ("bmd0") and the animations
 * (AnimSet, room_object_parts.h). Loading takes the files, then the texture through a loader
 * that may take several frames; once the texture is in, the texture file is freed, unless a
 * copy of it was asked for.
 *
 * Also the four animations a room object plays (its members at 0x7c4), a class over the main
 * program's animation (constructor ModelAnim_ConstructBase). */
#ifndef CLEAN_OV004_FURNITURE_MODEL_H
#define CLEAN_OV004_FURNITURE_MODEL_H

#include "types.h"

#include "main/lookups.h" /* ItemCode */
#include "main/model_anim.h"
#include "main/model_loader.h"
#include "room_object_parts.h"

typedef struct FurnitureModel {
    u8 *texture_file; /* while loading, and while the texture is not in */
    u8 *archive;
    u8 *model;          /* the first model of the archive's "bmd0" */
    u8 *texture;        /* the texture once it is in: then the model counts as loaded */
    ModelLoader loader; /* loads the texture (ModelLoader_StepTexture runs it) */
    AnimSet anims;
    ItemCode item; /* the furniture being loaded, 0xfff1 when none */
    u8 keep_texture_copy;
    u8 unk_73;
} FurnitureModel;

/* An animation of the room object: the main program's animation (model_anim.h) with a class
 * of its own (vtable data_ov004_0224fe44). Its animation object (base.anim) is where its frame
 * goes (RoomObject_AdvanceAnims writes it there), none until it is bound. */
typedef struct FurnitureAnim {
    ModelAnim base;
} FurnitureAnim;

int FurnitureModel_EndLoad(FurnitureModel *files);
u8 *FurnitureModel_Texture(FurnitureModel *files);
u8 *FurnitureModel_Model(FurnitureModel *files);
int FurnitureModel_LoadStep(FurnitureModel *files, void *slot, int number, int keep_texture_copy);
int FurnitureModel_Load(FurnitureModel *files, void *slot, int number, int keep_texture_copy);
int FurnitureModel_FreeTextureFile(FurnitureModel *files);
AnimSet *FurnitureModel_Anims(FurnitureModel *files);
int FurnitureModel_LoadFiles(FurnitureModel *files, void *slot, int number);
char *FurnitureModel_TexturePath(FurnitureModel *files, int number);
char *FurnitureModel_ArchivePath(FurnitureModel *files, int number);
int FurnitureModel_IsLoaded(FurnitureModel *files);
FurnitureModel *FurnitureModel_Destruct(FurnitureModel *files);
FurnitureModel *FurnitureModel_Construct(FurnitureModel *files);

AnimatedModelAnim *FurnitureAnim_Target(const FurnitureAnim *anim);
FurnitureAnim *FurnitureAnim_Delete(FurnitureAnim *anim);
FurnitureAnim *FurnitureAnim_Destruct(FurnitureAnim *anim);
FurnitureAnim *FurnitureAnim_Construct(FurnitureAnim *anim);

#endif
