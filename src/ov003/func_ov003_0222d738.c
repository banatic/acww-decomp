/* func_ov003_0222d738 @ 0x0222d738, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov003_02260540;
extern char data_ov003_02260558[];
extern void func_0204f818(int *x, int *y, void *src);

int func_ov003_0222d738(void *self)
{
    int ax, ay;
    int bx, by;
    if (data_ov003_02260540 != 0) {
        func_0204f818(&bx, &by, self);
        func_0204f818(&ax, &ay, data_ov003_02260558);
        if (ax == bx && ay == by) {
            return 1;
        }
    }
    return 0;
}
