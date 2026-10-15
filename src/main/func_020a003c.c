/* func_020a003c @ 0x020a003c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void OS_CreateThread(void *a, void *b, void *c, void *d, int e, int f);
extern void OS_WakeupThreadDirect(void *a);

extern void func_020a00c0(int);

void func_020a003c(void *obj, void *arg2)
{
    OS_CreateThread(obj, (void *) func_020a00c0, arg2, (char *) obj + 0x10c4, 0x1000, 30);
    OS_WakeupThreadDirect(obj);
}
