/* func_ov068_022690f8 @ 0x022690f8, 0x30 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_0226cfd4(int);
extern int func_02019c6c(void *, int, unsigned short);
extern void func_0202e194(int);
extern unsigned short data_020c80f8;

int func_ov068_022690f8(int p1, int p2)
{
    func_ov068_0226cfd4(p2);
    func_02019c6c((void *) (p2 + 0x564), 2, data_020c80f8);
    func_0202e194(p2);
    return 1;
}
