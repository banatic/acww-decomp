/* func_ov121_0229a0e0 @ 0x0229a0e0, 0x28 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a374(void *p, int n);
extern void func_ov121_02299a4c(void *p, int n);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov121_0229a0e0(void *self)
{
    func_ov002_0220a374((char *) self + 0x3a8, 5);
    func_ov121_02299a4c(self, 0x80);
    func_ov002_02208098(self, 0xb);
}
