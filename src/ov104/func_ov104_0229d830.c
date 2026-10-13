/* func_ov104_0229d830 @ 0x0229d830, 0x28 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229a898(void *dst, int val, int size);
extern void func_ov094_0229b794(void *dst, int val);

void func_ov104_0229d830(void *self)
{
    func_ov094_0229a898((char *) self + 0x2f8, 0, 0xe);
    func_ov094_0229b794((char *) self + 0xd58, 0xe);
}
