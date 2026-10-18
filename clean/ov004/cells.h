/* The cells of the town's map a room object covers (RoomObject_ListCells lists them in a
 * CellList, room_object.h), and the set of other objects standing on those cells (layer 1 of
 * the map) that move and turn along with an object on the floor (RoomObject_MoveOnMap). */
#ifndef CLEAN_OV004_CELLS_H
#define CLEAN_OV004_CELLS_H

#include "types.h"

#include "room_object.h" /* CellList, RoomObject */

/* Up to four objects, each once. */
typedef struct ObjectSet {
    u32 count;
    RoomObject *objects[4];
} ObjectSet;

int ObjectSet_Add(ObjectSet *set, RoomObject *object);
RoomObject *ObjectSet_At(const ObjectSet *set, int index);
unsigned long ObjectSet_Count(const ObjectSet *set);
ObjectSet *ObjectSet_Destruct(ObjectSet *set);
ObjectSet *ObjectSet_Construct(ObjectSet *set, CellList *cells, int layer);
void ObjectSet_AddOnCells(ObjectSet *set, CellList *cells, int layer);
void ObjectSet_Clear(ObjectSet *set);

Cell *CellList_At(CellList *list, int index);
unsigned long CellList_Count(const CellList *list);
int CellList_Add(CellList *list, int x, int y);
void CellList_Destruct(CellList *list);
CellList *CellList_Construct(CellList *list);

#endif
