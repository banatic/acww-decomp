/* Overlay 127: the telescope's view of the night sky ("menu/star/b_scp_*"), shared by the
 * constellation screens of overlays 128 (its object at 0x4a4) and 129 (at 0x734), and the judge
 * main's Constellations_Add loads it for (StarScope_StarsAreFree).
 *
 * The sky is main's map of 64 x 32 tiles (main/constellations.h), with its own tables here: the
 * sky's 164 stars by column and row, each piece (a line of a constellation) by its two stars, and
 * for each tile of the map whether a star or a piece is drawn there (STAR_SCOPE_KIND_*).
 *
 * The object is a layer load task of main's (main/layer_load_task.h) followed by the sky as
 * loaded and painted, the copy queued to the sky's layer (with the rows past the sky's top or
 * bottom blanked), the scope's own screen and the view: its scroll (x round 0x200, y from -24 to
 * 84), a bounce of the view's edge, a target the view glides to and the four arrows that
 * scroll it (STAR_SCOPE_ARROW_*). */
#ifndef CLEAN_OV127_STAR_SCOPE_H
#define CLEAN_OV127_STAR_SCOPE_H

#include "main/constellations.h"
#include "main/layer_load_task.h"
#include "types.h"

#define STAR_SCOPE_SKY_TILES 0x800
#define STAR_SCOPE_SCREEN_TILES 0x400
#define STAR_SCOPE_COLUMNS 64
#define STAR_SCOPE_ROWS 32
/* The stars of a constellation, at most (StarScope_CollectStars): the list ends with 0xff. */
#define STAR_SCOPE_STAR_LIST 0x11
#define STAR_SCOPE_NO_STAR 0xff

/* In `flags`. */
enum StarScopeFlag {
    STAR_SCOPE_FLAG_SCROLLED = 0x01, /* the layer's scroll and the rows blanked are to be updated */
    STAR_SCOPE_FLAG_PAINTED = 0x02,  /* the sky is to be copied and queued to its layer */
    STAR_SCOPE_FLAG_GLIDING = 0x04,  /* the view glides to its target (StarScope_StepGlide) */
    STAR_SCOPE_FLAG_SCROLL_SE = 0x08 /* the scrolling sound (0x883) plays */
};

/* The arrows, as they are drawn round the screen's middle and scroll the view. */
enum StarScopeArrow {
    STAR_SCOPE_ARROW_LEFT = 0,  /* x down */
    STAR_SCOPE_ARROW_RIGHT = 1, /* x up */
    STAR_SCOPE_ARROW_UP = 2,    /* y up */
    STAR_SCOPE_ARROW_DOWN = 3,  /* y down */
    STAR_SCOPE_ARROWS = 4       /* none (StarScope_ArrowAt, `pressed`) */
};

/* What a tile of the sky draws (the top four bits of the tiles' table). */
enum StarScopeKind {
    STAR_SCOPE_KIND_STAR = 1, /* the low twelve bits are the star */
    STAR_SCOPE_KIND_PIECE = 2 /* ... the piece */
};

typedef struct StarScope {
    LayerTask task;                     /* 0x0000: queues `shown` to the sky's layer */
    u16 sky[STAR_SCOPE_SKY_TILES];      /* 0x0024: "menu/star/bg.bsc", the constellations painted */
    u16 shown[STAR_SCOPE_SKY_TILES];    /* 0x1024: the sky with the rows past its edge blanked */
    u16 scope[STAR_SCOPE_SCREEN_TILES]; /* 0x2024: "menu/star/b_scp_bg.bsc" */
    s16 scroll_x;                       /* 0x2824: 0-0x1ff */
    s16 scroll_y;                       /* 0x2826: -24-84 */
    s16 bounce;                         /* 0x2828: the edge's bounce, -68-76 */
    s16 target_x;                       /* 0x282a */
    s16 target_y;                       /* 0x282c */
    s16 hidden_rows;                    /* 0x282e: rows blanked, at the top (above 0) or bottom */
    u16 flags;                          /* 0x2830: StarScopeFlag */
    u8 sky_layer;                       /* 0x2832 */
    u8 scope_layer;                     /* 0x2833 */
    u8 pressed;                         /* 0x2834: the arrow drawn pressed, StarScopeArrow */
    u8 nudge_arrow;                     /* 0x2835: the arrow of the nudge in progress */
    u8 nudge_steps;                     /* 0x2836: its steps left (StarScope_StepNudge) */
    u8 pad_2837;
} StarScope;

int StarScope_StarsAreFree(Constellation *draft);
void StarScope_CollectStars(const Constellation *constellation, u8 *stars);
int StarScope_ConstellationOfPiece(int piece);
const u8 *StarScope_PieceStars(int piece);
u8 StarScope_StarRow(u8 star);
u8 StarScope_StarColumn(unsigned int star);
int StarScope_PiecesAround(u16 *pieces, int column, int row);
int StarScope_PieceAt(unsigned int index);
int StarScope_PieceAtCell(int column, int row);
int StarScope_StarAt(unsigned int index);
int StarScope_StarAtCell(int column, int row);
void StarScope_ClearFlags(StarScope *scope, u16 flags);
void StarScope_SetFlags(StarScope *scope, u16 flags);
int StarScope_TestFlags(StarScope *scope, unsigned int flags);
s16 StarScope_ScrollY(StarScope *scope);
int StarScope_ScrollX(StarScope *scope);
int StarScope_Bounce(StarScope *scope);
void StarScope_StepGlide(StarScope *scope);
void StarScope_GlideTo(StarScope *scope, int x, int y);
void StarScope_PaintPiece(StarScope *scope, int piece, int palette);
int StarScope_SkyCellInLens(StarScope *scope, int x, int y, int *column, int *row);
int StarScope_SkyCellAt(StarScope *scope, int x, int y, int *column, int *row);
void StarScope_LookAt(StarScope *scope, int x, int y);
int StarScope_ScrollVertically(StarScope *scope, int amount, int bounce);
void StarScope_ScrollHorizontally(StarScope *scope, int amount);
int StarScope_StepNudge(StarScope *scope);
void StarScope_Nudge(StarScope *scope, int arrow);
void StarScope_HoldArrow(StarScope *scope, int arrow, int bounce);
void StarScope_ScrollByArrow(StarScope *scope, unsigned int arrow, int amount, int bounce);
int StarScope_ArrowAt(StarScope *scope, int x, int y);
int StarScope_DrawStarMark(StarScope *scope, int star);
void StarScope_DrawCentre(StarScope *scope, int y);
void StarScope_DrawArrows(StarScope *scope, int spread, int palette);
void StarScope_EndTask(StarScope *scope);
void StarScope_Update(StarScope *scope);
void StarScope_LoadObjGraphics(StarScope *scope);
void StarScope_LoadScopeLayer(StarScope *scope, u8 layer, int unused);
void StarScope_LoadSkyLayer(StarScope *scope, u8 layer);
void StarScope_Reset(StarScope *scope);
void StarScope_Destruct(StarScope *scope);
StarScope *StarScope_Construct(StarScope *scope);

#endif
