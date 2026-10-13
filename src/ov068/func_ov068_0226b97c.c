/* func_ov068_0226b97c @ 0x0226b97c, 0x94 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_0226cfd4(int);
extern void func_ov068_02266c34(int, int, int, int, int, int, int, int, int);
extern void func_02019d0c(int, int, int, int, int, int, int, int, int, int, int);
extern void func_0202e194(int);
extern void func_0201cbbc(int);
extern int data_020c814c;
extern unsigned short data_020c80f8;

extern unsigned char data_021fbee8[];

int func_ov068_0226b97c(int unused, int obj)
{
    func_ov068_0226cfd4(obj);
    func_ov068_02266c34(obj + 0x898, obj, 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    func_02019d0c(obj + 0x564, 3, 2, 0, 0, 0, 0xffff8000, 0, 0, data_020c80f8, 0);
    *(int *) (obj + 0x4e8) |= 2;
    func_0202e194(obj);
    func_0201cbbc(obj + 0x83c);
    return 1;
}
