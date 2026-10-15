/* func_020115d0 @ 0x020115d0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02004bbc(int);
extern void *func_02004f34(void *);

void func_020115d0(void)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (func_02004bbc(0xca0))) != 0) {
        func_02004f34(condition_value0);
    }
}
