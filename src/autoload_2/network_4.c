/* network_4: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020eb2ec @ 0x020eb2ec, 0x98 bytes, ARM
 * func_020eb188 @ 0x020eb188, 0x164 bytes, ARM
 * func_020eb108 @ 0x020eb108, 0x80 bytes, ARM
 * func_020eb070 @ 0x020eb070, 0x98 bytes, ARM
 */

#include "types.h"

extern unsigned short data_021fbefc; // 0x021fbefc
extern int data_0213e6bc;            // 0x0213e6c0
extern int data_021fbf1c;            // 0x021fbf44
extern int data_021fbf2c;            // 0x021fbf0c
int func_020edacc(int arg);
extern int data_0213e6c0;
extern int data_021fbf44;
extern int data_021fbf0c;
extern char *data_021fbf40;
extern int data_021fbf4c;
extern int data_021fbf14;
extern int data_021fbf10;
extern int data_0213e6f0;
extern int func_020edaf0(int, int);
extern unsigned long long func_020eb694(char *);
extern int OS_SNPrintf(char *buffer, unsigned int size, const char *format, ...);
extern int DWC_GetGHTTPData(int, int, int);
extern void func_020ed194(void *unused0, int unused1, int unused2, void *unused3);
extern void func_020ed320(const void *buffer, int length, int result, void *argument);

int func_020eb2ec(void)
{
    if (data_021fbefc < 4) {
        return 0;
    }
    if (data_0213e6bc == 0) {
        goto ret0;
    }
    if (data_021fbf1c != 0) {
        func_020edacc(data_021fbf1c);
        func_020edacc(data_021fbf2c);
        data_021fbf1c = 0;
        data_021fbf2c = 0;
    }
    return 1;
ret0:
    return 0;
}

int func_020eb188(int a, int b, int c, int d)
{
    if (data_021fbefc < 4) {
        return 0;
    }

    if (data_0213e6c0 != 0) {
        data_021fbf44 = func_020edaf0(0x100, 4);
        if (data_021fbf44 == 0) {
            return 0;
        }

        data_021fbf0c = func_020edaf0(0x29, 4);
        if (data_021fbf0c == 0) {
            func_020edacc(data_021fbf44);
            data_021fbf44 = 0;
            return 0;
        }

        data_0213e6c0 = 0;
        data_021fbf4c = a;
        data_021fbf14 = c;
        data_021fbf10 = d;

        OS_SNPrintf((char *) data_021fbf44, 0x100, (const char *) &data_0213e6f0, data_021fbf4c,
                    func_020eb694(data_021fbf40 + 0x20), d);
        DWC_GetGHTTPData(data_021fbf44, (int) func_020ed194, b);
        return 1;
    }
    return 0;
}

int func_020eb108(int a, int b, int c)
{
    if (data_021fbefc < 4) {
        return 0;
    }
    if (data_0213e6c0 == 0) {
        return 0;
    }
    data_021fbf14 = c;
    data_0213e6c0 = 0;
    DWC_GetGHTTPData((int) ((const char *) a), (int) func_020ed320, (int) ((void *) b));
    return 1;
}

int func_020eb070(void)
{
    if (data_021fbefc < 4) {
        return 0;
    }
    if (data_0213e6c0 == 0) {
        goto ret0;
    }
    if (data_021fbf44 != 0) {
        func_020edacc(data_021fbf44);
        func_020edacc(data_021fbf0c);
        data_021fbf44 = 0;
        data_021fbf0c = 0;
    }
    return 1;
ret0:
    return 0;
}
