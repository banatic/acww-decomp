/* func_020833d4 @ 0x020833d4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205db6c(int);
extern void func_02083cb4(void *receiver);

int func_020833d4(int arg)
{
    func_0205db6c(arg + 1);
    func_02083cb4((void *) arg);
    return arg;
}
