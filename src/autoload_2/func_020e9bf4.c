/* func_020e9bf4 @ 0x020e9bf4, 0x28 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void OS_Terminate(void);

void func_020e9bf4(int p0, int p1)
{
    if (p1 == 0) {
        return;
    }
    OS_Terminate();
}
