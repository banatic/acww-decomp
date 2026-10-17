/* Overlay 129: the screen where a player draws a constellation of their own in the night sky
 * (overlay group 0x1a, opened by overlay 92's dispatch in GroupParams mode 0x2e; overlay 128,
 * mode 0x2d, is its sibling). Vtable 0x0229dc38, constructor StarDesigner_New (0x3160 bytes,
 * named by the profile at 0x0229db50).
 *
 * A menu scene (ov002/menu_scene.h) with an error message, the bottom panel (buttons 3 "yes",
 * 4 "no", 5 "quit" and 6 "done"), a pointer (a Glider), the sky's twinkling palettes
 * (main/star_palette.h) and overlay 127's telescope view (ov127/star_scope.h) on sub BG0
 * (the sky) and sub BG3 (the scope).
 *
 * The constellation being drawn is the one of GroupParams' argument (main/constellations.h):
 * its name and up to 16 pieces, the lines between two stars of the sky's table. A piece is
 * started from a star and every next piece must join the end of the line (`end_star`) to
 * another star; touching a drawn piece takes it off, as long as what is left stays joined.
 * Pieces of the other constellations may not be touched: no piece next to one of their stars
 * is offered.
 *
 * The scene is driven by a pen (sub states 0-2) or by the keys, either as a free pointer over
 * the sky (sub state 3) or as a cursor over the four arrows and the two buttons (sub state 4).
 * "Done" and "quit" ask a question on the panel (states 4-7) answered by "yes" (the
 * constellation saved, or the screen left) or "no" (back to the drawing, states 8-11). */
#ifndef CLEAN_OV129_STAR_DESIGNER_H
#define CLEAN_OV129_STAR_DESIGNER_H

#include "main/constellations.h"
#include "main/star_palette.h"
#include "ov002/button_panel.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov127/star_scope.h"
#include "types.h"

/* The pieces of the sky's table (StarScope_PieceStars). */
#define STAR_DESIGNER_PIECES 454
#define STAR_DESIGNER_NO_PIECE 0xffff
#define STAR_DESIGNER_NO_STAR 0xff

/* What each piece of the sky is to the constellation drawn (`piece_state`); its palette is
 * data_ov129_0229dae0's entry of the state. */
enum StarDesignerPieceState {
    STAR_DESIGNER_PIECE_FREE = 0,  /* palette 4 */
    STAR_DESIGNER_PIECE_TAKEN = 1, /* in another constellation (palette 7) */
    STAR_DESIGNER_PIECE_DRAWN = 2, /* in the constellation drawn (palette 6) */
    STAR_DESIGNER_PIECE_OPEN = 3   /* may be drawn next, from the end of the line (palette 5) */
};

/* How far the drawing is (`mode`). */
enum StarDesignerMode {
    STAR_DESIGNER_MODE_EMPTY = 0, /* no star picked */
    STAR_DESIGNER_MODE_FIRST = 1, /* a first star picked (`first_star`), no piece yet */
    STAR_DESIGNER_MODE_PIECES = 2 /* pieces drawn, the line ending at `end_star` */
};

/* What a touch of a star did (StarDesigner_TouchStar and the three by mode). */
enum StarDesignerTouch {
    STAR_DESIGNER_TOUCH_NONE = 0,
    STAR_DESIGNER_TOUCH_STAR = 1,   /* a star picked as the start or the end of the line */
    STAR_DESIGNER_TOUCH_PIECES = 2, /* a piece drawn or taken off */
    STAR_DESIGNER_TOUCH_ERROR = 3   /* no piece can start there: the error message is shown */
};

/* In `flags`. */
enum StarDesignerFlag {
    STAR_DESIGNER_FLAG_ARROWS = 0x01,    /* the scope's arrows drawn */
    STAR_DESIGNER_FLAG_FREE = 0x02,      /* the keys move a free pointer over the sky */
    STAR_DESIGNER_FLAG_QUITTING = 0x04,  /* the question asked is "quit" (else "done") */
    STAR_DESIGNER_FLAG_PANEL = 0x08,     /* the panel drawn */
    STAR_DESIGNER_FLAG_CENTRE = 0x10,    /* the scope's centre drawn */
    STAR_DESIGNER_FLAG_SCROLL_SE = 0x20, /* the scrolling sound plays */
    STAR_DESIGNER_FLAG_SCROLLED = 0x40,  /* the view was scrolled this frame */
    STAR_DESIGNER_FLAG_END_MARK = 0x80   /* the end of the line marked */
};

/* The places of the key cursor (`cursor`): the scope's four arrows (StarScopeArrow, drawn left,
 * right, bottom and top) and two buttons of the panel. */
enum StarDesignerCursor {
    STAR_DESIGNER_CURSOR_DONE = 4, /* the panel's button 6 */
    STAR_DESIGNER_CURSOR_QUIT = 5, /* the panel's button 5 */
    STAR_DESIGNER_CURSORS = 6
};

/* The panel's buttons (ButtonPanel). */
enum StarDesignerButton {
    STAR_DESIGNER_BUTTON_YES = 3,
    STAR_DESIGNER_BUTTON_NO = 4,
    STAR_DESIGNER_BUTTON_QUIT = 5,
    STAR_DESIGNER_BUTTON_DONE = 6
};

/* The answer chosen by the keys (`answer`). */
enum StarDesignerAnswer { STAR_DESIGNER_ANSWER_YES = 0, STAR_DESIGNER_ANSWER_NO = 1 };

/* The states (phase 1, StarDesigner_RunState). */
enum StarDesignerState {
    STAR_DESIGNER_STATE_OPEN = 0,          /* StarDesigner_StateOpen */
    STAR_DESIGNER_STATE_WIPE_IN = 1,       /* StarDesigner_StateWipeIn */
    STAR_DESIGNER_STATE_CLOSE = 2,         /* StarDesigner_StateClose */
    STAR_DESIGNER_STATE_WIPE_OUT = 3,      /* StarDesigner_StateWipeOut */
    STAR_DESIGNER_STATE_ASK_START = 4,     /* StarDesigner_StateAskStart */
    STAR_DESIGNER_STATE_ASK_WIPE_OUT = 5,  /* StarDesigner_StateAskWipeOut */
    STAR_DESIGNER_STATE_ASK_SHOW = 6,      /* StarDesigner_StateAskShow */
    STAR_DESIGNER_STATE_ASK_WIPE_IN = 7,   /* StarDesigner_StateAskWipeIn */
    STAR_DESIGNER_STATE_BACK_START = 8,    /* StarDesigner_StateBackStart */
    STAR_DESIGNER_STATE_BACK_WIPE_OUT = 9, /* StarDesigner_StateBackWipeOut */
    STAR_DESIGNER_STATE_BACK_SHOW = 10,    /* StarDesigner_StateBackShow */
    STAR_DESIGNER_STATE_BACK_WIPE_IN = 11, /* StarDesigner_StateBackWipeIn */
    STAR_DESIGNER_STATES = 12
};

/* The sub states (phase 2, StarDesigner_RunSubState). */
enum StarDesignerSubState {
    STAR_DESIGNER_SUB_TOUCH = 0,         /* StarDesigner_SubTouch */
    STAR_DESIGNER_SUB_ARROW_PEN = 1,     /* StarDesigner_SubArrowPen */
    STAR_DESIGNER_SUB_NUDGE_PEN = 2,     /* StarDesigner_SubNudgePen */
    STAR_DESIGNER_SUB_FREE = 3,          /* StarDesigner_SubFree */
    STAR_DESIGNER_SUB_CURSOR = 4,        /* StarDesigner_SubCursor */
    STAR_DESIGNER_SUB_ARROW_KEY = 5,     /* StarDesigner_SubArrowKey */
    STAR_DESIGNER_SUB_NUDGE_KEY = 6,     /* StarDesigner_SubNudgeKey */
    STAR_DESIGNER_SUB_GLIDE = 7,         /* StarDesigner_SubGlide */
    STAR_DESIGNER_SUB_PRESS = 8,         /* StarDesigner_SubPress */
    STAR_DESIGNER_SUB_RELEASE = 9,       /* StarDesigner_SubRelease */
    STAR_DESIGNER_SUB_BUTTON = 10,       /* StarDesigner_SubButton */
    STAR_DESIGNER_SUB_ANSWER_PEN = 11,   /* StarDesigner_SubAnswerPen */
    STAR_DESIGNER_SUB_ANSWER_KEYS = 12,  /* StarDesigner_SubAnswerKeys */
    STAR_DESIGNER_SUB_ANSWER_PRESS = 13, /* StarDesigner_SubAnswerPress */
    STAR_DESIGNER_SUB_ERROR = 14,        /* StarDesigner_SubError */
    STAR_DESIGNER_SUB_STATES = 15
};

/* The phases set (MenuScene_Update runs phase 0 by the vtable's slot 0x48, 1 by 0x4c, 2 by
 * 0x50 and 5 by 0x5c). */
enum StarDesignerPhase {
    STAR_DESIGNER_PHASE_WAIT = 0,        /* the base's MenuScene_Wait */
    STAR_DESIGNER_PHASE_STATES = 1,      /* StarDesigner_RunState */
    STAR_DESIGNER_PHASE_INTERACTIVE = 2, /* StarDesigner_RunInteractive */
    STAR_DESIGNER_PHASE_DELETE = 5       /* StarDesigner_RequestDelete */
};

typedef struct StarDesigner {
    MenuScene base;                       /* 0x0000 */
    s32 x;                                /* 0x0094: the free pointer's place */
    s32 y;                                /* 0x0098 */
    s32 arrows_offset;                    /* 0x009c: the wipe's offset the arrows follow */
    s32 panel_offset;                     /* 0x00a0: and the panel */
    u16 flags;                            /* 0x00a4: StarDesignerFlag */
    u16 hover_piece;                      /* 0x00a6: the piece painted as pointed at */
    u16 flash_piece;                      /* 0x00a8: the piece painted as touched */
    u16 piece;                            /* 0x00aa: the piece under the pointer */
    u8 return_sub_state;                  /* 0x00ac */
    u8 arrow;                             /* 0x00ad: the arrow held, StarScopeArrow */
    u8 cursor;                            /* 0x00ae: StarScopeArrow or StarDesignerCursor */
    u8 answer;                            /* 0x00af: StarDesignerAnswer */
    u8 star;                              /* 0x00b0: the star under the pointer */
    u8 mode;                              /* 0x00b1: StarDesignerMode */
    u8 first_star;                        /* 0x00b2 */
    u8 end_star;                          /* 0x00b3: the end of the line */
    u8 flash_timer;                       /* 0x00b4: frames left of `flash_piece` */
    u8 pad_b5[3];                         /* 0x00b5 */
    ErrorMessage error;                   /* 0x00b8 */
    ButtonPanel panel;                    /* 0x01d4 */
    Glider pointer;                       /* 0x03a0 */
    StarPalette palette;                  /* 0x0404 */
    StarScope scope;                      /* 0x0734 */
    u16 name[CONSTELLATIONS_NAME_LENGTH]; /* 0x2f6c: the constellation's */
    u16 pieces[CONSTELLATIONS_PIECES];    /* 0x2f78: STAR_DESIGNER_NO_PIECE when empty */
    u8 piece_state[STAR_DESIGNER_PIECES]; /* 0x2f98: StarDesignerPieceState */
    u8 pad_315e[2];                       /* 0x315e */
} StarDesigner;

/* star_designer.c: the scene */
StarDesigner *StarDesigner_Destroy(StarDesigner *self);
StarDesigner *StarDesigner_Delete(StarDesigner *self);
void StarDesigner_ClearFlags(StarDesigner *self, unsigned short mask);
void StarDesigner_SetFlags(StarDesigner *self, unsigned short mask);
int StarDesigner_TestFlags(StarDesigner *self, unsigned short mask);
void StarDesigner_SetUpLayers(void);
void StarDesigner_LoadLayers(StarDesigner *self);
void StarDesigner_EndFrame(StarDesigner *self);
void StarDesigner_BeginFrame(StarDesigner *self);
void StarDesigner_EndInteractive(StarDesigner *self);
void StarDesigner_BeginInteractive(StarDesigner *self);
void StarDesigner_Teardown(StarDesigner *self);
void StarDesigner_Setup(StarDesigner *self);
int StarDesigner_StartInput(StarDesigner *self);
unsigned char *StarDesigner_EnterAnswerKeys(StarDesigner *self);
unsigned char *StarDesigner_EnterAnswerPen(StarDesigner *self);
void StarDesigner_StateBackWipeIn(StarDesigner *self);
void StarDesigner_StateBackShow(StarDesigner *self);
void StarDesigner_StateBackWipeOut(StarDesigner *self);
void StarDesigner_StateBackStart(StarDesigner *self);
void StarDesigner_StateAskWipeIn(StarDesigner *self);
void StarDesigner_StateAskShow(StarDesigner *self);
void StarDesigner_StateAskWipeOut(StarDesigner *self);
void StarDesigner_StateAskStart(StarDesigner *self);
void StarDesigner_FollowWipeWindow(StarDesigner *self);
void StarDesigner_FollowWipe(StarDesigner *self);
void StarDesigner_StateWipeOut(StarDesigner *self);
void StarDesigner_StateClose(StarDesigner *self);
void StarDesigner_StateWipeIn(StarDesigner *self);
void StarDesigner_StateOpen(StarDesigner *self);
int StarDesigner_RequestDelete(StarDesigner *self);
int StarDesigner_Phase4(void);
int StarDesigner_Phase3(void);
int StarDesigner_RunInteractive(StarDesigner *self);
void StarDesigner_RunSubState(StarDesigner *self);
int StarDesigner_RunState(StarDesigner *self);
int StarDesigner_Draw(StarDesigner *self);
int StarDesigner_End(StarDesigner *self);
int StarDesigner_Start(StarDesigner *self);
StarDesigner *StarDesigner_New(void);

/* star_designer_pieces.c: the constellation drawn */
int StarDesigner_TouchStar(StarDesigner *self);
int StarDesigner_TouchInPieces(StarDesigner *self);
int StarDesigner_TouchFromFirst(StarDesigner *self);
void StarDesigner_MoveEndAlong(StarDesigner *self);
int StarDesigner_TouchFirst(StarDesigner *self);
int StarDesigner_TakeOffPiece(StarDesigner *self);
unsigned short StarDesigner_PieceBetween(StarDesigner *self, int star, unsigned char other);
int StarDesigner_CanStartAt(StarDesigner *self, unsigned int star);
int StarDesigner_HasDrawnPieceAt(StarDesigner *self, u32 star);
int StarDesigner_PieceSlot(StarDesigner *self, unsigned short piece);
int StarDesigner_FreeSlot(StarDesigner *self);
int StarDesigner_FindUnderPointer(StarDesigner *self, int x, int y);
void StarDesigner_OpenPiecesAt(StarDesigner *self, int star);
void StarDesigner_OpenPiece(StarDesigner *self, unsigned short piece, int star);
int StarDesigner_PieceNearTaken(StarDesigner *self, int piece, int star);
void StarDesigner_Refresh(StarDesigner *self, int with_open);
void StarDesigner_PaintAll(StarDesigner *self);
void StarDesigner_Paint(StarDesigner *self, int piece);
void StarDesigner_OpenFromEnd(StarDesigner *self);
void StarDesigner_MarkDrawn(StarDesigner *self);
void StarDesigner_LoadConstellation(StarDesigner *self);
void StarDesigner_MarkTaken(StarDesigner *self);
void StarDesigner_UnmarkDrawn(StarDesigner *self);
void StarDesigner_ClearPieceStates(StarDesigner *self);
void StarDesigner_StepFlash(StarDesigner *self);
void StarDesigner_Flash(StarDesigner *self);
void StarDesigner_Unflash(StarDesigner *self);
void StarDesigner_Hover(StarDesigner *self);
void StarDesigner_Unhover(StarDesigner *self);

/* star_designer_input.c: the pointer, the cursor and the sub states */
void StarDesigner_ReleasePointer(StarDesigner *self);
void StarDesigner_PressPointer(StarDesigner *self);
void StarDesigner_ShowPointer(StarDesigner *self);
void StarDesigner_GlidePointer(StarDesigner *self, int x, int y);
void StarDesigner_GlideToCursor(StarDesigner *self);
void StarDesigner_HidePointer(StarDesigner *self);
int StarDesigner_CursorY(StarDesigner *self);
int StarDesigner_CursorX(StarDesigner *self);
void StarDesigner_PlacePointer(StarDesigner *self);
int StarDesigner_IsPointerSetB(StarDesigner *self);
int StarDesigner_IsPointerSetA(StarDesigner *self);
int StarDesigner_MoveCursor(StarDesigner *self, u32 keys);
void StarDesigner_ShowError(StarDesigner *self, char message);
void StarDesigner_AnswerNo(StarDesigner *self);
void StarDesigner_AnswerYes(StarDesigner *self);
void StarDesigner_PressQuit(StarDesigner *self);
void StarDesigner_PressDone(StarDesigner *self);
void StarDesigner_EnterDrawing(StarDesigner *self);
void StarDesigner_EnterKeys(StarDesigner *self);
void StarDesigner_EnterPen(StarDesigner *self);
void StarDesigner_SubError(StarDesigner *self);
void StarDesigner_SubAnswerPress(StarDesigner *self);
void StarDesigner_SubAnswerKeys(StarDesigner *self);
void StarDesigner_SubAnswerPen(StarDesigner *self);
void StarDesigner_SubButton(StarDesigner *self);
void StarDesigner_SubRelease(StarDesigner *self);
void StarDesigner_SubPress(StarDesigner *self);
void StarDesigner_SubGlide(StarDesigner *self);
void StarDesigner_SubNudgeKey(StarDesigner *self);
void StarDesigner_SubArrowKey(StarDesigner *self);
void StarDesigner_SubCursor(StarDesigner *self);
void StarDesigner_SubFree(StarDesigner *self);
void StarDesigner_SubNudgePen(StarDesigner *self);
void StarDesigner_SubArrowPen(StarDesigner *self);
void StarDesigner_SubTouch(StarDesigner *self);

#endif
