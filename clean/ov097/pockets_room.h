/* Overlay 097: the pockets scene's (ov096/pockets_screen.h) code for when data_020e54a8 is not
 * 0, the case in which main's func_02034b80 and func_02034b04 (which it calls when it is 1)
 * put up a wallpaper or a carpet in the room (overlay 4's room objects load wallpaper items
 * 0x1100-0x1143 and carpet items 0x1144-0x1187). The pockets scene asks it whether an item can
 * be used (PocketsRoom_CanUse, PocketsRoom_CheckUseItem), for the choice rows of a wallpaper or
 * a carpet in the grid (PocketsRoom_AddItemRows) and runs its two actions, 18 and 19, which
 * swap the picked wallpaper or carpet with the room's. When data_020e54a8 is 0 the scene uses
 * overlay 098 instead (ov098/pockets_town.h). */
#ifndef CLEAN_OV097_POCKETS_ROOM_H
#define CLEAN_OV097_POCKETS_ROOM_H

#include "ov096/pockets_screen.h"
#include "types.h"

int PocketsRoom_CanUse(PocketsScreen *self);
int PocketsRoom_CheckUseItem(PocketsScreen *self, u16 item);
void PocketsRoom_AddItemRows(PocketsScreen *self, u16 item);
void PocketsRoom_ActionWallpaper(PocketsScreen *self);
void PocketsRoom_ActionCarpet(PocketsScreen *self);

#endif
