/* How well the town's villagers get on with each other (villager_bonds.h). */
#include "villager_bonds.h"

#include "clean.h"
#include "npc_id.h"

#define VILLAGERS 8

/* The bytes of a villager's data (data_020cd884, 0x4e bytes for each of the 150 villagers) the
 * affinity reads. */
#define VILLAGER_DATA_BYTE_04 0x04
/* The element of a star sign (enum StarSign, lookups.h): earth, air, water and fire in turn. */
#define VILLAGER_BOND_ELEMENT(sign) ((sign) & 3)
#define VILLAGER_BOND_SAME_SPECIES 0x40
#define VILLAGER_BOND_GOOD_SPECIES 0x80
#define VILLAGER_BOND_BAD_SPECIES 0x00
#define VILLAGER_BOND_OTHER_SPECIES 0x20
#define VILLAGER_BOND_BOTH_HAVE_DATA 0x3f
/* From this sum on the difference of the bytes 4 is not taken off. */
#define VILLAGER_BOND_AFFINITY_CAP 200

typedef struct VillagerBondSpeciesPair {
    u8 a;
    u8 b;
} VillagerBondSpeciesPair;

extern u8 data_021e5a2c[]; /* the town's eight villagers, 0x7ec bytes each */
/* By personality and personality (0-5 each): 8, 40 or 96. */
extern const u8 data_020cd500[];
/* By element and element: 128 for the same, 0 for earth and air or water and fire, else 48. */
extern const u8 data_020cd484[4][4];
/* The seven pairs of species that get on well and the four that do not, in either order. */
extern const VillagerBondSpeciesPair data_020cd464[7];
extern const VillagerBondSpeciesPair data_020cd434[4];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
/* Villager `index` of `villagers`, or null for an index outside 0-7. */
extern void *func_0207cec0(void *villagers, int index);
extern NpcId *func_0208150c(void *villager); /* the villager's NpcId, at 0x7a0 */
extern int func_0207cf74(u32 index);         /* whether the index is 0-7 */
/* The villager's data (data_020cd884), or 0 when its number has none. */
extern int func_02080890(void *villager);
/* The villager's species (the byte at 0x4c of its data, 0-32), 0x21 without data. */
extern int func_020808ec(void *villager);
/* The star sign of the villager's birthday (at 0x26 of its data), 12 without data. */
extern int func_0208090c(void *villager);

/* ---- How well two villagers get on */

/* func_02079924: how well villagers `first` and `second` get on: their affinity and two and a
 * half times their bond, 0 unless both have a valid NpcId.
 * QUIRK: a villager with itself reads the bond of the pair before it in the table (index
 * first-1 with 7) and, for villager 0, VILLAGER_BOND_NONE, which the factor wraps to a large
 * negative number. */
int VillagerBond_Compatibility(const s8 *bonds, int first, int second)
{
    void *a = func_0207cec0(data_021e5a2c, first);
    void *b = func_0207cec0(data_021e5a2c, second);

    if (a == NULL || !NpcId_IsValid(func_0208150c(a)) || b == NULL || !NpcId_IsValid(func_0208150c(b))) {
        return 0;
    }
    int bond = VillagerBond_Get(bonds, first, second);
    int affinity = VillagerBond_Affinity(bonds, a, b);
    return affinity + ((int) ((u32) bond * 5u) >> 1);
}
CLEAN_AS(func_02079924, VillagerBond_Compatibility)

/* func_02079994: how well the two villagers suit each other (villager_bonds.h): 0 unless both
 * have a valid NpcId; the sum of the personality, element, species and data scores, and when
 * that is below 200, its distance from the difference of the bytes 4. */
int VillagerBond_Affinity(const s8 *bonds, void *first, void *second)
{
    if (first == NULL || !NpcId_IsValid(func_0208150c(first))) {
        return 0;
    }
    if (second == NULL || !NpcId_IsValid(func_0208150c(second))) {
        return 0;
    }
    int sum = VillagerBond_PersonalityScore(bonds, func_0208150c(first), func_0208150c(second));
    sum += VillagerBond_ElementScore(bonds, first, second);
    sum += VillagerBond_SpeciesScore(bonds, first, second);
    sum += VillagerBond_BothHaveData(bonds, first, second);
    if (sum >= VILLAGER_BOND_AFFINITY_CAP) {
        return sum;
    }
    sum -= VillagerBond_ByteDifference(bonds, first, second);
    return sum < 0 ? -sum : sum;
}
CLEAN_AS(func_02079994, VillagerBond_Affinity)

/* func_02079a24: how far apart the two villagers' bytes 4 of their data are, 0 unless both
 * have data. */
int VillagerBond_ByteDifference(const s8 *bonds, void *first, void *second)
{
    (void) bonds;
    const u8 *a = (const u8 *) (uintptr_t) func_02080890(first);
    const u8 *b = (const u8 *) (uintptr_t) func_02080890(second);

    if (a == NULL || b == NULL) {
        return 0;
    }
    int x = a[VILLAGER_DATA_BYTE_04];
    int y = b[VILLAGER_DATA_BYTE_04];
    return x > y ? x - y : y - x;
}
CLEAN_AS(func_02079a24, VillagerBond_ByteDifference)

/* func_02079a5c: 0x3f when both villagers have data, else 0. */
int VillagerBond_BothHaveData(const s8 *bonds, void *first, void *second)
{
    (void) bonds;
    int a = func_02080890(first);
    int b = func_02080890(second);

    return a != 0 && b != 0 ? VILLAGER_BOND_BOTH_HAVE_DATA : 0;
}
CLEAN_AS(func_02079a5c, VillagerBond_BothHaveData)

static int villager_bond_species_listed(const VillagerBondSpeciesPair *pairs, int count, int x, int y)
{
    for (int i = 0; i < count; i++) {
        if ((pairs[i].a == x && pairs[i].b == y) || (pairs[i].b == x && pairs[i].a == y)) {
            return 1;
        }
    }
    return 0;
}

/* func_02079a88: 0x40 for the same species (two villagers without data count as the same),
 * 0x80 for a good pair, 0 for a bad one and 0x20 for others. */
int VillagerBond_SpeciesScore(const s8 *bonds, void *first, void *second)
{
    (void) bonds;
    int x = func_020808ec(first);
    int y = func_020808ec(second);

    if (x == y) {
        return VILLAGER_BOND_SAME_SPECIES;
    }
    if (villager_bond_species_listed(data_020cd464, 7, x, y)) {
        return VILLAGER_BOND_GOOD_SPECIES;
    }
    if (villager_bond_species_listed(data_020cd434, 4, x, y)) {
        return VILLAGER_BOND_BAD_SPECIES;
    }
    return VILLAGER_BOND_OTHER_SPECIES;
}
CLEAN_AS(func_02079a88, VillagerBond_SpeciesScore)

/* func_02079b08: the score of the elements of the two villagers' star signs.
 * QUIRK: a villager without data counts as earth (sign 12). */
unsigned char VillagerBond_ElementScore(const s8 *bonds, void *first, void *second)
{
    (void) bonds;
    int a = VILLAGER_BOND_ELEMENT(func_0208090c(first));
    int b = VILLAGER_BOND_ELEMENT(func_0208090c(second));

    return data_020cd484[a][b];
}
CLEAN_AS(func_02079b08, VillagerBond_ElementScore)

/* func_02079b3c: the score of the two personalities, 0 unless both NpcIds are valid.
 * QUIRK: a personality of 6 or more is not checked and reads past the 6 x 6 table. */
int VillagerBond_PersonalityScore(const s8 *bonds, const void *first, const void *second)
{
    (void) bonds;
    if (!NpcId_IsValid(first) || !NpcId_IsValid(second)) {
        return 0;
    }
    int a = NpcId_Personality(first);
    int b = NpcId_Personality(second);
    return data_020cd500[a * 6 + b];
}
CLEAN_AS(func_02079b3c, VillagerBond_PersonalityScore)

/* ---- The table of bonds */

/* func_02079b7c: the bond of villagers `first` and `second`, VILLAGER_BOND_NONE unless both are
 * villager indexes and the pair is in the table (see VillagerBond_PairIndex). */
int VillagerBond_Get(const s8 *bonds, int first, int second)
{
    if (!func_0207cf74((u32) first) || !func_0207cf74((u32) second)) {
        return VILLAGER_BOND_NONE;
    }
    int index = VillagerBond_PairIndex(bonds, first, second);
    if (!VillagerBond_IsPairIndex(bonds, (unsigned int) index)) {
        return VILLAGER_BOND_NONE;
    }
    return bonds[index];
}
CLEAN_AS(func_02079b7c, VillagerBond_Get)

/* func_02079bc4: `amount` added to the bond of villagers `first` and `second` (both villager
 * indexes). */
void VillagerBond_Add(s8 *bonds, int first, int second, int amount)
{
    if (func_0207cf74((u32) first) && func_0207cf74((u32) second)) {
        VillagerBond_AddAt(bonds, VillagerBond_PairIndex(bonds, first, second), amount);
    }
}
CLEAN_AS(func_02079bc4, VillagerBond_Add)

/* func_02079c00: `amount` added to the bond at `index` (0-27), held to -128 to 127. The sum wraps
 * as the ARM's 32-bit addition does. */
void VillagerBond_AddAt(s8 *bonds, int index, int amount)
{
    if (!VillagerBond_IsPairIndex(bonds, (unsigned int) index)) {
        return;
    }
    int sum = (int) ((u32) bonds[index] + (u32) amount);
    if (sum > 127) {
        sum = 127;
    } else if (sum < -128) {
        sum = -128;
    }
    bonds[index] = (s8) sum;
}
CLEAN_AS(func_02079c00, VillagerBond_AddAt)

/* func_02079c30: every bond of villager `villager` (a villager index) with the others set to 0. */
void VillagerBond_ForgetVillager(s8 *bonds, int villager)
{
    if (!func_0207cf74((u32) villager)) {
        return;
    }
    for (int other = 0; other < VILLAGERS; other++) {
        if (other == villager) {
            continue;
        }
        int index = VillagerBond_PairIndex(bonds, villager, other);
        if (VillagerBond_IsPairIndex(bonds, (unsigned int) index)) {
            bonds[index] = 0;
        }
    }
}
CLEAN_AS(func_02079c30, VillagerBond_ForgetVillager)

/* func_02079c74: where the pair of villagers `first` and `second` is in the table, in either
 * order: the pairs of every lower villager come first (7 - v of them for villager v), then the
 * higher one's place after the lower. The ROM counts the first part in a loop; it is summed here,
 * wrapping to 32 bits as that loop does. A villager with itself gives the index before its
 * first pair. */
int VillagerBond_PairIndex(const s8 *bonds, int first, int second)
{
    (void) bonds;
    int low = first > second ? second : first;
    int high = first > second ? first : second;
    int64_t before = 0;

    if (low > 0) {
        /* the sum of 7 - i for i from 0 to low - 1 */
        before = (int64_t) low * 7 - (int64_t) low * (low - 1) / 2;
    }
    return (int) ((u32) before + (u32) high - (u32) low - 1u);
}
CLEAN_AS(func_02079c74, VillagerBond_PairIndex)

/* func_02079ca4 */
int VillagerBond_IsPairIndex(const s8 *bonds, unsigned int index)
{
    (void) bonds;
    return index < VILLAGER_BOND_PAIRS;
}
CLEAN_AS(func_02079ca4, VillagerBond_IsPairIndex)

/* func_02079cb0: every bond 0. */
void VillagerBond_Clear(s8 *bonds)
{
    MI_CpuFill8(bonds, 0, VILLAGER_BOND_PAIRS);
}
CLEAN_AS(func_02079cb0, VillagerBond_Clear)

/* func_02079cbc: the destructor: does nothing. */
void VillagerBond_Destruct(s8 *bonds)
{
    (void) bonds;
}
CLEAN_AS(func_02079cbc, VillagerBond_Destruct)

/* func_02079cc0: the constructor: does nothing. */
void VillagerBond_Construct(s8 *bonds)
{
    (void) bonds;
}
CLEAN_AS(func_02079cc0, VillagerBond_Construct)
