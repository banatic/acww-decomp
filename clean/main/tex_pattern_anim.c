/* A texture pattern animation played by copying texture images in VRAM (tex_pattern_anim.h). */
#include "tex_pattern_anim.h"

#include "clean.h"
#include "g3d_resource.h"
#include "vram_copy_task.h"

static_assert(sizeof(ModelLoaderTask) == 0x1c, "ModelLoaderTask size");
static_assert(offsetof(TexPatternAnimEntry, texture) == 0x20, "TexPatternAnimEntry texture");
static_assert(sizeof(TexPatternAnimEntry) == 0x28, "TexPatternAnimEntry size");
static_assert(offsetof(TexPatternAnim, model) == 0x18, "TexPatternAnim model");
static_assert(offsetof(TexPatternAnim, entries) == 0x28, "TexPatternAnim entries");
static_assert(sizeof(TexPatternAnim) == 0x2c, "TexPatternAnim size");

/* The class's vtable and the frame control's. */
extern const u8 data_020dd164[];
extern const u8 data_020dd184[];

/* The current heap. */
extern Heap *data_021fbe94;

/* The texture resource of a file. */
extern void *func_021077e8(u8 *file);

/* NitroSystem: the animation `index` of an animation file; the index of a name in a resource
 * dictionary (-1 when it is not there); the data of the texture pattern animation's material
 * `index`. */
extern u8 *NNS_G3dGetAnmByIdx(void *file, int index);
extern int NNS_G3dGetResDictIdxByName(const u8 *dict, const u8 *name);
extern const u8 *NNSi_G3dGetTexPatAnmDataByIdx(const u8 *anim, int index);

static u16 read_u16(const u8 *p)
{
    return *(const u16 *) (const void *) p;
}

static u32 read_u32(const u8 *p)
{
    return *(const u32 *) (const void *) p;
}

/* The 16-byte name of entry `index` of a NitroSystem resource dictionary (NNSG3dResDict): the
 * names follow the entries (their offset at 6, the names' offset from them at 2). */
static const u8 *dict_name(const u8 *dict, int index)
{
    const u8 *entries = dict + read_u16(dict + 6);
    return entries + read_u16(entries + 2) + index * 16;
}

/* The texture pattern animation's dictionary of materials, at 0xc. */
#define ANIM_DICT 0x0c
/* The animation's frame count, at 4, and the offset of its texture names, at 8. */
#define ANIM_FRAMES 4
#define ANIM_TEXTURE_NAMES 8
/* The texture resource's dictionary of textures, at 0x3c. */
#define TEXTURE_DICT 0x3c

/* A key: from whole frame `frame` on, the animation's texture name `name` is shown. */
#define KEY_SIZE 4
#define KEY_FRAME 0
#define KEY_NAME 2

/* The entry of the material `material`, or NULL. */
static TexPatternAnimEntry *find_entry(TexPatternAnim *self, int material)
{
    for (int i = 0; i < self->count; i++) {
        if (self->entries[i].material == material) {
            return &self->entries[i];
        }
    }
    return NULL;
}

/* func_02056610: the material named `material` animated again. */
void TexPatternAnim_Release(TexPatternAnim *self, const char *material)
{
    int index = G3dRes_MaterialIndex(self->model, material);
    if (index == -1) {
        return;
    }
    TexPatternAnimEntry *entry = find_entry(self, index);
    if (entry != NULL) {
        entry->flags &= (u8) ~TEX_PATTERN_ANIM_HELD;
    }
}
CLEAN_AS(func_02056610, TexPatternAnim_Release)

/* func_02056658: the material named `material` no longer animated: it keeps the texture it
 * shows until TexPatternAnim_Show changes it or TexPatternAnim_Release lets it go. */
void TexPatternAnim_Hold(TexPatternAnim *self, const char *material)
{
    int index = G3dRes_MaterialIndex(self->model, material);
    if (index == -1) {
        return;
    }
    TexPatternAnimEntry *entry = find_entry(self, index);
    if (entry != NULL) {
        entry->flags |= TEX_PATTERN_ANIM_HELD;
    }
}
CLEAN_AS(func_02056658, TexPatternAnim_Hold)

/* func_020566a0: the material named `material` made to show the texture named `texture`, its
 * key and frame forgotten so the animation sets it again once it is let go. Whether the
 * texture changed (0 also without such a material or entry).
 * QUIRK: the texture's index is kept in a byte before it is compared with -1, so a name the
 * texture resource does not have is not caught: texture 0xff is copied instead. */
int TexPatternAnim_Show(TexPatternAnim *self, const char *material, const char *texture)
{
    int index = G3dRes_MaterialIndex(self->model, material);
    if (index == -1) {
        return 0;
    }
    u8 shown = (u8) G3dRes_TextureIndex(self->texture, texture);
    TexPatternAnimEntry *entry = find_entry(self, index);
    if (entry == NULL || entry->texture == shown) {
        return 0;
    }
    entry->texture = shown;
    entry->key = TEX_PATTERN_ANIM_NONE;
    entry->frame = TEX_PATTERN_ANIM_NO_FRAME;
    TexPatternAnim_CopyTexture(entry, self->model, self->texture);
    return 1;
}
CLEAN_AS(func_020566a0, TexPatternAnim_Show)

/* func_02056730: every material not held shows the texture of the whole frame the frame
 * control is at (bits 12 to 27 of its 20.12 frame). */
void TexPatternAnim_Update(TexPatternAnim *self)
{
    u32 frame = ((u32) self->ctrl.frame << 4) >> 16;
    for (int i = 0; i < self->count; i++) {
        if (!TexPatternAnim_IsHeld(&self->entries[i])) {
            TexPatternAnim_UpdateEntry(&self->entries[i], frame, self->anim, self->texture, self->model);
        }
    }
}
CLEAN_AS(func_02056730, TexPatternAnim_Update)

/* func_02056778: one step of the frame control, then the textures updated. */
void TexPatternAnim_Step(TexPatternAnim *self)
{
    FrameCtrl_Step(&self->ctrl);
    TexPatternAnim_Update(self);
}
CLEAN_AS(func_02056778, TexPatternAnim_Step)

/* func_0205678c: the first animation of `anim_file` played: each of its materials found in the
 * model by name, nothing shown yet, and the frame control started with `frames` frames (0: the
 * animation's own count), `flags`, `speed` and `start` (FrameCtrl_Init).
 * REQUIRES: the animation has no more materials than the entries made by TexPatternAnim_Load;
 * the ones past them are written after the entries. */
void TexPatternAnim_Start(TexPatternAnim *self, void *anim_file, int start, int frames, u8 flags, fx32 speed)
{
    self->anim = NNS_G3dGetAnmByIdx(anim_file, 0);
    self->frames = read_u16(self->anim + ANIM_FRAMES);
    if (frames == 0) {
        frames = self->frames;
    }
    const u8 *materials = self->model + read_u32(self->model + 8);
    const u8 *dict = self->anim + ANIM_DICT;
    for (int i = 0; i < dict[1]; i++) {
        TexPatternAnimEntry *entry = &self->entries[i];
        entry->material = (u8) NNS_G3dGetResDictIdxByName(materials + 4, dict_name(dict, i));
        entry->keys = NNSi_G3dGetTexPatAnmDataByIdx(self->anim, i);
        entry->key = TEX_PATTERN_ANIM_NONE;
        entry->texture = TEX_PATTERN_ANIM_NONE;
        entry->frame = TEX_PATTERN_ANIM_NO_FRAME;
    }
    FrameCtrl_Init(&self->ctrl, (u32) frames, flags, (u32) speed, (u16) start);
}
CLEAN_AS(func_0205678c, TexPatternAnim_Start)

/* func_0205682c: every entry's transfer ended, then the animation cleared. The entries
 * themselves stay on the heap they were made on. */
void TexPatternAnim_Unload(TexPatternAnim *self)
{
    for (int i = 0; i < self->count; i++) {
        TexPatternAnim_ReleaseEntry(&self->entries[i]);
    }
    TexPatternAnim_Clear(self);
}
CLEAN_AS(func_0205682c, TexPatternAnim_Unload)

/* func_0205685c: the animation made for `model` with the textures of `texture_file`: `count`
 * entries made on `heap` (NULL: the current heap) and set up. 0 when the heap is full. */
int TexPatternAnim_Load(TexPatternAnim *self, u8 *model, u8 *texture_file, u8 count, Heap *heap)
{
    self->model = model;
    if (heap == NULL) {
        heap = data_021fbe94;
    }
    self->texture = func_021077e8(texture_file);
    self->count = count;
    self->entries = Heap_Alloc(heap, (int) sizeof(TexPatternAnimEntry) * self->count);
    if (self->entries == NULL) {
        return 0;
    }
    for (int i = 0; i < self->count; i++) {
        TexPatternAnim_ConstructEntry(&self->entries[i]);
        if (!TexPatternAnim_InitEntry(&self->entries[i])) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_0205685c, TexPatternAnim_Load)

/* func_020568dc: no model, animation or entries (the texture resource is left). */
void TexPatternAnim_Clear(TexPatternAnim *self)
{
    self->model = NULL;
    self->frames = 0;
    self->count = 0;
    self->entries = NULL;
    self->anim = NULL;
}
CLEAN_AS(func_020568dc, TexPatternAnim_Clear)

/* func_020568f0: the deleting destructor (the vtable's second entry). */
TexPatternAnim *TexPatternAnim_Delete(TexPatternAnim *self)
{
    self->ctrl.vtable = data_020dd164;
    FrameCtrl_Destruct(&self->ctrl);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_020568f0, TexPatternAnim_Delete)

/* func_02056910: the destructor (the vtable's first entry). */
TexPatternAnim *TexPatternAnim_Destruct(TexPatternAnim *self)
{
    self->ctrl.vtable = data_020dd164;
    FrameCtrl_Destruct(&self->ctrl);
    return self;
}
CLEAN_AS(func_02056910, TexPatternAnim_Destruct)

/* func_02056928: the constructor: the frame control's (frame 0, one frame a step, inline),
 * then nothing loaded. */
TexPatternAnim *TexPatternAnim_Construct(TexPatternAnim *self)
{
    self->ctrl.vtable = data_020dd184;
    self->ctrl.frame = 0;
    self->ctrl.previous = 0;
    self->ctrl.speed = 0x1000;
    self->ctrl.vtable = data_020dd164;
    TexPatternAnim_Clear(self);
    return self;
}
CLEAN_AS(func_02056928, TexPatternAnim_Construct)

/* func_02056958: whether the entry's material is held. */
int TexPatternAnim_IsHeld(const TexPatternAnimEntry *entry)
{
    return (entry->flags & TEX_PATTERN_ANIM_HELD) ? 1 : 0;
}
CLEAN_AS(func_02056958, TexPatternAnim_IsHeld)

/* func_02056968: the image of the entry's texture queued to be copied over its material's
 * texture in VRAM; when it cannot be, the entry forgets what it shows so the next update tries
 * again. */
void TexPatternAnim_CopyTexture(TexPatternAnimEntry *entry, u8 *model, u8 *texture)
{
    void *image = G3dRes_TextureImage((G3dResTex *) (void *) texture, entry->texture);
    if (VramCopyTask_QueueMaterialImage((VramCopyTask *) &entry->transfer, model, entry->material, image) == 0) {
        entry->key = TEX_PATTERN_ANIM_NONE;
        entry->texture = TEX_PATTERN_ANIM_NONE;
        entry->frame = TEX_PATTERN_ANIM_NO_FRAME;
    }
}
CLEAN_AS(func_02056968, TexPatternAnim_CopyTexture)

/* func_020569b0: the entry made to show the texture of whole frame `frame`: the last key that
 * starts at or before it (the first key when none does), its texture looked up by name in the
 * texture resource and copied when it is another one. Nothing for a material the model does
 * not have, nor when the frame or the key is the one shown already.
 * QUIRK: the key is counted in a byte, so a list of more than 256 keys would be searched
 * from its start again. */
void TexPatternAnim_UpdateEntry(TexPatternAnimEntry *entry, u32 frame, const u8 *anim, u8 *texture, u8 *model)
{
    if (entry->material == TEX_PATTERN_ANIM_NONE || frame == entry->frame) {
        return;
    }
    entry->frame = (u16) frame;

    const u8 *key = anim + read_u16(entry->keys + 6);
    int last = read_u16(entry->keys) - 1;
    u8 index = 0;
    while (index < last && read_u16(key + KEY_SIZE + KEY_FRAME) <= frame) {
        key += KEY_SIZE;
        index++;
    }
    if (entry->key == index) {
        return;
    }
    entry->key = index;

    const u8 *name = anim + read_u16(anim + ANIM_TEXTURE_NAMES) + key[KEY_NAME] * 16;
    u8 shown = (u8) NNS_G3dGetResDictIdxByName(texture + TEXTURE_DICT, name);
    if (shown == entry->texture) {
        return;
    }
    entry->texture = shown;
    TexPatternAnim_CopyTexture(entry, model, texture);
}
CLEAN_AS(func_020569b0, TexPatternAnim_UpdateEntry)

/* func_02056a38: nothing shown, and the transfer ended. */
void TexPatternAnim_ReleaseEntry(TexPatternAnimEntry *entry)
{
    TexPatternAnim_ResetEntry(entry);
    VramCopyTask_End((VramCopyTask *) &entry->transfer);
}
CLEAN_AS(func_02056a38, TexPatternAnim_ReleaseEntry)

/* func_02056a4c: nothing shown, and the transfer set up. 1. */
int TexPatternAnim_InitEntry(TexPatternAnimEntry *entry)
{
    TexPatternAnim_ResetEntry(entry);
    VramCopyTask_Reset((VramCopyTask *) &entry->transfer);
    return 1;
}
CLEAN_AS(func_02056a4c, TexPatternAnim_InitEntry)

/* func_02056a64: no material, texture, key or frame, not held, no animation data. */
void TexPatternAnim_ResetEntry(TexPatternAnimEntry *entry)
{
    entry->key = TEX_PATTERN_ANIM_NONE;
    entry->material = TEX_PATTERN_ANIM_NONE;
    entry->texture = TEX_PATTERN_ANIM_NONE;
    entry->flags = 0;
    entry->keys = NULL;
    entry->frame = TEX_PATTERN_ANIM_NO_FRAME;
}
CLEAN_AS(func_02056a64, TexPatternAnim_ResetEntry)

/* func_02056a8c: the entry's constructor: its transfer's. */
TexPatternAnimEntry *TexPatternAnim_ConstructEntry(TexPatternAnimEntry *entry)
{
    VramCopyTask_Construct((VramCopyTask *) &entry->transfer);
    return entry;
}
CLEAN_AS(func_02056a8c, TexPatternAnim_ConstructEntry)
