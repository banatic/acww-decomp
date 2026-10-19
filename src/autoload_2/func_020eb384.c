/* func_020eb384 @ 0x020eb384, 0x298 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

#pragma opt_strength_reduction off

extern u16 data_021fbefc;
extern int data_0213e6bc;
// "0123456789abcdef", the template of the local digit table
typedef struct {
    u8 c[17];
} HexDigits;
extern const HexDigits data_0213e6dc;
extern char *data_021fbf1c;
extern char *data_021fbf2c;
extern char *data_021fbf40;

extern const char data_0213e708[];
extern const char data_0213e720[];
extern const char data_0213e728[];
extern const char data_0213e72c[];
extern const char data_0213e734[];
extern const char data_0213e73c[];

extern int STD_GetStringLength(const char *s);
extern void *func_020edaf0(int size, int align);
extern int func_020edacc(void *p);
extern char *STD_CopyString(char *dst, const char *src);
extern int func_ov065_02277148(const void *src, u32 len, char *dst, int cap);
extern void MATH_CalcSHA1(void *digest, const void *data, int len);
extern void MI_CpuFill8(void *dst, int val, int n);
extern unsigned long long func_020eb694(char *p);
extern int OS_SNPrintf(char *buf, unsigned int n, const char *fmt, ...);
extern int func_ov065_0227f6b0(void *sb);
extern int func_ov065_0227f6a4(void *sb, const char *k, const void *v);
extern int DWC_PostGHTTPData(int a, void *sb, void *cb, int d);
extern void func_020ed3c0(void);

int func_020eb384(int a0, const void *a1, u32 a2, int a3)
{
    void *sb;
    int len;
    int cap;
    int enc;
    u8 *d;
    u32 i;

    if (data_021fbefc < 4) {
        return 0;
    }
    if (data_0213e6bc == 0) {
        goto ret0;
    }

    cap = ((a2 + 2) / 3) * 4 + 1;
    len = STD_GetStringLength(data_0213e708);
    data_021fbf1c = (char *) func_020edaf0(len + cap, 4);
    if (data_021fbf1c == 0) {
        return 0;
    }
    data_021fbf2c = (char *) func_020edaf0(0x29, 4);
    if (data_021fbf2c == 0) {
        func_020edacc(data_021fbf1c);
        data_021fbf1c = 0;
        return 0;
    }
    STD_CopyString(data_021fbf1c, data_0213e708);
    enc = func_ov065_02277148(a1, a2, data_021fbf1c + len, cap);
    MATH_CalcSHA1(data_021fbf2c + 0x14, data_021fbf1c, len + enc);
    {
        HexDigits hex = data_0213e6dc;
        d = (u8 *) data_021fbf2c + 0x14;
        for (i = 0; i < 0x14; i++) {
            data_021fbf2c[i * 2] = hex.c[d[i] >> 4];
            *(data_021fbf2c + i * 2 + 1) = hex.c[d[i] & 0xf];
        }
    }
    data_021fbf2c[0x28] = 0;
    data_0213e6bc = 0;
    {
        char buf[16];
        MI_CpuFill8(buf, 0, 0x10);
        OS_SNPrintf(buf, 0x10, data_0213e720, func_020eb694(data_021fbf40 + 0x20));
        func_ov065_0227f6b0(&sb);
        func_ov065_0227f6a4(&sb, data_0213e728, buf);
        func_ov065_0227f6a4(&sb, data_0213e72c, data_021fbf2c);
        func_ov065_0227f6a4(&sb, data_0213e734, data_021fbf1c + 0x14);
        func_ov065_0227f6a4(&sb, data_0213e73c, (const void *) a3);
        DWC_PostGHTTPData(a0, &sb, (void *) func_020ed3c0, 0);
    }
    return 1;
ret0:
    return 0;
}
