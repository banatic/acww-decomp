/* The file of a wallpaper's texture (wallpaper_file.h). */
#include "wallpaper_file.h"

#include "clean.h"
#include "g3d_resource.h"
#include "c_library.h"
#include "rom_file.h"

/* The texture resource of a file. */
extern G3dResTex *func_021077e8(void *file);
extern void __register_global_object(void *object, void *destruct, void *record);
/* The destructor of an item code (TrivialObject_DestructItemCode), as handed to the game. */
extern void func_020051b0(void *item);

extern const char data_020e5958[]; /* "/wall/wall_%d.nsbtx" */

/* WallpaperFile_Load's fallback item (a static of that function), its guard (bit 0 once it is
 * set) and its record for __register_global_object. */
extern u16 data_021f6ca8;
extern u32 data_021f6cac;
extern u8 data_021f6cb0[];

/* Room for the path: "/wall/wall_" and a number below 68 and ".nsbtx". */
#define WALLPAPER_FILE_PATH_SIZE 32

/* func_020ba1ec: the file's texture resource (its address). */
unsigned int WallpaperFile_Texture(void *file)
{
    return (unsigned int) (uintptr_t) func_021077e8(file);
}
CLEAN_AS(func_020ba1ec, WallpaperFile_Texture)

/* func_020ba1f4: the texture of the wallpaper `*item` read into `file`; 1 when it was read.
 * An item that is not a wallpaper loads wallpaper 0 (item 0x1100) instead. */
int WallpaperFile_Load(void *file, u16 *item)
{
    unsigned int code = *item;
    if (code >= WALLPAPER_FILE_FIRST_ITEM && code <= WALLPAPER_FILE_LAST_ITEM) {
        char path[WALLPAPER_FILE_PATH_SIZE];
        CLib_SPrintf(path, data_020e5958, (int) (code - WALLPAPER_FILE_FIRST_ITEM));
        return RomFile_Read(path, file, -1) != 0;
    }
    if ((data_021f6cac & 1) == 0) {
        data_021f6ca8 = WALLPAPER_FILE_FIRST_ITEM;
        __register_global_object(&data_021f6ca8, (void *) (uintptr_t) func_020051b0, data_021f6cb0);
        data_021f6cac |= 1;
    }
    return WallpaperFile_Load(file, &data_021f6ca8);
}
CLEAN_AS(func_020ba1f4, WallpaperFile_Load)

/* func_020ba294: the constructor, which leaves the file as it is. */
void *WallpaperFile_Construct(void *file)
{
    return file;
}
CLEAN_AS(func_020ba294, WallpaperFile_Construct)
