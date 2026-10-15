/* func_ov132_0229b630 @ 0x0229b630, 0x5a bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov132_0229b4c0(void);
extern void func_ov132_0229b3d8(void *self);
extern void func_ov132_0229b3cc(void);
extern void func_ov002_02207f20(void *self, int a, int b, int c, int d);
extern void func_02002708(int a);
extern void func_ov132_0229b578(void *self);
extern void func_ov132_0229ad60(void *self, int a);
extern int func_ov002_0220ab84(void *self, int a);
extern void func_ov002_02208090(void *self, int a);

void func_ov132_0229b630(void *self)
{
    func_ov132_0229b4c0();
    func_ov132_0229b3d8(self);
    asm {
        mov r0, self
    }
    func_ov132_0229b3cc();
    func_ov002_02207f20(self, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov132_0229b578(self);
    func_ov132_0229ad60(self, 1);
    func_ov002_0220ab84((char *) self + 0xf8, 0x65);
    func_ov002_02208090(self, 1);
}
