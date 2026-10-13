/* func_ov144_0229ac40 @ 0x0229ac40, 0x50 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220af94(void *p);
extern void func_02002c6c(void *p, int a, int b, int c, int d, int e);
extern void func_02002d14(void *p, int a, int b, int c, int d, int e);
extern int data_021fbe94;
extern unsigned char data_ov144_0229b458[];
extern unsigned char data_ov144_0229b46c[];

void func_ov144_0229ac40(void *self)
{
    int val;
    func_ov002_0220af94((char *) self + 0x170);
    val = data_021fbe94;
    func_02002c6c(data_ov144_0229b458, val, 8, 0xc0, 0xc0, 0x120);
    func_02002d14(data_ov144_0229b46c, val, 8, 4, 4, 5);
}
