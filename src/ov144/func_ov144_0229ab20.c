/* func_ov144_0229ab20 @ 0x0229ab20, 0x34 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov144_0229a4b8(int a);
extern void func_ov144_0229a4c8(int a, int b, int c);
extern void func_ov002_02208098(int a, int b);

void func_ov144_0229ab20(int p)
{
    if (data_021fbdd8) {
        func_ov144_0229a4c8(p, data_021f6c54, 1);
    } else {
        func_ov144_0229a4b8(p);
        func_ov002_02208098(p, 0);
    }
}
