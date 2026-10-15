/* func_ov145_0229a678 @ 0x0229a678, 0x50 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220af94(void *receiver);
extern int func_02002c6c(char *a, int b, int c, int d, int e, int f);
extern int func_02002d14(char *a, int b, int c, int d, int e, int f);
extern int data_021fbe94;
extern char data_ov145_0229aee0[];
extern char data_ov145_0229aef8[];
void func_ov145_0229a678(char *param)
{
    int value;
    func_ov002_0220af94(param + 0x174);
    value = data_021fbe94;
    func_02002c6c(data_ov145_0229aee0, value, 8, 0xc0, 0xc0, 0x13f);
    func_02002d14(data_ov145_0229aef8, value, 8, 4, 4, 9);
}
