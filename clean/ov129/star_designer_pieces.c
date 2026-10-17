/* The constellation drawn on overlay 129's screen (star_designer.h): the stars and pieces under
 * the pointer, what a touch of a star does by how far the drawing is, the state of each piece
 * of the sky and its palette, and the pieces painted as pointed at or touched. */
#include "star_designer.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "main/constellations.h"
#include "main/group_params.h"
#include "main/sound.h"
#include "ov002/button_panel.h"
#include "ov127/star_scope.h"

/* The pieces round a star (StarScope_PiecesAround), at most. */
#define STAR_DESIGNER_AROUND 10

/* The sounds (SoundSys_PlaySe). */
#define STAR_DESIGNER_SE_STAR 0x880  /* a star picked */
#define STAR_DESIGNER_SE_DRAWN 0x881 /* a piece drawn */
#define STAR_DESIGNER_SE_TAKEN 0x882 /* a piece taken off */

/* The palettes a piece is painted in apart from its state's. */
#define STAR_DESIGNER_PALETTE_FLASH 10       /* touched */
#define STAR_DESIGNER_PALETTE_HOVER_DRAWN 11 /* pointed at, drawn: it would be taken off */
#define STAR_DESIGNER_PALETTE_HOVER_OPEN 8   /* pointed at, open: it would be drawn */
#define STAR_DESIGNER_FLASH_FRAMES 5

/* The error message when no piece can start from the star touched. */
#define STAR_DESIGNER_MESSAGE_NO_START 0x16

/* The palette of each piece state (StarDesignerPieceState). */
extern const u8 data_ov129_0229dae0[4];
/* The five points round the pointer looked at for a star or a piece: x and y offsets. */
extern const s32 data_ov129_0229db04[5];
extern const s32 data_ov129_0229db18[5];

/* The pieces round a star, by its column and row. */
static int star_designer_pieces_around(u16 *pieces, unsigned int star)
{
    int column = StarScope_StarColumn(star);
    int row = StarScope_StarRow((u8) star);
    return StarScope_PiecesAround(pieces, column, row);
}

/* A slot of the constellation's pieces.
 * QUIRK: slot -1 (no slot) is the halfword before the pieces, the name's last character. */
static u16 *star_designer_slot(StarDesigner *self, int slot)
{
    return (u16 *) (void *) ((u8 *) self + offsetof(StarDesigner, pieces) + 2 * slot);
}

/* func_ov129_0229b800: a touch (or A) on the star under the pointer, by the mode; a star picked
 * is heard, and after a star picked or a piece changed the pieces' states are made again with
 * the open ones and painted. */
int StarDesigner_TouchStar(StarDesigner *self)
{
    int result = STAR_DESIGNER_TOUCH_NONE;

    switch (self->mode) {
        case STAR_DESIGNER_MODE_EMPTY:
            result = StarDesigner_TouchFirst(self);
            break;
        case STAR_DESIGNER_MODE_FIRST:
            result = StarDesigner_TouchFromFirst(self);
            break;
        case STAR_DESIGNER_MODE_PIECES:
            result = StarDesigner_TouchInPieces(self);
            break;
    }
    if (result == STAR_DESIGNER_TOUCH_STAR) {
        SoundSys_PlaySe(STAR_DESIGNER_SE_STAR);
    }
    if (result == STAR_DESIGNER_TOUCH_STAR || result == STAR_DESIGNER_TOUCH_PIECES) {
        StarDesigner_Refresh(self, 1);
    }
    return result;
}
CLEAN_AS(func_ov129_0229b800, StarDesigner_TouchStar)

/* func_ov129_0229b85c: a touch with pieces drawn. A star other than the end of the line: with
 * no end it becomes the end; when an open piece joins it to the end, that piece is the one
 * touched; else, when a drawn piece reaches it, it becomes the end. Then the piece touched (the
 * one under the pointer unless set above): a drawn one is taken off, an open one drawn into the
 * first free slot and the end moved to its other star. */
int StarDesigner_TouchInPieces(StarDesigner *self)
{
    int piece;

    if (self->star != STAR_DESIGNER_NO_STAR && self->end_star != self->star) {
        if (self->end_star == STAR_DESIGNER_NO_STAR) {
            self->end_star = self->star;
            return STAR_DESIGNER_TOUCH_STAR;
        }
        piece = StarDesigner_PieceBetween(self, self->end_star, self->star);
        if (piece != STAR_DESIGNER_NO_PIECE && self->piece_state[piece] == STAR_DESIGNER_PIECE_OPEN) {
            self->piece = (u16) piece;
        } else if (StarDesigner_HasDrawnPieceAt(self, self->star) != 0) {
            self->end_star = self->star;
            return STAR_DESIGNER_TOUCH_STAR;
        }
    }
    piece = self->piece;
    if (piece == STAR_DESIGNER_NO_PIECE) {
        return STAR_DESIGNER_TOUCH_NONE;
    }
    switch (self->piece_state[piece]) {
        case STAR_DESIGNER_PIECE_DRAWN:
            return StarDesigner_TakeOffPiece(self);
        case STAR_DESIGNER_PIECE_OPEN:
            /* an open piece is only marked while a slot is free (StarDesigner_OpenPiecesAt) */
            *star_designer_slot(self, StarDesigner_FreeSlot(self)) = self->piece;
            StarDesigner_MoveEndAlong(self);
            return STAR_DESIGNER_TOUCH_PIECES;
        default:
            return STAR_DESIGNER_TOUCH_NONE;
    }
}
CLEAN_AS(func_ov129_0229b85c, StarDesigner_TouchInPieces)

/* func_ov129_0229b910: a touch with only the first star picked. Another star: the open piece
 * joining it to the first is the one touched, else the touch starts again from that star (its
 * result returned when it did something). Then an open piece touched is the first piece: the
 * pieces mode, "done" enabled and the end moved along it. */
int StarDesigner_TouchFromFirst(StarDesigner *self)
{
    int piece;

    if (self->first_star != self->star) {
        piece = StarDesigner_PieceBetween(self, self->first_star, self->star);
        if (piece != STAR_DESIGNER_NO_PIECE && self->piece_state[piece] == STAR_DESIGNER_PIECE_OPEN) {
            self->piece = (u16) piece;
        } else {
            int result = StarDesigner_TouchFirst(self);
            if (result != STAR_DESIGNER_TOUCH_NONE) {
                return result;
            }
        }
    }
    if (self->piece != STAR_DESIGNER_NO_PIECE && self->piece_state[self->piece] == STAR_DESIGNER_PIECE_OPEN) {
        self->mode = STAR_DESIGNER_MODE_PIECES;
        self->pieces[0] = self->piece;
        ButtonPanel_ClearSpriteFlag4(&self->panel, STAR_DESIGNER_BUTTON_DONE);
        StarDesigner_MoveEndAlong(self);
        return STAR_DESIGNER_TOUCH_PIECES;
    }
    return STAR_DESIGNER_TOUCH_NONE;
}
CLEAN_AS(func_ov129_0229b910, StarDesigner_TouchFromFirst)

/* func_ov129_0229b9a0: a piece drawn (heard): the end of the line moves to the piece's other
 * star (its second when the end is its first, else its first). */
void StarDesigner_MoveEndAlong(StarDesigner *self)
{
    const u8 *stars;

    SoundSys_PlaySe(STAR_DESIGNER_SE_DRAWN);
    stars = StarScope_PieceStars(self->piece);
    if (stars[0] == self->end_star) {
        self->end_star = stars[1];
    } else {
        self->end_star = stars[0];
    }
}
CLEAN_AS(func_ov129_0229b9a0, StarDesigner_MoveEndAlong)

/* func_ov129_0229b9d8: a touch with no star picked: a star under the pointer from which a piece
 * can start becomes the first star and the end of the line (the first-star mode); one from
 * which none can shows error message 0x16. Returns StarDesigner_CanStartAt's answer (0 with no
 * star under the pointer). */
int StarDesigner_TouchFirst(StarDesigner *self)
{
    int result;

    if (self->star == STAR_DESIGNER_NO_STAR) {
        return STAR_DESIGNER_TOUCH_NONE;
    }
    result = StarDesigner_CanStartAt(self, self->star);
    if (result == STAR_DESIGNER_TOUCH_STAR) {
        self->mode = STAR_DESIGNER_MODE_FIRST;
        self->first_star = self->star;
        self->end_star = self->star;
    } else if (result == STAR_DESIGNER_TOUCH_ERROR) {
        StarDesigner_ShowError(self, STAR_DESIGNER_MESSAGE_NO_START);
    }
    return result;
}
CLEAN_AS(func_ov129_0229b9d8, StarDesigner_TouchFirst)

/* The marks of the walk over the pieces left in StarDesigner_TakeOffPiece. */
enum {
    STAR_DESIGNER_WALK_UNSEEN = 0,
    STAR_DESIGNER_WALK_NEXT = 1, /* reached, its neighbours not yet looked at */
    STAR_DESIGNER_WALK_DONE = 2,
    STAR_DESIGNER_WALK_EMPTY = 3 /* an empty slot */
};

/* func_ov129_0229ba2c: the drawn piece under the pointer taken off, when what is left stays one
 * line: the pieces left are walked from the first through the pieces round their stars, and if
 * one is not reached the piece is put back (0). With none left the drawing is empty again
 * ("done" disabled). Else, when the end of the line was a star of the piece, the piece is freed
 * and the end moves to its other star unless a drawn piece still reaches the end. Heard; 2. */
int StarDesigner_TakeOffPiece(StarDesigner *self)
{
    u8 marks[CONSTELLATIONS_PIECES];
    u16 around[STAR_DESIGNER_AROUND];
    int slot = StarDesigner_PieceSlot(self, self->piece);
    int count;
    int changed;
    const u8 *stars;
    u8 other;

    if (slot == -1) {
        return STAR_DESIGNER_TOUCH_NONE;
    }
    self->pieces[slot] = STAR_DESIGNER_NO_PIECE;

    count = 0;
    for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
        if (self->pieces[i] == STAR_DESIGNER_NO_PIECE) {
            marks[i] = STAR_DESIGNER_WALK_EMPTY;
        } else {
            marks[i] = count > 0 ? STAR_DESIGNER_WALK_UNSEEN : STAR_DESIGNER_WALK_NEXT;
            count++;
        }
    }
    if (count == 0) {
        ButtonPanel_SetSpriteFlag4(&self->panel, STAR_DESIGNER_BUTTON_DONE);
        self->mode = STAR_DESIGNER_MODE_EMPTY;
        self->end_star = STAR_DESIGNER_NO_STAR;
        SoundSys_PlaySe(STAR_DESIGNER_SE_TAKEN);
        return STAR_DESIGNER_TOUCH_PIECES;
    }

    changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
            if (marks[i] != STAR_DESIGNER_WALK_NEXT) {
                continue;
            }
            stars = StarScope_PieceStars(self->pieces[i]);
            for (int end = 0; end < 2; end++) {
                int n = star_designer_pieces_around(around, stars[end]);
                for (int k = 0; k < n; k++) {
                    int found = StarDesigner_PieceSlot(self, around[k]);
                    if (found != -1 && marks[found] == STAR_DESIGNER_WALK_UNSEEN) {
                        marks[found] = STAR_DESIGNER_WALK_NEXT;
                    }
                }
            }
            marks[i] = STAR_DESIGNER_WALK_DONE;
        }
        for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
            if (marks[i] == STAR_DESIGNER_WALK_NEXT) {
                changed = 1;
            }
        }
    }
    for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
        if (marks[i] == STAR_DESIGNER_WALK_UNSEEN) {
            self->pieces[slot] = self->piece;
            return STAR_DESIGNER_TOUCH_NONE;
        }
    }

    stars = StarScope_PieceStars(self->piece);
    other = STAR_DESIGNER_NO_STAR;
    if (stars[0] == self->end_star) {
        other = stars[1];
    } else if (stars[1] == self->end_star) {
        other = stars[0];
    }
    if (other != STAR_DESIGNER_NO_STAR) {
        self->piece_state[self->piece] = STAR_DESIGNER_PIECE_FREE;
        if (StarDesigner_HasDrawnPieceAt(self, self->end_star) == 0) {
            self->end_star = other;
        }
    }
    SoundSys_PlaySe(STAR_DESIGNER_SE_TAKEN);
    return STAR_DESIGNER_TOUCH_PIECES;
}
CLEAN_AS(func_ov129_0229ba2c, StarDesigner_TakeOffPiece)

/* func_ov129_0229bbd8: the first piece round `star` that has `other` as one of its stars, or
 * STAR_DESIGNER_NO_PIECE. */
unsigned short StarDesigner_PieceBetween(StarDesigner *self, int star, unsigned char other)
{
    u16 around[STAR_DESIGNER_AROUND];
    int count;

    (void) self;
    count = star_designer_pieces_around(around, (unsigned int) star);
    for (int i = 0; i < count; i++) {
        const u8 *stars = StarScope_PieceStars(around[i]);
        for (int end = 0; end < 2; end++) {
            if (other == stars[end]) {
                return around[i];
            }
        }
    }
    return STAR_DESIGNER_NO_PIECE;
}
CLEAN_AS(func_ov129_0229bbd8, StarDesigner_PieceBetween)

/* func_ov129_0229bc34: whether a first piece can be drawn from `star`: 0 when a piece round it
 * is another constellation's, 1 when a piece round it does not reach one at its other star, 3
 * when every one does. */
int StarDesigner_CanStartAt(StarDesigner *self, unsigned int star)
{
    u16 around[STAR_DESIGNER_AROUND];
    int count = star_designer_pieces_around(around, star);

    for (int i = 0; i < count; i++) {
        if (self->piece_state[around[i]] == STAR_DESIGNER_PIECE_TAKEN) {
            return STAR_DESIGNER_TOUCH_NONE;
        }
    }
    for (int i = 0; i < count; i++) {
        if (StarDesigner_PieceNearTaken(self, around[i], (int) star) == 0) {
            return STAR_DESIGNER_TOUCH_STAR;
        }
    }
    return STAR_DESIGNER_TOUCH_ERROR;
}
CLEAN_AS(func_ov129_0229bc34, StarDesigner_CanStartAt)

/* func_ov129_0229bca4: whether a drawn piece is round `star` (the source passes it as a
 * pointer). */
int StarDesigner_HasDrawnPieceAt(StarDesigner *self, u32 star)
{
    u16 around[STAR_DESIGNER_AROUND];
    int count = star_designer_pieces_around(around, star);

    for (int i = 0; i < count; i++) {
        if (self->piece_state[around[i]] == STAR_DESIGNER_PIECE_DRAWN) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov129_0229bca4, StarDesigner_HasDrawnPieceAt)

/* func_ov129_0229bcf0: the slot holding `piece`, or -1. */
int StarDesigner_PieceSlot(StarDesigner *self, unsigned short piece)
{
    for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
        if (piece == self->pieces[i]) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_ov129_0229bcf0, StarDesigner_PieceSlot)

/* func_ov129_0229bd1c: the first empty slot, or -1. */
int StarDesigner_FreeSlot(StarDesigner *self)
{
    for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
        if (self->pieces[i] == STAR_DESIGNER_NO_PIECE) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_ov129_0229bd1c, StarDesigner_FreeSlot)

/* func_ov129_0229bd4c: the star and the piece under the point (x, y) of the screen: at the
 * point and 4 pixels below, above, left and right of it, the first sky cell in the lens holding
 * a star gives `star` and the first holding a piece gives `piece`. Returns whether either was
 * found. (The source passes x and y as pointers.) */
int StarDesigner_FindUnderPointer(StarDesigner *self, int x, int y)
{
    self->star = STAR_DESIGNER_NO_STAR;
    self->piece = STAR_DESIGNER_NO_PIECE;
    for (int i = 0; i < 5; i++) {
        int column;
        int row;
        if (StarScope_SkyCellInLens(&self->scope, x + data_ov129_0229db04[i], y + data_ov129_0229db18[i], &column, &row) ==
            0) {
            continue;
        }
        if (self->star == STAR_DESIGNER_NO_STAR) {
            int star = StarScope_StarAtCell(column, row);
            if (star != -1) {
                self->star = (u8) star;
            }
        }
        if (self->piece == STAR_DESIGNER_NO_PIECE) {
            int piece = StarScope_PieceAtCell(column, row);
            if (piece != -1) {
                self->piece = (u16) piece;
            }
        }
    }
    return self->star != STAR_DESIGNER_NO_STAR || self->piece != STAR_DESIGNER_NO_PIECE;
}
CLEAN_AS(func_ov129_0229bd4c, StarDesigner_FindUnderPointer)

/* func_ov129_0229be04: while a slot is free, the pieces round `star` that may be drawn from it
 * marked open. */
void StarDesigner_OpenPiecesAt(StarDesigner *self, int star)
{
    u16 around[STAR_DESIGNER_AROUND];
    int count;

    if (star == STAR_DESIGNER_NO_STAR) {
        return;
    }
    if (StarDesigner_FreeSlot(self) == -1) {
        return;
    }
    count = star_designer_pieces_around(around, (unsigned int) star);
    for (int i = 0; i < count; i++) {
        StarDesigner_OpenPiece(self, around[i], star);
    }
}
CLEAN_AS(func_ov129_0229be04, StarDesigner_OpenPiecesAt)

/* func_ov129_0229be58: a free piece drawn from `star` marked open, unless its other star
 * reaches another constellation. */
void StarDesigner_OpenPiece(StarDesigner *self, unsigned short piece, int star)
{
    if (self->piece_state[piece] != STAR_DESIGNER_PIECE_FREE) {
        return;
    }
    if (StarDesigner_PieceNearTaken(self, piece, star) != 0) {
        return;
    }
    self->piece_state[piece] = STAR_DESIGNER_PIECE_OPEN;
}
CLEAN_AS(func_ov129_0229be58, StarDesigner_OpenPiece)

/* func_ov129_0229be7c: whether a piece of another constellation is round a star of `piece`
 * other than `star`. (The source passes the piece as a pointer.) */
int StarDesigner_PieceNearTaken(StarDesigner *self, int piece, int star)
{
    u16 around[STAR_DESIGNER_AROUND];
    const u8 *stars = StarScope_PieceStars(piece);

    for (int end = 0; end < 2; end++) {
        u8 other = stars[end];
        if (star != other) {
            int count = star_designer_pieces_around(around, other);
            for (int k = 0; k < count; k++) {
                if (self->piece_state[around[k]] == STAR_DESIGNER_PIECE_TAKEN) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov129_0229be7c, StarDesigner_PieceNearTaken)

/* func_ov129_0229bee4: the pieces' states made again (the constellation's drawn, with
 * `with_open` the ones that may be drawn next open) and every piece painted. */
void StarDesigner_Refresh(StarDesigner *self, int with_open)
{
    StarDesigner_UnmarkDrawn(self);
    StarDesigner_MarkDrawn(self);
    if (with_open != 0) {
        StarDesigner_OpenFromEnd(self);
    }
    StarDesigner_PaintAll(self);
}
CLEAN_AS(func_ov129_0229bee4, StarDesigner_Refresh)

/* func_ov129_0229bf10: every piece of the sky painted by its state. */
void StarDesigner_PaintAll(StarDesigner *self)
{
    for (int i = 0; i < STAR_DESIGNER_PIECES; i++) {
        StarDesigner_Paint(self, i);
    }
}
CLEAN_AS(func_ov129_0229bf10, StarDesigner_PaintAll)

/* func_ov129_0229bf30: a piece painted in its state's palette. */
void StarDesigner_Paint(StarDesigner *self, int piece)
{
    StarScope_PaintPiece(&self->scope, piece, data_ov129_0229dae0[self->piece_state[piece]]);
}
CLEAN_AS(func_ov129_0229bf30, StarDesigner_Paint)

/* func_ov129_0229bf54: the pieces open from the first star (first-star mode) or from the end of
 * the line (pieces mode). */
void StarDesigner_OpenFromEnd(StarDesigner *self)
{
    switch (self->mode) {
        case STAR_DESIGNER_MODE_EMPTY:
            break;
        case STAR_DESIGNER_MODE_FIRST:
            StarDesigner_OpenPiecesAt(self, self->first_star);
            break;
        case STAR_DESIGNER_MODE_PIECES:
            StarDesigner_OpenPiecesAt(self, self->end_star);
            break;
    }
}
CLEAN_AS(func_ov129_0229bf54, StarDesigner_OpenFromEnd)

/* func_ov129_0229bf88: the constellation's pieces marked drawn. */
void StarDesigner_MarkDrawn(StarDesigner *self)
{
    for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
        u16 piece = self->pieces[i];
        if (piece != STAR_DESIGNER_NO_PIECE) {
            self->piece_state[piece] = STAR_DESIGNER_PIECE_DRAWN;
        }
    }
}
CLEAN_AS(func_ov129_0229bf88, StarDesigner_MarkDrawn)

/* func_ov129_0229bfbc: the constellation of GroupParams' argument taken: when it exists its
 * pieces and name, the pieces mode with the end of the line at the first star of its first
 * piece, and the view put on that star (its tile's centre, in whole 4 pixels); else no piece,
 * an empty name and the empty mode. Its pieces marked drawn. */
void StarDesigner_LoadConstellation(StarDesigner *self)
{
    const Constellation *source = (const Constellation *) (uintptr_t) Constellations_Get(GroupParams_Arg());
    int first = STAR_DESIGNER_NO_PIECE;

    if (source != NULL) {
        int x;
        int y;
        for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
            self->pieces[i] = source->pieces[i];
            if (self->pieces[i] != STAR_DESIGNER_NO_PIECE && first == STAR_DESIGNER_NO_PIECE) {
                first = self->pieces[i];
            }
        }
        self->mode = STAR_DESIGNER_MODE_PIECES;
        self->end_star = StarScope_PieceStars(first)[0];
        x = StarScope_StarColumn(self->end_star) << 3;
        y = StarScope_StarRow(self->end_star) << 3;
        StarScope_LookAt(&self->scope, (x + 4) & 0xfffc, (y + 4) & 0xfffc);
        for (int i = 0; i < CONSTELLATIONS_NAME_LENGTH; i++) {
            self->name[i] = source->name[i];
        }
    } else {
        for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
            self->pieces[i] = (u16) first;
        }
        for (int i = 0; i < CONSTELLATIONS_NAME_LENGTH; i++) {
            self->name[i] = 0;
        }
        self->mode = STAR_DESIGNER_MODE_EMPTY;
    }
    StarDesigner_MarkDrawn(self);
}
CLEAN_AS(func_ov129_0229bfbc, StarDesigner_LoadConstellation)

/* func_ov129_0229c094: the pieces of every other constellation that exists marked taken. */
void StarDesigner_MarkTaken(StarDesigner *self)
{
    int own = GroupParams_Arg();

    for (int i = 0; i < CONSTELLATIONS_COUNT; i++) {
        const Constellation *other;
        if (i == own) {
            continue;
        }
        other = (const Constellation *) (uintptr_t) Constellations_Get(i);
        if (other == NULL) {
            continue;
        }
        for (int j = 0; j < CONSTELLATIONS_PIECES; j++) {
            u16 piece = other->pieces[j];
            if (piece != STAR_DESIGNER_NO_PIECE) {
                self->piece_state[piece] = STAR_DESIGNER_PIECE_TAKEN;
            }
        }
    }
}
CLEAN_AS(func_ov129_0229c094, StarDesigner_MarkTaken)

/* func_ov129_0229c0e8: the drawn and open pieces freed. */
void StarDesigner_UnmarkDrawn(StarDesigner *self)
{
    for (int i = 0; i < STAR_DESIGNER_PIECES; i++) {
        u8 state = self->piece_state[i];
        if (state == STAR_DESIGNER_PIECE_DRAWN || state == STAR_DESIGNER_PIECE_OPEN) {
            self->piece_state[i] = STAR_DESIGNER_PIECE_FREE;
        }
    }
}
CLEAN_AS(func_ov129_0229c0e8, StarDesigner_UnmarkDrawn)

/* func_ov129_0229c118: every piece free. */
void StarDesigner_ClearPieceStates(StarDesigner *self)
{
    for (int i = 0; i < STAR_DESIGNER_PIECES; i++) {
        self->piece_state[i] = STAR_DESIGNER_PIECE_FREE;
    }
}
CLEAN_AS(func_ov129_0229c118, StarDesigner_ClearPieceStates)

/* func_ov129_0229c140: the touched piece's flash counted down, and painted back at its end. */
void StarDesigner_StepFlash(StarDesigner *self)
{
    if (self->flash_timer != 0) {
        self->flash_timer--;
        if (self->flash_timer == 0) {
            StarDesigner_Unflash(self);
        }
    }
}
CLEAN_AS(func_ov129_0229c140, StarDesigner_StepFlash)

/* func_ov129_0229c170: the piece under the pointer flashed for 5 frames (painted in palette 10
 * when drawn or open), the one flashed before painted back. */
void StarDesigner_Flash(StarDesigner *self)
{
    int piece;

    self->flash_timer = STAR_DESIGNER_FLASH_FRAMES;
    if (self->piece != self->flash_piece) {
        StarDesigner_Unflash(self);
    }
    piece = self->piece;
    if (piece != STAR_DESIGNER_NO_PIECE) {
        u8 state = self->piece_state[piece];
        if (state == STAR_DESIGNER_PIECE_DRAWN || state == STAR_DESIGNER_PIECE_OPEN) {
            StarScope_PaintPiece(&self->scope, piece, STAR_DESIGNER_PALETTE_FLASH);
        }
    }
    self->flash_piece = self->piece;
}
CLEAN_AS(func_ov129_0229c170, StarDesigner_Flash)

/* func_ov129_0229c1d4: the flashed piece painted back by its state and forgotten. */
void StarDesigner_Unflash(StarDesigner *self)
{
    if (self->flash_piece != STAR_DESIGNER_NO_PIECE) {
        StarDesigner_Paint(self, self->flash_piece);
        self->flash_piece = STAR_DESIGNER_NO_PIECE;
    }
}
CLEAN_AS(func_ov129_0229c1d4, StarDesigner_Unflash)

/* func_ov129_0229c1f8: the piece the free pointer is at painted as such (palette 11 when drawn,
 * 8 when open), the one painted before painted back. Over a star other than the end of the
 * line, the open piece joining the two is the one pointed at; else in the pieces mode none when
 * a drawn piece reaches the star. */
void StarDesigner_Hover(StarDesigner *self)
{
    int piece;

    if (StarDesigner_FindUnderPointer(self, self->x, self->y) != 0) {
        if (self->star != STAR_DESIGNER_NO_STAR && self->end_star != STAR_DESIGNER_NO_STAR && self->star != self->end_star) {
            switch (self->mode) {
                case STAR_DESIGNER_MODE_FIRST:
                case STAR_DESIGNER_MODE_PIECES: {
                    int between = StarDesigner_PieceBetween(self, self->end_star, self->star);
                    if (between != STAR_DESIGNER_NO_PIECE && self->piece_state[between] == STAR_DESIGNER_PIECE_OPEN) {
                        self->piece = (u16) between;
                    } else if (self->mode == STAR_DESIGNER_MODE_PIECES) {
                        if (StarDesigner_HasDrawnPieceAt(self, self->star) != 0) {
                            self->piece = STAR_DESIGNER_NO_PIECE;
                        }
                    }
                    break;
                }
            }
        }
        piece = self->piece;
    } else {
        piece = STAR_DESIGNER_NO_PIECE;
    }
    if (piece != self->hover_piece) {
        StarDesigner_Unhover(self);
    }
    if (piece != STAR_DESIGNER_NO_PIECE) {
        u8 state = self->piece_state[piece];
        if (state == STAR_DESIGNER_PIECE_DRAWN) {
            StarScope_PaintPiece(&self->scope, piece, STAR_DESIGNER_PALETTE_HOVER_DRAWN);
        } else if (state == STAR_DESIGNER_PIECE_OPEN) {
            StarScope_PaintPiece(&self->scope, piece, STAR_DESIGNER_PALETTE_HOVER_OPEN);
        }
    }
    self->hover_piece = (u16) piece;
}
CLEAN_AS(func_ov129_0229c1f8, StarDesigner_Hover)

/* func_ov129_0229c2d8: the piece pointed at painted back by its state and forgotten. */
void StarDesigner_Unhover(StarDesigner *self)
{
    if (self->hover_piece != STAR_DESIGNER_NO_PIECE) {
        StarDesigner_Paint(self, self->hover_piece);
        self->hover_piece = STAR_DESIGNER_NO_PIECE;
    }
}
CLEAN_AS(func_ov129_0229c2d8, StarDesigner_Unhover)
