/* func_020b6c0c @ 0x020b6c0c, 0x114 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020b6c0c;
typedef int (UnkStruct_020b6c0c::*PMF)(u64);
struct UnkStruct_020b6c0c {
    int pad_00;
};

extern PMF data_020e54c4, data_020e54cc, data_020e54d4, data_020e54e4, data_020e54fc, data_020e54dc;
extern u8 data_021f42f0;

extern "C" u64 OS_GetTick(void);
extern "C" void func_02074904(int);
extern "C" void func_020a6c08(void);
extern "C" void func_02046600(void);

extern int data_021f6930;
extern PMF data_021f6a3c[6];

extern "C" int func_020b6c0c(UnkStruct_020b6c0c *obj)
{
    if (!(data_021f6930 & 1)) {
        data_021f6a3c[0] = data_020e54c4;
        data_021f6a3c[1] = data_020e54cc;
        data_021f6a3c[2] = data_020e54d4;
        data_021f6a3c[3] = data_020e54e4;
        data_021f6a3c[4] = data_020e54fc;
        data_021f6a3c[5] = data_020e54dc;
        data_021f6930 |= 1;
    }
    u64 start;
    int flag;

    start = OS_GetTick();
    flag = 0;
    for (;;) {
        if ((u32) (data_021f42f0 - 1) >= 6) {
            break;
        }
        if ((obj->*data_021f6a3c[data_021f42f0 - 1])(start) != 0) {
            data_021f42f0++;
            if (data_021f42f0 > 6) {
                break;
            }
            if ((u32) (((OS_GetTick() - start) * 64) / 33514) > 40) {
                flag = 1;
                break;
            }
        } else {
            flag = 1;
            break;
        }
    }
    if (flag) {
        func_02074904(0);
        func_020a6c08();
        func_02046600();
        return -1;
    } else {
        return 1;
    }
}
