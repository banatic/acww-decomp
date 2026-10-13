/* func_020eb188 @ 0x020eb188, 0x164 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern unsigned short data_021fbefc;
extern int data_0213e6c0;
extern int data_021fbf44;
extern int data_021fbf0c;
extern char *data_021fbf40;
extern int data_021fbf4c;
extern int data_021fbf14;
extern int data_021fbf10;
extern int data_0213e6f0;

extern int func_020edaf0(int, int);
extern void UTi_PutString(int);
extern u64 func_020eb694(char *);
extern void OS_SNPrintf(int, int, int, int, u64, int);
extern void DWC_GetGHTTPData(int, int, int);
extern void func_020ed194(void);

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
            UTi_PutString(data_021fbf44);
            data_021fbf44 = 0;
            return 0;
        }

        data_0213e6c0 = 0;
        data_021fbf4c = a;
        data_021fbf14 = c;
        data_021fbf10 = d;

        OS_SNPrintf(data_021fbf44, 0x100, (int) &data_0213e6f0, data_021fbf4c, func_020eb694(data_021fbf40 + 0x20), d);
        DWC_GetGHTTPData(data_021fbf44, (int) func_020ed194, b);
        return 1;
    }
    return 0;
}
