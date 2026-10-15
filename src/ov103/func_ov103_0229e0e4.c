/* func_ov103_0229e0e4 @ 0x0229e0e4, 0xc4 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
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
