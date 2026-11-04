/* heap_12: 6 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020ea080 @ 0x020ea080, 0x4 bytes, ARM
 * func_020ea07c @ 0x020ea07c, 0x4 bytes, ARM
 * func_020ea074 @ 0x020ea074, 0x8 bytes, ARM
 * func_020ea064 @ 0x020ea064, 0x10 bytes, ARM
 * func_020ea054 @ 0x020ea054, 0x10 bytes, ARM
 * func_020ea044 @ 0x020ea044, 0x10 bytes, ARM
 */

extern void OS_LockMutex(void *mutex);
extern void OS_UnlockMutex(void *mutex);
extern int OS_TryLockMutex(void *mutex);

void func_020ea080(void) {}

void func_020ea07c(void) {}

int func_020ea074(void)
{
    return 1;
}

void func_020ea064(void *obj)
{
    OS_LockMutex((char *) obj + 0x18);
}

void func_020ea054(void *mutex)
{
    OS_UnlockMutex((char *) mutex + 0x18);
}

void func_020ea044(void *mutex)
{
    OS_TryLockMutex((char *) mutex + 0x18);
}
