/* func_ov108_0229dde0 @ 0x0229dde0, 0xa8 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220919c(void *p);
extern int func_ov108_0229c2dc(void *self, int mode);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *p);
extern void func_ov108_0229c998(void *self);
extern void func_ov002_0220ad18(void *p, void *q);
extern void func_ov094_0229a850(void *p, int a, int b);
extern void func_ov094_0229b738(void *p, int a, int b);
extern void func_ov094_02299d84(void *receiver, int value);

int func_ov108_0229dde0(char *self)
{
    void (*fn)(void *);
    void *p98;
    int v;

    func_ov002_0220919c(self + 0x24fc);

    if (func_ov108_0229c2dc(self, 1) == 0) {
        return 1;
    }

    {
        void *thisPtr = self + 0x23b0;
        void **vtable = *(void ***) thisPtr;
        fn = (void (*)(void *)) vtable[2];
        fn(thisPtr);
    }

    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(self + 0x2498);
    }

    func_ov108_0229c998(self);

    if (func_ov108_0229c2dc(self, 2) != 0) {
        p98 = *(void **) (self + 0x98);
        func_ov002_0220ad18(self + 0x2a0c, p98);
        v = *(int *) (self + 0x98) - 0x10;
        func_ov094_0229a850(self + 0x2f0, 0, v);
        func_ov094_0229b738(self + 0xd50, 0, v);
        func_ov094_02299d84(self + 0xd78, v);
    }

    return 1;
}
