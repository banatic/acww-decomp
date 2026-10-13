/* func_ov004_02222728 @ 0x02222728, 0x90 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02222178(void *self, int a);
extern int func_0201c2a4(void *self, int a);
extern void func_02016108(void *p, int n);
extern void func_ov004_022227e8(void *self);

void func_ov004_02222728(char *self, unsigned int k, int a2)
{
    volatile int v[3];
    int t;

    v[0] = *(int *) (self + 0x5c);
    t = *(int *) (self + 0x60);
    v[1] = t;
    v[2] = *(int *) (self + 0x64);
    v[1] = t + 0x2000;
    switch (k) {
        case 3:
            *(char *) (self + 0x560) = (char) a2;
            func_ov004_02222178(self, 2);
            break;
        case 0:
            *(char *) (self + 0x560) = (char) a2;
            func_02016108(self + 0x8a0, func_0201c2a4(self, 4));
            func_ov004_02222178(self, 3);
            break;
        case 8:
            func_ov004_022227e8(self);
            func_ov004_02222178(self, 0);
            break;
        case 4:
            func_ov004_02222178(self, 0);
            break;
    }
}
