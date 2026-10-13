/* func_020497b0 @ 0x020497b0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204a198(void *arg1, unsigned short arg2, int arg3, int arg4);
extern void func_02049818(void *arg1, void *arg2, unsigned short *arg3, void *arg4, int arg5, int arg6);

void func_020497b0(void *a, void *b, unsigned short *c, unsigned int *d, int e, int f)
{
    if (f < 64) {
        func_0204a198(b, *c, e, f);
    } else {
        unsigned int local[2];
        local[0] = d[0];
        local[1] = d[1];
        func_02049818(a, b, c, local, e, f);
    }
}
