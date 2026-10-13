/* func_ov106_0229ee44 @ 0x0229ee44, 0x70 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov106_0229e860(char *p);
extern void func_ov094_0229ad20(void *p);
extern void func_ov094_0229b2b0(void *p);
extern void func_ov094_0229b274(int a, int b);
extern void func_ov106_0229d104(void *p);
extern void func_ov002_02207f20(void *a, int b, int c, int d, int e);
extern void func_02002708(int a);
extern void func_ov002_02208090(void *p, int n);
extern void func_ov106_0229c354(void *p, int b);
extern void func_ov106_0229eafc(void *p);

void func_ov106_0229ee44(char *self)
{
    func_ov106_0229e860(self);
    func_ov094_0229ad20(self + 0xf8);
    func_ov094_0229b2b0(self + 0x0b58);
    func_ov094_0229b274((int) (self + 0x0b58), (int) (self + 0x2bb4));
    func_ov106_0229d104(self);
    func_ov002_02207f20(self, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02208090(self, 2);
    func_ov106_0229c354(self, 1);
    func_ov106_0229c354(self, 2);
    func_ov106_0229eafc(self);
}
