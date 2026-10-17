/* The scene of overlay 123 (vtable 0x0229d024, include/cpp/ov123/Obj_ov123_0229d024.h; constructor
 * DesignEditor_New, 0x51fc bytes): the design editor, a menu scene (ov002/menu_scene.h) that
 * edits one 32x32 design of 16-colour pixels (main/design.h) on the touch screen, as the evidence
 * says:
 *
 * - overlay 92's dispatcher opens it (as overlay group 0x0d) for its modes 2 and 3
 *   (ov092/menu_dispatch.c), and GroupParams_Mode says which design it edits: mode 2 the current
 *   player's design at GroupParams_Arg's place in their order (DesignEditor_LoadPlayerDesign,
 *   DesignEditor_SavePlayerDesign), mode 3 the design of the town's statistics record
 *   (main/wfc_stats.h; DesignEditor_LoadTownDesign, DesignEditor_SaveTownDesign);
 * - its look is "menu/edit/...": bg.bpl, bg0.bch, bg1.bch, a.bsc, b.bsc, c.bsc, obj.bpl,
 *   obj0.bch and obj1.bch;
 * - the canvas is the design shown four times bigger at (0x40, 8) of the touch screen
 *   (0x80 x 0x80 pixels), drawn as characters of layer 6 (DesignEditor_ZoomPixels);
 * - beside it are the tools (DesignEditorTool), a palette button, a button for layer 3
 *   (DesignEditor_ToggleLayer3) and the row of the palette's fifteen colours; the pen picks
 *   them, and the d-pad walks them with a cursor sprite (`key_place`, DesignEditorPlace);
 * - the drawing keeps two copies of the pixels: a stroke first copies the current one to the
 *   other and draws on that (DesignEditor_Snapshot), so tool 5 swaps back to the copy before
 *   the stroke and again (DesignEditor_Undo).
 *
 * The panel's save and quit buttons ask a question (states 6-8); its "yes" (command 0x1f) ends
 * the editor, saving the design unless the quit button asked (flag 0x08), and its "no" goes back
 * to editing (states 9-0x0b). A player design worn as clothes or a hat (item codes 0x12a8-0x12af and
 * 0x1429-0x1430) has the player put it on again after the editor closes. */
#ifndef CLEAN_OV123_DESIGN_EDITOR_H
#define CLEAN_OV123_DESIGN_EDITOR_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/button_panel.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "types.h"

#define DESIGN_EDITOR_SIZE 32    /* the design's width and height in pixels */
#define DESIGN_EDITOR_WORDS 0x80 /* its pixels in words: four 8-pixel words a row */

/* In `flags`. */
enum DesignEditorFlag {
    DESIGN_EDITOR_FLAG_DRAWN = 0x01,            /* the scene's draw runs (DesignEditor_Draw) */
    DESIGN_EDITOR_FLAG_QUIT = 0x08,             /* the panel's quit choice is taken: the design is not saved */
    DESIGN_EDITOR_FLAG_SCREEN_DIRTY = 0x10,     /* the screen map at `screen` is to be loaded (DesignEditor_QueueScreen) */
    DESIGN_EDITOR_FLAG_LAYER3 = 0x20,           /* layer 3 is shown, blended (DesignEditor_ShowLayer3) */
    DESIGN_EDITOR_FLAG_DIRTY = 0x40,            /* the pixels changed: their characters are rebuilt (DesignEditor_Refresh) */
    DESIGN_EDITOR_FLAG_FIRST_COPY = 0x80,       /* the current pixels are pixels[0], else pixels[1] */
    DESIGN_EDITOR_FLAG_SHAPE = 0x100,           /* a line, rectangle or ellipse is being dragged out */
    DESIGN_EDITOR_FLAG_PLACE_AT_ONCE = 0x200,   /* the cursor sprite jumps to its place, once */
    DESIGN_EDITOR_FLAG_DIM_LATER = 0x400,       /* the screen is dimmed once the layers have slid up for the question */
    DESIGN_EDITOR_FLAG_PICKING = 0x800,         /* the colour under the key cursor is being picked (B held) */
    DESIGN_EDITOR_FLAG_STROKE = 0x1000,         /* the pen is drawing on the canvas */
    DESIGN_EDITOR_FLAG_PRESSED = 0x2000,        /* the button under the pen was pressed; not again until it moves */
    DESIGN_EDITOR_FLAG_UNDONE = 0x4000,         /* the last stroke was undone (the next undo redoes it) */
    DESIGN_EDITOR_FLAG_WORN_CLOTHES = 0x8000,   /* the saved design is the player's clothes */
    DESIGN_EDITOR_FLAG_WORN_HAT = 0x10000,      /* the saved design is the player's hat */
    DESIGN_EDITOR_FLAG_LAYER3_DIMMED = 0x20000, /* the dimming hid layer 3: shown again after the question */
    DESIGN_EDITOR_FLAG_KEY_SOUND = 0x40000,     /* sound 0x863 runs while A draws */
    DESIGN_EDITOR_FLAG_PEN_SOUND = 0x80000,     /* sound 0x862 runs while the pen draws */
    DESIGN_EDITOR_FLAG_PEN_MOVED = 0x100000     /* the pen moved this frame */
};

/* The tools (`tool`; DesignEditor_UseTool draws with them). */
enum DesignEditorTool {
    DESIGN_EDITOR_TOOL_PEN_1 = 0,   /* one pixel */
    DESIGN_EDITOR_TOOL_PEN_2 = 1,   /* 2x2 pixels, up and left */
    DESIGN_EDITOR_TOOL_PEN_3 = 2,   /* 3x3 pixels around */
    DESIGN_EDITOR_TOOL_STAMP_0 = 3, /* a 16x16 one-bit stamp (data_ov123_0229ca14) */
    DESIGN_EDITOR_TOOL_STAMP_1 = 4, /* another (data_ov123_0229ca34) */
    DESIGN_EDITOR_TOOL_UNDO = 5,    /* a button, not a tool (DesignEditor_Undo) */
    DESIGN_EDITOR_TOOL_RECTANGLE = 6,
    DESIGN_EDITOR_TOOL_ELLIPSE = 7,
    DESIGN_EDITOR_TOOL_LINE = 8,
    DESIGN_EDITOR_TOOL_FILL = 9,     /* a flood fill */
    DESIGN_EDITOR_TOOL_PATTERN = 10, /* the whole design painted through a one-bit pattern */
    DESIGN_EDITOR_TOOL_CLEAR = 11,   /* the whole design one colour */
    DESIGN_EDITOR_TOOL_DOTS = 3,     /* in DesignEditor_PaintBrush: the shape's preview dots */
    DESIGN_EDITOR_NO_TOOL = 0x22
};

/* What a place under the pen or the key cursor stands for (`command`, `hover`, `key_place`):
 * the tools 0-0x0b (DesignEditorTool), then: */
enum DesignEditorPlace {
    DESIGN_EDITOR_PLACE_PALETTE = 0x0c,  /* the next palette */
    DESIGN_EDITOR_PLACE_LAYER3 = 0x0d,   /* layer 3 shown or hidden */
    DESIGN_EDITOR_PLACE_COLOUR_1 = 0x0e, /* 0x0e-0x1c: the colours 1-15 */
    DESIGN_EDITOR_PLACE_COLOUR_15 = 0x1c,
    DESIGN_EDITOR_PLACE_SAVE = 0x1d,   /* the panel's button 9: save */
    DESIGN_EDITOR_PLACE_QUIT = 0x1e,   /* the panel's button 8: quit without saving */
    DESIGN_EDITOR_PLACE_DONE = 0x1f,   /* the question's "yes" (button 3): the editor ends */
    DESIGN_EDITOR_PLACE_CHOICE = 0x20, /* the question's "no" (button 4): back to editing */
    DESIGN_EDITOR_PLACE_CANVAS = 0x21,
    DESIGN_EDITOR_NO_PLACE = 0x22
};

/* Which part the d-pad walks (`key_mode`). */
enum DesignEditorKeyMode {
    DESIGN_EDITOR_KEYS_PLACES = 0,  /* the tools, buttons and colours */
    DESIGN_EDITOR_KEYS_COLOURS = 1, /* the colours, from the canvas's Y */
    DESIGN_EDITOR_KEYS_CANVAS = 2   /* a cursor on the canvas's pixels */
};

/* The sub states, run from the table of DesignEditor_RunSubState (MenuScene_SetSubState). */
enum DesignEditorSubState {
    DESIGN_EDITOR_SUB_TOUCH = 0x00,       /* DesignEditor_IdleByTouch */
    DESIGN_EDITOR_SUB_TOUCH_PANEL = 0x01, /* DesignEditor_PanelByTouch */
    DESIGN_EDITOR_SUB_DRAW = 0x02,        /* DesignEditor_DrawByTouch */
    DESIGN_EDITOR_SUB_PLACES = 0x03,      /* DesignEditor_PlacesByKeys */
    DESIGN_EDITOR_SUB_CANVAS = 0x04,      /* DesignEditor_CanvasByKeys */
    DESIGN_EDITOR_SUB_KEY_DRAW = 0x05,    /* DesignEditor_DrawByKeys */
    DESIGN_EDITOR_SUB_KEY_SHAPE = 0x06,   /* DesignEditor_ShapeByKeys */
    DESIGN_EDITOR_SUB_PICK = 0x07,        /* DesignEditor_PickByKeys */
    DESIGN_EDITOR_SUB_PANEL = 0x08,       /* DesignEditor_PanelByKeys */
    DESIGN_EDITOR_SUB_SPRITE_MOVE = 0x09, /* DesignEditor_WaitCursorSprite */
    DESIGN_EDITOR_SUB_PRESS = 0x0a,       /* DesignEditor_PressAtCursor */
    DESIGN_EDITOR_SUB_PRESS_END = 0x0b,   /* DesignEditor_FinishPress */
    DESIGN_EDITOR_SUB_PANEL_PRESS = 0x0c, /* DesignEditor_WaitPanelPress */
    DESIGN_EDITOR_SUB_STATES = 0x0d
};

/* The states, run from the table of DesignEditor_RunState (MenuScene_SetState). States 6-8 ask
 * the panel's question (save, or quit without saving) and 9-0x0b go back to editing. */
enum DesignEditorState {
    DESIGN_EDITOR_STATE_SETUP = 0x00,                 /* DesignEditor_StartSetup */
    DESIGN_EDITOR_STATE_WIPE_IN = 0x01,               /* DesignEditor_WipeIn */
    DESIGN_EDITOR_STATE_DONE = 0x02,                  /* DesignEditor_FinishEditing */
    DESIGN_EDITOR_STATE_WAIT_PLAYER = 0x03,           /* DesignEditor_WaitPlayer */
    DESIGN_EDITOR_STATE_START_WIPE_OUT = 0x04,        /* DesignEditor_StartWipeOut */
    DESIGN_EDITOR_STATE_WIPE_OUT = 0x05,              /* DesignEditor_WipeOut */
    DESIGN_EDITOR_STATE_START_QUESTION = 0x06,        /* DesignEditor_StartQuestion */
    DESIGN_EDITOR_STATE_QUESTION_WIPE_OUT = 0x07,     /* DesignEditor_QuestionWipeOut */
    DESIGN_EDITOR_STATE_QUESTION_WIPE_IN = 0x08,      /* DesignEditor_QuestionWipeIn */
    DESIGN_EDITOR_STATE_START_END_QUESTION = 0x09,    /* DesignEditor_StartEndQuestion */
    DESIGN_EDITOR_STATE_END_QUESTION_WIPE_OUT = 0x0a, /* DesignEditor_EndQuestionWipeOut */
    DESIGN_EDITOR_STATE_END_QUESTION_WIPE_IN = 0x0b,  /* DesignEditor_EndQuestionWipeIn */
    DESIGN_EDITOR_STATES = 0x0c
};

/* The phases set (MenuScene.phase; menu_scene.c's MenuScene_Update runs phase 0 by the vtable's
 * slot 0x48, 1 by 0x4c, 2 by 0x50 and 5 by 0x5c, as ov092/menu_dispatch.h says). */
enum DesignEditorPhase {
    DESIGN_EDITOR_PHASE_WAIT = 0,        /* the base's wait */
    DESIGN_EDITOR_PHASE_STATES = 1,      /* DesignEditor_RunState */
    DESIGN_EDITOR_PHASE_INTERACTIVE = 2, /* DesignEditor_RunInteractive */
    DESIGN_EDITOR_PHASE_END = 5          /* DesignEditor_End */
};

#define DESIGN_EDITOR_TASKS 3

typedef struct DesignEditor {
    MenuScene base;                             /* 0x0000 */
    s32 wipe_y;                                 /* 0x0094: MenuScene_WipeOffsetY's, when the layers were scrolled */
    s32 slide;                                  /* 0x0098: the layers' offset, 0-0x10 (DesignEditor_ScrollLayers) */
    u32 flags;                                  /* 0x009c: DesignEditorFlag */
    u8 return_sub_state;                        /* 0x00a0: the sub state after the cursor sprite stops */
    u8 palette;                                 /* 0x00a1: the design's palette, 0-15 */
    u8 colour;                                  /* 0x00a2: the colour drawn, 1-15 */
    u8 colour_x;                                /* 0x00a3: (colour - 1) * 12, the colour marker's x */
    u8 tool;                                    /* 0x00a4: DesignEditorTool */
    u8 command;                                 /* 0x00a5: the place pressed (DesignEditor_RunCommand) */
    u8 lit_place;                               /* 0x00a6: the place shown lit (DesignEditor_LightPlace) */
    u8 lit_frames;                              /* 0x00a7: the frames it stays lit */
    u8 pen_px;                                  /* 0x00a8: the canvas pixel under the pen (or the key cursor's) */
    u8 pen_py;                                  /* 0x00a9 */
    u8 key_place;                               /* 0x00aa: the key cursor's place (DesignEditorPlace) */
    u8 saved_place;                             /* 0x00ab: the place to go back to from the canvas */
    u8 key_mode;                                /* 0x00ac: DesignEditorKeyMode */
    u8 start_px;                                /* 0x00ad: where the stroke or shape started */
    u8 start_py;                                /* 0x00ae */
    u8 cursor_px;                               /* 0x00af: the key cursor's pixel */
    u8 cursor_py;                               /* 0x00b0 */
    u8 hover_frames;                            /* 0x00b1: the frames the pen stayed on `hover` */
    u8 hover;                                   /* 0x00b2: the place under the pen */
    u8 key_delay;                               /* 0x00b3: the frames before a held d-pad moves the cursor again */
    u8 pen_x;                                   /* 0x00b4: the pen's point last frame */
    u8 pen_y;                                   /* 0x00b5 */
    u8 pad_b6[2];                               /* 0x00b6 */
    TextLabel label;                            /* 0x00b8: the palette's number */
    LayerTaskPair tasks[DESIGN_EDITOR_TASKS];   /* 0x0124: the palette and canvas characters, the
                                                 * zoomed characters, the screen map */
    Glider cursor_sprite;                       /* 0x01cc: a Glider0 */
    u16 screen[0x400];                          /* 0x0230: "menu/edit/a.bsc", the places lit in it */
    u32 pixels[2][DESIGN_EDITOR_WORDS];         /* 0x0a30: the two copies of the design's pixels */
    u32 zoomed[DESIGN_EDITOR_WORDS * 16];       /* 0x0e30: the pixels four times bigger, 128x128 */
    u32 chars[DESIGN_EDITOR_WORDS];             /* 0x2e30: the pixels as 4x4 characters */
    u32 zoomed_chars[DESIGN_EDITOR_WORDS * 16]; /* 0x3030: the zoomed pixels as 16x16 characters */
    ButtonPanel panel;                          /* 0x5030 */
} DesignEditor;

DesignEditor *DesignEditor_Destroy(DesignEditor *self);
DesignEditor *DesignEditor_Delete(DesignEditor *self);
void DesignEditor_ClearFlags(DesignEditor *self, unsigned int flags);
void DesignEditor_SetFlags(DesignEditor *self, unsigned int flags);
int DesignEditor_TestFlags(DesignEditor *self, int flags);
void DesignEditor_Undim(DesignEditor *self);
void DesignEditor_Dim(DesignEditor *self);
void DesignEditor_HideLayer3(DesignEditor *self);
void DesignEditor_ShowLayer3(DesignEditor *self);
void DesignEditor_ToggleLayer3(DesignEditor *self);
u32 *DesignEditor_Pixels(DesignEditor *self);
void DesignEditor_Undo(DesignEditor *self);
void DesignEditor_Snapshot(DesignEditor *self);
void DesignEditor_EndLayerTasks(DesignEditor *self);
void DesignEditor_EndShape(DesignEditor *self);
void DesignEditor_StartShape(DesignEditor *self);
void DesignEditor_DrawShapePreview(DesignEditor *self);
int DesignEditor_DrawMarker(DesignEditor *self, int px, int py);
void DesignEditor_DrawToolCursor(DesignEditor *self, int px, int py);
void DesignEditor_DrawPreviewDot(DesignEditor *self, int px, int py);
void DesignEditor_DrawShapeCorner(DesignEditor *self, int px, int py, int corner);
void DesignEditor_CloseLabel(DesignEditor *self);
void DesignEditor_StepLitPlace(DesignEditor *self);
void DesignEditor_UnlightPlace(DesignEditor *self);
void DesignEditor_LightPlace(DesignEditor *self, unsigned char place);
void DesignEditor_SelectTool(DesignEditor *self, unsigned char tool);
void DesignEditor_QueueScreen(DesignEditor *self);
void DesignEditor_SetPlacePalette(DesignEditor *self, unsigned int place, unsigned int palette);
void DesignEditor_SetPalette(DesignEditor *self, int palette);
void DesignEditor_SetColour(DesignEditor *self, unsigned char colour);
int DesignEditor_QueuePalette(DesignEditor *self);
void DesignEditor_Refresh(DesignEditor *self);
void DesignEditor_QueueZoomedChars(DesignEditor *self);
void DesignEditor_LoadZoomedChars(DesignEditor *self);
void DesignEditor_QueueChars(DesignEditor *self);
int DesignEditor_LoadChars(DesignEditor *self);
void DesignEditor_SaveTownDesign(DesignEditor *self);
void DesignEditor_LoadTownDesign(DesignEditor *self);
void DesignEditor_SavePlayerDesign(DesignEditor *self);
void DesignEditor_LoadPlayerDesign(DesignEditor *self);
void DesignEditor_LoadObjects(DesignEditor *self);
void DesignEditor_LoadLayers(DesignEditor *self);
void DesignEditor_SetUpLayers(void);
void DesignEditor_EndFrame(DesignEditor *self);
void DesignEditor_BeginFrame(DesignEditor *self);
void DesignEditor_EndInteractiveFrame(DesignEditor *self);
void DesignEditor_BeginInteractiveFrame(DesignEditor *self);
void DesignEditor_Teardown(DesignEditor *self);
void DesignEditor_Reset(DesignEditor *self);
void DesignEditor_ScrollLayers(DesignEditor *self);
void DesignEditor_ScrollWithWipe(DesignEditor *self);
void DesignEditor_EndQuestionWipeIn(DesignEditor *self);
void DesignEditor_EndQuestionWipeOut(DesignEditor *self);
void DesignEditor_StartEndQuestion(DesignEditor *self);
void DesignEditor_QuestionWipeIn(DesignEditor *self);
void DesignEditor_QuestionWipeOut(DesignEditor *self);
void DesignEditor_StartQuestion(DesignEditor *self);
void DesignEditor_WipeOut(DesignEditor *self);
void DesignEditor_StartWipeOut(DesignEditor *self);
void DesignEditor_WaitPlayer(DesignEditor *self);
void DesignEditor_FinishEditing(DesignEditor *self);
void DesignEditor_WipeIn(DesignEditor *self);
void DesignEditor_StartSetup(DesignEditor *self);
int DesignEditor_End(DesignEditor *self);
int DesignEditor_Phase4Idle(void);
int DesignEditor_Phase3Idle(void);
int DesignEditor_RunInteractive(DesignEditor *self);
void DesignEditor_RunSubState(DesignEditor *self);
int DesignEditor_RunState(DesignEditor *self);
int DesignEditor_Draw(DesignEditor *self);
int DesignEditor_Close(DesignEditor *self);
int DesignEditor_Start(DesignEditor *self);
DesignEditor *DesignEditor_New(void);

#endif
