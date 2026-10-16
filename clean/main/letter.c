/* Writing and reading a letter (letter.h). */
#include "letter.h"

#include "autoload_2/heap.h"
#include "autoload_2/links.h"
#include "clean.h"
#include "main/mail_text.h"
#include "main/message_reader.h"
#include "main/player_pockets.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/text_base.h"
#include "main/text_string.h"
#include "main/town_villager.h"
#include "main/villager_roster.h"

static_assert(sizeof(LetterParty) == 0x20 && offsetof(LetterParty, kind) == 0x1e, "party");
static_assert(offsetof(Letter, addressee) == 0x04 && offsetof(Letter, sender) == 0x24, "letter parties");
static_assert(offsetof(Letter, header) == 0x44 && offsetof(Letter, body) == 0x58 && offsetof(Letter, footer) == 0xd8,
              "letter texts");
static_assert(offsetof(Letter, header_line) == 0xf8 && offsetof(Letter, item) == 0xfc && sizeof(Letter) == 0x100, "letter");
static_assert(offsetof(LetterDefaults, footer) == 0x28 && offsetof(LetterDefaults, self_header_line) == 0x49, "defaults");
static_assert(offsetof(LetterBodyText, text) == 0x0e, "body text");

/* The vtables: the letter's and the body text's. */
extern const u32 data_020de760[];
extern const TextVtable data_020de770;

/* The three texts the letter message files are loaded into: header, body, footer. */
extern u8 data_021cd8c4[];
extern u8 data_021cd9b0[];
extern u8 data_021cd8ec[];

/* The body text Letter_SetTexts converts through, built on its first use (bit 0 of
 * data_021cd890) and registered for destruction at exit with its record data_021cd8ac. */
extern LetterBodyText data_021cd920;
extern u32 data_021cd890;
extern u8 data_021cd8ac[];
extern void __register_global_object(void *object, void *destruct, void *record);
/* The body text's destructor, as the game registers it. */
extern void *func_02065c98(void *text);

/* The four players' records. */
extern u8 data_021dc7bc[];
/* The town's villagers. */
extern u8 data_021e5a2c[];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern int func_02051c8c_unk(const u16 *text, int max); /* the characters before a 0, at most max */

/* A party's name: into a text object (func_0206671c) or as 16-bit characters (func_02066788). */
extern int func_0206671c(LetterParty *party, void *text);
extern void *func_02066788(LetterParty *party, u16 *name);
/* The party if it is a villager (kinds 3, 5) or a player (kinds 1, 2, 6), else NULL. */
extern LetterParty *func_020666f8(LetterParty *party);
extern LetterParty *func_02066708(LetterParty *party);
/* The party set to a player of kind 2 or to a villager of kind 3. */
extern void func_020666d0(LetterParty *party, const DesignCreator *player);
extern void func_020666e4(LetterParty *party, const NpcId *villager);
/* A player's 0x1e bytes copied into a party (the kind is not touched). */
extern void func_020951dc(const DesignCreator *player, LetterParty *party);

/* A player on the stack: built, copied from another and taken down. */
extern DesignCreator *func_0209529c(DesignCreator *player);
extern void func_0209525c(DesignCreator *player, const DesignCreator *src);
extern DesignCreator *func_0209526c(DesignCreator *player);

/* A name as a text object (0x24 bytes): built and taken down, and a player's name put in it. */
typedef struct LetterNameText {
    u32 words[9];
} LetterNameText;
extern void *func_02094fd4(LetterNameText *text);
extern void *func_02094fbc(LetterNameText *text);
extern void *func_02095074(const DesignCreator *player, LetterNameText *text);

#define LETTER_MESSAGE_HEADER 0x23      /* "2d_menu" message: the default header */
#define LETTER_MESSAGE_SELF_HEADER 0x26 /* the default header to oneself */
#define LETTER_MESSAGE_FOOTER 0x24      /* the default footer, with the sender's name */
#define LETTER_TEXT_LINE_MAX WIDE_TEXT_CAPACITY
#define LETTER_NO_PART MAIL_TEXT_PARTS
#define LETTER_BOTTLE_PAPER 0x0c
#define LETTER_BOTTLE_TAG 0x0c
#define LETTER_DELIVERED_TAG 0x11

/* --- The body text --- */

/* func_02065c70 (vtable entry 3): the address of the characters. */
int LetterBodyText_Buffer(int text)
{
    return (int) ((u32) text + offsetof(LetterBodyText, text));
}
CLEAN_AS(func_02065c70, LetterBodyText_Buffer)

/* func_02065c74 (vtable entry 2): the capacity in characters. */
int LetterBodyText_Capacity(void)
{
    return LETTER_BODY_CHARS;
}
CLEAN_AS(func_02065c74, LetterBodyText_Capacity)

/* func_02065c78 (vtable entry 1): the destructor, then the object freed. */
LetterBodyText *LetterBodyText_DestructDelete(LetterBodyText *text)
{
    text->vtable = &data_020de770;
    TextBase_WideDestruct(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_02065c78, LetterBodyText_DestructDelete)

/* func_02065c98 (vtable entry 0): the destructor. */
void *LetterBodyText_Destruct(void *text)
{
    ((LetterBodyText *) text)->vtable = &data_020de770;
    TextBase_WideDestruct(text);
    return text;
}
CLEAN_AS(func_02065c98, LetterBodyText_Destruct)

/* func_02065cb0: the constructor: the wide text base, then the vtable. */
void *LetterBodyText_Construct(void *text)
{
    TextBase_WideConstruct(text);
    ((LetterBodyText *) text)->vtable = &data_020de770;
    return text;
}
CLEAN_AS(func_02065cb0, LetterBodyText_Construct)

/* --- The defaults and the texts --- */

/* func_02065cc8: a player's defaults cleared, and both headers loaded from their messages. */
void LetterDefaults_Init(LetterDefaults *defaults)
{
    char message;

    MI_CpuFill8(defaults, 0, sizeof(LetterDefaults));
    message = LETTER_MESSAGE_HEADER;
    Letter_LoadText(&message, defaults->header, &defaults->header_line, NULL);
    message = LETTER_MESSAGE_SELF_HEADER;
    Letter_LoadText(&message, defaults->self_header, &defaults->self_header_line, NULL);
}
CLEAN_AS(func_02065cc8, LetterDefaults_Init)

/* func_02065d0c: the "2d_menu" message whose number is at `message`, written to `dst`: its
 * first line (its length to *first_line), then `name` (up to 6 characters, before its first 0)
 * when given, then, when the first line ended with a newline, the second line.
 * REQUIRES: the first line is shorter than 41 characters; else the original tests the
 * character after the wide text, from its own stack, where Clean takes no second line. */
void Letter_LoadText(const char *message, u16 *dst, u8 *first_line, const u16 *name)
{
    TextLabel label;
    WideText wide;

    TextLabel_Construct(&label);
    WideText_Construct(&wide);
    MessageReader_LoadMenuMessage((int) (uintptr_t) &label, (unsigned char *) (uintptr_t) message, NULL);
    TextBase_BytesToWide((WideTextBase *) (void *) &wide, (TextBase *) (void *) &label);

    u16 *text = wide.text;
    int length = TextString_LineLength(text, LETTER_TEXT_LINE_MAX, 0);
    *first_line = (u8) length;
    if (length != 0) {
        TextString_CopyChars(text, dst, length);
    }

    int written = length;
    if (name != NULL) {
        int name_length = func_02051c8c_unk(name, LETTER_NAME_CHARS);
        TextString_CopyChars(name, dst + length, name_length);
        written = length + name_length;
    }

    if (length < LETTER_TEXT_LINE_MAX && text[length] == TEXT_STRING_NEWLINE) {
        int start = length + 1;
        int second = TextString_LineLength(text + start, LETTER_TEXT_LINE_MAX - start, 0);
        if (second != 0) {
            TextString_CopyChars(text + start, dst + written, second);
        }
    }

    WideText_Destruct(&wide);
    TextLabel_Destruct(&label);
}
CLEAN_AS(func_02065d0c, Letter_LoadText)

/* func_02065db8: the letter's footer kept as the default and, when it has an addressee, its
 * header too: as the header to oneself when it is to its writer, else as the other. */
void LetterDefaults_Save(LetterDefaults *defaults, const Letter *letter)
{
    TextString_CopyChars(letter->footer, defaults->footer, LETTER_FOOTER_CHARS);
    if (Letter_HasNoAddressee((Letter *) (uintptr_t) letter)) {
        return;
    }

    u16 *header;
    if (Letter_IsToSelf(letter)) {
        header = defaults->self_header;
        defaults->self_header_line = letter->header_line;
    } else {
        header = defaults->header;
        defaults->header_line = letter->header_line;
    }
    TextString_CopyChars(letter->header, header, LETTER_HEADER_CHARS);
}
CLEAN_AS(func_02065db8, LetterDefaults_Save)

/* func_02065e10: the letter's footer: `footer` when it is not empty, else the default footer
 * message with the sender's name. */
void Letter_SetFooter(Letter *letter, const u16 *footer)
{
    if (footer[0] != 0) {
        TextString_CopyChars(footer, letter->footer, LETTER_FOOTER_CHARS);
        return;
    }

    u16 name[LETTER_NAME_CHARS];
    u8 line;
    char message;
    TextString_ClearChars(name, LETTER_NAME_CHARS);
    Letter_SenderName(letter, name);
    message = LETTER_MESSAGE_FOOTER;
    Letter_LoadText(&message, letter->footer, &line, name);
}
CLEAN_AS(func_02065e10, Letter_SetFooter)

/* func_02065e60: the current player's default header (to someone else) put in the letter,
 * unless it is addressed to a player or a villager (kinds 2 and 3). */
void Letter_TakeDefaultHeader(Letter *letter)
{
    if (letter->addressee.kind == LETTER_PARTY_PLAYER || letter->addressee.kind == LETTER_PARTY_VILLAGER) {
        return;
    }

    LetterDefaults *defaults =
        (LetterDefaults *) (void *) PlayerPockets_LetterDefaults(PlayerRecord_Pockets(PlayerRecords_Current()));
    TextString_CopyChars(defaults->header, letter->header, LETTER_HEADER_CHARS);
    letter->header_line = defaults->header_line;
}
CLEAN_AS(func_02065e60, Letter_TakeDefaultHeader)

/* --- The fields --- */

/* func_02065e9c: whether the letter is to its writer (an addressee of kind 1). */
int Letter_IsToSelf(const Letter *letter)
{
    return letter->addressee.kind == LETTER_PARTY_SELF;
}
CLEAN_AS(func_02065e9c, Letter_IsToSelf)

/* func_02065eac: the state set, the mark kept. QUIRK: a state above 0x3f is ORed into the
 * mark's bits. */
void Letter_SetState(Letter *letter, u8 state)
{
    letter->state = (u8) ((letter->state & ~LETTER_STATE_MASK) | state);
}
CLEAN_AS(func_02065eac, Letter_SetState)

/* func_02065ec0: the state (LetterState). */
u8 Letter_State(const Letter *letter)
{
    return letter->state & LETTER_STATE_MASK;
}
CLEAN_AS(func_02065ec0, Letter_State)

/* func_02065ed0: the item set, with the mark `mark` (0xff for 0); the item it carried
 * returned. */
u16 Letter_SetItem(Letter *letter, u16 item, int mark)
{
    u16 old = letter->item;
    if (mark == 0xff) {
        mark = 0;
    }
    letter->item = item;
    Letter_SetMark(letter, (u32) mark);
    return old;
}
CLEAN_AS(func_02065ed0, Letter_SetItem)

/* func_02065ef4: the mark (bits 6-7 of the state byte) set, the state kept; the mark is cut to
 * the byte. */
void Letter_SetMark(Letter *letter, u32 mark)
{
    letter->state = (u8) ((letter->state & LETTER_STATE_MASK) | (mark << LETTER_MARK_SHIFT));
}
CLEAN_AS(func_02065ef4, Letter_SetMark)

/* func_02065f08: the mark (0-3). */
u32 Letter_Mark(const Letter *letter)
{
    return (u32) letter->state >> LETTER_MARK_SHIFT;
}
CLEAN_AS(func_02065f08, Letter_Mark)

/* func_02065f18: the item, LETTER_NO_ITEM for none. */
u16 Letter_Item(const Letter *letter)
{
    return letter->item;
}
CLEAN_AS(func_02065f18, Letter_Item)

/* func_02065f20: whether the letter has no addressee (kind 7). */
int Letter_HasNoAddressee(Letter *letter)
{
    return LetterParty_IsKind(&letter->addressee, LETTER_PARTY_NONE);
}
CLEAN_AS(func_02065f20, Letter_HasNoAddressee)

/* func_02065f2c: the addressee's name put in the text object `text`. */
int Letter_AddresseeNameText(Letter *letter, void *text)
{
    return func_0206671c(&letter->addressee, text);
}
CLEAN_AS(func_02065f2c, Letter_AddresseeNameText)

/* func_02065f38: the sender's name put in the text object `text`. */
void Letter_SenderNameText(Letter *letter, void *text)
{
    func_0206671c(&letter->sender, text);
}
CLEAN_AS(func_02065f38, Letter_SenderNameText)

/* func_02065f44: the byte its writer gives (Letter.tag). */
u8 Letter_Tag(const Letter *letter)
{
    return letter->tag;
}
CLEAN_AS(func_02065f44, Letter_Tag)

/* func_02065f4c: the addressee's name written to `name`; returns what func_02066788 does. */
int Letter_AddresseeName(Letter *letter, u16 *name)
{
    return (int) (uintptr_t) func_02066788(&letter->addressee, name);
}
CLEAN_AS(func_02065f4c, Letter_AddresseeName)

/* func_02065f58: the sender's name written to `name`; returns what func_02066788 does. */
int Letter_SenderName(Letter *letter, u16 *name)
{
    return (int) (uintptr_t) func_02066788(&letter->sender, name);
}
CLEAN_AS(func_02065f58, Letter_SenderName)

/* func_02065f64: the addressee if it is a villager, else NULL. */
LetterParty *Letter_VillagerAddressee(Letter *letter)
{
    return func_020666f8(&letter->addressee);
}
CLEAN_AS(func_02065f64, Letter_VillagerAddressee)

/* func_02065f70: the addressee if it is a player, else NULL. */
LetterParty *Letter_PlayerAddressee(Letter *letter)
{
    return func_02066708(&letter->addressee);
}
CLEAN_AS(func_02065f70, Letter_PlayerAddressee)

/* func_02065f7c: the sender if it is a player, as an address; else 0. */
int Letter_PlayerSender(Letter *letter)
{
    return (int) (uintptr_t) func_02066708(&letter->sender);
}
CLEAN_AS(func_02065f7c, Letter_PlayerSender)

/* --- Writing a letter from the message files --- */

/* func_02065f88: a bottle's letter written from `message` of the file `name`. */
void Letter_WriteBottle(Letter *letter, const u8 *message, const char *name)
{
    s32 first_line;
    MailText_LoadMail(data_021cd8c4, data_021cd9b0, data_021cd8ec, &first_line, message, name);
    Letter_SetBottle(letter, data_021cd8c4, data_021cd9b0, data_021cd8ec, first_line);
}
CLEAN_AS(func_02065f88, Letter_WriteBottle)

/* func_02065fc4: a bottle's letter: paper 0x0c, from a special character, to no one (a player
 * of kind 6 when the header has no first line), with the texts given. */
void Letter_SetBottle(Letter *letter, void *header, void *body, void *footer, int first_line)
{
    Letter_Clear(letter);
    letter->paper = LETTER_BOTTLE_PAPER;
    Letter_SetState(letter, LETTER_STATE_BOTTLE);
    LetterParty_SetKind(&letter->sender, LETTER_PARTY_SPECIAL);
    LetterParty_Clear(&letter->addressee);
    if (first_line < 0) {
        LetterParty_SetKind(&letter->addressee, LETTER_PARTY_PLAYER_B);
        first_line = 0;
    }
    letter->tag = LETTER_BOTTLE_TAG;
    Letter_SetTexts(letter, &first_line, header, body, footer);
}
CLEAN_AS(func_02065fc4, Letter_SetBottle)

/* func_02066024: a special character's letter to `player`, written from `message` of the file
 * `name` with the player's name where the text asks for it. */
void Letter_WriteSpecialToPlayer(Letter *letter, const u8 *message, const char *name, const u8 *tag, const u8 *paper,
                                 const DesignCreator *player)
{
    LetterNameText text;
    s32 first_line;

    func_02094fd4(&text);
    func_02095074(player, &text);
    MailText_SetParticleName(&text);
    func_02094fbc(&text);
    MailText_LoadMail(data_021cd8c4, data_021cd9b0, data_021cd8ec, &first_line, message, name);
    Letter_SetSpecialToPlayer(letter, data_021cd8c4, data_021cd9b0, data_021cd8ec, first_line, tag, paper, player);
}
CLEAN_AS(func_02066024, Letter_WriteSpecialToPlayer)

/* func_02066088: a special character's letter to `player` (of kind 6 when the header has no
 * first line), received, with *paper, *tag and the texts given. */
void Letter_SetSpecialToPlayer(Letter *letter, void *header, void *body, void *footer, int first_line, const u8 *tag,
                               const u8 *paper, const DesignCreator *player)
{
    DesignCreator addressee;

    func_0209529c(&addressee);
    func_0209525c(&addressee, player);
    Letter_Clear(letter);
    letter->paper = *paper;
    letter->tag = *tag;
    LetterParty_SetKind(&letter->sender, LETTER_PARTY_SPECIAL);
    func_020666d0(&letter->addressee, &addressee);
    if (first_line < 0) {
        LetterParty_SetKind(&letter->addressee, LETTER_PARTY_PLAYER_B);
        first_line = 0;
    }
    Letter_SetState(letter, LETTER_STATE_RECEIVED);
    Letter_SetTexts(letter, &first_line, header, body, footer);
    func_0209526c(&addressee);
}
CLEAN_AS(func_02066088, Letter_SetSpecialToPlayer)

/* The sender's name put in part `part` of the letter texts, unless `part` is
 * MAIL_TEXT_PARTS (none). */
static void set_sender_part(const NpcId *sender, int part)
{
    LetterNameText text;

    if (part == LETTER_NO_PART) {
        return;
    }
    func_02094fd4(&text);
    NpcId_FormatName(sender, (char *) &text);
    MailText_SetPartText(part, &text);
    func_02094fbc(&text);
}

/* func_02066104: a villager's letter to another, written from the "mailz" messages with the
 * sender's name in part `sender_part` (none for 11) and the addressee's where the text asks
 * for it. */
void Letter_WriteBetweenVillagersZ(Letter *letter, const u8 *super_message, const u8 *msga_message, const u8 *msgb_message,
                                   const u8 *psz_message, const char *name, const u8 *paper, const NpcId *sender,
                                   const NpcId *addressee, int sender_part)
{
    LetterNameText text;
    s32 first_line;

    set_sender_part(sender, sender_part);
    func_02094fd4(&text);
    NpcId_FormatName(addressee, (char *) &text);
    MailText_SetParticleName(&text);
    func_02094fbc(&text);
    MailText_LoadMailz(data_021cd8c4, data_021cd9b0, data_021cd8ec, &first_line, super_message, msga_message, msgb_message,
                       psz_message, name);
    Letter_SetBetweenVillagers(letter, data_021cd8c4, data_021cd9b0, data_021cd8ec, first_line, paper, sender, addressee);
}
CLEAN_AS(func_02066104, Letter_WriteBetweenVillagersZ)

/* func_02066198: a villager's letter to another (of kind 5 when the header has no first line),
 * with *paper and the texts given. */
void Letter_SetBetweenVillagers(Letter *letter, void *header, void *body, void *footer, int first_line, const u8 *paper,
                                const NpcId *sender, const NpcId *addressee)
{
    NpcId from;
    NpcId to;

    NpcId_Construct(&from);
    NpcId_Construct(&to);
    NpcId_Copy(&from, sender);
    NpcId_Copy(&to, addressee);
    Letter_Clear(letter);
    letter->paper = *paper;
    letter->tag = 0;
    func_020666e4(&letter->sender, &from);
    func_020666e4(&letter->addressee, &to);
    if (first_line < 0) {
        LetterParty_SetKind(&letter->addressee, LETTER_PARTY_VILLAGER_B);
        first_line = 0;
    }
    Letter_SetState(letter, LETTER_STATE_BETWEEN_VILLAGERS);
    Letter_SetTexts(letter, &first_line, header, body, footer);
    NpcId_Destruct(&to);
    NpcId_Destruct(&from);
}
CLEAN_AS(func_02066198, Letter_SetBetweenVillagers)

/* func_02066228: a villager's letter to `player`, written from the "mailz" messages with the
 * sender's name in part `sender_part` (none for 11) and the player's where the text asks for
 * it. */
void Letter_WriteVillagerToPlayerZ(Letter *letter, const u8 *super_message, const u8 *msga_message, const u8 *msgb_message,
                                   const u8 *psz_message, const char *name, const u8 *paper, const NpcId *sender,
                                   const DesignCreator *player, int sender_part)
{
    LetterNameText text;
    s32 first_line;

    set_sender_part(sender, sender_part);
    func_02094fd4(&text);
    func_02095074(player, &text);
    MailText_SetParticleName(&text);
    func_02094fbc(&text);
    MailText_LoadMailz(data_021cd8c4, data_021cd9b0, data_021cd8ec, &first_line, super_message, msga_message, msgb_message,
                       psz_message, name);
    Letter_SetVillagerToPlayer(letter, data_021cd8c4, data_021cd9b0, data_021cd8ec, first_line, paper, sender, player);
}
CLEAN_AS(func_02066228, Letter_WriteVillagerToPlayerZ)

/* func_020662bc: a villager's letter to `player`, written from `message` of the file `name`
 * with the sender's name in part `sender_part` (none for 11) and the player's where the text
 * asks for it. */
void Letter_WriteVillagerToPlayer(Letter *letter, const u8 *message, const char *name, const u8 *paper, const NpcId *sender,
                                  const DesignCreator *player, int sender_part)
{
    LetterNameText text;
    s32 first_line;

    set_sender_part(sender, sender_part);
    func_02094fd4(&text);
    func_02095074(player, &text);
    MailText_SetParticleName(&text);
    func_02094fbc(&text);
    MailText_LoadMail(data_021cd8c4, data_021cd9b0, data_021cd8ec, &first_line, message, name);
    Letter_SetVillagerToPlayer(letter, data_021cd8c4, data_021cd9b0, data_021cd8ec, first_line, paper, sender, player);
}
CLEAN_AS(func_020662bc, Letter_WriteVillagerToPlayer)

/* func_02066344: a villager's letter to `player`, received, with *paper and the texts given.
 * QUIRK: when the header has no first line the addressee, a player, takes kind 5 (a
 * villager's), so Letter_VillagerAddressee then finds it and Letter_PlayerAddressee does
 * not. */
void Letter_SetVillagerToPlayer(Letter *letter, void *header, void *body, void *footer, int first_line, const u8 *paper,
                                const NpcId *sender, const DesignCreator *player)
{
    NpcId from;
    DesignCreator to;

    NpcId_Construct(&from);
    func_0209529c(&to);
    NpcId_Copy(&from, sender);
    func_0209525c(&to, player);
    Letter_Clear(letter);
    letter->paper = *paper;
    letter->tag = 0;
    func_020666e4(&letter->sender, &from);
    func_020666d0(&letter->addressee, &to);
    if (first_line < 0) {
        LetterParty_SetKind(&letter->addressee, LETTER_PARTY_VILLAGER_B);
        first_line = 0;
    }
    Letter_SetState(letter, LETTER_STATE_RECEIVED);
    Letter_SetTexts(letter, &first_line, header, body, footer);
    func_0209526c(&to);
    NpcId_Destruct(&from);
}
CLEAN_AS(func_02066344, Letter_SetVillagerToPlayer)

/* func_020663d4: the letter's texts from the three loaded texts (8-bit): 10 characters of the
 * header with its first line's length (cut to a byte), 64 of the body (through the body text,
 * built on first use) and 16 of the footer. */
void Letter_SetTexts(Letter *letter, const int *first_line, void *header, void *body, void *footer)
{
    WideText wide;

    letter->header_line = (u8) *first_line;
    WideText_Construct(&wide);
    TextBase_BytesToWide((WideTextBase *) (void *) &wide, (TextBase *) header);
    TextString_CopyChars(wide.text, letter->header, LETTER_HEADER_CHARS);

    if ((data_021cd890 & 1) == 0) {
        LetterBodyText_Construct(&data_021cd920);
        __register_global_object(&data_021cd920, (void *) (uintptr_t) func_02065c98, data_021cd8ac);
        data_021cd890 |= 1;
    }
    TextString_ClearWide((TextObject *) (void *) &data_021cd920);
    TextBase_BytesToWide((WideTextBase *) (void *) &data_021cd920, (TextBase *) body);
    TextString_CopyChars(data_021cd920.text, letter->body, LETTER_BODY_CHARS);

    TextBase_BytesToWide((WideTextBase *) (void *) &wide, (TextBase *) footer);
    TextString_CopyChars(wide.text, letter->footer, LETTER_FOOTER_CHARS);
    WideText_Destruct(&wide);
}
CLEAN_AS(func_020663d4, Letter_SetTexts)

/* --- A letter's life --- */

/* func_02066478: the letter delivered: received, tag 0x11, and marked 1 when it carries an
 * item. */
void Letter_MarkDelivered(Letter *letter)
{
    Letter_SetState(letter, LETTER_STATE_RECEIVED);
    letter->tag = LETTER_DELIVERED_TAG;
    if (letter->item != LETTER_NO_ITEM) {
        Letter_SetMark(letter, 1);
    }
}
CLEAN_AS(func_02066478, Letter_MarkDelivered)

/* func_020664a8: a received letter's state moved on: 2 to 3, 5 to 6, 7 to 8; others kept. */
void Letter_AdvanceReceived(Letter *letter)
{
    switch (Letter_State(letter)) {
        case LETTER_STATE_RECEIVED:
            Letter_SetState(letter, LETTER_STATE_RECEIVED_NEXT);
            break;
        case LETTER_STATE_BOTTLE:
            Letter_SetState(letter, LETTER_STATE_BOTTLE_NEXT);
            break;
        case LETTER_STATE_BETWEEN_VILLAGERS:
            Letter_SetState(letter, LETTER_STATE_BETWEEN_VILLAGERS_NEXT);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020664a8, Letter_AdvanceReceived)

/* func_020664e0: a written letter's state moved on (1 to 2, 4 to 5), and marked 1; others are
 * not touched. */
void Letter_AdvanceWritten(Letter *letter)
{
    switch (Letter_State(letter)) {
        case LETTER_STATE_WRITTEN:
            Letter_SetState(letter, LETTER_STATE_RECEIVED);
            break;
        case LETTER_STATE_BOTTLE_WRITTEN:
            Letter_SetState(letter, LETTER_STATE_BOTTLE);
            break;
        default:
            return;
    }
    Letter_SetMark(letter, 1);
}
CLEAN_AS(func_020664e0, Letter_AdvanceWritten)

/* func_02066514: the letter addressed to this system's player (kind 1), taking their default
 * header to themself unless it was already addressed so. */
void Letter_AddressToSelf(Letter *letter)
{
    u8 *record = PlayerRecords_Current();
    DesignCreator *player = PlayerRecord_Player(record);
    if (letter->addressee.kind != LETTER_PARTY_SELF) {
        LetterDefaults *defaults = (LetterDefaults *) (void *) PlayerPockets_LetterDefaults(PlayerRecord_Pockets(record));
        TextString_CopyChars(defaults->self_header, letter->header, LETTER_HEADER_CHARS);
        letter->header_line = defaults->self_header_line;
    }
    LetterParty_SetPlayer(&letter->addressee, player);
}
CLEAN_AS(func_02066514, Letter_AddressToSelf)

/* func_02066560: the letter addressed to the town's player `index` (0-3), with the default
 * header when it was not to a player or a villager. */
void Letter_AddressToPlayer(Letter *letter, int index)
{
    DesignCreator *player = PlayerRecord_Player(PlayerRecords_TownRecord(data_021dc7bc, index));
    Letter_TakeDefaultHeader(letter);
    func_020666d0(&letter->addressee, player);
}
CLEAN_AS(func_02066560, Letter_AddressToPlayer)

/* func_0206658c: the letter addressed to the town's villager `index` (0-7), with the default
 * header when it was not to a player or a villager. */
void Letter_AddressToVillager(Letter *letter, int index)
{
    NpcId *villager = TownVillager_NpcId(VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, index));
    Letter_TakeDefaultHeader(letter);
    func_020666e4(&letter->addressee, villager);
}
CLEAN_AS(func_0206658c, Letter_AddressToVillager)

/* func_020665b8: a bottle's letter started by this system's player: paper 0x0c, to no one,
 * with the default header message. */
void Letter_StartBottle(Letter *letter)
{
    char message;

    Letter_StartWriting(letter, LETTER_BOTTLE_PAPER);
    Letter_SetState(letter, LETTER_STATE_BOTTLE_WRITTEN);
    LetterParty_Clear(&letter->addressee);
    message = LETTER_MESSAGE_HEADER;
    Letter_LoadText(&message, letter->header, &letter->header_line, NULL);
}
CLEAN_AS(func_020665b8, Letter_StartBottle)

/* func_020665f0: a letter started by this system's player on `paper` (cut to a byte): from
 * them (kind 2), written, with their default footer. */
void Letter_StartWriting(Letter *letter, int paper)
{
    u8 *record = PlayerRecords_Current();
    Letter_Clear(letter);
    letter->paper = (u8) paper;
    letter->tag = 0;
    letter->sender.kind = LETTER_PARTY_PLAYER;
    func_020951dc(PlayerRecord_Player(record), &letter->sender);
    Letter_SetState(letter, LETTER_STATE_WRITTEN);
    LetterDefaults *defaults = (LetterDefaults *) (void *) PlayerPockets_LetterDefaults(PlayerRecord_Pockets(record));
    Letter_SetFooter(letter, defaults->footer);
}
CLEAN_AS(func_020665f0, Letter_StartWriting)

/* func_02066648: the paper. */
u8 Letter_Paper(const Letter *letter)
{
    return letter->paper;
}
CLEAN_AS(func_02066648, Letter_Paper)

/* func_02066650: the letter cleared: every byte 0, no item. QUIRK: its vtable is cleared too. */
void Letter_Clear(Letter *letter)
{
    MI_CpuFill8(letter, 0, sizeof(Letter));
    letter->item = LETTER_NO_ITEM;
}
CLEAN_AS(func_02066650, Letter_Clear)

/* func_02066670 (vtable entry 1): the destructor, then the object freed. */
Letter *Letter_DestructDelete(Letter *letter)
{
    letter->vtable = data_020de760;
    Heap_OperatorDeleteB(letter);
    return letter;
}
CLEAN_AS(func_02066670, Letter_DestructDelete)

/* func_02066688 (vtable entry 0): the destructor: the vtable set. */
void Letter_Destruct(Letter *letter)
{
    letter->vtable = data_020de760;
}
CLEAN_AS(func_02066688, Letter_Destruct)

/* func_02066694: the constructor: the vtable set, nothing else. */
void Letter_Construct(Letter *letter)
{
    letter->vtable = data_020de760;
}
CLEAN_AS(func_02066694, Letter_Construct)

/* --- A party --- */

/* func_020666a0: whether the party is of `kind`. */
int LetterParty_IsKind(const LetterParty *party, int kind)
{
    return party->kind == kind;
}
CLEAN_AS(func_020666a0, LetterParty_IsKind)

/* func_020666b0: the party's kind set (cut to a byte), the rest kept. */
void LetterParty_SetKind(LetterParty *party, int kind)
{
    party->kind = (u8) kind;
}
CLEAN_AS(func_020666b0, LetterParty_SetKind)

/* func_020666b4: the party made no one (kind 7), the rest kept. */
void LetterParty_Clear(LetterParty *party)
{
    party->kind = LETTER_PARTY_NONE;
}
CLEAN_AS(func_020666b4, LetterParty_Clear)

/* func_020666bc: the party made this system's player (kind 1), copied from `player`. */
void LetterParty_SetPlayer(LetterParty *party, const DesignCreator *player)
{
    party->kind = LETTER_PARTY_SELF;
    func_020951dc(player, party);
}
CLEAN_AS(func_020666bc, LetterParty_SetPlayer)
