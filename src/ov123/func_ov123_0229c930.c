/* func_ov123_0229c930 @ 0x0229c930, 0x74 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int size);
extern void func_ov002_0220830c(void);
extern void __cxa_vec_ctor(void *ptr, int a, int b, void (*f1)(void), void (*f2)(void));
extern void func_020b9af4(void *ptr);
extern void func_ov002_02209ccc(void *ptr);
extern void func_ov002_0220b008(void *ptr);
extern void func_02070be8(void);
extern void func_02070c08(void);

extern unsigned char data_ov123_0229d024[];

void *func_ov123_0229c930(void)
{
    void *p;
    char *ptr;
    char *end;

    p = func_ov002_02207f80(0x51fc);
    if (p != 0) {
        func_ov002_0220830c();
        ((void **) p)[0] = (void *) data_ov123_0229d024;
        __cxa_vec_ctor((char *) p + 0xb8, 1, 0x6c, func_02070c08, func_02070be8);
        ptr = (char *) p + 0x124;
        end = (char *) p + 0x1cc;
        do {
            func_020b9af4(ptr);
            ptr += 0x38;
        } while (ptr != end);
        func_ov002_02209ccc(end);
        func_ov002_0220b008((char *) p + 0x5030);
    }
    return p;
}
