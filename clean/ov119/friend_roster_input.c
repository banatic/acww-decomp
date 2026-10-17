/* The friend roster of overlay 119 (friend_roster.h): the cursor and the pen, the choices and
 * their actions, the cursor sprite, the sub states and the switch to another tab of the
 * menu. */
#include "friend_roster.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/network.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/oam_buffer.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/session.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/text_string.h"
#include "main/town_name.h"
#include "ov002/key_repeat.h"
#include "ov090/menu_tabs.h"

/* The pen (autoload_2/input.c): down, and gone down this frame; where it is. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* x */
extern u8 data_021f6c54; /* y */

/* The pad (autoload_2/input.h) and the buttons read in `pressed`. */
extern PadState data_021fbe40;
#define FRIEND_ROSTER_PAD_A 0x0001
#define FRIEND_ROSTER_PAD_B 0x0002
#define FRIEND_ROSTER_PAD_SELECT 0x0004
#define FRIEND_ROSTER_PAD_R 0x0100
#define FRIEND_ROSTER_PAD_L 0x0200
#define FRIEND_ROSTER_PAD_X 0x0400
#define FRIEND_ROSTER_PAD_Y 0x0800

/* The session (main/session.h). */
extern NetSession *data_020ccf94;

/* The six page tabs' cells; the second OBJ of each places the tab. */
extern const OamEntry *const data_ov119_0229cca8[FRIEND_ROSTER_PAGE_TABS];

/* The error messages (ErrorMessage_Open): the roster is full; the player is a friend already. */
#define FRIEND_ROSTER_ERROR_FULL 0x13
#define FRIEND_ROSTER_ERROR_KNOWN 0x14

/* The sounds (SoundSys_PlaySe): a page tab, the friend key's tab, a row or the button. */
#define FRIEND_ROSTER_SOUND_TAB 0x0b
#define FRIEND_ROSTER_SOUND_KEY_TAB 0x0f
#define FRIEND_ROSTER_SOUND_PICK 0x2b

/* The text codes of the choices' rows (ChoiceEntries_Add). */
#define FRIEND_ROSTER_TEXT_CANCEL 0x02
#define FRIEND_ROSTER_TEXT_YES 0x04
#define FRIEND_ROSTER_TEXT_NO 0x13
#define FRIEND_ROSTER_TEXT_REGISTER 0xce
#define FRIEND_ROSTER_TEXT_TAB_11 0xcf
#define FRIEND_ROSTER_TEXT_TAB_9 0xd0
#define FRIEND_ROSTER_TEXT_TAB_13 0xd1
#define FRIEND_ROSTER_TEXT_DELETE 0xd2
#define FRIEND_ROSTER_TEXT_ASK_DELETE 0xd3

/* The menu's tabs this scene opens (ov090's MenuTab). */
#define FRIEND_ROSTER_MENU_TAB_POCKETS 0
#define FRIEND_ROSTER_MENU_TAB_4 4
#define FRIEND_ROSTER_MENU_TAB_5 5
#define FRIEND_ROSTER_MENU_TAB_SELF 6
#define FRIEND_ROSTER_MENU_TAB_CLOSE 7
#define FRIEND_ROSTER_MENU_TAB_9 9
#define FRIEND_ROSTER_MENU_TAB_11 11
#define FRIEND_ROSTER_MENU_TAB_13 13
#define FRIEND_ROSTER_MENU_TAB_REGISTER 14

/* The layer the fade hides while the page changes (the page's map). */
#define FRIEND_ROSTER_LAYER_PAGE 4

static MenuScene *fr_scene(FriendRoster *self)
{
    return &self->base;
}

static PagedChoice *fr_choice(FriendRoster *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static MenuTabs *fr_menu(FriendRoster *self)
{
    return (MenuTabs *) (void *) Process_GetParent((Process *) (void *) self);
}

static CellLayerSprite *fr_sprite_cells(FriendRoster *self)
{
    /* The cursor sprite's base is main's cell layer sprite (ov002/glide.h). */
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void fr_update_sprite(FriendRoster *self)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) self->cursor_sprite.vtable;
    vtable[3](&self->cursor_sprite);
}

/* The pen went down this frame. */
static int fr_pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* ---- The choices */

/* func_ov119_0229a4e4: the menu asked to close while a choice is up: the choice cancelled, the
 * cursor sprite hidden, the choice closed, sub state 0x0c (which runs the cancel once it is
 * idle). */
void FriendRoster_CancelChoiceOnClose(FriendRoster *self)
{
    self->action = FRIEND_ROSTER_ACTION_CANCEL;
    FriendRoster_HideCursorSprite(self);
    PagedChoice_RequestClose(fr_choice(self), 0);
    MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_CHOICE_RUN);
}
CLEAN_AS(func_ov119_0229a4e4, FriendRoster_CancelChoiceOnClose)

/* func_ov119_0229a50c: the entries shown as a choice (the first row set apart for a
 * `question`), above y 0x9c for the button or 0xb8 for a row, opened; sub state 0x0a. The
 * question flag is cleared (FriendRoster_AskDelete sets it again after). */
void FriendRoster_ShowChoice(FriendRoster *self, int question)
{
    PagedChoice_ShowEntries(fr_choice(self), &self->entries, question);
    int bottom = self->cursor == FRIEND_ROSTER_PLACE_BUTTON ? 0x9c : 0xb8;
    PagedChoice_PlaceAbove(fr_choice(self), 0x100, bottom);
    PagedChoice_RequestOpen(fr_choice(self), 0);
    MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_CHOICE_OPEN);
    FriendRoster_ClearFlags(self, FRIEND_ROSTER_FLAG_QUESTION);
}
CLEAN_AS(func_ov119_0229a50c, FriendRoster_ShowChoice)

/* func_ov119_0229a560: the action picked (FriendRosterAction); a cancel and the values past 10
 * go back to the idle sub state. */
void FriendRoster_RunAction(FriendRoster *self)
{
    switch (self->action) {
        case FRIEND_ROSTER_ACTION_DELETE:
            FriendRoster_DeleteFriend(self);
            break;
        case FRIEND_ROSTER_ACTION_ASK_DELETE:
            FriendRoster_AskDelete(self);
            break;
        case FRIEND_ROSTER_ACTION_TAB_9:
            FriendRoster_OpenTabWithFriend(self, FRIEND_ROSTER_MENU_TAB_9);
            break;
        case FRIEND_ROSTER_ACTION_TAB_11:
            FriendRoster_OpenTabWithFriend(self, FRIEND_ROSTER_MENU_TAB_11);
            break;
        case FRIEND_ROSTER_ACTION_TAB_13:
            FriendRoster_OpenTabWithFriend(self, FRIEND_ROSTER_MENU_TAB_13);
            break;
        case FRIEND_ROSTER_ACTION_REGISTER:
            FriendRoster_OpenRegister(self);
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            FriendRoster_AddPlayer(self);
            break;
        default:
            FriendRoster_ReturnToIdle(self);
            break;
    }
}
CLEAN_AS(func_ov119_0229a560, FriendRoster_RunAction)

/* func_ov119_0229a5cc: the value kept with choice row `row`.
 * QUIRK: read from the scene's bytes as the ROM does, for any row. */
unsigned char FriendRoster_EntryValue(FriendRoster *self, int row)
{
    const u8 *bytes = (const u8 *) self;
    return bytes[offsetof(FriendRoster, entries) + offsetof(ChoiceEntries, values) + row];
}
CLEAN_AS(func_ov119_0229a5cc, FriendRoster_EntryValue)

/* ---- The cursor's places */

/* func_ov119_0229b0f8: the place under the pen at (x, y): a page tab (each 0x22 wide and 0x12
 * high, from its cell's second OBJ, 0x83 and 0x61 on), a shown row (16 pixels each from y 0x30,
 * x 0x18-0xc0), the button, else FRIEND_ROSTER_PLACE_NONE. */
int FriendRoster_PlaceAt(FriendRoster *self, int x, int y)
{
    int left = OamBuffer_ObjX(&data_ov119_0229cca8[0][1]) + 0x83;
    if (left <= x && left + 0x22 >= x) {
        for (int i = 0; i < FRIEND_ROSTER_PAGE_TABS; i++) {
            int top = OamBuffer_ObjY(&data_ov119_0229cca8[i][1]) + 0x61;
            if (top <= y && top + 0x12 >= y) {
                return (u8) (FRIEND_ROSTER_PLACE_TAB + i);
            }
        }
    }
    if (x >= 0x18 && x <= 0xc0 && y >= 0x30 && y < 0xb0) {
        int row = (y - 0x30) >> 4;
        if (row < self->rows_shown) {
            return (u8) row;
        }
    }
    if (x >= 0xc3 && x <= 0xf3 && y >= 0x9f && y <= 0xb5) {
        return FRIEND_ROSTER_PLACE_BUTTON;
    }
    return FRIEND_ROSTER_PLACE_NONE;
}
CLEAN_AS(func_ov119_0229b0f8, FriendRoster_PlaceAt)

/* func_ov119_0229b188: the cursor's place pressed. A place of the menu's bar switches to its
 * tab (unless it is this one); another page tab fades to its page (sub state 0x0e, with its
 * sound); a row is picked and the button pressed (palette 8), each opening its choice after 3
 * frames (sub state 8). Whether anything happened. */
int FriendRoster_PressCursorPlace(FriendRoster *self)
{
    u8 place = self->cursor;
    if (place >= FRIEND_ROSTER_PLACE_BAR && place <= FRIEND_ROSTER_PLACE_BAR_LAST) {
        return FriendRoster_SelectTab(self, place - FRIEND_ROSTER_PLACE_BAR) != 0;
    }
    if (place >= FRIEND_ROSTER_PLACE_TAB && place <= FRIEND_ROSTER_PLACE_TAB_LAST) {
        u8 tab = (u8) (place - FRIEND_ROSTER_PLACE_TAB);
        if (tab == self->tab) {
            return 0;
        }
        self->tab = tab;
        MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_FADE_OUT);
        if (tab == FRIEND_ROSTER_PAGE_OWN_KEY) {
            SoundSys_PlaySe(FRIEND_ROSTER_SOUND_KEY_TAB);
        } else {
            SoundSys_PlaySe(FRIEND_ROSTER_SOUND_TAB);
        }
        return 1;
    }
    if (place == FRIEND_ROSTER_PLACE_BUTTON) {
        self->button_palette = 8;
        self->delay = 3;
        MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_OPEN_DELAY);
        SoundSys_PlaySe(FRIEND_ROSTER_SOUND_PICK);
        return 1;
    }
    if (place <= FRIEND_ROSTER_PLACE_ROW_LAST) {
        self->highlight = place;
        FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_ROWS_DIRTY);
        self->delay = 3;
        MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_OPEN_DELAY);
        SoundSys_PlaySe(FRIEND_ROSTER_SOUND_PICK);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov119_0229b188, FriendRoster_PressCursorPlace)

/* ---- The roster's changes */

/* func_ov119_0229b248: after friend `index` was added: the slots made again, the friend's page
 * shown (or the page drawn again when it is the one selected), back to the idle sub state. */
void FriendRoster_Refresh(FriendRoster *self, int index)
{
    FriendRoster_BuildSlots(self);
    int page = FriendRoster_PageOfFriend(self, index);
    if (page != self->tab) {
        FriendRoster_ShowPage(self, (u8) page);
    } else {
        FriendRoster_RedrawPage(self);
    }
    FriendRoster_ReturnToIdle(self);
}
CLEAN_AS(func_ov119_0229b248, FriendRoster_Refresh)

/* func_ov119_0229b284 (actions 6-9): the session's player (action - 6) added as a friend at the
 * first free place: error 0x13 when the roster is full, 0x14 when the player's friend data is a
 * friend's already. The friend takes the player's friend data, name and town name; the menu is
 * told the roster changed. Online NitroDWC is given the friend too, retried in sub state 0x10
 * while it refuses. */
void FriendRoster_AddPlayer(FriendRoster *self)
{
    int index = FriendRoster_FreeIndex(self);
    if (index == -1) {
        FriendRoster_ShowError(self, FRIEND_ROSTER_ERROR_FULL);
        return;
    }
    u8 *record = PlayerRecords_OfPlayer(self->action - FRIEND_ROSTER_ACTION_PLAYER);
    if (FriendRoster_HasFriend(self, WifiAccount_GetFriendData(PlayerRecord_WifiAccount(record)))) {
        FriendRoster_ShowError(self, FRIEND_ROSTER_ERROR_KNOWN);
        return;
    }
    WifiFriend *friends = FriendRoster_Friends(self);
    DesignCreator *player = PlayerRecord_Player(record);
    WifiFriend *entry = &friends[index];
    WifiFriendData *data = WifiFriend_GetFriendData(entry);
    WifiFriendData_Copy(data, WifiAccount_GetFriendData(PlayerRecord_WifiAccount(record)));
    const u16 *name = (const u16 *) (uintptr_t) PlayerId_Name((int) (uintptr_t) player);
    TextString_CopyChars(name, WifiFriend_GetText0C(entry), WIFI_FRIEND_TEXT_LENGTH);
    const u16 *town = (const u16 *) (uintptr_t) TownName_Name((int) (uintptr_t) PlayerId_Town(player));
    TextString_CopyChars(town, WifiFriend_GetText18(entry), WIFI_FRIEND_TEXT_LENGTH);
    MenuTabs_MarkRosterChanged(fr_menu(self));
    self->friend_index = (u8) index;
    if (FriendRoster_IsOnline(self)) {
        WifiFriend *added = &friends[self->friend_index];
        if (!Wfc_SetFriend(self->friend_index, WifiFriendData_GetData(WifiFriend_GetFriendData(added)))) {
            MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_RETRY_SET);
            return;
        }
    }
    FriendRoster_Refresh(self, index);
}
CLEAN_AS(func_ov119_0229b284, FriendRoster_AddPlayer)

/* func_ov119_0229b38c (action 5): a friend to register by friend key: the first free place
 * cleared and handed to the menu's tab 14 in GroupParams' argument, the bar slid out; error
 * 0x13 when the roster is full. */
void FriendRoster_OpenRegister(FriendRoster *self)
{
    int index = FriendRoster_FreeIndex(self);
    if (index == -1) {
        FriendRoster_ShowError(self, FRIEND_ROSTER_ERROR_FULL);
        return;
    }
    WifiFriend *friends = FriendRoster_Friends(self);
    WifiFriend_Clear(&friends[index]);
    GroupParams_SetArg((u8) index);
    FriendRoster_SelectTab(self, FRIEND_ROSTER_MENU_TAB_REGISTER);
    FriendRoster_SlideBarOut(self);
}
CLEAN_AS(func_ov119_0229b38c, FriendRoster_OpenRegister)

/* func_ov119_0229b3dc (actions 2-4): the menu's tab `tab` with the cursor's friend in
 * GroupParams' argument, the bar slid out. */
void FriendRoster_OpenTabWithFriend(FriendRoster *self, int tab)
{
    GroupParams_SetArg(FriendRoster_SlotAtCursor(self));
    FriendRoster_SelectTab(self, tab);
    FriendRoster_SlideBarOut(self);
}
CLEAN_AS(func_ov119_0229b3dc, FriendRoster_OpenTabWithFriend)

/* func_ov119_0229b408 (action 1): the cursor's friend cleared, no row picked, the page drawn
 * again; sub state 9 then finishes the delete (the roster and NitroDWC) a frame later. Nothing
 * for a row past the set friends. */
void FriendRoster_DeleteFriend(FriendRoster *self)
{
    WifiFriend *entry = FriendRoster_FriendAtCursor(self);
    if (entry == NULL) {
        return;
    }
    WifiFriend_Clear(entry);
    self->highlight = -1;
    FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_MAP_DIRTY);
    FriendRoster_RedrawPage(self);
    self->delay = 1;
    MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_DELETED);
    self->friend_index = FriendRoster_SlotAtCursor(self);
}
CLEAN_AS(func_ov119_0229b408, FriendRoster_DeleteFriend)

/* func_ov119_0229b450 (action 0): the question whether to delete (text 0xd3), then yes (action
 * 1) and no (a cancel). */
void FriendRoster_AskDelete(FriendRoster *self)
{
    ChoiceEntries_Clear(&self->entries, FRIEND_ROSTER_ACTION_CANCEL);
    ChoiceEntries_Add(&self->entries, FRIEND_ROSTER_TEXT_ASK_DELETE, FRIEND_ROSTER_ACTION_CANCEL);
    ChoiceEntries_Add(&self->entries, FRIEND_ROSTER_TEXT_YES, FRIEND_ROSTER_ACTION_DELETE);
    ChoiceEntries_Add(&self->entries, FRIEND_ROSTER_TEXT_NO, FRIEND_ROSTER_ACTION_CANCEL);
    FriendRoster_ShowChoice(self, 1);
    FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_QUESTION);
}
CLEAN_AS(func_ov119_0229b450, FriendRoster_AskDelete)

/* func_ov119_0229b49c: a friend's choice: tab 11 (text 0xcf), tab 9 (0xd0), tab 13 (0xd1, only
 * for a friend registered by friend key, WifiFriendData_IsNotFriendKey answering 0), delete
 * (0xd2) and cancel. */
void FriendRoster_OpenFriendChoice(FriendRoster *self)
{
    ChoiceEntries_Clear(&self->entries, FRIEND_ROSTER_ACTION_CANCEL);
    ChoiceEntries_Add(&self->entries, FRIEND_ROSTER_TEXT_TAB_11, FRIEND_ROSTER_ACTION_TAB_11);
    ChoiceEntries_Add(&self->entries, FRIEND_ROSTER_TEXT_TAB_9, FRIEND_ROSTER_ACTION_TAB_9);
    WifiFriend *entry = FriendRoster_FriendAtCursor(self);
    if (entry != NULL) {
        WifiFriendData *data = WifiFriend_GetFriendData(entry);
        if (WifiFriendData_IsNotFriendKey(data) == 0) {
            ChoiceEntries_Add(&self->entries, FRIEND_ROSTER_TEXT_TAB_13, FRIEND_ROSTER_ACTION_TAB_13);
        }
    }
    ChoiceEntries_Add(&self->entries, FRIEND_ROSTER_TEXT_DELETE, FRIEND_ROSTER_ACTION_ASK_DELETE);
    ChoiceEntries_Add(&self->entries, FRIEND_ROSTER_TEXT_CANCEL, FRIEND_ROSTER_ACTION_CANCEL);
    FriendRoster_ShowChoice(self, 0);
}
CLEAN_AS(func_ov119_0229b49c, FriendRoster_OpenFriendChoice)

/* func_ov119_0229b510: the button's choice, its palette back to 7: while the session is
 * linked, the name of each of its players other than this system's (action 6 + slot, for the
 * players present), then register by friend key (text 0xce) and cancel. */
void FriendRoster_OpenButtonChoice(FriendRoster *self)
{
    self->button_palette = 7;
    ChoiceEntries_Clear(&self->entries, FRIEND_ROSTER_ACTION_CANCEL);
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session)) {
        int local_slot = session->local_slot;
        PlayerIdText name;
        PlayerIdText_Construct(&name);
        for (int i = 0; i < 4; i++) {
            if (local_slot == i) {
                continue;
            }
            u8 *record = PlayerRecords_OfPlayer(i);
            if (record == NULL) {
                continue;
            }
            PlayerId_NameToText(PlayerRecord_Player(record), (TextBase *) (void *) &name);
            PagedChoice_AddTextEntry(fr_choice(self), &self->entries, &name, (u8) (i + FRIEND_ROSTER_ACTION_PLAYER));
        }
        PlayerIdText_Destruct(&name);
    }
    ChoiceEntries_Add(&self->entries, FRIEND_ROSTER_TEXT_REGISTER, FRIEND_ROSTER_ACTION_REGISTER);
    ChoiceEntries_Add(&self->entries, FRIEND_ROSTER_TEXT_CANCEL, FRIEND_ROSTER_ACTION_CANCEL);
    FriendRoster_ShowChoice(self, 0);
}
CLEAN_AS(func_ov119_0229b510, FriendRoster_OpenButtonChoice)

/* func_ov119_0229b5a8: the cursor moved by the repeated d-pad `keys`; whether it moved. From a
 * row: down and up along the shown rows (up from the first goes to the bar's place of this tab),
 * right to the page tab level with the cursor sprite (or the button below them). From the bar:
 * left and right along it, down to the first row on the left half with rows shown, else to the
 * first page tab. From a page tab: up and down along them (past them: the bar, the button),
 * left to the row level with the sprite. From the button: up to the last page tab, left to the
 * last row shown. */
int FriendRoster_MoveCursor(FriendRoster *self, int keys)
{
    unsigned int start = self->cursor;
    if (keys == 0) {
        return 0;
    }
    if (start <= FRIEND_ROSTER_PLACE_ROW_LAST) {
        if (KeyRepeat_HasDown(keys)) {
            if (self->cursor + 1 < self->rows_shown) {
                self->cursor = (u8) (self->cursor + 1);
            }
        } else if (KeyRepeat_HasUp(keys)) {
            if (self->cursor != 0) {
                self->cursor = (u8) (self->cursor - 1);
            } else {
                self->cursor = FRIEND_ROSTER_PLACE_BAR_SELF;
            }
        } else if (KeyRepeat_HasRight(keys)) {
            int y = Glider_ScreenY(&self->cursor_sprite);
            if (y > 0x94) {
                self->cursor = FRIEND_ROSTER_PLACE_BUTTON;
            } else {
                int tab = y - 0x35;
                if (tab < 0) {
                    tab = 0;
                }
                tab >>= 4;
                if (tab >= FRIEND_ROSTER_PAGE_TABS) {
                    tab = FRIEND_ROSTER_PAGE_TABS - 1;
                }
                self->cursor = (u8) (tab + FRIEND_ROSTER_PLACE_TAB);
            }
        }
    } else if (start >= FRIEND_ROSTER_PLACE_BAR && start <= FRIEND_ROSTER_PLACE_BAR_LAST) {
        if (KeyRepeat_HasLeft(keys)) {
            if (self->cursor > FRIEND_ROSTER_PLACE_BAR) {
                self->cursor = (u8) (self->cursor - 1);
            }
        } else if (KeyRepeat_HasRight(keys)) {
            if (self->cursor < FRIEND_ROSTER_PLACE_BAR_LAST) {
                self->cursor = (u8) (self->cursor + 1);
            }
        } else if (KeyRepeat_HasDown(keys)) {
            int x = Glider_ScreenX(&self->cursor_sprite);
            if (self->rows_shown != 0 && x < 0x80) {
                self->cursor = 0;
            } else {
                self->cursor = FRIEND_ROSTER_PLACE_TAB;
            }
        }
    } else if (start >= FRIEND_ROSTER_PLACE_TAB && start <= FRIEND_ROSTER_PLACE_TAB_LAST) {
        if (KeyRepeat_HasUp(keys)) {
            if (self->cursor > FRIEND_ROSTER_PLACE_TAB) {
                self->cursor = (u8) (self->cursor - 1);
            } else {
                self->cursor = FRIEND_ROSTER_PLACE_BAR_SELF;
            }
        } else if (KeyRepeat_HasDown(keys)) {
            if (self->cursor < FRIEND_ROSTER_PLACE_TAB_LAST) {
                self->cursor = (u8) (self->cursor + 1);
            } else {
                self->cursor = FRIEND_ROSTER_PLACE_BUTTON;
            }
        } else if (KeyRepeat_HasLeft(keys)) {
            if (self->rows_shown != 0) {
                int row = Glider_ScreenY(&self->cursor_sprite) - 0x30;
                if (row < 0) {
                    row = 0;
                }
                row >>= 4;
                if (row >= self->rows_shown) {
                    row = self->rows_shown - 1;
                }
                self->cursor = (u8) row;
            }
        }
    } else if (start == FRIEND_ROSTER_PLACE_BUTTON) {
        if (KeyRepeat_HasUp(keys)) {
            self->cursor = FRIEND_ROSTER_PLACE_TAB_LAST;
        }
        if (KeyRepeat_HasLeft(keys)) {
            if (self->rows_shown != 0) {
                self->cursor = (u8) (self->rows_shown - 1);
            }
        }
    }
    return start != self->cursor;
}
CLEAN_AS(func_ov119_0229b5a8, FriendRoster_MoveCursor)

/* ---- The cursor sprite */

/* func_ov119_0229b7c8: the sprite's first animation of its set, updated at once. */
void FriendRoster_ShowCursorSprite(FriendRoster *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    fr_update_sprite(self);
}
CLEAN_AS(func_ov119_0229b7c8, FriendRoster_ShowCursorSprite)

/* func_ov119_0229b7e8: the press let go (the third animation of the set), sub state 5. */
void FriendRoster_ReleaseCursorSprite(FriendRoster *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_PRESS_END);
}
CLEAN_AS(func_ov119_0229b7e8, FriendRoster_ReleaseCursorSprite)

/* func_ov119_0229b808: the press (the second animation of the set), sub state 4. */
void FriendRoster_PressCursorSprite(FriendRoster *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_PRESS);
}
CLEAN_AS(func_ov119_0229b808, FriendRoster_PressCursorSprite)

/* func_ov119_0229b828: the cursor on the choice's first row (its third, past the question,
 * when there is one), the sprite placed at the row's text with animation 7. */
void FriendRoster_PointAtChoice(FriendRoster *self)
{
    if (FriendRoster_TestFlags(self, FRIEND_ROSTER_FLAG_QUESTION)) {
        self->choice_row = 2;
    } else {
        self->choice_row = 0;
    }
    int x = PagedChoice_TextX(fr_choice(self));
    int y = PagedChoice_RowY(fr_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
}
CLEAN_AS(func_ov119_0229b828, FriendRoster_PointAtChoice)

/* func_ov119_0229b884: B in a choice: the cancel, its last row picked (with the sound), the
 * sprite there showing animation 8 at its end, sub state 0x0b. Answers what
 * MenuScene_SetSubState does. */
int FriendRoster_CancelChoice(FriendRoster *self)
{
    self->action = FRIEND_ROSTER_ACTION_CANCEL;
    self->choice_row = PagedChoice_PickLastRow(fr_choice(self), 1);
    int x = PagedChoice_TextX(fr_choice(self));
    int y = PagedChoice_RowY(fr_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    CellLayerSprite_SetAnimAtEnd(fr_sprite_cells(self), GLIDER_ANIM_SET_B + 1);
    return (int) (uintptr_t) MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_CHOICE_CLOSE);
}
CLEAN_AS(func_ov119_0229b884, FriendRoster_CancelChoice)

/* func_ov119_0229b8e4: the sprite moved in 2 steps to the choice row, then back to this sub
 * state (sub state 3 waits). */
void FriendRoster_MoveToChoiceRow(FriendRoster *self)
{
    int x = PagedChoice_TextX(fr_choice(self));
    int y = PagedChoice_RowY(fr_choice(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov119_0229b8e4, FriendRoster_MoveToChoiceRow)

/* func_ov119_0229b930: the sprite turned for the cursor's place (set B on a row, C on the bar,
 * A elsewhere) and eased there in 3 steps, then back to this sub state. */
void FriendRoster_EaseToCursor(FriendRoster *self)
{
    u8 place = self->cursor;
    if (place <= FRIEND_ROSTER_PLACE_ROW_LAST) {
        Glider_TurnToSetB(&self->cursor_sprite);
    } else if (place >= FRIEND_ROSTER_PLACE_BAR && place <= FRIEND_ROSTER_PLACE_BAR_LAST) {
        Glider_TurnToSetC(&self->cursor_sprite);
    } else {
        Glider_TurnToSetA(&self->cursor_sprite);
    }
    int x = FriendRoster_CursorX(self);
    int y = FriendRoster_CursorY(self);
    Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov119_0229b930, FriendRoster_EaseToCursor)

/* func_ov119_0229b9a4: the sprite shows nothing, updated at once. */
void FriendRoster_HideCursorSprite(FriendRoster *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    fr_update_sprite(self);
}
CLEAN_AS(func_ov119_0229b9a4, FriendRoster_HideCursorSprite)

/* func_ov119_0229b9c8: the y the sprite points at for the cursor's place. */
int FriendRoster_CursorY(FriendRoster *self)
{
    u8 place = self->cursor;
    if (place <= FRIEND_ROSTER_PLACE_ROW_LAST) {
        return place * 16 + 56;
    }
    if (place >= FRIEND_ROSTER_PLACE_BAR && place <= FRIEND_ROSTER_PLACE_BAR_LAST) {
        return 8;
    }
    if (place >= FRIEND_ROSTER_PLACE_TAB && place <= FRIEND_ROSTER_PLACE_TAB_LAST) {
        return (place - FRIEND_ROSTER_PLACE_TAB) * 16 + 63;
    }
    if (place == FRIEND_ROSTER_PLACE_BUTTON) {
        return 170;
    }
    return 96;
}
CLEAN_AS(func_ov119_0229b9c8, FriendRoster_CursorY)

/* func_ov119_0229ba00: the x the sprite points at for the cursor's place (the bar's from
 * MenuTabs_TabX). */
int FriendRoster_CursorX(FriendRoster *self)
{
    u8 place = self->cursor;
    if (place <= FRIEND_ROSTER_PLACE_ROW_LAST) {
        return 0x20;
    }
    if (place >= FRIEND_ROSTER_PLACE_BAR && place <= FRIEND_ROSTER_PLACE_BAR_LAST) {
        return MenuTabs_TabX(place - FRIEND_ROSTER_PLACE_BAR);
    }
    if (place >= FRIEND_ROSTER_PLACE_TAB && place <= FRIEND_ROSTER_PLACE_TAB_LAST) {
        return 0xd6;
    }
    if (place == FRIEND_ROSTER_PLACE_BUTTON) {
        return 0xdb;
    }
    return 0x80;
}
CLEAN_AS(func_ov119_0229ba00, FriendRoster_CursorX)

/* func_ov119_0229ba3c: the cursor kept on a shown row (the first page tab when none is shown),
 * the sprite placed at it with the animation of its place (7 a row, 13 the bar, 1 the others)
 * and shown. */
void FriendRoster_PlaceCursorSprite(FriendRoster *self)
{
    if (self->cursor <= FRIEND_ROSTER_PLACE_ROW_LAST) {
        u8 shown = self->rows_shown;
        if (shown == 0) {
            self->cursor = FRIEND_ROSTER_PLACE_TAB;
        } else if (shown <= self->cursor) {
            self->cursor = (u8) (shown - 1);
        }
    }
    int x = FriendRoster_CursorX(self);
    int y = FriendRoster_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    u8 place = self->cursor;
    if (place <= FRIEND_ROSTER_PLACE_ROW_LAST) {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
    } else if (place >= FRIEND_ROSTER_PLACE_BAR && place <= FRIEND_ROSTER_PLACE_BAR_LAST) {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_C);
    } else {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    }
    FriendRoster_ShowCursorSprite(self);
}
CLEAN_AS(func_ov119_0229ba3c, FriendRoster_PlaceCursorSprite)

/* ---- The sub states */

/* func_ov119_0229bba8: error message `message` opened, sub state 0x0d, the sprite hidden. */
void FriendRoster_ShowError(FriendRoster *self, unsigned char message)
{
    u8 number = message;
    ErrorMessage_Open(&self->error, &number, 1, 0);
    MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_ERROR);
    FriendRoster_HideCursorSprite(self);
}
CLEAN_AS(func_ov119_0229bba8, FriendRoster_ShowError)

/* func_ov119_0229bbe4: back to the idle sub state of the controls in use (the pen's, else the
 * keys'), no row picked. */
void FriendRoster_ReturnToIdle(FriendRoster *self)
{
    self->highlight = -1;
    FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_ROWS_DIRTY);
    if (StateFlags_IsClear2()) {
        FriendRoster_EnterTouch(self);
    } else {
        FriendRoster_EnterKeys(self);
    }
}
CLEAN_AS(func_ov119_0229bbe4, FriendRoster_ReturnToIdle)

/* func_ov119_0229bc14: the keys take over: the sprite at the cursor, the key repeat reset, sub
 * state 2. */
void FriendRoster_EnterKeys(FriendRoster *self)
{
    FriendRoster_PlaceCursorSprite(self);
    MenuScene_ResetKeyRepeat(fr_scene(self));
    MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_KEYS);
}
CLEAN_AS(func_ov119_0229bc14, FriendRoster_EnterKeys)

/* func_ov119_0229bc30: the pen takes over: the sprite hidden, sub state 0. */
void FriendRoster_EnterTouch(FriendRoster *self)
{
    FriendRoster_HideCursorSprite(self);
    MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_TOUCH);
}
CLEAN_AS(func_ov119_0229bc30, FriendRoster_EnterTouch)

/* func_ov119_0229bc48 (sub state 0x11): NitroDWC asked again to delete the friend; once it
 * does, the page is drawn again and the scene idles. */
void FriendRoster_RetryDeleteFriend(FriendRoster *self)
{
    if (Wfc_DeleteFriend(self->friend_index)) {
        FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_MAP_DIRTY);
        FriendRoster_RedrawPage(self);
        FriendRoster_ReturnToIdle(self);
    }
}
CLEAN_AS(func_ov119_0229bc48, FriendRoster_RetryDeleteFriend)

/* func_ov119_0229bc74 (sub state 0x10): NitroDWC asked again to take the added friend; once it
 * does, FriendRoster_Refresh. */
void FriendRoster_RetrySetFriend(FriendRoster *self)
{
    WifiFriend *friends = FriendRoster_Friends(self);
    WifiFriendData *data = WifiFriendData_GetData(WifiFriend_GetFriendData(&friends[self->friend_index]));
    if (Wfc_SetFriend(self->friend_index, data)) {
        FriendRoster_Refresh(self, self->friend_index);
    }
}
CLEAN_AS(func_ov119_0229bc74, FriendRoster_RetrySetFriend)

/* func_ov119_0229bcb0 (sub state 0x0f): the fade back in, a step a frame with the page's layer
 * shown; at its end the pen's idle sub state, or the keys' press let go. */
void FriendRoster_FadeIn(FriendRoster *self)
{
    if (self->fade < FRIEND_ROSTER_FADE_STEPS) {
        DisplayLayer_Show(FRIEND_ROSTER_LAYER_PAGE);
        self->fade++;
        FriendRoster_Fade(self, self->fade);
    } else if (StateFlags_IsClear2()) {
        FriendRoster_EnterTouch(self);
    } else {
        FriendRoster_ReleaseCursorSprite(self);
    }
}
CLEAN_AS(func_ov119_0229bcb0, FriendRoster_FadeIn)

/* func_ov119_0229bcf8 (sub state 0x0e): the fade out, a step a frame; at its end the page's
 * layer hidden, the selected tab's page shown, sub state 0x0f. */
void FriendRoster_FadeOut(FriendRoster *self)
{
    if (self->fade > 0) {
        self->fade--;
        FriendRoster_Fade(self, self->fade);
    } else {
        DisplayLayer_Hide(FRIEND_ROSTER_LAYER_PAGE);
        FriendRoster_ShowPage(self, self->tab);
        MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_FADE_IN);
    }
}
CLEAN_AS(func_ov119_0229bcf8, FriendRoster_FadeOut)

/* func_ov119_0229bd40 (sub state 0x0d): the error message until it closes,
 * then the idle sub state. */
void FriendRoster_WaitError(FriendRoster *self)
{
    if (ErrorMessage_Update(&self->error, 1)) {
        FriendRoster_ReturnToIdle(self);
    }
}
CLEAN_AS(func_ov119_0229bd40, FriendRoster_WaitError)

/* func_ov119_0229bd64 (sub state 0x0c): the action, once the choice is idle. */
void FriendRoster_RunActionWhenIdle(FriendRoster *self)
{
    if (PagedChoice_IsIdle(fr_choice(self))) {
        FriendRoster_RunAction(self);
    }
}
CLEAN_AS(func_ov119_0229bd64, FriendRoster_RunActionWhenIdle)

/* func_ov119_0229bd80 (sub state 0x0b): once the picked row's delay has run, the choice closed,
 * the sprite hidden if it shows anything, sub state 0x0c. */
void FriendRoster_CloseChoice(FriendRoster *self)
{
    if (PagedChoice_CountDown(fr_choice(self))) {
        PagedChoice_RequestClose(fr_choice(self), 0);
        if (CellLayerSprite_AnimNumber(fr_sprite_cells(self))) {
            FriendRoster_HideCursorSprite(self);
        }
        MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_CHOICE_RUN);
    }
}
CLEAN_AS(func_ov119_0229bd80, FriendRoster_CloseChoice)

/* func_ov119_0229bdbc (sub state 0x0a): once the choice is shown, its keys' sub state with the
 * sprite on its row, or its pen's. */
void FriendRoster_WaitChoiceShown(FriendRoster *self)
{
    if (PagedChoice_IsShown(fr_choice(self))) {
        if (StateFlags_Test2()) {
            FriendRoster_PointAtChoice(self);
            MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_CHOICE_KEYS);
        } else {
            MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_CHOICE_TOUCH);
        }
    }
}
CLEAN_AS(func_ov119_0229bdbc, FriendRoster_WaitChoiceShown)

/* func_ov119_0229bdf0 (sub state 9): the frame after a delete: the gaps closed, the menu told,
 * and online NitroDWC asked to delete the friend (sub state 0x11 retries while it refuses).
 * The next frame draws the page again and idles. */
void FriendRoster_FinishDelete(FriendRoster *self)
{
    if (self->delay != 0) {
        self->delay = 0;
        FriendRoster_Compact(self);
        MenuTabs_MarkRosterChanged(fr_menu(self));
        if (FriendRoster_IsOnline(self)) {
            if (!Wfc_DeleteFriend(self->friend_index)) {
                MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_RETRY_DELETE);
            }
        }
    } else {
        FriendRoster_SetFlags(self, FRIEND_ROSTER_FLAG_MAP_DIRTY);
        FriendRoster_RedrawPage(self);
        FriendRoster_ReturnToIdle(self);
    }
}
CLEAN_AS(func_ov119_0229bdf0, FriendRoster_FinishDelete)

/* func_ov119_0229be50 (sub state 8): after `delay` frames the sprite hidden and the choice of
 * the button or of the cursor's friend opened. */
void FriendRoster_WaitToOpenChoice(FriendRoster *self)
{
    if (self->delay != 0) {
        self->delay--;
        return;
    }
    FriendRoster_HideCursorSprite(self);
    if (self->cursor == FRIEND_ROSTER_PLACE_BUTTON) {
        FriendRoster_OpenButtonChoice(self);
    } else {
        FriendRoster_OpenFriendChoice(self);
    }
}
CLEAN_AS(func_ov119_0229be50, FriendRoster_WaitToOpenChoice)

/* func_ov119_0229be8c (sub state 7): a close cancels the choice; else once the sprite's press
 * has played, the cursor's row picked (with the sound), its action kept, sub state 0x0b. */
void FriendRoster_PressChoiceRow(FriendRoster *self)
{
    if (StateFlags_MenuCloseAsked()) {
        FriendRoster_CancelChoiceOnClose(self);
        return;
    }
    if (CellLayerSprite_IsDone(fr_sprite_cells(self))) {
        PagedChoice_PickRowWithSound(fr_choice(self), self->choice_row, 1);
        self->action = FriendRoster_EntryValue(self, self->choice_row);
        MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_CHOICE_CLOSE);
    }
}
CLEAN_AS(func_ov119_0229be8c, FriendRoster_PressChoiceRow)

/* func_ov119_0229bee0 (sub state 6): a choice by the keys. A close cancels it; the pen hands it
 * to sub state 1 (the sprite hidden); the d-pad moves the row (not onto a question); A presses
 * the row (sub state 7), B cancels. */
void FriendRoster_ChooseByKeys(FriendRoster *self)
{
    if (StateFlags_MenuCloseAsked()) {
        FriendRoster_CancelChoiceOnClose(self);
        return;
    }
    if (MenuScene_TakeTouch(fr_scene(self))) {
        FriendRoster_HideCursorSprite(self);
        MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_CHOICE_TOUCH);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(fr_scene(self));
    u8 first = (u8) FriendRoster_TestFlags(self, FRIEND_ROSTER_FLAG_QUESTION);
    if (PagedChoice_MoveCursor(fr_choice(self), keys, &self->choice_row, first)) {
        FriendRoster_MoveToChoiceRow(self);
    } else if (data_021fbe40.pressed & FRIEND_ROSTER_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_CHOICE_PRESS);
    } else if (data_021fbe40.pressed & FRIEND_ROSTER_PAD_B) {
        FriendRoster_CancelChoice(self);
    }
}
CLEAN_AS(func_ov119_0229bee0, FriendRoster_ChooseByKeys)

/* func_ov119_0229bf7c (sub state 5): once the press is let go, the sprite's first animation,
 * sub state 2. */
void FriendRoster_FinishPress(FriendRoster *self)
{
    if (CellLayerSprite_IsDone(fr_sprite_cells(self))) {
        FriendRoster_ShowCursorSprite(self);
        MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_KEYS);
    }
}
CLEAN_AS(func_ov119_0229bf7c, FriendRoster_FinishPress)

/* func_ov119_0229bfa4 (sub state 4): once the sprite's press has played, the cursor's place
 * pressed; when nothing happens the press is let go. */
void FriendRoster_PressPlace(FriendRoster *self)
{
    if (CellLayerSprite_IsDone(fr_sprite_cells(self))) {
        if (FriendRoster_PressCursorPlace(self) != 1) {
            FriendRoster_ReleaseCursorSprite(self);
        }
    }
}
CLEAN_AS(func_ov119_0229bfa4, FriendRoster_PressPlace)

/* Obj_ov119_0229cea0::func_ov119_0229bfdc (sub state 3): once the sprite stops, back to the sub
 * state it moved from, run at once. */
void FriendRoster_WaitCursorSprite(FriendRoster *self)
{
    if (!Glider_IsMoving(&self->cursor_sprite)) {
        MenuScene_SetSubState(fr_scene(self), self->return_sub_state);
        FriendRoster_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov119_0229cea019func_ov119_0229bfdcEv, FriendRoster_WaitCursorSprite)

/* func_ov119_0229c008 (sub state 2): the keys. The pen hands over to sub state 0; the d-pad
 * moves the cursor (the sprite eases after it); A presses the place; R and L switch to the
 * menu's next and previous tab. */
void FriendRoster_BrowseByKeys(FriendRoster *self)
{
    if (MenuScene_TakeTouch(fr_scene(self))) {
        FriendRoster_EnterTouch(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(fr_scene(self));
    if (FriendRoster_MoveCursor(self, keys)) {
        FriendRoster_EaseToCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & FRIEND_ROSTER_PAD_A) {
        FriendRoster_PressCursorSprite(self);
    } else if (pressed & FRIEND_ROSTER_PAD_R) {
        FriendRoster_SelectTab(self, MenuTabs_NextTab(FRIEND_ROSTER_MENU_TAB_SELF));
    } else if (pressed & FRIEND_ROSTER_PAD_L) {
        FriendRoster_SelectTab(self, MenuTabs_PreviousTab(FRIEND_ROSTER_MENU_TAB_SELF));
    }
}
CLEAN_AS(func_ov119_0229c008, FriendRoster_BrowseByKeys)

/* func_ov119_0229c090 (sub state 1): a choice by the pen. A close cancels it; the buttons hand
 * it to sub state 6 (the sprite on its first row); the pen picks the row under it (not a
 * question; with the sound) and keeps its action, sub state 0x0b. */
void FriendRoster_ChooseByTouch(FriendRoster *self)
{
    if (StateFlags_MenuCloseAsked()) {
        FriendRoster_CancelChoiceOnClose(self);
        return;
    }
    if (MenuScene_TakeButtons(fr_scene(self), 1)) {
        FriendRoster_PointAtChoice(self);
        MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_CHOICE_KEYS);
        return;
    }
    if (!fr_pen_pressed()) {
        return;
    }
    int row = PagedChoice_RowAtOrLast(fr_choice(self), data_021f6c58, data_021f6c54);
    if (row < 0) {
        return;
    }
    if (FriendRoster_TestFlags(self, FRIEND_ROSTER_FLAG_QUESTION) && row == 0) {
        return;
    }
    PagedChoice_PickRowWithSound(fr_choice(self), row, 1);
    self->action = FriendRoster_EntryValue(self, row);
    MenuScene_SetSubState(fr_scene(self), FRIEND_ROSTER_SUB_CHOICE_CLOSE);
}
CLEAN_AS(func_ov119_0229c090, FriendRoster_ChooseByTouch)

/* func_ov119_0229c13c (sub state 0): the pen. The buttons hand over to sub state 2; the pen
 * going down on a place moves the cursor there and presses it. */
void FriendRoster_IdleByTouch(FriendRoster *self)
{
    if (MenuScene_TakeButtons(fr_scene(self), 1)) {
        FriendRoster_EnterKeys(self);
        return;
    }
    if (fr_pen_pressed()) {
        int place = FriendRoster_PlaceAt(self, data_021f6c58, data_021f6c54);
        if (place != FRIEND_ROSTER_PLACE_NONE) {
            self->cursor = (u8) place;
            FriendRoster_PressCursorPlace(self);
        }
    }
}
CLEAN_AS(func_ov119_0229c13c, FriendRoster_IdleByTouch)

/* ---- The menu's tabs */

/* func_ov119_0229c5f4: the menu's bar slides out. */
void FriendRoster_SlideBarOut(FriendRoster *self)
{
    MenuTabs_SlideOut(fr_menu(self));
}
CLEAN_AS(func_ov119_0229c5f4, FriendRoster_SlideBarOut)

/* func_ov119_0229c608: the menu switched to `tab` (MenuTabs_SelectTab) and the scene wiped out
 * (state 3, phase 1); nothing for -1 or this tab. Whether it switched. */
int FriendRoster_SelectTab(FriendRoster *self, int tab)
{
    MenuTabs *menu = fr_menu(self);
    if (tab == -1 || tab == FRIEND_ROSTER_MENU_TAB_SELF) {
        return 0;
    }
    MenuTabs_SelectTab(menu, (u8) tab);
    self->base.state = FRIEND_ROSTER_STATE_WIPE_OUT;
    MenuScene_SetPhase(fr_scene(self), FRIEND_ROSTER_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov119_0229c608, FriendRoster_SelectTab)

/* func_ov119_0229c648: the menu's own controls, before the frame: the close's delay counted; a
 * close asked for in sub states 0, 2, 4, 5, 8, 14 and 15 closes the menu. In sub states 0 and 2
 * the bar's place the pen goes down on (with the pen in use), or B (close), Y (tab 0), X (tab
 * 5) and SELECT (tab 4) switch tabs. Whether it switched. */
int FriendRoster_TakeMenuKeys(FriendRoster *self)
{
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked()) {
        switch (self->base.sub_state) {
            case FRIEND_ROSTER_SUB_TOUCH:
            case FRIEND_ROSTER_SUB_KEYS:
            case FRIEND_ROSTER_SUB_PRESS:
            case FRIEND_ROSTER_SUB_PRESS_END:
            case FRIEND_ROSTER_SUB_OPEN_DELAY:
            case FRIEND_ROSTER_SUB_FADE_OUT:
            case FRIEND_ROSTER_SUB_FADE_IN:
                return FriendRoster_SelectTab(self, FRIEND_ROSTER_MENU_TAB_CLOSE);
            default:
                break;
        }
    }
    if (self->base.sub_state != FRIEND_ROSTER_SUB_TOUCH && self->base.sub_state != FRIEND_ROSTER_SUB_KEYS) {
        return 0;
    }
    int tab = -1;
    if (StateFlags_IsClear2()) {
        tab = MenuTabs_TabAtTouch();
    } else {
        u16 pressed = data_021fbe40.pressed;
        if (pressed & FRIEND_ROSTER_PAD_B) {
            tab = FRIEND_ROSTER_MENU_TAB_CLOSE;
        } else if (pressed & FRIEND_ROSTER_PAD_Y) {
            tab = FRIEND_ROSTER_MENU_TAB_POCKETS;
        } else if (pressed & FRIEND_ROSTER_PAD_X) {
            tab = FRIEND_ROSTER_MENU_TAB_5;
        } else if (pressed & FRIEND_ROSTER_PAD_SELECT) {
            tab = FRIEND_ROSTER_MENU_TAB_4;
        }
    }
    return FriendRoster_SelectTab(self, tab);
}
CLEAN_AS(func_ov119_0229c648, FriendRoster_TakeMenuKeys)
