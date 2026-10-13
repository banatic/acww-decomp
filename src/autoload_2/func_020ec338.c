/* func_020ec338 @ 0x020ec338, 0x64 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern u8 data_021fbef8;
extern int func_ov066_0226a8c4(int a, int b, int c);
extern int DWC_SetRecvBuffer(u8 a, int b, int c);

int func_020ec338(int a, int b, int c)
{
    u8 v;

    v = data_021fbef8;
    if ((u8) (v + 0xff) <= 1) {
        return func_ov066_0226a8c4(a, b, c);
    }
    if ((u8) (v + 0xfd) <= 1) {
        return DWC_SetRecvBuffer((u8) a, b, c);
    }
    return 0;
}
