/* The papers' backgrounds (paper.h). */
#include "paper.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/display_layers.h"

extern Heap *data_021fbe94;                                      /* the current heap */
extern int func_02064328(char *buffer, const char *format, ...); /* sprintf */
extern const char data_ov002_0220bc9c[];                         /* "menu/paper/chr/%03d.bch" */
extern const char data_ov002_0220bcb4[];                         /* "menu/paper/scr/%03d.bsc" */
extern const char data_ov002_0220bccc[];                         /* "menu/paper/plt/%03d.bpl" */

/* func_ov002_0220a448: loads paper `paper`'s characters 0x10 to 0x74 (from the file's 0x10),
 * its screen, and its palettes 12 to 14 (from the file's 12) onto `layer`, from the current
 * heap.
 * QUIRK: the palette file's name is printed with `paper` passed twice; the format uses one. */
void Paper_LoadBackground(int paper, int layer)
{
    char path[0x20];
    Heap *heap = data_021fbe94;

    func_02064328(path, data_ov002_0220bc9c, paper);
    DisplayLayer_LoadCharsFromFile(path, heap, layer, 0x10, 0x10, 0x74);
    func_02064328(path, data_ov002_0220bcb4, paper);
    DisplayLayer_LoadScreenFromFile(path, heap, layer);
    func_02064328(path, data_ov002_0220bccc, paper, paper);
    DisplayLayer_LoadPalettesFromFile(path, heap, layer, 0xc, 0xc, 0xe);
}
CLEAN_AS(func_ov002_0220a448, Paper_LoadBackground)
