/* func_ov074_022791e0 @ 0x022791e0, 0x50 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(char *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern void func_02013c04(char *a);

int func_ov074_022791e0(char *self)
{
    func_02019d0c(self + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    self[0x651] = 0;
    func_02013c04(self + 0x558);
    return 1;
}
