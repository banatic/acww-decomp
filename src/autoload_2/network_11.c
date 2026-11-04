/* network_11: 7 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ec434 @ 0x020ec434, 0x68 bytes, ARM
 * func_020ec3fc @ 0x020ec3fc, 0x38 bytes, ARM
 * func_020ec39c @ 0x020ec39c, 0x60 bytes, ARM
 * func_020ec338 @ 0x020ec338, 0x64 bytes, ARM
 * func_020ec2d4 @ 0x020ec2d4, 0x64 bytes, ARM
 * func_020ec260 @ 0x020ec260, 0x74 bytes, ARM
 * func_020ec1f8 @ 0x020ec1f8, 0x68 bytes, ARM
 */

#include "types.h"

extern int func_ov066_02266ce8(void);
extern unsigned short data_021fbefc;
extern int func_ov065_0227f208(void);
extern unsigned char data_021fbef8;
extern int func_ov066_0226a8c4(int a, int b, int c);
extern int DWC_SetRecvBuffer(u8 a, int b, int c);
extern int func_ov066_0226807c(void);
extern int func_ov065_02277c28(void);
extern int func_ov066_022699cc(void) __attribute__((arm));
extern int DWC_GetMyAID(void) __attribute__((thumb));
extern int func_ov066_0226997c(void);
extern int func_ov065_02277b98(void);

int func_020ec434(void)
{
    int x = func_ov066_02266ce8();
    switch (x) {
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 0:
        default:
            return 0;
    }
}

int func_020ec3fc(void)
{
    if (data_021fbefc <= 1U) {
        return 0;
    }
    return func_ov065_0227f208();
}

int func_020ec39c(void)
{
    if ((unsigned char) (data_021fbef8 + 0xff) <= 1) {
        return func_020ec434();
    } else if ((unsigned char) (data_021fbef8 + 0xfd) <= 1) {
        return func_020ec3fc();
    } else {
        return 0;
    }
}

int func_020ec338(int a, int b, int c)
{
    u8 v;

    v = (*(u8 *) &data_021fbef8);
    if ((u8) (v + 0xff) <= 1) {
        return func_ov066_0226a8c4(a, b, c);
    }
    if ((u8) (v + 0xfd) <= 1) {
        return DWC_SetRecvBuffer((u8) a, b, c);
    }
    return 0;
}

int func_020ec2d4(void)
{
    unsigned char c = data_021fbef8;
    if ((unsigned char) (c + 0xff) <= 1) {
        return func_ov066_0226807c();
    }
    if ((unsigned char) (c + 0xfd) > 1) {
        return 1;
    }
    return func_ov065_02277c28() & 0xff;
}

int func_020ec260(void)
{
    unsigned char b = data_021fbef8;
    if ((unsigned char) (b + 0xFF) <= 1) {
        if (b == 1) {
            return 0;
        }
        return func_ov066_022699cc();
    } else {
        if ((unsigned char) (b + 0xFD) <= 1) {
            return DWC_GetMyAID();
        } else {
            return 0;
        }
    }
}

int func_020ec1f8(void)
{
    unsigned char c = data_021fbef8;
    if ((unsigned char) (c + 0xff) <= 1) {
        return func_ov066_0226997c();
    } else if ((unsigned char) (c + 0xfd) <= 1) {
        return (unsigned short) func_ov065_02277b98();
    } else {
        return 1;
    }
}
