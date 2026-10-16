/* The town's order of the item groups (item_group_order.h). */
#include "item_group_order.h"

#include "clean.h"
#include "main_random.h"
#include "room_score.h"

/* The six orders: the weights of the groups 1-3 in each. */
extern const u8 data_020cca9c[ITEM_GROUP_ORDER_ROWS][ITEM_GROUP_ORDER_GROUPS];
/* The town's three values before the first and third are set: only the second (30) is kept. */
extern const u8 data_020de63c[ITEM_GROUP_ORDER_GROUPS];

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
/* An order's destructor and constructor, handed to the C++ runtime (ItemGroupOrder_Destruct,
 * ItemGroupOrder_Construct). */
extern void func_0206411c(void *order);
extern void func_02064120(void *order);

/* The town's first value is 60 less, and its third 10 more than this, a tenth of two of the
 * house's edge sums (FX_Div of the plain sum by 10.0), cut to a byte. */
#define ITEM_GROUP_ORDER_TEN 0xa000 /* 10.0 */
#define ITEM_GROUP_ORDER_FIRST_BASE 60
#define ITEM_GROUP_ORDER_THIRD_BASE 10
/* The first and third values add up to this (in bytes). */
#define ITEM_GROUP_ORDER_FIRST_AND_THIRD 70
/* The chances of the random place are out of this. */
#define ITEM_GROUP_ORDER_CHANCES 100

typedef u32 ItemGroupOrderBelow(DateRandom *source, u32 bound);

static u8 house_tenth(void)
{
    int sum = RoomScore_HouseHighX() + RoomScore_HouseHighZ();
    return (u8) FX_Div(sum, ITEM_GROUP_ORDER_TEN);
}

/* func_02063eb8: each kind's order set at random. */
void ItemGroupOrder_InitAll(u8 *orders)
{
    for (u32 i = 0; i < ITEM_GROUP_ORDER_KINDS; i++) {
        ItemGroupOrder_Init((char *) &orders[i]);
    }
}
CLEAN_AS(func_02063eb8, ItemGroupOrder_InitAll)

/* func_02063ed4: the nine orders destructed (by the C++ runtime). */
void *ItemGroupOrder_DestructAll(void *orders)
{
    __cxa_vec_cleanup(orders, ITEM_GROUP_ORDER_KINDS, 1, func_0206411c);
    return orders;
}
CLEAN_AS(func_02063ed4, ItemGroupOrder_DestructAll)

/* func_02063ef0: the nine orders constructed (by the C++ runtime). */
void *ItemGroupOrder_ConstructAll(void *orders)
{
    __cxa_vec_ctor(orders, ITEM_GROUP_ORDER_KINDS, 1, func_02064120, func_0206411c);
    return orders;
}
CLEAN_AS(func_02063ef0, ItemGroupOrder_ConstructAll)

/* func_02063f18: the group (1-3) the order gives `weight`; group 1 when none does. */
int ItemGroupOrder_GroupOfWeight(u8 *order, u8 weight)
{
    const u8 *row = ItemGroupOrder_Row(order);
    for (u32 i = 0; i < ITEM_GROUP_ORDER_GROUPS; i++) {
        if (row[i] == weight) {
            return (int) i + 1;
        }
    }
    return 1;
}
CLEAN_AS(func_02063f18, ItemGroupOrder_GroupOfWeight)

/* func_02063f3c: the order's byte. */
int ItemGroupOrder_Get(u8 *order)
{
    return *order;
}
CLEAN_AS(func_02063f3c, ItemGroupOrder_Get)

/* func_02063f40: the town's value `index` (0-2): 60 - x, 30 or x + 10 (see house_tenth);
 * the first for an index past 2. */
u8 ItemGroupOrder_Weight(u32 index)
{
    u8 tenth = house_tenth();
    u8 values[ITEM_GROUP_ORDER_GROUPS];
    values[0] = (u8) (ITEM_GROUP_ORDER_FIRST_BASE - tenth);
    values[1] = data_020de63c[1];
    values[2] = (u8) (tenth + ITEM_GROUP_ORDER_THIRD_BASE);
    return index < ITEM_GROUP_ORDER_GROUPS ? values[index] : values[0];
}
CLEAN_AS(func_02063f40, ItemGroupOrder_Weight)

/* func_02063f94: the group an item list of the kind whose order is `order` draws from.
 *
 * For ITEM_GROUP_ORDER_RANDOM a number below 100 from `source` (the clock's source when it is
 * NULL, built on the stack either way) picks the place: the first with a chance of the first
 * value, the third with the third's, else the second; the group is then asked for that place
 * (the values computed again). For a place, the group of the weight that ranks as the place's
 * value ranks: 60 when it is the greatest, 30 when it is in the middle, else 10. Any other
 * `place` is returned as it is.
 * QUIRK: the values are bytes (the first and third add up to 70 modulo 256), so the middle
 * case of the first place never holds; the ties fall as the game's comparisons have them. */
int ItemGroupOrder_PickGroup(u8 *order, int place, DateRandom *source)
{
    u8 first = (u8) (ITEM_GROUP_ORDER_FIRST_BASE - house_tenth());
    u8 third = (u8) (ITEM_GROUP_ORDER_FIRST_AND_THIRD - first);
    int second = ITEM_GROUP_ORDER_MIDDLE;

    switch (place) {
        case ITEM_GROUP_ORDER_RANDOM: {
            DateRandom clock;
            DateRandom_Construct(&clock);
            if (source == NULL) {
                source = &clock;
            }
            u32 roll = ((ItemGroupOrderBelow *) (uintptr_t) source->vtable->below)(source, ITEM_GROUP_ORDER_CHANCES);
            int picked;
            if (roll < first) {
                picked = ItemGroupOrder_PickGroup(order, ITEM_GROUP_ORDER_FIRST, source);
            } else if (roll < (u32) (first + third)) {
                picked = ItemGroupOrder_PickGroup(order, ITEM_GROUP_ORDER_THIRD, source);
            } else {
                picked = ItemGroupOrder_PickGroup(order, ITEM_GROUP_ORDER_SECOND, source);
            }
            DateRandom_Destruct(&clock);
            return picked;
        }
        case ITEM_GROUP_ORDER_FIRST:
            if (first >= second && first >= third) {
                return ItemGroupOrder_GroupOfWeight(order, ITEM_GROUP_ORDER_HIGH);
            }
            if (first <= second && third <= second) {
                return ItemGroupOrder_GroupOfWeight(order, ITEM_GROUP_ORDER_MIDDLE);
            }
            return ItemGroupOrder_GroupOfWeight(order, ITEM_GROUP_ORDER_LOW);
        case ITEM_GROUP_ORDER_SECOND:
            if ((first <= second && first >= third) || (first >= second && first <= third)) {
                return ItemGroupOrder_GroupOfWeight(order, ITEM_GROUP_ORDER_HIGH);
            }
            if ((first >= second && third <= second) || (first <= second && third >= second)) {
                return ItemGroupOrder_GroupOfWeight(order, ITEM_GROUP_ORDER_MIDDLE);
            }
            return ItemGroupOrder_GroupOfWeight(order, ITEM_GROUP_ORDER_LOW);
        case ITEM_GROUP_ORDER_THIRD:
            if (first <= second && first <= third) {
                return ItemGroupOrder_GroupOfWeight(order, ITEM_GROUP_ORDER_HIGH);
            }
            if (first >= second && third >= second) {
                return ItemGroupOrder_GroupOfWeight(order, ITEM_GROUP_ORDER_MIDDLE);
            }
            return ItemGroupOrder_GroupOfWeight(order, ITEM_GROUP_ORDER_LOW);
        default:
            return place;
    }
}
CLEAN_AS(func_02063f94, ItemGroupOrder_PickGroup)

/* func_020640e0: the order's row of weights.
 * QUIRK: a byte past the six orders is first stored back reduced modulo 6. */
u8 *ItemGroupOrder_Row(u8 *order)
{
    if (*order >= ITEM_GROUP_ORDER_ROWS) {
        *order = *order % ITEM_GROUP_ORDER_ROWS;
    }
    return (u8 *) data_020cca9c[*order];
}
CLEAN_AS(func_020640e0, ItemGroupOrder_Row)

/* func_02064108: one of the six orders at random. */
void ItemGroupOrder_Init(char *order)
{
    *order = (char) MainRandom_Below(ITEM_GROUP_ORDER_ROWS);
}
CLEAN_AS(func_02064108, ItemGroupOrder_Init)

/* func_0206411c: the destructor: nothing to do. */
void ItemGroupOrder_Destruct(void *order)
{
    (void) order;
}
CLEAN_AS(func_0206411c, ItemGroupOrder_Destruct)

/* func_02064120: the constructor: nothing to do (the byte is set by ItemGroupOrder_Init). */
void ItemGroupOrder_Construct(void *order)
{
    (void) order;
}
CLEAN_AS(func_02064120, ItemGroupOrder_Construct)
