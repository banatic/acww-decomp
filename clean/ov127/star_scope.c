/* The telescope's view of the night sky, overlay 127 (star_scope.h): the stars' and pieces'
 * tables, the judge of a draft constellation, the view's scroll, glide and arrows, and the
 * layers it loads. */
#include "star_scope.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "itcm/vector.h"
#include "main/display_layers.h"
#include "main/oam_buffer.h"
#include "main/rom_file.h"
#include "main/sound.h"

static_assert(sizeof(LayerTask) == 0x24 && offsetof(StarScope, sky) == 0x24, "task");
static_assert(offsetof(StarScope, shown) == 0x1024 && offsetof(StarScope, scope) == 0x2024, "maps");
static_assert(offsetof(StarScope, scroll_x) == 0x2824 && offsetof(StarScope, bounce) == 0x2828, "scroll");
static_assert(offsetof(StarScope, target_x) == 0x282a && offsetof(StarScope, hidden_rows) == 0x282e, "target");
static_assert(offsetof(StarScope, flags) == 0x2830 && offsetof(StarScope, sky_layer) == 0x2832, "flags");
static_assert(offsetof(StarScope, pressed) == 0x2834 && offsetof(StarScope, nudge_steps) == 0x2836, "arrows");
static_assert(sizeof(StarScope) == 0x2838, "size");

/* The stars (column, row), the pieces (their two stars) and the sky's tiles (StarScopeKind in
 * the top four bits, the star or piece below). */
extern const u8 data_ov127_0229a104[];
extern const u16 data_ov127_0229a24c[];
extern const u16 data_ov127_0229a5d8[];

/* The judge's two lists of stars (STAR_SCOPE_STAR_LIST bytes each, 0x14 apart). */
extern u8 data_ov127_0229b6e0[];
extern u8 data_ov127_0229b6f4[];

/* A nudge's steps back (StarScope_StepNudge), from the last. */
extern const s32 data_ov127_0229a0fc[2];

/* The scrolling sound's pan by arrow; the OBJs of a star's mark, the screen's centre and the
 * four arrows, and where the arrows sit round the middle (in steps of a quarter of the spread). */
extern const u8 data_ov127_0229b5e0[STAR_SCOPE_ARROWS];
extern const OamEntry data_ov127_0229b5e4;
extern const OamEntry data_ov127_0229b5ec;
extern const s32 data_ov127_0229b5f4[STAR_SCOPE_ARROWS];
extern const s32 data_ov127_0229b604[STAR_SCOPE_ARROWS];
extern const OamEntry data_ov127_0229b614[STAR_SCOPE_ARROWS];

/* The files: "menu/star/b_scp_obj.bpl", "...b_scp_obj.bch", "...b_scp_bg.bpl", "...b_scp_bg.bch",
 * "...b_scp_bg.bsc", "menu/star/b_bg.bch" and "menu/star/bg.bsc". */
extern const char data_ov127_0229b634[];
extern const char data_ov127_0229b64c[];
extern const char data_ov127_0229b664[];
extern const char data_ov127_0229b67c[];
extern const char data_ov127_0229b694[];
extern const char data_ov127_0229b6ac[];
extern const char data_ov127_0229b6c0[];

/* The heap the scenes load into (autoload_2/heap.c). */
extern Heap *data_021fbe94;

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

#define STAR_SCOPE_SCROLL_SE 0x883
#define STAR_SCOPE_SCROLL_X_MASK 0x1ff
#define STAR_SCOPE_SCROLL_Y_MIN (-24)
#define STAR_SCOPE_SCROLL_Y_MAX 84
#define STAR_SCOPE_BOUNCE_MIN (-68)
#define STAR_SCOPE_BOUNCE_MAX 76
/* The screen's middle; the empty sky a blanked row shows (tile 0x10, palette 4); the scope's
 * screen tile that is its lens. */
#define STAR_SCOPE_MIDDLE_X 0x80
#define STAR_SCOPE_MIDDLE_Y 0x60
#define STAR_SCOPE_EMPTY_SKY 0x4010
#define STAR_SCOPE_LENS_TILE 0x20

/* An arithmetic shift right (the ARM's asr) of `value`, `shift` below 32. */
static int star_scope_asr(int value, int shift)
{
    return value >= 0 ? value >> shift : ~(~value >> shift);
}

/* func_ov127_022995a0: whether no star of the draft is a star of a kept constellation (the
 * stars of each are listed into the overlay's two lists, StarScope_CollectStars). */
int StarScope_StarsAreFree(Constellation *draft)
{
    StarScope_CollectStars(draft, data_ov127_0229b6e0);
    for (int i = 0; i < CONSTELLATIONS_COUNT; i++) {
        int kept = Constellations_At(i);
        if (kept == 0) {
            continue;
        }
        StarScope_CollectStars((const Constellation *) (uintptr_t) (u32) kept, data_ov127_0229b6f4);
        for (int k = 0; k < STAR_SCOPE_STAR_LIST && data_ov127_0229b6e0[k] != STAR_SCOPE_NO_STAR; k++) {
            for (int m = 0; m < STAR_SCOPE_STAR_LIST && data_ov127_0229b6f4[m] != STAR_SCOPE_NO_STAR; m++) {
                if (data_ov127_0229b6e0[k] == data_ov127_0229b6f4[m]) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
CLEAN_AS(func_ov127_022995a0, StarScope_StarsAreFree)

/* func_ov127_0229960c: the stars of a constellation's pieces into `stars`, each once, in the
 * order met; the rest of the list's 17 places 0xff.
 * QUIRK: the list is not bounded: pieces with more than 17 stars among them run on past it. */
void StarScope_CollectStars(const Constellation *constellation, u8 *stars)
{
    for (int i = 0; i < STAR_SCOPE_STAR_LIST; i++) {
        stars[i] = STAR_SCOPE_NO_STAR;
    }
    int count = 0;
    for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
        int piece = constellation->pieces[i];
        if (piece == CONSTELLATIONS_NO_PIECE) {
            continue;
        }
        const u8 *ends = StarScope_PieceStars((u16) piece);
        for (int j = 0; j < 2; j++) {
            int k = 0;
            while (k < count && stars[k] != ends[j]) {
                k++;
            }
            if (k == count) {
                stars[count] = ends[j];
                count++;
            }
        }
    }
}
CLEAN_AS(func_ov127_0229960c, StarScope_CollectStars)

/* func_ov127_02299680: the first kept constellation one of whose pieces is `piece`, or -1. */
int StarScope_ConstellationOfPiece(int piece)
{
    for (int i = 0; i < CONSTELLATIONS_COUNT; i++) {
        int kept = Constellations_Get(i);
        if (kept == 0) {
            continue;
        }
        const Constellation *constellation = (const Constellation *) (uintptr_t) (u32) kept;
        for (int j = 0; j < CONSTELLATIONS_PIECES; j++) {
            if (piece == constellation->pieces[j]) {
                return i;
            }
        }
    }
    return -1;
}
CLEAN_AS(func_ov127_02299680, StarScope_ConstellationOfPiece)

/* func_ov127_022996bc: the two stars of a piece. */
const u8 *StarScope_PieceStars(int piece)
{
    return (const u8 *) (const void *) &data_ov127_0229a24c[piece];
}
CLEAN_AS(func_ov127_022996bc, StarScope_PieceStars)

/* func_ov127_022996c8: a star's row. */
u8 StarScope_StarRow(u8 star)
{
    return data_ov127_0229a104[star * 2 + 1];
}
CLEAN_AS(func_ov127_022996c8, StarScope_StarRow)

/* func_ov127_022996d8: a star's column. */
u8 StarScope_StarColumn(unsigned int star)
{
    return data_ov127_0229a104[star * 2];
}
CLEAN_AS(func_ov127_022996d8, StarScope_StarColumn)

/* Adds the piece at a tile, if any, to `pieces`. */
static int star_scope_add_piece(u16 *pieces, int count, int column, int row)
{
    int piece = StarScope_PieceAtCell(column, row);
    if (piece != -1) {
        pieces[count] = (u16) piece;
        count++;
    }
    return count;
}

/* func_ov127_022996e4: the pieces drawn on the eight tiles round a star's (`column`, `row`),
 * row by row from the top left, into `pieces`; how many. The columns wrap round the sky, the
 * rows above the first and below the last are left out.
 * QUIRK: at column 62 of row 0 the count is one less (the last piece found is left out, and with
 * none the count is -1). */
int StarScope_PiecesAround(u16 *pieces, int column, int row)
{
    int left = (column - 1) & (STAR_SCOPE_COLUMNS - 1);
    int right = (column + 1) & (STAR_SCOPE_COLUMNS - 1);
    int above = row - 1;
    int below = row + 1;
    int count = 0;
    if (above >= 0) {
        count = star_scope_add_piece(pieces, count, left, above);
        count = star_scope_add_piece(pieces, count, column, above);
        count = star_scope_add_piece(pieces, count, right, above);
    }
    count = star_scope_add_piece(pieces, count, left, row);
    count = star_scope_add_piece(pieces, count, right, row);
    if (below < STAR_SCOPE_ROWS) {
        count = star_scope_add_piece(pieces, count, left, below);
        count = star_scope_add_piece(pieces, count, column, below);
        count = star_scope_add_piece(pieces, count, right, below);
    }
    if (column == 0x3e && row == 0) {
        count--;
    }
    return count;
}
CLEAN_AS(func_ov127_022996e4, StarScope_PiecesAround)

/* func_ov127_022997d8: the piece drawn on the sky's tile `index`, or -1. */
int StarScope_PieceAt(unsigned int index)
{
    u16 entry = data_ov127_0229a5d8[index];
    if ((entry & 0xf000) >> 12 == STAR_SCOPE_KIND_PIECE) {
        return entry & 0xfff;
    }
    return -1;
}
CLEAN_AS(func_ov127_022997d8, StarScope_PieceAt)

/* func_ov127_02299804: ... on the tile at (`column`, `row`). */
int StarScope_PieceAtCell(int column, int row)
{
    return StarScope_PieceAt((unsigned int) Constellations_MapIndex(column, row));
}
CLEAN_AS(func_ov127_02299804, StarScope_PieceAtCell)

/* func_ov127_02299818: the star on the sky's tile `index`, or -1. */
int StarScope_StarAt(unsigned int index)
{
    u16 entry = data_ov127_0229a5d8[index];
    if ((entry & 0xf000) >> 12 == STAR_SCOPE_KIND_STAR) {
        return entry & 0x0fff;
    }
    return -1;
}
CLEAN_AS(func_ov127_02299818, StarScope_StarAt)

/* func_ov127_02299844: ... on the tile at (`column`, `row`). */
int StarScope_StarAtCell(int column, int row)
{
    return StarScope_StarAt((unsigned int) Constellations_MapIndex(column, row));
}
CLEAN_AS(func_ov127_02299844, StarScope_StarAtCell)

/* func_ov127_02299858 */
void StarScope_ClearFlags(StarScope *scope, u16 flags)
{
    scope->flags = (u16) (scope->flags & ~flags);
}
CLEAN_AS(func_ov127_02299858, StarScope_ClearFlags)

/* func_ov127_02299868 */
void StarScope_SetFlags(StarScope *scope, u16 flags)
{
    scope->flags = (u16) (scope->flags | flags);
}
CLEAN_AS(func_ov127_02299868, StarScope_SetFlags)

/* func_ov127_02299878 */
int StarScope_TestFlags(StarScope *scope, unsigned int flags)
{
    return (scope->flags & flags) != 0;
}
CLEAN_AS(func_ov127_02299878, StarScope_TestFlags)

/* func_ov127_02299890 */
s16 StarScope_ScrollY(StarScope *scope)
{
    return scope->scroll_y;
}
CLEAN_AS(func_ov127_02299890, StarScope_ScrollY)

/* func_ov127_0229989c */
int StarScope_ScrollX(StarScope *scope)
{
    return scope->scroll_x;
}
CLEAN_AS(func_ov127_0229989c, StarScope_ScrollX)

/* func_ov127_022998a8 */
int StarScope_Bounce(StarScope *scope)
{
    return scope->bounce;
}
CLEAN_AS(func_ov127_022998a8, StarScope_Bounce)

/* func_ov127_022998b4: a step of the view's glide to its target (scrolled). The target's x is
 * taken the short way round the sky. Within 8 pixels the view is put at the target and the glide
 * ends; else it moves towards it by half the distance, between 8 and 64 pixels (in 20.12 fixed
 * point, through main's vectors with y 0).
 * QUIRK: the x moved to is not wrapped round the sky: it can be below 0 or past 0x1ff until the
 * next scroll wraps it. */
void StarScope_StepGlide(StarScope *scope)
{
    StarScope_SetFlags(scope, STAR_SCOPE_FLAG_SCROLLED);

    Vec3 from = {scope->scroll_x * 0x1000, 0, scope->scroll_y * 0x1000};
    int target_x = scope->target_x;
    int diff = scope->target_x - scope->scroll_x;
    if (diff <= -0x100) {
        target_x += 0x200;
    } else if (diff >= 0x100) {
        target_x -= 0x200;
    }
    Vec3 to = {target_x * 0x1000, 0, scope->target_y * 0x1000};

    Vec3 step;
    Vec_Subtract(&step, &to, &from);
    fx32 distance = Vec_LengthXZ(&step);
    if (distance <= 0x8000) {
        StarScope_ClearFlags(scope, STAR_SCOPE_FLAG_GLIDING);
        scope->scroll_x = scope->target_x;
        scope->scroll_y = scope->target_y;
        return;
    }

    fx32 speed = distance >> 1;
    if (speed < 0x8000) {
        speed = 0x8000;
    } else if (speed > 0x40000) {
        speed = 0x40000;
    }
    step.x = FX_Div(FX_MulFunc(step.x, speed), distance);
    step.z = FX_Div(FX_MulFunc(step.z, speed), distance);

    Vec3 at;
    Vec_Add(&at, &from, &step);
    scope->scroll_x = (s16) star_scope_asr(at.x, 12);
    scope->scroll_y = (s16) star_scope_asr(at.z, 12);
}
CLEAN_AS(func_ov127_022998b4, StarScope_StepGlide)

/* func_ov127_022999c0: the view to glide to centre the sky's point (`x`, `y`) of the screen at
 * scroll 0 (its y kept to -24-84). */
void StarScope_GlideTo(StarScope *scope, int x, int y)
{
    scope->target_x = (s16) ((x - STAR_SCOPE_MIDDLE_X) & STAR_SCOPE_SCROLL_X_MASK);
    scope->target_y = (s16) (y - STAR_SCOPE_MIDDLE_Y);
    if (scope->target_y < STAR_SCOPE_SCROLL_Y_MIN) {
        scope->target_y = STAR_SCOPE_SCROLL_Y_MIN;
    } else if (scope->target_y > STAR_SCOPE_SCROLL_Y_MAX) {
        scope->target_y = STAR_SCOPE_SCROLL_Y_MAX;
    }
    StarScope_SetFlags(scope, STAR_SCOPE_FLAG_GLIDING);
}
CLEAN_AS(func_ov127_022999c0, StarScope_GlideTo)

/* func_ov127_02299a00: a piece painted into the sky in `palette` (main's
 * Constellations_PaintPiece), to be queued. */
void StarScope_PaintPiece(StarScope *scope, int piece, int palette)
{
    Constellations_PaintPiece(scope->sky, piece, palette);
    StarScope_SetFlags(scope, STAR_SCOPE_FLAG_PAINTED);
}
CLEAN_AS(func_ov127_02299a00, StarScope_PaintPiece)

/* func_ov127_02299a18: when the screen's point (`x`, `y`) is in the scope's lens (its tile of
 * the scope's screen is tile 0x20), the sky's tile under it (StarScope_SkyCellAt); else 0.
 * REQUIRES: the point is on the screen (0-255, 0-191); the game reads the screen's tile from
 * outside the scope's screen for others. */
int StarScope_SkyCellInLens(StarScope *scope, int x, int y, int *column, int *row)
{
    int tile = star_scope_asr(x, 3) + star_scope_asr(y, 3) * 32;
    u32 address = (u32) (uintptr_t) scope + offsetof(StarScope, scope) + (u32) tile * 2;
    u16 entry = *(const u16 *) (uintptr_t) address;
    if ((entry & 0x3ff) == STAR_SCOPE_LENS_TILE) {
        return StarScope_SkyCellAt(scope, x, y, column, row);
    }
    return 0;
}
CLEAN_AS(func_ov127_02299a18, StarScope_SkyCellInLens)

/* func_ov127_02299a50: the sky's tile under the screen's point (`x`, `y`) at the view's scroll,
 * the x round the sky; 0 when the point is above or below the sky. */
int StarScope_SkyCellAt(StarScope *scope, int x, int y, int *column, int *row)
{
    int sky_x = (x + scope->scroll_x) & STAR_SCOPE_SCROLL_X_MASK;
    int sky_y = y + scope->scroll_y;
    if (sky_y < 0 || sky_y >= 0x100) {
        return 0;
    }
    *column = sky_x >> 3;
    *row = sky_y >> 3;
    return 1;
}
CLEAN_AS(func_ov127_02299a50, StarScope_SkyCellAt)

/* func_ov127_02299a94: the view put to centre the sky's point (`x`, `y`) of the screen at
 * scroll 0, its y then kept to -24-84 (a vertical scroll by 0). */
void StarScope_LookAt(StarScope *scope, int x, int y)
{
    scope->scroll_x = (s16) (u16) ((x - STAR_SCOPE_MIDDLE_X) & STAR_SCOPE_SCROLL_X_MASK);
    scope->scroll_y = (s16) (u16) (y - STAR_SCOPE_MIDDLE_Y);
    StarScope_ScrollVertically(scope, 0, 0);
}
CLEAN_AS(func_ov127_02299a94, StarScope_LookAt)

/* func_ov127_02299abc: the view scrolled by `amount` down the sky. With `bounce` set and a
 * bounce under way, the bounce takes the amount instead (kept to -68-76, and ended when it
 * changes sign) and 1 is answered. Else the scroll is kept to -24-84, an edge reached with
 * `bounce` set starting a bounce of the amount; the view is to be scrolled, and whether its y
 * changed is answered. */
int StarScope_ScrollVertically(StarScope *scope, int amount, int bounce)
{
    s16 before = scope->scroll_y;
    if (bounce != 0 && scope->bounce != 0) {
        int old = scope->bounce;
        scope->bounce = (s16) (old + amount);
        if (scope->bounce < STAR_SCOPE_BOUNCE_MIN) {
            scope->bounce = STAR_SCOPE_BOUNCE_MIN;
        } else if (scope->bounce > STAR_SCOPE_BOUNCE_MAX) {
            scope->bounce = STAR_SCOPE_BOUNCE_MAX;
        }
        if (scope->bounce * old < 0) {
            scope->bounce = 0;
        }
        return 1;
    }
    scope->scroll_y = (s16) (scope->scroll_y + amount);
    if (scope->scroll_y < STAR_SCOPE_SCROLL_Y_MIN) {
        scope->scroll_y = STAR_SCOPE_SCROLL_Y_MIN;
        if (bounce != 0) {
            scope->bounce = (s16) amount;
        }
    } else if (scope->scroll_y > STAR_SCOPE_SCROLL_Y_MAX) {
        scope->scroll_y = STAR_SCOPE_SCROLL_Y_MAX;
        if (bounce != 0) {
            scope->bounce = (s16) amount;
        }
    }
    StarScope_SetFlags(scope, STAR_SCOPE_FLAG_SCROLLED);
    return before != scope->scroll_y;
}
CLEAN_AS(func_ov127_02299abc, StarScope_ScrollVertically)

/* func_ov127_02299b58: the view scrolled by `amount` along the sky, round it. */
void StarScope_ScrollHorizontally(StarScope *scope, int amount)
{
    scope->scroll_x = (s16) ((scope->scroll_x + amount) & STAR_SCOPE_SCROLL_X_MASK);
    StarScope_SetFlags(scope, STAR_SCOPE_FLAG_SCROLLED);
}
CLEAN_AS(func_ov127_02299b58, StarScope_ScrollHorizontally)

/* func_ov127_02299b78: a step of a nudge (StarScope_Nudge): the view scrolled by the step's
 * amount by the nudge's arrow (0, then -1: back where it was); whether the nudge is over. */
int StarScope_StepNudge(StarScope *scope)
{
    if (scope->nudge_steps != 0) {
        scope->nudge_steps--;
        StarScope_ScrollByArrow(scope, scope->nudge_arrow, data_ov127_0229a0fc[scope->nudge_steps], 0);
    }
    return scope->nudge_steps == 0;
}
CLEAN_AS(func_ov127_02299b78, StarScope_StepNudge)

/* func_ov127_02299bbc: an arrow tapped: the scrolling sound stopped if it plays, the view
 * scrolled by 1 by the arrow and a nudge of two steps started (StarScope_StepNudge). */
void StarScope_Nudge(StarScope *scope, int arrow)
{
    if (StarScope_TestFlags(scope, STAR_SCOPE_FLAG_SCROLL_SE)) {
        StarScope_ClearFlags(scope, STAR_SCOPE_FLAG_SCROLL_SE);
        SoundSys_StopSound(STAR_SCOPE_SCROLL_SE, 1);
    }
    StarScope_ScrollByArrow(scope, (unsigned int) arrow, 1, 0);
    scope->nudge_steps = 2;
    scope->nudge_arrow = (u8) arrow;
}
CLEAN_AS(func_ov127_02299bbc, StarScope_Nudge)

/* func_ov127_02299c08: an arrow held: the view scrolled by 4 by it (with `bounce`) and the
 * arrow drawn pressed. While the view moves (not counting a scroll that reached the top or
 * bottom), the scrolling sound plays, panned by the arrow when `bounce` is set; else it stops. */
void StarScope_HoldArrow(StarScope *scope, int arrow, int bounce)
{
    int old_bounce = scope->bounce;
    int old_x = scope->scroll_x;
    int old_y = scope->scroll_y;

    StarScope_ScrollByArrow(scope, (unsigned int) arrow, 4, bounce);
    scope->pressed = (u8) arrow;

    int moved = old_bounce != scope->bounce || old_x != scope->scroll_x || old_y != scope->scroll_y;
    if (old_y != scope->scroll_y &&
        (scope->scroll_y == STAR_SCOPE_SCROLL_Y_MIN || scope->scroll_y == STAR_SCOPE_SCROLL_Y_MAX)) {
        moved = 0;
    }

    if (moved) {
        if (StarScope_TestFlags(scope, STAR_SCOPE_FLAG_SCROLL_SE) == 0) {
            StarScope_SetFlags(scope, STAR_SCOPE_FLAG_SCROLL_SE);
            SoundSys_StartOnHandle38(STAR_SCOPE_SCROLL_SE);
        }
    } else if (StarScope_TestFlags(scope, STAR_SCOPE_FLAG_SCROLL_SE) == 1) {
        StarScope_ClearFlags(scope, STAR_SCOPE_FLAG_SCROLL_SE);
        SoundSys_StopSound(STAR_SCOPE_SCROLL_SE, 1);
    }

    if (StarScope_TestFlags(scope, STAR_SCOPE_FLAG_SCROLL_SE) != 0 && bounce != 0) {
        SoundSys_ChangePlayerByte(data_ov127_0229b5e0[arrow]);
    }
}
CLEAN_AS(func_ov127_02299c08, StarScope_HoldArrow)

/* func_ov127_02299cd8: the view scrolled by `amount` the way of an arrow (StarScopeArrow); the
 * vertical ones with `bounce`. Any other arrow does nothing. */
void StarScope_ScrollByArrow(StarScope *scope, unsigned int arrow, int amount, int bounce)
{
    switch (arrow) {
        case STAR_SCOPE_ARROW_LEFT:
            StarScope_ScrollHorizontally(scope, -amount);
            break;
        case STAR_SCOPE_ARROW_RIGHT:
            StarScope_ScrollHorizontally(scope, amount);
            break;
        case STAR_SCOPE_ARROW_UP:
            StarScope_ScrollVertically(scope, amount, bounce);
            break;
        case STAR_SCOPE_ARROW_DOWN:
            StarScope_ScrollVertically(scope, -amount, bounce);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov127_02299cd8, StarScope_ScrollByArrow)

/* func_ov127_02299d20: the arrow whose OBJ, drawn round the screen's middle, holds the screen's
 * point (`x`, `y`) with a margin of 2, the first of them; else STAR_SCOPE_ARROWS. */
int StarScope_ArrowAt(StarScope *scope, int x, int y)
{
    (void) scope;
    int dx = x - STAR_SCOPE_MIDDLE_X;
    int dy = y - STAR_SCOPE_MIDDLE_Y;
    for (int i = 0; i < STAR_SCOPE_ARROWS; i++) {
        if (OamBuffer_ObjContains(&data_ov127_0229b614[i], dx, dy, 2, 2)) {
            return i;
        }
    }
    return STAR_SCOPE_ARROWS;
}
CLEAN_AS(func_ov127_02299d20, StarScope_ArrowAt)

/* func_ov127_02299d64: a mark drawn on a star at the view's scroll (the x round the screen's
 * 0x200, the OBJ's own palette, priority 2); answers the draw's. */
int StarScope_DrawStarMark(StarScope *scope, int star)
{
    int scroll_x = StarScope_ScrollX(scope);
    int column = StarScope_StarColumn((unsigned int) star);
    int x = -scroll_x + 4 + column * 8;
    int scroll_y = StarScope_ScrollY(scope);
    int row = StarScope_StarRow((u8) star);
    int y = -scroll_y + 4 + row * 8;
    return OamBuffer_DrawObjAffine(1, &data_ov127_0229b5e4, x & 0x1ff, y, -1, 2, NULL);
}
CLEAN_AS(func_ov127_02299d64, StarScope_DrawStarMark)

/* func_ov127_02299dc0: the screen's centre mark drawn, moved down by `y` (priority 1). */
void StarScope_DrawCentre(StarScope *scope, int y)
{
    (void) scope;
    OamBuffer_DrawObjAffine(1, &data_ov127_0229b5ec, STAR_SCOPE_MIDDLE_X, y + STAR_SCOPE_MIDDLE_Y, -1, 1, NULL);
}
CLEAN_AS(func_ov127_02299dc0, StarScope_DrawCentre)

/* func_ov127_02299de8: the four arrows drawn round the screen's middle, each a quarter of
 * `spread` from it its own way, in `palette` (palette 7 for the arrow drawn pressed); then no
 * arrow is pressed. */
void StarScope_DrawArrows(StarScope *scope, int spread, int palette)
{
    int quarter = star_scope_asr(spread, 2);
    for (int i = 0; i < STAR_SCOPE_ARROWS; i++) {
        int arrow_palette = i == scope->pressed ? 7 : palette;
        OamBuffer_DrawObjAffine(1, &data_ov127_0229b614[i], data_ov127_0229b5f4[i] * quarter + STAR_SCOPE_MIDDLE_X,
                                data_ov127_0229b604[i] * quarter + STAR_SCOPE_MIDDLE_Y, arrow_palette, 1, NULL);
    }
    scope->pressed = STAR_SCOPE_ARROWS;
}
CLEAN_AS(func_ov127_02299de8, StarScope_DrawArrows)

/* func_ov127_02299e5c: the layer task taken off the main loop's queue and reset. */
void StarScope_EndTask(StarScope *scope)
{
    LayerTask_End(&scope->task);
}
CLEAN_AS(func_ov127_02299e5c, StarScope_EndTask)

/* Rows of the shown sky blanked (both screens), from `first`, `count` of them. */
static void star_scope_blank_rows(StarScope *scope, int first, int count)
{
    u16 *left = &scope->shown[first * 32];
    u16 *right = left + STAR_SCOPE_SCREEN_TILES;
    for (int i = 0; i < count * 32; i++) {
        left[i] = STAR_SCOPE_EMPTY_SKY;
        right[i] = STAR_SCOPE_EMPTY_SKY;
    }
}

/* The rows shown past the sky's edge at a vertical scroll: past its top (a negative count, for a
 * negative scroll) or past its bottom (for a scroll from 0x40), (scroll - 7) / 8 and
 * (scroll - 0x39) / 8 rounded down. */
static int star_scope_rows_past_edge(int scroll_y)
{
    if (scroll_y < 0) {
        return star_scope_asr(scroll_y - 7, 3);
    }
    if (scroll_y >= 0x40) {
        return star_scope_asr(scroll_y - 0x39, 3);
    }
    return 0;
}

/* func_ov127_02299e64: the view's frame: a step of the glide while it glides; when scrolled,
 * the sky's layer scrolled and the rows past the sky's edge counted (when that changed, the
 * sky is to be queued again); when to be queued, the sky copied into the shown sky, the rows
 * past the edge blanked (at the top for a positive count, at the bottom for a negative one) and
 * the shown sky queued to the sky's layer. The layer wraps round vertically, so the rows shown
 * past the sky's bottom are the map's first ones and those past its top the map's last ones. */
void StarScope_Update(StarScope *scope)
{
    if (StarScope_TestFlags(scope, STAR_SCOPE_FLAG_GLIDING) != 0) {
        StarScope_StepGlide(scope);
    }
    if (StarScope_TestFlags(scope, STAR_SCOPE_FLAG_SCROLLED) != 0) {
        DisplayLayer_SetScroll(scope->sky_layer, scope->scroll_x, scope->scroll_y);
        StarScope_ClearFlags(scope, STAR_SCOPE_FLAG_SCROLLED);
        int rows = star_scope_rows_past_edge(scope->scroll_y);
        if (rows != scope->hidden_rows) {
            scope->hidden_rows = (s16) rows;
            StarScope_SetFlags(scope, STAR_SCOPE_FLAG_PAINTED);
        }
    }
    if (StarScope_TestFlags(scope, STAR_SCOPE_FLAG_PAINTED) != 0) {
        MI_CpuCopy8(scope->sky, scope->shown, sizeof(scope->sky));
        int rows = scope->hidden_rows;
        if (rows > 0) {
            star_scope_blank_rows(scope, 0, rows);
        } else if (rows < 0) {
            star_scope_blank_rows(scope, rows + 32, -rows);
        }
        LayerTask_QueueScreen(&scope->task, (int) (uintptr_t) scope->shown, scope->sky_layer, sizeof(scope->shown), 0);
        StarScope_ClearFlags(scope, STAR_SCOPE_FLAG_PAINTED);
    }
}
CLEAN_AS(func_ov127_02299e64, StarScope_Update)

/* func_ov127_02299f90: the OBJs' palettes 5-9 and characters 0xc0-0x13f loaded from the scope's
 * files. */
void StarScope_LoadObjGraphics(StarScope *scope)
{
    (void) scope;
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov127_0229b634, heap, 8, 5, 5, 9);
    DisplayLayer_LoadCharsFromFile(data_ov127_0229b64c, heap, 8, 0xc0, 0xc0, 0x13f);
}
CLEAN_AS(func_ov127_02299f90, StarScope_LoadObjGraphics)

/* func_ov127_02299fd4: the scope's own layer `layer`: its palettes 8-11 (from the file's 4) and
 * characters 0x20-0xbf, and its screen read into `scope` and loaded. */
void StarScope_LoadScopeLayer(StarScope *scope, u8 layer, int unused)
{
    (void) unused;
    Heap *heap = data_021fbe94;
    scope->scope_layer = layer;
    DisplayLayer_LoadPalettesFromFile(data_ov127_0229b664, heap, scope->scope_layer, 4, 8, 0xb);
    DisplayLayer_LoadCharsFromFile(data_ov127_0229b67c, heap, scope->scope_layer, 0x20, 0x20, 0xbf);
    RomFile_Read(data_ov127_0229b694, scope->scope, sizeof(scope->scope));
    DisplayLayer_LoadScreen(scope->scope, scope->scope_layer, sizeof(scope->scope), 0);
}
CLEAN_AS(func_ov127_02299fd4, StarScope_LoadScopeLayer)

/* func_ov127_0229a04c: the sky's layer `layer`: its control (a 512 x 256 screen), characters
 * 0x10-0x1f, and the sky's screen read into `sky`, the kept constellations painted into it
 * (main's Constellations_PaintAll) and loaded. */
void StarScope_LoadSkyLayer(StarScope *scope, u8 layer)
{
    scope->sky_layer = layer;
    DisplayLayer_SetBgControl(scope->sky_layer, 1, 0, 0);
    DisplayLayer_LoadCharsFromFile(data_ov127_0229b6ac, data_021fbe94, scope->sky_layer, 0x10, 0x10, 0x1f);
    RomFile_Read(data_ov127_0229b6c0, scope->sky, sizeof(scope->sky));
    Constellations_PaintAll(scope->sky);
    DisplayLayer_LoadScreen(scope->sky, scope->sky_layer, sizeof(scope->sky), 0);
}
CLEAN_AS(func_ov127_0229a04c, StarScope_LoadSkyLayer)

/* func_ov127_0229a0bc: no flags, the view at the sky's top left with no rows blanked and no
 * bounce. */
void StarScope_Reset(StarScope *scope)
{
    scope->flags = 0;
    scope->scroll_x = 0;
    scope->scroll_y = 0;
    scope->hidden_rows = 0;
    scope->bounce = 0;
}
CLEAN_AS(func_ov127_0229a0bc, StarScope_Reset)

/* func_ov127_0229a0e8: the destructor: nothing to do. */
void StarScope_Destruct(StarScope *scope)
{
    (void) scope;
}
CLEAN_AS(func_ov127_0229a0e8, StarScope_Destruct)

/* func_ov127_0229a0ec: the constructor: the layer task's. */
StarScope *StarScope_Construct(StarScope *scope)
{
    LayerTask_Construct(&scope->task);
    return scope;
}
CLEAN_AS(func_ov127_0229a0ec, StarScope_Construct)
