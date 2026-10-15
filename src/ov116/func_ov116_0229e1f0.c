/* func_ov116_0229e1f0 @ 0x0229e1f0, 0x38 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c58;

extern void func_ov114_0229d32c(char *p, unsigned char b);
extern void func_ov114_0229d304(char *p);
extern unsigned char *func_ov002_02208098(char *p, unsigned char value);

void func_ov116_0229e1f0(char *arg)
{
    if (data_021fbdd8) {
        func_ov114_0229d32c(arg + 0xf8, data_021f6c58);
    } else {
        func_ov114_0229d304(arg + 0xf8);
        func_ov002_02208098(arg, 0);
    }
}
