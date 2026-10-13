/* func_ov108_0229dec4 @ 0x0229dec4, 0xbc bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void func_ov002_0220830c(void);
extern void func_02066694(void *p);
extern void func_020b9af4(void *p);
extern void func_ov094_0229b000(void *p);
extern void func_ov094_0229bc3c(void *p);
extern void func_ov094_0229a2ec(void *p);
extern void func_ov002_02207e40(void *p);
extern void func_ov002_02209e44(void *p);
extern void func_ov002_02209ccc(void *p);
extern void func_ov002_02209b14(void *p);
extern void func_ov002_0220ba24(void *p);
extern void func_ov002_0220b008(void *p);
extern unsigned char data_ov108_0229e098[];

void *func_ov108_0229dec4(void)
{
    char *p;
    char *q;
    char *end;

    p = (char *) func_ov002_02207f80(0x2bd8);
    if (p != 0) {
        func_ov002_0220830c();
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
