/* func_020ef840 @ 0x020ef840, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(void);
extern void func_020ef874(int, int, int);

void func_020ef840(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    if (r0 == 0) {
        OS_Terminate();
    }
    func_020ef874(r5, 0, r4);
}
