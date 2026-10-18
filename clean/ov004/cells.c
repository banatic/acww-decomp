/* The cells a room object covers and the objects standing on them (cells.h). */
#include "cells.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"
#include "room_objects.h"

static_assert(sizeof(ObjectSet) == 0x14, "object set");
static_assert(offsetof(CellList, cells) == 4, "cell list cells");
static_assert(sizeof(CellList) == 0x24, "cell list");

#define SET_SIZE 4
#define LIST_SIZE 4
#define LAYER_FLOOR 0
#define LAYER_ON_TOP 1

/* func_ov004_0220da70: `object` added unless it is null, the set is full or already holds it;
 * whether it was. */
int ObjectSet_Add(ObjectSet *set, RoomObject *object)
{
    if (object == NULL) {
        return 0;
    }
    u32 count = set->count;
    if (count >= SET_SIZE) {
        return 0;
    }
    for (u32 i = 0; i < count; i++) {
        if (set->objects[i] == object) {
            return 0;
        }
    }
    set->count++;
    set->objects[count] = object;
    return 1;
}
CLEAN_AS(func_ov004_0220da70, ObjectSet_Add)

/* func_ov004_0220dab0; the index is taken modulo 4. */
RoomObject *ObjectSet_At(const ObjectSet *set, int index)
{
    return set->objects[index & (SET_SIZE - 1)];
}
CLEAN_AS(func_ov004_0220dab0, ObjectSet_At)

/* func_ov004_0220dabc */
unsigned long ObjectSet_Count(const ObjectSet *set)
{
    return set->count;
}
CLEAN_AS(func_ov004_0220dabc, ObjectSet_Count)

/* func_ov004_0220dac0: empties the set. */
ObjectSet *ObjectSet_Destruct(ObjectSet *set)
{
    ObjectSet_Clear(set);
    return set;
}
CLEAN_AS(func_ov004_0220dac0, ObjectSet_Destruct)

/* func_ov004_0220dad0: the objects standing on `cells`, for an object on `layer`. */
ObjectSet *ObjectSet_Construct(ObjectSet *set, CellList *cells, int layer)
{
    ObjectSet_Clear(set);
    ObjectSet_AddOnCells(set, cells, layer);
    return set;
}
CLEAN_AS(func_ov004_0220dad0, ObjectSet_Construct)

/* func_ov004_0220daf0: for an object on the floor, adds the objects on top (layer 1) of each of
 * its cells; an object on top carries nothing. */
void ObjectSet_AddOnCells(ObjectSet *set, CellList *cells, int layer)
{
    if (layer != LAYER_FLOOR) {
        return;
    }
    for (unsigned long i = 0; i < CellList_Count(cells); i++) {
        void *grid = RoomObjects_Grid();
        int x = CellList_At(cells, (int) i)->x;
        int y = CellList_At(cells, (int) i)->y;
        RoomObject *object = RoomObjects_GridObjectAt(grid, x, y, LAYER_ON_TOP);
        if (object != NULL) {
            ObjectSet_Add(set, object);
        }
    }
}
CLEAN_AS(func_ov004_0220daf0, ObjectSet_AddOnCells)

/* func_ov004_0220db48 */
void ObjectSet_Clear(ObjectSet *set)
{
    set->count = 0;
    for (int i = 0; i < SET_SIZE; i++) {
        set->objects[i] = NULL;
    }
}
CLEAN_AS(func_ov004_0220db48, ObjectSet_Clear)

/* func_ov004_0220db5c; the index is taken modulo 4. */
Cell *CellList_At(CellList *list, int index)
{
    return &list->cells[index & (LIST_SIZE - 1)];
}
CLEAN_AS(func_ov004_0220db5c, CellList_At)

/* func_ov004_0220db68 */
unsigned long CellList_Count(const CellList *list)
{
    return list->count;
}
CLEAN_AS(func_ov004_0220db68, CellList_Count)

/* func_ov004_0220db6c: cell (x, y) appended unless the list is full; whether it was. */
int CellList_Add(CellList *list, int x, int y)
{
    if (list->count < LIST_SIZE) {
        list->cells[list->count].x = x;
        list->cells[list->count].y = y;
        list->count++;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0220db6c, CellList_Add)

/* func_ov004_0220db90 */
void CellList_Destruct(CellList *list)
{
    (void) list;
}
CLEAN_AS(func_ov004_0220db90, CellList_Destruct)

/* func_ov004_0220db94: an empty list with every cell (0, 0). */
CellList *CellList_Construct(CellList *list)
{
    for (int i = 0; i < LIST_SIZE; i++) {
        list->cells[i].x = 0;
        list->cells[i].y = 0;
    }
    list->count = 0;
    return list;
}
CLEAN_AS(func_ov004_0220db94, CellList_Construct)
