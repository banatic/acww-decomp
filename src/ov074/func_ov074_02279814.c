/* func_ov074_02279814 @ 0x02279814, 0x2c bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void *argument0);
extern void func_ov074_02278a6c(int, int);

extern int data_021fbe94;

int func_ov074_02279814(int param)
{
    if (func_0202ec14((void *) param) == 0) {
        return 0;
    }
    func_ov074_02278a6c(param + 0x714, data_021fbe94);
    return 1;
}
