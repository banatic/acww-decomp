/* func_ov101_0229c4e0 @ 0x0229c4e0, 0x3c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fc80(unsigned char);
extern void func_0206fc4c(int);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern int func_ov002_02207d24(void *, int);
extern void func_ov101_0229c844(void *);

void func_ov101_0229c4e0(void *self)
{
    unsigned char b = *(unsigned char *) ((char *) self + 0xb4);
    func_0206fc80(b);
    func_0206fc4c(1);
    *(unsigned char *) ((char *) self + 0x8c) = 3;
    func_ov002_022080a0(self, 1);
    func_ov002_02207d24((char *) self + 0x21b4, 1);
    func_ov101_0229c844(self);
}
