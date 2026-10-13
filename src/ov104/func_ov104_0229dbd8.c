/* func_ov104_0229dbd8 @ 0x0229dbd8, 0x48 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(unsigned char *ptr, int x);
extern void func_ov094_022999c0(void);
extern void func_ov104_0229d4a8(unsigned char *self, int val);
extern void func_ov104_0229d528(unsigned char *self);

void func_ov104_0229dbd8(unsigned char *self, int val)
{
    self[0xb7] = val;
    func_ov002_02207d24(self + 0x23b8, 1);
    func_ov104_0229d4a8(self, val);
    if (self[0xb4] == 1) {
        self[0xbb] = 8;
    }
    func_ov104_0229d528(self);
    func_ov094_022999c0();
}
