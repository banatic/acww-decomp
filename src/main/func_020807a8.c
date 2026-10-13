/* func_020807a8 @ 0x020807a8, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020807dc(int arg);
extern void func_020807c0(int arg1, int arg2);

void func_020807a8(int arg)
{
    func_020807c0(arg, func_020807dc(arg));
}
