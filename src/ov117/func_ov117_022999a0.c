/* func_ov117_022999a0 @ 0x022999a0, 0x40 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov117_0229a320;
extern void func_ov117_02299a94(int, int);
extern int func_ov117_02299a88(int);
extern void func_ov117_02299ca4(int, int);
extern void func_020e9898(int);

void func_ov117_022999a0(int p0, int p1)
{
    if (data_ov117_0229a320 != 0) {
        func_ov117_02299a94(data_ov117_0229a320, p0);
        if (p1 != 0) {
            func_ov117_02299ca4(func_ov117_02299a88(data_ov117_0229a320), p1);
        }
        func_020e9898(data_ov117_0229a320);
        data_ov117_0229a320 = 0;
    }
}
