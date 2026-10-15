/* func_ov079_02279680 @ 0x02279680, 0x1c bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov079_02279b24(void *argument0);
extern void func_ov079_02279c34(int, int);

int func_ov079_02279680(int param)
{
    int r4 = param;
    if (func_ov079_02279b24((void *) param) != 0) {
        func_ov079_02279c34(r4, 2);
    }
    return 1;
}
