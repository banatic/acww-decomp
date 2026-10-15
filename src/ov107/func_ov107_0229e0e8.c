/* func_ov107_0229e0e8 @ 0x0229e0e8, 0xa8 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220919c(void *p);
extern int func_ov107_0229c2b4(void *self, int mode);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *p);
extern void func_ov107_0229cf58(void *self);
extern void func_ov002_0220ad18(void *p, void *q);
extern void func_ov094_0229a850(void *p, int a, int b);
extern void func_ov094_0229b738(void *p, int a, int b);
extern void func_ov094_02299d84(void *receiver, int value);

int func_ov107_0229e0e8(char *self)
{
    void (*fn)(void *);
    void *p98;
    int v;

    func_ov002_0220919c(self + 0x2318);

    if (func_ov107_0229c2b4(self, 1) == 0) {
        return 1;
    }

    {
        void *thisPtr = self + 0x21cc;
        void **vtable = *(void ***) thisPtr;
        fn = (void (*)(void *)) vtable[2];
        fn(thisPtr);
    }

    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(self + 0x22b4);
    }

    func_ov107_0229cf58(self);

    if (func_ov107_0229c2b4(self, 2) != 0) {
        p98 = *(void **) (self + 0x98);
        func_ov002_0220ad18(self + 0x2828, p98);
        v = *(int *) (self + 0x98) - 0x10;
        func_ov094_0229a850(self + 0x10c, 0, v);
        func_ov094_0229b738(self + 0xb6c, 0, v);
        func_ov094_02299d84(self + 0xb94, v);
    }

    return 1;
}
