/* func_ov100_0229eaec @ 0x0229eaec, 0xb8 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void func_ov002_0220830c(void);
extern void func_020b9af4(void *p);
extern void func_ov094_0229b000(void *p);
extern void func_ov094_0229bc3c(void *p);
extern void func_ov094_0229a2ec(void *p);
extern void func_ov002_02207e40(void *p);
extern void func_ov002_02209e44(void *p);
extern void func_ov002_02209ccc(void *p);
extern void func_ov002_02209b14(void *p);
extern void func_ov002_0220ba24(void *p);
extern void __cxa_vec_ctor(void *p, int a, int b, void (*cb1)(void), void (*cb2)(void));
extern void func_02070c08(void);
extern void func_02070be8(void);
extern char data_ov100_0229ecb8;

void *func_ov100_0229eaec(void)
{
    void *p;
    char *q;
    char *end;

    p = func_ov002_02207f80(0x292c);
    if (p != 0) {
        func_ov002_0220830c();
        *(void **) p = (void *) &data_ov100_0229ecb8;

        q = (char *) p + 0x94;
        end = (char *) p + 0xcc;
        do {
            func_020b9af4(q);
            q += 0x38;
        } while (q != end);

        func_ov094_0229b000(end);
        func_ov094_0229bc3c((char *) p + 0xb2c);
        func_ov094_0229a2ec((char *) p + 0xb54);
        func_ov002_02207e40((char *) p + 0x218c);
        func_ov002_02209e44((char *) p + 0x225c);
        func_ov002_02209ccc((char *) p + 0x2274);
        func_ov002_02209b14((char *) p + 0x22d8);
        func_ov002_0220ba24((char *) p + 0x26cc);
        __cxa_vec_ctor((char *) p + 0x27e8, 2, 0x6c, func_02070c08, func_02070be8);
    }

    return p;
}
