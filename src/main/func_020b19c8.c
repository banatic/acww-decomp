/* func_020b19c8 @ 0x020b19c8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *arg, int a, int b, void (*callback)(void));
extern void func_020b1a54(void);
void *func_020b19c8(void *arg);

void *func_020b19c8(void *arg)
{
    func_02138c48(arg, 0x10, 0x4a, func_020b1a54);
    return arg;
}
