/* func_ov123_0229a094 @ 0x0229a094, 0x38 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_0229ae7c(void *a, void *b);
extern int func_ov123_0229ae74(void *a, void *b);
extern int func_020896b8(int a, void *b, int c, int d, int e, int f, int g);
extern int data_ov123_0229ceb0;

int func_ov123_0229a094(void *arg0, void *arg1, void *arg2)
{
    int v1, v2;
    v1 = func_ov123_0229ae7c(arg0, arg1);
    v2 = func_ov123_0229ae74(arg0, arg2);
    return func_020896b8(1, &data_ov123_0229ceb0, v1, v2, -1, -1, 0);
}
