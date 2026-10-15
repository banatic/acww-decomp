/* func_ov068_022674b0 @ 0x022674b0, 0xa8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_0226cfd4(void *);
extern void func_0201651c(void *, int);
extern void func_ov068_02266c34(void *, void *, int, int, int, void *, int, int, int);
extern void func_0202e188(void *);
extern void func_02013c0c(void *);
extern int func_0201c2c8(void *, int);
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern void func_0201cbbc(void *);

extern unsigned char data_021fbee8[];
extern unsigned int data_020c814c;
extern unsigned short data_020c80f8;

void func_ov068_022674b0(char *p1, char *p2)
{
    int res;

    func_ov068_0226cfd4(p2);
    func_0201651c((char *) p2 + 0x334, 0);
    func_ov068_02266c34((char *) p2 + 0x898, p2, 1, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    func_0202e188(p2);
    func_02013c0c((char *) p2 + 0x558);
    res = func_0201c2c8(p2, 4);
    func_02019d0c((char *) p2 + 0x564, 3, 1, 0, 0, 0, res, 0, 0, data_020c80f8, 0);
    func_0201cbbc((char *) p2 + 0x83c);
    p1[0x1c] = 0;
    p1[0xe0] = 1;
}
