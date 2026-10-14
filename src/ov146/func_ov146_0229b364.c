/* func_ov146_0229b364 @ 0x0229b364, 0x84 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int size);
extern void func_ov002_0220830c(void);
extern void func_ov002_02209ccc(void *obj);
extern void __cxa_vec_ctor(void *obj, int a, int b, void (*f1)(void), void (*f2)(void));
extern void func_020b9cfc(void *obj);
extern void func_ov002_0220b10c(void *obj);
extern void func_ov002_0220a5fc(void *obj);
extern void func_02070be8(void);
extern void func_02070c08(void);
extern char data_ov146_0229b680;

void *func_ov146_0229b364(void)
{
    void *p = func_ov002_02207f80(0x1ffc);
    if (p != 0) {
        func_ov002_0220830c();
        *(void **) p = &data_ov146_0229b680;
        func_ov002_02209ccc((char *) p + 0x15cc);
        __cxa_vec_ctor((char *) p + 0x1630, 0x14, 0x6c, func_02070c08, func_02070be8);
        {
            char *ptr = (char *) p + 0x1ea0;
            char *end = (char *) p + 0x1ee8;
            do {
                func_020b9cfc(ptr);
                ptr += 0x24;
            } while (ptr != end);
            func_ov002_0220b10c(end);
        }
        func_ov002_0220a5fc((char *) p + 0x1fb4);
    }
    return p;
}
