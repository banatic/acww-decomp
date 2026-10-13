/* func_ov114_0229d9d8 @ 0x0229d9d8, 0x40 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a5e4(void *p);
extern void func_02138c48(void *p, int a, int b, void (*cb)(void));
extern void func_ov114_0229d130(void *p);
extern void func_ov094_0229b0f8(void *p);
extern void func_02070be8(void);

void *func_ov114_0229d9d8(void *arg)
{
    func_ov002_0220a5e4((char *) arg + 0x121c);
    func_02138c48((char *) arg + 0x106c, 4, 0x6c, &func_02070be8);
    func_ov114_0229d130((char *) arg + 0x808);
    func_ov094_0229b0f8(arg);
    return arg;
}
