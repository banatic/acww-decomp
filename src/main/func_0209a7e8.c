/* func_0209a7e8 @ 0x0209a7e8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm void func_02138c48(void *, int, int, void *);
extern void func_02003750(void *);
extern void func_0209bd7c(void *);
extern void func_0209526c(void);

void *func_0209a7e8(void *arg)
{
    func_02138c48((char *) arg + 0x1c, 5, 0x1e, (void *) func_0209526c);
    func_02003750((char *) arg + 0xc);
    func_0209bd7c(arg);
    return arg;
}
