/* func_020ec5ac @ 0x020ec5ac, 0x29c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern u16 data_021fbf00;   // 0x021fbf00
extern u32 data_021fbf54;   // 0x021fbf54
extern void *data_0213e6c4; // 0x0213e6c4
extern u32 data_0213e6b8;   // 0x0213e6b8
extern u16 data_021fbefc;   // 0x021fbefc
extern void *data_021fbf1c; // 0x021fbf1c
extern void *data_021fbf2c; // 0x021fbf2c
extern void *data_021fbf44; // 0x021fbf44
extern void *data_021fbf0c; // 0x021fbf0c

extern u64 OS_GetTick(void);
#define OS_TicksToMilliSeconds(t) (((u64) (t) << 6) / 0x82eaULL)

extern int func_020eba18(void);
extern int func_020edacc(void *p);
extern int func_ov065_02277cbc(void);
extern int func_ov065_02277c28(void);
extern int func_ov065_0227f710(void);
extern void func_ov065_022781e4(void);
extern int func_ov065_0227f22c(void);

int func_020ec5ac(void)
{
    switch (data_021fbf00) {
        case 0:
            data_021fbf54 = (u32) OS_TicksToMilliSeconds(OS_GetTick());
            data_021fbf00 = 1;
            break;
        case 1:
            if (data_0213e6c4 == 0 || data_021fbefc == 4 ||
                (unsigned int) (OS_TicksToMilliSeconds(OS_GetTick()) - data_021fbf54 > data_0213e6b8) != 0) {
                func_020eba18();
                if (func_ov065_02277cbc() < 0) {
                    data_021fbf54 = 0;
                } else {
                    data_021fbf54 = (u32) OS_TicksToMilliSeconds(OS_GetTick());
                }
                data_021fbf00 = 2;
            }
            break;
        case 2:
            if (func_ov065_02277c28() < 2) {
                data_021fbf00 = 3;
            } else if ((unsigned int) (OS_TicksToMilliSeconds(OS_GetTick()) - data_021fbf54 > data_0213e6b8) != 0) {
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
