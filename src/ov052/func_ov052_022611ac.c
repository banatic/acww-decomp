/* func_ov052_022611ac @ 0x022611ac, 0x44 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(int);
extern int func_02019de8(int);
extern void func_02019c6c(int, int, unsigned short);
extern void func_0203e0a8(int, int);

int func_ov052_022611ac(int p)
{
    if (func_02019e00(p + 0x564) == 3) {
        if (func_02019de8(p + 0x564) != 0) {
            func_02019c6c(p + 0x564, 1, *(unsigned short *) (p + 0x71c));
        }
    }
    func_0203e0a8(p, 0);
    return 1;
}
