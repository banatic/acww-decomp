/* song_pockets_6: 3 functions, module ov109
 * mwccarm 1.2/base -O4,s
 * func_ov109_0229da60 @ 0x0229da60, 0xa0 bytes, Thumb
 * func_ov109_0229da40 @ 0x0229da40, 0x20 bytes, Thumb
 * func_ov109_0229da24 @ 0x0229da24, 0x1a bytes, Thumb
 */

extern void *func_ov002_02207f80(unsigned int);
extern void *func_ov002_0220830c(void *);
extern void *func_020b9af4(void *);
extern void *func_ov094_0229b000(void *);
extern void func_ov094_0229bc3c(void *);
extern void *func_ov094_0229a2ec(void *);
extern void *func_ov002_02207e40(void *);
extern void func_ov002_02209e44(void *);
extern void *func_ov002_02209ccc(void *);
extern void *func_ov002_02209b14(void *);
extern void *func_ov002_0220ba24(void *);
extern void *func_ov002_0220b008(void *);
extern int data_ov109_0229dbd8;
extern void func_ov109_0229d514(void *arg0);
extern void func_ov002_02208090(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern int func_020ee45c(void *arg0);
extern void func_ov092_0229929c(void *);
extern void func_ov109_0229d4d8(int);

void *func_ov109_0229da60(void)
{
    void *self = func_ov002_02207f80(0x29dc);
    if (self != 0) {
        func_ov002_0220830c(self);
        *(void **) self = (void *) &data_ov109_0229dbd8;
        {
            char *p = (char *) self + 0x94;
            char *end = (char *) self + 0xcc;
            do {
                func_020b9af4(p);
                p += 0x38;
            } while (p != end);
            func_ov094_0229b000(end);
            func_ov094_0229bc3c((char *) self + 0xb2c);
            func_ov094_0229a2ec((char *) self + 0xb54);
            func_ov002_02207e40((char *) self + 0x218c);
            func_ov002_02209e44((char *) self + 0x225c);
            func_ov002_02209ccc((char *) self + 0x2274);
            func_ov002_02209b14((char *) self + 0x22d8);
            func_ov002_0220ba24((char *) self + 0x26cc);
            func_ov002_0220b008((char *) self + 0x27e8);
        }
    }
    return self;
}

int func_ov109_0229da40(void *p)
{
    func_ov109_0229d514((void *) p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0(p, 0);
    return 1;
}

int func_ov109_0229da24(int a)
{
    int r4 = a;
    func_ov092_0229929c((void *) func_020ee45c((void *) a));
    func_ov109_0229d4d8(r4);
    return 1;
}
