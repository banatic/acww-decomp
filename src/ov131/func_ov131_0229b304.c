/* func_ov131_0229b304 @ 0x0229b304, 0x34 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern void func_ov130_0229a24c(void *p);
extern void func_ov002_02208098(void *p, int n);
extern void func_ov130_0229a224(void *p);

void func_ov131_0229b304(void *param)
{
    if (data_021fbdd8 == 0) {
        func_ov130_0229a24c((char *) param + 0x2c4);
        func_ov002_02208098(param, 0);
    } else {
        func_ov130_0229a224((char *) param + 0x2c4);
    }
}
