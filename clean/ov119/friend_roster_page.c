/* The friend roster of overlay 119 (friend_roster.h): its pages. The rows of a friends' page
 * (the friend's icon, town and name), this user's friend key, the session's other players, the
 * labels the texts are drawn with, the palettes' fade and the graphics loaded and queued. */
#include "friend_roster.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/message_query.h"
#include "main/message_reader.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/screen_map.h"
#include "main/session.h"
#include "main/text_base.h"
#include "main/town_name.h"

/* The menu's heap. */
extern Heap *data_021fbe94;

/* The session (main/session.h). */
extern NetSession *data_020ccf94;

extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);

/* "menu/friend/obj0.bch", "obj1.bch", "obj.bpl", "obj1.bpl", "bg0.bpl", "bg2.bpl", "bg0.bch",
 * "a_bg.bsc", "b_bg.bsc" and "d_bg.bsc". */
extern const char data_ov119_0229cf00[], data_ov119_0229cf18[], data_ov119_0229cf30[], data_ov119_0229cf44[];
extern const char data_ov119_0229cf5c[], data_ov119_0229cf70[], data_ov119_0229cf84[], data_ov119_0229cf98[];
extern const char data_ov119_0229cfb0[], data_ov119_0229cfc8[];

/* The layers: the frame (a_bg.bsc) and the page's map behind it (`map`); the OBJs'. */
#define FRIEND_ROSTER_LAYER_FRAME 6
#define FRIEND_ROSTER_LAYER_PAGE 4
#define FRIEND_ROSTER_LAYER_OBJ 8

/* The maps are 32 entries wide; a row's icon is a 2x2 block at column 3 of map row 6 + 2 * row,
 * its texts from column 5 to 0x17. */
#define FRIEND_ROSTER_MAP_WIDTH 32
#define FRIEND_ROSTER_ICON_FIRST (6 * FRIEND_ROSTER_MAP_WIDTH + 3)
#define FRIEND_ROSTER_ROW_STEP (2 * FRIEND_ROSTER_MAP_WIDTH)

/* The icons' first tiles (FriendRoster_SetRowIcon). */
enum FriendRosterIcon {
    FRIEND_ROSTER_ICON_NONE = 0x10,   /* one blank tile for the whole block */
    FRIEND_ROSTER_ICON_FRIEND = 0x50, /* a friend whose data is not a friend key */
    FRIEND_ROSTER_ICON_KEY = 0x54,    /* a friend registered by friend key */
    FRIEND_ROSTER_ICON_PLAYER = 0x58  /* a player of the session */
};

/* The rows' palettes in the map: 3 as loaded (and faded), 4 for the picked row, 5 for the
 * blink of the players' rows. */
#define FRIEND_ROSTER_PALETTE_ROW 3
#define FRIEND_ROSTER_PALETTE_PICKED 4
#define FRIEND_ROSTER_PALETTE_BLINK 5

/* The messages of "2d_menu" used: a town's name in part 0 (the friend's or player's town), the
 * three pages' titles, the scene's title and the header (this user's account, by its state). */
#define FRIEND_ROSTER_MESSAGE_TOWN 0x66
#define FRIEND_ROSTER_MESSAGE_FRIENDS 0xcd
#define FRIEND_ROSTER_MESSAGE_OWN_KEY 0xea
#define FRIEND_ROSTER_MESSAGE_PLAYERS 0xeb
#define FRIEND_ROSTER_MESSAGE_TITLE 0xd6
#define FRIEND_ROSTER_MESSAGE_NO_ACCOUNT 0xd4 /* WifiAccount_IsAuthentic answers 0 */
#define FRIEND_ROSTER_MESSAGE_ACCOUNT_EC 0xec /* func_021012c4 answers 0 */
#define FRIEND_ROSTER_MESSAGE_ACCOUNT 0xd5

#define FRIEND_ROSTER_BLANK_DIGIT 10
#define FRIEND_ROSTER_HEADER_LINES 3

/* A label's text box opened (style, first tile, width in cells, colour 15) and shown. */
static void fr_open_label(TextLabel *label, int style, int first_tile, int cells, int center)
{
    TextLabel_OpenStyledBox2(label, style, first_tile, cells, 0xf, 0, 0);
    TextLabel_Show(label, center, 0);
}

/* The ROM's signed division (_s32_div_f): a divisor of 0 gives the numerator back, and
 * INT32_MIN / -1 gives INT32_MIN. */
static int fr_div(int numerator, int divisor)
{
    if (divisor == 0) {
        return numerator;
    }
    if (divisor == -1) {
        return (int) (0u - (unsigned int) numerator);
    }
    return numerator / divisor;
}

/* func_ov119_0229a434: a frame of the rows' blink: at frame 10 the players' rows take palette 5,
 * at 25 every row is back to palette 3 and the blink starts again. */
void FriendRoster_StepBlink(FriendRoster *self)
{
    self->blink++;
    if (self->blink == 10) {
        FriendRoster_BlinkPlayerRows(self);
    } else if (self->blink >= 25) {
        FriendRoster_ResetRowPalettes(self);
        self->blink = 0;
    }
}
CLEAN_AS(func_ov119_0229a434, FriendRoster_StepBlink)

/* func_ov119_0229a46c: the rows' icons in palette 3 (columns 3-4 of map rows 6-21), the map
 * queued. */
void FriendRoster_ResetRowPalettes(FriendRoster *self)
{
    ScreenMap_SetPalette(self->list_map, 3, 6, 4, 0x15, FRIEND_ROSTER_PALETTE_ROW);
    FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_MAP_DIRTY);
}
CLEAN_AS(func_ov119_0229a46c, FriendRoster_ResetRowPalettes)

/* func_ov119_0229a49c: the icons back to palette 3, then those of the players' rows in 5. */
void FriendRoster_BlinkPlayerRows(FriendRoster *self)
{
    FriendRoster_ResetRowPalettes(self);
    for (int i = 0; i < FRIEND_ROSTER_ROWS; i++) {
        if (self->player_rows & (1 << i)) {
            int top = i * 2 + 6;
            ScreenMap_SetPalette(self->list_map, 3, top, 4, top + 1, FRIEND_ROSTER_PALETTE_BLINK);
        }
    }
}
CLEAN_AS(func_ov119_0229a49c, FriendRoster_BlinkPlayerRows)

/* func_ov119_0229a5d8: this user's friend key in twelve decimal digits, the most significant
 * first; all blank unless WifiAccount_IsAuthentic and func_021012c4 both answer with a common
 * bit set. */
void FriendRoster_LoadKeyDigits(FriendRoster *self)
{
    u8 *record = PlayerRecords_Current();
    int authentic = WifiAccount_IsAuthentic(PlayerRecord_WifiAccount(record));
    int other = WifiAccount_Call021012c4(PlayerRecord_WifiAccount(record));
    if ((authentic & other) == 0) {
        for (int i = 0; i < WIFI_FRIEND_KEY_DIGITS; i++) {
            self->key_digits[i] = FRIEND_ROSTER_BLANK_DIGIT;
        }
        return;
    }
    u64 key = WifiAccount_GetUserKey(PlayerRecord_WifiAccount(record));
    for (int i = WIFI_FRIEND_KEY_DIGITS - 1; i >= 0; i--) {
        self->key_digits[i] = (u8) (key % 10);
        key /= 10;
    }
}
CLEAN_AS(func_ov119_0229a5d8, FriendRoster_LoadKeyDigits)

/* func_ov119_0229a650: the page (0-3) showing the first set friend at or after `index`; with
 * none, the page of the last set friend, and page 0 for an empty roster. */
int FriendRoster_PageOfFriend(FriendRoster *self, int index)
{
    WifiFriend *friends = FriendRoster_Friends(self);
    int count = 0;
    for (int i = 0; i < WIFI_FRIENDS; i++) {
        if (WifiFriendData_IsSet(WifiFriend_GetFriendData(&friends[i]))) {
            count++;
            if (i >= index) {
                break;
            }
        }
    }
    if (count > 0) {
        return (int) (((unsigned int) (count - 1) >> 3) & 0xff);
    }
    return 0;
}
CLEAN_AS(func_ov119_0229a650, FriendRoster_PageOfFriend)

/* func_ov119_0229a69c: `page` shown, unless it is: selected, its title made, its map chosen
 * (the friend key's for page 4, else the list's) and queued, its rows drawn. */
void FriendRoster_ShowPage(FriendRoster *self, unsigned char page)
{
    if (page == self->page) {
        return;
    }
    self->tab = page;
    self->page = page;
    if (self->page == FRIEND_ROSTER_PAGE_PLAYERS) {
        FriendRoster_ShowPageTitle(self, FRIEND_ROSTER_MESSAGE_PLAYERS);
        self->map = self->list_map;
    } else if (self->page == FRIEND_ROSTER_PAGE_OWN_KEY) {
        FriendRoster_ShowPageTitle(self, FRIEND_ROSTER_MESSAGE_OWN_KEY);
        self->map = self->key_map;
    } else {
        FriendRoster_ShowPageTitle(self, FRIEND_ROSTER_MESSAGE_FRIENDS);
        self->map = self->list_map;
    }
    FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_MAP_DIRTY);
    FriendRoster_RedrawPage(self);
}
CLEAN_AS(func_ov119_0229a69c, FriendRoster_ShowPage)

/* func_ov119_0229a714: the page drawn again: no blink, the icons' palettes reset, no rows shown
 * yet; then this user's information (page 4), the players (page 5) or the friends (with their
 * rows' palettes set again). */
void FriendRoster_RedrawPage(FriendRoster *self)
{
    self->player_rows = 0;
    self->blink = 0;
    FriendRoster_ResetRowPalettes(self);
    self->rows_shown = 0;
    if (self->page == FRIEND_ROSTER_PAGE_OWN_KEY) {
        FriendRoster_DrawOwnInfo(self);
    } else if (self->page == FRIEND_ROSTER_PAGE_PLAYERS) {
        FriendRoster_DrawPlayerRows(self);
    } else {
        FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_ROWS_DIRTY);
        FriendRoster_DrawFriendRows(self);
    }
}
CLEAN_AS(func_ov119_0229a714, FriendRoster_RedrawPage)

/* A row's two labels: the town's at tile 0x1ce + 0x14 * row (10 cells), the name's at 0x14e +
 * 0x10 * row (8 cells). */
#define FRIEND_ROSTER_TOWN_TILE 0x1ce
#define FRIEND_ROSTER_TOWN_TILE_STEP 0x14
#define FRIEND_ROSTER_NAME_TILE 0x14e
#define FRIEND_ROSTER_NAME_TILE_STEP 0x10

/* func_ov119_0229a764: the eight rows of a friends' page (slots page * 8 on): for a set friend
 * its town (from its text at 0x18, by message 0x66) and its name (its text at 0x0c), counted in
 * `rows_shown`, with the icon of a friend key or of a friend; else both labels emptied and no
 * icon. */
void FriendRoster_DrawFriendRows(FriendRoster *self)
{
    WifiFriend *friends = FriendRoster_Friends(self);
    const u8 *bytes = (const u8 *) self;
    int slot = self->page << 3;
    int town_tile = FRIEND_ROSTER_TOWN_TILE;
    int name_tile = FRIEND_ROSTER_NAME_TILE;
    int icon = FRIEND_ROSTER_ICON_FIRST;
    TownNameText town;
    TownNameWideText wide;
    TownNameText_Construct(&town);
    TownNameWideText_Construct(&wide);
    for (int i = 0; i < FRIEND_ROSTER_ROWS; i++) {
        TextLabel *town_label = FriendRoster_NextLabel(self);
        TextLabel *name_label = FriendRoster_NextLabel(self);
        int index = bytes[offsetof(FriendRoster, slots) + slot];
        WifiFriend *entry = index < WIFI_FRIENDS ? &friends[index] : NULL;
        if (entry != NULL && WifiFriendData_IsSet(WifiFriend_GetFriendData(entry))) {
            TextBase_SetWide(&wide, WifiFriend_GetText18(entry), WIFI_FRIEND_TEXT_LENGTH);
            TextBase_WideToBytes((TextBase *) (void *) &town, (WideTextBase *) (void *) &wide, 0, 0);
            MessageReader_SetPart(0, (int) (uintptr_t) &town);
            TextLabel_LoadMenuMessage(town_label, FRIEND_ROSTER_MESSAGE_TOWN);
            TextLabel_SetFromWide(name_label, WifiFriend_GetText0C(entry), (void *) (uintptr_t) WIFI_FRIEND_TEXT_LENGTH);
            self->rows_shown++;
            if (WifiFriendData_IsNotFriendKey(WifiFriend_GetFriendData(entry))) {
                FriendRoster_SetRowIcon((int) (uintptr_t) self, &self->list_map[icon], FRIEND_ROSTER_ICON_FRIEND);
            } else {
                FriendRoster_SetRowIcon((int) (uintptr_t) self, &self->list_map[icon], FRIEND_ROSTER_ICON_KEY);
            }
        } else {
            TextBase_Clear(town_label);
            TextBase_Clear(name_label);
            FriendRoster_SetRowIcon((int) (uintptr_t) self, &self->list_map[icon], FRIEND_ROSTER_ICON_NONE);
        }
        fr_open_label(town_label, 4, town_tile, 0xa, 0);
        fr_open_label(name_label, 4, name_tile, 8, 0);
        town_tile += FRIEND_ROSTER_TOWN_TILE_STEP;
        name_tile += FRIEND_ROSTER_NAME_TILE_STEP;
        slot++;
        icon += FRIEND_ROSTER_ROW_STEP;
    }
    TownNameWideText_Destruct(&wide);
    TownNameText_Destruct(&town);
}
CLEAN_AS(func_ov119_0229a764, FriendRoster_DrawFriendRows)

static u16 fr_with_tile(u16 entry, unsigned short tile)
{
    return (u16) ((entry & 0xfc00) | tile);
}

/* func_ov119_0229a8ec: a row's 2x2 icon set to the tiles from `tile` on, left to right, top to
 * bottom (their palettes and flips kept); the blank tile is used for all four. */
void FriendRoster_SetRowIcon(int unused, u16 *map, unsigned short tile)
{
    (void) unused;
    map[0] = fr_with_tile(map[0], tile);
    if (tile != FRIEND_ROSTER_ICON_NONE) {
        tile = (unsigned short) (tile + 1);
    }
    map[1] = fr_with_tile(map[1], tile);
    if (tile != FRIEND_ROSTER_ICON_NONE) {
        tile = (unsigned short) (tile + 1);
    }
    map[FRIEND_ROSTER_MAP_WIDTH] = fr_with_tile(map[FRIEND_ROSTER_MAP_WIDTH], tile);
    if (tile != FRIEND_ROSTER_ICON_NONE) {
        tile = (unsigned short) (tile + 1);
    }
    map[FRIEND_ROSTER_MAP_WIDTH + 1] = fr_with_tile(map[FRIEND_ROSTER_MAP_WIDTH + 1], tile);
}
CLEAN_AS(func_ov119_0229a8ec, FriendRoster_SetRowIcon)

/* func_ov119_0229a968: the header: the message telling of this user's account (0xd4 when it is
 * not authentic, 0xec when func_021012c4 answers 0, else 0xd5) loaded into the header's text,
 * and its first three lines shown, 0x28 tiles apart. */
void FriendRoster_ShowHeader(FriendRoster *self)
{
    u8 message;
    u8 *record = PlayerRecords_Current();
    if (!WifiAccount_IsAuthentic(PlayerRecord_WifiAccount(record))) {
        message = FRIEND_ROSTER_MESSAGE_NO_ACCOUNT;
    } else if (!WifiAccount_Call021012c4(PlayerRecord_WifiAccount(record))) {
        message = FRIEND_ROSTER_MESSAGE_ACCOUNT_EC;
    } else {
        message = FRIEND_ROSTER_MESSAGE_ACCOUNT;
    }
    MessageReader_LoadMenuMessage(&self->header, &message, NULL);
    for (int i = 0; i < FRIEND_ROSTER_HEADER_LINES; i++) {
        TextLabel *label = FriendRoster_NextLabel(self);
        int line = MessageQuery_Line((int) (uintptr_t) self->header.text, i);
        TextBase_SetLine((TextBase *) (void *) label, (const char *) (uintptr_t) line);
        fr_open_label(label, 4, i * 0x28 + 0x8a, 0x14, 0);
    }
}
CLEAN_AS(func_ov119_0229a968, FriendRoster_ShowHeader)

/* func_ov119_0229aa18 (page 4): the current player's town (by message 0x66) and name. */
void FriendRoster_DrawOwnInfo(FriendRoster *self)
{
    TownNameText town;
    PlayerIdText name;
    DesignCreator *player = PlayerRecord_Player(PlayerRecords_Current());
    TextLabel *label = FriendRoster_NextLabel(self);
    TownNameText_Construct(&town);
    TownName_ToText(PlayerId_Town(player), (TextBase *) (void *) &town);
    MessageReader_SetPart(0, (int) (uintptr_t) &town);
    TextLabel_LoadMenuMessage(label, FRIEND_ROSTER_MESSAGE_TOWN);
    fr_open_label(label, 4, 0x102, 0xa, 0);
    label = FriendRoster_NextLabel(self);
    PlayerIdText_Construct(&name);
    PlayerId_NameToText(player, (TextBase *) (void *) &name);
    TextBase_Copy((TextBase *) (void *) label, (TextBase *) (void *) &name);
    fr_open_label(label, 4, 0x116, 8, 0);
    PlayerIdText_Destruct(&name);
    TownNameText_Destruct(&town);
}
CLEAN_AS(func_ov119_0229aa18, FriendRoster_DrawOwnInfo)

/* func_ov119_0229aacc (page 5): while the session is linked, its players other than this
 * system's, in slot order, one a row: town (by message 0x66), name and the player's icon, the
 * row's bit set in `player_rows`; the other rows empty. Then the rows' texts in palette 5.
 * QUIRK: whether the session is linked is asked again for each row. */
void FriendRoster_DrawPlayerRows(FriendRoster *self)
{
    int town_tile = FRIEND_ROSTER_TOWN_TILE;
    int name_tile = FRIEND_ROSTER_NAME_TILE;
    int icon = FRIEND_ROSTER_ICON_FIRST;
    NetSession *session = data_020ccf94;
    int local_slot = session->local_slot;
    int slot = 0;
    TownNameText town;
    PlayerIdText name;
    TownNameText_Construct(&town);
    PlayerIdText_Construct(&name);
    for (int i = 0; i < FRIEND_ROSTER_ROWS; i++) {
        TextLabel *town_label = FriendRoster_NextLabel(self);
        TextLabel *name_label = FriendRoster_NextLabel(self);
        u8 *record = NULL;
        if (Session_IsLinked(session)) {
            if (local_slot == slot) {
                slot++;
            }
            if (slot < 4) {
                record = PlayerRecords_OfPlayer(slot);
                slot++;
            }
        }
        if (record != NULL) {
            DesignCreator *player = PlayerRecord_Player(record);
            TownName_ToText(PlayerId_Town(player), (TextBase *) (void *) &town);
            MessageReader_SetPart(0, (int) (uintptr_t) &town);
            TextLabel_LoadMenuMessage(town_label, FRIEND_ROSTER_MESSAGE_TOWN);
            PlayerId_NameToText(player, (TextBase *) (void *) &name);
            TextBase_Copy((TextBase *) (void *) name_label, (TextBase *) (void *) &name);
            FriendRoster_SetRowIcon((int) (uintptr_t) self, &self->list_map[icon], FRIEND_ROSTER_ICON_PLAYER);
            self->player_rows = (u8) (self->player_rows | (1 << i));
        } else {
            TextBase_Clear(town_label);
            TextBase_Clear(name_label);
            FriendRoster_SetRowIcon((int) (uintptr_t) self, &self->list_map[icon], FRIEND_ROSTER_ICON_NONE);
        }
        fr_open_label(town_label, 4, town_tile, 0xa, 0);
        fr_open_label(name_label, 4, name_tile, 8, 0);
        town_tile += FRIEND_ROSTER_TOWN_TILE_STEP;
        name_tile += FRIEND_ROSTER_NAME_TILE_STEP;
        icon += FRIEND_ROSTER_ROW_STEP;
    }
    ScreenMap_SetPalette(self->list_map, 5, 6, 0x17, 0x15, FRIEND_ROSTER_PALETTE_BLINK);
    PlayerIdText_Destruct(&name);
    TownNameText_Destruct(&town);
}
CLEAN_AS(func_ov119_0229aacc, FriendRoster_DrawPlayerRows)

/* func_ov119_0229ae84: the palettes at fade `level` (clamped to 0-5), queued from now on: the
 * copies made from the loaded ones, then BG colours 2-5 and 15 and OBJ colours 1-3 and 15
 * blended toward their palette's colour 14 (FriendRoster_BlendColour; 5 is as loaded, 0 is
 * colour 14). */
void FriendRoster_Fade(FriendRoster *self, int level)
{
    int unused = (int) (uintptr_t) self;
    if (level < 0) {
        level = 0;
    } else if (level > FRIEND_ROSTER_FADE_STEPS) {
        level = FRIEND_ROSTER_FADE_STEPS;
    }
    FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_FADED);
    MIi_CpuCopy16(self->obj_palette, self->obj_faded, sizeof(self->obj_faded));
    MIi_CpuCopy16(self->bg_palette, self->bg_faded, sizeof(self->bg_faded));
    for (int i = 2; i <= 5; i++) {
        self->bg_faded[i] =
            FriendRoster_BlendColour(unused, self->bg_palette[i], self->bg_palette[14], level, FRIEND_ROSTER_FADE_STEPS);
    }
    self->bg_faded[15] =
        FriendRoster_BlendColour(unused, self->bg_palette[15], self->bg_palette[14], level, FRIEND_ROSTER_FADE_STEPS);
    for (int i = 1; i <= 3; i++) {
        self->obj_faded[i] =
            FriendRoster_BlendColour(unused, self->obj_palette[i], self->obj_palette[14], level, FRIEND_ROSTER_FADE_STEPS);
    }
    self->obj_faded[15] =
        FriendRoster_BlendColour(unused, self->obj_faded[15], self->obj_palette[14], level, FRIEND_ROSTER_FADE_STEPS);
}
CLEAN_AS(func_ov119_0229ae84, FriendRoster_Fade)

static int fr_blend_channel(int a, int b, int weight, int total)
{
    return (u8) fr_div(a * weight + b * (total - weight), total);
}

/* func_ov119_0229af64: the BGR555 `colour` blended toward `toward`, `weight` parts of `total`
 * the colour's, channel by channel; each channel's result is kept to 8 bits before it is
 * packed. */
u16 FriendRoster_BlendColour(int unused, int colour, int toward, int weight, int total)
{
    (void) unused;
    int b = fr_blend_channel((u8) (colour & 0x1f), (u8) (toward & 0x1f), weight, total);
    int g = fr_blend_channel((u8) ((colour & 0x3e0) >> 5), (u8) ((toward & 0x3e0) >> 5), weight, total);
    int r = fr_blend_channel((u8) ((colour & 0x7c00) >> 10), (u8) ((toward & 0x7c00) >> 10), weight, total);
    return (u16) (b | (g << 5) | (r << 10));
}
CLEAN_AS(func_ov119_0229af64, FriendRoster_BlendColour)

/* func_ov119_0229b00c: the graphics of a frame: the blink stepped; rows' palettes asked for set
 * the texts of a friends' page in palette 3 and the picked row's in 4, and the map queued; the
 * map queued to the page's layer until the task takes it; the faded palettes queued (BG palette
 * 3 of the frame's layer, OBJ palette 10). */
void FriendRoster_UpdateGraphics(FriendRoster *self)
{
    FriendRoster_StepBlink(self);
    if (FriendRoster_TestFlags(self, FRIEND_ROSTER_FLAG_ROWS_DIRTY)) {
        if (self->page <= FRIEND_ROSTER_PAGE_FRIENDS_LAST) {
            ScreenMap_SetPalette(self->list_map, 5, 6, 0x17, 0x15, FRIEND_ROSTER_PALETTE_ROW);
            s16 picked = self->highlight;
            if (picked != -1) {
                int top = picked * 2 + 6;
                ScreenMap_SetPalette(self->list_map, 5, top, 0x17, top + 1, FRIEND_ROSTER_PALETTE_PICKED);
            }
        }
        FriendRoster_ClearFlags(self, FRIEND_ROSTER_FLAG_ROWS_DIRTY);
        FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_MAP_DIRTY);
    }
    if (FriendRoster_TestFlags(self, FRIEND_ROSTER_FLAG_MAP_DIRTY)) {
        if (LayerTask_QueueScreen(&self->tasks[0], (int) (uintptr_t) self->map, FRIEND_ROSTER_LAYER_PAGE,
                                  sizeof(self->list_map), 0)) {
            FriendRoster_ClearFlags(self, FRIEND_ROSTER_FLAG_MAP_DIRTY);
        }
    }
    if (FriendRoster_TestFlags(self, FRIEND_ROSTER_FLAG_FADED)) {
        LayerTask_QueuePalette(&self->tasks[1], (int) (uintptr_t) self->bg_faded, FRIEND_ROSTER_LAYER_FRAME, 3);
        LayerTask_QueuePalette(&self->tasks[2], (int) (uintptr_t) self->obj_faded, FRIEND_ROSTER_LAYER_OBJ, 0xa);
    }
}
CLEAN_AS(func_ov119_0229b00c, FriendRoster_UpdateGraphics)

/* func_ov119_0229bacc: the page's title, message `message` centred at tile 0x160. */
void FriendRoster_ShowPageTitle(FriendRoster *self, int message)
{
    TextLabel *label = FriendRoster_NextLabel(self);
    TextLabel_LoadMenuMessage(label, (char) message);
    fr_open_label(label, 8, 0x160, 0xd, 1);
}
CLEAN_AS(func_ov119_0229bacc, FriendRoster_ShowPageTitle)

/* func_ov119_0229bb0c: the scene's title, message 0xd6 centred at tile 0xca. */
void FriendRoster_ShowTitle(FriendRoster *self)
{
    TextLabel *label = FriendRoster_NextLabel(self);
    TextLabel_LoadMenuMessage(label, (char) FRIEND_ROSTER_MESSAGE_TITLE);
    fr_open_label(label, 8, 0xca, 6, 1);
}
CLEAN_AS(func_ov119_0229bb0c, FriendRoster_ShowTitle)

/* func_ov119_0229bb44: the next label to draw a text with; once all nineteen are handed out,
 * the last one again. */
TextLabel *FriendRoster_NextLabel(FriendRoster *self)
{
    if (self->labels_used >= FRIEND_ROSTER_LABELS) {
        return &self->labels[FRIEND_ROSTER_LABELS - 1];
    }
    self->labels_used++;
    return &self->labels[self->labels_used - 1];
}
CLEAN_AS(func_ov119_0229bb44, FriendRoster_NextLabel)

/* func_ov119_0229bb7c: none handed out, every label's box closed. */
void FriendRoster_ReleaseLabels(FriendRoster *self)
{
    self->labels_used = 0;
    for (int i = 0; i < FRIEND_ROSTER_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov119_0229bb7c, FriendRoster_ReleaseLabels)

/* func_ov119_0229c1a0: the OBJs' characters (obj0.bch to 0xc0-0x15d, obj1.bch to 0x1a0-0x1df)
 * and palettes 4-10 (obj.bpl), and obj1.bpl read into `obj_palette` for the fade. */
void FriendRoster_LoadObjGraphics(FriendRoster *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov119_0229cf00, heap, FRIEND_ROSTER_LAYER_OBJ, 0xc0, 0xc0, 0x15d);
    DisplayLayer_LoadCharsFromFile(data_ov119_0229cf18, heap, FRIEND_ROSTER_LAYER_OBJ, 0x1a0, 0x1a0, 0x1df);
    DisplayLayer_LoadPalettesFromFile(data_ov119_0229cf30, heap, FRIEND_ROSTER_LAYER_OBJ, 4, 4, 0xa);
    RomFile_Read(data_ov119_0229cf44, self->obj_palette, sizeof(self->obj_palette));
}
CLEAN_AS(func_ov119_0229c1a0, FriendRoster_LoadObjGraphics)

/* func_ov119_0229c218: the frame's palettes 1-5 (bg0.bpl), bg2.bpl read into `bg_palette` for
 * the fade, its characters 0x11-0x89 (bg0.bch) and screen (a_bg.bsc), and the two maps of the
 * page's layer read (b_bg.bsc, d_bg.bsc). */
void FriendRoster_LoadBgGraphics(FriendRoster *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov119_0229cf5c, heap, FRIEND_ROSTER_LAYER_FRAME, 1, 1, 5);
    RomFile_Read(data_ov119_0229cf70, self->bg_palette, sizeof(self->bg_palette));
    DisplayLayer_LoadCharsFromFile(data_ov119_0229cf84, heap, FRIEND_ROSTER_LAYER_FRAME, 0x11, 0x11, 0x89);
    DisplayLayer_LoadScreenFromFile(data_ov119_0229cf98, heap, FRIEND_ROSTER_LAYER_FRAME);
    RomFile_Read(data_ov119_0229cfb0, self->list_map, sizeof(self->list_map));
    RomFile_Read(data_ov119_0229cfc8, self->key_map, sizeof(self->key_map));
}
CLEAN_AS(func_ov119_0229c218, FriendRoster_LoadBgGraphics)
