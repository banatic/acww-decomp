/* func_ov004_0220d220 @ 0x0220d220, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a50(void *a, const char *name);
extern void func_020b3720(void *self, void *c);
int func_ov004_0220d220(unsigned char *self, void *a, void *b, void *c)
{
    if (a != 0) {
        *(signed char *) (self + 0x14) = func_02057a50(a, (const char *) (b));
        if (*(signed char *) (self + 0x14) != -1) {
            func_020b3720(self, c);
            *(void **) (self + 0x18) = a;
            return 1;
        }
    }
    return 0;
}
