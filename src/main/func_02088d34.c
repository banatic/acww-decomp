/* func_02088d34 @ 0x02088d34, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088d9c(void *self);
extern int func_02088dd8(void *self);
extern int func_02088d94(void *self);
extern int func_02088db8(void *self);

int func_02088d34(void *self, int b, int c, int d, int e)
{
    int t;
    int h;
    int r;

    t = func_02088d9c(self) - d;
    if (t > b) {
        return 0;
    }

    r = func_02088dd8(self);
    if ((d << 1) + r + t < b) {
        return 0;
    }

    h = func_02088d94(self) - e;
    if (h > c) {
        return 0;
    }

    r = func_02088db8(self);
    if ((e << 1) + r + h < c) {
        return 0;
    }

    return 1;
}