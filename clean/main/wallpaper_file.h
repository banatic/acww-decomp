/* The file of a wallpaper's texture (0x10c4 bytes, filled from "/wall/wall_%d.nsbtx"), which
 * overlay 4 keeps two of to put the room's wallpaper on its walls. */
#ifndef CLEAN_MAIN_WALLPAPER_FILE_H
#define CLEAN_MAIN_WALLPAPER_FILE_H

#include "types.h"

/* The wallpaper items: 0x1100 to 0x1143, wallpaper 0 to 67. */
#define WALLPAPER_FILE_FIRST_ITEM 0x1100
#define WALLPAPER_FILE_LAST_ITEM 0x1143

unsigned int WallpaperFile_Texture(void *file);
int WallpaperFile_Load(void *file, u16 *item);
void *WallpaperFile_Construct(void *file);

#endif
