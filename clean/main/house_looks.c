/* The record of the four house looks and the checkpoint's design (house_looks.h). */
#include "house_looks.h"

#include "acre_map.h"
#include "acre_record.h"
#include "acre_tile.h"
#include "clean.h"
#include "design_info.h"
#include "design_sets.h"

static_assert(offsetof(HouseLooksRecord, design) == 0x04, "design");
static_assert(offsetof(HouseLooksDesign, style) == 0x234, "style");

/* The inner acres of the town, the ones whose buildings a reset takes off. */
#define HOUSE_LOOKS_FIRST_ACRE 1
#define HOUSE_LOOKS_LAST_ACRE 4
/* An unset look while the looks are drawn. */
#define HOUSE_LOOKS_NONE 0xff

extern int func_020644cc(int range); /* a random number below `range` */

static int house_looks_is_building(u16 code)
{
    return code >= ACRE_TILE_BUILDING_FIRST && code <= ACRE_TILE_BUILDING_LAST;
}

/* func_020b374c: the record's design part (record + 4), as an address. */
int HouseLooks_Design(HouseLooksRecord *record)
{
    return (int) (uintptr_t) &record->design;
}
CLEAN_AS(func_020b374c, HouseLooks_Design)

/* func_020b3750: the record's looks (the record itself). */
u8 *HouseLooks_Looks(HouseLooksRecord *record)
{
    return record->looks;
}
CLEAN_AS(func_020b3750, HouseLooks_Looks)

/* func_020b3754: the record reset for a new town: new looks, a new style and the default
 * design; then every building (codes 0x5000-0x5021) on layer 0 of the town's acres (1, 1) to
 * (4, 4) is taken off its tile (AcreMap_ClearBuildingAt), acre by acre and tile by tile, x
 * first. Acres outside the map are skipped.
 * REQUIRES: the town's map exists (AcreMap_Town is not 0); the original reads it regardless. */
void HouseLooks_Reset(HouseLooksRecord *record)
{
    HouseLooks_ResetLooks(record->looks);
    HouseLooks_ResetDesign(&record->design);

    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    for (u32 acre_z = HOUSE_LOOKS_FIRST_ACRE; acre_z <= HOUSE_LOOKS_LAST_ACRE; acre_z++) {
        for (u32 acre_x = HOUSE_LOOKS_FIRST_ACRE; acre_x <= HOUSE_LOOKS_LAST_ACRE; acre_x++) {
            if (acre_x >= (u32) town->acres_wide || acre_z >= (u32) town->acres_high || town->acres == NULL) {
                continue;
            }
            AcreRecord *acre = (AcreRecord *) (town->acres + (acre_x + acre_z * (u32) town->acres_wide) * ACRE_MAP_ACRE_SIZE);
            for (int z = 0; z < ACRE_RECORD_SIDE; z++) {
                for (int x = 0; x < ACRE_RECORD_SIDE; x++) {
                    u16 *item = AcreRecord_Tile(acre, (unsigned int) x, (unsigned int) z, 0);
                    if (item == NULL || !house_looks_is_building(*item)) {
                        continue;
                    }
                    int tile_x;
                    int tile_z;
                    AcreTile_TileOfAcre(&tile_x, &tile_z, (int) acre_x, (int) acre_z, x, z);
                    AcreMap_ClearBuildingAt((int) (uintptr_t) town, (int) (uintptr_t) item, tile_x, tile_z);
                }
            }
        }
    }
}
CLEAN_AS(func_020b3754, HouseLooks_Reset)

/* func_020b3818: the record's destructor: the design part's, then the looks'. */
HouseLooksRecord *HouseLooks_Destruct(HouseLooksRecord *record)
{
    HouseLooks_DestructDesign(&record->design);
    HouseLooks_DestructLooks(record);
    return record;
}
CLEAN_AS(func_020b3818, HouseLooks_Destruct)

/* func_020b3830: the record's constructor: the looks', then the design part's. */
HouseLooksRecord *HouseLooks_Construct(HouseLooksRecord *record)
{
    HouseLooks_ConstructLooks();
    HouseLooks_ConstructDesign(&record->design);
    return record;
}
CLEAN_AS(func_020b3830, HouseLooks_Construct)

/* func_020b3848: the design (DesignHolder_Design). */
Design *HouseLooks_DesignItself(HouseLooksDesign *design)
{
    return DesignHolder_Design(&design->design);
}
CLEAN_AS(func_020b3848, HouseLooks_DesignItself)

/* func_020b3850: `source` copied into the design (Design_Assign). */
void HouseLooks_SetDesign(HouseLooksDesign *design, const Design *source)
{
    Design_Assign(&design->design, source);
}
CLEAN_AS(func_020b3850, HouseLooks_SetDesign)

/* func_020b3858: the style, 0-2. A style of 3 or more is first brought below 3 and written
 * back. */
int HouseLooks_Style(HouseLooksDesign *design)
{
    if (design->style >= HOUSE_LOOKS_STYLES) {
        design->style = (u8) (design->style % HOUSE_LOOKS_STYLES);
    }
    return design->style;
}
CLEAN_AS(func_020b3858, HouseLooks_Style)

/* func_020b3880: a random style, then the default design (DesignHolder_Reset). */
void HouseLooks_ResetDesign(HouseLooksDesign *design)
{
    design->style = (u8) func_020644cc(HOUSE_LOOKS_STYLES);
    DesignHolder_Reset(&design->design);
}
CLEAN_AS(func_020b3880, HouseLooks_ResetDesign)

/* func_020b38a0: the design part's destructor (DesignHolder_Destruct); its own address. */
int HouseLooks_DestructDesign(HouseLooksDesign *design)
{
    DesignHolder_Destruct(&design->design);
    return (int) (uintptr_t) design;
}
CLEAN_AS(func_020b38a0, HouseLooks_DestructDesign)

/* func_020b38b0: the design part's constructor (DesignHolder_Construct). */
HouseLooksDesign *HouseLooks_ConstructDesign(HouseLooksDesign *design)
{
    DesignHolder_Construct(&design->design);
    return design;
}
CLEAN_AS(func_020b38b0, HouseLooks_ConstructDesign)

/* func_020b38c0: look `index` (taken modulo 4), brought below 25. */
int HouseLooks_Look(const u8 *looks, int index)
{
    unsigned int look = looks[index & (HOUSE_LOOKS_COUNT - 1)];
    return (int) (look % (HOUSE_LOOKS_SETS * HOUSE_LOOKS_VARIANTS));
}
CLEAN_AS(func_020b38c0, HouseLooks_Look)

/* func_020b38dc: new looks. A random set gives the first three looks, three different
 * variants of it drawn one after the other; the fourth is a random variant of another set,
 * the set drawn among the four that are left. Six random numbers are drawn, in this order:
 * the first set (below 5), the other set (below 4), the three variants (below 5, 4 and 3)
 * and the last variant (below 5).
 * QUIRK: a draw out of its range (the game's never are) leaves the look 0xff, or the other
 * set at 0. */
void HouseLooks_ResetLooks(u8 *looks)
{
    int first_set = func_020644cc(HOUSE_LOOKS_SETS);
    unsigned int other_pick = (unsigned int) func_020644cc(HOUSE_LOOKS_SETS - 1);

    /* The other set: the other_pick-th set that is not the first one. */
    int other_set = 0;
    unsigned int seen = 0;
    for (unsigned int set = 0; set < HOUSE_LOOKS_SETS; set++) {
        if (set == (unsigned int) first_set) {
            continue;
        }
        if (seen == other_pick) {
            other_set = (int) set;
            break;
        }
        seen++;
    }

    for (unsigned int i = 0; i < HOUSE_LOOKS_COUNT; i++) {
        looks[i] = HOUSE_LOOKS_NONE;
    }

    /* Each of the first three: the pick-th variant of the first set not drawn yet. */
    int base = HOUSE_LOOKS_VARIANTS * (first_set % HOUSE_LOOKS_SETS);
    for (unsigned int k = 0; k < HOUSE_LOOKS_COUNT - 1; k++) {
        unsigned int pick = (unsigned int) func_020644cc(HOUSE_LOOKS_VARIANTS - (int) k);
        unsigned int free_seen = 0;
        for (unsigned int variant = 0; variant < HOUSE_LOOKS_VARIANTS; variant++) {
            int look = (int) variant + base;
            int taken = 0;
            for (unsigned int u = 0; u < HOUSE_LOOKS_COUNT; u++) {
                if (looks[u] == look) {
                    taken = 1;
                    break;
                }
            }
            if (taken) {
                continue;
            }
            if (free_seen == pick) {
                looks[k] = (u8) look;
                break;
            }
            free_seen++;
        }
    }

    unsigned int variant = (unsigned int) func_020644cc(HOUSE_LOOKS_VARIANTS);
    looks[HOUSE_LOOKS_COUNT - 1] =
        (u8) (HOUSE_LOOKS_VARIANTS * (other_set % HOUSE_LOOKS_SETS) + (int) (variant % HOUSE_LOOKS_VARIANTS));
}
CLEAN_AS(func_020b38dc, HouseLooks_ResetLooks)

/* func_020b39b4: the looks' destructor; nothing to do. */
void HouseLooks_DestructLooks(HouseLooksRecord *record)
{
    (void) record;
}
CLEAN_AS(func_020b39b4, HouseLooks_DestructLooks)

/* func_020b39b8: the looks' constructor; nothing to do. */
void HouseLooks_ConstructLooks(void) {}
CLEAN_AS(func_020b39b8, HouseLooks_ConstructLooks)
