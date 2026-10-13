/* func_ov115_0229e1f0 @ 0x0229e1f0, 0x38 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c58;
extern void func_ov114_0229d32c(void *ptr, unsigned char val);
extern void func_ov114_0229d304(void *ptr);
extern void func_ov002_02208098(void *ptr, int val);

void func_ov115_0229e1f0(void *self)
{
    if (data_021fbdd8) {
        func_ov114_0229d32c((char *) self + 0xf8, data_021f6c58);
    } else {
        func_ov114_0229d304((char *) self + 0xf8);
        func_ov002_02208098(self, 0);
    }
}
