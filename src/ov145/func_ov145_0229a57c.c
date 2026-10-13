/* func_ov145_0229a57c @ 0x0229a57c, 0x34 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern int func_ov145_0229a220(int a, int b, int c);
extern void func_ov145_0229a210(void);
extern int func_ov002_02208098(int a, int b);

int func_ov145_0229a57c(int param)
{
    if (data_021fbdd8 != 0) {
        return func_ov145_0229a220(param, data_021f6c54, 0);
    } else {
        func_ov145_0229a210();
        return func_ov002_02208098(param, 0);
    }
}
