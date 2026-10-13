/* func_ov004_02224bdc @ 0x02224bdc, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *self);
extern void func_0201c280(void *self, void *p);
extern void func_ov004_02224544(void *p, void *self);
extern void func_0201c3f4(void *self, int a);
extern void func_0203edf4(void *self, int a);
extern void func_0201af28(void *p, int a, int b, int c, int d);
extern void func_0201b38c(void *p, int a);
extern void func_0201b388(void *p, int a);
extern void func_0201b384(void *p, int a);

int func_ov004_02224bdc(char *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, self + 0x658);
    func_ov004_02224544(self + 0x658, self);
    func_0201c3f4(self, 0x100);
    func_0203edf4(self, 0x5000);
    func_0201af28(self + 0x350, 2, 0x166, 0xcc, 0x133);
    func_0201b38c(self + 0x2a0, 0xf2);
    func_0201b388(self + 0x2a0, 0xf4);
    func_0201b384(self + 0x2a0, 0xf4);
    return 1;
}
