/* func_ov120_0229c45c @ 0x0229c45c, 0xa4 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void func_ov002_0220830c(void);
extern void func_020b9cfc(void *p);
extern void __cxa_vec_ctor(void *p, int a, int b, void (*c)(void), void (*d)(void));
extern void func_ov002_0220a5fc(void *p);
extern void func_ov002_02209ccc(void *p);
extern void func_02070be8(void);
extern void func_02070c08(void);
extern void func_ov120_0229a420(void);
extern void func_ov120_0229a424(void);
extern char data_ov120_0229c650;

void *func_ov120_0229c45c(void)
{
    void *obj = func_ov002_02207f80(0x2770);
    if (obj != 0) {
        char *p;
        char *end;
        int val;

        func_ov002_0220830c();
        ((void **) obj)[0] = &data_ov120_0229c650;
        p = (char *) obj + 0xb0;
        end = (char *) obj + 0xf8;
        do {
            func_020b9cfc(p);
            p += 0x24;
        } while (p != end);

        __cxa_vec_ctor(end, 0xd, 0x6c, &func_02070c08, &func_02070be8);
        func_ov002_0220a5fc((char *) obj + 0x674);
        func_ov002_02209ccc((char *) obj + 0x6bc);
        val = 3;
        __cxa_vec_ctor((char *) obj + 0x273a, val, val, &func_ov120_0229a424, &func_ov120_0229a420);
        __cxa_vec_ctor((char *) obj + 0x2743, 0xe, 3, &func_ov120_0229a424, &func_ov120_0229a420);
    }
    return obj;
}
