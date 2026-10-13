/* func_020a0070 @ 0x020a0070, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int OS_IsThreadTerminated(void);
extern void OS_KillThread(int, int);

void func_020a0070(int r0)
{
    int r4 = r0;
    if (OS_IsThreadTerminated() == 0) {
        OS_KillThread(r4, 0);
    }
}
