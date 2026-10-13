/* func_ov096_022a018c @ 0x022a018c, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(int);
extern void func_ov096_0229dc48(int);
extern int func_ov002_0220909c(int);
extern void func_ov002_022096d8(int, int);
extern void func_ov002_02207d24(int, int);

int func_ov096_022a018c(int r0)
{
    int r4 = r0;
    if (func_ov002_0220909c(r4 + 0x2564) != 0) {
        func_ov002_022096d8(r4 + 0x2564, 0);
        func_ov002_02207d24(r4 + 0x2418, 1);
        if (func_0208e4bc(r4 + 0x2500) != 0) {
            func_ov096_0229dc48(r4);
        }
        return 1;
    }
    return 0;
}
