/* func_ov116_0229e7e0 @ 0x0229e7e0, 0x58 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void func_ov002_0220830c(void);
extern void func_ov002_02209ccc(void *p);
extern void func_ov114_0229da18(void *p);
extern void func_02138d6c(void *p, int a, int b, void (*cb1)(void), void (*cb2)(void));
extern void func_02070be8(void);
extern void func_02070c08(void);
extern char data_ov116_0229e8b8[];

void *func_ov116_0229e7e0(void)
{
    void *self = func_ov002_02207f80(0x1430);
    if (self) {
        func_ov002_0220830c();
        *(void **) self = &data_ov116_0229e8b8;
        func_ov002_02209ccc((char *) self + 0x94);
        func_ov114_0229da18((char *) self + 0xf8);
        func_02138d6c((char *) self + 0x13b8, 1, 0x6c, func_02070c08, func_02070be8);
    }
    return self;
}
