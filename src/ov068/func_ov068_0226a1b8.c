/* func_ov068_0226a1b8 @ 0x0226a1b8, 0xa8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0201ce50(void *);
extern void *func_0201c314(void *, void *);
extern void func_ov068_0226cfd4(void *);
extern int func_02019d0c(void *, int, int, int, int, int, void *, int, int, unsigned short, int);
extern void func_ov068_02266c34(void *, void *, int, int, void *, void *, int, int, int);
extern void func_0202e188(void *);
extern void func_ov068_0226ad78(void *, void *, int, int, int);
extern void func_0201cbc4(void *);
extern unsigned short data_020c80f8;
extern int data_020c814c;
extern unsigned char data_021fbee8;

int func_ov068_0226a1b8(void *p1, void *p2)
{
    void *r7;
    void *r6;

    r7 = func_0201ce50(p2);
    r6 = func_0201c314(p2, r7);
    func_ov068_0226cfd4(p2);
    func_02019d0c((char *) p2 + 0x564, 3, 1, 0, 0, 0, r6, 0, 0, data_020c80f8, 0);
    func_ov068_02266c34((char *) p2 + 0x898, p2, 2, 0, r7, (void *) &data_021fbee8, 4, data_020c814c, 1);
    ((char *) p1)[0x1c] = 0;
    func_0202e188(p2);
    func_ov068_0226ad78(p1, p2, 0, 0, 1);
    func_0201cbc4((char *) p2 + 0x83c);
    return 1;
}
