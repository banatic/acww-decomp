/* func_ov142_0229c208 @ 0x0229c208, 0x84 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void func_ov002_0220830c(void);
extern void func_ov002_02209ccc(void *p);
extern void func_ov002_0220a5fc(void *p);
extern void func_ov002_0220b008(void *p);
extern void __arm func_02138d6c(void *p, int a, int b, void (*f1)(void), void (*f2)(void));
extern void func_020b9cfc(void *p);
extern void func_02070be8(void);
extern void func_02070c08(void);
extern char data_ov142_0229c3e8;

void *func_ov142_0229c208(void)
{
    void *block = func_ov002_02207f80(0x30e0);
    if (block) {
        func_ov002_0220830c();
        *(void **) block = &data_ov142_0229c3e8;
        func_ov002_02209ccc((char *) block + 0xe8);
        func_ov002_0220a5fc((char *) block + 0x14c);
        func_ov002_0220b008((char *) block + 0x194);
        func_02138d6c((char *) block + 0x360, 0xe, 0x6c, func_02070c08, func_02070be8);
        {
            char *p = (char *) block + 0x948;
            char *end = (char *) block + 0x9d8;
            do {
                func_020b9cfc(p);
                p += 0x24;
            } while (p != end);
        }
    }
    return block;
}
