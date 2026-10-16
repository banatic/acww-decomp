/* Putting an item on a tile of a map while linked: an item record of five bytes (the item
 * code, a scene byte holding the scene and a flag (PackedBytes_JoinScene), then the tile's x
 * and z as signed bytes) is put on the town's map (scene 0, where the flag sets the tile's bit
 * in its acre) or on the room's map of that number.
 *
 * The machine that holds the scene (LinkGlobal_HoldsScene) puts the item down and, when
 * linked, sends the record on to the others as session message 18 (SessionMessage_PlaceTownItems
 * puts it down there); any other machine sends it to the holder as message 19
 * (SessionMessage_RelayTownItems). */
#ifndef CLEAN_MAIN_LINKED_MAP_ITEMS_H
#define CLEAN_MAIN_LINKED_MAP_ITEMS_H

#include "types.h"

/* The size of an item record. */
#define LINKED_MAP_ITEMS_RECORD_SIZE 5

void LinkedMapItems_Set(unsigned char x, unsigned char z, int scene, int item, int flag);
void LinkedMapItems_PlaceAndShare(u8 *record);
int LinkedMapItems_Place(unsigned char *record);

#endif
