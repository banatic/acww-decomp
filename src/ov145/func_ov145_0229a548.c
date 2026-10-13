/* func_ov145_0229a548 @ 0x0229a548, 0x34 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov145_0229a220(void *arg, unsigned char b, int c);
extern void func_ov145_0229a210(void *arg);
extern void func_ov002_02208098(void *arg, int c);

void func_ov145_0229a548(void *arg)
{
    if (data_021fbdd8 != 0) {
        func_ov145_0229a220(arg, data_021f6c54, 1);
    } else {
        func_ov145_0229a210(arg);
        func_ov002_02208098(arg, 0);
    }
}
