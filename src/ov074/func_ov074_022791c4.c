/* func_ov074_022791c4 @ 0x022791c4, 0x1c bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov074_02279668(void *argument0);
extern void func_ov074_02279778(int, int);

int func_ov074_022791c4(int param)
{
    int result;
    int local = param;

    result = func_ov074_02279668((void *) param);
    if (result != 0) {
        func_ov074_02279778(local, 2);
    }
    return 1;
}
