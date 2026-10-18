/* Finding, copying and swapping designs (design.h). */
#include "design.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "clean.h"
#include "design_assets.h"
#include "main/item_code.h"
#include "acre_map.h"
#include "acre_record.h"
#include "design_info.h"
#include "design_sets.h"
#include "house_looks.h"
#include "house_record.h"
#include "item_form.h"
#include "main_random.h"
#include "npc_id.h"
#include "ov003/checkpoint.h"
#include "ov003/object_actors.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_query.h"
#include "session.h"
#include "shop_list_a.h"
#include "town_villager.h"
#include "villager_data.h"
#include "villager_mode_record.h"
#include "villager_object.h"
#include "villager_roster.h"
#include "villager_status.h"
#include "wfc_stats.h"

static_assert(sizeof(DesignCreator) == 0x1e, "creator");
static_assert(offsetof(DesignInfo, title) == 0x1e, "title");
static_assert(offsetof(DesignInfo, palette_and_kind) == 0x32, "palette");
static_assert(offsetof(Design, info) == DESIGN_PIXELS_SIZE, "info");
static_assert(sizeof(Design) == DESIGN_SIZE, "design");

/* What a copy moves: everything but the last byte, which is padding. */
#define DESIGN_COPIED_SIZE (offsetof(Design, info) + offsetof(DesignInfo, palette_and_kind) + 1)

/* The player-message category of DesignMessage and the third argument it is sent with. */
#define DESIGN_MESSAGE_CATEGORY 0x15
#define DESIGN_MESSAGE_TARGET 4

#define MESSAGE_KIND_BITS 0xf
#define MESSAGE_INDEX_BITS 0x3ff
#define MESSAGE_KIND_A_SHIFT 0
#define MESSAGE_INDEX_A_SHIFT 4
#define MESSAGE_KIND_B_SHIFT 14
#define MESSAGE_INDEX_B_SHIFT 18
#define MESSAGE_SWAP (1u << 28)

/* What a lookup of the kind table answers with: the design's address, or 0. */
typedef int (*DesignLookup)(int index);

/* The multiplayer session; only the slot of this system is read here. */
typedef struct Session {
    u8 unk_00[0x64];
    int local_slot;
} Session;

/* A map of acres (the town, or one room), each 0x28 bytes and holding a 16x16 grid of item
 * codes that func_02037e0c reads. */
typedef struct ItemMap {
    u8 *acres;
    int width;
    int height;
} ItemMap;

#define ACRE_SIZE 0x28
#define ACRE_ITEMS 16 /* 16 by 16 */
#define ROOMS 5

/* The item codes that stand for one of a player's eight designs, eight per player in player
 * order. On the town map one code each; in the rooms four codes each (the low two bits are a
 * variant, ITEM_CODE_VARIANT_BASE) in four ranges; and the two codes at 0x448 and 0x44a of the
 * records at data_021ebcd4, which get 0x113e and 0x1182 back. */
#define TOWN_DESIGN_FIRST 0xa7
#define TOWN_DESIGN_LAST 0xc6
#define ROOM_DESIGN_RANGES 4
#define ROOM_DESIGN_CODES 0x80
#define RECORD_DESIGN_FIRST 0x1188
#define RECORD_DESIGN_LAST 0x11a7
#define RECORD_FIRST_DEFAULT 0x113e
#define RECORD_SECOND_DEFAULT 0x1182

static const u16 room_design_first[ROOM_DESIGN_RANGES] = {0x3d84, 0x3ea4, 0x3f24, 0x4224};

/* Design_VillagerTakeShopDesign's draw (of 100) and the items it looks for. */
#define TAKE_DRAW 100
#define TAKE_ITEMS 6
#define TAKE_ITEM_FIRST 0x1380
#define TAKE_ITEM_LAST 0x139f
#define TAKE_ROOM_ITEM_FIRST 0x3e24
#define TAKE_ROOM_ITEM_LAST 0x3ea3

/* Design_Changed: the scene (func_020b65c4) the shop's textures exist in, and the overlay 3
 * actor that shows DESIGN_KIND_RECORD_5. */
#define SHOP_SCENE 10
#define RECORD_5_ACTOR 0x500b

extern const u32 data_020ccf6c[]; /* the lookups by kind: Design_FindSlot0 ... Design_FindLocal */
extern Session *data_020ccf94;    /* the session (also the message being built to send) */
extern u8 data_021ed278[];        /* the shop's designs */
extern u8 data_021e5a2c[];        /* the villagers (0x7ec bytes each) */
extern u8 data_021f3278[];        /* DESIGN_KIND_RECORD_8 */
extern u8 data_021f34b0[];        /* DESIGN_KIND_RECORD_5, at 4 */
extern u8 data_021ebcd4[];        /* five 0x450-byte records with two design codes */
extern u8 data_021f3b44[];        /* the list of six items Design_VillagerTakeShopDesign reads */
extern u8 data_020e54a8;          /* 0 or 1: which of the refreshes of Design_Changed apply */

/* Design_Swap's function-local static design, built on first use. */
extern u32 data_021d0474; /* its guard: bit 0 */
extern Design data_021d05cc;
extern u8 data_021d0498[]; /* its destruction record */
/* Design_RemovePlayerItems's function-local static item code. */
extern u32 data_021d0488; /* its guard: bit 0 */
extern ItemCode data_021d046c;
extern u8 data_021d048c[]; /* its destruction record */

extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_020051b0(void *item);    /* an item code's destructor: nothing */
extern void *func_02072da4(void *design); /* and destructor */

static int design_address(const void *design)
{
    return (int) (uintptr_t) design;
}

static Design *design_at(int address)
{
    return (Design *) (uintptr_t) address;
}

/* func_020714a0: message 0x15 from another system: copy or swap the two designs it names,
 * without sending it on. QUIRK: the indices are cut to 8 bits. */
int Design_Receive(const DesignMessage *message)
{
    u32 bits = message->bits;
    int kind_a = (int) ((bits >> MESSAGE_KIND_A_SHIFT) & MESSAGE_KIND_BITS);
    int index_a = (u8) ((bits >> MESSAGE_INDEX_A_SHIFT) & MESSAGE_INDEX_BITS);
    int kind_b = (int) ((bits >> MESSAGE_KIND_B_SHIFT) & MESSAGE_KIND_BITS);
    int index_b = (u8) ((bits >> MESSAGE_INDEX_B_SHIFT) & MESSAGE_INDEX_BITS);
    if (bits & MESSAGE_SWAP) {
        return Design_Swap(kind_a, index_a, kind_b, index_b, 0);
    }
    return Design_Copy(kind_a, index_a, kind_b, index_b, 0);
}
CLEAN_AS(func_020714a0, Design_Receive)

/* func_02071604: the design `index` of a kind, through the kind's lookup; 0 for kinds past
 * the table. REQUIRES: kind >= 0 (a negative one would call what lies before the table). */
int Design_Find(int kind, int index)
{
    if (kind >= DESIGN_KINDS) {
        return 0;
    }
    return ((DesignLookup) (uintptr_t) data_020ccf6c[kind])(index);
}
CLEAN_AS(func_02071604, Design_Find)

/* func_02071628: DESIGN_KIND_LOCAL: one of this system's player's designs, 0 without one. */
int Design_FindLocal(int index)
{
    int record = (int) (uintptr_t) PlayerRecords_Current();
    if (record == 0) {
        return 0;
    }
    return PlayerDesigns_At((PlayerDesigns *) (uintptr_t) (design_address(PlayerRecord_Designs((void *) (uintptr_t) record))),
                            index);
}
CLEAN_AS(func_02071628, Design_FindLocal)

/* func_02071648: DESIGN_KIND_RECORD_8, a single design: the index is not used. */
int Design_FindRecord8(int index)
{
    (void) index;
    return design_address(WfcStats_Design((WfcStats *) (void *) data_021f3278));
}
CLEAN_AS(func_02071648, Design_FindRecord8)

/* func_02071658: DESIGN_KIND_SAMPLE: reads sample `index` into the one place for a sample and
 * returns it. */
int Design_FindSample(int index)
{
    int sample = DesignSample_Get();
    DesignSample_Load((void *) (uintptr_t) sample, (unsigned int) index);
    return design_address(DesignSample_Design((void *) (uintptr_t) sample));
}
CLEAN_AS(func_02071658, Design_FindSample)

/* func_02071678: DESIGN_KIND_VILLAGER: the design of a villager, 0 without the villager. */
int Design_FindVillager(int villager)
{
    void *record = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, villager);
    if (record == NULL) {
        return 0;
    }
    return (int) TownVillager_Design((u8 *) (uintptr_t) record);
}
CLEAN_AS(func_02071678, Design_FindVillager)

/* func_0207169c: DESIGN_KIND_RECORD_5, a single design: the index is not used. */
int Design_FindRecord5(int index)
{
    (void) index;
    int record = HouseLooks_Design((HouseLooksRecord *) (uintptr_t) design_address(data_021f34b0));
    return design_address(HouseLooks_DesignItself((void *) (uintptr_t) record));
}
CLEAN_AS(func_0207169c, Design_FindRecord5)

/* func_020716b4: DESIGN_KIND_SHOP. */
int Design_FindShop(int index)
{
    return (int) ShopDesigns_At((unsigned int) (uintptr_t) data_021ed278, (unsigned int) index);
}
CLEAN_AS(func_020716b4, Design_FindShop)

/* func_020716c4: kind 3. */
int Design_FindSlot3(int index)
{
    return Design_FindSessionPlayer(3, index);
}
CLEAN_AS(func_020716c4, Design_FindSlot3)

/* func_020716d0: kind 2. */
int Design_FindSlot2(int index)
{
    return Design_FindSessionPlayer(2, index);
}
CLEAN_AS(func_020716d0, Design_FindSlot2)

/* func_020716dc: kind 1. */
int Design_FindSlot1(int index)
{
    return Design_FindSessionPlayer(1, index);
}
CLEAN_AS(func_020716dc, Design_FindSlot1)

/* func_020716e8: kind 0. */
int Design_FindSlot0(int index)
{
    return Design_FindSessionPlayer(0, index);
}
CLEAN_AS(func_020716e8, Design_FindSlot0)

/* func_020716f4: one of the designs of the player at a session slot; 0 outside a session or
 * without that player. */
int Design_FindSessionPlayer(int slot, int index)
{
    if (Session_IsLinked((NetSession *) data_020ccf94) == 0) {
        return 0;
    }
    int record = (int) (uintptr_t) PlayerRecords_OfPlayer(slot);
    if (record == 0) {
        return 0;
    }
    return PlayerDesigns_At((PlayerDesigns *) (uintptr_t) (design_address(PlayerRecord_Designs((void *) (uintptr_t) record))),
                            index);
}
CLEAN_AS(func_020716f4, Design_FindSessionPlayer)

static void *acre_at(const ItemMap *map, int x, int y)
{
    if ((unsigned int) x < (unsigned int) map->width && (unsigned int) y < (unsigned int) map->height && map->acres != NULL) {
        return map->acres + ACRE_SIZE * (x + y * map->width);
    }
    return NULL;
}

/* The player (0-3) a room code of a design belongs to, or -1 for other codes. */
static int room_design_owner(unsigned int code)
{
    for (int i = 0; i < ROOM_DESIGN_RANGES; i++) {
        if (code >= room_design_first[i] && code < room_design_first[i] + ROOM_DESIGN_CODES) {
            int design = (int) (code - room_design_first[i]) >> 2;
            return (design >> 3) & 3;
        }
    }
    return -1;
}

static int is_record_design(unsigned int code)
{
    return code >= RECORD_DESIGN_FIRST && code <= RECORD_DESIGN_LAST;
}

static int record_design_owner(unsigned int code)
{
    return ((int) (code - RECORD_DESIGN_FIRST) >> 3) & 3;
}

/* func_0207172c: takes away every item code that stands for one of a player's designs (the
 * player leaves the town, func_0209ef10): on the town map but its border acres, and in the
 * five rooms, they become nothing; the two codes of the records at data_021ebcd4 get their
 * defaults back.
 * QUIRK: the first call builds a function-local static item code (nothing, 0xfff1) and
 * registers it for destruction (func_020051b0, which does nothing); it is what is written. */
void Design_RemovePlayerItems(int player)
{
    if ((data_021d0488 & 1) == 0) {
        data_021d046c = ITEM_CODE_NONE;
        __register_global_object(&data_021d046c, (void *) func_020051b0, data_021d048c);
        data_021d0488 |= 1;
    }

    ItemMap *town = (ItemMap *) (uintptr_t) AcreMap_Town();
    if (town != NULL) {
        for (int y = 1; y < town->height - 1; y++) {
            for (int x = 1; x < town->width - 1; x++) {
                void *acre = acre_at(town, x, y);
                if (acre == NULL) {
                    continue;
                }
                for (int row = 0; row < ACRE_ITEMS; row++) {
                    for (int column = 0; column < ACRE_ITEMS; column++) {
                        u16 *item = AcreRecord_Tile(acre, column, row, 0);
                        if (item == NULL) {
                            continue;
                        }
                        unsigned int code = *item;
                        if (code >= TOWN_DESIGN_FIRST && code <= TOWN_DESIGN_LAST &&
                            (int) (code - TOWN_DESIGN_FIRST) / 8 == player) {
                            AcreRecord_SetTile(acre, &data_021d046c, column, row, 0);
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < ROOMS; i++) {
        ItemMap *room = (ItemMap *) (uintptr_t) AcreMap_Room(i);
        if (room != NULL) {
            void *acre = acre_at(room, 0, 0);
            if (acre != NULL) {
                for (int y = 0; y < ACRE_ITEMS; y++) {
                    for (int x = 0; x < ACRE_ITEMS; x++) {
                        u16 *item = AcreRecord_Tile(acre, x, y, 0);
                        if (item == NULL) {
                            continue;
                        }
                        int owner = room_design_owner(*item);
                        if (owner != -1 && owner == player) {
                            AcreRecord_SetTile(acre, &data_021d046c, x, y, 0);
                        }
                    }
                }
            }
        }

        void *record = (void *) (uintptr_t) HouseRecord_Room((HouseRecord *) (void *) data_021ebcd4, i);
        if (record == NULL) {
            continue;
        }
        /* Each code is read once to test it and again to see whose it is. */
        if (is_record_design(*HouseRecord_RoomWallpaper(record, NULL))) {
            unsigned int code = *HouseRecord_RoomWallpaper(record, NULL);
            if (record_design_owner(code) == player) {
                ItemCode first = RECORD_FIRST_DEFAULT;
                HouseRecord_RoomSetWallpaper(record, &first, 0);
            }
        }
        if (!is_record_design(*(u16 *) HouseRecord_RoomCarpet(record, NULL))) {
            continue;
        }
        unsigned int code = *(u16 *) HouseRecord_RoomCarpet(record, NULL);
        if (record_design_owner(code) == player) {
            ItemCode second = RECORD_SECOND_DEFAULT;
            HouseRecord_RoomSetCarpet(record, &second, 0);
        }
    }
}
CLEAN_AS(func_0207172c, Design_RemovePlayerItems)

/* Sends DesignMessage: the two designs (by resolved kind) and whether they were swapped. */
static void send_message(int kind_a, int index_a, int kind_b, int index_b, int swap)
{
    DesignMessage message;
    message.bits = ((u32) (kind_a & MESSAGE_KIND_BITS) << MESSAGE_KIND_A_SHIFT) |
                   ((u32) (index_a & MESSAGE_INDEX_BITS) << MESSAGE_INDEX_A_SHIFT) |
                   ((u32) (kind_b & MESSAGE_KIND_BITS) << MESSAGE_KIND_B_SHIFT) |
                   ((u32) (index_b & MESSAGE_INDEX_BITS) << MESSAGE_INDEX_B_SHIFT) | (swap ? MESSAGE_SWAP : 0);
    Session *outgoing = data_020ccf94;
    Session_BeginMessage((NetSession *) outgoing);
    Session_AppendMessage((NetSession *) outgoing, &message, sizeof(message));
    Session_EndMessage((NetSession *) outgoing, DESIGN_MESSAGE_CATEGORY, DESIGN_MESSAGE_TARGET);
}

/* func_02071aa8: swaps two designs, refreshes what shows them and, when asked and in a session,
 * tells the other systems. 0 when either is a sample (which is read only).
 * REQUIRES: both designs exist (Design_Find gives no 0).
 * QUIRK: the swap goes through a function-local static design (data_021d05cc), built and
 * registered for destruction on first use. */
int Design_Swap(int kind_a, int index_a, int kind_b, int index_b, u8 announce_it)
{
    int a = Design_ResolveKind(kind_a);
    int b = Design_ResolveKind(kind_b);
    if (a == DESIGN_KIND_SAMPLE || b == DESIGN_KIND_SAMPLE) {
        return 0;
    }
    Design *design_a = design_at(Design_Find(a, index_a));
    Design *design_b = design_at(Design_Find(b, index_b));
    if ((data_021d0474 & 1) == 0) {
        Design_Construct((char *) &data_021d05cc);
        __register_global_object(&data_021d05cc, (void *) func_02072da4, data_021d0498);
        data_021d0474 |= 1;
    }
    memcpy(&data_021d05cc, design_b, DESIGN_COPIED_SIZE);
    memmove(design_b, design_a, DESIGN_COPIED_SIZE);
    memcpy(design_a, &data_021d05cc, DESIGN_COPIED_SIZE);

    Design_Changed(a, index_a);
    Design_Changed(b, index_b);
    if (announce_it != 0 && Session_IsLinked((NetSession *) data_020ccf94) != 0) {
        send_message(a, index_a, b, index_b, 1);
    }
    return 1;
}
CLEAN_AS(func_02071aa8, Design_Swap)

/* func_02071d60: in a session, DESIGN_KIND_LOCAL becomes this system's slot (kind 0-3), the
 * kind the other systems know its player by; other kinds stay. */
int Design_ResolveKind(int kind)
{
    Session *session = data_020ccf94;
    if (Session_IsLinked((NetSession *) session) != 0 && kind == DESIGN_KIND_LOCAL) {
        return session->local_slot;
    }
    return kind;
}
CLEAN_AS(func_02071d60, Design_ResolveKind)

/* func_02071d8c: copies one design over another, refreshes what shows the copy and, when asked
 * and in a session, tells the other systems. 0 when the copy would go to a sample.
 * REQUIRES: both designs exist (Design_Find gives no 0). */
int Design_Copy(int kind_from, int index_from, int kind_to, int index_to, u8 announce_it)
{
    int from = Design_ResolveKind(kind_from);
    int to = Design_ResolveKind(kind_to);
    if (to == DESIGN_KIND_SAMPLE) {
        return 0;
    }
    Design *source = design_at(Design_Find(from, index_from));
    Design *target = design_at(Design_Find(to, index_to));
    memmove(target, source, DESIGN_COPIED_SIZE);
    Design_Changed(to, index_to);
    if (announce_it != 0 && Session_IsLinked((NetSession *) data_020ccf94) != 0) {
        send_message(from, index_from, to, index_to, 0);
    }
    return 1;
}
CLEAN_AS(func_02071d8c, Design_Copy)

static int shop_design_kind(unsigned int index)
{
    unsigned int design = ShopDesigns_At((unsigned int) (uintptr_t) data_021ed278, (u8) index);
    return DesignInfo_Kind((DesignInfo *) (uintptr_t) Design_Info(design));
}

/* func_02071efc: a villager may take one of the shop's designs as its own. A draw of 100 decides:
 * when the villager's byte 16 at 0x734 is 3, below 15 it takes a design whose kind (the low
 * bits of DesignInfo byte 0x32) is the villager's byte (func_020808b0), below 20 one whose
 * kind differs; otherwise below 10 a matching one. Which design of those is random. The result
 * is Design_Copy's, 0 when nothing is taken.
 * QUIRK: draws of 20-29 (byte 3) or 10-14 (otherwise) look through six items for one of 0x1380-
 * 0x139f or 0x3e24-0x3ea3, convert it (func_02061e2c) and throw the result away.
 * REQUIRES: the villager's byte exists (func_020808b0 gives no 0). */
int Design_VillagerTakeShopDesign(int villager, int announce_it)
{
    void *record = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, villager);
    if (record == NULL) {
        return 0;
    }
    unsigned int address = (unsigned int) (uintptr_t) record;
    if (NpcId_IsValid((void *) (uintptr_t) TownVillager_NpcId((u8 *) (uintptr_t) address)) == 0) {
        return 0;
    }
    int wanted = *(u8 *) (uintptr_t) VillagerData_Byte29((u8 *) (uintptr_t) address);
    int mode = VillagerModeRecord_Mode(
        VillagerObject_RecordMode((void *) (uintptr_t) VillagerStatus_ModeRecord((u8 *) (uintptr_t) address)));
    unsigned int draw = MainRandom_Below(TAKE_DRAW);

    int take = 0;
    int matching = 0;
    int look_at_items = 0;
    if (mode == 3) {
        if (draw < 15) {
            take = 1;
            matching = 1;
        } else if (draw < 20) {
            take = 1;
        } else if (draw < 30) {
            look_at_items = 1;
        }
    } else {
        if (draw < 10) {
            take = 1;
            matching = 1;
        } else if (draw < 15) {
            look_at_items = 1;
        }
    }

    if (look_at_items) {
        ItemCode item = ITEM_CODE_NONE;
        int found = 0;
        for (int i = 0; i < TAKE_ITEMS; i++) {
            ShopListA_Item((ShopListA *) (void *) data_021f3b44, i, &item);
            if ((item >= TAKE_ITEM_FIRST && item <= TAKE_ITEM_LAST) ||
                (item >= TAKE_ROOM_ITEM_FIRST && item <= TAKE_ROOM_ITEM_LAST)) {
                found = 1;
                break;
            }
        }
        if (found) {
            ItemCode converted;
            ItemForm_ToCarried(&converted, &item);
        }
    }

    if (!take) {
        return 0;
    }
    int candidates = 0;
    for (unsigned int i = 0; i < DESIGNS_PER_SET; i++) {
        int kind = shop_design_kind(i);
        if ((kind == wanted) == matching) {
            candidates++;
        }
    }
    if (candidates <= 0) {
        return 0;
    }
    int pick = (int) MainRandom_Below(candidates);
    int seen = 0;
    unsigned int chosen;
    for (chosen = 0; chosen < DESIGNS_PER_SET; chosen++) {
        int kind = shop_design_kind(chosen);
        if ((kind == wanted) == matching) {
            if (pick == seen) {
                break;
            }
            seen++;
        }
    }
    return Design_Copy(DESIGN_KIND_SHOP, (u8) (chosen & 7), DESIGN_KIND_VILLAGER, (u8) villager, (u8) announce_it);
}
CLEAN_AS(func_02071efc, Design_VillagerTakeShopDesign)

/* func_020720ac: after a design of a kind changed, refreshes what shows it. 1 for the kinds it
 * knows (0, 4, 5 and 9), 0 for the others.
 * QUIRK: kinds 0 and 9 both refresh the textures of the player at session slot 0 (their
 * player number from func_0209985c, with the given index), whichever player the design is. */
int Design_Changed(int kind, int index)
{
    switch (kind) {
        case DESIGN_KIND_SLOT_0:
        case DESIGN_KIND_LOCAL: {
            int record = (int) (uintptr_t) PlayerRecords_OfPlayer(0);
            if (record != 0) {
                int player = PlayerRecord_Number((u8 *) (uintptr_t) record);
                if (player != -1) {
                    DesignTextures_UpdatePlayer((u8) (player & 3), index);
                }
            }
            return 1;
        }
        case DESIGN_KIND_SHOP:
            if (data_020e54a8 == 1 && SceneQuery_Current() == SHOP_SCENE) {
                DesignTextures_UpdateShop((unsigned int) index);
                DesignManager_MarkShopChanged((DesignManager *) (uintptr_t) DesignManager_Get(), index & 7);
            }
            return 1;
        case DESIGN_KIND_RECORD_5:
            if (data_020e54a8 == 0 && SceneQuery_CurrentIs0() != 0) {
                void *actor = ObjectActors_FindByCode(RECORD_5_ACTOR);
                if (actor != NULL) {
                    Checkpoint_RefreshDesign(actor);
                }
            }
            return 1;
    }
    return 0;
}
CLEAN_AS(func_020720ac, Design_Changed)
