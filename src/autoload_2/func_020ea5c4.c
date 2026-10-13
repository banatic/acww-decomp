/* func_020ea5c4 @ 0x020ea5c4, 0x70 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void OS_SetThreadParameter(void *thread, unsigned int param);
extern unsigned int OS_GetThreadParameter(void *thread);
extern unsigned int data_021fbe94;
extern void (*data_021fbe88)(void *, void *);

void func_020ea5c4(void *a, void *b)
{
    OS_SetThreadParameter(a, data_021fbe94);
    data_021fbe94 = OS_GetThreadParameter(b);
    OS_SetThreadParameter(b, 0);
    if (data_021fbe88) {
        data_021fbe88(a, b);
    }
}
