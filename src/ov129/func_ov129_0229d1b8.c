/* func_ov129_0229d1b8 @ 0x0229d1b8, 0x60 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov127_02299e64(void *addr);
extern int func_ov129_0229b7ec(void *self, int n);
extern void func_ov129_0229b7dc(void *self, int n);
extern void func_02004658(int v);
extern void func_ov129_0229b7cc(void *self, int n);
extern void func_02004644(int v, int n);

void func_ov129_0229d1b8(void *self)
{
    func_ov127_02299e64((char *) self + 0x734);
    if (func_ov129_0229b7ec(self, 0x40) != 0) {
        if (func_ov129_0229b7ec(self, 0x20) == 0) {
            func_ov129_0229b7dc(self, 0x20);
            func_02004658(0x883);
        }
    } else {
        if (func_ov129_0229b7ec(self, 0x20) != 0) {
            func_ov129_0229b7cc(self, 0x20);
            func_02004644(0x883, 1);
        }
    }
}
