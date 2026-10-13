/* func_ov068_0226906c @ 0x0226906c, 0x88 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c2c8(void *a, int b);
extern void func_ov068_0226cfd4(void *a);
extern void func_02019d0c(void *a, int b1, int b2, int b3, int b4, int b5, int b6, int b7, int b8, int b9, int b10);
extern void func_ov068_02266c34(void *a, void *b, int c, int d, int e, void *f, int g, int h, int i);
extern void func_0202e188(void *a);
extern void func_0201cbc4(void *a);
extern unsigned short data_020c80f8;
extern int data_020c814c;

extern unsigned char data_021fbee8[];

int func_ov068_0226906c(int unused, void *obj)
{
    int val = func_0201c2c8(obj, 4);
    func_ov068_0226cfd4(obj);
    func_02019d0c((char *) obj + 0x564, 3, 1, 0, 0, 0, val, 0, 0, data_020c80f8, 0);
    func_ov068_02266c34((char *) obj + 0x898, obj, 1, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    func_0202e188(obj);
    func_0201cbc4((char *) obj + 0x83c);
    return 1;
}
