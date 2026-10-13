/* func_ov123_0229c30c @ 0x0229c30c, 0x50 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_020027f0(int);
extern void func_020019f4(void);
extern void func_ov123_02299630(int, int);
extern void func_ov123_0229c07c(int);
extern int func_ov002_02207f3c(int, int);
extern void func_ov002_022080a0(int, int);
extern void func_ov002_0220ad0c(int);

void func_ov123_0229c30c(int r0)
{
    int r4 = r0;
    if (func_ov002_02207f3c(r4, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_020027f0(3);
        func_ov002_022080a0(r4, 5);
        func_020019f4();
        func_ov123_02299630(r4, 1);
        func_ov002_0220ad0c(r4 + 0x5030);
    } else {
        func_ov123_0229c07c(r4);
    }
}
