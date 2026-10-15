/* func_ov107_0229e1cc @ 0x0229e1cc, 0xb4 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
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
