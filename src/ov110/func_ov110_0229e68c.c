/* func_ov110_0229e68c @ 0x0229e68c, 0x8c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov110_0229e1cc(void *p);
extern void func_ov094_0229ad20(void *p);
extern void func_ov094_0229ace4(void *p, void *q);
extern void func_ov110_0229d17c(void *p);
extern void func_ov094_0229b2b0(void *p);
extern void func_ov094_0229b794(void *p, int n);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int n);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov002_02208090(void *p, int a);
extern void func_ov110_0229c2b8(void *p, int a);
extern int func_ov002_02207f60(void *p);

void func_ov110_0229e68c(void *self)
{
    func_ov110_0229e1cc(self);
    func_ov094_0229ad20((char *) self + 0x138);
    func_ov094_0229ace4((char *) self + 0x138, (char *) self + 0xb0);
    func_ov110_0229d17c(self);
    func_ov094_0229b2b0((char *) self + 0xb98);
    func_ov094_0229b794((char *) self + 0xb98, 0xf);
    func_ov002_02207f20(self, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02208090(self, 2);
    func_ov110_0229c2b8(self, 1);
    func_ov110_0229c2b8(self, 2);
    *(int *) ((char *) self + 0x98) = func_ov002_02207f60(self);
}
