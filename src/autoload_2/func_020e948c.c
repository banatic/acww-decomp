/* func_020e948c @ 0x020e948c, 0xbc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void TP_Init(void);
extern int TP_GetUserInfo(unsigned char *);
extern void TP_SetCalibrateParam(unsigned char *);
extern void TP_RequestSetStabilityAsync(int, int);
extern void TP_WaitBusy(int);
extern int TP_CheckError(int);
extern void TP_RequestAutoSamplingStartAsync(int, int, void *, int);
extern void OS_Terminate(void);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned short data_021fbde0;
extern unsigned short data_021fbde4;
extern unsigned char data_021fbdf0;

void func_020e948c(void)
{
    unsigned char userInfo[12];
    TP_Init();
    TP_GetUserInfo(userInfo);
    TP_SetCalibrateParam(userInfo);
    TP_RequestSetStabilityAsync(3, 30);
    TP_WaitBusy(8);
    if (TP_CheckError(8) != 0) {
        OS_Terminate();
    }
    TP_RequestAutoSamplingStartAsync(0, 4, &data_021fbdf0, 9);
    TP_WaitBusy(2);
    if (TP_CheckError(2) != 0) {
        OS_Terminate();
    }
    data_021fbdd8 = 0;
    data_021fbddc = 0;
    data_021fbde0 = 0xff;
    data_021fbde4 = 0xff;
}
