/* func_020837d0 @ 0x020837d0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d51c(int);
extern void func_02083cb4(void *receiver);

int func_020837d0(int arg)
{
    func_0205d51c(arg + 1);
    func_02083cb4((void *) arg);
    return arg;
}
