/* func_020b82ec @ 0x020b82ec, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b8020(void);
extern void func_020b8038(void);
extern void func_02138d6c(void *arg, int a, int b, void (*cb1)(void), void (*cb2)(void));

void *func_020b82ec(void *arg)
{
    func_02138d6c(arg, 10, 0x44, func_020b8038, func_020b8020);
    return arg;
}
