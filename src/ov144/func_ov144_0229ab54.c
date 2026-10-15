/* func_ov144_0229ab54 @ 0x0229ab54, 0x34 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov144_0229a4c8(int a, unsigned char b, int c);
extern int func_ov144_0229a4b8(int arg0);
extern unsigned char *func_ov002_02208098(int a, unsigned char value);

void func_ov144_0229ab54(int param)
{
    if (data_021fbdd8) {
        func_ov144_0229a4c8(param, data_021f6c54, 0);
    } else {
        func_ov144_0229a4b8(param);
        func_ov002_02208098(param, 0);
    }
}
