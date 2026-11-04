/* network_10: 8 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ec148 @ 0x020ec148, 0x50 bytes, ARM
 * func_020ec040 @ 0x020ec040, 0x108 bytes, ARM
 * func_020ebfd8 @ 0x020ebfd8, 0x68 bytes, ARM
 * func_020ebf70 @ 0x020ebf70, 0x68 bytes, ARM
 * func_020ebeb8 @ 0x020ebeb8, 0xb8 bytes, ARM
 * func_020ebc30 @ 0x020ebc30, 0x288 bytes, ARM
 * func_020eba94 @ 0x020eba94, 0x19c bytes, ARM
 * func_020eba18 @ 0x020eba18, 0x7c bytes, ARM
 */

#include "types.h"

typedef struct {
    u8 *p;
    u32 unk_04;
} Str;

extern int func_020ec1b4(void);
extern int func_020ec198(void);
extern unsigned char data_021fbef8;
extern u32 data_021fbf98;
extern u32 data_021fbf18;
extern u32 data_0213e6b8;
extern u64 OS_GetTick(void);
extern int func_020ed9f4(void);
extern int OS_ReadMessage(void *queue, u32 *msg, u32 flags);
extern u32 DWC_GetAIDList(Str *s);
extern u8 DWC_GetMyAID(void);
extern int func_ov065_0227eef4(u8 c);
extern int func_ov066_02269934(void);
extern int func_020ec920(void);
extern int func_020ed73c(int a, int b, int c, int d);
extern void func_020ed8f4(void);
extern int func_ov066_0226760c(void);
extern u8 data_021fbf68;
extern int DWC_GetLastError(unsigned int *);
extern unsigned int data_021fbf24;
extern struct Entry {
    unsigned char pad_00[2];
    unsigned char flag;
    unsigned char pad_03;
} data_021fbff8[16];

int func_020ec148(void)
{
    if (data_021fbef8 == 2) {
        return func_020ec1b4();
    }
    if (data_021fbef8 == 4) {
        return func_020ec198();
    }
    return -1;
}

int func_020ec040(u32 param)
{
    u32 msg;
    u64 q;
    unsigned int flag;

    if (param != 0) {
        if (OS_ReadMessage(&data_021fbf98, &msg, 0)) {
            if (data_021fbf18 != 0) {
                q = OS_GetTick();
                q = (q << 6) / 0x82eaULL;
                flag = (q - (u64) data_021fbf18) > (u64) data_0213e6b8;
                if (flag != 0) {
                    data_021fbf18 = 0;
                    func_020ed9f4();
                }
            } else {
                q = OS_GetTick();
                q = (q << 6) / 0x82eaULL;
                data_021fbf18 = (u32) q;
            }
        } else {
            data_021fbf18 = 0;
            return 1;
        }
    } else {
        data_021fbf18 = 0;
    }
    return 0;
}

int func_020ebfd8(void)
{
    Str s;
    u32 i;
    u32 n;
    u8 c;

    n = DWC_GetAIDList(&s);
    for (i = 0; i < n; i++) {
        c = s.p[i];
        if (c != DWC_GetMyAID()) {
            if (func_ov065_0227eef4(c) == 0) {
                return 0;
            }
        }
    }
    return 1;
}

int func_020ebf70(void)
{
    unsigned char b = data_021fbef8;
    if ((unsigned char) (b + 255) <= 1) {
        return func_020ec040(func_ov066_02269934());
    } else {
        if ((unsigned char) (b + 253) > 1) {
            return 0;
        } else {
            return func_020ec040(func_020ebfd8());
        }
    }
}

int func_020ebeb8(int a, int b, int c, int d, int e, int f, unsigned short g, int h, int i, int j, unsigned short k, int l)
{
    int v1, v2, v3;
    if (func_020ec920() != 0 && func_020ebf70() != 0) {
        v1 = func_020ed73c(a, b, c, d);
        v2 = func_020ed73c(e, f, g, h);
        v3 = func_020ed73c(i, j, k, l);
        if (v1 != 0 || v2 != 0 || v3 != 0) {
            if (func_020ed9f4() != 0) {
                return 1;
            }
            func_020ed8f4();
        }
    }
    return 0;
}

int func_020ebc30(void)
{
    int v;

    v = func_ov066_0226760c();
    if ((v & 0x80) != 0) {
        switch (v & ~0x80) {
            case 0:
                return 0;
            case 12:
                return 0x800c;
            case 1:
                return 0x8001;
            case 2:
                return 0x8002;
            case 3:
                return 0x8003;
            case 4:
                return 0x8004;
            case 5:
                return 0x8005;
            case 6:
                return 0x8006;
            case 7:
                return 0x8007;
            case 8:
                return 0x8008;
            case 9:
                return 0x8009;
            case 10:
                return 0x800a;
            case 11:
                return 0x800b;
            case 13:
                return 0x800d;
            case 14:
                return 0x800e;
            case 15:
                return 0x800f;
            case 16:
                return 0x8010;
            case 65:
                return 0x8041;
            case 66:
                return 0x8042;
            case 67:
                return 0x8043;
            case 68:
                return 0x8044;
            default:
                return 0xffff;
        }
    }
    if (data_021fbf68 == 0xff) {
        return 0x80ff;
    }
    return 0;
}

int func_020eba94(void)
{
    int ret = DWC_GetLastError(&data_021fbf24);
    if (ret != 0) {
        switch (ret) {
            case 1:
                return 0x4001;
            case 2:
                return 0x4002;
            case 3:
                return 0x4003;
            case 4:
                return 0x4004;
            case 5:
                return 0x4005;
            case 6:
                return 0x4006;
            case 9:
                return 0x4009;
            case 10:
                return 0x400a;
            case 7:
                return 0x4007;
            case 11:
                return 0x400b;
            case 8:
                return 0x4008;
            default:
                return 0xffff;
        }
    } else {
        unsigned int i;
        for (i = 0; i < 16; i++) {
            if ((unsigned int) data_021fbff8[i].flag > 30u) {
                data_021fbf24 = 1000000;
                return 0x4007;
            }
        }
        return 0;
    }
}

int func_020eba18(void)
{
    unsigned char b = data_021fbef8;
    (*(int *) &data_021fbf24) = 0;
    if ((((unsigned int) b + 0xffU) & 0xffU) <= 1U) {
        return func_020ebc30();
    }
    if ((((unsigned int) b + 0xfdU) & 0xffU) <= 1U) {
        return func_020eba94();
    }
    return (b == 5) ? 0 : 0xffff;
}
