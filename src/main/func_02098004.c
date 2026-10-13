/* func_02098004 @ 0x02098004, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066688(void);
extern void func_02138c48(int arg, int a, int b, void (*cb)(void));

int func_02098004(int arg)
{
    func_02138c48(arg, 0xa, 0x100, func_02066688);
    return arg;
}
