/* func_ov109_0229da60 @ 0x0229da60, 0xa0 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
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
