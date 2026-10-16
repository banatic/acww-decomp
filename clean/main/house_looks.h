/* A record of the town's state (data_021f34b0, at 0x16d08 in the state block): the looks of
 * four houses and a design with a style.
 *
 * - The looks are four numbers 0-24: set (look / 5) and variant (look % 5) of the textures
 *   "/str/npcHsTex/<set>/house_<set><variant>..." and ".../light_<set><variant>..." that
 *   overlay 3 loads, the set as a letter from 'A'. The first three share one set and differ in
 *   variant; the fourth comes from another set.
 * - The design (DesignHolder, design_sets.h) is the one overlay 3's checkpoint wears
 *   (ov003/checkpoint.h); the style after it (0-2) picks the checkpoint's model, "obj_check<n>".
 *
 * Resetting the record (a new town) also takes every building off the town's inner acres
 * 1-4. */
#ifndef CLEAN_MAIN_HOUSE_LOOKS_H
#define CLEAN_MAIN_HOUSE_LOOKS_H

#include "design.h"
#include "types.h"

#define HOUSE_LOOKS_COUNT 4
#define HOUSE_LOOKS_SETS 5
#define HOUSE_LOOKS_VARIANTS 5
#define HOUSE_LOOKS_STYLES 3

/* The design and its style. */
typedef struct HouseLooksDesign {
    Design design;
    u8 style; /* 0x234 */
} HouseLooksDesign;

typedef struct HouseLooksRecord {
    u8 looks[HOUSE_LOOKS_COUNT]; /* 0x00 */
    HouseLooksDesign design;     /* 0x04 */
} HouseLooksRecord;

int HouseLooks_Design(HouseLooksRecord *record);
u8 *HouseLooks_Looks(HouseLooksRecord *record);
void HouseLooks_Reset(HouseLooksRecord *record);
HouseLooksRecord *HouseLooks_Destruct(HouseLooksRecord *record);
HouseLooksRecord *HouseLooks_Construct(HouseLooksRecord *record);
Design *HouseLooks_DesignItself(HouseLooksDesign *design);
void HouseLooks_SetDesign(HouseLooksDesign *design, const Design *source);
int HouseLooks_Style(HouseLooksDesign *design);
void HouseLooks_ResetDesign(HouseLooksDesign *design);
int HouseLooks_DestructDesign(HouseLooksDesign *design);
HouseLooksDesign *HouseLooks_ConstructDesign(HouseLooksDesign *design);
int HouseLooks_Look(const u8 *looks, int index);
void HouseLooks_ResetLooks(u8 *looks);
void HouseLooks_DestructLooks(HouseLooksRecord *record);
void HouseLooks_ConstructLooks(void);

#endif
