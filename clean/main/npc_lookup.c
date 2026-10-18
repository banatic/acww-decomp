/* What the game looks up about a villager or a person (npc_lookup.h). */
#include "npc_lookup.h"

#include <string.h>

#include "clean.h"
#include "date_time.h"
#include "npc_id.h"
#include "session.h"
#include "small_texts.h"
#include "town_villager.h"
#include "villager_roster.h"
#include "lookups.h"
#include "message_reader.h"
#include "text_base.h"

#define NPC_CODE_KIND(code) (((code) & 0xf000) >> 12)
#define NPC_CODE_INDEX(code) ((code) & 0xfff)

/* In a special character's record: its personality kind and its species byte. */
#define NPC_SPECIAL_KIND 1
#define NPC_SPECIAL_SPECIES 2

/* What NpcLookup_FourUnlessSlotTaken gives while this system holds no slot of the session. */
#define NPC_LOOKUP_UNLINKED_COUNT 4

extern NetSession *data_020ccf94;  /* the game's session */
extern VillagerTown data_021e5a2c; /* the town's villagers */
extern const VillagerData data_020cd884[NPC_COUNT];
extern const char data_020e19a8[]; /* "st_npc_habit" */
extern const char data_020e19b8[]; /* "st_spnpc_name" */
extern const char data_020e19c8[]; /* "st_npc_name" */

/* func_020821d4: whether the time of `when` (its hour and minute) is strictly between the
 * start and the end of the night window of `personality`.
 * QUIRK: both ends are excluded: at the very minute the window starts, it is not in it. */
int NpcLookup_IsInNightWindow(int personality, const DateTime *when)
{
    const DayWindow *window = Lookups_DayWindow((u32) personality);
    DateTime bound;
    memset(&bound, 0, sizeof(bound));
    bound.hour = window->start_hour;
    bound.minute = window->start_minute;
    if (DateTime_Compare(when, &bound, DATE_TIME_HOUR | DATE_TIME_MINUTE) == 1) {
        bound.hour = window->end_hour;
        bound.minute = window->end_minute;
        return DateTime_Compare(when, &bound, DATE_TIME_HOUR | DATE_TIME_MINUTE) == -1;
    }
    return 0;
}
CLEAN_AS(func_020821d4, NpcLookup_IsInNightWindow)

/* func_02082240: 0 while this system holds its slot of the session, else 4 (how many villagers
 * may go out at most, and how many blocks ResourcePools_BlockCreate counts). */
int NpcLookup_FourUnlessSlotTaken(void)
{
    NetSession *session = data_020ccf94;
    if (Session_IsSlotTaken(session, session->local_slot) != 0) {
        return 0;
    }
    return NPC_LOOKUP_UNLINKED_COUNT;
}
CLEAN_AS(func_02082240, NpcLookup_FourUnlessSlotTaken)

/* func_02082308: villager `number`'s first catchphrase into a wide text, through a label of ten
 * characters; whether the number was valid (the wide text is untouched when not). */
int NpcLookup_CatchphraseToWide(void *wide, int number)
{
    Label10Text label;
    int done = 0;
    Label10Text_Construct(&label);
    if (NpcLookup_FormatCatchphrase(&label, number)) {
        TextBase_BytesToWide(wide, (TextBase *) &label);
        done = 1;
    }
    Label10Text_Destruct(&label);
    return done;
}
CLEAN_AS(func_02082308, NpcLookup_CatchphraseToWide)

/* func_02082340: villager `number`'s first catchphrase (its message of "st_npc_habit") into a
 * label; 0 for a number out of range. */
int NpcLookup_FormatCatchphrase(void *label, int number)
{
    if (!Npc_IsValidNumber((u32) number)) {
        return 0;
    }
    u8 message = (u8) number;
    MessageReader_LoadMessage((int) (uintptr_t) label, &message, (int) (uintptr_t) data_020e19a8);
    return 1;
}
CLEAN_AS(func_02082340, NpcLookup_FormatCatchphrase)

/* func_0208239c: the species byte of the person `*code` names: the town villager's
 * (VillagerData_SpeciesByte) or the special character's; 0 for no person. */
int NpcLookup_SpeciesByte(const ItemCode *code)
{
    int index = NPC_CODE_INDEX(*code);
    switch (NPC_CODE_KIND(*code)) {
        case NPC_CODE_KIND_SPECIAL: {
            const u8 *record = Lookups_KindDRecord(code);
            if (record != NULL) {
                return record[NPC_SPECIAL_SPECIES];
            }
            break;
        }
        case NPC_CODE_KIND_VILLAGER: {
            u8 *villager = VillagerRoster_At(&data_021e5a2c, index);
            if (villager != NULL) {
                return VillagerData_SpeciesByte(villager);
            }
            break;
        }
    }
    return NPC_LOOKUP_NO_SPECIES;
}
CLEAN_AS(func_0208239c, NpcLookup_SpeciesByte)

/* func_020823e8: the personality kind of the person `*code` names: the town villager's
 * (NpcId_PersonalityKind) or the special character's; 5 for no person. */
int NpcLookup_PersonalityKind(ItemCode *code)
{
    int index = NPC_CODE_INDEX(*code);
    switch (NPC_CODE_KIND(*code)) {
        case NPC_CODE_KIND_VILLAGER: {
            u8 *villager = VillagerRoster_At(&data_021e5a2c, index);
            if (villager != NULL) {
                return NpcId_PersonalityKind(TownVillager_NpcId(villager));
            }
            break;
        }
        case NPC_CODE_KIND_SPECIAL: {
            const u8 *record = Lookups_KindDRecord(code);
            if (record != NULL) {
                return record[NPC_SPECIAL_KIND];
            }
            break;
        }
    }
    return NPC_LOOKUP_NO_KIND;
}
CLEAN_AS(func_020823e8, NpcLookup_PersonalityKind)

/* func_02082438: the name of the person `*code` names into a label: the special character's
 * (its message of "st_spnpc_name"), or the town villager's (NpcId_FormatName); whether one was
 * written. */
int NpcLookup_FormatPersonName(void *label, ItemCode *code)
{
    int index = NPC_CODE_INDEX(*code);
    switch (NPC_CODE_KIND(*code)) {
        case NPC_CODE_KIND_SPECIAL:
            if (index < NPC_SPECIAL_COUNT) {
                u8 message = (u8) index;
                MessageReader_LoadMessage((int) (uintptr_t) label, &message, (int) (uintptr_t) data_020e19b8);
                return 1;
            }
            break;
        case NPC_CODE_KIND_VILLAGER: {
            u8 *villager = VillagerRoster_At(&data_021e5a2c, index);
            if (villager != NULL) {
                return NpcId_FormatName(TownVillager_NpcId(villager), label);
            }
            break;
        }
    }
    return 0;
}
CLEAN_AS(func_02082438, NpcLookup_FormatPersonName)

/* func_0208249c: villager `number`'s name (its message of "st_npc_name") into a label; 0 for a
 * number out of range. */
int NpcLookup_FormatName(char *label, int number)
{
    if (!Npc_IsValidNumber((u32) number)) {
        return 0;
    }
    u8 message = (u8) number;
    MessageReader_LoadMessage((int) (uintptr_t) label, &message, (int) (uintptr_t) data_020e19c8);
    return 1;
}
CLEAN_AS(func_0208249c, NpcLookup_FormatName)

/* func_02082500: villager `number`'s data, NULL for a number out of range. */
const VillagerData *NpcLookup_Data(int number)
{
    if (!Npc_IsValidNumber((u32) number)) {
        return NULL;
    }
    return &data_020cd884[number];
}
CLEAN_AS(func_02082500, NpcLookup_Data)
