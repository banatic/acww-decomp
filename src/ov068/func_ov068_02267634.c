/* func_ov068_02267634 @ 0x02267634, 0x74 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02016104(int);
extern void func_02013aac(int);
extern int func_0201c314(int, int);
extern void func_ov068_02266c34(int, int, int, int, int, int, int, int, int);
extern int func_020147fc(int, int, int, int);
extern int data_021fbee8;
extern int data_020c814c;

int func_ov068_02267634(int param0, int param1)
{
    int r4, r6;
    r4 = func_02016104(param1 + 0x680);
    r6 = 0;
    func_02013aac(param1);
    if (r4 != 0) {
        r6 = func_0201c314(param1, r4);
    }
    func_ov068_02266c34(param1 + 0x898, param1, 1, 0, 0, (int) &data_021fbee8, 4, data_020c814c, 1);
    func_020147fc(param1 + 0x618, 0, r6, 0);
    return 1;
}
