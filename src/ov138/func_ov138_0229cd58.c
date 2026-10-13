/* func_ov138_0229cd58 @ 0x0229cd58, 0x3c bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov134_02299af0(char *p, unsigned char b);
extern void func_ov134_02299a84(char *p);
extern void func_ov002_02208098(void *p, int n);

void func_ov138_0229cd58(char *param)
{
    if (data_021fbdd8) {
        func_ov134_02299af0(param + 0x2c8, data_021f6c54);
    } else {
        func_ov134_02299a84(param + 0x2c8);
        func_ov002_02208098(param, 1);
    }
}
