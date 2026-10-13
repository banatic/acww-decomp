/* func_02088cf4 @ 0x02088cf4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088d34(void *p, int a, int b, int c, int d);

struct Elem {
    int x;
    int y;
};

int func_02088cf4(struct Elem *p, int count, int a, int b, int c, int d)
{
    int i;
    for (i = 0; i < count; i++) {
        if (func_02088d34(p, a, b, c, d)) {
            return i;
        }
        p++;
    }
    return -1;
}
