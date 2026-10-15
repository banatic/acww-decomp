/* func_020ed194 @ 0x020ed194, 0x18c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

// Builds the Nintendo WFC query URL: SHA-1 of the salt and s, hex-encoded, formatted with the PID.
#pragma opt_strength_reduction off

extern const char data_0213e708[];
extern const char data_0213e758[];
extern u8 *data_021fbf0c;
extern void *data_021fbf40;
extern unsigned int data_021fbf10;
extern void *data_021fbf44;
extern unsigned int data_021fbf4c;
extern int data_0213e6c0;

extern char *STD_CopyString(char *, const char *);
extern char *STD_ConcatenateString(char *, const char *);
extern int STD_GetStringLength(const char *);
extern void MATH_CalcSHA1(void *, const void *, unsigned int);
extern unsigned long long func_020eb694(void *);
extern int OS_SNPrintf(void *, int, const char *, ...);
extern void func_020ed370(int buffer, int size, int result, int user_data);
extern int DWC_GetGHTTPData(void *, void (*)(int, int, int, int), char *);

void func_020ed194(const char *s, int len, int flag, char *buf)
{
    unsigned int i;
    long long t;
    u8 *d;

    if (s == 0) {
        goto err;
    }
    if (len == 0) {
        goto err;
    }
    if (flag != 0) {
        goto err;
    }

    STD_CopyString(buf, data_0213e708);
    STD_ConcatenateString(buf, s);
    MATH_CalcSHA1(data_021fbf0c + 0x14, buf, len + STD_GetStringLength(data_0213e708));
    {
        unsigned char tbl[17] = "0123456789abcdef";
        d = data_021fbf0c + 0x14;
        for (i = 0; i < 0x14; i++) {
            data_021fbf0c[i * 2] = tbl[d[i] >> 4];
            *(data_021fbf0c + i * 2 + 1) = tbl[d[i] & 0xf];
        }
    }
    data_021fbf0c[0x28] = 0;
    t = func_020eb694((char *) data_021fbf40 + 0x20);
    OS_SNPrintf(data_021fbf44, 0x100, data_0213e758, data_021fbf4c, t, data_021fbf0c, data_021fbf10);
    DWC_GetGHTTPData(data_021fbf44, func_020ed370, buf);
    return;
err:
    data_0213e6c0 = 1;
}
