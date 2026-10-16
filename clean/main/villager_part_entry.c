/* The entry at 0x94 of the villagers' part of a player's record (villager_part_entry.h). */
#include "villager_part_entry.h"

#include "clean.h"
#include "nook_store.h"
#include "player_record.h"
#include "player_records.h"
#include "shops.h"

static_assert(sizeof(VillagerPartEntry) == 16, "entry");
static_assert(offsetof(VillagerPartEntry, index) == 0x0c, "index");
static_assert(offsetof(VillagerPartEntry, choices) == 0x0d, "choices");

/* The kind of the codes the entries name, and the four codes index 0 names. */
#define VILLAGER_PART_ENTRY_CODE_KIND 0xd
#define VILLAGER_PART_ENTRY_INDEX0_FIRST 0xd019
#define VILLAGER_PART_ENTRY_INDEX0_LAST 0xd01c
/* The choices left out outside the shops' hours, and on the Nook store's closed days. */
#define VILLAGER_PART_ENTRY_SHOP_CHOICES 0x03
#define VILLAGER_PART_ENTRY_STORE_CHOICE 0x01
/* Choices 2 and 3 count as one when both are open. */
#define VILLAGER_PART_ENTRY_PAIR_FIRST 2
#define VILLAGER_PART_ENTRY_PAIR_SECOND 3
#define VILLAGER_PART_ENTRY_ALL_CHOICES 0x1f

extern const u16 data_020d1a54[VILLAGER_PART_ENTRY_CHOICES]; /* the code each index names */
extern const u16 data_020d1a28[2];                           /* the entry's items: 0x155f, 0x1560 */
extern NookStore data_021f395c;

extern int func_020644cc(int bound);                   /* a random number below `bound` */
extern int func_02094ffc(const DesignCreator *player); /* 0 for a player of this town */
extern int func_0204bcdc(const u16 *code);             /* whether the code has a variant */
extern int func_0204bc64(const u16 *code);             /* its item without the variant */
extern int func_02082438(void *text, const u16 *code); /* writes the code's name */
/* An object: whether it holds something (type below 22), the low five bits of its byte 0x0b
 * and their setter, its item set, set to a type and item, and emptied. */
extern int func_0209bd44(const u8 *object);
extern int func_0209bba0(const u8 *object);
extern void func_0209bb90(u8 *object, int value);
extern void func_0209bb68(u8 *object, const u16 *item);
extern void func_0209bd30(u8 *object, u8 type, const u16 *item, u8 low_bits);
extern void func_0209bd5c(u8 *object);

/* Bit `bit` of a byte, as the ARM shifts: by the low byte of `bit`, nothing from 8 on. */
static u8 villager_part_entry_bit(int bit)
{
    u32 amount = (u32) bit & 0xff;
    return amount < 8 ? (u8) (1u << amount) : 0;
}

/* func_0209af80: whether `code` is the one the entry names, for the current player of this
 * town while the entry holds something with the low bits of its byte 0x0b clear. Index 0 takes
 * any of the codes 0xd019-0xd01c; the others their code, compared without the variant when
 * `code` has one. */
int VillagerPartEntry_Accepts(VillagerPartEntry *entry, const u16 *code)
{
    if (entry->index >= VILLAGER_PART_ENTRY_CHOICES) {
        return 0;
    }
    if (PlayerRecords_Current() == NULL) {
        return 0;
    }
    if (func_02094ffc(PlayerRecord_Player(PlayerRecords_Current())) != 0) {
        return 0;
    }
    if ((*code >> 12) != VILLAGER_PART_ENTRY_CODE_KIND) {
        return 0;
    }
    if (func_0209bd44(entry->object) == 0 || func_0209bba0(entry->object) != 0) {
        return 0;
    }
    if (*code >= VILLAGER_PART_ENTRY_INDEX0_FIRST && *code <= VILLAGER_PART_ENTRY_INDEX0_LAST) {
        return entry->index == 0;
    }

    u16 wanted = data_020d1a54[entry->index];
    if (func_0204bcdc(code) != 0) {
        int item = func_0204bc64(code);
        return item == func_0204bc64(&wanted);
    }
    return *code == wanted;
}
CLEAN_AS(func_0209af80, VillagerPartEntry_Accepts)

/* func_0209b044: the entry moves to another open choice drawn at random: it is closed, its index
 * kept, the low bits of the object's byte 0x0b cleared and its item drawn anew. Then when one
 * choice is left, or two on a coin toss, all choices close. 0, with the choices closed, when
 * none can be drawn; 0 when none were open. */
int VillagerPartEntry_Advance(VillagerPartEntry *entry)
{
    if (entry->choices == 0) {
        return 0;
    }
    u32 choice = (u32) VillagerPartEntry_PickChoice(entry, entry->choices);
    if (choice >= VILLAGER_PART_ENTRY_CHOICES) {
        entry->choices = 0;
        return 0;
    }

    VillagerPartEntry_CloseChoice(entry, (int) choice);
    entry->index = (u8) choice;
    func_0209bb90(entry->object, 0);
    u16 item = data_020d1a28[func_020644cc(10) & 1];
    func_0209bb68(entry->object, &item);

    u8 left = VillagerPartEntry_CountLeft(entry, entry->choices);
    if (left == 1 || (left == 2 && (func_020644cc(10) & 1) != 0)) {
        entry->choices = 0;
    }
    return 1;
}
CLEAN_AS(func_0209b044, VillagerPartEntry_Advance)

/* func_0209b0c4: the name of the code the entry names written into `text` (func_02082438's
 * result); 0 without an entry. */
int VillagerPartEntry_WriteName(VillagerPartEntry *entry, void *text)
{
    if (entry->index >= VILLAGER_PART_ENTRY_CHOICES) {
        return 0;
    }
    u16 code = data_020d1a54[entry->index];
    return func_02082438(text, &code);
}
CLEAN_AS(func_0209b0c4, VillagerPartEntry_WriteName)

/* func_0209b0f0 */
VillagerPartEntry *VillagerPartEntry_Self(VillagerPartEntry *entry)
{
    return entry;
}
CLEAN_AS(func_0209b0f0, VillagerPartEntry_Self)

/* func_0209b0f4: a new entry: type 20 with one of its two items drawn at random, all five
 * choices open, then one drawn and closed. */
void VillagerPartEntry_Start(VillagerPartEntry *entry)
{
    int which = func_020644cc(10) & 1;
    VillagerPartEntry_Clear(entry);
    u16 item = data_020d1a28[which];
    func_0209bd30(entry->object, VILLAGER_PART_ENTRY_TYPE, &item, 0);
    entry->choices |= VILLAGER_PART_ENTRY_ALL_CHOICES;

    u32 choice = (u32) VillagerPartEntry_PickChoice(entry, entry->choices);
    if (choice < VILLAGER_PART_ENTRY_CHOICES) {
        VillagerPartEntry_CloseChoice(entry, (int) choice);
        entry->index = (u8) choice;
    }
}
CLEAN_AS(func_0209b0f4, VillagerPartEntry_Start)

/* func_0209b160: choice `choice` closed; choices 2 and 3 close together. */
void VillagerPartEntry_CloseChoice(VillagerPartEntry *entry, int choice)
{
    if ((u32) choice - VILLAGER_PART_ENTRY_PAIR_FIRST <= 1) {
        entry->choices &= (u8) ~(1u << VILLAGER_PART_ENTRY_PAIR_FIRST);
        entry->choices &= (u8) ~(1u << VILLAGER_PART_ENTRY_PAIR_SECOND);
    } else {
        entry->choices &= (u8) ~villager_part_entry_bit(choice);
    }
}
CLEAN_AS(func_0209b160, VillagerPartEntry_CloseChoice)

/* func_0209b184: one of the `choices` (bits 0-4) drawn at random, leaving out choices 0 and 1
 * outside the shops' hours (8 to 22) and choice 0 on the days the Nook store is closed; -1 when
 * none is left. */
int VillagerPartEntry_PickChoice(VillagerPartEntry *entry, int choices)
{
    if (Shops_IsHour8To22() == 0) {
        choices = (u8) (choices & ~VILLAGER_PART_ENTRY_SHOP_CHOICES);
    } else if (NookStore_IsClosedToday(&data_021f395c) != 0) {
        choices = (u8) (choices & ~VILLAGER_PART_ENTRY_STORE_CHOICE);
    }

    int count = VillagerPartEntry_CountChoices(entry, choices);
    if (count > 0) {
        int n = func_020644cc(count);
        for (int i = 0; i < VILLAGER_PART_ENTRY_CHOICES; i++) {
            if (((choices >> i) & 1) == 0) {
                continue;
            }
            if (n == 0) {
                return i;
            }
            n--;
        }
    }
    return -1;
}
CLEAN_AS(func_0209b184, VillagerPartEntry_PickChoice)

/* func_0209b1f0: how many of the `choices` are open, counting choices 2 and 3 as one. */
u8 VillagerPartEntry_CountLeft(VillagerPartEntry *entry, int choices)
{
    u8 count = VillagerPartEntry_CountChoices(entry, choices);
    if (((choices >> VILLAGER_PART_ENTRY_PAIR_FIRST) & 1) != 0 && ((choices >> VILLAGER_PART_ENTRY_PAIR_SECOND) & 1) != 0) {
        count--;
    }
    return count;
}
CLEAN_AS(func_0209b1f0, VillagerPartEntry_CountLeft)

/* func_0209b218: how many of bits 0-4 of `choices` are set. `entry` is not used. */
u8 VillagerPartEntry_CountChoices(VillagerPartEntry *entry, int choices)
{
    (void) entry;
    u8 count = 0;
    for (int i = 0; i < VILLAGER_PART_ENTRY_CHOICES; i++) {
        if (((choices >> i) & 1) != 0) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_0209b218, VillagerPartEntry_CountChoices)

/* func_0209b23c: no entry: the object emptied, no index, no choice open. */
void VillagerPartEntry_Clear(VillagerPartEntry *entry)
{
    func_0209bd5c(entry->object);
    entry->index = VILLAGER_PART_ENTRY_NONE;
    entry->choices = 0;
}
CLEAN_AS(func_0209b23c, VillagerPartEntry_Clear)
