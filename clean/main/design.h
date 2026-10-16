/* The 32x32 designs ("menu/desi/..." are their files): where each set of designs lives, finding
 * one by kind and index, copying and swapping them (and telling the other players of a
 * multiplayer session), and the designs' item codes taken away when a player leaves.
 *
 * A design is 0x200 bytes of 16-colour pixels in bitmap order, then its information: who made
 * it, its title, and its palette (one of 16 in "/menu/desi/b_myd_ten0_obj.bpl", design_assets.h).
 * A design is named by a kind (DesignKind) and an index in that kind's set. */
#ifndef CLEAN_MAIN_DESIGN_H
#define CLEAN_MAIN_DESIGN_H

#include "types.h"

#define DESIGN_PIXELS_SIZE 0x200
#define DESIGN_SIZE 0x234
#define DESIGNS_PER_SET 8 /* a player's, the shop's */

/* Who made a design (0x1e bytes; func_02072eec copies it). */
typedef struct DesignCreator {
    u16 town_id;
    u16 town_name[6];
    u16 player_id;
    u16 player_name[6];
    s8 unk_1c;
    u8 unk_1d;
} DesignCreator;

/* A design's information, after its pixels. */
typedef struct DesignInfo {
    DesignCreator creator;
    u16 title[10];
    u8 palette_and_kind; /* the low four bits: func_02072e30, compared with a villager's byte;
                            the high four: the palette (func_02072f74) */
} DesignInfo;

typedef struct Design {
    u8 pixels[DESIGN_PIXELS_SIZE];
    DesignInfo info;
} Design;

/* The sets a kind names. Kinds 0-3 and 9 are players, the others places in the game's data. */
enum DesignKind {
    DESIGN_KIND_SLOT_0 = 0, /* 0-3: the player at that slot of the multiplayer session */
    /* The eight designs at data_021ed278, which villagers take (Design_VillagerTakeShopDesign);
     * likely the Able Sisters'. */
    DESIGN_KIND_SHOP = 4,
    DESIGN_KIND_RECORD_5 = 5, /* the one design at data_021f34b0 + 4 (overlay 3's actor 0x500b) */
    DESIGN_KIND_VILLAGER = 6, /* the design of each villager (by villager) */
    DESIGN_KIND_SAMPLE = 7,   /* the samples "menu/desi/myc/obj%d.bch", one at a time: read only */
    DESIGN_KIND_RECORD_8 = 8, /* the one design at data_021f3278 */
    DESIGN_KIND_LOCAL = 9,    /* this system's player; a session slot in messages */
    DESIGN_KINDS = 10
};

/* The word of message 0x15 that copies or swaps two designs between the session's systems. */
typedef struct DesignMessage {
    u32 bits; /* 0-3: kind A, 4-13: index A, 14-17: kind B, 18-27: index B, 28: swap */
} DesignMessage;

int Design_Receive(const DesignMessage *message);
int Design_Find(int kind, int index);
int Design_FindLocal(int index);
int Design_FindRecord8(int index);
int Design_FindSample(int index);
int Design_FindVillager(int villager);
int Design_FindRecord5(int index);
int Design_FindShop(int index);
int Design_FindSlot3(int index);
int Design_FindSlot2(int index);
int Design_FindSlot1(int index);
int Design_FindSlot0(int index);
int Design_FindSessionPlayer(int slot, int index);
void Design_RemovePlayerItems(int player);
int Design_Swap(int kind_a, int index_a, int kind_b, int index_b, u8 announce);
int Design_ResolveKind(int kind);
int Design_Copy(int kind_from, int index_from, int kind_to, int index_to, u8 announce);
int Design_VillagerTakeShopDesign(int villager, int announce);
int Design_Changed(int kind, int index);

#endif
