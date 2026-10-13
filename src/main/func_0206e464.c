/* func_0206e464 @ 0x0206e464, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int OS_DisableInterrupts(void);
extern void OS_DisableIrqMask(int);
extern void OS_ResetRequestIrqMask(int);
extern void func_02077b70(int *, int);
extern void func_ov065_0227f1f4(int, int);
extern void func_0204f934(int);
extern int func_020e98f4(int, int);
extern void func_ov001_022141f4(int, int, int);
extern int func_020e9898(int);
extern void func_0204f8ec(int);
extern void func_02077b9c(int *);
extern void OS_RestoreInterrupts(int);
extern int data_021d11c4;
extern int SDK_OVERLAY_ov065_ID;
extern int func_0206e4fc;
extern int func_0206e4f0;
extern int SDK_OVERLAY_ov001_ID;
void func_0206e464(void)
{
    int a = OS_DisableInterrupts();
    unsigned short saved = *(volatile unsigned short *) 0x04000208;
    *(volatile unsigned short *) 0x04000208 = 0;
    OS_DisableIrqMask(7);
    OS_ResetRequestIrqMask(7);
    func_02077b70(&data_021d11c4, (int) &SDK_OVERLAY_ov065_ID);
    func_ov065_0227f1f4((int) &func_0206e4fc, (int) &func_0206e4f0);
    func_0204f934((int) &SDK_OVERLAY_ov001_ID);
    {
        int v = func_020e98f4(0x40000, 0x20);
        func_ov001_022141f4(v, 6, 0);
        func_020e9898(v);
    }
    func_0204f8ec((int) &SDK_OVERLAY_ov001_ID);
    func_02077b9c(&data_021d11c4);
    (void) *(volatile unsigned short *) 0x04000208;
    *(volatile unsigned short *) 0x04000208 = saved;
    OS_RestoreInterrupts(a);
}
