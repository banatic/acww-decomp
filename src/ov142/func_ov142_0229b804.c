/* func_ov142_0229b804 @ 0x0229b804, 0x70 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220af94(int);
extern int func_02002c6c(int, int *, int, int, int, int);
extern int func_02002d14(int, int *, int, int, int, int);
extern int *data_021fbe94;

extern unsigned char data_ov142_0229c4d8[];
extern unsigned char data_ov142_0229c4f0[];
extern unsigned char data_ov142_0229c508[];

void func_ov142_0229b804(int param)
{
    int *p;
    func_ov002_0220af94(param + 0x194);
    p = data_021fbe94;
    func_02002c6c((unsigned int) data_ov142_0229c4d8, p, 8, 0xc0, 0xc0, 0x11f);
    func_02002c6c((unsigned int) data_ov142_0229c4f0, p, 8, 0x120, 0x120, 0x17f);
    func_02002d14((unsigned int) data_ov142_0229c508, p, 8, 4, 4, 9);
}
