/* func_ov002_022098ec @ 0x022098ec, 0x1c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209318(void *self);
extern void func_ov002_02209804(void *self, int x, int y);

void func_ov002_022098ec(void *self, int x, int y)
{
    int ny = y - func_ov002_02209318(self);

    func_ov002_02209804(self, x, ny);
}
