/* func_0209bd98 @ 0x0209bd98, 0x118 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 data_021dc50c;
extern u16 data_021dc570[8];
extern void func_020051b0(void *o);
extern void __register_global_object(void *o, void (*d)(void *), void *n);
extern u8 data_021dc510[12], data_021dc51c[12], data_021dc528[12], data_021dc534[12], data_021dc540[12], data_021dc54c[12],
    data_021dc558[12], data_021dc564[12];
extern int func_0209c38c(int i);

void func_0209bd98(u16 *out, int i)
{
    if (!(data_021dc50c & 1)) {
        data_021dc570[0] = 0x1376;
        __register_global_object(&data_021dc570[0], func_020051b0, data_021dc510);
        data_021dc570[1] = 0x1374;
        __register_global_object(&data_021dc570[1], func_020051b0, data_021dc51c);
        data_021dc570[2] = 0x1369;
        __register_global_object(&data_021dc570[2], func_020051b0, data_021dc528);
        data_021dc570[3] = 0xfff1;
        __register_global_object(&data_021dc570[3], func_020051b0, data_021dc534);
        data_021dc570[4] = 0xfff1;
        __register_global_object(&data_021dc570[4], func_020051b0, data_021dc540);
        data_021dc570[5] = 0x1378;
        __register_global_object(&data_021dc570[5], func_020051b0, data_021dc54c);
        data_021dc570[6] = 0xfff1;
        __register_global_object(&data_021dc570[6], func_020051b0, data_021dc558);
        data_021dc570[7] = 0xfff1;
        __register_global_object(&data_021dc570[7], func_020051b0, data_021dc564);
        data_021dc50c |= 1;
    }
    if (func_0209c38c(i)) {
        *out = data_021dc570[i];
    } else {
        *out = 0xfff1;
    }
}
