/* heap_15: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020ea550 @ 0x020ea550, 0x34 bytes, ARM
 * func_020ea50c @ 0x020ea50c, 0x44 bytes, ARM
 */

typedef void (*OSIntrCallback)(void *, void *);

extern OSIntrCallback OS_SetSwitchThreadCallback(OSIntrCallback callback);
extern OSIntrCallback data_021fbe88;
extern void func_020ea5c4(void *argument0, void *argument1);
extern void *OS_DisableInterrupts(void);
extern void *OS_RestoreInterrupts(void *arg);
extern void *func_020ea298(void *region, void *size);
extern int data_021fbe8c;
extern int data_021fbe94;
extern char data_021fbe78;

void *func_020ea550(void)
{
    void *saved = OS_DisableInterrupts();
    data_021fbe88 = OS_SetSwitchThreadCallback((void (*)(void *, void *)) func_020ea5c4);
    return OS_RestoreInterrupts(saved);
}

int func_020ea50c(void *region, void *size)
{
    int res = (int) func_020ea298(region, size);
    if (res) {
        data_021fbe8c = res;
        data_021fbe94 = res;
    }
    data_021fbe78 = 1;
    return res;
}
