/* func_ov112_022a0548 @ 0x022a0548, 0x68 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[];
extern int func_ov095_0229cf64(unsigned char *p, int a);
extern int func_ov112_022a03ac(unsigned char *p, int a);
extern void func_ov095_0229c8e4(unsigned char *p, int a);
extern unsigned char *func_ov002_02208098(unsigned char *p, unsigned char value);

int func_ov112_022a0548(unsigned char *self)
{
    if (!(data_021fbe40[1] & 0x200)) {
        return 0;
    }

    if (func_ov095_0229cf64(self + 0x384, 11) != 0) {
        return 0;
    }

    func_ov112_022a03ac(self, 0x118);
    func_ov095_0229c8e4(self + 0x384, 0x109);
    *(self + 0xc1) = *(self + 0x8d);
    func_ov002_02208098(self, 14);
    return 1;
}
