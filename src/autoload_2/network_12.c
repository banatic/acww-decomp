/* network_12: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ec980 @ 0x020ec980, 0x200 bytes, ARM
 * func_020ec920 @ 0x020ec920, 0x60 bytes, ARM
 * func_020ec848 @ 0x020ec848, 0xd8 bytes, ARM
 * func_020ec5ac @ 0x020ec5ac, 0x29c bytes, ARM
 */

#include "types.h"

#define OS_TicksToMilliSeconds(t) (((u64) (t) << 6) / 0x82eaULL)

typedef struct S1f8 {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
} S1f8;

extern unsigned short data_021fbefc;
extern int data_021fbf5c;
extern int data_0213e744;
extern int data_0213e6bc;
extern int data_0213e6c4;
extern int data_0213e750;
extern int data_021fbf3c;
extern int data_021fbf40;
extern int data_021fc220;
extern void func_020ed3d4(int result, int index, int user_data);
extern unsigned char data_021fbef8;
extern void func_020ed144(unsigned short value, int index);
extern S1f8 data_021fbff8;
extern int func_ov065_0227f46c(void *p);
extern void DWC_SetAuthServer(int n);
extern void DWC_ConnectInetAsync(void);
extern int func_ov065_0227f380(void);
extern int DWC_GetInetStatus(void);
extern int func_ov065_0227f720(void *p);
extern void func_ov065_022782d4(void *a, int b, int c, void *d, void *e, int f, int g, int h, int i);
extern void func_ov065_02277f98(int a, int b, void (*callback)(int, int, int), int d);
extern void DWC_SetSendSplitMax(int n);
extern void *func_ov065_0227ecf0(void (*callback)(unsigned short, int));
extern void func_020ecfec(void);
extern int func_020ec1f8(void);
extern int func_020ecb80(void);
extern int func_ov066_022672b8(int a, int b, int c);
extern unsigned long long OS_GetTick(void);
extern int func_ov066_0226760c(void);
extern void func_ov066_0226b90c(void);
extern int func_ov066_02267404(void);
extern unsigned int data_0213e6b8;
extern u16 data_021fbf00;   // 0x021fbf00
extern u32 data_021fbf54;   // 0x021fbf54
extern void *data_021fbf1c; // 0x021fbf1c
extern void *data_021fbf2c; // 0x021fbf2c
extern void *data_021fbf44; // 0x021fbf44
extern void *data_021fbf0c; // 0x021fbf0c
extern int func_020eba18(void);
extern int func_020edacc(void *p);
extern int func_ov065_02277cbc(void);
extern int func_ov065_02277c28(void);
extern int func_ov065_0227f710(void);
extern void func_ov065_022781e4(void);
extern int func_ov065_0227f22c(void);

int func_020ec980(void)
{
    switch (data_021fbefc) {
        case 0:
            func_ov065_0227f46c(&data_021fbf5c);
            DWC_SetAuthServer(2);
            DWC_ConnectInetAsync();
            data_021fbefc = 1;
            break;
        case 1:
            if (func_ov065_0227f380() != 0) {
                if (DWC_GetInetStatus() == 4) {
                    data_021fbefc = 2;
                }
            }
            break;
        case 2:
            func_ov065_0227f720(&data_0213e744);
            data_0213e6bc = 1;
            data_0213e6c4 = 1;
            func_ov065_022782d4(&data_021fc220, data_021fbf40 + 0x20, 0x299e, &data_0213e744, &data_0213e750, 0, 0,
                                data_021fbf3c, 0x20);
            func_ov065_02277f98(0, 0, &func_020ed3d4, 0);
            data_021fbefc = 3;
            break;
        case 3:
            if (data_0213e6c4 == 0) {
                data_0213e6c4 = 1;
                data_021fbefc = 4;
            }
            break;
        case 4:
            if (data_021fbef8 == 3) {
                data_0213e6c4 = 0;
            }
            if (data_0213e6c4 == 0) {
                DWC_SetSendSplitMax(0x100);
                func_ov065_0227ecf0(&func_020ed144);
                func_020ecfec();
                data_021fbefc = 5;
            }
            break;
        case 5:
            if (data_021fbef8 != 4) {
                goto ret1;
            }
            if ((func_020ec1f8() & 1) != 0) {
                if (data_021fbff8.unk_02 <= 0x1e) {
                    goto ret1;
                }
            }
            return 0;
        ret1:
            return 1;
    }
    return 0;
}

int func_020ec920(void)
{
    if ((data_021fbef8 == 1) || (data_021fbef8 == 2)) {
        return func_020ecb80();
    }
    if ((data_021fbef8 == 3) || (data_021fbef8 == 4)) {
        return func_020ec980();
    }
    return 0;
}

int func_020ec848(void)
{
    unsigned int start;
    unsigned int over;

    func_ov066_022672b8(0, 0, 0);
    start = (unsigned int) ((OS_GetTick() << 6) / 0x82ea);
    while (func_ov066_0226760c() != 2) {
        over = (unsigned int) (((unsigned long long) ((OS_GetTick() << 6) / 0x82ea) - start) > data_0213e6b8);
        if (over != 0) {
            return 0;
        }
    }
    func_ov066_0226b90c();
    if (func_ov066_02267404() == 0) {
        return 0;
    }
    data_021fbef8 = 6;
    return 1;
}

int func_020ec5ac(void)
{
    switch (data_021fbf00) {
        case 0:
            data_021fbf54 = (u32) OS_TicksToMilliSeconds((u64) OS_GetTick());
            data_021fbf00 = 1;
            break;
        case 1:
            if ((*(void * *) &data_0213e6c4) == 0 || (*(u16 *) &data_021fbefc) == 4 ||
                (unsigned int) (OS_TicksToMilliSeconds((u64) OS_GetTick()) - data_021fbf54 > (*(u32 *) &data_0213e6b8)) != 0) {
                func_020eba18();
                if (func_ov065_02277cbc() < 0) {
                    data_021fbf54 = 0;
                } else {
                    data_021fbf54 = (u32) OS_TicksToMilliSeconds((u64) OS_GetTick());
                }
                data_021fbf00 = 2;
            }
            break;
        case 2:
            if (func_ov065_02277c28() < 2) {
                data_021fbf00 = 3;
            } else if ((unsigned int) (OS_TicksToMilliSeconds((u64) OS_GetTick()) - data_021fbf54 > (*(u32 *) &data_0213e6b8)) != 0) {
                data_021fbf00 = 3;
            }
            break;
        case 3:
            func_ov065_0227f710();
            data_021fbf00 = 4;
            break;
        case 4:
            func_ov065_022781e4();
            data_021fbf00 = 5;
            break;
        case 5:
            if (func_ov065_0227f22c() != 0) {
                data_021fbf00 = 6;
            }
            break;
        case 6:
            if (data_021fbf1c != 0) {
                func_020edacc(data_021fbf1c);
                func_020edacc(data_021fbf2c);
                data_021fbf1c = 0;
                data_021fbf2c = 0;
            }
            if (data_021fbf44 != 0) {
                func_020edacc(data_021fbf44);
                func_020edacc(data_021fbf0c);
                data_021fbf44 = 0;
                data_021fbf0c = 0;
            }
            data_021fbf00 = 7;
            break;
        case 7:
            return 1;
    }
    return 0;
}
