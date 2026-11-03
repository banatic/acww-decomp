/* carried_letters_13: 3 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229e0e4 @ 0x0229e0e4, 0xc4 bytes, Thumb
 * func_ov103_0229e0c4 @ 0x0229e0c4, 0x20 bytes, Thumb
 * func_ov103_0229e0a8 @ 0x0229e0a8, 0x1a bytes, Thumb
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *p);
extern void *func_020b9af4(void *p);
extern void *func_ov094_0229b000(void *p);
extern void func_ov094_0229bc3c(void *p);
extern void *func_ov094_0229a2ec(void *p);
extern void *func_ov002_02207e40(void *p);
extern void func_ov002_02209e44(void *p);
extern void *func_ov002_02209ccc(void *p);
extern void *func_ov002_02209b14(void *p);
extern void *func_ov002_0220ba24(void *p);
extern void *func_0206e388(void *p);
extern void *func_ov002_0220b47c(void *p);
extern void func_02066694(void *p);
extern char data_ov103_0229e2e0[];
extern void func_ov103_0229d99c(int);
extern void func_ov002_02208090(int, int);
extern unsigned char *func_ov002_022080a0(int, unsigned char value);
extern int func_020ee45c(void *arg);
extern void func_ov092_0229929c(int arg);
extern void func_ov103_0229d960(void *arg);

void *func_ov103_0229e0e4(void)
{
    char *self;
    char *p;
    char *q;

    self = (char *) func_ov002_02207f80(0x2dac);
    if (self != 0) {
        func_ov002_0220830c(self);
        *(void **) self = (void *) data_ov103_0229e2e0;
        p = self + 0x94;
        q = self + 0xcc;
        do {
            func_020b9af4(p);
            p += 0x38;
        } while (p != q);
        func_ov094_0229b000(q);
        func_ov094_0229bc3c(self + 0xb2c);
        func_ov094_0229a2ec(self + 0xb54);
        func_ov002_02207e40(self + 0x218c);
        func_ov002_02209e44(self + 0x225c);
        func_ov002_02209ccc(self + 0x2274);
        func_ov002_02209b14(self + 0x22d8);
        func_ov002_0220ba24(self + 0x26cc);
        func_0206e388(self + 0x27e8);
        func_ov002_0220b47c(self + 0x2b10);
        func_02066694(self + 0x2ba0);
        func_02066694(self + 0x2ca0);
    }
    return self;
}

int func_ov103_0229e0c4(int arg)
{
    func_ov103_0229d99c(arg);
    func_ov002_02208090(arg, 0);
    func_ov002_022080a0(arg, 0);
    return 1;
}

int func_ov103_0229e0a8(void *arg)
{
    int ret;

    ret = func_020ee45c(arg);
    func_ov092_0229929c(ret);
    func_ov103_0229d960(arg);
    return 1;
}
