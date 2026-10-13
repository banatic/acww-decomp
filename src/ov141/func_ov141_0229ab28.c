/* func_ov141_0229ab28 @ 0x0229ab28, 0x74 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov141_02299f7c(void *self, int a);
extern void func_0206fc4c(int a);
extern unsigned int *func_0206f7bc(void);
extern int func_0206f7b0(void);
extern void func_0206f7c8(void);
extern void MI_CpuCopy8(void *src, void *dst, unsigned int len);
extern void func_020ee470(void *self);

int func_ov141_0229ab28(char *self)
{
    unsigned int *p;
    int flag2;

    if (func_ov141_02299f7c(self, 2) != 0) {
        func_0206fc4c(0);
    } else {
        int idx;
        func_0206fc4c(1);

        p = func_0206f7bc();
        if (p != 0) {
            idx = *(int *) (self + 0x1270);
            MI_CpuCopy8(self + 0xc8c + idx * 0xe0, p, 0xe0);
        }

        flag2 = func_0206f7b0();
        if (flag2 != 0) {
            idx = *(int *) (self + 0x1270);
            MI_CpuCopy8(self + 0x11cc + idx * 0x1a, (void *) flag2, 0x1a);
        }
    }

    func_0206f7c8();
    func_020ee470(self);
    return 1;
}
