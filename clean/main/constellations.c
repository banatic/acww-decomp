/* The players' constellations in the night sky (constellations.h). */
#include "constellations.h"

#include "clean.h"
#include "main/overlay_slots.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/text_string.h"
#include "date_time.h"
#include "exchange_block.h"
#include "main_random.h"
#include "ov127/star_scope.h"
#include "player_id.h"
#include "sky.h"
#include "text_base.h"

static_assert(sizeof(DesignCreator) == 0x1e, "constellation creator");
static_assert(sizeof(Constellation) == 0x4a, "constellation");
static_assert(offsetof(ConstellationStore, kept) == 0x4a0, "constellation store");
static_assert(offsetof(ConstellationStore, unseen) == 0x4a2, "constellation store");

/* The sky map: two screens of 32 x 32 tiles side by side, 0x200 pixels round. */
#define CONSTELLATIONS_SKY_TILES 0x800
#define CONSTELLATIONS_SCREEN_COLUMNS 32
#define CONSTELLATIONS_SCREEN_TILES 0x400
#define CONSTELLATIONS_COLUMNS 64
#define CONSTELLATIONS_ROWS 32
#define CONSTELLATIONS_SKY_WIDTH 0x200
#define CONSTELLATIONS_TILE_SIZE 8
/* A sky map entry: the tile in bits 0-9, the palette in bits 12-15. */
#define CONSTELLATIONS_TILE_MASK 0x3ff
#define CONSTELLATIONS_PALETTE_SHIFT 12
/* The tiles that draw a star, the palette of a constellation's stars, and the empty sky (tile
 * 0x10 in palette 4) a star left out of every constellation becomes. */
#define CONSTELLATIONS_FIRST_STAR_TILE 0x13
#define CONSTELLATIONS_LAST_STAR_TILE 0x1f
#define CONSTELLATIONS_STAR_PALETTE 7
#define CONSTELLATIONS_EMPTY_SKY 0x4010
/* A piece's stars: up to four (column, row) pairs, a column of 0xff ending them. */
#define CONSTELLATIONS_PIECE_STARS 4
#define CONSTELLATIONS_PIECE_END 0xff
/* The screen's middle, and the part of the screen a constellation's middle must be in to be
 * in view. */
#define CONSTELLATIONS_SCREEN_MIDDLE_X 0x80
#define CONSTELLATIONS_SCREEN_MIDDLE_Y 0x60
#define CONSTELLATIONS_VIEW_LEFT 0x40
#define CONSTELLATIONS_VIEW_RIGHT 0xc0
#define CONSTELLATIONS_VIEW_TOP 0x10
#define CONSTELLATIONS_VIEW_BOTTOM 0x88
/* The stars show from 18:00 to 5:59. */
#define CONSTELLATIONS_DAY_START 6
#define CONSTELLATIONS_NIGHT_START 18

/* The constellations kept, the draft's holder (the draft is at 0x100 of it), the columns
 * marked by Constellations_Center (one bit each) and the pieces' stars. */
extern ConstellationStore data_021f2b04;
extern u8 data_021ee418[];
extern u32 data_021f4b08[2];
extern const u8 data_020e42a0[];
/* Overlay 127, which judges a draft. */
extern char SDK_OVERLAY_ov127_ID;

/* One bit, shifted as the ARM shifts by a register: by the low byte, nothing left past 31. */
static u32 constellations_bit(int shift)
{
    u32 amount = (u32) shift & 0xffu;
    return amount < 32 ? 1u << amount : 0;
}

static ConstellationStore *constellations_store(int address)
{
    return (ConstellationStore *) (uintptr_t) (u32) address;
}

/* Constellation `number` of the store at `address`, kept or not. */
static Constellation *constellations_slot(int address, int number)
{
    return (Constellation *) (uintptr_t) ((u32) address + (u32) number * sizeof(Constellation));
}

/* The pieces of the constellation at `address`. */
static const u16 *constellations_pieces(int address)
{
    return (const u16 *) (uintptr_t) ((u32) address + offsetof(Constellation, pieces));
}

/* func_020b0f54: the sky map `map` readied: the kept constellations' stars in their palette,
 * and every other star replaced by empty sky. */
void Constellations_MarkSkyMap(u16 *map)
{
    Constellations_PaintAll(map);
    for (int i = 0; i < CONSTELLATIONS_SKY_TILES; i++) {
        if (Constellations_IsStarTile(map[i] & CONSTELLATIONS_TILE_MASK) != 0 &&
            (map[i] >> CONSTELLATIONS_PALETTE_SHIFT) != CONSTELLATIONS_STAR_PALETTE) {
            map[i] = CONSTELLATIONS_EMPTY_SKY;
        }
    }
}
CLEAN_AS(func_020b0f54, Constellations_MarkSkyMap)

/* func_020b0fa0: every kept constellation's stars in the stars' palette. */
void Constellations_PaintAll(u16 *map)
{
    for (int i = 0; i < CONSTELLATIONS_COUNT; i++) {
        int constellation = Constellations_At(i);
        if (constellation != 0) {
            Constellations_Paint(map, (const Constellation *) (uintptr_t) (u32) constellation, CONSTELLATIONS_STAR_PALETTE);
        }
    }
}
CLEAN_AS(func_020b0fa0, Constellations_PaintAll)

/* func_020b0fc8: the constellation's stars in palette `palette`. */
void Constellations_Paint(u16 *map, const Constellation *constellation, int palette)
{
    for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
        u16 piece = constellation->pieces[i];
        if (piece != CONSTELLATIONS_NO_PIECE) {
            Constellations_PaintPiece(map, piece, palette);
        }
    }
}
CLEAN_AS(func_020b0fc8, Constellations_Paint)

/* func_020b0ffc: the piece's stars in palette `palette` (its low four bits). */
void Constellations_PaintPiece(u16 *map, int piece, int palette)
{
    const u8 *star = Constellations_PieceStars((unsigned int) piece);
    int high = (palette & 0xf) << CONSTELLATIONS_PALETTE_SHIFT;
    for (int i = 0; i < CONSTELLATIONS_PIECE_STARS; i++, star += 2) {
        if (star[0] == CONSTELLATIONS_PIECE_END) {
            break;
        }
        int index = Constellations_MapIndex(star[0], star[1]);
        map[index] = (u16) ((map[index] & 0xfff) | high);
    }
}
CLEAN_AS(func_020b0ffc, Constellations_PaintPiece)

/* func_020b1050: the sky map entry of a tile, the columns from 32 on being the second screen. */
int Constellations_MapIndex(int column, int row)
{
    int screen = 0;
    if (column >= CONSTELLATIONS_SCREEN_COLUMNS) {
        screen = CONSTELLATIONS_SCREEN_TILES;
        column -= CONSTELLATIONS_SCREEN_COLUMNS;
    }
    return screen + row * CONSTELLATIONS_SCREEN_COLUMNS + column;
}
CLEAN_AS(func_020b1050, Constellations_MapIndex)

/* func_020b1068: whether the tile draws a star. */
int Constellations_IsStarTile(int tile)
{
    return tile >= CONSTELLATIONS_FIRST_STAR_TILE && tile <= CONSTELLATIONS_LAST_STAR_TILE;
}
CLEAN_AS(func_020b1068, Constellations_IsStarTile)

/* func_020b1078: whether a kept constellation other than number `except` has the name (trailing
 * spaces left out). */
int Constellations_NameTaken(const u16 *name, int except)
{
    for (int i = 0; i < CONSTELLATIONS_COUNT; i++) {
        if (i == except) {
            continue;
        }
        int constellation = Constellations_Get(i);
        if (constellation == 0) {
            continue;
        }
        if (TextString_EqualTrimmed(name, ((const Constellation *) (uintptr_t) (u32) constellation)->name,
                                    CONSTELLATIONS_NAME_LENGTH) != 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_020b1078, Constellations_NameTaken)

/* func_020b10b8: the draft, when it has pieces, kept (Constellations_Add); a draft that uses a
 * piece twice, or that was kept, is emptied. */
void Constellations_FileDraft(void)
{
    void *holder = data_021ee418;
    if (ExchangeBlock_IsSendable(holder) == 0) {
        return;
    }
    Constellation *draft = (Constellation *) (uintptr_t) ExchangeBlock_Constellation(holder);
    int pieces = 0;
    for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
        if (draft->pieces[i] == CONSTELLATIONS_NO_PIECE) {
            continue;
        }
        pieces++;
        for (int j = 0; j < i; j++) {
            if (draft->pieces[i] == draft->pieces[j]) {
                Constellations_Clear(draft);
                return;
            }
        }
    }
    if (pieces != 0 && Constellations_Add(draft) != 0) {
        Constellations_Clear(draft);
    }
}
CLEAN_AS(func_020b10b8, Constellations_FileDraft)

/* func_020b1130: the draft emptied, then made a copy of a kept constellation drawn at random,
 * when there is one. */
void Constellations_DraftRandom(void)
{
    Constellation *draft =
        (Constellation *) (uintptr_t) (ExchangeBlock_Constellation((ExchangeBlock *) (void *) data_021ee418));
    Constellations_Clear(draft);
    int kept = 0;
    ConstellationStore *store = constellations_store(Constellations_StoreAddress());
    for (int i = 0; i < CONSTELLATIONS_COUNT; i++) {
        if (Constellations_IsKept(store, i) != 0) {
            kept++;
        }
    }
    if (kept == 0) {
        return;
    }
    int skip = (int) MainRandom_Below(kept);
    for (int i = 0; i < CONSTELLATIONS_COUNT; i++) {
        if (Constellations_IsKept(store, i) == 0) {
            continue;
        }
        if (skip > 0) {
            skip--;
        } else {
            Constellations_Copy(draft, (const Constellation *) (uintptr_t) (u32) Constellations_Get(i));
            return;
        }
    }
}
CLEAN_AS(func_020b1130, Constellations_DraftRandom)

/* func_020b11a4: the constellation kept in the first free place, marked new, when there is a
 * place, no kept constellation has its name and overlay 127 accepts it; whether it was. */
int Constellations_Add(Constellation *constellation)
{
    int number = Constellations_FreeSlot();
    if (number == -1) {
        return 0;
    }
    if (Constellations_NameTaken(constellation->name, -1) != 0) {
        return 0;
    }
    Constellations_LoadJudge();
    int accepted = StarScope_StarsAreFree(constellation);
    Constellations_ReleaseJudge();
    if (accepted != 0) {
        Constellations_Put(constellation, number, 1);
    }
    return accepted;
}
CLEAN_AS(func_020b11a4, Constellations_Add)

/* func_020b11ec: overlay 127 released. */
void Constellations_ReleaseJudge(void)
{
    OverlaySlots_Release((u8) (uintptr_t) &SDK_OVERLAY_ov127_ID);
}
CLEAN_AS(func_020b11ec, Constellations_ReleaseJudge)

/* func_020b11fc: overlay 127 loaded. */
void Constellations_LoadJudge(void)
{
    OverlaySlots_Load((u8) (uintptr_t) &SDK_OVERLAY_ov127_ID);
}
CLEAN_AS(func_020b11fc, Constellations_LoadJudge)

/* func_020b120c: at night, the kept constellation in view whose middle is nearest the screen's,
 * the first of equals; -1 by day or without one. */
int Constellations_Nearest(void)
{
    DateTime now = {0};
    DateTime_Now(&now);
    if (now.hour >= CONSTELLATIONS_DAY_START && now.hour < CONSTELLATIONS_NIGHT_START) {
        return -1;
    }
    int scroll_x = Sky_StarsX();
    int scroll_y = Sky_StarsY();
    int nearest = -1;
    int nearest_distance = 0;
    for (int i = 0; i < CONSTELLATIONS_COUNT; i++) {
        int constellation = Constellations_Get(i);
        if (constellation == 0) {
            continue;
        }
        int x, y;
        Constellations_Center(constellations_pieces(constellation), &x, &y);
        if (x < scroll_x) {
            x += CONSTELLATIONS_SKY_WIDTH;
        }
        if (Constellations_InView(scroll_x, scroll_y, x, y) == 0) {
            continue;
        }
        int dy = y - (scroll_y + CONSTELLATIONS_SCREEN_MIDDLE_Y);
        int dx = x - (scroll_x + CONSTELLATIONS_SCREEN_MIDDLE_X);
        int distance = dx * dx + dy * dy;
        if (nearest == -1 || nearest_distance > distance) {
            nearest = i;
            nearest_distance = distance;
        }
    }
    return nearest;
}
CLEAN_AS(func_020b120c, Constellations_Nearest)

/* func_020b12b0: whether the point (x, y) of the sky lies in the middle part of the screen when
 * the sky is scrolled to (scroll_x, scroll_y). */
int Constellations_InView(int scroll_x, int scroll_y, int x, int y)
{
    if (y < scroll_y + CONSTELLATIONS_VIEW_TOP || y > scroll_y + CONSTELLATIONS_VIEW_BOTTOM) {
        return 0;
    }
    if (x < scroll_x + CONSTELLATIONS_VIEW_LEFT || x > scroll_x + CONSTELLATIONS_VIEW_RIGHT) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_020b12b0, Constellations_InView)

/* func_020b12e0: the time at which the sky shows constellation `number` in the screen's middle
 * (func_020ba3bc).
 * QUIRK: for a constellation not kept the pieces are read from address 0x2a. */
void Constellations_TimeInView(DateTime *when, int number)
{
    int x, y;
    Constellations_Center(constellations_pieces(Constellations_Get(number)), &x, &y);
    Sky_TimeForStarScroll(when, x - CONSTELLATIONS_SCREEN_MIDDLE_X, y - CONSTELLATIONS_SCREEN_MIDDLE_Y);
}
CLEAN_AS(func_020b12e0, Constellations_TimeInView)

/* func_020b1310: no constellation new. */
void Constellations_ClearNew(void)
{
    constellations_store(Constellations_StoreAddress())->unseen = 0;
}
CLEAN_AS(func_020b1310, Constellations_ClearNew)

/* func_020b1328: the new constellation to `*number` (-1 without one), unmarking those no longer
 * kept on the way: 0 without one, 1 for one, 2 as soon as a second is seen. */
int Constellations_TakeNew(int *number)
{
    *number = -1;
    ConstellationStore *store = constellations_store(Constellations_StoreAddress());
    for (int i = 0; i < CONSTELLATIONS_COUNT; i++) {
        u32 mask = 1u << i;
        if ((store->unseen & mask) == 0) {
            continue;
        }
        if (Constellations_IsKept(store, i) != 0) {
            if (*number != -1) {
                return 2;
            }
            *number = i;
        } else {
            store->unseen = (u16) (store->unseen & ~mask);
        }
    }
    return *number == -1 ? 0 : 1;
}
CLEAN_AS(func_020b1328, Constellations_TakeNew)

/* func_020b1394: a kept constellation's name into the 8-bit text object `text`; whether it is
 * kept. */
int Constellations_NameToText(void *text, int number)
{
    u32 wide[0x1c / sizeof(u32)];

    if (Constellations_IsKept(constellations_store(Constellations_StoreAddress()), number) == 0) {
        return 0;
    }
    const Constellation *constellation = (const Constellation *) (uintptr_t) (u32) Constellations_Get(number);
    ConstellationsWideName_Construct((ConstellationsWideName *) wide);
    TextBase_SetWide(wide, constellation->name, CONSTELLATIONS_NAME_LENGTH);
    TextBase_WideToBytes(text, (WideTextBase *) wide, 0, 0);
    ConstellationsWideName_Destruct((ConstellationsWideName *) wide);
    return 1;
}
CLEAN_AS(func_020b1394, Constellations_NameToText)

/* func_020b13e4: a kept constellation's name, or no characters. */
void Constellations_GetName(u16 *name, int number)
{
    int store = Constellations_StoreAddress();
    TextString_ClearChars(name, CONSTELLATIONS_NAME_LENGTH);
    if (Constellations_IsKept(constellations_store(store), number) != 0) {
        TextString_CopyChars(constellations_slot(store, number)->name, name, CONSTELLATIONS_NAME_LENGTH);
    }
}
CLEAN_AS(func_020b13e4, Constellations_GetName)

/* func_020b141c: constellation `number` named, kept or not. */
void Constellations_SetName(const u16 *name, int number)
{
    int store = Constellations_StoreAddress();
    TextString_CopyChars(name, constellations_slot(store, number)->name, CONSTELLATIONS_NAME_LENGTH);
}
CLEAN_AS(func_020b141c, Constellations_SetName)

/* func_020b1444: this system's player as the maker. */
void Constellations_SetCreator(DesignCreator *creator)
{
    *creator = *PlayerRecord_Player(PlayerRecords_Current());
}
CLEAN_AS(func_020b1444, Constellations_SetCreator)

/* func_020b1498: the address of kept constellation `number`, or 0 (as Constellations_Get). */
int Constellations_At(int number)
{
    int store = Constellations_StoreAddress();
    if (Constellations_IsKept(constellations_store(store), number) == 0) {
        return 0;
    }
    return store + number * (int) sizeof(Constellation);
}
CLEAN_AS(func_020b1498, Constellations_At)

/* func_020b14c0: constellation `number` no longer kept nor new. */
void Constellations_Remove(int number)
{
    ConstellationStore *store = constellations_store(Constellations_StoreAddress());
    Constellations_ClearKept(store, number);
    store->unseen = (u16) (store->unseen & ~constellations_bit(number));
}
CLEAN_AS(func_020b14c0, Constellations_Remove)

/* func_020b14ec: a copy of `constellation` kept as number `number`, marked new if `is_new`. */
void Constellations_Put(const Constellation *constellation, int number, int is_new)
{
    int store = Constellations_StoreAddress();
    Constellations_SetKept(constellations_store(store), number);
    Constellations_Copy(constellations_slot(store, number), constellation);
    if (is_new != 0) {
        constellations_store(store)->unseen = (u16) (constellations_store(store)->unseen | constellations_bit(number));
    }
}
CLEAN_AS(func_020b14ec, Constellations_Put)

/* func_020b1530: the address of kept constellation `number`, or 0. */
int Constellations_Get(int number)
{
    int store = Constellations_StoreAddress();
    if (Constellations_IsKept(constellations_store(store), number) == 0) {
        return 0;
    }
    return store + number * (int) sizeof(Constellation);
}
CLEAN_AS(func_020b1530, Constellations_Get)

/* func_020b1558: the free places. */
int Constellations_CountFree(void)
{
    ConstellationStore *store = constellations_store(Constellations_StoreAddress());
    int free_places = 0;
    for (int i = 0; i < CONSTELLATIONS_COUNT; i++) {
        if (Constellations_IsKept(store, i) == 0) {
            free_places++;
        }
    }
    return free_places;
}
CLEAN_AS(func_020b1558, Constellations_CountFree)

/* func_020b1580: the first free place, or -1. */
int Constellations_FreeSlot(void)
{
    ConstellationStore *store = constellations_store(Constellations_StoreAddress());
    for (int i = 0; i < CONSTELLATIONS_COUNT; i++) {
        if (Constellations_IsKept(store, i) == 0) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_020b1580, Constellations_FreeSlot)

/* func_020b15b0: the store's address. */
int Constellations_StoreAddress(void)
{
    return (int) (uintptr_t) &data_021f2b04;
}
CLEAN_AS(func_020b15b0, Constellations_StoreAddress)

/* func_020b15b8: the middle of the constellation's stars on the sky, in pixels. Across, the sky
 * wraps round: from the first column with a star, the run of columns that holds it (gaps of a
 * single column bridged) is followed back and forward, and its middle taken; stars spread all
 * the way round count from column 0. Down, the middle of the top and bottom rows. Without
 * stars, (0x204, 0x80). */
void Constellations_Center(const u16 *pieces, int *x, int *y)
{
    Constellations_ClearColumns();
    int top = CONSTELLATIONS_ROWS;
    int bottom = -1;
    for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
        if (pieces[i] == CONSTELLATIONS_NO_PIECE) {
            continue;
        }
        const u8 *star = Constellations_PieceStars(pieces[i]);
        for (int k = 0; k < CONSTELLATIONS_PIECE_STARS; k++, star += 2) {
            if (star[0] == CONSTELLATIONS_PIECE_END) {
                break;
            }
            Constellations_MarkColumn(star[0]);
            if (top > star[1]) {
                top = star[1];
            }
            if (bottom < star[1]) {
                bottom = star[1];
            }
        }
    }

    int first = 0;
    while (first < CONSTELLATIONS_COLUMNS && Constellations_ColumnMarked(first) == 0) {
        first++;
    }

    /* Back from the first column, to where two empty columns in a row end the run. */
    int start = first;
    int column = (first + CONSTELLATIONS_COLUMNS - 1) % CONSTELLATIONS_COLUMNS;
    int ended = 0;
    int gap = 0;
    while (ended == 0 && column != start) {
        if (Constellations_ColumnMarked(column) != 0) {
            gap = 0;
            start = column;
        } else if (gap != 0) {
            ended = 1;
        } else {
            gap = 1;
        }
        column = (column + CONSTELLATIONS_COLUMNS - 1) % CONSTELLATIONS_COLUMNS;
    }

    int end;
    if (ended != 0) {
        /* And forward from it the same way. */
        end = first;
        column = (first + 1) % CONSTELLATIONS_COLUMNS;
        ended = 0;
        gap = 0;
        while (ended == 0 && column != end) {
            if (Constellations_ColumnMarked(column) != 0) {
                gap = 0;
                end = column;
            } else if (gap != 0) {
                ended = 1;
            } else {
                gap = 1;
            }
            column = (column + 1) % CONSTELLATIONS_COLUMNS;
        }
    } else {
        start = 0;
        end = 0;
    }

    int half_tile = CONSTELLATIONS_TILE_SIZE / 2;
    if (start <= end) {
        *x = (start + end + 1) * half_tile;
    } else {
        *x = ((start + CONSTELLATIONS_COLUMNS + 1 + end) * half_tile) & (CONSTELLATIONS_SKY_WIDTH - 1);
    }
    *y = (top * CONSTELLATIONS_TILE_SIZE + (bottom + 1) * CONSTELLATIONS_TILE_SIZE) / 2;
}
CLEAN_AS(func_020b15b8, Constellations_Center)

/* func_020b16fc: whether Constellations_Center marked the column. */
int Constellations_ColumnMarked(int column)
{
    if (column >= 32) {
        return (data_021f4b08[1] & constellations_bit(column - 32)) != 0;
    }
    return (data_021f4b08[0] & constellations_bit(column)) != 0;
}
CLEAN_AS(func_020b16fc, Constellations_ColumnMarked)

/* func_020b1730 */
void Constellations_MarkColumn(int column)
{
    if (column >= 32) {
        data_021f4b08[1] |= constellations_bit(column - 32);
    } else {
        data_021f4b08[0] |= constellations_bit(column);
    }
}
CLEAN_AS(func_020b1730, Constellations_MarkColumn)

/* func_020b1758 */
void Constellations_ClearColumns(void)
{
    data_021f4b08[1] = 0;
    data_021f4b08[0] = 0;
}
CLEAN_AS(func_020b1758, Constellations_ClearColumns)

/* func_020b1768: piece `piece`'s stars (eight bytes each in the table). */
const u8 *Constellations_PieceStars(unsigned int piece)
{
    return (const u8 *) (uintptr_t) ((u32) (uintptr_t) data_020e42a0 + piece * 8u);
}
CLEAN_AS(func_020b1768, Constellations_PieceStars)

/* ---- The name's two text classes */

static_assert(offsetof(ConstellationsWideName, text) == 0xe, "wide name characters");
static_assert(sizeof(ConstellationsWideName) == 0x1c, "wide name");
static_assert(offsetof(ConstellationsLabel, text) == 0x12, "label characters");
static_assert(sizeof(ConstellationsLabel) == 0x20, "label");

extern const TextVtable data_020e4278; /* the wide name's vtable */
extern const TextVtable data_020e4290; /* the label's vtable */

extern void Heap_OperatorDeleteB(void *block);

/* The vector helpers are handed the game's own constructor and destructor of a
 * constellation, declared as the helpers call them (their results are not used). */
extern void func_020b1a64(void *constellation);
extern void func_020b1a54(void *constellation);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_020b18bc (vtable entry 3): the address of the characters. */
int ConstellationsWideName_Buffer(int text)
{
    return (int) ((u32) text + offsetof(ConstellationsWideName, text));
}
CLEAN_AS(func_020b18bc, ConstellationsWideName_Buffer)

/* func_020b18c0 (vtable entry 2) */
int ConstellationsWideName_Capacity(void)
{
    return CONSTELLATIONS_NAME_LENGTH;
}
CLEAN_AS(func_020b18c0, ConstellationsWideName_Capacity)

/* func_020b18c4 (vtable entry 1) */
ConstellationsWideName *ConstellationsWideName_DestructDelete(ConstellationsWideName *text)
{
    text->vtable = &data_020e4278;
    TextBase_WideDestruct(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_020b18c4, ConstellationsWideName_DestructDelete)

/* func_020b18e4 (vtable entry 0) */
ConstellationsWideName *ConstellationsWideName_Destruct(ConstellationsWideName *text)
{
    text->vtable = &data_020e4278;
    TextBase_WideDestruct(text);
    return text;
}
CLEAN_AS(func_020b18e4, ConstellationsWideName_Destruct)

/* func_020b18fc */
ConstellationsWideName *ConstellationsWideName_Construct(ConstellationsWideName *text)
{
    TextBase_WideConstruct(text);
    text->vtable = &data_020e4278;
    return text;
}
CLEAN_AS(func_020b18fc, ConstellationsWideName_Construct)

/* func_020b1914 (vtable entry 3): the address of the characters. */
int ConstellationsLabel_Buffer(int label)
{
    return (int) ((u32) label + offsetof(ConstellationsLabel, text));
}
CLEAN_AS(func_020b1914, ConstellationsLabel_Buffer)

/* func_020b1918 (vtable entry 2) */
int ConstellationsLabel_Capacity(void)
{
    return CONSTELLATIONS_LABEL_CAPACITY;
}
CLEAN_AS(func_020b1918, ConstellationsLabel_Capacity)

/* func_020b191c (vtable entry 1) */
ConstellationsLabel *ConstellationsLabel_DestructDelete(ConstellationsLabel *label)
{
    label->vtable = &data_020e4290;
    TextBase_Destruct((TextBase *) label);
    Heap_OperatorDeleteB(label);
    return label;
}
CLEAN_AS(func_020b191c, ConstellationsLabel_DestructDelete)

/* func_020b193c (vtable entry 0) */
ConstellationsLabel *ConstellationsLabel_Destruct(ConstellationsLabel *label)
{
    label->vtable = &data_020e4290;
    TextBase_Destruct((TextBase *) label);
    return label;
}
CLEAN_AS(func_020b193c, ConstellationsLabel_Destruct)

/* func_020b1954: an empty label. */
ConstellationsLabel *ConstellationsLabel_Construct(ConstellationsLabel *label)
{
    TextBase_Construct(label);
    label->vtable = &data_020e4290;
    TextBase_Clear(label);
    return label;
}
CLEAN_AS(func_020b1954, ConstellationsLabel_Construct)

/* ---- The store */

/* func_020b1974: whether constellation `number` is kept. */
int Constellations_IsKept(const ConstellationStore *store, int number)
{
    return (store->kept & constellations_bit(number)) != 0;
}
CLEAN_AS(func_020b1974, Constellations_IsKept)

/* func_020b198c */
void Constellations_ClearKept(ConstellationStore *store, int number)
{
    store->kept = (u16) (store->kept & ~constellations_bit(number));
}
CLEAN_AS(func_020b198c, Constellations_ClearKept)

/* func_020b19a0 */
void Constellations_SetKept(ConstellationStore *store, int number)
{
    store->kept = (u16) (store->kept | constellations_bit(number));
}
CLEAN_AS(func_020b19a0, Constellations_SetKept)

/* func_020b19b4: none kept and none new (the state block's setting up, func_0209ef7c). */
void Constellations_ResetStore(ConstellationStore *store)
{
    store->kept = 0;
    store->unseen = 0;
}
CLEAN_AS(func_020b19b4, Constellations_ResetStore)

/* func_020b19c8: the list's destructor, each constellation destructed by the game's
 * func_020b1a54. */
ConstellationStore *Constellations_DestructList(ConstellationStore *store)
{
    __cxa_vec_cleanup(store->list, CONSTELLATIONS_COUNT, sizeof(Constellation), func_020b1a54);
    return store;
}
CLEAN_AS(func_020b19c8, Constellations_DestructList)

/* func_020b19e4: the list's constructor, with the game's func_020b1a64 and func_020b1a54. */
int Constellations_ConstructList(int store)
{
    __cxa_vec_ctor((void *) (uintptr_t) (u32) store, CONSTELLATIONS_COUNT, sizeof(Constellation), func_020b1a64,
                   func_020b1a54);
    return store;
}
CLEAN_AS(func_020b19e4, Constellations_ConstructList)

/* func_020b1a0c: `src` copied over `dst`. */
Constellation *Constellations_Copy(Constellation *dst, const Constellation *src)
{
    MI_CpuCopy8(src, dst, sizeof(Constellation));
    return dst;
}
CLEAN_AS(func_020b1a0c, Constellations_Copy)

/* func_020b1a24: no pieces, no name and no maker. */
void Constellations_Clear(Constellation *constellation)
{
    for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
        constellation->pieces[i] = CONSTELLATIONS_NO_PIECE;
    }
    TextString_ClearChars(constellation->name, CONSTELLATIONS_NAME_LENGTH);
    PlayerId_Clear(&constellation->creator);
}
CLEAN_AS(func_020b1a24, Constellations_Clear)

/* func_020b1a54: a constellation's destructor (its maker's). */
Constellation *Constellations_DestructOne(Constellation *constellation)
{
    PlayerId_Destruct(&constellation->creator);
    return constellation;
}
CLEAN_AS(func_020b1a54, Constellations_DestructOne)

/* func_020b1a64: a constellation's constructor (its maker's). */
int Constellations_ConstructOne(int constellation)
{
    PlayerId_Construct((DesignCreator *) (uintptr_t) (u32) constellation);
    return constellation;
}
CLEAN_AS(func_020b1a64, Constellations_ConstructOne)
