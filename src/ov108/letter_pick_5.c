/* letter_pick_5: 4 functions, module ov108
 * mwccarm 1.2/base -O4,s
 * func_ov108_0229dec4 @ 0x0229dec4, 0xbc bytes, Thumb
 * func_ov108_0229dea4 @ 0x0229dea4, 0x20 bytes, Thumb
 * func_ov108_0229de88 @ 0x0229de88, 0x1a bytes, Thumb
 * func_ov108_0229dde0 @ 0x0229dde0, 0xa8 bytes, Thumb
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *argument0);
extern void func_02066694(void *p);
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
extern unsigned char data_ov108_0229e098[];
extern void func_ov108_0229d960(void *);
extern void func_ov002_02208090(void *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_020ee45c(int);
extern void func_ov092_0229929c(int);
extern void func_ov108_0229d920(int);
extern void func_ov002_0220919c(void *p);
extern int func_ov108_0229c2dc(void *self, int mode);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *p);
extern void func_ov108_0229c998(void *self);
extern void func_ov002_0220ad18(void *p, void *q);
extern void func_ov094_0229a850(void *p, int a, int b);
extern void func_ov094_0229b738(void *p, int a, int b);
extern void func_ov094_02299d84(void *receiver, int value);

void *func_ov108_0229dec4(void)
{
    char *p;
    char *q;
    char *end;

    p = (char *) func_ov002_02207f80(0x2bd8);
    if (p != 0) {
        func_ov002_0220830c(p);
        *(void **) p = (void *) data_ov108_0229e098;
        func_02066694(p + 0xac);
        func_02066694(p + 0x1ac);

        q = p + 0x2b8;
        end = p + 0x2f0;
        do {
            func_020b9af4(q);
            q += 0x38;
        } while (q != end);

        func_ov094_0229b000(end);
        func_ov094_0229bc3c(p + 0xd50);
        func_ov094_0229a2ec(p + 0xd78);
        func_ov002_02207e40(p + 0x23b0);
        func_ov002_02209e44(p + 0x2480);
        func_ov002_02209ccc(p + 0x2498);
        func_ov002_02209b14(p + 0x24fc);
        func_ov002_0220ba24(p + 0x28f0);
        func_ov002_0220b008(p + 0x2a0c);
    }
    return p;
}

int func_ov108_0229dea4(void *p)
{
    func_ov108_0229d960(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0((void *) (p), 0);
    return 1;
}

int func_ov108_0229de88(int arg)
{
    func_ov092_0229929c(func_020ee45c(arg));
    func_ov108_0229d920(arg);
    return 1;
}

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
