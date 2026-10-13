/* func_020ea054 @ 0x020ea054, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_UnlockMutex(void *mutex);

void func_020ea054(void *mutex)
{
    OS_UnlockMutex((char *) mutex + 0x18);
}
