/* func_ov002_0220a58c @ 0x0220a58c, 0x36 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a530(void *self);
extern int func_ov002_0220a51c(void *self);

int func_ov002_0220a58c(void *self, int x, int y)
{
    int dx;
    int dy;

    dx = x - func_ov002_0220a530(self);
    dy = y - func_ov002_0220a51c(self);
    if (dx < 0 || dx > 0x10) {
        return 0;
    }
    if (dy < 0 || dy > 0x10) {
        return 0;
    }
    return 1;
}
