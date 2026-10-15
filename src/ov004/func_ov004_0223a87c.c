/* func_ov004_0223a87c @ 0x0223a87c, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021f3b28[];
extern int func_ov004_0223a8f0(void);

int func_ov004_0223a87c(void *receiver)
{
    int h = data_021f3b28[3] & 0x1f;
    if (h <= 6) {
        return 0;
    }
    if (h <= 9) {
        return 1;
    }
    if (h <= 0xf) {
        return func_ov004_0223a8f0() ? 8 : 2;
    }
    if (h <= 0x12) {
        return 3;
    }
    if (h <= 0x15) {
        return 4;
    }
    if (h <= 0x19) {
        return 5;
    }
    if (h <= 0x1c) {
        return func_ov004_0223a8f0() ? 9 : 6;
    }
    return func_ov004_0223a8f0() ? 0xa : 7;
}
