/* func_01ffcc60 @ 0x01ffcc60, 0x94 bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cfb88;
extern int data_020dd828;
extern unsigned short data_021cfb6c;
extern char data_021cfb98;
extern char data_021cfb90;
extern void OS_WakeupThread(void *);
extern void func_020b98ec(void);
extern void func_0205c054(void);

extern unsigned char SDK_AUTOLOAD_DTCM_START[];

void func_01ffcc60(void)
{
    if (++data_021cfb88 >= data_020dd828) {
        if (data_021cfb6c != 0) {
            OS_WakeupThread((void *) &data_021cfb98);
            data_021cfb88 = 0;
            func_020b98ec();
        }
    }
    func_0205c054();
    OS_WakeupThread((void *) &data_021cfb90);

    {
        volatile char *base = (volatile char *) SDK_AUTOLOAD_DTCM_START;
        base += 0x3000;
        *(volatile unsigned int *) (base + 0xff8) |= 1;
    }
}
