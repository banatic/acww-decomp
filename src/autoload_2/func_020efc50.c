/* func_020efc50 @ 0x020efc50, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(void);

void func_020efc50(void *p)
{
    if (p == 0) {
        OS_Terminate();
    }
    *(int *) p = 0;
    *(int *) ((char *) p + 4) = 0;
}
