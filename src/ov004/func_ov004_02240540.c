/* func_ov004_02240540 @ 0x02240540, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02240f2c(void *self, int a, int b, int c, int d, int e, int f);
extern int func_0209d088(void *p);
extern void NNS_G3dMdlSetMdlAlpha(int x, int a, int b);
extern void func_ov004_02241008(void *self, int *u, int *v);

void func_ov004_02240540(void *self)
{
    int u[2], v[2];

    func_ov004_02240f2c(self, 0xc8, 0x3c, 0, 0, 0, 0);
    NNS_G3dMdlSetMdlAlpha(func_0209d088((char *) self + 0x288), 0, 0);
    u[0] = 0xa6;
    u[1] = 0x106;
    v[0] = 0xfc;
    v[1] = 0x150;
    func_ov004_02241008(self, u, v);
}
