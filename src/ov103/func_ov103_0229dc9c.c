/* func_ov103_0229dc9c @ 0x0229dc9c, 0x74 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov103_0229d890(char *self);
extern void func_ov094_0229ad20(char *ptr);
extern void func_ov094_0229b2b0(char *ptr);
extern void func_ov103_0229cc70(char *self);
extern void func_ov002_02207f20(char *self, int a, int b, int c, int d);
extern void func_02002708(int a);
extern void func_ov002_02207e80(char *self, int a, int b, int c);
extern void func_ov002_02208090(char *self, int a);
extern void func_ov103_0229c2e4(char *self, int a);
extern int func_ov002_02207f60(char *self);

void func_ov103_0229dc9c(char *self)
{
    func_ov103_0229d890(self);
    func_ov094_0229ad20(self + 0xcc);
    func_ov094_0229b2b0(self + 0xb2c);
    func_ov103_0229cc70(self);
    func_ov002_02207f20(self, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02208090(self, 2);
    func_ov103_0229c2e4(self, 1);
    func_ov103_0229c2e4(self, 2);
    *(unsigned int *) (self + 0x2b8c) = func_ov002_02207f60(self);
}
