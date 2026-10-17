/* Overlay 124's object, kept by the scenes of overlays 125 (at 0x94) and 126 (at 0xb0), which
 * ov092's dispatch loads with it for its modes 0x04-0x0a (overlay group 0x0e: overlays 124 and
 * 125) and 0x0b-0x17 (group 0x0f: overlays 124, 126 and 095), as ov092/menu_dispatch.c lists.
 * Its files are those under "menu/han/"; what the screens show is not known, so the object is
 * named after that folder.
 *
 * It holds a text label (an array of one, built by __cxa_vec_ctor) and a sign: a panel sprite
 * (ov002/panel_sprite.h) showing a message of "2d_menu" chosen by the mode, drawn with a few
 * OBJs of its own. By the mode (GroupParams_Mode) it also picks:
 *
 * - `kind`: the background ("menu/han/bg%d.bch", its palette in "menu/han/ten0_bg.bpl") and the
 *   sign's characters (five kinds a file, "menu/han/obj0.bch" to "obj3.bch", with the palette of
 *   "menu/han/ten0_obj.bpl");
 * - the text's style (HanPanel_TextStyle), which places and opens the label's box. */
#ifndef CLEAN_OV124_HAN_PANEL_H
#define CLEAN_OV124_HAN_PANEL_H

#include "clean.h"
#include "main/text_label.h"
#include "ov002/panel_sprite.h"
#include "types.h"

typedef struct HanPanel {
    TextLabel label;  /* 0x00: an array of one (HanPanel_Construct) */
    PanelSprite sign; /* 0x6c */
    u8 kind;          /* 0xe8: the background and the sign's characters, by the mode */
    u8 palette;       /* 0xe9: the OBJ palette the sign's own OBJs are drawn in */
    u8 pad_ea[2];
} HanPanel;

static_assert(offsetof(HanPanel, sign) == 0x6c && offsetof(HanPanel, kind) == 0xe8, "members");
static_assert(sizeof(HanPanel) == 0xec, "size (ov125's next member at 0x180)");

/* What HanPanel_TextStyle answers. */
enum HanPanelStyle {
    HAN_PANEL_STYLE_0 = 0, /* most modes */
    HAN_PANEL_STYLE_1 = 1, /* modes 0x0f-0x12 and 0x18-0x1b */
    HAN_PANEL_STYLE_3 = 3  /* mode 0x15 */
};

void HanPanel_CloseTexts(HanPanel *self);
void HanPanel_DrawWithSign(HanPanel *self, int x, int y);
void HanPanel_DrawBase(HanPanel *self, int x, int y);
void HanPanel_LoadSign(HanPanel *self, int palette);
int HanPanel_LoadBackground(HanPanel *self, int layer, int screen);
int HanPanel_TextStyle(HanPanel *self);
void HanPanel_SetTextBoxParams(HanPanel *self, int a, int b, int c, int d);
void HanPanel_SetTextFromWide(HanPanel *self, const u16 *text, void *length);
void HanPanel_ShowText(HanPanel *self);
void HanPanel_OpenTextBox(HanPanel *self);
int HanPanel_LoadStyledBackground(HanPanel *self, int layer);
void HanPanel_ShowModeMessage(HanPanel *self, int layer, int second_layer);
HanPanel *HanPanel_Destroy(HanPanel *self);
HanPanel *HanPanel_Construct(HanPanel *self);

#endif
