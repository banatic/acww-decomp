/* func_ov004_02225b14 @ 0x02225b14, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8858(void *p);
extern int func_020a186c(void);
extern void func_ov004_02225ba4(void *self, int k);

int func_ov004_02225b14(void *self)
{
    unsigned int a, b;

    a = ((unsigned int) *(int *) ((char *) self + 0x190) << 4) >> 16;
    b = ((unsigned int) *(int *) ((char *) self + 0x18c) << 4) >> 16;
    if (a == b - 1 && func_020e8858((char *) self + 0x658) == 0 && func_020a186c() != 0) {
        func_ov004_02225ba4(self, 1);
    }
    return 1;
}
