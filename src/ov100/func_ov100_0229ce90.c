/* func_ov100_0229ce90 @ 0x0229ce90, 0x3c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229c2c0(void *, int);
extern void func_ov094_0229a6bc(void *, int, int);

void func_ov100_0229ce90(void *s)
{
    if (func_ov100_0229c2c0(s, 0x40) == 0) {
        unsigned char b;
        b = ((unsigned char *) s)[0x291d];
        if (b != 0 && b == 1) {
            func_ov094_0229a6bc((char *) s + 0xcc, *(int *) ((char *) s + 0x28d4), *(int *) ((char *) s + 0x28d8));
        }
    }
}
