/* func_020eed48 @ 0x020eed48, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(void);
extern void func_0210b7e0(void *self);

void func_020eed48(void *self)
{
    if (self == 0) {
        OS_Terminate();
    }
    func_0210b7e0(self);
}
