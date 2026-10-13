/* func_ov066_0226748c @ 0x0226748c, 0xa4 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int data_ov066_0226bdec;
extern int data_ov066_0226bde8;
extern int data_ov066_0226bde4;
extern int data_ov066_0226bde0;

extern int func_ov066_02266908(int, int);
extern int func_ov066_02267530(int);
extern void func_ov066_0226686c(int);
extern void func_ov066_022668c4(int);
extern void OS_InitTick(void);
extern void OS_InitAlarm(void);
extern int WM_IsExistAllowedChannel(void);

int func_ov066_0226748c(int r0, int r1, int r2, int r3)
{
    int r4 = r0;
    int result;

    if (data_ov066_0226bdec == 0) {
        data_ov066_0226bde8 = r1;
        data_ov066_0226bde4 = r2;
        data_ov066_0226bde0 = r3;
        result = func_ov066_02266908(0x40, 4);
        data_ov066_0226bdec = result;
        if (result != 0) {
            OS_InitTick();
            OS_InitAlarm();
            if (WM_IsExistAllowedChannel() != 0) {
                func_ov066_02267530(r4);
                return 1;
            }
            func_ov066_0226686c(0x41);
            func_ov066_022668c4(data_ov066_0226bdec);
        }
    }
    return 0;
}
