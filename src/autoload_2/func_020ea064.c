/* func_020ea064 @ 0x020ea064, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_LockMutex(void *mutex);

void func_020ea064(void *obj)
{
    OS_LockMutex((char *) obj + 0x18);
}
