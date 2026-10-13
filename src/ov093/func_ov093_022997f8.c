/* func_ov093_022997f8 @ 0x022997f8, 0x68 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov093_02298fd8(void *);
extern void func_ov093_02298f64(void *);
extern void func_020b9cfc(void *);
extern void func_02070be8(void);
extern void func_02070c08(void);
extern void func_02138d6c(void *, int, int, void (*)(void), void (*)(void));

void *func_ov093_022997f8(void *self)
{
    func_ov093_02298fd8((char *) self + 0x18);
    func_ov093_02298fd8((char *) self + 0x820);
    func_ov093_02298f64((char *) self + 0x1828);
    func_02138d6c((char *) self + 0x19e0, 0x1a, 0x6c, func_02070c08, func_02070be8);
    {
        char *p = (char *) self + 0x24d8;
        char *end = (char *) self + 0x2520;
        do {
            func_020b9cfc(p);
            p += 0x24;
        } while (p != end);
    }
    return self;
}
