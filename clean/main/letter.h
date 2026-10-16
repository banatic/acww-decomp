/* A letter (0x100 bytes, class data_020de760): who it is to and from, its three texts (a
 * header, a body and a footer, in 16-bit characters), its paper, its state and the item it
 * carries. mail.h keeps and delivers letters; this is how one is written and read.
 *
 * Its addressee and its sender are each a party (LetterParty): a player (a DesignCreator, the
 * 0x1e bytes that name a player of a town) or a villager (an NpcId), with a kind byte after it.
 *
 * The game writes letters in several ways, each a "write" function that loads the texts from
 * the letter message files (mail_text.h, into the three texts at data_021cd8c4, data_021cd9b0
 * and data_021cd8ec) and a "set" function that clears the letter and fills it from them:
 *
 * - a special character's letter to a player (shops, the player's mother, events): its sender
 *   is LETTER_PARTY_SPECIAL, named only by the text;
 * - a villager's letter to a player, or to another villager;
 * - a letter found in a bottle;
 * - a player's own letter, started from a paper (Letter_StartWriting) and addressed to a
 *   player, a villager or the player themself (Letter_AddressTo...); a bottle's letter is
 *   started the same way (Letter_StartBottle).
 *
 * A player keeps the headers and the footer last written as defaults (LetterDefaults): one
 * header for letters to themself, one for the others. */
#ifndef CLEAN_MAIN_LETTER_H
#define CLEAN_MAIN_LETTER_H

#include "main/design.h"
#include "main/npc_id.h"
#include "main/text_label.h"
#include "types.h"

#define LETTER_HEADER_CHARS 10
#define LETTER_BODY_CHARS 64
#define LETTER_FOOTER_CHARS 16
#define LETTER_NAME_CHARS 6
#define LETTER_NO_ITEM 0xfff1
#define LETTER_STATE_MASK 0x3f
#define LETTER_MARK_SHIFT 6

/* A party's kind (LetterParty.kind). */
enum LetterPartyKind {
    LETTER_PARTY_SELF = 1,       /* this system's player, writing to themself */
    LETTER_PARTY_PLAYER = 2,     /* a player */
    LETTER_PARTY_VILLAGER = 3,   /* a villager */
    LETTER_PARTY_SPECIAL = 4,    /* a special character, named only by the letter's text */
    LETTER_PARTY_VILLAGER_B = 5, /* a villager's kind, set on an addressee whose header has no
                                  * first line */
    LETTER_PARTY_PLAYER_B = 6,   /* a player's kind, set the same way */
    LETTER_PARTY_NONE = 7,
};

/* A letter's state (the low six bits of its byte 0xfa). */
enum LetterState {
    LETTER_STATE_NONE = 0, /* no letter: an empty place */
    LETTER_STATE_WRITTEN = 1,
    LETTER_STATE_RECEIVED = 2,
    LETTER_STATE_RECEIVED_NEXT = 3,
    LETTER_STATE_BOTTLE_WRITTEN = 4,
    LETTER_STATE_BOTTLE = 5,
    LETTER_STATE_BOTTLE_NEXT = 6,
    LETTER_STATE_BETWEEN_VILLAGERS = 7,
    LETTER_STATE_BETWEEN_VILLAGERS_NEXT = 8,
};

/* Who a letter is to or from (0x20 bytes). */
typedef struct LetterParty {
    union {
        DesignCreator player; /* kinds 1, 2 and 6 */
        NpcId villager;       /* kinds 3 and 5 */
    } who;
    u8 kind; /* 0x1e: LetterPartyKind */
    u8 unk_1f;
} LetterParty;

typedef struct Letter {
    const void *vtable;              /* data_020de760, until Letter_Clear clears it */
    LetterParty addressee;           /* 0x04 */
    LetterParty sender;              /* 0x24 */
    u16 header[LETTER_HEADER_CHARS]; /* 0x44 */
    u16 body[LETTER_BODY_CHARS];     /* 0x58 */
    u16 footer[LETTER_FOOTER_CHARS]; /* 0xd8 */
    u8 header_line;                  /* 0xf8: the header's first line, in characters */
    u8 paper;                        /* 0xf9 */
    u8 state;                        /* 0xfa: LetterState, and the mark in bits 6-7 */
    u8 tag;                          /* 0xfb: a value its writer gives (0x0c in a bottle's,
                                      * 0x11 once delivered, 0 in a player's or villager's) */
    u16 item;                        /* 0xfc: LETTER_NO_ITEM for none */
    u8 unk_fe[2];
} Letter;

/* A player's defaults for the letters they write (0x4a bytes, in their pockets). */
typedef struct LetterDefaults {
    u16 header[LETTER_HEADER_CHARS];      /* to someone else */
    u16 self_header[LETTER_HEADER_CHARS]; /* 0x14: to themself */
    u16 footer[LETTER_FOOTER_CHARS];      /* 0x28 */
    u8 header_line;                       /* 0x48 */
    u8 self_header_line;                  /* 0x49 */
} LetterDefaults;

/* The wide text a letter's body is converted through (class data_020de770): a wide text base
 * with 64 characters. */
typedef struct LetterBodyText {
    const TextVtable *vtable;
    u8 attributes[0xa];
    u16 text[LETTER_BODY_CHARS]; /* 0x0e */
} LetterBodyText;

int LetterBodyText_Buffer(int text);
int LetterBodyText_Capacity(void);
LetterBodyText *LetterBodyText_DestructDelete(LetterBodyText *text);
void *LetterBodyText_Destruct(void *text);
void *LetterBodyText_Construct(void *text);

void LetterDefaults_Init(LetterDefaults *defaults);
void Letter_LoadText(const char *message, u16 *dst, u8 *first_line, const u16 *name);
void LetterDefaults_Save(LetterDefaults *defaults, const Letter *letter);
void Letter_SetFooter(Letter *letter, const u16 *footer);
void Letter_TakeDefaultHeader(Letter *letter);
int Letter_IsToSelf(const Letter *letter);
void Letter_SetState(Letter *letter, u8 state);
u8 Letter_State(const Letter *letter);
u16 Letter_SetItem(Letter *letter, u16 item, int mark);
void Letter_SetMark(Letter *letter, u32 mark);
u32 Letter_Mark(const Letter *letter);
u16 Letter_Item(const Letter *letter);
int Letter_HasNoAddressee(Letter *letter);
int Letter_AddresseeNameText(Letter *letter, void *text);
void Letter_SenderNameText(Letter *letter, void *text);
u8 Letter_Tag(const Letter *letter);
int Letter_AddresseeName(Letter *letter, u16 *name);
int Letter_SenderName(Letter *letter, u16 *name);
LetterParty *Letter_VillagerAddressee(Letter *letter);
LetterParty *Letter_PlayerAddressee(Letter *letter);
int Letter_PlayerSender(Letter *letter);
void Letter_WriteBottle(Letter *letter, const u8 *message, const char *name);
void Letter_SetBottle(Letter *letter, void *header, void *body, void *footer, int first_line);
void Letter_WriteSpecialToPlayer(Letter *letter, const u8 *message, const char *name, const u8 *tag, const u8 *paper,
                                 const DesignCreator *player);
void Letter_SetSpecialToPlayer(Letter *letter, void *header, void *body, void *footer, int first_line, const u8 *tag,
                               const u8 *paper, const DesignCreator *player);
void Letter_WriteBetweenVillagersZ(Letter *letter, const u8 *super_message, const u8 *msga_message, const u8 *msgb_message,
                                   const u8 *psz_message, const char *name, const u8 *paper, const NpcId *sender,
                                   const NpcId *addressee, int sender_part);
void Letter_SetBetweenVillagers(Letter *letter, void *header, void *body, void *footer, int first_line, const u8 *paper,
                                const NpcId *sender, const NpcId *addressee);
void Letter_WriteVillagerToPlayerZ(Letter *letter, const u8 *super_message, const u8 *msga_message, const u8 *msgb_message,
                                   const u8 *psz_message, const char *name, const u8 *paper, const NpcId *sender,
                                   const DesignCreator *player, int sender_part);
void Letter_WriteVillagerToPlayer(Letter *letter, const u8 *message, const char *name, const u8 *paper, const NpcId *sender,
                                  const DesignCreator *player, int sender_part);
void Letter_SetVillagerToPlayer(Letter *letter, void *header, void *body, void *footer, int first_line, const u8 *paper,
                                const NpcId *sender, const DesignCreator *player);
void Letter_SetTexts(Letter *letter, const int *first_line, void *header, void *body, void *footer);
void Letter_MarkDelivered(Letter *letter);
void Letter_AdvanceReceived(Letter *letter);
void Letter_AdvanceWritten(Letter *letter);
void Letter_AddressToSelf(Letter *letter);
void Letter_AddressToPlayer(Letter *letter, int index);
void Letter_AddressToVillager(Letter *letter, int index);
void Letter_StartBottle(Letter *letter);
void Letter_StartWriting(Letter *letter, int paper);
u8 Letter_Paper(const Letter *letter);
void Letter_Clear(Letter *letter);
Letter *Letter_DestructDelete(Letter *letter);
void Letter_Destruct(Letter *letter);
void Letter_Construct(Letter *letter);

int LetterParty_IsKind(const LetterParty *party, int kind);
void LetterParty_SetKind(LetterParty *party, int kind);
void LetterParty_Clear(LetterParty *party);
void LetterParty_SetPlayer(LetterParty *party, const DesignCreator *player);

#endif
