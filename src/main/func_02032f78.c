/* func_02032f78 @ 0x02032f78, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __arm func_02138c48(void *a, int b, int c, void *d);

extern void func_020330e8(void);

void *func_02032f78(void *arg)
{
    func_02138c48((char *) arg + 4, 0x10, 0x24, (void *) func_020330e8);
    return arg;
}
