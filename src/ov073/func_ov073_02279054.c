/* func_ov073_02279054 @ 0x02279054, 0x1c bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov073_022794f8(int unused0);
extern void func_ov073_02279608(int, int);

int func_ov073_02279054(int r0)
{
    int r4 = r0;
    if (func_ov073_022794f8(r0) != 0) {
        func_ov073_02279608(r4, 2);
    }
    return 1;
}
