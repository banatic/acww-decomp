/* func_ov094_0229a2ec @ 0x0229a2ec, 0x3c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9af4(void *);
extern void func_02138d6c(void *ptr, int a, int b, void (*f1)(void), void (*f2)(void));
extern void func_02070be8(void);
extern void func_02070c08(void);

void *func_ov094_0229a2ec(void *base)
{
    char *p = (char *) base + 0x38;
    char *end = (char *) base + 0xe0;
    do {
        func_020b9af4(p);
        p += 0x38;
    } while (p != end);
    func_02138d6c(end, 2, 0x6c, func_02070c08, func_02070be8);
    return base;
}
