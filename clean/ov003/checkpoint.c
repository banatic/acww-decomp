/* The checkpoint: its files and the town's design on it (checkpoint.h). */
#include "checkpoint.h"

#include "autoload_2/heap.h" /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "main/actor_table.h"
#include "main/animated_model.h"
#include "main/c_library.h"
#include "main/collision_map.h"
#include "main/house_looks.h"
#include "main/item_texture.h"
#include "main/vram_copy_task.h"
#include "house_files.h"
#include "ov009/scene_actor_life.h"

static_assert(offsetof(Checkpoint, model) == 0x198, "model");
static_assert(offsetof(Checkpoint, design) == 0x2b4, "design");
static_assert(offsetof(CheckpointDesign, texture_file) == 0x28, "texture file");
static_assert(offsetof(Checkpoint, position) == 0x5c, "position");
static_assert(offsetof(Checkpoint, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(Checkpoint, model_object) == 0x13c, "model object");
static_assert(sizeof(Checkpoint) == 0x5a0, "the size Checkpoint_New allocates");

#define CHECKPOINT_RECEIVER_OFFSET 0xec
/* The edges func_02030920 makes solid: all four. */
#define CHECKPOINT_SOLID_EDGES 15

/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_02238934[];
extern const u8 data_ov003_022389f8[];

/* "w", the material the design goes on. */
extern const char data_ov003_02238a70[];
/* "/str/chkp/%s%c_lt.nsbtx", "/str/chkp/%s%c.nsbtx" and "/str/chkp/%s%c.arc", and the buffers
 * the paths are written into. */
extern const char data_ov003_02238a74[];
extern const char data_ov003_02238a8c[];
extern const char data_ov003_02238aa4[];
extern char data_ov003_0223c88c[];
extern char data_ov003_0223c844[];
extern char data_ov003_0223c868[];
/* "obj_check0", "obj_check1" and "obj_check2", by style. */
extern const char *const data_ov003_02238908[3];
/* The record of the town's single design (design_sets.h). */
extern u8 data_021f34b0[];

/* func_ov003_0221c430: takes the design off the material (the binding's func_020b9e2c). */
void Checkpoint_ReleaseDesign(CheckpointDesign *design)
{
    VramCopyMaterial_End((VramCopyMaterial *) design);
}
CLEAN_AS(func_ov003_0221c430, Checkpoint_ReleaseDesign)

/* func_ov003_0221c438: loads design `source` into the texture file and puts the file's texture
 * on the material "w" of `model`; when both worked, `source` is copied into the town's design
 * record and 1 is returned, else 0. */
int Checkpoint_PutDesign(CheckpointDesign *design, void *model, void *source)
{
    if (ClothTexture_SetDesign((DesignModel *) design->texture_file, source) == 0) {
        return 0;
    }
    void *texture = ClothTexture_Textures((DesignModel *) design->texture_file);
    if (VramCopyMaterial_Queue((VramCopyMaterial *) design->binding, model, data_ov003_02238a70, texture, 0, 0) == 0) {
        return 0;
    }
    HouseLooks_SetDesign((HouseLooksDesign *) (uintptr_t) HouseLooks_Design((HouseLooksRecord *) data_021f34b0), source);
    return 1;
}
CLEAN_AS(func_ov003_0221c438, Checkpoint_PutDesign)

/* func_ov003_0221c490: the design part's destructor: the texture file's; the binding is not
 * destroyed here (Checkpoint_ReleaseDesign takes it down). */
CheckpointDesign *Checkpoint_DestroyDesign(CheckpointDesign *design)
{
    ClothTexture_Destruct((DesignModel *) design->texture_file);
    return design;
}
CLEAN_AS(func_ov003_0221c490, Checkpoint_DestroyDesign)

/* func_ov003_0221c4a4: the design part's constructor: the binding's, then the texture
 * file's. */
CheckpointDesign *Checkpoint_ConstructDesign(CheckpointDesign *design)
{
    VramCopyMaterial_Construct((VramCopyMaterial *) design->binding);
    ClothTexture_Construct((DesignModel *) design->texture_file);
    return design;
}
CLEAN_AS(func_ov003_0221c4a4, Checkpoint_ConstructDesign)

/* func_ov003_0221c4bc: puts the town's design, as the record holds it now, on the model again;
 * always 1. Main calls it when that design changed (Design_Changed). */
int Checkpoint_RefreshDesign(Checkpoint *checkpoint)
{
    void *model = checkpoint->model;
    void *source =
        HouseLooks_DesignItself((HouseLooksDesign *) (uintptr_t) HouseLooks_Design((HouseLooksRecord *) data_021f34b0));
    Checkpoint_PutDesign(&checkpoint->design, model, source);
    return 1;
}
CLEAN_AS(func_ov003_0221c4bc, Checkpoint_RefreshDesign)

/* func_ov003_0221c4f4 (vtable slot 0x94): always 0. */
int Checkpoint_Slot94(void)
{
    return 0;
}
CLEAN_AS(func_ov003_0221c4f4, Checkpoint_Slot94)

/* func_ov003_0221c4f8 (vtable slot 0xac): "/str/chkp/<model><letter>_lt.nsbtx", in a buffer
 * of the overlay. */
char *Checkpoint_LtTexturePath(void)
{
    const char *name = Checkpoint_ModelName();
    int letter = HouseFiles_SeasonLetter();
    CLib_SPrintf(data_ov003_0223c88c, data_ov003_02238a74, name, letter);
    return data_ov003_0223c88c;
}
CLEAN_AS(func_ov003_0221c4f8, Checkpoint_LtTexturePath)

/* func_ov003_0221c520 (vtable slot 0xa8): "/str/chkp/<model><letter>.nsbtx". */
char *Checkpoint_TexturePath(void)
{
    const char *name = Checkpoint_ModelName();
    int letter = HouseFiles_SeasonLetter();
    CLib_SPrintf(data_ov003_0223c844, data_ov003_02238a8c, name, letter);
    return data_ov003_0223c844;
}
CLEAN_AS(func_ov003_0221c520, Checkpoint_TexturePath)

/* func_ov003_0221c548 (vtable slot 0xa4): "/str/chkp/<model><letter>.arc". */
char *Checkpoint_ArchivePath(void)
{
    const char *name = Checkpoint_ModelName();
    int letter = HouseFiles_SeasonLetter();
    CLib_SPrintf(data_ov003_0223c868, data_ov003_02238aa4, name, letter);
    return data_ov003_0223c868;
}
CLEAN_AS(func_ov003_0221c548, Checkpoint_ArchivePath)

/* func_ov003_0221c570: "obj_check<style>"; Checkpoint_Style is always below 3. */
const char *Checkpoint_ModelName(void)
{
    return data_ov003_02238908[Checkpoint_Style()];
}
CLEAN_AS(func_ov003_0221c570, Checkpoint_ModelName)

/* func_ov003_0221c588: the style kept after the town's design, 0 to 2. */
int Checkpoint_Style(void)
{
    return HouseLooks_Style((HouseLooksDesign *) (uintptr_t) HouseLooks_Design((HouseLooksRecord *) data_021f34b0));
}
CLEAN_AS(func_ov003_0221c588, Checkpoint_Style)

/* func_ov003_0221c5a0 (vtable slot 0x0c, leaving the scene): takes the design off; always 1. */
int Checkpoint_Leave(Checkpoint *checkpoint)
{
    Checkpoint_ReleaseDesign(&checkpoint->design);
    return 1;
}
CLEAN_AS(func_ov003_0221c5a0, Checkpoint_Leave)

/* func_ov003_0221c5b8 (vtable slot 0x24): always 1. */
int Checkpoint_Slot24(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221c5b8, Checkpoint_Slot24)

/* func_ov003_0221c5bc (vtable slot 0x18, its update): the model's animation goes on; always
 * 1. */
int Checkpoint_Update(Checkpoint *checkpoint)
{
    AnimatedModel_StepFrames((AnimatedModel *) checkpoint->model_object);
    return 1;
}
CLEAN_AS(func_ov003_0221c5bc, Checkpoint_Update)

/* func_ov003_0221c5d4 (vtable slot 0x70, setting it up): puts the town's design on the model,
 * as Checkpoint_RefreshDesign does, and makes the five tiles of the row before its own tile
 * (x - 2 to x + 2 at z - 1) solid on every edge; always 1. */
int Checkpoint_Init(Checkpoint *checkpoint)
{
    void *model = checkpoint->model;
    void *source =
        HouseLooks_DesignItself((HouseLooksDesign *) (uintptr_t) HouseLooks_Design((HouseLooksRecord *) data_021f34b0));
    Checkpoint_PutDesign(&checkpoint->design, model, source);

    int x;
    int z;
    Position_Tile(&x, &z, (const Position *) &checkpoint->position);
    for (int dx = -2; dx <= 2; dx++) {
        CollisionMap_RetypeWithSides(x + dx, z - 1, CHECKPOINT_SOLID_EDGES);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221c5d4, Checkpoint_Init)

/* The vtables set back, the design part destroyed, then overlay 9's destructor. */
static void checkpoint_destroy_parts(Checkpoint *checkpoint)
{
    checkpoint->vtable = data_ov003_02238934;
    checkpoint->receiver_vtable = data_ov003_022389f8;
    Checkpoint_DestroyDesign(&checkpoint->design);
    SceneActor_Destruct((SceneActor *) checkpoint);
}

/* func_ov003_0221c630 (vtable slot 0x44, the deleting destructor): the destructor's work, then
 * the memory freed. */
Checkpoint *Checkpoint_DestroyAndFree(Checkpoint *checkpoint)
{
    checkpoint_destroy_parts(checkpoint);
    Heap_FreeAux(checkpoint);
    return checkpoint;
}
CLEAN_AS(func_ov003_0221c630, Checkpoint_DestroyAndFree)

/* func_ov003_0221c668 (vtable slot 0x40): the destructor, without freeing. */
Checkpoint *Checkpoint_Destroy(Checkpoint *checkpoint)
{
    checkpoint_destroy_parts(checkpoint);
    return checkpoint;
}
CLEAN_AS(func_ov003_0221c668, Checkpoint_Destroy)

/* func_ov003_0221c69c: the constructor: overlay 9's, the vtables, then the design part's. */
Checkpoint *Checkpoint_Construct(Checkpoint *checkpoint)
{
    SceneActor_ConstructBase((SceneActor *) checkpoint);
    checkpoint->vtable = data_ov003_02238934;
    checkpoint->receiver_vtable = data_ov003_022389f8;
    Checkpoint_ConstructDesign(&checkpoint->design);
    return checkpoint;
}
CLEAN_AS(func_ov003_0221c69c, Checkpoint_Construct)

/* func_ov003_0221c6cc (the class's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void Checkpoint_New(void)
{
    Checkpoint *checkpoint = Heap_AllocAuxZeroed(sizeof(Checkpoint));
    if (checkpoint != NULL) {
        Checkpoint_Construct(checkpoint);
    }
}
CLEAN_AS(func_ov003_0221c6cc, Checkpoint_New)

/* The checkpoint around its receiver part, as the receiver vtable's thunks find it. */
static Checkpoint *checkpoint_from_receiver(void *receiver)
{
    return (Checkpoint *) (void *) ((u8 *) receiver - CHECKPOINT_RECEIVER_OFFSET);
}

/* _ZThn236_N18Obj_ov003_02238934D0Ev (receiver slot 0x04): Checkpoint_DestroyAndFree. */
Checkpoint *Checkpoint_ReceiverDestroyAndFree(void *receiver)
{
    return Checkpoint_DestroyAndFree(checkpoint_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238934D0Ev, Checkpoint_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_02238934D1Ev (receiver slot 0x00): Checkpoint_Destroy. */
Checkpoint *Checkpoint_ReceiverDestroy(void *receiver)
{
    return Checkpoint_Destroy(checkpoint_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238934D1Ev, Checkpoint_ReceiverDestroy)
