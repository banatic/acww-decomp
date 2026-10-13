/* func_ov068_02266cb0 @ 0x02266cb0, 0x3c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02266c34(int *, int, int, int, int, int, int, int, int);
extern int data_020c814c;

extern unsigned char data_021fbee8[];

void func_ov068_02266cb0(int *p, int something)
{
    func_ov068_02266c34(p, something, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    p[1] = 2;
    p[3] = -1;
    p[4] = -1;
}
