/* func_020ea044 @ 0x020ea044, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int OS_TryLockMutex(void *mutex);

void func_020ea044(void *mutex)
{
    OS_TryLockMutex((char *) mutex + 0x18);
}
