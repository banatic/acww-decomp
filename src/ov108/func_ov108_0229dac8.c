/* func_ov108_0229dac8 @ 0x0229dac8, 0x84 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov108_0229d82c(void *);
extern void func_ov002_0220ab84(void *, int);
extern void func_ov094_0229ad20(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov108_0229cbbc(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov108_0229c2cc(void *, int);
extern int func_ov002_02207f60(void *);

void func_ov108_0229dac8(char *self)
{
    func_ov108_0229d82c(self);
    func_ov002_0220ab84(self + 0x2a0c, 0x65);
    func_ov094_0229ad20(self + 0x2f0);
    func_ov094_0229b2b0(self + 0xd50);
    func_ov108_0229cbbc(self);
    func_ov002_02207f20(self, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(self, 6, 0, ~0xf);
    func_ov002_02208090(self, 2);
    func_ov108_0229c2cc(self, 1);
    func_ov108_0229c2cc(self, 2);
    *(int *) (self + 0x98) = func_ov002_02207f60(self);
}
