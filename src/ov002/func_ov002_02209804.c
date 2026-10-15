/* func_ov002_02209804 @ 0x02209804, 0x48 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209324(void *self);
extern int func_ov002_02209318(void *self);
extern int func_ov002_0220984c(void *self, int x, int y);

void func_ov002_02209804(void *self, int x, int y)
{
    int w;
    int h;

    w = func_ov002_02209324(self);
    h = func_ov002_02209318(self);
    if (x < 0) {
        x = 0;
    }
    if (y < 0xa) {
        y = 0xa;
    }
    if (x + w > 0xff) {
        x = 0xff - w;
    }
    if (y + h > 0xb6) {
        y = 0xb6 - h;
    }
    func_ov002_0220984c(self, x, y);
}
