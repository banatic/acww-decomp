/* A texture pattern animation played by copying textures into one texture slot
 * (tex_slot_anim.h). */
#include "tex_slot_anim.h"

#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(TexSlotAnim, upload) == 0x18, "TexSlotAnim upload");
static_assert(offsetof(TexSlotAnim, target) == 0x50, "TexSlotAnim target");
static_assert(offsetof(TexSlotAnim, texture_name) == 0x54, "TexSlotAnim texture_name");
static_assert(offsetof(TexSlotAnim, palette_name) == 0x65, "TexSlotAnim palette_name");
static_assert(offsetof(TexSlotAnim, source) == 0x78, "TexSlotAnim source");
static_assert(offsetof(TexSlotAnim, palette_only) == 0x8c, "TexSlotAnim palette_only");
static_assert(sizeof(TexSlotAnim) == 0x90, "TexSlotAnim size");

/* The class's vtable and the frame control's. */
extern const u8 data_020dd194[];
extern const u8 data_020dd184[];

/* NitroSystem: the key of the texture pattern animation's material `material` shown at whole
 * frame `frame` (the frame at 0, the texture's index in the animation's names at 2, the
 * palette's at 3), NULL when there is none; the animation's names of textures and palettes;
 * the index of a 16-byte name in a resource dictionary (-1 when it is not there). */
extern const u8 *NNSi_G3dGetTexPatAnmFV(const u8 *anim, u32 material, u32 frame);
extern const u8 *NNSi_G3dGetTexPatAnmTexNameByIdx(const u8 *anim, u8 index);
extern const u8 *NNSi_G3dGetTexPatAnmPlttNameByIdx(const u8 *anim, u8 index);
extern int NNS_G3dGetResDictIdxByName(const u8 *dict, const u8 *name);

/* The animation's frame count, at 4. A key's texture and palette name indices. */
#define ANIM_FRAMES 4
#define KEY_TEXTURE 2
#define KEY_PALETTE 3

/* The frame control's step of one frame a call (20.12). */
#define ONE_FRAME 0x1000

/* func_020574c4: the source's texture and palette (by their names in the animation) of the
 * whole frame the frame control is at (bits 12 to 27 of its 20.12 frame); -1 for both without
 * a key, and for one the key does not name. */
void TexSlotAnim_CurrentIndices(TexSlotAnim *self, int *texture, int *palette)
{
    *palette = TEX_SLOT_ANIM_NONE;
    *texture = *palette;
    const u8 *key = NNSi_G3dGetTexPatAnmFV(self->anim, 0, ((u32) self->ctrl.frame >> 12) & 0xffff);
    if (key == NULL) {
        return;
    }
    const u8 *texture_name = NNSi_G3dGetTexPatAnmTexNameByIdx(self->anim, key[KEY_TEXTURE]);
    const u8 *palette_name = NNSi_G3dGetTexPatAnmPlttNameByIdx(self->anim, key[KEY_PALETTE]);
    *texture = texture_name != NULL ? NNS_G3dGetResDictIdxByName(self->source->texture_dict, texture_name) : -1;
    const u8 *palettes = (const u8 *) self->source + self->source->palette_dict;
    *palette = palette_name != NULL ? NNS_G3dGetResDictIdxByName(palettes, palette_name) : -1;
}
CLEAN_AS(func_020574c4, TexSlotAnim_CurrentIndices)

/* func_02057538: one frame of the animation: the frame control steps, and the texture and the
 * palette of the new frame are copied into the slot, each only when it changed (the texture
 * never while `palette_only` is set). Whether the copies were started; the indices copied are
 * kept only then. */
int TexSlotAnim_Update(TexSlotAnim *self)
{
    int texture;
    int palette;

    self->previous_texture = self->texture;
    FrameCtrl_Step(&self->ctrl);
    TexSlotAnim_CurrentIndices(self, &texture, &palette);
    if (self->texture == texture || self->palette_only != 0) {
        texture = TEX_SLOT_ANIM_NONE;
    }
    if (self->palette == palette) {
        palette = TEX_SLOT_ANIM_NONE;
    }
    const char *texture_name = TexSlotName_Text(&self->texture_name);
    const char *palette_name = TexSlotName_Text(&self->palette_name);
    if (TexUpload_SendByName(&self->upload, self->target, texture_name, palette_name, self->source, texture, palette) == 0) {
        return 0;
    }
    if (texture != TEX_SLOT_ANIM_NONE) {
        self->texture = texture;
    }
    if (palette != TEX_SLOT_ANIM_NONE) {
        self->palette = palette;
    }
    return 1;
}
CLEAN_AS(func_02057538, TexSlotAnim_Update)

/* func_020575e4: the animation started from its first frame, playing in a loop: the slot is
 * the target's texture and palette named, and the first frame's texture and palette are
 * copied into it. Always 1. */
int TexSlotAnim_Start(TexSlotAnim *self, G3dResTex *target, const char *texture_name, const char *palette_name,
                      G3dResTex *source, const u8 *anim, u8 palette_only)
{
    TexSlotAnim_Clear(self);
    self->palette_only = palette_only;
    TexSlotName_Set(&self->texture_name, texture_name);
    TexSlotName_Set(&self->palette_name, palette_name);
    self->target = target;
    self->source = source;
    self->anim = anim;
    FrameCtrl_Init(&self->ctrl, *(const u16 *) (const void *) (anim + ANIM_FRAMES), 0, ONE_FRAME, 0);
    TexSlotAnim_Update(self);
    return 1;
}
CLEAN_AS(func_020575e4, TexSlotAnim_Start)

/* func_02057640: no slot, resources or animation, and nothing copied yet (the previous
 * texture is kept). */
void TexSlotAnim_Clear(TexSlotAnim *self)
{
    self->target = NULL;
    self->source = NULL;
    self->anim = NULL;
    self->palette = TEX_SLOT_ANIM_NONE;
    self->texture = TEX_SLOT_ANIM_NONE;
}
CLEAN_AS(func_02057640, TexSlotAnim_Clear)

/* The destructor's work, members last to first, the frame control's own destructor last. */
static void destruct(TexSlotAnim *self)
{
    self->ctrl.vtable = data_020dd194;
    TexSlotAnim_Clear(self);
    TexSlotName_Destruct(&self->palette_name);
    TexSlotName_Destruct(&self->texture_name);
    TexUpload_Destruct(&self->upload);
    FrameCtrl_Destruct(&self->ctrl);
}

/* func_02057658: the deleting destructor (the vtable's second entry). */
TexSlotAnim *TexSlotAnim_Delete(TexSlotAnim *self)
{
    destruct(self);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_02057658, TexSlotAnim_Delete)

/* func_02057694: the destructor. */
TexSlotAnim *TexSlotAnim_Destruct(TexSlotAnim *self)
{
    destruct(self);
    return self;
}
CLEAN_AS(func_02057694, TexSlotAnim_Destruct)

/* func_020576cc: the constructor: the frame control's (at frame 0, one frame a step, inline)
 * then the class's vtable, the members' constructors, and nothing set. */
TexSlotAnim *TexSlotAnim_Construct(TexSlotAnim *self)
{
    self->ctrl.vtable = data_020dd184;
    self->ctrl.frame = 0;
    self->ctrl.previous = 0;
    self->ctrl.speed = ONE_FRAME;
    self->ctrl.vtable = data_020dd194;
    TexUpload_Construct(&self->upload);
    TexSlotName_Construct(&self->texture_name);
    TexSlotName_Construct(&self->palette_name);
    self->target = NULL;
    self->source = NULL;
    self->anim = NULL;
    self->palette = TEX_SLOT_ANIM_NONE;
    self->texture = TEX_SLOT_ANIM_NONE;
    self->previous_texture = TEX_SLOT_ANIM_NONE;
    return self;
}
CLEAN_AS(func_020576cc, TexSlotAnim_Construct)

/* func_0205772c: the name's text. */
const char *TexSlotName_Text(const TexSlotName *name)
{
    return name->text;
}
CLEAN_AS(func_0205772c, TexSlotName_Text)

/* func_02057730: the name set to `text` (nothing for NULL), the rest of its bytes cleared.
 * QUIRK: a text of 17 characters or more is cut to 17 bytes without its end. */
void TexSlotName_Set(TexSlotName *name, const char *text)
{
    if (text == NULL) {
        return;
    }
    size_t length = strlen(text) + 1;
    for (size_t i = 0; i < TEX_SLOT_NAME_SIZE; i++) {
        name->text[i] = i < length ? text[i] : 0;
    }
}
CLEAN_AS(func_02057730, TexSlotName_Set)

/* func_02057764: the name's destructor: nothing to do. */
void TexSlotName_Destruct(TexSlotName *name)
{
    (void) name;
}
CLEAN_AS(func_02057764, TexSlotName_Destruct)

/* func_02057768: the name's constructor: all its bytes cleared. */
void TexSlotName_Construct(TexSlotName *name)
{
    memset(name->text, 0, sizeof(name->text));
}
CLEAN_AS(func_02057768, TexSlotName_Construct)
