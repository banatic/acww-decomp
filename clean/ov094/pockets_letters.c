/* Overlay 094's letters object (pockets_letters.h): its sets of bits, the held letter's pick-up,
 * the places' letters and positions, their drawing, the touch and the popup's text. */
#include "pockets_letters.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/message_reader.h"
#include "main/oam_buffer.h"
#include "main/player_id.h"
#include "main/player_pockets.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/sliding_window.h"
#include "main/text_string.h"

static_assert(offsetof(PocketsLetters, filled) == 0x08 && offsetof(PocketsLetters, dimmed) == 0x18, "letters bits");
static_assert(offsetof(PocketsLetters, priority) == 0x20 && offsetof(PocketsLetters, lifted) == 0x24, "letters");
static_assert(offsetof(PocketsLetters, held_size) == 0x27 && sizeof(PocketsLetters) == 0x28, "letters size");
static_assert(sizeof(Letter) == 0x100, "letter");

/* The held letter's sizes at pick-up steps 0 to 3 (2, 4, 6, 8 tenths). */
extern const u8 data_ov094_0229bddc[];

/* The first places of the ten letters PocketsLetters_SetTenAt23 is given. */
#define POCKETS_LETTERS_TEN_FIRST 0x23
#define POCKETS_LETTERS_TEN 10

/* func_ov094_0229b110. REQUIRES: `bit` in 0-63 (the places use 0-0x36). */
int PocketsLetterBits_Test(PocketsBits *bits, int bit)
{
    return (bits->words[bit >> 5] & (1u << (bit & 31))) != 0;
}
CLEAN_AS(func_ov094_0229b110, PocketsLetterBits_Test)

/* func_ov094_0229b134. REQUIRES: `bit` in 0-63. */
void PocketsLetterBits_Clear(PocketsBits *bits, int bit)
{
    bits->words[bit >> 5] &= ~(1u << (bit & 31));
}
CLEAN_AS(func_ov094_0229b134, PocketsLetterBits_Clear)

/* func_ov094_0229b154. REQUIRES: `bit` in 0-63. */
void PocketsLetterBits_Set(PocketsBits *bits, int bit)
{
    bits->words[bit >> 5] |= 1u << (bit & 31);
}
CLEAN_AS(func_ov094_0229b154, PocketsLetterBits_Set)

/* func_ov094_0229b174 */
void PocketsLetterBits_ClearAll(PocketsBits *bits)
{
    for (int i = 0; i < 2; i++) {
        bits->words[i] = 0;
    }
}
CLEAN_AS(func_ov094_0229b174, PocketsLetterBits_ClearAll)

/* func_ov094_0229b184: the held letter's size at this step of the pick-up; full size once the
 * steps are over. */
int PocketsLetters_PickUpSize(PocketsLetters *letters)
{
    u8 step = letters->pickup_step;

    if (step >= POCKETS_LETTERS_PICKUP_STEPS) {
        return POCKETS_LETTERS_FULL_SIZE;
    }
    return data_ov094_0229bddc[step];
}
CLEAN_AS(func_ov094_0229b184, PocketsLetters_PickUpSize)

/* func_ov094_0229b19c: a step of the pick-up (the held letter shrinks to 8, 6, 4 and 2 tenths);
 * 1 once it is over, the letter back at full size. */
int PocketsLetters_StepPickUp(PocketsLetters *letters)
{
    if (letters->pickup_step != 0) {
        letters->pickup_step--;
        letters->held_size = (u8) PocketsLetters_PickUpSize(letters);
        return 0;
    }
    PocketsLetters_EndPickUp(letters);
    return 1;
}
CLEAN_AS(func_ov094_0229b19c, PocketsLetters_StepPickUp)

/* func_ov094_0229b1d0: the held letter at full size. */
void PocketsLetters_EndPickUp(PocketsLetters *letters)
{
    letters->held_size = POCKETS_LETTERS_FULL_SIZE;
}
CLEAN_AS(func_ov094_0229b1d0, PocketsLetters_EndPickUp)

/* func_ov094_0229b1d8: a pick-up of four steps started, the letter at full size. */
void PocketsLetters_StartPickUp(PocketsLetters *letters)
{
    letters->pickup_step = POCKETS_LETTERS_PICKUP_STEPS;
    letters->held_size = POCKETS_LETTERS_FULL_SIZE;
}
CLEAN_AS(func_ov094_0229b1d8, PocketsLetters_StartPickUp)

/* func_ov094_0229b1e8: the icon of `letter`: POCKETS_LETTERS_NO_ICON when its state is 0 (no
 * letter), else two by state from state 1, the second of the two when it carries an item. */
int PocketsLetters_IconOf(PocketsLetters *letters, const Letter *letter)
{
    int state = Letter_State(letter);
    int icon;

    (void) letters;
    if (state == 0) {
        return POCKETS_LETTERS_NO_ICON;
    }
    icon = (state - 1) * 2;
    if (Letter_Item(letter) != PLAYER_POCKETS_NO_ITEM) {
        icon++;
    }
    return icon;
}
CLEAN_AS(func_ov094_0229b1e8, PocketsLetters_IconOf)

/* func_ov094_0229b220: `list` kept, and its first `count` letters put at the places from
 * `first_place`: each place is filled when its letter has an icon. */
void PocketsLetters_SetList(PocketsLetters *letters, Letter *list, int first_place, int count)
{
    const Letter *letter;

    letters->letters = list;
    letter = letters->letters;
    for (int i = 0; i < count; i++, letter++) {
        if (PocketsLetters_IconOf(letters, letter) != POCKETS_LETTERS_NO_ICON) {
            PocketsLetterBits_Set(&letters->filled, first_place + i);
        } else {
            PocketsLetterBits_Clear(&letters->filled, first_place + i);
        }
    }
}
CLEAN_AS(func_ov094_0229b220, PocketsLetters_SetList)

/* func_ov094_0229b274: the ten letters of `list` at places 0x23-0x2c. */
void PocketsLetters_SetTenAt23(PocketsLetters *letters, Letter *list)
{
    PocketsLetters_SetList(letters, list, POCKETS_LETTERS_TEN_FIRST, POCKETS_LETTERS_TEN);
}
CLEAN_AS(func_ov094_0229b274, PocketsLetters_SetTenAt23)

/* The places' groups: the current player's ten letters, the page of 25 and the two lists of ten
 * at 0x23 and 0x2d (each of the last three from the list last given). */
#define POCKETS_LETTERS_POCKETS 10
#define POCKETS_LETTERS_PAGE_FIRST 10
#define POCKETS_LETTERS_PAGE 25
#define POCKETS_LETTERS_OTHER_FIRST 0x2d
/* The places of the pockets are in two columns, those of the page in five, those of the lists
 * of ten in two. Each row is 24 pixels below the one before it, from y 0x3c. */
#define POCKETS_LETTERS_TOP 0x3c
#define POCKETS_LETTERS_ROW 24
#define POCKETS_LETTERS_PAGE_COLUMNS 5
#define POCKETS_LETTERS_POCKETS_LEFT 0xcc
#define POCKETS_LETTERS_POCKETS_RIGHT 0xe4
#define POCKETS_LETTERS_LISTS_LEFT 0x6c
#define POCKETS_LETTERS_LISTS_RIGHT 0x84
/* A place is not drawn when its x is left of this (off the screen). */
#define POCKETS_LETTERS_LEFTMOST (-24)
#define POCKETS_LETTERS_OBJ_MARGIN 8 /* the 32 x 32 OBJs round a 16 x 16 one */
#define POCKETS_LETTERS_OWN_PALETTE (-1)
#define POCKETS_LETTERS_DIMMED_PALETTE 0xe
#define POCKETS_LETTERS_LIFT_START 2
#define POCKETS_LETTERS_SCALE_ONE 0x1000
#define POCKETS_LETTERS_TILE_MASK 0x3ffu /* in attr2 */
#define POCKETS_LETTERS_PALETTE_SHIFT 12 /* in attr2 */
/* The touch finds a place whose position is within (x - 20, x + 4) and (y - 20, y + 4). */
#define POCKETS_LETTERS_TOUCH_BEFORE 20
#define POCKETS_LETTERS_TOUCH_AFTER 4
/* The touch looks among the places 0x2d-0x36 only from x 0x60 to 0xa0, among the pockets only
 * from x 0xc0. */
#define POCKETS_LETTERS_TOUCH_LIST_MIN_X 0x60
#define POCKETS_LETTERS_TOUCH_LIST_MAX_X 0xa0
#define POCKETS_LETTERS_TOUCH_POCKETS_MIN_X 0xc0
/* PocketsLetters_DimByState's bits, and the palettes it reloads for them. */
#define POCKETS_LETTERS_DIM_WRITTEN 1   /* states 1 and 4 (palette 4) */
#define POCKETS_LETTERS_DIM_RECEIVED 2  /* states 2, 3, 5 and 6 (palette 5) */
#define POCKETS_LETTERS_DIM_VILLAGERS 4 /* states 7 and 8 (palette 6) */
#define POCKETS_LETTERS_DIM_BOTTLE 8    /* state 4 */
#define POCKETS_LETTERS_PALETTE_WRITTEN 4
#define POCKETS_LETTERS_PALETTE_RECEIVED 5
#define POCKETS_LETTERS_PALETTE_VILLAGERS 6
#define POCKETS_LETTERS_PALETTE_FILE_FIRST 4
/* The menu messages of the popup's two lines. */
#define POCKETS_LETTERS_MESSAGE_FROM 0x4b
#define POCKETS_LETTERS_MESSAGE_FROM_TAG_0 0x3d
#define POCKETS_LETTERS_MESSAGE_NO_ADDRESSEE 0x43
#define POCKETS_LETTERS_MESSAGE_TO 0x3c
#define POCKETS_LETTERS_TAG_DELIVERED 0x11

static_assert(sizeof(PlayerIdText) == 0x20 && sizeof(SlidingWindowText) == 0x30, "popup texts");
static_assert(sizeof(TextLabel) == 0x6c, "popup labels");

/* The class's vtable. */
extern const u32 data_ov094_0229c114[];
/* The x of the page's five columns. */
extern const u8 data_ov094_0229c0ec[];
/* The letter's OBJ (a 16 x 16 OBJ whose tile and palette are set for each letter drawn), the OBJ
 * drawn round a filled place, the one under a lifted place and the one on a marked place. */
extern OamEntry data_ov094_0229c0f4;
extern const OamEntry data_ov094_0229c11c;
extern const OamEntry data_ov094_0229c124;
extern const OamEntry data_ov094_0229c12c;
/* The palette and the first tile of each of the 16 icons (PocketsLetters_IconOf). */
extern const u8 data_ov094_0229c0fc[];
extern const u16 data_ov094_0229c134[];
/* The lift's offsets by `lift` (-2, -3, -5 pixels). */
extern const u32 data_ov094_0229bde0[];
/* The menu message of the popup's first line, by the letter's tag. */
extern const u16 data_ov094_0229bdec[];
/* "menu/inventory/b_itm_ten0_obj.bpl" */
extern const char data_ov094_0229c154[];
extern Heap *data_021fbe94;

/* `attr2` with the bits `mask` << `shift` set to `value`. */
static u16 letters_attr2(u16 attr2, unsigned int value, unsigned int mask, int shift)
{
    return (u16) ((attr2 & ~(mask << shift)) | ((value & mask) << shift));
}

/* The current player's ten letters. */
static Letter *letters_pockets(void)
{
    return (Letter *) (void *) PlayerPockets_Letter(PlayerRecord_Pockets(PlayerRecords_Current()), 0);
}

static int in_group(int place, int first, int count)
{
    return place >= first && place < first + count;
}

/* func_ov094_0229b288: the 25 letters of a page of `list` at places 10-34. */
void PocketsLetters_SetPage(PocketsLetters *letters, Letter *list)
{
    PocketsLetters_SetList(letters, list, POCKETS_LETTERS_PAGE_FIRST, POCKETS_LETTERS_PAGE);
}
CLEAN_AS(func_ov094_0229b288, PocketsLetters_SetPage)

/* func_ov094_0229b29c: the ten letters of `list` at places 0x2d-0x36. */
void PocketsLetters_SetTenAt2d(PocketsLetters *letters, Letter *list)
{
    PocketsLetters_SetList(letters, list, POCKETS_LETTERS_OTHER_FIRST, POCKETS_LETTERS_TEN);
}
CLEAN_AS(func_ov094_0229b29c, PocketsLetters_SetTenAt2d)

/* func_ov094_0229b2b0: places 0-9 filled by the current player's ten letters (not kept as the
 * list: PocketsLetters_LetterAt finds them each time). */
void PocketsLetters_LoadPockets(PocketsLetters *letters)
{
    const Letter *letter = letters_pockets();

    for (int place = 0; place < POCKETS_LETTERS_POCKETS; place++, letter++) {
        if (PocketsLetters_IconOf(letters, letter) != POCKETS_LETTERS_NO_ICON) {
            PocketsLetterBits_Set(&letters->filled, place);
        } else {
            PocketsLetterBits_Clear(&letters->filled, place);
        }
    }
}
CLEAN_AS(func_ov094_0229b2b0, PocketsLetters_LoadPockets)

/* func_ov094_0229b30c: whether place `place` holds no letter. */
int PocketsLetters_IsEmpty(PocketsLetters *letters, int place)
{
    return PocketsLetterBits_Test(&letters->filled, place) == 0;
}
CLEAN_AS(func_ov094_0229b30c, PocketsLetters_IsEmpty)

/* func_ov094_0229b328: place `place`'s y on the screen; 0 for a number that is no place. */
int PocketsLetters_PlaceY(PocketsLetters *letters, int place)
{
    int row;

    (void) letters;
    if (in_group(place, 0, POCKETS_LETTERS_POCKETS)) {
        row = place / 2;
    } else if (in_group(place, POCKETS_LETTERS_PAGE_FIRST, POCKETS_LETTERS_PAGE)) {
        row = (place - POCKETS_LETTERS_PAGE_FIRST) / POCKETS_LETTERS_PAGE_COLUMNS;
    } else if (in_group(place, POCKETS_LETTERS_TEN_FIRST, POCKETS_LETTERS_TEN)) {
        row = (place - POCKETS_LETTERS_TEN_FIRST) / 2;
    } else if (in_group(place, POCKETS_LETTERS_OTHER_FIRST, POCKETS_LETTERS_TEN)) {
        row = (place - POCKETS_LETTERS_OTHER_FIRST) / 2;
    } else {
        return 0;
    }
    return POCKETS_LETTERS_TOP + POCKETS_LETTERS_ROW * row;
}
CLEAN_AS(func_ov094_0229b328, PocketsLetters_PlaceY)

/* func_ov094_0229b384: place `place`'s x on the screen; 0 for a number that is no place. */
int PocketsLetters_PlaceX(PocketsLetters *letters, int place)
{
    (void) letters;
    if (in_group(place, 0, POCKETS_LETTERS_POCKETS)) {
        return (place & 1) ? POCKETS_LETTERS_POCKETS_RIGHT : POCKETS_LETTERS_POCKETS_LEFT;
    }
    if (in_group(place, POCKETS_LETTERS_PAGE_FIRST, POCKETS_LETTERS_PAGE)) {
        return data_ov094_0229c0ec[(place - POCKETS_LETTERS_PAGE_FIRST) % POCKETS_LETTERS_PAGE_COLUMNS];
    }
    if (in_group(place, POCKETS_LETTERS_TEN_FIRST, POCKETS_LETTERS_TEN)) {
        return ((place - POCKETS_LETTERS_TEN_FIRST) & 1) ? POCKETS_LETTERS_LISTS_RIGHT : POCKETS_LETTERS_LISTS_LEFT;
    }
    if (in_group(place, POCKETS_LETTERS_OTHER_FIRST, POCKETS_LETTERS_TEN)) {
        return ((place - POCKETS_LETTERS_OTHER_FIRST) & 1) ? POCKETS_LETTERS_LISTS_RIGHT : POCKETS_LETTERS_LISTS_LEFT;
    }
    return 0;
}
CLEAN_AS(func_ov094_0229b384, PocketsLetters_PlaceX)

/* func_ov094_0229b3f0: place `place`, holding `letter`, drawn moved by (x, y), unless it is off
 * the screen's left: the mark when marked; when filled, the letter (raised by the lift's offset
 * when lifted) with the OBJ round it in the letter's palette, and for the lifted place the
 * lowered copy under it. A dimmed letter of state 4 (a bottle's the player wrote) is drawn in
 * palette 14; the other dimmed letters are dimmed by their palettes (PocketsLetters_DimByState).
 */
void PocketsLetters_DrawPlace(PocketsLetters *letters, const Letter *letter, int place, int x, int y)
{
    int at_x = x + PocketsLetters_PlaceX(letters, place);
    int at_y = y + PocketsLetters_PlaceY(letters, place);
    int palette;

    if (at_x < POCKETS_LETTERS_LEFTMOST) {
        return;
    }
    if (PocketsLetterBits_Test(&letters->marked, place)) {
        PocketsLetters_DrawMark(letters, at_x, at_y);
    }
    if (!PocketsLetterBits_Test(&letters->filled, place)) {
        return;
    }
    if (PocketsLetters_IsLifted(letters, (u8) place)) {
        int lift = (int) PocketsLetters_LiftOffset(letters);
        at_x += lift;
        at_y += lift;
    }
    if (PocketsLetters_IsDimmed(letters, (u8) place) && Letter_State(letter) == LETTER_STATE_BOTTLE_WRITTEN) {
        palette = POCKETS_LETTERS_DIMMED_PALETTE;
    } else {
        palette = PocketsLetters_PaletteOf(letters, letter);
    }
    PocketsLetters_DrawLetter(letters, at_x, at_y, palette, letter, NULL);
    PocketsLetters_DrawSurround(letters, at_x, at_y, palette, NULL);
    if (PocketsLetters_IsLifted(letters, (u8) place)) {
        PocketsLetters_DrawLowered(letters, at_x, at_y, NULL);
    }
}
CLEAN_AS(func_ov094_0229b3f0, PocketsLetters_DrawPlace)

/* func_ov094_0229b4c0: data_ov094_0229c124 centred on (x, y). */
void PocketsLetters_DrawLowered(PocketsLetters *letters, int x, int y, const OamAffine *params)
{
    OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, &data_ov094_0229c124, x - POCKETS_LETTERS_OBJ_MARGIN,
                            y - POCKETS_LETTERS_OBJ_MARGIN, POCKETS_LETTERS_OWN_PALETTE, letters->priority, params);
}
CLEAN_AS(func_ov094_0229b4c0, PocketsLetters_DrawLowered)

/* func_ov094_0229b4f0: data_ov094_0229c11c centred on (x, y), in `palette` (-1: its own). */
void PocketsLetters_DrawSurround(PocketsLetters *letters, int x, int y, int palette, const OamAffine *params)
{
    OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, &data_ov094_0229c11c, x - POCKETS_LETTERS_OBJ_MARGIN,
                            y - POCKETS_LETTERS_OBJ_MARGIN, palette, letters->priority, params);
}
CLEAN_AS(func_ov094_0229b4f0, PocketsLetters_DrawSurround)

/* func_ov094_0229b520: data_ov094_0229c12c centred on (x, y). */
int PocketsLetters_DrawMark(PocketsLetters *letters, int x, int y)
{
    return OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, &data_ov094_0229c12c, x - POCKETS_LETTERS_OBJ_MARGIN,
                                   y - POCKETS_LETTERS_OBJ_MARGIN, POCKETS_LETTERS_OWN_PALETTE, letters->priority, NULL);
}
CLEAN_AS(func_ov094_0229b520, PocketsLetters_DrawMark)

/* func_ov094_0229b550: `letter`'s icon drawn at (x, y): the letter's OBJ given palette `palette`
 * (its low four bits) and the icon's tile, then drawn; nothing for a letter without an icon. */
void PocketsLetters_DrawLetter(PocketsLetters *letters, int x, int y, int palette, const Letter *letter,
                               const OamAffine *params)
{
    int icon = PocketsLetters_IconOf(letters, letter);

    if (icon == POCKETS_LETTERS_NO_ICON) {
        return;
    }
    data_ov094_0229c0f4.attr2 = letters_attr2(data_ov094_0229c0f4.attr2, (u8) palette, 0xfu, POCKETS_LETTERS_PALETTE_SHIFT);
    data_ov094_0229c0f4.attr2 =
        letters_attr2(data_ov094_0229c0f4.attr2, data_ov094_0229c134[icon], POCKETS_LETTERS_TILE_MASK, 0);
    OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, &data_ov094_0229c0f4, x, y, POCKETS_LETTERS_OWN_PALETTE, letters->priority,
                            params);
}
CLEAN_AS(func_ov094_0229b550, PocketsLetters_DrawLetter)

/* func_ov094_0229b5c8: the palette of `letter`'s icon; -1 without an icon. */
int PocketsLetters_PaletteOf(PocketsLetters *letters, const Letter *letter)
{
    int icon = PocketsLetters_IconOf(letters, letter);

    if (icon == POCKETS_LETTERS_NO_ICON) {
        return -1;
    }
    return data_ov094_0229c0fc[icon];
}
CLEAN_AS(func_ov094_0229b5c8, PocketsLetters_PaletteOf)

/* func_ov094_0229b5e8: the held `letter` drawn at (x, y) at its size (not at all at size 0):
 * at full size with the OBJ round it and the lowered copy under it, else scaled, with the OBJ
 * round it scaled too and no lowered copy. */
void PocketsLetters_DrawHeld(PocketsLetters *letters, int x, int y, const Letter *letter)
{
    int scale;

    if (letters->held_size == 0) {
        return;
    }
    scale = PocketsGrid_SizeScale(letters->held_size);
    if (scale == POCKETS_LETTERS_SCALE_ONE) {
        PocketsLetters_DrawLetter(letters, x, y, PocketsLetters_PaletteOf(letters, letter), letter, NULL);
        PocketsLetters_DrawSurround(letters, x, y, PocketsLetters_PaletteOf(letters, letter), NULL);
        PocketsLetters_DrawLowered(letters, x, y, NULL);
    } else {
        OamAffine params = {scale, 0, 0, scale};
        PocketsLetters_DrawLetter(letters, x, y, PocketsLetters_PaletteOf(letters, letter), letter, &params);
        PocketsLetters_DrawSurround(letters, x, y, PocketsLetters_PaletteOf(letters, letter), &params);
    }
}
CLEAN_AS(func_ov094_0229b5e8, PocketsLetters_DrawHeld)

/* Places `first` to `first + count - 1` drawn moved by (x, y), with the letters of `list`. */
static void letters_draw_group(PocketsLetters *letters, const Letter *list, int first, int count, int x, int y)
{
    for (int i = 0; i < count; i++) {
        PocketsLetters_DrawPlace(letters, &list[i], first + i, x, y);
    }
}

/* func_ov094_0229b690: places 0x2d-0x36 drawn moved by (x, y). */
void PocketsLetters_DrawTenAt2d(PocketsLetters *letters, int x, int y)
{
    letters_draw_group(letters, letters->letters, POCKETS_LETTERS_OTHER_FIRST, POCKETS_LETTERS_TEN, x, y);
}
CLEAN_AS(func_ov094_0229b690, PocketsLetters_DrawTenAt2d)

/* func_ov094_0229b6c8: places 0x23-0x2c drawn moved by (x, y). */
void PocketsLetters_DrawTenAt23(PocketsLetters *letters, int x, int y)
{
    letters_draw_group(letters, letters->letters, POCKETS_LETTERS_TEN_FIRST, POCKETS_LETTERS_TEN, x, y);
}
CLEAN_AS(func_ov094_0229b6c8, PocketsLetters_DrawTenAt23)

/* func_ov094_0229b700: the page's places (10-34) drawn moved by (x, y). */
void PocketsLetters_DrawPage(PocketsLetters *letters, int x, int y)
{
    letters_draw_group(letters, letters->letters, POCKETS_LETTERS_PAGE_FIRST, POCKETS_LETTERS_PAGE, x, y);
}
CLEAN_AS(func_ov094_0229b700, PocketsLetters_DrawPage)

/* func_ov094_0229b738: the pockets' places (0-9) drawn moved by (x, y), with the current
 * player's letters. */
void PocketsLetters_DrawPockets(PocketsLetters *letters, int x, int y)
{
    letters_draw_group(letters, letters_pockets(), 0, POCKETS_LETTERS_POCKETS, x, y);
}
CLEAN_AS(func_ov094_0229b738, PocketsLetters_DrawPockets)

/* func_ov094_0229b77c: place `place` dimmed. */
void PocketsLetters_DimPlace(PocketsLetters *letters, int place)
{
    PocketsLetterBits_Set(&letters->dimmed, place);
}
CLEAN_AS(func_ov094_0229b77c, PocketsLetters_DimPlace)

/* func_ov094_0229b788: whether place `place` is dimmed. */
int PocketsLetters_IsDimmed(PocketsLetters *letters, int place)
{
    return PocketsLetterBits_Test(&letters->dimmed, place);
}
CLEAN_AS(func_ov094_0229b788, PocketsLetters_IsDimmed)

/* func_ov094_0229b794: the pockets' letters (places 0-9) dimmed by their states for the bits of
 * `states` (POCKETS_LETTERS_DIM_...), the others not; then for each of bits 1, 2 and 4 the
 * palette of its letters (4, 5, 6) reloaded from menu/inventory/b_itm_ten0_obj.bpl. */
void PocketsLetters_DimByState(PocketsLetters *letters, unsigned int states)
{
    unsigned int written = states & POCKETS_LETTERS_DIM_WRITTEN;
    unsigned int bottle = states & POCKETS_LETTERS_DIM_BOTTLE;
    unsigned int received = states & POCKETS_LETTERS_DIM_RECEIVED;
    unsigned int villagers = states & POCKETS_LETTERS_DIM_VILLAGERS;
    Heap *heap;

    PocketsLetterBits_ClearAll(&letters->dimmed);
    for (u8 place = 0; place < POCKETS_LETTERS_POCKETS; place++) {
        switch (Letter_State(PocketsLetters_LetterAt(letters, place))) {
            case LETTER_STATE_WRITTEN:
                if (written) {
                    PocketsLetters_DimPlace(letters, place);
                }
                break;
            case LETTER_STATE_BOTTLE_WRITTEN:
                if (bottle || written) {
                    PocketsLetters_DimPlace(letters, place);
                }
                break;
            case LETTER_STATE_RECEIVED:
            case LETTER_STATE_RECEIVED_NEXT:
            case LETTER_STATE_BOTTLE:
            case LETTER_STATE_BOTTLE_NEXT:
                if (received) {
                    PocketsLetters_DimPlace(letters, place);
                }
                break;
            case LETTER_STATE_BETWEEN_VILLAGERS:
            case LETTER_STATE_BETWEEN_VILLAGERS_NEXT:
                if (villagers) {
                    PocketsLetters_DimPlace(letters, place);
                }
                break;
            default:
                break;
        }
    }
    heap = data_021fbe94;
    if (written) {
        DisplayLayer_LoadPalettesFromFile(data_ov094_0229c154, heap, LAYER_SUB_OBJ, POCKETS_LETTERS_PALETTE_FILE_FIRST,
                                          POCKETS_LETTERS_PALETTE_WRITTEN, POCKETS_LETTERS_PALETTE_WRITTEN);
    }
    if (received) {
        DisplayLayer_LoadPalettesFromFile(data_ov094_0229c154, heap, LAYER_SUB_OBJ, POCKETS_LETTERS_PALETTE_FILE_FIRST,
                                          POCKETS_LETTERS_PALETTE_RECEIVED, POCKETS_LETTERS_PALETTE_RECEIVED);
    }
    if (villagers) {
        DisplayLayer_LoadPalettesFromFile(data_ov094_0229c154, heap, LAYER_SUB_OBJ, POCKETS_LETTERS_PALETTE_FILE_FIRST,
                                          POCKETS_LETTERS_PALETTE_VILLAGERS, POCKETS_LETTERS_PALETTE_VILLAGERS);
    }
}
CLEAN_AS(func_ov094_0229b794, PocketsLetters_DimByState)

/* func_ov094_0229b890: place `place`'s letter cleared and the place emptied. */
void PocketsLetters_ClearPlace(PocketsLetters *letters, int place)
{
    Letter_Clear(PocketsLetters_LetterAt(letters, place));
    PocketsLetterBits_Clear(&letters->filled, place);
}
CLEAN_AS(func_ov094_0229b890, PocketsLetters_ClearPlace)

/* func_ov094_0229b8b4: `letter` copied into place `place`'s letter and the place filled. */
void PocketsLetters_SetPlace(PocketsLetters *letters, int place, const Letter *letter)
{
    Letter_Assign(PocketsLetters_LetterAt(letters, place), letter);
    PocketsLetterBits_Set(&letters->filled, place);
}
CLEAN_AS(func_ov094_0229b8b4, PocketsLetters_SetPlace)

/* func_ov094_0229b8d8: place `place`'s letter: one of the current player's for places 0-9, else
 * one of the list last given (from its start for each group of places); NULL for a number that
 * is no place. */
Letter *PocketsLetters_LetterAt(PocketsLetters *letters, int place)
{
    PlayerPockets *pockets = PlayerRecord_Pockets(PlayerRecords_Current());

    if (in_group(place, 0, POCKETS_LETTERS_POCKETS)) {
        return PlayerPockets_Letter(pockets, place);
    }
    if (in_group(place, POCKETS_LETTERS_PAGE_FIRST, POCKETS_LETTERS_PAGE)) {
        return &letters->letters[place - POCKETS_LETTERS_PAGE_FIRST];
    }
    if (in_group(place, POCKETS_LETTERS_TEN_FIRST, POCKETS_LETTERS_TEN)) {
        return &letters->letters[place - POCKETS_LETTERS_TEN_FIRST];
    }
    if (in_group(place, POCKETS_LETTERS_OTHER_FIRST, POCKETS_LETTERS_TEN)) {
        return &letters->letters[place - POCKETS_LETTERS_OTHER_FIRST];
    }
    return NULL;
}
CLEAN_AS(func_ov094_0229b8d8, PocketsLetters_LetterAt)

/* func_ov094_0229b938: place `place` marked. */
void PocketsLetters_MarkPlace(PocketsLetters *letters, int place)
{
    PocketsLetterBits_Set(&letters->marked, place);
}
CLEAN_AS(func_ov094_0229b938, PocketsLetters_MarkPlace)

/* func_ov094_0229b944: no place marked. */
void PocketsLetters_ClearMarks(PocketsLetters *letters)
{
    PocketsLetterBits_ClearAll(&letters->marked);
}
CLEAN_AS(func_ov094_0229b944, PocketsLetters_ClearMarks)

/* func_ov094_0229b950: place `place` lifted, its lift starting again when it was not the lifted
 * one; none lifted when the place is dimmed. */
void PocketsLetters_Lift(PocketsLetters *letters, int place)
{
    if (PocketsLetters_IsDimmed(letters, (u8) place)) {
        PocketsLetters_Unlift(letters);
    } else if (letters->lifted != place) {
        letters->lifted = (u8) place;
        letters->lift = POCKETS_LETTERS_LIFT_START;
    }
}
CLEAN_AS(func_ov094_0229b950, PocketsLetters_Lift)

/* func_ov094_0229b98c: no place lifted. */
void PocketsLetters_Unlift(PocketsLetters *letters)
{
    letters->lifted = POCKETS_LETTERS_NO_PLACE;
}
CLEAN_AS(func_ov094_0229b98c, PocketsLetters_Unlift)

/* func_ov094_0229b994: the lifted place's offset now (a negative number of pixels, as the
 * table's word). REQUIRES: `lift` 0-2 (it counts down from 2). */
unsigned int PocketsLetters_LiftOffset(PocketsLetters *letters)
{
    return data_ov094_0229bde0[letters->lift];
}
CLEAN_AS(func_ov094_0229b994, PocketsLetters_LiftOffset)

/* func_ov094_0229b9a4: whether place `place` is the lifted one. */
int PocketsLetters_IsLifted(PocketsLetters *letters, u8 place)
{
    return place == letters->lifted;
}
CLEAN_AS(func_ov094_0229b9a4, PocketsLetters_IsLifted)

/* func_ov094_0229b9b4: `popup` given the text of place `place`'s letter. */
int PocketsLetters_ShowPlaceText(PocketsLetters *letters, Popup *popup, int place)
{
    return (int) (uintptr_t) PocketsLetters_SetPopupText(letters, popup, PocketsLetters_LetterAt(letters, place));
}
CLEAN_AS(func_ov094_0229b9b4, PocketsLetters_ShowPlaceText)

/* func_ov094_0229b9d4: `popup` given the text of `letter`. Two lines are made: who it is from
 * (menu message 0x4b with the sender's name as part 1 for a delivered letter (tag 0x11) or a
 * bottle's the player wrote; 0x3d with the sender's name for another letter of tag 0; else the
 * message of its tag) and who it is to (menu message 0x3c with part 0 the addressee's name, or
 * menu message 0x43 when it has none). The popup shows the second for the letters the player or
 * a villager wrote (states 1, 4, 7 and 8), else the first. Returns what destroying the label
 * returns (its address). */
TextLabel *PocketsLetters_SetPopupText(PocketsLetters *letters, Popup *popup, Letter *letter)
{
    /* The texts in the order of the ROM's frame. */
    struct PopupTexts {
        PlayerIdText name;      /* 0x00 */
        SlidingWindowText to;   /* 0x20 */
        SlidingWindowText from; /* 0x50 */
        TextLabel label;        /* 0x80 */
        TextLabel no_addressee; /* 0xec */
    } texts;
    static_assert(offsetof(struct PopupTexts, from) == 0x50 && offsetof(struct PopupTexts, no_addressee) == 0xec,
                  "the ROM's frame");
    int state;
    int tag;

    (void) letters;
    state = Letter_State(letter);
    TextLabel_Construct(&texts.label);
    PlayerIdText_Construct(&texts.name);
    SlidingWindowText_Construct(&texts.to);
    SlidingWindowText_Construct(&texts.from);
    tag = Letter_Tag(letter);
    if (tag == POCKETS_LETTERS_TAG_DELIVERED) {
        Letter_SenderNameText(letter, &texts.name);
        MessageReader_SetPart(1, (int) (uintptr_t) &texts.name);
        TextLabel_LoadMenuMessage(&texts.label, POCKETS_LETTERS_MESSAGE_FROM);
    } else if (tag == 0) {
        Letter_SenderNameText(letter, &texts.name);
        MessageReader_SetPart(1, (int) (uintptr_t) &texts.name);
        if (state == LETTER_STATE_BOTTLE_WRITTEN) {
            TextLabel_LoadMenuMessage(&texts.label, POCKETS_LETTERS_MESSAGE_FROM);
        } else {
            TextLabel_LoadMenuMessage(&texts.label, POCKETS_LETTERS_MESSAGE_FROM_TAG_0);
        }
    } else {
        TextLabel_LoadMenuMessage(&texts.label, (char) data_ov094_0229bdec[tag]);
    }
    TextString_CopyBytes((TextObject *) (void *) &texts.from, (TextObject *) (void *) &texts.label);
    if (Letter_HasNoAddressee(letter)) {
        TextLabel_Construct(&texts.no_addressee);
        TextLabel_LoadMenuMessage(&texts.no_addressee, POCKETS_LETTERS_MESSAGE_NO_ADDRESSEE);
        MessageReader_SetPart(0, (int) (uintptr_t) &texts.no_addressee);
        TextLabel_Destruct(&texts.no_addressee);
    } else {
        Letter_AddresseeNameText(letter, &texts.name);
        MessageReader_SetPart(0, (int) (uintptr_t) &texts.name);
    }
    TextLabel_LoadMenuMessage(&texts.label, POCKETS_LETTERS_MESSAGE_TO);
    TextString_CopyBytes((TextObject *) (void *) &texts.to, (TextObject *) (void *) &texts.label);
    switch (state) {
        case LETTER_STATE_WRITTEN:
        case LETTER_STATE_BOTTLE_WRITTEN:
        case LETTER_STATE_BETWEEN_VILLAGERS:
        case LETTER_STATE_BETWEEN_VILLAGERS_NEXT:
            SlidingWindow_SetText((SlidingWindow *) (void *) popup, (struct TextObject *) (void *) &texts.to);
            break;
        default:
            SlidingWindow_SetText((SlidingWindow *) (void *) popup, (struct TextObject *) (void *) &texts.from);
            break;
    }
    SlidingWindowText_Destruct(&texts.from);
    SlidingWindowText_Destruct(&texts.to);
    PlayerIdText_Destruct(&texts.name);
    return TextLabel_Destruct(&texts.label);
}
CLEAN_AS(func_ov094_0229b9d4, PocketsLetters_SetPopupText)

/* func_ov094_0229bb04: the first of places `first` to `last` whose position is strictly within
 * (x - 20, x + 4) and (y - 20, y + 4); POCKETS_LETTERS_NO_PLACE for none. */
u8 PocketsLetters_PlaceNear(PocketsLetters *letters, int x, int y, int first, u8 last)
{
    for (int place = first; place <= last; place++) {
        int place_x = PocketsLetters_PlaceX(letters, place);
        int place_y;

        if (x - POCKETS_LETTERS_TOUCH_BEFORE >= place_x || place_x >= x + POCKETS_LETTERS_TOUCH_AFTER) {
            continue;
        }
        place_y = PocketsLetters_PlaceY(letters, place);
        if (y - POCKETS_LETTERS_TOUCH_BEFORE >= place_y || place_y >= y + POCKETS_LETTERS_TOUCH_AFTER) {
            continue;
        }
        return (u8) place;
    }
    return POCKETS_LETTERS_NO_PLACE;
}
CLEAN_AS(func_ov094_0229bb04, PocketsLetters_PlaceNear)

/* func_ov094_0229bb5c: the place of 0x23-0x2c under the touch at (x, y). */
int PocketsLetters_TenAt23AtTouch(PocketsLetters *letters, int x, int y)
{
    return PocketsLetters_PlaceNear(letters, x, y, POCKETS_LETTERS_TEN_FIRST,
                                    POCKETS_LETTERS_TEN_FIRST + POCKETS_LETTERS_TEN - 1);
}
CLEAN_AS(func_ov094_0229bb5c, PocketsLetters_TenAt23AtTouch)

/* func_ov094_0229bb70: the page's place (10-34) under the touch at (x, y). */
int PocketsLetters_PageAtTouch(PocketsLetters *letters, int x, int y)
{
    return PocketsLetters_PlaceNear(letters, x, y, POCKETS_LETTERS_PAGE_FIRST,
                                    POCKETS_LETTERS_PAGE_FIRST + POCKETS_LETTERS_PAGE - 1);
}
CLEAN_AS(func_ov094_0229bb70, PocketsLetters_PageAtTouch)

/* func_ov094_0229bb84: the place of 0x2d-0x36 under the touch at (x, y); none outside x
 * 0x60-0xa0. */
int PocketsLetters_TenAt2dAtTouch(PocketsLetters *letters, int x, int y)
{
    if (x > POCKETS_LETTERS_TOUCH_LIST_MAX_X || x < POCKETS_LETTERS_TOUCH_LIST_MIN_X) {
        return POCKETS_LETTERS_NO_PLACE;
    }
    return PocketsLetters_PlaceNear(letters, x, y, POCKETS_LETTERS_OTHER_FIRST,
                                    POCKETS_LETTERS_OTHER_FIRST + POCKETS_LETTERS_TEN - 1);
}
CLEAN_AS(func_ov094_0229bb84, PocketsLetters_TenAt2dAtTouch)

/* func_ov094_0229bba4: the pockets' place (0-9) under the touch at (x, y); none left of x 0xc0. */
int PocketsLetters_PocketAtTouch(PocketsLetters *letters, int x, int y)
{
    if (x < POCKETS_LETTERS_TOUCH_POCKETS_MIN_X) {
        return POCKETS_LETTERS_NO_PLACE;
    }
    return PocketsLetters_PlaceNear(letters, x, y, 0, POCKETS_LETTERS_POCKETS - 1);
}
CLEAN_AS(func_ov094_0229bba4, PocketsLetters_PocketAtTouch)

/* func_ov094_0229bbc0: a frame begun: the lift a step on. */
void PocketsLetters_BeginFrame(PocketsLetters *letters)
{
    if (letters->lift != 0) {
        letters->lift--;
    }
}
CLEAN_AS(func_ov094_0229bbc0, PocketsLetters_BeginFrame)

/* func_ov094_0229bbd8: the letters set up empty, with no list, nothing lifted, their OBJs at
 * priority `priority` and the held letter at full size. */
void PocketsLetters_Init(PocketsLetters *letters, int priority)
{
    PocketsLetterBits_ClearAll(&letters->filled);
    PocketsLetterBits_ClearAll(&letters->marked);
    PocketsLetterBits_ClearAll(&letters->dimmed);
    letters->lifted = POCKETS_LETTERS_NO_PLACE;
    letters->lift = 0;
    letters->priority = priority;
    letters->letters = NULL;
    letters->held_size = POCKETS_LETTERS_FULL_SIZE;
}
CLEAN_AS(func_ov094_0229bbd8, PocketsLetters_Init)

/* func_ov094_0229bc18 (vtable entry 1): the destructor that frees the object. */
PocketsLetters *PocketsLetters_DestructDelete(PocketsLetters *letters)
{
    letters->vtable = (u32) (uintptr_t) data_ov094_0229c114;
    Heap_OperatorDeleteB(letters);
    return letters;
}
CLEAN_AS(func_ov094_0229bc18, PocketsLetters_DestructDelete)

/* func_ov094_0229bc30 (vtable entry 0): the destructor. */
void PocketsLetters_Destruct(PocketsLetters *letters)
{
    letters->vtable = (u32) (uintptr_t) data_ov094_0229c114;
}
CLEAN_AS(func_ov094_0229bc30, PocketsLetters_Destruct)

/* func_ov094_0229bc3c: the constructor. */
void PocketsLetters_Construct(PocketsLetters *letters)
{
    letters->vtable = (u32) (uintptr_t) data_ov094_0229c114;
}
CLEAN_AS(func_ov094_0229bc3c, PocketsLetters_Construct)
