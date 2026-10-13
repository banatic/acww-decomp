/* func_02082bc0 @ 0x02082bc0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02082bec(void);
extern void func_02082bfc(void);
extern void func_02138c48(void *, int, int, void (*)(void));

void *func_02082bc0(void *arg)
{
    func_02138c48((char *) arg + 0x40, 4, 8, func_02082bec);
    func_02138c48(arg, 8, 8, func_02082bfc);
    return arg;
}
