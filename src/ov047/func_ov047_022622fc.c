/* func_ov047_022622fc @ 0x022622fc, 0x64 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void func_02019c20(char *p, int a, int b, int c, int d, int e);
extern void func_0201ad18(char *p, int a, int b, int c, int d, int e, int f, int g);
extern int data_020c814c;

extern unsigned char data_021fbee8[];

int func_ov047_022622fc(char *p)
{
    func_02019c20(p + 0x564, 1, 0xf0, 0, *(unsigned short *) (p + 0x738), 0);
    *(unsigned char *) (p + 0x736) = 1;
    func_0201ad18(p + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    return 1;
}
