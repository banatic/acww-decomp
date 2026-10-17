/* The design editor of overlay 123 (design_editor.h): its destructors and constructor, its flags,
 * its two copies of the pixels, the places lit in its screen map, the loads of its layers and
 * of the design, its sprites, its states and the slots of its class. */
#include "design_editor.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "design_editor_canvas.h"
#include "design_editor_input.h"
#include "main/design.h"
#include "main/design_assets.h"
#include "main/design_info.h"
#include "main/design_sets.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/group_params.h"
#include "main/oam_buffer.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/scene_sound.h"
#include "main/screen_map.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/wfc_stats.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(DesignEditor, wipe_y) == 0x94, "wipe_y");
static_assert(offsetof(DesignEditor, flags) == 0x9c && offsetof(DesignEditor, tool) == 0xa4, "flags");
static_assert(offsetof(DesignEditor, pen_px) == 0xa8 && offsetof(DesignEditor, key_place) == 0xaa, "pen");
static_assert(offsetof(DesignEditor, cursor_px) == 0xaf && offsetof(DesignEditor, pen_x) == 0xb4, "cursor");
static_assert(offsetof(DesignEditor, label) == 0xb8 && sizeof(TextLabel) == 0x6c, "label");
static_assert(offsetof(DesignEditor, tasks) == 0x124 && sizeof(LayerTaskPair) == 0x38, "tasks");
static_assert(offsetof(DesignEditor, cursor_sprite) == 0x1cc && sizeof(Glider) == 0x64, "cursor sprite");
static_assert(offsetof(DesignEditor, screen) == 0x230 && offsetof(DesignEditor, pixels) == 0xa30, "screen");
static_assert(offsetof(DesignEditor, zoomed) == 0xe30 && offsetof(DesignEditor, chars) == 0x2e30, "zoomed");
static_assert(offsetof(DesignEditor, zoomed_chars) == 0x3030 && offsetof(DesignEditor, panel) == 0x5030, "panel");
static_assert(sizeof(DesignEditor) == 0x51fc, "size (func_ov123_0229c930)");

/* The scene's vtable. */
extern const u8 data_ov123_0229d024[];

/* The label's constructor and destructor, handed to __cxa_vec_ctor and __cxa_vec_cleanup (so
 * the game's symbols). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void *func_02070c08(void *label);
extern void *func_02070be8(void *label);

/* The SDK's word copy (from, to, bytes). */
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);

/* The scene heap the layers' files are read with. */
extern Heap *data_021fbe94;

/* The files of the editor's look. */
extern const char data_ov123_0229d21c[]; /* "menu/edit/obj.bpl" */
extern const char data_ov123_0229d230[]; /* "menu/edit/obj0.bch" */
extern const char data_ov123_0229d244[]; /* "menu/edit/obj1.bch" */
extern const char data_ov123_0229d258[]; /* "menu/edit/bg.bpl" */
extern const char data_ov123_0229d26c[]; /* "menu/edit/a.bsc" */
extern const char data_ov123_0229d27c[]; /* "menu/edit/b.bsc" */
extern const char data_ov123_0229d28c[]; /* "menu/edit/c.bsc" */
extern const char data_ov123_0229d29c[]; /* "menu/edit/bg1.bch" */
extern const char data_ov123_0229d2b0[]; /* "menu/edit/bg0.bch" */

/* The town's statistics record, whose first bytes are a design (main/wfc_stats.h). */
extern u8 data_021f3278[];

/* The places of the screen map lit or not (DesignEditor_SetPlacePalette): their left, right and
 * top cells (each two cells high), for the tools 0-0x0b and the palette button. */
#define DESIGN_EDITOR_MAP_PLACES 12
extern const u8 data_ov123_0229c9a4[];
extern const u8 data_ov123_0229c9b4[];
extern const u8 data_ov123_0229c9c4[];

/* The palettes of the screen map's places. */
#define DESIGN_EDITOR_MAP_UNLIT 4
#define DESIGN_EDITOR_MAP_LIT 5

/* The frames a pressed button stays lit. */
#define DESIGN_EDITOR_LIT_FRAMES 4

/* The sprites (one OBJ or a cell each). */
extern const OamEntry data_ov123_0229ceb0;            /* a shape's ends (DesignEditor_DrawMarker) */
extern const OamEntry data_ov123_0229cf08;            /* a preview dot */
extern OamEntry data_ov123_0229cf20;                  /* a box's corner, flipped by the corner */
extern const u16 data_ov123_0229cea0[4];              /* the corner's flips, in the field at attr1 bit 9 */
extern const OamEntry *const data_ov123_0229cfec[13]; /* the canvas cursor of each tool, or NULL */
extern const OamEntry data_ov123_0229ce90[];          /* the canvas cursor while picking a colour */
extern const OamEntry data_ov123_0229ce88;            /* drawn with the keys in use */
extern const OamEntry data_ov123_0229cf7c[];
extern const OamEntry data_ov123_0229cfcc[];         /* the colour's marker, at its x */
extern const OamEntry data_ov123_0229cea8[];         /* the palette's number box for palettes 0-8 */
extern const OamEntry data_ov123_0229cf6c[];         /* and for 9-15 */
extern const OamEntry *const data_ov123_0229cf60[3]; /* the key mode's sign */

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov123_0229d2e0; /* the sub states' guard */
extern u32 data_ov123_0229d2e8; /* the states' guard */
extern MemberPointer data_ov123_0229d34c[DESIGN_EDITOR_SUB_STATES];
extern MemberPointer data_ov123_0229d2ec[DESIGN_EDITOR_STATES];
extern const MemberPointer data_ov123_0229cf28, data_ov123_0229ce50, data_ov123_0229cf30, data_ov123_0229ce98,
    data_ov123_0229ced0, data_ov123_0229cf00, data_ov123_0229cef8, data_ov123_0229cef0, data_ov123_0229cee8,
    data_ov123_0229cf10, data_ov123_0229cee0, data_ov123_0229ce68, data_ov123_0229ce78;
extern const MemberPointer data_ov123_0229ce70, data_ov123_0229ce80, data_ov123_0229ced8, data_ov123_0229ce48,
    data_ov123_0229ce58, data_ov123_0229cf38, data_ov123_0229cec0, data_ov123_0229ce40, data_ov123_0229cf58,
    data_ov123_0229cf50, data_ov123_0229cf48, data_ov123_0229cf40;

/* The layers: the canvas, the tools and the palette on 6, 4 behind it, and 3 that the button
 * 0x0d shows and hides. */
#define DESIGN_EDITOR_LAYER_CANVAS LAYER_SUB_BG3
#define DESIGN_EDITOR_LAYER_BACK LAYER_SUB_BG1
#define DESIGN_EDITOR_LAYER_3 LAYER_SUB_BG0
#define DESIGN_EDITOR_LAYER_OBJ LAYER_SUB_OBJ
#define DESIGN_EDITOR_SUB_SCREEN 1

/* The wipes' margin on window 2. */
#define DESIGN_EDITOR_WIPE_MARGIN 0x30

/* What the parent (overlay 92's) is told: the scene ends with the backdrop closed. */
#define DESIGN_EDITOR_PARENT_CLOSE 0x44

/* An OAM_BUFFER draw's "keep" for the palette and the priority. */
#define DESIGN_EDITOR_KEEP (-1)

static MenuScene *de_scene(DesignEditor *self)
{
    return &self->base;
}

static LayerTask *de_task(DesignEditor *self, int index)
{
    return &self->tasks[index].first;
}

static int de_address(const void *p)
{
    return (int) (uintptr_t) p;
}

/* The cursor sprite's update through its class (vtable slot 3). */
static void de_update_cursor_sprite(DesignEditor *self)
{
    Glider *sprite = &self->cursor_sprite;
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* A cell drawn at full scale on the touch screen. */
static void de_draw_cell(const OamEntry *cell, int x, int y, int priority)
{
    OamBuffer_DrawCell(DESIGN_EDITOR_SUB_SCREEN, cell, x, y, DESIGN_EDITOR_KEEP, priority, 0x1000, 0x1000, 0, -1, 0, 0);
}

/* The base's members, then the base. The three layer tasks are not destructed. */
static void de_destroy_members(DesignEditor *self)
{
    self->base.vtable = data_ov123_0229d024;
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->cursor_sprite);
    __cxa_vec_cleanup(&self->label, 1, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    MenuScene_DestroyBase(de_scene(self));
}

/* func_ov123_022995a0 (vtable slot 0x40) */
DesignEditor *DesignEditor_Destroy(DesignEditor *self)
{
    de_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov123_022995a0, DesignEditor_Destroy)

/* func_ov123_022995e4 (vtable slot 0x44) */
DesignEditor *DesignEditor_Delete(DesignEditor *self)
{
    de_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov123_022995e4, DesignEditor_Delete)

/* func_ov123_02299630 */
void DesignEditor_ClearFlags(DesignEditor *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov123_02299630, DesignEditor_ClearFlags)

/* func_ov123_02299640 */
void DesignEditor_SetFlags(DesignEditor *self, unsigned int flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov123_02299640, DesignEditor_SetFlags)

/* func_ov123_02299650: 1 when any of the flags is set. */
int DesignEditor_TestFlags(DesignEditor *self, int flags)
{
    return (self->flags & (u32) flags) != 0;
}
CLEAN_AS(func_ov123_02299650, DesignEditor_TestFlags)

/* func_ov123_02299664: the touch screen's dimming (DesignEditor_Dim) taken off: the OBJ window's
 * brightness ended, the panel's flag 2 cleared and window 1 disabled. */
void DesignEditor_Undim(DesignEditor *self)
{
    DisplayShadow_EndSubObjWindowBrightness();
    ButtonPanel_ClearFlag2(&self->panel);
    DisplayShadow_DisableSubWindows(2);
}
CLEAN_AS(func_ov123_02299664, DesignEditor_Undim)

/* func_ov123_02299684: the touch screen dimmed for the panel's question: layer 3 hidden first
 * when shown (and remembered, DESIGN_EDITOR_FLAG_LAYER3_DIMMED), the brightness outside the OBJ
 * window lowered (-6), the panel's flag 2 set and window 1 put round (0x40, 0x18)-(0xc0, 0x98)
 * with all planes and no effects. */
void DesignEditor_Dim(DesignEditor *self)
{
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_LAYER3) != 0) {
        DesignEditor_HideLayer3(self);
        DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_LAYER3_DIMMED);
    }
    DisplayShadow_BeginSubObjWindowBrightness();
    DisplayShadow_SetSubBrightness((u8) -6);
    ButtonPanel_SetFlag2(&self->panel);
    DisplayShadow_SetSubWindow1Planes(0x1f, 0);
    DisplayShadow_EnableSubWindows(2);
    DisplayShadow_SetSubWindow1(0x40, 0x18, 0xc0, 0x98);
}
CLEAN_AS(func_ov123_02299684, DesignEditor_Dim)

/* func_ov123_02299930: layer 3 hidden, when shown. */
void DesignEditor_HideLayer3(DesignEditor *self)
{
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_LAYER3) != 0) {
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_LAYER3);
        DisplayLayer_Hide(DESIGN_EDITOR_LAYER_3);
    }
}
CLEAN_AS(func_ov123_02299930, DesignEditor_HideLayer3)

/* func_ov123_02299954: layer 3 shown, when hidden, blended over the planes behind it (planes 1
 * over 8, alpha 12). */
void DesignEditor_ShowLayer3(DesignEditor *self)
{
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_LAYER3) == 0) {
        DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_LAYER3);
        DisplayLayer_Show(DESIGN_EDITOR_LAYER_3);
        DisplayShadow_SetSubAlpha(1, 8, 0xc);
    }
}
CLEAN_AS(func_ov123_02299954, DesignEditor_ShowLayer3)

/* func_ov123_02299980: layer 3 hidden (sound 0x42) or shown (sound 0x41). */
void DesignEditor_ToggleLayer3(DesignEditor *self)
{
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_LAYER3) != 0) {
        DesignEditor_HideLayer3(self);
        SoundSys_PlaySe(0x42);
    } else {
        DesignEditor_ShowLayer3(self);
        SoundSys_PlaySe(0x41);
    }
}
CLEAN_AS(func_ov123_02299980, DesignEditor_ToggleLayer3)

/* func_ov123_02299d9c: the current copy of the pixels. */
u32 *DesignEditor_Pixels(DesignEditor *self)
{
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_FIRST_COPY)) {
        return self->pixels[0];
    }
    return self->pixels[1];
}
CLEAN_AS(func_ov123_02299d9c, DesignEditor_Pixels)

/* func_ov123_02299dc4: tool 5: the other copy made current (the one before the last stroke, or
 * after it again), sound 0x86c when this redoes and 0x86b when it undoes; the pixels redrawn. */
void DesignEditor_Undo(DesignEditor *self)
{
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_FIRST_COPY)) {
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_FIRST_COPY);
    } else {
        DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_FIRST_COPY);
    }
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_UNDONE)) {
        SoundSys_PlaySe(0x86c);
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_UNDONE);
    } else {
        SoundSys_PlaySe(0x86b);
        DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_UNDONE);
    }
    DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_DIRTY);
}
CLEAN_AS(func_ov123_02299dc4, DesignEditor_Undo)

/* func_ov123_02299e28: before a stroke: the current copy copied to the other, which becomes the
 * current one (so the stroke can be undone). */
void DesignEditor_Snapshot(DesignEditor *self)
{
    DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_UNDONE);
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_FIRST_COPY)) {
        MIi_CpuCopy32(self->pixels[0], self->pixels[1], sizeof self->pixels[0]);
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_FIRST_COPY);
    } else {
        MIi_CpuCopy32(self->pixels[1], self->pixels[0], sizeof self->pixels[0]);
        DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_FIRST_COPY);
    }
}
CLEAN_AS(func_ov123_02299e28, DesignEditor_Snapshot)

/* func_ov123_02299e84: the three layer tasks taken off the queue. */
void DesignEditor_EndLayerTasks(DesignEditor *self)
{
    for (int i = 0; i < DESIGN_EDITOR_TASKS; i++) {
        LayerTask_End(de_task(self, i));
    }
}
CLEAN_AS(func_ov123_02299e84, DesignEditor_EndLayerTasks)

/* func_ov123_02299ec4: a shape ends: the flag cleared and the corner sprite back to its first
 * flip (horizontal: the field of attr1's bits 9-13 keeps its bits 0-2, bit 3 set, bit 4
 * cleared). */
void DesignEditor_EndShape(DesignEditor *self)
{
    DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_SHAPE);
    u16 attr1 = data_ov123_0229cf20.attr1;
    u32 field = ((((u32) attr1 >> 9) & 0x1f) & ~0x18u) | 8;
    data_ov123_0229cf20.attr1 = (u16) ((attr1 & 0xc1ffu) | ((field & 0x1f) << 9));
}
CLEAN_AS(func_ov123_02299ec4, DesignEditor_EndShape)

/* func_ov123_02299f08: a shape starts (sound 0x866) at the pixel under the pen. */
void DesignEditor_StartShape(DesignEditor *self)
{
    SoundSys_PlaySe(0x866);
    DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_SHAPE);
    self->start_px = self->pen_px;
    self->start_py = self->pen_py;
}
CLEAN_AS(func_ov123_02299f08, DesignEditor_StartShape)

/* func_ov123_02299f40: the shape being dragged out, previewed with sprites: a line's two ends
 * and its points as dots (DesignEditor_Line with brush 3); a box's two corners (flipped by
 * which corner they are) and dots on every second pixel of its outline, the far sides' dots
 * lined up with the near sides' by the box's size. */
void DesignEditor_DrawShapePreview(DesignEditor *self)
{
    if (self->tool == DESIGN_EDITOR_TOOL_LINE) {
        DesignEditor_DrawMarker(self, self->pen_px, self->pen_py);
        DesignEditor_DrawMarker(self, self->start_px, self->start_py);
        DesignEditor_Line(self, self->pen_px, self->pen_py, self->start_px, self->start_py, 1, DESIGN_EDITOR_TOOL_DOTS);
        return;
    }
    u32 x_min = self->start_px;
    u32 pen_x = self->pen_px;
    u32 x_max;
    u32 start_corner;
    u32 pen_corner;
    if (pen_x >= x_min) {
        start_corner = 2;
        pen_corner = 0;
        x_max = pen_x;
    } else {
        start_corner = 0;
        pen_corner = 2;
        x_max = x_min;
        x_min = pen_x;
    }
    u32 y_min = self->start_py;
    u32 pen_y = self->pen_py;
    u32 y_max;
    if (pen_y >= y_min) {
        pen_corner++;
        y_max = pen_y;
    } else {
        start_corner++;
        y_max = y_min;
        y_min = pen_y;
    }
    DesignEditor_DrawShapeCorner(self, (int) pen_x, (int) pen_y, (int) pen_corner);
    DesignEditor_DrawShapeCorner(self, self->start_px, self->start_py, (int) start_corner);
    for (u32 x = x_min; x <= x_max; x = (u8) (x + 2)) {
        DesignEditor_DrawPreviewDot(self, (int) x, (int) y_min);
    }
    if (y_min != y_max) {
        u32 x = x_min;
        if ((y_max - y_min) & 1) {
            x = (u8) (x_min + 1);
        }
        for (; x <= x_max; x = (u8) (x + 2)) {
            DesignEditor_DrawPreviewDot(self, (int) x, (int) y_max);
        }
    }
    u32 first_y = y_min + 2;
    for (u32 y = (u8) first_y; y < y_max; y = (u8) (y + 2)) {
        DesignEditor_DrawPreviewDot(self, (int) x_min, (int) y);
    }
    if (x_min != x_max) {
        u32 y = (u8) first_y;
        if ((x_max - x_min) & 1) {
            y = (u8) (y - 1);
        }
        for (; y < y_max; y = (u8) (y + 2)) {
            DesignEditor_DrawPreviewDot(self, (int) x_max, (int) y);
        }
    }
}
CLEAN_AS(func_ov123_02299f40, DesignEditor_DrawShapePreview)

/* func_ov123_0229a094: a shape's end sprite at pixel (px, py). Answers the draw's answer. */
int DesignEditor_DrawMarker(DesignEditor *self, int px, int py)
{
    int x = DesignEditor_ScreenX(self, px);
    int y = DesignEditor_ScreenY(self, py);
    return OamBuffer_DrawObjAffine(DESIGN_EDITOR_SUB_SCREEN, &data_ov123_0229ceb0, x, y, DESIGN_EDITOR_KEEP,
                                   DESIGN_EDITOR_KEEP, NULL);
}
CLEAN_AS(func_ov123_0229a094, DesignEditor_DrawMarker)

/* func_ov123_0229a0cc: the canvas cursor of the tool at pixel (px, py) (the picker's while a
 * colour is picked; two pixels up and left for pen 2), when the tool has one. */
void DesignEditor_DrawToolCursor(DesignEditor *self, int px, int py)
{
    int x = DesignEditor_ScreenX(self, px);
    int y = DesignEditor_ScreenY(self, py);
    const OamEntry *cell = data_ov123_0229cfec[self->tool];
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_PICKING) != 0) {
        cell = data_ov123_0229ce90;
    }
    if (self->tool == DESIGN_EDITOR_TOOL_PEN_2) {
        x -= 2;
        y -= 2;
    }
    if (cell != NULL) {
        de_draw_cell(cell, x, y, DESIGN_EDITOR_KEEP);
    }
}
CLEAN_AS(func_ov123_0229a0cc, DesignEditor_DrawToolCursor)

/* func_ov123_0229a148: a preview dot at pixel (px, py). */
void DesignEditor_DrawPreviewDot(DesignEditor *self, int px, int py)
{
    int x = DesignEditor_ScreenX(self, px);
    int y = DesignEditor_ScreenY(self, py);
    OamBuffer_DrawObjAffine(DESIGN_EDITOR_SUB_SCREEN, &data_ov123_0229cf08, x, y, DESIGN_EDITOR_KEEP, DESIGN_EDITOR_KEEP,
                            NULL);
}
CLEAN_AS(func_ov123_0229a148, DesignEditor_DrawPreviewDot)

/* func_ov123_0229a180: a box's corner sprite at pixel (px, py), its flips (attr1's bits 12-13)
 * set by the corner (0-3). */
void DesignEditor_DrawShapeCorner(DesignEditor *self, int px, int py, int corner)
{
    int x = DesignEditor_ScreenX(self, px);
    int y = DesignEditor_ScreenY(self, py);
    u16 attr1 = data_ov123_0229cf20.attr1;
    u32 field = ((((u32) attr1 >> 9) & 0x1f) & ~0x18u) | data_ov123_0229cea0[corner];
    data_ov123_0229cf20.attr1 = (u16) ((attr1 & 0xc1ffu) | ((field & 0x1f) << 9));
    OamBuffer_DrawObjAffine(DESIGN_EDITOR_SUB_SCREEN, &data_ov123_0229cf20, x, y, DESIGN_EDITOR_KEEP, DESIGN_EDITOR_KEEP,
                            NULL);
}
CLEAN_AS(func_ov123_0229a180, DesignEditor_DrawShapeCorner)

/* func_ov123_0229a1e8: the palette number's box closed. */
void DesignEditor_CloseLabel(DesignEditor *self)
{
    TextLabel_CloseBox(&self->label);
}
CLEAN_AS(func_ov123_0229a1e8, DesignEditor_CloseLabel)

/* func_ov123_0229a1f4: a frame of the lit place: unlit when its frames run out. */
void DesignEditor_StepLitPlace(DesignEditor *self)
{
    if (self->lit_frames != 0) {
        self->lit_frames--;
        if (self->lit_frames == 0) {
            DesignEditor_UnlightPlace(self);
        }
    }
}
CLEAN_AS(func_ov123_0229a1f4, DesignEditor_StepLitPlace)

/* func_ov123_0229a224: the lit place unlit; none lit. */
void DesignEditor_UnlightPlace(DesignEditor *self)
{
    DesignEditor_SetPlacePalette(self, self->lit_place, DESIGN_EDITOR_MAP_UNLIT);
    self->lit_place = DESIGN_EDITOR_NO_PLACE;
    self->lit_frames = 0;
}
CLEAN_AS(func_ov123_0229a224, DesignEditor_UnlightPlace)

/* func_ov123_0229a248: `place` lit for four frames, the one lit before unlit. */
void DesignEditor_LightPlace(DesignEditor *self, unsigned char place)
{
    DesignEditor_UnlightPlace(self);
    self->lit_place = place;
    self->lit_frames = DESIGN_EDITOR_LIT_FRAMES;
    DesignEditor_SetPlacePalette(self, self->lit_place, DESIGN_EDITOR_MAP_LIT);
}
CLEAN_AS(func_ov123_0229a248, DesignEditor_LightPlace)

/* func_ov123_0229a278: `tool` chosen, when it is not already: the one before unlit (with sound
 * 0x0b, when there was one) and the new one lit. */
void DesignEditor_SelectTool(DesignEditor *self, unsigned char tool)
{
    u8 current = self->tool;
    if (current == tool) {
        return;
    }
    if (current != DESIGN_EDITOR_NO_TOOL) {
        DesignEditor_SetPlacePalette(self, current, DESIGN_EDITOR_MAP_UNLIT);
        SoundSys_PlaySe(0x0b);
    }
    self->tool = tool;
    DesignEditor_SetPlacePalette(self, self->tool, DESIGN_EDITOR_MAP_LIT);
}
CLEAN_AS(func_ov123_0229a278, DesignEditor_SelectTool)

/* func_ov123_0229a2b4: the screen map queued for layer 6 when it changed; the flag cleared once
 * the queue takes it. */
void DesignEditor_QueueScreen(DesignEditor *self)
{
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_SCREEN_DIRTY) == 0) {
        return;
    }
    if (LayerTask_QueueScreen(de_task(self, 2), de_address(self->screen), DESIGN_EDITOR_LAYER_CANVAS, sizeof self->screen,
                              0) != 0) {
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_SCREEN_DIRTY);
    }
}
CLEAN_AS(func_ov123_0229a2b4, DesignEditor_QueueScreen)

/* func_ov123_0229a2f8: the cells of `place` (a tool or the palette button) in the screen map set
 * to `palette`; nothing for other places. */
void DesignEditor_SetPlacePalette(DesignEditor *self, unsigned int place, unsigned int palette)
{
    if (place > DESIGN_EDITOR_PLACE_PALETTE) {
        return;
    }
    ScreenMap_SetPalette(self->screen, data_ov123_0229c9a4[place], data_ov123_0229c9c4[place], data_ov123_0229c9b4[place],
                         data_ov123_0229c9c4[place] + 2, palette);
    DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_SCREEN_DIRTY);
}
CLEAN_AS(func_ov123_0229a2f8, DesignEditor_SetPlacePalette)

/* func_ov123_0229b0dc: the design's palette set to `palette` (0-15), its colours queued for the
 * canvas, and its number shown (1-16, a space or "1" before the last digit, in wide digits). */
void DesignEditor_SetPalette(DesignEditor *self, int palette)
{
    /* BUG: the game hands five characters from a buffer of four (the fourth not set, the
     * fifth past it); the text ends at the third. These are zero here. */
    u16 text[5] = {0};
    self->palette = (u8) palette;
    DesignEditor_QueuePalette(self);
    text[0] = (unsigned int) palette < 9 ? 0x3000 : 0xff11;
    text[1] = (u16) (0xff10 + (palette + 1) % 10);
    text[2] = 0;
    TextLabel_SetFromWide(&self->label, text, (void *) (uintptr_t) 5);
    TextLabel_OpenStyledBox(&self->label, 8, 0x128, 2, 6, 0, 1);
    TextLabel_Show(&self->label, 0, 0);
}
CLEAN_AS(func_ov123_0229b0dc, DesignEditor_SetPalette)

/* func_ov123_0229b160: the colour drawn (1-15) and its marker's x. */
void DesignEditor_SetColour(DesignEditor *self, unsigned char colour)
{
    self->colour = colour;
    self->colour_x = (u8) ((colour - 1) * 12);
}
CLEAN_AS(func_ov123_0229b160, DesignEditor_SetColour)

/* func_ov123_0229b174: the design palette's colours queued as layer 6's palette 14. */
int DesignEditor_QueuePalette(DesignEditor *self)
{
    DesignManager *manager = (DesignManager *) (uintptr_t) DesignManager_Get();
    int colours = (int) DesignManager_Palette(manager, self->palette);
    return LayerTask_QueuePalette(de_task(self, 0), colours, DESIGN_EDITOR_LAYER_CANVAS, 0xe);
}
CLEAN_AS(func_ov123_0229b174, DesignEditor_QueuePalette)

/* func_ov123_0229b1a0: when the pixels changed: their characters and the zoomed ones rebuilt
 * and queued. */
void DesignEditor_Refresh(DesignEditor *self)
{
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_DIRTY)) {
        DesignEditor_MakeChars(self);
        DesignEditor_ZoomPixels(self);
        DesignEditor_QueueChars(self);
        DesignEditor_QueueZoomedChars(self);
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_DIRTY);
    }
}
CLEAN_AS(func_ov123_0229b1a0, DesignEditor_Refresh)

/* func_ov123_0229b1d4: the zoomed characters queued as layer 6's characters 0x20-0x11f. */
void DesignEditor_QueueZoomedChars(DesignEditor *self)
{
    LayerTask_QueueChars(de_task(self, 1), de_address(self->zoomed_chars), DESIGN_EDITOR_LAYER_CANVAS, 0x20, 0x20, 0x11f);
}
CLEAN_AS(func_ov123_0229b1d4, DesignEditor_QueueZoomedChars)

/* func_ov123_0229b204: the zoomed characters loaded at once (as DesignEditor_QueueZoomedChars). */
void DesignEditor_LoadZoomedChars(DesignEditor *self)
{
    DisplayLayer_LoadChars((u32) de_address(self->zoomed_chars), DESIGN_EDITOR_LAYER_CANVAS, 0x20, 0x20, 0x11f);
}
CLEAN_AS(func_ov123_0229b204, DesignEditor_LoadZoomedChars)

/* func_ov123_0229b308: the design's characters queued as layer 6's characters 0x120-0x12f. */
void DesignEditor_QueueChars(DesignEditor *self)
{
    LayerTask_QueueChars(de_task(self, 0), de_address(self->chars), DESIGN_EDITOR_LAYER_CANVAS, 0x120, 0x120, 0x12f);
}
CLEAN_AS(func_ov123_0229b308, DesignEditor_QueueChars)

/* func_ov123_0229b33c: the design's characters loaded at once. */
int DesignEditor_LoadChars(DesignEditor *self)
{
    return DisplayLayer_LoadChars((u32) de_address(self->chars), DESIGN_EDITOR_LAYER_CANVAS, 0x120, 0x120, 0x12f);
}
CLEAN_AS(func_ov123_0229b33c, DesignEditor_LoadChars)

/* func_ov123_0229b384: the pixels saved to the town record's design, made locally and with
 * the palette. */
void DesignEditor_SaveTownDesign(DesignEditor *self)
{
    Design *design = WfcStats_Design((WfcStats *) (void *) data_021f3278);
    Design_SetPixels(design, DesignEditor_Pixels(self));
    DesignInfo_SetCreatorLocal((DesignInfo *) (uintptr_t) Design_Info((unsigned int) (uintptr_t) design));
    DesignInfo_SetPalette((DesignInfo *) (uintptr_t) Design_Info((unsigned int) (uintptr_t) design), self->palette);
}
CLEAN_AS(func_ov123_0229b384, DesignEditor_SaveTownDesign)

/* func_ov123_0229b3c4: the town record's design taken into both copies, with its palette. */
void DesignEditor_LoadTownDesign(DesignEditor *self)
{
    Design *design = WfcStats_Design((WfcStats *) (void *) data_021f3278);
    MIi_CpuCopy32(Design_Pixels(design), self->pixels[0], sizeof self->pixels[0]);
    MIi_CpuCopy32(Design_Pixels(design), self->pixels[1], sizeof self->pixels[1]);
    DesignEditor_SetPalette(self,
                            DesignInfo_Palette((DesignInfo *) (uintptr_t) Design_Info((unsigned int) (uintptr_t) design)));
}
CLEAN_AS(func_ov123_0229b3c4, DesignEditor_LoadTownDesign)

/* The item codes of the player's designs worn: clothes and hats, one for each design slot. */
#define DESIGN_EDITOR_CLOTHES_FIRST 0x12a8
#define DESIGN_EDITOR_CLOTHES_LAST 0x12af
#define DESIGN_EDITOR_HAT_FIRST 0x1429
#define DESIGN_EDITOR_HAT_LAST 0x1430

/* The design slot an item code of [first, last] wears, or -1. */
static int de_worn_slot(u16 code, int first, int last)
{
    if (code >= first && code <= last) {
        return code - first;
    }
    return -1;
}

/* func_ov123_0229b41c: the pixels saved to the current player's design at GroupParams_Arg's
 * place of their order, made locally and with the palette. When the player wears that design's
 * slot as clothes or as a hat, the flags say so. */
void DesignEditor_SavePlayerDesign(DesignEditor *self)
{
    u8 *record = PlayerRecords_Current();
    PlayerDesigns *designs = PlayerRecord_Designs(record);
    u8 place = GroupParams_Arg();
    Design *design = (Design *) (uintptr_t) PlayerDesigns_InOrder(designs, place);
    Design_SetPixels(design, DesignEditor_Pixels(self));
    DesignInfo_SetCreatorLocal((DesignInfo *) (uintptr_t) Design_Info((unsigned int) (uintptr_t) design));
    DesignInfo_SetPalette((DesignInfo *) (uintptr_t) Design_Info((unsigned int) (uintptr_t) design), self->palette);
    int slot = DesignOrder_Get((unsigned char *) (uintptr_t) PlayerDesigns_Order(designs), place);
    int worn = de_worn_slot(*PlayerRecord_Clothes(record), DESIGN_EDITOR_CLOTHES_FIRST, DESIGN_EDITOR_CLOTHES_LAST);
    if (worn != -1 && worn == slot) {
        DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_WORN_CLOTHES);
    }
    worn = de_worn_slot(*PlayerRecord_HeadItem(record), DESIGN_EDITOR_HAT_FIRST, DESIGN_EDITOR_HAT_LAST);
    if (worn != -1 && worn == slot) {
        DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_WORN_HAT);
    }
}
CLEAN_AS(func_ov123_0229b41c, DesignEditor_SavePlayerDesign)

/* func_ov123_0229b508: the current player's design at GroupParams_Arg's place taken into both
 * copies, with its palette. */
void DesignEditor_LoadPlayerDesign(DesignEditor *self)
{
    PlayerDesigns *designs = PlayerRecord_Designs(PlayerRecords_Current());
    Design *design = (Design *) (uintptr_t) PlayerDesigns_InOrder(designs, GroupParams_Arg());
    MIi_CpuCopy32(Design_Pixels(design), self->pixels[0], sizeof self->pixels[0]);
    MIi_CpuCopy32(Design_Pixels(design), self->pixels[1], sizeof self->pixels[1]);
    DesignEditor_SetPalette(self,
                            DesignInfo_Palette((DesignInfo *) (uintptr_t) Design_Info((unsigned int) (uintptr_t) design)));
}
CLEAN_AS(func_ov123_0229b508, DesignEditor_LoadPlayerDesign)

/* func_ov123_0229bdfc: the sprites' palettes and characters ("menu/edit/obj.bpl", "obj0.bch",
 * "obj1.bch"). */
void DesignEditor_LoadObjects(DesignEditor *self)
{
    (void) self;
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov123_0229d21c, heap, DESIGN_EDITOR_LAYER_OBJ, 4, 4, 0xc);
    DisplayLayer_LoadCharsFromFile(data_ov123_0229d230, heap, DESIGN_EDITOR_LAYER_OBJ, 0xc0, 0xc0, 0x12f);
    DisplayLayer_LoadCharsFromFile(data_ov123_0229d244, heap, DESIGN_EDITOR_LAYER_OBJ, 0x130, 0x130, 0x19f);
}
CLEAN_AS(func_ov123_0229bdfc, DesignEditor_LoadObjects)

/* func_ov123_0229be60: the layers' palettes, screens and characters: layer 6's screen map read
 * into `screen` (where the places are lit) and loaded from there. */
void DesignEditor_LoadLayers(DesignEditor *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov123_0229d258, heap, DESIGN_EDITOR_LAYER_CANVAS, 4, 4, 0xe);
    RomFile_Read(data_ov123_0229d26c, self->screen, sizeof self->screen);
    DisplayLayer_LoadScreen(self->screen, DESIGN_EDITOR_LAYER_CANVAS, sizeof self->screen, 0);
    DisplayLayer_LoadScreenFromFile(data_ov123_0229d27c, heap, DESIGN_EDITOR_LAYER_BACK);
    DisplayLayer_LoadScreenFromFile(data_ov123_0229d28c, heap, DESIGN_EDITOR_LAYER_3);
    DisplayLayer_LoadCharsFromFile(data_ov123_0229d29c, heap, DESIGN_EDITOR_LAYER_CANVAS, 0x120, 0x120, 0x1ff);
    DisplayLayer_LoadCharsFromFile(data_ov123_0229d2b0, heap, DESIGN_EDITOR_LAYER_CANVAS, 0x10, 0x10, 0x1f);
}
CLEAN_AS(func_ov123_0229be60, DesignEditor_LoadLayers)

/* func_ov123_0229bf04: the touch screen in mode 0, its layers 6, 4 and 3 at priority 2 with
 * the first background control. */
void DesignEditor_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(DESIGN_EDITOR_LAYER_CANVAS, 2);
    DisplayLayer_SetBgControl(DESIGN_EDITOR_LAYER_CANVAS, 0, 0, 0);
    DisplayLayer_SetPriority(DESIGN_EDITOR_LAYER_BACK, 2);
    DisplayLayer_SetBgControl(DESIGN_EDITOR_LAYER_BACK, 0, 0, 0);
    DisplayLayer_SetPriority(DESIGN_EDITOR_LAYER_3, 2);
    DisplayLayer_SetBgControl(DESIGN_EDITOR_LAYER_3, 0, 0, 0);
}
CLEAN_AS(func_ov123_0229bf04, DesignEditor_SetUpLayers)

/* func_ov123_0229bf50: a frame's end: the pixels' characters and the screen map queued when
 * they changed. */
void DesignEditor_EndFrame(DesignEditor *self)
{
    DesignEditor_Refresh(self);
    DesignEditor_QueueScreen(self);
}
CLEAN_AS(func_ov123_0229bf50, DesignEditor_EndFrame)

/* func_ov123_0229bf64: a frame's start: the panel's and the label's text boxes closed, the lit
 * place's frame. */
void DesignEditor_BeginFrame(DesignEditor *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    DesignEditor_CloseLabel(self);
    DesignEditor_StepLitPlace(self);
}
CLEAN_AS(func_ov123_0229bf64, DesignEditor_BeginFrame)

/* func_ov123_0229bf88: an interactive frame's end (DesignEditor_EndFrame). */
void DesignEditor_EndInteractiveFrame(DesignEditor *self)
{
    DesignEditor_EndFrame(self);
}
CLEAN_AS(func_ov123_0229bf88, DesignEditor_EndInteractiveFrame)

/* func_ov123_0229bf90: an interactive frame's start, then the cursor sprite's update. */
void DesignEditor_BeginInteractiveFrame(DesignEditor *self)
{
    DesignEditor_BeginFrame(self);
    de_update_cursor_sprite(self);
}
CLEAN_AS(func_ov123_0229bf90, DesignEditor_BeginInteractiveFrame)

/* func_ov123_0229bfac: the scene's members ended: the text boxes closed and the layer tasks
 * taken off the queue; the player asked to go back to state 0x10, and the scene sound's slot
 * 0x24 given 0 when the town's design was edited. */
void DesignEditor_Teardown(DesignEditor *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    DesignEditor_CloseLabel(self);
    DesignEditor_EndLayerTasks(self);
    PlayerActorOps_RequestState10();
    if (GroupParams_Mode() == 3) {
        SceneSound_Vfunc24(0);
    }
}
CLEAN_AS(func_ov123_0229bfac, DesignEditor_Teardown)

/* func_ov123_0229bfe0: the editor's fields at its start: colour 1, no flags, nothing lit, the
 * key cursor on the first place and the canvas cursor at (16, 16); main's byte 0xc4c cleared and
 * the player asked into state 5. */
void DesignEditor_Reset(DesignEditor *self)
{
    DesignEditor_SetColour(self, 1);
    self->flags = 0;
    self->lit_place = DESIGN_EDITOR_NO_PLACE;
    DesignEditor_UnlightPlace(self);
    self->key_place = 0;
    self->saved_place = 0;
    self->key_mode = DESIGN_EDITOR_KEYS_PLACES;
    DesignEditor_EndShape(self);
    self->cursor_px = 0x10;
    self->cursor_py = 0x10;
    GroupParams_SetC4C(0);
    PlayerActorOps_RequestState5();
    self->slide = 0;
    self->key_delay = 0;
}
CLEAN_AS(func_ov123_0229bfe0, DesignEditor_Reset)

/* func_ov123_0229c044: layers 6, 4 and 3 scrolled up by `slide`. */
void DesignEditor_ScrollLayers(DesignEditor *self)
{
    DisplayLayer_SetScroll(DESIGN_EDITOR_LAYER_CANVAS, 0, -self->slide);
    DisplayLayer_SetScroll(DESIGN_EDITOR_LAYER_BACK, 0, -self->slide);
    DisplayLayer_SetScroll(DESIGN_EDITOR_LAYER_3, 0, -self->slide);
}
CLEAN_AS(func_ov123_0229c044, DesignEditor_ScrollLayers)

/* func_ov123_0229c07c: layers 6, 4 and 3 scrolled with the wipe (plus `slide`); the wipe's y
 * kept for the sprites. */
void DesignEditor_ScrollWithWipe(DesignEditor *self)
{
    MenuScene_ScrollWipe(de_scene(self), DESIGN_EDITOR_LAYER_CANVAS, 0, self->slide);
    MenuScene_ScrollWipe(de_scene(self), DESIGN_EDITOR_LAYER_BACK, 0, self->slide);
    MenuScene_ScrollWipe(de_scene(self), DESIGN_EDITOR_LAYER_3, 0, self->slide);
    self->wipe_y = MenuScene_WipeOffsetY(de_scene(self));
}
CLEAN_AS(func_ov123_0229c07c, DesignEditor_ScrollWithWipe)

/* func_ov123_0229c0c0 (state 0x0b): the panel's question gone, the layers slide back down two
 * pixels a frame; once the wipe is back, editing again (phase 2, DesignEditor_EnterIdle). */
void DesignEditor_EndQuestionWipeIn(DesignEditor *self)
{
    if (MenuScene_StepWipeBack(de_scene(self), -1) != 0) {
        MenuScene_SetPhase(de_scene(self), DESIGN_EDITOR_PHASE_INTERACTIVE);
        DesignEditor_EnterIdle(self);
        self->slide = 0;
    } else if (self->slide >= 2) {
        self->slide -= 2;
    } else {
        self->slide = 0;
    }
    DesignEditor_ScrollLayers(self);
}
CLEAN_AS(func_ov123_0229c0c0, DesignEditor_EndQuestionWipeIn)

/* func_ov123_0229c118 (state 0x0a): once the wipe is done, wiping back covered with the panel
 * in layout 2 (state 0x0b); the layers slide down two pixels a frame. */
void DesignEditor_EndQuestionWipeOut(DesignEditor *self)
{
    if (MenuScene_StepWipe(de_scene(self), -1) != 0) {
        MenuScene_StartWipeCovered(de_scene(self), 0, 0);
        ButtonPanel_SetLayout2(&self->panel);
        MenuScene_SetState(de_scene(self), DESIGN_EDITOR_STATE_END_QUESTION_WIPE_IN);
    }
    if (self->slide >= 2) {
        self->slide -= 2;
    } else {
        self->slide = 0;
    }
    DesignEditor_ScrollLayers(self);
}
CLEAN_AS(func_ov123_0229c118, DesignEditor_EndQuestionWipeOut)

/* func_ov123_0229c174 (state 9, the answer "no"): the dimming taken off, layer 3 shown again
 * when the dimming hid it, the panel wiping out (state 0x0a) with the layers 0x10 up. */
void DesignEditor_StartEndQuestion(DesignEditor *self)
{
    DesignEditor_Undim(self);
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_LAYER3_DIMMED)) {
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_LAYER3_DIMMED);
        DesignEditor_ShowLayer3(self);
    }
    MenuScene_StartWipe(de_scene(self), 0, 0);
    MenuScene_SetState(de_scene(self), DESIGN_EDITOR_STATE_END_QUESTION_WIPE_OUT);
    self->slide = 0x10;
}
CLEAN_AS(func_ov123_0229c174, DesignEditor_StartEndQuestion)

/* The layers' slide up for the question: two pixels a frame up to 0x10, where the screen is
 * dimmed. */
static void de_slide_up(DesignEditor *self)
{
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_DIM_LATER) != 0) {
        if (self->slide < 0x10) {
            self->slide += 2;
        } else {
            DesignEditor_Dim(self);
            self->slide = 0x10;
            DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_DIM_LATER);
        }
    }
}

/* func_ov123_0229c1b8 (state 8): once the wipe is back, the question is asked (phase 2,
 * DesignEditor_EnterPanel), and the screen dimmed at once if the slide had not done it; else
 * the layers keep sliding up. */
void DesignEditor_QuestionWipeIn(DesignEditor *self)
{
    if (MenuScene_StepWipeBack(de_scene(self), -1) != 0) {
        MenuScene_SetPhase(de_scene(self), DESIGN_EDITOR_PHASE_INTERACTIVE);
        DesignEditor_EnterPanel(self);
        if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_DIM_LATER) != 0) {
            DesignEditor_Dim(self);
            self->slide = 0x10;
            DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_DIM_LATER);
        }
    } else {
        de_slide_up(self);
    }
    DesignEditor_ScrollLayers(self);
}
CLEAN_AS(func_ov123_0229c1b8, DesignEditor_QuestionWipeIn)

/* func_ov123_0229c248 (state 7): once the wipe is done, wiping back covered with the panel's
 * question (message 0x87 "quit" with the quit flag, else 0x22; state 8); the layers slide up. */
void DesignEditor_QuestionWipeOut(DesignEditor *self)
{
    if (MenuScene_StepWipe(de_scene(self), -1) != 0) {
        MenuScene_StartWipeCovered(de_scene(self), 0, 0);
        if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_QUIT) != 0) {
            ButtonPanel_SetLayout7(&self->panel, 0x87);
        } else {
            ButtonPanel_SetLayout7(&self->panel, 0x22);
        }
        MenuScene_SetState(de_scene(self), DESIGN_EDITOR_STATE_QUESTION_WIPE_IN);
    }
    de_slide_up(self);
    DesignEditor_ScrollLayers(self);
}
CLEAN_AS(func_ov123_0229c248, DesignEditor_QuestionWipeOut)

/* func_ov123_0229c2dc (state 6, the save or quit button pressed): the panel wiping out (state
 * 7), the layers from 0 and the dimming to come. */
void DesignEditor_StartQuestion(DesignEditor *self)
{
    MenuScene_StartWipe(de_scene(self), 0, 0);
    MenuScene_SetState(de_scene(self), DESIGN_EDITOR_STATE_QUESTION_WIPE_OUT);
    self->slide = 0;
    DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_DIM_LATER);
}
CLEAN_AS(func_ov123_0229c2dc, DesignEditor_StartQuestion)

/* func_ov123_0229c30c (state 5): the wipe out; once done, the layers hidden with their scroll
 * reset, the end phase, no blend, the scene no longer drawn and the panel's layout cleared. */
void DesignEditor_WipeOut(DesignEditor *self)
{
    if (MenuScene_StepWipe(de_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(DESIGN_EDITOR_LAYER_CANVAS);
        DisplayLayer_HideAndResetScroll(DESIGN_EDITOR_LAYER_BACK);
        DisplayLayer_HideAndResetScroll(DESIGN_EDITOR_LAYER_3);
        MenuScene_SetPhase(de_scene(self), DESIGN_EDITOR_PHASE_END);
        DisplayShadow_SubBlendOff();
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_DRAWN);
        ButtonPanel_ClearLayout(&self->panel);
    } else {
        DesignEditor_ScrollWithWipe(self);
    }
}
CLEAN_AS(func_ov123_0229c30c, DesignEditor_WipeOut)

/* func_ov123_0229c35c (state 4): the dimming taken off, the parent told the scene ends with its
 * backdrop closed, and the wipe out on window 2 (state 5). */
void DesignEditor_StartWipeOut(DesignEditor *self)
{
    DesignEditor_Undim(self);
    MenuDispatch_SetMode((MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self), DESIGN_EDITOR_PARENT_CLOSE,
                         1);
    MenuScene_StartWipeOnWindow2(de_scene(self), 0xb, 0, 0, DESIGN_EDITOR_WIPE_MARGIN);
    DesignEditor_ScrollWithWipe(self);
    MenuScene_SetState(de_scene(self), DESIGN_EDITOR_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov123_0229c35c, DesignEditor_StartWipeOut)

/* func_ov123_0229c39c (state 3): once the player is past the start of state 7, the wipe out
 * (state 4). */
void DesignEditor_WaitPlayer(DesignEditor *self)
{
    if (PlayerActorOps_EarlyInState7() == 0) {
        MenuScene_SetState(de_scene(self), DESIGN_EDITOR_STATE_START_WIPE_OUT);
    }
}
CLEAN_AS(func_ov123_0229c39c, DesignEditor_WaitPlayer)

/* func_ov123_0229c3b8 (state 2, the answer "yes"): when the saved design is not worn, the wipe
 * out at once (state 4). Else the player is asked to put on the clothes, then the hat, again
 * (state 7 of the player, each asked until it is taken), and the scene waits for them
 * (state 3).
 * BUG: the hat taken clears the clothes' flag instead of the hat's; as the state moves on, it
 * changes nothing. */
void DesignEditor_FinishEditing(DesignEditor *self)
{
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_WORN_CLOTHES) == 0 &&
        DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_WORN_HAT) == 0) {
        MenuScene_SetState(de_scene(self), DESIGN_EDITOR_STATE_START_WIPE_OUT);
        DesignEditor_StartWipeOut(self);
        return;
    }
    u8 *record = PlayerRecords_Current();
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_WORN_CLOTHES) != 0) {
        if (PlayerActorOps_RequestState7Kind0Next10(PlayerRecord_Clothes(record)) == 0) {
            return;
        }
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_WORN_CLOTHES);
    }
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_WORN_HAT) != 0) {
        if (PlayerActorOps_RequestState7Kind2Next10(PlayerRecord_HeadItem(record)) == 0) {
            return;
        }
#ifdef BUGFIX
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_WORN_HAT);
#else
        DesignEditor_ClearFlags(self, DESIGN_EDITOR_FLAG_WORN_CLOTHES);
#endif
    }
    MenuScene_SetState(de_scene(self), DESIGN_EDITOR_STATE_WAIT_PLAYER);
}
CLEAN_AS(func_ov123_0229c3b8, DesignEditor_FinishEditing)

/* func_ov123_0229c448 (state 1): the wipe in; once back, editing (phase 2, DesignEditor_EnterIdle).
 * The layers follow the wipe. */
void DesignEditor_WipeIn(DesignEditor *self)
{
    if (MenuScene_StepWipeBack(de_scene(self), 0) != 0) {
        MenuScene_SetPhase(de_scene(self), DESIGN_EDITOR_PHASE_INTERACTIVE);
        DesignEditor_EnterIdle(self);
    }
    DesignEditor_ScrollWithWipe(self);
}
CLEAN_AS(func_ov123_0229c448, DesignEditor_WipeIn)

/* func_ov123_0229c470 (state 0): the layers set up and loaded, tool 0 chosen, the sprites
 * loaded, the design taken (GroupParams_Mode 2: the player's, 3: the town's), its characters
 * made and loaded at once; the panel in layout 2, the wipe in on window 2, layers 6, 4 and 3
 * shown, the scene drawn (state 1). */
void DesignEditor_StartSetup(DesignEditor *self)
{
    DesignEditor_SetUpLayers();
    DesignEditor_LoadLayers(self);
    self->tool = DESIGN_EDITOR_NO_TOOL;
    DesignEditor_SelectTool(self, DESIGN_EDITOR_TOOL_PEN_1);
    DesignEditor_LoadObjects(self);
    switch (GroupParams_Mode()) {
        case 2:
            DesignEditor_LoadPlayerDesign(self);
            break;
        case 3:
            DesignEditor_LoadTownDesign(self);
            break;
    }
    DesignEditor_MakeChars(self);
    DesignEditor_ZoomPixels(self);
    DesignEditor_LoadChars(self);
    DesignEditor_LoadZoomedChars(self);
    ButtonPanel_SetLayout2(&self->panel);
    MenuScene_StartWipeCoveredOnWindow2(de_scene(self), 0xb, 4, 0, DESIGN_EDITOR_WIPE_MARGIN);
    DisplayLayer_Show(DESIGN_EDITOR_LAYER_CANVAS);
    DisplayLayer_Show(DESIGN_EDITOR_LAYER_BACK);
    DesignEditor_ShowLayer3(self);
    DesignEditor_ScrollWithWipe(self);
    DesignEditor_SetFlags(self, DESIGN_EDITOR_FLAG_DRAWN);
    MenuScene_SetState(de_scene(self), DESIGN_EDITOR_STATE_WIPE_IN);
}
CLEAN_AS(func_ov123_0229c470, DesignEditor_StartSetup)

/* func_ov123_0229c518 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int DesignEditor_End(DesignEditor *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov123_0229c518, DesignEditor_End)

/* func_ov123_0229c528 (vtable slot 0x58, phase 4): nothing. */
int DesignEditor_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov123_0229c528, DesignEditor_Phase4Idle)

/* func_ov123_0229c52c (vtable slot 0x54, phase 3): nothing. */
int DesignEditor_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov123_0229c52c, DesignEditor_Phase3Idle)

/* Obj_ov123_0229d024::func_ov123_0229c530 (vtable slot 0x50, phase 2): an interactive frame:
 * its start, its sub state and its end. Answers 1. */
int DesignEditor_RunInteractive(DesignEditor *self)
{
    DesignEditor_BeginInteractiveFrame(self);
    DesignEditor_RunSubState(self);
    DesignEditor_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov123_0229d02419func_ov123_0229c530Ev, DesignEditor_RunInteractive)

/* Obj_ov123_0229d024::func_ov123_0229c54c: the sub state's function (DesignEditorSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 0x0d; the game reads past the table for others. */
void DesignEditor_RunSubState(DesignEditor *self)
{
    static const MemberPointer *const sub_states[DESIGN_EDITOR_SUB_STATES] = {
        &data_ov123_0229cf28, &data_ov123_0229ce50, &data_ov123_0229cf30, &data_ov123_0229ce98, &data_ov123_0229ced0,
        &data_ov123_0229cf00, &data_ov123_0229cef8, &data_ov123_0229cef0, &data_ov123_0229cee8, &data_ov123_0229cf10,
        &data_ov123_0229cee0, &data_ov123_0229ce68, &data_ov123_0229ce78,
    };
    MemberTable_InitOnce(&data_ov123_0229d2e0, data_ov123_0229d34c, sub_states, DESIGN_EDITOR_SUB_STATES);
    MemberPointer_CallVoid(&data_ov123_0229d34c[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov123_0229d02419func_ov123_0229c54cEv, DesignEditor_RunSubState)

/* func_ov123_0229c650 (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (DesignEditorState) between the frame's start and end, through the table of member functions
 * (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 0x0c; the game reads past the table for others. */
int DesignEditor_RunState(DesignEditor *self)
{
    static const MemberPointer *const states[DESIGN_EDITOR_STATES] = {
        &data_ov123_0229ce70, &data_ov123_0229ce80, &data_ov123_0229ced8, &data_ov123_0229ce48,
        &data_ov123_0229ce58, &data_ov123_0229cf38, &data_ov123_0229cec0, &data_ov123_0229ce40,
        &data_ov123_0229cf58, &data_ov123_0229cf50, &data_ov123_0229cf48, &data_ov123_0229cf40,
    };
    MemberTable_InitOnce(&data_ov123_0229d2e8, data_ov123_0229d2ec, states, DESIGN_EDITOR_STATES);
    DesignEditor_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov123_0229d2ec[self->base.state], self);
    DesignEditor_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov123_0229c650, DesignEditor_RunState)

/* func_ov123_0229c754 (vtable slot 0x24): the scene's sprites. With the keys in use
 * (StateFlags_Test2): on the canvas the tool's cursor (none while a shape is dragged out), else
 * the cursor sprite. The shape's preview, the panel at the wipe's y. While the scene is drawn,
 * at the layers' offset plus the wipe's y: the colour's marker and the palette number's box,
 * and with the keys in use two more sprites and the key mode's sign. Answers 1. */
int DesignEditor_Draw(DesignEditor *self)
{
    if (StateFlags_Test2()) {
        if (self->key_mode == DESIGN_EDITOR_KEYS_CANVAS) {
            if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_SHAPE) == 0) {
                DesignEditor_DrawToolCursor(self, self->cursor_px, self->cursor_py);
            }
        } else {
            Glider_DrawWrapped(&self->cursor_sprite);
        }
    }
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_SHAPE) != 0) {
        DesignEditor_DrawShapePreview(self);
    }
    ButtonPanel_Draw(&self->panel, MenuScene_WipeOffsetY(de_scene(self)));
    if (DesignEditor_TestFlags(self, DESIGN_EDITOR_FLAG_DRAWN) != 0) {
        int y = (int) ((u32) self->slide + ((u32) self->wipe_y + 0x60));
        if (StateFlags_Test2()) {
            OamBuffer_DrawObjAffine(DESIGN_EDITOR_SUB_SCREEN, &data_ov123_0229ce88, 0x80, y, DESIGN_EDITOR_KEEP,
                                    DESIGN_EDITOR_KEEP, NULL);
            de_draw_cell(data_ov123_0229cf7c, 0x80, y, DESIGN_EDITOR_KEEP);
        }
        de_draw_cell(data_ov123_0229cfcc, self->colour_x + 0x80, y, 2);
        if (self->palette < 9) {
            de_draw_cell(data_ov123_0229cea8, 0x80, y, 2);
        } else {
            de_draw_cell(data_ov123_0229cf6c, 0x80, y, 2);
        }
        if (StateFlags_Test2()) {
            de_draw_cell(data_ov123_0229cf60[self->key_mode], 0x80, y, DESIGN_EDITOR_KEEP);
        }
    }
    return 1;
}
CLEAN_AS(func_ov123_0229c754, DesignEditor_Draw)

/* func_ov123_0229c8f4 (vtable slot 0x0c): the scene closes: the parent told and the members
 * torn down. Answers 1. */
int DesignEditor_Close(DesignEditor *self)
{
    MenuDispatch_ChildClosed((MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self));
    DesignEditor_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov123_0229c8f4, DesignEditor_Close)

/* func_ov123_0229c910 (vtable slot 0x00): the scene starts: its fields reset, state 0 (written
 * as it is, not through MenuScene_SetState) and phase 0. Answers 1. */
int DesignEditor_Start(DesignEditor *self)
{
    DesignEditor_Reset(self);
    self->base.state = DESIGN_EDITOR_STATE_SETUP;
    MenuScene_SetPhase(de_scene(self), DESIGN_EDITOR_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov123_0229c910, DesignEditor_Start)

/* func_ov123_0229c930: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed in order, the label by __cxa_vec_ctor. */
DesignEditor *DesignEditor_New(void)
{
    DesignEditor *self = MenuScene_Alloc(sizeof(DesignEditor));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(de_scene(self));
    self->base.vtable = data_ov123_0229d024;
    __cxa_vec_ctor(&self->label, 1, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    for (int i = 0; i < DESIGN_EDITOR_TASKS; i++) {
        LayerTask_ConstructPair(&self->tasks[i]);
    }
    Glider0_Construct(&self->cursor_sprite);
    ButtonPanel_Construct(&self->panel);
    return self;
}
CLEAN_AS(func_ov123_0229c930, DesignEditor_New)
