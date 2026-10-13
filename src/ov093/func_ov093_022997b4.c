/* func_ov093_022997b4 @ 0x022997b4, 0x44 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *p, int a, int b, void (*cb)(void));
extern void func_ov093_02298f4c(void *p);
extern void func_ov093_02298fd4(void *p);
extern void func_02070be8(void);

void *func_ov093_022997b4(void *base)
{
    func_02138c48((char *) base + 0x19e0, 0x1a, 0x6c, func_02070be8);
    func_ov093_02298f4c((char *) base + 0x1828);
    func_ov093_02298fd4((char *) base + 0x0820);
    func_ov093_02298fd4((char *) base + 0x18);
    return base;
}
