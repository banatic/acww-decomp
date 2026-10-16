/* A villager's errand of catching an insect or a fish (villager_errand_catch.h). */
#include "villager_errand_catch.h"

#include <string.h>

#include "clean.h"
#include "creature_draw.h"
#include "date_time.h"
#include "item_object.h"
#include "session_villager.h"
#include "villager_status.h"

/* The scene object's virtual function that gives its villager's town record. */
#define VILLAGER_ERRAND_CATCH_SLOT_RECORD 0x64

/* The object types of the two errands, and their items. */
#define VILLAGER_ERRAND_CATCH_TYPE_INSECT 0
#define VILLAGER_ERRAND_CATCH_TYPE_FISH 1
#define VILLAGER_ERRAND_CATCH_INSECT_FIRST 0x12b0
#define VILLAGER_ERRAND_CATCH_INSECT_LAST 0x12e7
#define VILLAGER_ERRAND_CATCH_FISH_FIRST 0x12e8
#define VILLAGER_ERRAND_CATCH_FISH_LAST 0x131f

/* The weight bands step 2 draws the first of. */
#define VILLAGER_ERRAND_CATCH_BANDS 4
/* The fields DateTime_Compare looks at: all six. */
#define VILLAGER_ERRAND_CATCH_ALL_FIELDS 0x3f

/* The minutes a catch waits since the last one, by step (-1 at step 0). */
extern const s8 data_020c8958[VILLAGER_ERRAND_CATCH_STEPS];

/* Whether the insect `*item` can be had at the hours first-last of the month; an insect drawn
 * of the weight bands first-last for the month into `*item`, nonzero when one was. */
extern int func_0202cef4(u16 *item, int first, int last, int month);
extern int func_0202d190(u16 *item, int first, int last, int month);
/* A place drawn by `count` weights, -1 when they are all 0. */
extern int func_0202d6e4(const u8 *weights, int count);
/* A random number below `bound`. */
extern int func_020644cc(int bound);
/* Whether a player id is set. */
extern int func_020951bc(const DesignCreator *player);

/* The town record of the scene object's villager (its virtual function at 0x64). */
static u8 *errand_scene_record(void *scene)
{
    const u8 *vtable = *(const u8 *const *) scene;
    u32 code = *(const u32 *) (const void *) (vtable + VILLAGER_ERRAND_CATCH_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(void *))(uintptr_t) code)(scene);
}

static int errand_is_insect(u16 item)
{
    return item >= VILLAGER_ERRAND_CATCH_INSECT_FIRST && item <= VILLAGER_ERRAND_CATCH_INSECT_LAST;
}

static int errand_is_fish(u16 item)
{
    return item >= VILLAGER_ERRAND_CATCH_FISH_FIRST && item <= VILLAGER_ERRAND_CATCH_FISH_LAST;
}

/* func_0202c57c: for the scene object's villager (when it has a town record), the insect and
 * then the fish errand's catch, both at now. */
void VillagerErrandCatch_Update(void *scene, int chances, int weights, int check_time)
{
    if (errand_scene_record(scene) == NULL) {
        return;
    }
    VillagerObject *object =
        VillagerObject_OfRecord((VillagerRecord *) (void *) VillagerStatus_ModeRecord(errand_scene_record(scene)));
    DateTime now = {0};
    DateTime_Now(&now);
    VillagerErrandCatch_Insect(scene, object, (u8 *) (uintptr_t) chances, (void *) (uintptr_t) weights, (u8) check_time, &now);
    VillagerErrandCatch_Fish(scene, object, (u8 *) (uintptr_t) chances, (void *) (uintptr_t) weights, (u8) check_time, &now);
}
CLEAN_AS(func_0202c57c, VillagerErrandCatch_Update)

/* What both errands do after the catch: the item sent to the session when it is one of the
 * errand's kind and the scene object has a villager, then the time of the catch kept. */
static void errand_after(void *scene, VillagerObject *object, DateTime *now, int (*of_kind)(u16 item))
{
    if (errand_scene_record(scene) != NULL && of_kind(*VillagerObject_Item(object))) {
        u8 *record = errand_scene_record(scene);
        SessionVillager_SendObjectItem(record, VillagerObject_Item(object));
    }
    DateTime when = *now;
    *VillagerObject_Date(object) = when;
}

/* The chance in 100 of the step (0 past the table). */
static int errand_chance(const u8 *chances, int step)
{
    return step < VILLAGER_ERRAND_CATCH_STEPS ? chances[step] : 0;
}

/* func_0202c5dc: the fish errand's catch (villager_errand_catch.h). */
void VillagerErrandCatch_Fish(void *scene, VillagerObject *object, u8 *chances, void *weights, u8 check_time, DateTime *now)
{
    ItemObject *base = (ItemObject *) (void *) VillagerObject_Base(object);
    if (ItemObject_Type(base) != VILLAGER_ERRAND_CATCH_TYPE_FISH) {
        return;
    }
    int step = VillagerObject_Step(object);
    if (VillagerErrandCatch_CanCatch(scene, object, now, check_time) == 0) {
        return;
    }
    int chance = errand_chance(chances, step);
    int roll = func_020644cc(100);
    u16 item = *ItemObject_Item(base);
    switch (step) {
        case 1:
        case 3:
        case 4:
            if (roll < chance && CreatureDraw_FishAvailable(&item, now->hour, now->hour, now->month, now->day) != 0) {
                *VillagerObject_Item(object) = item;
            }
            break;
        case 2:
            if (roll < chance) {
                int band = func_0202d6e4((const u8 *) weights, VILLAGER_ERRAND_CATCH_BANDS);
                if (CreatureDraw_FishOfBands(&item, band, band + 1, now->month, now->day) != 0) {
                    *VillagerObject_Item(object) = item;
                }
            }
            break;
        default:
            break;
    }
    errand_after(scene, object, now, errand_is_fish);
}
CLEAN_AS(func_0202c5dc, VillagerErrandCatch_Fish)

/* func_0202c704: the insect errand's catch (villager_errand_catch.h). */
void VillagerErrandCatch_Insect(void *scene, VillagerObject *object, u8 *chances, void *weights, u8 check_time, DateTime *now)
{
    ItemObject *base = (ItemObject *) (void *) VillagerObject_Base(object);
    if (ItemObject_Type(base) != VILLAGER_ERRAND_CATCH_TYPE_INSECT) {
        return;
    }
    int step = VillagerObject_Step(object);
    if (VillagerErrandCatch_CanCatch(scene, object, now, check_time) == 0) {
        return;
    }
    int chance = errand_chance(chances, step);
    int roll = func_020644cc(100);
    u16 item = *ItemObject_Item(base);
    switch (step) {
        case 1:
        case 3:
        case 4:
            if (roll < chance && func_0202cef4(&item, now->hour, now->hour, now->month) != 0) {
                *VillagerObject_Item(object) = item;
            }
            break;
        case 2:
            if (roll < chance) {
                int band = func_0202d6e4((const u8 *) weights, VILLAGER_ERRAND_CATCH_BANDS);
                if (func_0202d190(&item, band, band + 1, now->month) != 0) {
                    *VillagerObject_Item(object) = item;
                }
            }
            break;
        default:
            break;
    }
    errand_after(scene, object, now, errand_is_insect);
}
CLEAN_AS(func_0202c704, VillagerErrandCatch_Insect)

/* func_0202c824: whether the villager can catch now: its object in use, with low bits 0, of
 * group 0, past step 0 and before its last step, with a player set, and an insect errand that
 * has caught no insect yet or a fish errand that has caught no fish. Without `check_time` that
 * is all; else the object needs a date, and when now is after it, at least the step's minutes
 * of data_020c8958 since it (none at step 0); now before it is fine, now at it is not. */
int VillagerErrandCatch_CanCatch(void *scene, VillagerObject *object, DateTime *now, u8 check_time)
{
    (void) scene;
    ItemObject *base = (ItemObject *) (void *) VillagerObject_Base(object);
    int step = VillagerObject_Step(object);
    if (ItemObject_IsInUse(base) == 0 || ItemObject_Low5(base) != 0 || ItemObject_Group(base) != 0 || step == 0) {
        return 0;
    }
    if (func_020951bc(VillagerObject_Player(object)) == 0) {
        return 0;
    }
    int type = ItemObject_Type(base);
    if (step >= VillagerObject_StepsForType(type)) {
        return 0;
    }
    int caught;
    if (type == VILLAGER_ERRAND_CATCH_TYPE_INSECT && !errand_is_insect(*VillagerObject_Item(object))) {
        caught = 0;
    } else if (type != VILLAGER_ERRAND_CATCH_TYPE_FISH) {
        return 0;
    } else {
        caught = errand_is_fish(*VillagerObject_Item(object));
    }
    if (caught) {
        return 0;
    }

    DateTime *last = VillagerObject_Date(object);
    if (check_time == 0) {
        return 1;
    }
    u32 words[2];
    memcpy(words, last, sizeof words);
    if (words[0] == 0 && words[1] == 0) {
        return 0;
    }
    int order = DateTime_Compare(now, last, VILLAGER_ERRAND_CATCH_ALL_FIELDS);
    if (order == 1) {
        int wait = step < VILLAGER_ERRAND_CATCH_STEPS ? data_020c8958[step] : 0;
        if (wait <= 0 || DateTime_MinutesBetween(last, now) < wait) {
            return 0;
        }
        return 1;
    }
    return order == -1;
}
CLEAN_AS(func_0202c824, VillagerErrandCatch_CanCatch)
