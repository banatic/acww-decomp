/* func_02017310 @ 0x02017310, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(int, int);
extern int func_020164cc(int, int);
extern void func_02057cb8(int);
extern void func_02016764(int, int, int, int, int, int, int, int);
extern void func_02019af0(int, int);
extern unsigned short data_020c80f8;

void func_02017310(int param1, int param2)
{
    if (func_020164a0(param2 + 0x334, 0) != 0x2A) {
        return;
    }
    if (func_020164cc(param2 + 0x334, param2) == 0) {
        return;
    }
    func_02057cb8(param2);
    func_02016764(param2 + 0x334, param2, 0, data_020c80f8, 0, 0x1000, 0, 0);
    func_02019af0(param1, 1);
}
