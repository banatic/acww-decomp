/* func_ov129_0229cfc8 @ 0x0229cfc8, 0x40 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern void func_ov127_02299bbc(void *p, unsigned char c);
extern void func_ov002_02208098(void *p, int n);
extern void func_ov127_02299c08(void *p, unsigned char c, int n);

void func_ov129_0229cfc8(void *self)
{
    if (data_021fbdd8 == 0) {
        func_ov127_02299bbc((char *) self + 0x734, *(unsigned char *) ((char *) self + 0xad));
        func_ov002_02208098(self, 2);
    } else {
        func_ov127_02299c08((char *) self + 0x734, *(unsigned char *) ((char *) self + 0xad), 0);
    }
}
