/* func_ov093_02299514 @ 0x02299514, 0x68 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94;
extern int data_ov093_02299880;
extern int data_ov093_02299884;

extern int func_02002d14(int a, int b, int c, int d, int e, int f);
extern int func_02002c6c(int a, int b, int c, int d, int e, int f);

void func_ov093_02299514(void *self)
{
    int r4;
    r4 = data_021fbe94;
    func_02002d14(data_ov093_02299880, r4, 4, 1, 1, 3);
    func_02002d14(data_ov093_02299880, r4, 0, 1, 1, 3);
    func_02002c6c(data_ov093_02299884, r4, 4, 0x10, 0x10, 0x10);
    func_02002c6c(data_ov093_02299884, r4, 0, 0x10, 0x10, 0x10);
}
