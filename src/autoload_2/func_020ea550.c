/* func_020ea550 @ 0x020ea550, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef void (*OSIntrCallback)(void *, void *);
extern OSIntrCallback OS_SetSwitchThreadCallback(OSIntrCallback callback);
extern OSIntrCallback data_021fbe88;
extern void func_020ea5c4(void *argument0, void *argument1);
extern void *OS_DisableInterrupts(void);
extern void *OS_RestoreInterrupts(void *arg);

void *func_020ea550(void)
{
    void *saved = OS_DisableInterrupts();
    data_021fbe88 = OS_SetSwitchThreadCallback((void (*)(void *, void *)) func_020ea5c4);
    return OS_RestoreInterrupts(saved);
}
