/* input: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e9548 @ 0x020e9548, 0xb0 bytes, ARM
 * func_020e948c @ 0x020e948c, 0xbc bytes, ARM
 */

#include "types.h"

#define REG_UNKNOWN (*(volatile u16 *) 0x027fffa8)
#define REG_KEYINPUT (*(volatile u16 *) 0x04000130)

extern u8 data_021fbe38;
extern u16 data_021fbe3c;
extern struct {
    u16 x;
    u16 y;
    u16 z;
} data_021fbe40;
extern s16 data_02138f6c[];
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

void func_020e9548(void)
{
    int keys;
    u16 old;
    u32 idx;
    s16 tab;
    u16 changed;

    if ((REG_UNKNOWN & 0x8000) >> 15) {
        keys = 0;
    } else {
        keys = (u16) (((REG_KEYINPUT | REG_UNKNOWN) ^ 0x2fff) & 0x2fff);
    }

    idx = ((u32) keys & 0xf0) >> 4;
    old = data_021fbe3c;
    tab = data_02138f6c[idx];
    changed = (u16) (keys & (keys ^ old));

    data_021fbe38 = 0;
    data_021fbe40.y = changed;
    data_021fbe3c = (u16) keys;
    data_021fbe40.x = (u16) keys;
    data_021fbe40.z = tab;
}

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
