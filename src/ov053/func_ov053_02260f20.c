/* func_ov053_02260f20 @ 0x02260f20, 0x74 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020c814c;
extern unsigned short data_020c80f8;
extern char data_021fbee8;

extern void func_0201ad18(char *p, int a, int b, int c, int d, int e, int f, int g);
extern void func_02019d0c(char *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

int func_ov053_02260f20(char *param)
{
    func_0201ad18(param + 0x3b0, 0, 0, 0, (int) &data_021fbee8, 4, data_020c814c, 1);
    *((unsigned char *) (param + 0x719)) = 0;
    func_02019d0c(param + 0x564, 3, 1, 0, 0, 0, 0x4000, 0, 0, data_020c80f8, 0);
    return 1;
}
