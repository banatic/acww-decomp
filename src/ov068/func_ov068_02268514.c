/* func_ov068_02268514 @ 0x02268514, 0xbc bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_0226cfd4(void *self);
extern void func_02019c20(void *addr, int p1, int p2, int p3, unsigned short p4, int p5);
extern void func_ov068_02266c34(void *a, void *b, int c, int d, int e, char *f, int g, unsigned int h, int i);
extern void func_02012394(void *addr, unsigned short val, int p2);
extern void func_0202e194(void *self);
extern void func_02013c04(void *addr);
extern void func_0200442c(void *addr, int p1, int p2, int p3);
extern void func_0201cbbc(void *addr);

extern unsigned short data_020c80f8;
extern unsigned int data_020c814c;
extern char data_021fbee8;

int func_ov068_02268514(int unused, char *self)
{
    unsigned short r4;

    func_ov068_0226cfd4(self);
    r4 = data_020c80f8;
    func_02019c20(self + 0x564, 1, 0x127, 0, r4, 0);
    func_ov068_02266c34(self + 0x898, self, 0, 0, 0, &data_021fbee8, 4, data_020c814c, 1);
    func_02012394(self + 0x9b4, r4, 0);
    *(unsigned int *) (self + 0x4e8) |= 2;
    func_0202e194(self);
    func_02013c04(self + 0x558);
    func_0200442c(self + 0x514, 0x7ee, 0x7f, 0);
    func_0201cbbc(self + 0x83c);
    return 1;
}
