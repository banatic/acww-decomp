/* func_020e9a08 @ 0x020e9a08, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int OS_DisableInterrupts(void);
extern unsigned int OS_RestoreInterrupts(int);
extern int data_021fbe94;

int func_020e9a08(int param)
{
    int result = OS_DisableInterrupts();
    int old = data_021fbe94;
    data_021fbe94 = param;
    OS_RestoreInterrupts(result);
    return old;
}
