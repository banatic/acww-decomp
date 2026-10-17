/* Overlay 094's sheet of item icons (vtable data_ov094_0229bf80, 0x808 bytes), kept at 0x184 of
 * the grid object (pockets_grid.h). It holds one file of 16 icons of 32 bytes' characters each
 * (16 x 16 pixels, as ScreenMap_CellTile numbers the cells), read from the ROM when asked for an
 * icon of another file:
 *
 * - "menu/icon/icon%02d.bch", file icon / 16, for the item icons (PocketsIcons_Chars), with a
 *   palette for each icon (PocketsIcons_Palette);
 * - "menu/icon/pre%d.bch", by a variant, for the frames of the grid's pick-up
 *   (PocketsIcons_LoadPickUpFrame), after which the next item icon reads its file again. */
#ifndef CLEAN_OV094_POCKETS_ICONS_H
#define CLEAN_OV094_POCKETS_ICONS_H

#include "types.h"

#define POCKETS_ICONS_FILE_SIZE 0x800
#define POCKETS_ICONS_PER_FILE 16
#define POCKETS_ICONS_NO_FILE 0xff

typedef struct PocketsIcons {
    u32 vtable;                        /* 0x000: data_ov094_0229bf80 */
    u8 chars[POCKETS_ICONS_FILE_SIZE]; /* 0x004: the file read */
    u8 file;                           /* 0x804: the icon file in `chars`, POCKETS_ICONS_NO_FILE for none */
    u8 pad_805[3];
} PocketsIcons;

u8 PocketsIcons_Palette(PocketsIcons *icons, int icon);
u8 *PocketsIcons_LoadPickUpFrame(PocketsIcons *icons, unsigned int frame, unsigned int variant);
u8 *PocketsIcons_Chars(PocketsIcons *icons, int icon);
void PocketsIcons_Forget(PocketsIcons *icons);
PocketsIcons *PocketsIcons_DestructDelete(PocketsIcons *icons);
void PocketsIcons_Destruct(PocketsIcons *icons);
void PocketsIcons_Construct(PocketsIcons *icons);

#endif
