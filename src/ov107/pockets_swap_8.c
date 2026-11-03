/* pockets_swap_8: 4 functions, module ov107
 * mwccarm 1.2/base -O4,s
 * func_ov107_0229e1cc @ 0x0229e1cc, 0xb4 bytes, Thumb
 * func_ov107_0229e1ac @ 0x0229e1ac, 0x20 bytes, Thumb
 * func_ov107_0229e190 @ 0x0229e190, 0x1a bytes, Thumb
 * func_ov107_0229e0e8 @ 0x0229e0e8, 0xa8 bytes, Thumb
 */

extern void *func_ov002_02207f80(int size);
extern void *func_ov002_0220830c(void *argument0);
extern void *func_020b9af4(void *p);
extern void *func_ov094_0229b000(void *p);
extern void func_ov094_0229bc3c(void *p);
extern void *func_ov094_0229a2ec(void *p);
extern void *func_ov002_02207e40(void *p);
extern void func_ov002_02209e44(void *p);
extern void *func_ov002_02209ccc(void *p);
extern void *func_ov002_02209b14(void *p);
extern void *func_ov002_0220ba24(void *p);
extern void *func_ov002_0220b008(void *p);
extern char data_ov107_0229e3b8;
extern void func_ov107_0229dc58(void *p);
extern void func_ov002_02208090(void *p, int n);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_020ee45c(int a);
extern void func_ov092_0229929c(int a);
extern void func_ov107_0229dc18(int a);
extern void func_ov002_0220919c(void *p);
extern int func_ov107_0229c2b4(void *self, int mode);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *p);
extern void func_ov107_0229cf58(void *self);
extern void func_ov002_0220ad18(void *p, void *q);
extern void func_ov094_0229a850(void *p, int a, int b);
extern void func_ov094_0229b738(void *p, int a, int b);
extern void func_ov094_02299d84(void *receiver, int value);

void *func_ov107_0229e1cc(void)
{
    void *p;
    char *q;
    char *end;

    p = func_ov002_02207f80(0x29f4);
    if (p != 0) {
        func_ov002_0220830c(p);
        *(void **) p = &data_ov107_0229e3b8;
        *(int *) ((char *) p + 0xcc) = 0;
        *(int *) ((char *) p + 0xd0) = 0;

        q = (char *) p + 0xd4;
        end = (char *) p + 0x10c;
        do {
            func_020b9af4(q);
            q += 0x38;
        } while (q != end);

        func_ov094_0229b000(end);
        func_ov094_0229bc3c((char *) p + 0xb6c);
        func_ov094_0229a2ec((char *) p + 0xb94);
        func_ov002_02207e40((char *) p + 0x21cc);
        func_ov002_02209e44((char *) p + 0x229c);
        func_ov002_02209ccc((char *) p + 0x22b4);
        func_ov002_02209b14((char *) p + 0x2318);
        func_ov002_0220ba24((char *) p + 0x270c);
        func_ov002_0220b008((char *) p + 0x2828);
    }
    return p;
}

int func_ov107_0229e1ac(void *p)
{
    func_ov107_0229dc58(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0((void *) (p), 0);
    return 1;
}

int func_ov107_0229e190(int a)
{
    int b;
    b = func_020ee45c(a);
    func_ov092_0229929c(b);
    func_ov107_0229dc18(a);
    return 1;
}

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
