/* Overlay 124's object (han_panel.h). */
#include "han_panel.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/c_library.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/oam_buffer.h"
#include "main/rom_file.h"

/* The heap the files are loaded into. */
extern Heap *data_021fbe94;

/* The sign's characters, five kinds a file: "menu/han/obj0.bch" to "menu/han/obj3.bch". */
extern const char *const data_ov124_0229f4a0[4];
/* The backgrounds' screens: "menu/han/a_bg.bsc", "c_bg", "d_bg", "f_bg", "g_bg" and "e_bg". */
extern const char *const data_ov124_0229f578[6];
/* The OBJs drawn under the panel: alone (HanPanel_DrawBase) and with the sign. */
extern const OamEntry data_ov124_0229f590[];
extern const OamEntry data_ov124_0229f5b0[];
/* The sign's cells. */
extern const PanelCell data_ov124_0229f5d0[];
extern const char data_ov124_0229f610[]; /* "menu/han/ten0_obj.bpl" */
extern const char data_ov124_0229f628[]; /* "menu/han/bg.bch" */
extern const char data_ov124_0229f638[]; /* "menu/han/bg.bpl" */
extern const char data_ov124_0229f648[]; /* "menu/han/bg%d.bch" */
extern const char data_ov124_0229f65c[]; /* "menu/han/ten0_bg.bpl" */
extern const char data_ov124_0229f674[]; /* "menu/han/b_bg.bsc" */

/* The label's class: its constructor and destructor (main/text_label.h), handed to the array
 * helpers. */
extern TextLabel *func_02070c08(TextLabel *label);
extern TextLabel *func_02070be8(TextLabel *label);

/* The C++ runtime's array helpers. */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The sign's characters: 5 kinds a file, 0xc0 bytes (6 characters) a kind on each of 6 rows
 * of 0x400 bytes, loaded to characters 0x15a-0x15f, 0x17a-0x17f, ... of layer 8. */
#define SIGN_KINDS_PER_FILE 5
#define SIGN_KIND_BYTES 0xc0
#define SIGN_ROWS 6
#define SIGN_ROW_BYTES 0x400
#define SIGN_FIRST_CHAR 0x15a
#define SIGN_ROW_CHARS 0x20
#define SIGN_CHARS 5
#define SIGN_LAYER 8
#define SIGN_TEXT_CELLS 0xe
#define SIGN_SHADOW_CELL 2

/* The OBJs: on the sub screen, from its centre, at priority 2, unscaled. */
#define OBJ_SCREEN 1
#define OBJ_CENTER_X 0x80
#define OBJ_CENTER_Y 0x60
#define OBJ_PRIORITY 2
#define OBJ_SCALE 0x1000

/* The background's characters and palettes. */
#define BG_FIRST_CHAR 0x10
#define BG_LAST_CHAR 0x169
#define BG_KIND_FIRST_CHAR 0x113
#define BG_KIND_LAST_CHAR 0x126
#define BG_KIND_PALETTE 0xe

/* The screen HanPanel_ShowModeMessage loads. */
#define MESSAGE_SCREEN 5

/* func_ov124_0229eea0: the label's box and the sign's text closed. */
void HanPanel_CloseTexts(HanPanel *self)
{
    TextLabel_CloseBox(&self->label);
    PanelSprite_CloseText(&self->sign);
}
CLEAN_AS(func_ov124_0229eea0, HanPanel_CloseTexts)

/* func_ov124_0229eeb8: the sign drawn at (x, y), then its OBJs (data_ov124_0229f5b0) in its
 * palette. */
void HanPanel_DrawWithSign(HanPanel *self, int x, int y)
{
    PanelSprite_Draw(&self->sign, x, y, -1);
    OamBuffer_DrawCell(OBJ_SCREEN, data_ov124_0229f5b0, x + OBJ_CENTER_X, y + OBJ_CENTER_Y, self->palette, OBJ_PRIORITY,
                       OBJ_SCALE, OBJ_SCALE, 0, -1, 0, 0);
}
CLEAN_AS(func_ov124_0229eeb8, HanPanel_DrawWithSign)

/* func_ov124_0229ef08: only the OBJs of data_ov124_0229f590 drawn at (x, y), in the sign's
 * palette. */
void HanPanel_DrawBase(HanPanel *self, int x, int y)
{
    OamBuffer_DrawCell(OBJ_SCREEN, data_ov124_0229f590, x + OBJ_CENTER_X, y + OBJ_CENTER_Y, self->palette, OBJ_PRIORITY,
                       OBJ_SCALE, OBJ_SCALE, 0, -1, 0, 0);
}
CLEAN_AS(func_ov124_0229ef08, HanPanel_DrawBase)

/* func_ov124_0229ef4c: the sign set up for `kind`: its characters loaded from their file (6
 * rows of 6 characters into layer 8, the file freed after), its palette `kind` of
 * "ten0_obj.bpl" loaded into OBJ palette `palette` (kept for the draws), its cells set and its
 * message chosen by the mode (none for other modes). */
void HanPanel_LoadSign(HanPanel *self, int palette)
{
    int kind = self->kind;
    Heap *heap = data_021fbe94;
    u32 size;
    u8 *file = RomFile_Load(data_ov124_0229f4a0[kind / SIGN_KINDS_PER_FILE], heap, -4, &size);
    const u8 *row = file + (kind % SIGN_KINDS_PER_FILE) * SIGN_KIND_BYTES;
    u32 first = SIGN_FIRST_CHAR;
    for (int i = 0; i < SIGN_ROWS; i++) {
        DisplayLayer_LoadChars((u32) (uintptr_t) row, SIGN_LAYER, first, first, first + SIGN_CHARS);
        row += SIGN_ROW_BYTES;
        first += SIGN_ROW_CHARS;
    }
    Heap_Free(heap, file);
    DisplayLayer_LoadPaletteFromFile(data_ov124_0229f610, heap, SIGN_LAYER, self->kind, (u8) palette);
    self->palette = (u8) palette;
    PanelSprite_SetCells(&self->sign, data_ov124_0229f5d0, SIGN_TEXT_CELLS, SIGN_SHADOW_CELL);

    switch (GroupParams_Mode()) {
        case 0x0b:
            PanelSprite_ShowFlat(&self->sign, 0x3b);
            break;
        case 0x0f:
            PanelSprite_ShowFlat(&self->sign, 0xe6);
            break;
        case 0x10:
            PanelSprite_ShowFlat(&self->sign, 0xe7);
            break;
        case 0x18:
        case 0x19:
            PanelSprite_ShowFlat(&self->sign, 0xe9);
            break;
        case 0x1a:
        case 0x1b:
            PanelSprite_ShowFlat(&self->sign, 0xe8);
            break;
        case 0x0c:
            PanelSprite_ShowFlat(&self->sign, 0x42);
            break;
        case 0x0d:
            PanelSprite_ShowFlat(&self->sign, 0x44);
            break;
        case 0x0e:
            PanelSprite_ShowFlat(&self->sign, 0x48);
            break;
        case 0x12:
            PanelSprite_ShowFlat(&self->sign, 0x4e);
            break;
        case 0x13:
            PanelSprite_ShowFlat(&self->sign, 0x4d);
            break;
        case 0x14:
            PanelSprite_ShowFlat(&self->sign, 0x4f);
            break;
        case 0x15:
            PanelSprite_ShowFlat(&self->sign, 0x45);
            break;
        case 0x16:
            PanelSprite_ShowFlat(&self->sign, 0x46);
            break;
        case 0x11:
            PanelSprite_ShowFlat(&self->sign, 0x4c);
            break;
        case 0x17:
            PanelSprite_ShowFlat(&self->sign, 0x41);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov124_0229ef4c, HanPanel_LoadSign)

/* The background's kind for the current mode (0 for modes not listed). */
static u8 kind_of_mode(void)
{
    switch (GroupParams_Mode()) {
        case 0x04:
        case 0x05:
        case 0x07:
        case 0x08:
            return 0;
        case 0x06:
        case 0x09:
            return 2;
        case 0x0b:
            return 1;
        case 0x0c:
            return 3;
        case 0x0d:
            return 4;
        case 0x0e:
            return 7;
        case 0x0f:
        case 0x1a:
        case 0x1b:
            return 5;
        case 0x10:
        case 0x18:
        case 0x19:
            return 6;
        case 0x11:
            return 8;
        case 0x12:
            return 0xe;
        case 0x13:
            return 0xd;
        case 0x14:
            return 0xc;
        case 0x15:
            return 0xb;
        case 0x16:
            return 9;
        case 0x17:
            return 0xa;
        case 0x0a:
            return 0xf;
        default:
            return 0;
    }
}

/* func_ov124_0229f0ec: the background loaded into `layer`: the shared characters
 * ("menu/han/bg.bch", characters 0x10-0x169) and palettes 1-6 ("menu/han/bg.bpl"); the kind
 * chosen by the mode and kept, its characters ("menu/han/bg<kind>.bch", 0x113-0x126) and its
 * palette `kind` of "ten0_bg.bpl" into palette 14; then screen `screen` of
 * data_ov124_0229f578, whose load's answer is answered. */
int HanPanel_LoadBackground(HanPanel *self, int layer, int screen)
{
    Heap *heap = data_021fbe94;
    char path[0x24];

    DisplayLayer_LoadCharsFromFile(data_ov124_0229f628, heap, layer, BG_FIRST_CHAR, BG_FIRST_CHAR, BG_LAST_CHAR);
    DisplayLayer_LoadPalettesFromFile(data_ov124_0229f638, heap, layer, 1, 1, 6);
    self->kind = kind_of_mode();
    CLib_SPrintf(path, data_ov124_0229f648, self->kind);
    DisplayLayer_LoadCharsFromFile(path, heap, layer, BG_KIND_FIRST_CHAR, BG_KIND_FIRST_CHAR, BG_KIND_LAST_CHAR);
    DisplayLayer_LoadPaletteFromFile(data_ov124_0229f65c, heap, layer, self->kind, BG_KIND_PALETTE);
    return DisplayLayer_LoadScreenFromFile(data_ov124_0229f578[screen], heap, layer);
}
CLEAN_AS(func_ov124_0229f0ec, HanPanel_LoadBackground)

/* func_ov124_0229f27c: the text's style for the current mode (HanPanelStyle). */
int HanPanel_TextStyle(HanPanel *self)
{
    (void) self;
    switch (GroupParams_Mode()) {
        case 0x0f:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
            return HAN_PANEL_STYLE_1;
        case 0x15:
            return HAN_PANEL_STYLE_3;
        default:
            return HAN_PANEL_STYLE_0;
    }
}
CLEAN_AS(func_ov124_0229f27c, HanPanel_TextStyle)

/* func_ov124_0229f2c8 */
void HanPanel_SetTextBoxParams(HanPanel *self, int a, int b, int c, int d)
{
    TextLabel_SetBoxParams(&self->label, a, b, c, d);
}
CLEAN_AS(func_ov124_0229f2c8, HanPanel_SetTextBoxParams)

/* func_ov124_0229f2dc */
void HanPanel_SetTextFromWide(HanPanel *self, const u16 *text, void *length)
{
    TextLabel_SetFromWide(&self->label, text, length);
}
CLEAN_AS(func_ov124_0229f2dc, HanPanel_SetTextFromWide)

/* func_ov124_0229f2e4: the label shown, 2 pixels in for styles 0 and 1, at 0 for 2-4.
 * REQUIRES: the style is 0-4 (HanPanel_TextStyle answers 0, 1 or 3); the ROM passes an unset
 * offset for others. */
void HanPanel_ShowText(HanPanel *self)
{
    int offset = 0;
    switch (HanPanel_TextStyle(self)) {
        case 0:
        case 1:
            offset = 2;
            break;
        default:
            offset = 0;
            break;
    }
    TextLabel_ShowAt(&self->label, offset);
}
CLEAN_AS(func_ov124_0229f2e4, HanPanel_ShowText)

/* func_ov124_0229f320: the label's box opened in style 3 (colours 4 and 1, 0x11 wide) with a
 * height by the text's style: 0xd, 8, 0x14, 5 or 0xa for styles 0-4.
 * REQUIRES: the style is 0-4 (HanPanel_TextStyle answers 0, 1 or 3); the ROM passes an unset
 * height for others. */
void HanPanel_OpenTextBox(HanPanel *self)
{
    static const u8 heights[5] = {0xd, 8, 0x14, 5, 0xa};
    unsigned int style = (unsigned int) HanPanel_TextStyle(self);
    int height = style < 5 ? heights[style] : 0;
    TextLabel_OpenStyledBox2(&self->label, 3, 0x11, height, 4, 1, 0);
}
CLEAN_AS(func_ov124_0229f320, HanPanel_OpenTextBox)

/* func_ov124_0229f378: the background loaded into `layer` with the screen of the text's style;
 * the screen load's answer. */
int HanPanel_LoadStyledBackground(HanPanel *self, int layer)
{
    int style = HanPanel_TextStyle(self);
    return HanPanel_LoadBackground(self, layer, style);
}
CLEAN_AS(func_ov124_0229f378, HanPanel_LoadStyledBackground)

/* func_ov124_0229f398: the background loaded into `layer` with screen 5, "menu/han/b_bg.bsc"
 * loaded into `second_layer`, and the label given a message of "2d_menu" by the mode (0x3a for
 * modes not listed), opened with `layer` as its style and shown centred.
 * QUIRK: the box's style is the layer number the caller passes. */
void HanPanel_ShowModeMessage(HanPanel *self, int layer, int second_layer)
{
    int message;

    HanPanel_LoadBackground(self, layer, MESSAGE_SCREEN);
    DisplayLayer_LoadScreenFromFile(data_ov124_0229f674, data_021fbe94, second_layer);
    switch (GroupParams_Mode()) {
        case 0x05:
            message = 0x90;
            break;
        case 0x08:
        case 0x09:
            message = 0x92;
            break;
        case 0x06:
            message = 0x49;
            break;
        default: /* modes 0x04, 0x07 and 0x0a among them */
            message = 0x3a;
            break;
    }
    TextLabel_LoadMenuMessage(&self->label, (char) message);
    TextLabel_OpenStyledBox2(&self->label, layer, 0x11, 0xd, 4, 1, 0);
    TextLabel_Show(&self->label, 1, 0);
}
CLEAN_AS(func_ov124_0229f398, HanPanel_ShowModeMessage)

/* func_ov124_0229f43c: the sign destroyed, then the label (an array of one). */
HanPanel *HanPanel_Destroy(HanPanel *self)
{
    PanelSprite_Destroy(&self->sign);
    __cxa_vec_cleanup(&self->label, 1, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    return self;
}
CLEAN_AS(func_ov124_0229f43c, HanPanel_Destroy)

/* func_ov124_0229f460: the label (an array of one) constructed, then the sign. */
HanPanel *HanPanel_Construct(HanPanel *self)
{
    __cxa_vec_ctor(&self->label, 1, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    PanelSprite_Construct(&self->sign);
    return self;
}
CLEAN_AS(func_ov124_0229f460, HanPanel_Construct)
