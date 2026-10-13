/* func_0205f7bc @ 0x0205f7bc, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 data_021c9ad0;
extern u8 *data_020ccf94;
extern u32 func_0205f800(void);
extern u32 func_020ea0e0(u32, u32);

void func_0205f7bc(u32 *arr)
{
    u32 a;
    u32 count;
    u32 i;

    a = data_021c9ad0;
    count = data_020ccf94[0x6c];

    for (i = 0; i < count; i++) {
        arr[i] = func_020ea0e0(func_0205f800(), a);
    }
}
