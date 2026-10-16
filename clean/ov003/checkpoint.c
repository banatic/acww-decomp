/* The checkpoint: its files and the town's design on it (checkpoint.h). */
#include "checkpoint.h"

#include "clean.h"

static_assert(offsetof(Checkpoint, model) == 0x198, "model");
static_assert(offsetof(Checkpoint, design) == 0x2b4, "design");
static_assert(offsetof(CheckpointDesign, texture_file) == 0x28, "texture file");

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

/* A texture binding of main: its destructor (func_020b9e2c takes the texture off), its
 * constructor, and putting texture 0 and palette 0 of `texture` on the material named
 * `material` of `model` (whether it could). */
extern void func_020b9e2c(CheckpointDesign *design);
extern void *func_020b9e58(void *binding);
extern int func_020b9d3c(void *binding, void *model, const char *material, void *texture, int tex_index, int plt_index);
/* A texture file: loading a design into it (whether it could), its texture block, its
 * destructor and its constructor. */
extern int func_0203cff8(void *file, void *design);
extern void *func_0203cfc8(void *file);
extern void func_0203d224(void *file);
extern void func_0203d228(void *file);
/* The design record: the part after its first word, the design in it, copying a design into
 * it, and the style byte after the design, reduced below 3. */
extern void *func_020b374c(void *record);
extern void *func_020b3848(void *record);
extern void func_020b3850(void *record, void *design);
extern int func_020b3858(void *record);
/* A letter for the textures (from data_ov003_0223666c by func_020b6598). */
extern signed char func_ov003_022203dc(void);
extern int func_02064328(char *buffer, const char *format, ...); /* sprintf */

/* func_ov003_0221c430: takes the design off the material (the binding's func_020b9e2c). */
void Checkpoint_ReleaseDesign(CheckpointDesign *design)
{
    func_020b9e2c(design);
}
CLEAN_AS(func_ov003_0221c430, Checkpoint_ReleaseDesign)

/* func_ov003_0221c438: loads design `source` into the texture file and puts the file's texture
 * on the material "w" of `model`; when both worked, `source` is copied into the town's design
 * record and 1 is returned, else 0. */
int Checkpoint_PutDesign(CheckpointDesign *design, void *model, void *source)
{
    if (func_0203cff8(design->texture_file, source) == 0) {
        return 0;
    }
    void *texture = func_0203cfc8(design->texture_file);
    if (func_020b9d3c(design->binding, model, data_ov003_02238a70, texture, 0, 0) == 0) {
        return 0;
    }
    func_020b3850(func_020b374c(data_021f34b0), source);
    return 1;
}
CLEAN_AS(func_ov003_0221c438, Checkpoint_PutDesign)

/* func_ov003_0221c490: the design part's destructor: the texture file's; the binding is not
 * destroyed here (Checkpoint_ReleaseDesign takes it down). */
CheckpointDesign *Checkpoint_DestroyDesign(CheckpointDesign *design)
{
    func_0203d224(design->texture_file);
    return design;
}
CLEAN_AS(func_ov003_0221c490, Checkpoint_DestroyDesign)

/* func_ov003_0221c4a4: the design part's constructor: the binding's, then the texture
 * file's. */
CheckpointDesign *Checkpoint_ConstructDesign(CheckpointDesign *design)
{
    func_020b9e58(design->binding);
    func_0203d228(design->texture_file);
    return design;
}
CLEAN_AS(func_ov003_0221c4a4, Checkpoint_ConstructDesign)

/* func_ov003_0221c4bc: puts the town's design, as the record holds it now, on the model again;
 * always 1. Main calls it when that design changed (Design_Changed). */
int Checkpoint_RefreshDesign(Checkpoint *checkpoint)
{
    void *model = checkpoint->model;
    void *source = func_020b3848(func_020b374c(data_021f34b0));
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
    int letter = func_ov003_022203dc();
    func_02064328(data_ov003_0223c88c, data_ov003_02238a74, name, letter);
    return data_ov003_0223c88c;
}
CLEAN_AS(func_ov003_0221c4f8, Checkpoint_LtTexturePath)

/* func_ov003_0221c520 (vtable slot 0xa8): "/str/chkp/<model><letter>.nsbtx". */
char *Checkpoint_TexturePath(void)
{
    const char *name = Checkpoint_ModelName();
    int letter = func_ov003_022203dc();
    func_02064328(data_ov003_0223c844, data_ov003_02238a8c, name, letter);
    return data_ov003_0223c844;
}
CLEAN_AS(func_ov003_0221c520, Checkpoint_TexturePath)

/* func_ov003_0221c548 (vtable slot 0xa4): "/str/chkp/<model><letter>.arc". */
char *Checkpoint_ArchivePath(void)
{
    const char *name = Checkpoint_ModelName();
    int letter = func_ov003_022203dc();
    func_02064328(data_ov003_0223c868, data_ov003_02238aa4, name, letter);
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
    return func_020b3858(func_020b374c(data_021f34b0));
}
CLEAN_AS(func_ov003_0221c588, Checkpoint_Style)
