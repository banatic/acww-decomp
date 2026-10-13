/* func_020bc790 @ 0x020bc790, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bca80(void *ptr, int a, int b, int c);
extern void func_020bc9c4(void *ptr, int a);
extern void func_020bcab0(void *ptr);

void func_020bc790(void *arg)
{
    int field = *(int *) ((char *) arg + 0x2f30);
    if (field < 0) {
        func_020bca80(arg, 0x28, 0x96, 0x190);
    } else if (field == 0) {
        func_020bc9c4(arg, 0x14);
    }
    func_020bcab0(arg);
}
