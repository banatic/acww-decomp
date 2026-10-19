/* Overlay 094's sheet of item icons (pockets_icons.h). */
#include "pockets_icons.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/c_library.h"
#include "main/rom_file.h"
#include "main/screen_map.h"

static_assert(offsetof(PocketsIcons, file) == 0x804 && sizeof(PocketsIcons) == 0x808, "icons");

/* The class's vtable. */
extern const u32 data_ov094_0229bf80[];
/* The palette of each item icon. */
extern const u8 data_ov094_0229bc8c[];
/* "menu/icon/pre%d.bch" and "menu/icon/icon%02d.bch". */
extern const char data_ov094_0229c0c0[];
extern const char data_ov094_0229c0d4[];

#define POCKETS_ICONS_PATH_SIZE 0x28
#define POCKETS_ICONS_CHARS_SIZE 0x20 /* of one icon */

static u8 *icon_chars(PocketsIcons *icons, int cell)
{
    return icons->chars + ScreenMap_CellTile(cell) * POCKETS_ICONS_CHARS_SIZE;
}

/* func_ov094_0229b03c: the palette of item icon `icon`. */
u8 PocketsIcons_Palette(PocketsIcons *icons, int icon)
{
    (void) icons;
    return data_ov094_0229bc8c[icon];
}
CLEAN_AS(func_ov094_0229b03c, PocketsIcons_Palette)

/* func_ov094_0229b048: frame `frame` of the pick-up's file of variant `variant`, which is read
 * every time; the next item icon reads its file again.
 * QUIRK: the matching source names `variant` unused, but the ROM's code leaves it where the
 * format's number is read: the file is "menu/icon/pre<variant>.bch". */
u8 *PocketsIcons_LoadPickUpFrame(PocketsIcons *icons, unsigned int frame, unsigned int variant)
{
    char path[POCKETS_ICONS_PATH_SIZE];
    u8 *chars;

    CLib_SPrintf(path, data_ov094_0229c0c0, variant);
    RomFile_Read(path, icons->chars, POCKETS_ICONS_FILE_SIZE);
    chars = icon_chars(icons, (int) frame);
    icons->file = POCKETS_ICONS_NO_FILE;
    return chars;
}
CLEAN_AS(func_ov094_0229b048, PocketsIcons_LoadPickUpFrame)

/* func_ov094_0229b088: the characters of item icon `icon`, its file ("menu/icon/icon<icon /
 * 16>.bch") read first unless it is the one held. */
u8 *PocketsIcons_Chars(PocketsIcons *icons, int icon)
{
    char path[POCKETS_ICONS_PATH_SIZE];
    int file = icon >> 4;

    if (file != icons->file) {
        icons->file = (u8) file;
        CLib_SPrintf(path, data_ov094_0229c0d4, file);
        RomFile_Read(path, icons->chars, POCKETS_ICONS_FILE_SIZE);
    }
    return icon_chars(icons, icon & (POCKETS_ICONS_PER_FILE - 1));
}
CLEAN_AS(func_ov094_0229b088, PocketsIcons_Chars)

/* func_ov094_0229b0d4: no file held, so the next icon reads its file. */
void PocketsIcons_Forget(PocketsIcons *icons)
{
    icons->file = POCKETS_ICONS_NO_FILE;
}
CLEAN_AS(func_ov094_0229b0d4, PocketsIcons_Forget)

/* func_ov094_0229b0e0 (vtable entry 3): the destructor that frees the sheet. */
PocketsIcons *PocketsIcons_DestructDelete(PocketsIcons *icons)
{
    icons->vtable = (u32) (uintptr_t) data_ov094_0229bf80;
    Heap_OperatorDeleteB(icons);
    return icons;
}
CLEAN_AS(func_ov094_0229b0e0, PocketsIcons_DestructDelete)

/* func_ov094_0229b0f8 (vtable entry 2): the destructor. */
void PocketsIcons_Destruct(PocketsIcons *icons)
{
    icons->vtable = (u32) (uintptr_t) data_ov094_0229bf80;
}
CLEAN_AS(func_ov094_0229b0f8, PocketsIcons_Destruct)

/* func_ov094_0229b104: the constructor. */
void PocketsIcons_Construct(PocketsIcons *icons)
{
    icons->vtable = (u32) (uintptr_t) data_ov094_0229bf80;
}
CLEAN_AS(func_ov094_0229b104, PocketsIcons_Construct)
