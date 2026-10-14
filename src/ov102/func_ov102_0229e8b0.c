/* func_ov102_0229e8b0 @ 0x0229e8b0, 0xac bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int size);
extern void func_ov002_0220830c(void);
extern void func_020b9af4(void *p);
extern void func_ov094_0229b000(void *p);
extern void func_ov094_0229bc3c(void *p);
extern void func_ov094_0229a2ec(void *p);
extern void func_ov002_02207e40(void *p);
extern void func_ov002_02209e44(void *p);
extern void func_ov002_02209ccc(void *p);
extern void func_ov002_0220ba24(void *p);
extern void __cxa_vec_ctor(void *p, int a, int b, void (*c)(void), void (*d)(void));
extern void func_02070be8(void);
extern void func_02070c08(void);
extern unsigned char data_ov102_0229ea60;

void *func_ov102_0229e8b0(void)
{
    char *p = (char *) func_ov002_02207f80(0x25ac);

    if (p != 0) {
        char *s;
        char *end;

        func_ov002_0220830c();
        *((unsigned int *) p) = (unsigned int) &data_ov102_0229ea60;

        s = p + 0x94;
        end = p + 0xcc;
        do {
            func_020b9af4(s);
            s += 0x38;
        } while (s != end);

        func_ov094_0229b000(end);

        func_ov094_0229bc3c(p + 0xb2c);
        func_ov094_0229a2ec(p + 0xb54);
        func_ov002_02207e40(p + 0x218c);
        func_ov002_02209e44(p + 0x225c);
        func_ov002_02209ccc(p + 0x2274);
        func_ov002_0220ba24(p + 0x22d8);

        __cxa_vec_ctor(p + 0x23f4, 2, 0x6c, func_02070c08, func_02070be8);
    }

    return p;
}
