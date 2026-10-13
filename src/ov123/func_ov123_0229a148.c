/* func_ov123_0229a148 @ 0x0229a148, 0x38 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_0229ae7c(int);
extern int func_ov123_0229ae74(int, int);
extern void func_020896b8(int, int *, int, int, int, int, int);
extern int data_ov123_0229cf08;

void func_ov123_0229a148(int a0, int a1, int a2)
{
    int v1 = func_ov123_0229ae7c(a0);
    int v2 = func_ov123_0229ae74(a0, a2);
    func_020896b8(1, &data_ov123_0229cf08, v1, v2, -1, -1, 0);
}
