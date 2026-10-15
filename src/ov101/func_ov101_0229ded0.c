/* func_ov101_0229ded0 @ 0x0229ded0, 0xa0 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int);
extern void *func_ov002_0220830c(void *arg0);
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
extern char data_ov101_0229e078;

void *func_ov101_0229ded0(void)
{
    void *self;
    char *p;
    char *end;

    self = func_ov002_02207f80(0x29dc);
    if (self != 0) {
        func_ov002_0220830c((void *) self);
        *(void **) self = (void *) &data_ov101_0229e078;

        p = (char *) self + 0xbc;
        end = (char *) self + 0xf4;
        do {
            func_020b9af4(p);
            p += 0x38;
        } while (p != end);

        func_ov094_0229b000(end);
        func_ov094_0229bc3c((char *) self + 0xb54);
        func_ov094_0229a2ec((char *) self + 0xb7c);
        func_ov002_02207e40((char *) self + 0x21b4);
        func_ov002_02209e44((char *) self + 0x2284);
        func_ov002_02209ccc((char *) self + 0x229c);
        func_ov002_02209b14((char *) self + 0x2300);
        func_ov002_0220ba24((char *) self + 0x26f4);
        func_ov002_0220b008((char *) self + 0x2810);
    }
    return self;
}
