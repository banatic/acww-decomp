/* func_ov136_0229ccf4 @ 0x0229ccf4, 0x3c bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov134_02299af0(void *ptr, unsigned char val);
extern void func_ov134_02299a84(void *ptr);
extern void func_ov002_02208098(void *ptr, int val);

void func_ov136_0229ccf4(void *param)
{
    if (data_021fbdd8) {
        func_ov134_02299af0((char *) param + 0x2C4, data_021f6c54);
    } else {
        func_ov134_02299a84((char *) param + 0x2C4);
        func_ov002_02208098(param, 3);
    }
}
