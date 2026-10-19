/* The keyboard entry scene of overlay 126 (keyboard_entry.h): its destructors, its flags, the
 * taboo filter, and the text of each mode: where it comes from and where it goes. */
#include "keyboard_entry.h"

#include "clean.h"
#include "keyboard_entry_calls.h"
#include "main/constellations.h"
#include "main/design_info.h"
#include "main/design_sets.h"
#include "main/group_params.h"
#include "main/message_reader.h"
#include "main/name_texts.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/text_base.h"
#include "main/text_string.h"
#include "main/town_name.h"
#include "main/wfc_stats.h"
#include "ov124/han_panel.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(KeyboardEntry, wipe_y) == 0x94, "wipe");
static_assert(offsetof(KeyboardEntry, hint_x) == 0xa0 && offsetof(KeyboardEntry, flags) == 0xa4, "flags");
static_assert(offsetof(KeyboardEntry, position) == 0xa8 && offsetof(KeyboardEntry, field_left) == 0xab, "bytes");
static_assert(offsetof(KeyboardEntry, field_width) == 0xaf && offsetof(KeyboardEntry, field) == 0xb0, "field");
static_assert(offsetof(KeyboardEntry, keyboard) == 0x19c && offsetof(KeyboardEntry, tasks) == 0x24a4, "keyboard");
static_assert(offsetof(KeyboardEntry, labels) == 0x24ec && offsetof(KeyboardEntry, panel) == 0x3dc4, "panel");
static_assert(offsetof(KeyboardEntry, pointer) == 0x3f90 && offsetof(KeyboardEntry, hint) == 0x3ff4, "pointer");
static_assert(offsetof(KeyboardEntry, filter_text) == 0x4060 && offsetof(KeyboardEntry, filter_wide) == 0x40cc, "filter");
static_assert(offsetof(KeyboardEntry, error) == 0x412c && offsetof(KeyboardEntry, text) == 0x4248, "text");
static_assert(offsetof(KeyboardEntry, clipboard) == 0x4268 && sizeof(KeyboardEntry) == 0x4288, "size (func_ov126_022a1ef0)");
static_assert(sizeof(WifiFriend) == 0x24 && sizeof(DesignTitle) == 0x14, "friend, title");

/* The scene's vtable. */
extern const u8 data_ov126_022a20c8[];

/* The labels' destructor is handed to __cxa_vec_cleanup, so it is the game's symbol. */
extern int **func_02070be8(void *label);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The town record's statistics (WfcStats), the town (its number and name) and the four
 * players' records. */
extern u8 data_021f3278[];
extern u8 data_021dc7aa[];
extern u8 data_021dc7bc[];

/* The message archives the text is compared with: "st_password", "st_general". */
extern const char data_ov126_022a2128[];
extern const char data_ov126_022a2134[];

/* The song items (main/house_record.h): their names are compared with the text. */
#define KEYBOARD_ENTRY_SONG_FIRST 0x1323
#define KEYBOARD_ENTRY_SONG_LAST 0x1368

#define KEYBOARD_ENTRY_PLAYERS 4

static int keyboard_entry_label_arg(TextLabel *label)
{
    return (int) (uintptr_t) label;
}

/* --- The destructors and the flags --- */

/* The members' destructors, last member first, then the base's. */
static void keyboard_entry_destroy_members(KeyboardEntry *self)
{
    self->base.vtable = data_ov126_022a20c8;
    ErrorMessage_Destruct(&self->error);
    WideText_Destruct(&self->filter_wide);
    TextLabel_Destruct(&self->filter_text);
    TextLabel_Destruct(&self->hint);
    Glider0_Destroy(&self->pointer);
    ButtonPanel_Destroy(&self->panel);
    __cxa_vec_cleanup(self->labels, 2, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    HanPanel_Destroy((HanPanel *) (void *) self->field);
    MenuScene_DestroyBase(&self->base);
}

/* func_ov126_0229f6a0: the destructor. */
KeyboardEntry *KeyboardEntry_Destroy(KeyboardEntry *self)
{
    keyboard_entry_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov126_0229f6a0, KeyboardEntry_Destroy)

/* func_ov126_0229f720: the deleting destructor. */
KeyboardEntry *KeyboardEntry_Delete(KeyboardEntry *self)
{
    keyboard_entry_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov126_0229f720, KeyboardEntry_Delete)

/* func_ov126_0229f7a8 */
void KeyboardEntry_ClearFlags(KeyboardEntry *self, unsigned short mask)
{
    self->flags &= (u16) ~mask;
}
CLEAN_AS(func_ov126_0229f7a8, KeyboardEntry_ClearFlags)

/* func_ov126_0229f7b8 */
void KeyboardEntry_SetFlags(KeyboardEntry *self, unsigned short mask)
{
    self->flags |= mask;
}
CLEAN_AS(func_ov126_0229f7b8, KeyboardEntry_SetFlags)

/* func_ov126_0229f7c8: 1 when any of `mask` is set. */
int KeyboardEntry_TestFlags(KeyboardEntry *self, unsigned int mask)
{
    return (self->flags & mask) != 0;
}
CLEAN_AS(func_ov126_0229f7c8, KeyboardEntry_TestFlags)

/* --- The text committed --- */

/* func_ov126_0229f7dc: the text run through the taboo filter: carried into the 8-bit label,
 * filtered there and, when the filter changed it, carried back. */
void KeyboardEntry_FilterTaboo(KeyboardEntry *self)
{
    TextBase_SetWide(&self->filter_wide, self->text, self->max_chars);
    TextBase_WideToBytes((TextBase *) (void *) &self->filter_text, (WideTextBase *) (void *) &self->filter_wide, 0, 0);
    if (MessageReader_FilterTaboo(&self->filter_text)) {
        TextBase_BytesToWide((WideTextBase *) (void *) &self->filter_wide, (TextBase *) (void *) &self->filter_text);
        TextString_CopyWideOut((TextObject *) (void *) &self->filter_wide, self->text, self->max_chars);
    }
}
CLEAN_AS(func_ov126_0229f7dc, KeyboardEntry_FilterTaboo)

/* func_ov126_0229f83c: the text taken where the mode says, after the taboo filter for every mode
 * but the three that compare the text (0x0c-0x0e). Modes 0x11, 0x13 and 0x15-0x17 only hand the
 * text to main (KeyboardEntry_WipeOut does that for all). */
void KeyboardEntry_Commit(KeyboardEntry *self)
{
    unsigned int mode = GroupParams_Mode();

    if (mode != KEYBOARD_ENTRY_MODE_GENERAL_WORD && mode != KEYBOARD_ENTRY_MODE_SONG && mode != KEYBOARD_ENTRY_MODE_PASSWORD) {
        KeyboardEntry_FilterTaboo(self);
    }
    switch (mode) {
        case KEYBOARD_ENTRY_MODE_DESIGN_TITLE:
            KeyboardEntry_CommitDesignTitle(self);
            break;
        case KEYBOARD_ENTRY_MODE_GENERAL_WORD:
            KeyboardEntry_CheckGeneralWord(self);
            break;
        case KEYBOARD_ENTRY_MODE_SONG:
            KeyboardEntry_FindSong(self);
            break;
        case KEYBOARD_ENTRY_MODE_PASSWORD:
            KeyboardEntry_CheckPassword(self);
            break;
        case KEYBOARD_ENTRY_MODE_PLAYER_NAME:
            KeyboardEntry_CommitPlayerName(self);
            break;
        case KEYBOARD_ENTRY_MODE_TOWN_NAME:
            KeyboardEntry_CommitTownName(self);
            break;
        case KEYBOARD_ENTRY_MODE_CONSTELLATION:
            KeyboardEntry_CommitConstellation(self);
            break;
        case KEYBOARD_ENTRY_MODE_RECORD_DESIGN_TITLE:
            KeyboardEntry_CommitRecordDesignTitle(self);
            break;
        case KEYBOARD_ENTRY_MODE_FRIEND_TEXT_18:
        case KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_18:
            KeyboardEntry_CommitFriendText18(self);
            break;
        case KEYBOARD_ENTRY_MODE_FRIEND_TEXT_0C:
        case KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_0C:
            KeyboardEntry_CommitFriendText0C(self);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov126_0229f83c, KeyboardEntry_Commit)

/* func_ov126_0229f8e8: the text's first six characters into the friend's text 0x0c. */
void KeyboardEntry_CommitFriendText0C(KeyboardEntry *self)
{
    TextString_CopyChars(self->text, WifiFriend_GetText0C(KeyboardEntry_Friend()), WIFI_FRIEND_TEXT_LENGTH);
}
CLEAN_AS(func_ov126_0229f8e8, KeyboardEntry_CommitFriendText0C)

/* func_ov126_0229f90c: the text's first six characters into the friend's text 0x18. */
void KeyboardEntry_CommitFriendText18(KeyboardEntry *self)
{
    TextString_CopyChars(self->text, WifiFriend_GetText18(KeyboardEntry_Friend()), WIFI_FRIEND_TEXT_LENGTH);
}
CLEAN_AS(func_ov126_0229f90c, KeyboardEntry_CommitFriendText18)

/* func_ov126_0229f930: the text's first ten characters as the title of the town record's
 * design. */
void KeyboardEntry_CommitRecordDesignTitle(KeyboardEntry *self)
{
    DesignTitle title;
    struct Design *design = WfcStats_Design((WfcStats *) (void *) data_021f3278);
    TextString_CopyChars(self->text, title.chars, DESIGN_TITLE_LENGTH);
    unsigned int info = Design_Info((unsigned int) (uintptr_t) design);
    DesignInfo_SetTitle((DesignInfo *) (uintptr_t) info, &title);
}
CLEAN_AS(func_ov126_0229f930, KeyboardEntry_CommitRecordDesignTitle)

/* func_ov126_0229f968: the text as the name of constellation `arg`; main is told the input
 * failed (0) when another constellation has the name, which is set all the same. */
void KeyboardEntry_CommitConstellation(KeyboardEntry *self)
{
    int number = GroupParams_Arg();
    if (Constellations_NameTaken(self->text, number)) {
        GroupParams_SetC4C(KEYBOARD_ENTRY_OUTCOME_CANCELLED);
    }
    Constellations_SetName(self->text, number);
}
CLEAN_AS(func_ov126_0229f968, KeyboardEntry_CommitConstellation)

/* func_ov126_0229f9a0: the text as the town's name. */
void KeyboardEntry_CommitTownName(KeyboardEntry *self)
{
    TownName_Make((TownName *) (void *) data_021dc7aa, self->text);
}
CLEAN_AS(func_ov126_0229f9a0, KeyboardEntry_CommitTownName)

/* func_ov126_0229f9b8: the text as the current player's name, unless another player of the town
 * has it (its first six characters, trimmed): then main is told so (2) and nothing is set.
 * QUIRK: the current player's name is asked for once more before its index, unused. */
void KeyboardEntry_CommitPlayerName(KeyboardEntry *self)
{
    u8 *current = PlayerRecords_Current();

    PlayerRecord_Player(current);
    DesignCreator *player = PlayerRecord_Player(current);
    int own = PlayerRecords_FindIndex(data_021dc7bc, (const PlayerRecordsId *) (void *) player);
    for (int i = 0; i < KEYBOARD_ENTRY_PLAYERS; i++) {
        if (i == own || PlayerRecords_TownExists(data_021dc7bc, i) == 0) {
            continue;
        }
        DesignCreator *other = PlayerRecord_Player(PlayerRecords_TownRecord(data_021dc7bc, i));
        const u16 *name = (const u16 *) (uintptr_t) PlayerId_Name((int) (uintptr_t) other);
        if (TextString_EqualTrimmed(name, self->text, WIFI_FRIEND_TEXT_LENGTH) != 0) {
            GroupParams_SetC4C(KEYBOARD_ENTRY_OUTCOME_NAME_TAKEN);
            return;
        }
    }
    PlayerId_SetName(PlayerRecord_Player(current), self->text);
}
CLEAN_AS(func_ov126_0229f9b8, KeyboardEntry_CommitPlayerName)

/* Message `arg` of an archive compared with the text (trimmed): main is told the input failed
 * (0) when they differ. */
static void keyboard_entry_check_message(KeyboardEntry *self, const char *archive)
{
    TextLabel label;

    TextLabel_Construct(&label);
    int number = GroupParams_Arg();
    TextLabel_LoadMessage(keyboard_entry_label_arg(&label), (char *) (uintptr_t) archive, (char) number);
    if (TextLabel_EqualsTrimmed(&label, self->text, self->max_chars) == 0) {
        GroupParams_SetC4C(KEYBOARD_ENTRY_OUTCOME_CANCELLED);
    }
    TextLabel_Destruct(&label);
}

/* func_ov126_0229fa38: the text compared with password `arg` ("st_password"). */
void KeyboardEntry_CheckPassword(KeyboardEntry *self)
{
    keyboard_entry_check_message(self, data_ov126_022a2128);
}
CLEAN_AS(func_ov126_0229fa38, KeyboardEntry_CheckPassword)

/* func_ov126_0229fa80: the song whose name is the text (trimmed): main is given its number
 * (GroupParams_SetArg) and told the input succeeded (1); else told it failed (0). */
void KeyboardEntry_FindSong(KeyboardEntry *self)
{
    NameText name;
    TextLabel label;

    NameText_Construct(&name);
    TextLabel_Construct(&label);
    for (u16 song = KEYBOARD_ENTRY_SONG_FIRST; song <= KEYBOARD_ENTRY_SONG_LAST; song++) {
        u16 item = song;
        NameText_SetItem(&name, &item);
        TextBase_Copy((TextBase *) (void *) &label, (TextBase *) (void *) &name);
        if (TextLabel_EqualsTrimmed(&label, self->text, self->max_chars) != 0) {
            GroupParams_SetArg((u8) (song - KEYBOARD_ENTRY_SONG_FIRST));
            GroupParams_SetC4C(KEYBOARD_ENTRY_OUTCOME_DONE);
            TextLabel_Destruct(&label);
            NameText_Destruct(&name);
            return;
        }
    }
    GroupParams_SetC4C(KEYBOARD_ENTRY_OUTCOME_CANCELLED);
    TextLabel_Destruct(&label);
    NameText_Destruct(&name);
}
CLEAN_AS(func_ov126_0229fa80, KeyboardEntry_FindSong)

/* func_ov126_0229fb10: the text compared with message `arg` of "st_general". */
void KeyboardEntry_CheckGeneralWord(KeyboardEntry *self)
{
    keyboard_entry_check_message(self, data_ov126_022a2134);
}
CLEAN_AS(func_ov126_0229fb10, KeyboardEntry_CheckGeneralWord)

/* The current player's design `arg`, in the designs' order. */
static unsigned int keyboard_entry_design_info(void)
{
    PlayerDesigns *designs = PlayerRecord_Designs(PlayerRecords_Current());
    int place = GroupParams_Arg();
    int design = PlayerDesigns_InOrder(designs, place);
    return (unsigned int) design;
}

/* func_ov126_0229fb58: the text's first ten characters as the title of the current player's
 * design `arg`. */
void KeyboardEntry_CommitDesignTitle(KeyboardEntry *self)
{
    DesignTitle title;
    unsigned int design = keyboard_entry_design_info();
    TextString_CopyChars(self->text, title.chars, DESIGN_TITLE_LENGTH);
    unsigned int info = Design_Info(design);
    DesignInfo_SetTitle((DesignInfo *) (uintptr_t) info, &title);
}
CLEAN_AS(func_ov126_0229fb58, KeyboardEntry_CommitDesignTitle)

/* --- The text loaded --- */

/* func_ov126_0229fb9c: the text the input starts with, by the mode; the modes not named start
 * with the empty text the setup left. */
void KeyboardEntry_LoadText(KeyboardEntry *self)
{
    switch (GroupParams_Mode()) {
        case KEYBOARD_ENTRY_MODE_11:
        case KEYBOARD_ENTRY_MODE_15:
        case 0x16:
        case KEYBOARD_ENTRY_MODE_17:
            TextString_CopyChars(GroupParams_Text(), self->text, self->max_chars);
            break;
        case KEYBOARD_ENTRY_MODE_DESIGN_TITLE:
            KeyboardEntry_LoadDesignTitle(self);
            break;
        case KEYBOARD_ENTRY_MODE_CONSTELLATION:
            KeyboardEntry_LoadConstellation(self);
            break;
        case KEYBOARD_ENTRY_MODE_FRIEND_TEXT_18:
        case KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_18:
            KeyboardEntry_LoadFriendText18(self);
            break;
        case KEYBOARD_ENTRY_MODE_FRIEND_TEXT_0C:
        case KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_0C:
            KeyboardEntry_LoadFriendText0C(self);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov126_0229fb9c, KeyboardEntry_LoadText)

/* func_ov126_0229fc14: the friend's text 0x0c as the text. */
void KeyboardEntry_LoadFriendText0C(KeyboardEntry *self)
{
    TextString_CopyChars(WifiFriend_GetText0C(KeyboardEntry_Friend()), self->text, WIFI_FRIEND_TEXT_LENGTH);
}
CLEAN_AS(func_ov126_0229fc14, KeyboardEntry_LoadFriendText0C)

/* func_ov126_0229fc34: the friend's text 0x18 as the text. */
void KeyboardEntry_LoadFriendText18(KeyboardEntry *self)
{
    TextString_CopyChars(WifiFriend_GetText18(KeyboardEntry_Friend()), self->text, WIFI_FRIEND_TEXT_LENGTH);
}
CLEAN_AS(func_ov126_0229fc34, KeyboardEntry_LoadFriendText18)

/* func_ov126_0229fc54: friend `arg` of the current player's roster. */
WifiFriend *KeyboardEntry_Friend(void)
{
    WifiFriendList *list = PlayerRecord_WifiFriends(PlayerRecords_Current());
    int index = GroupParams_Arg();
    WifiFriend *friends = WifiFriendList_GetEntries(list);
    return &friends[index];
}
CLEAN_AS(func_ov126_0229fc54, KeyboardEntry_Friend)

/* func_ov126_0229fc7c: the name of constellation `arg` as the text. */
void KeyboardEntry_LoadConstellation(KeyboardEntry *self)
{
    Constellations_GetName(self->text, GroupParams_Arg());
}
CLEAN_AS(func_ov126_0229fc7c, KeyboardEntry_LoadConstellation)

/* func_ov126_0229fc98: the title of the current player's design `arg` as the text. */
void KeyboardEntry_LoadDesignTitle(KeyboardEntry *self)
{
    DesignTitle title;
    unsigned int info = Design_Info(keyboard_entry_design_info());
    DesignInfo_GetTitle((DesignInfo *) (uintptr_t) info, &title);
    TextString_CopyChars(title.chars, self->text, DESIGN_TITLE_LENGTH);
}
CLEAN_AS(func_ov126_0229fc98, KeyboardEntry_LoadDesignTitle)
