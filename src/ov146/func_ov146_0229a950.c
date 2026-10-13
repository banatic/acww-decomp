/* func_ov146_0229a950 @ 0x0229a950, 0x34 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov146_02299c44(int a, int b, int c);
extern void func_ov146_02299c34(void);
extern void func_ov002_02208098(int a, int b);

void func_ov146_0229a950(int param)
{
    if (data_021fbdd8 != 0) {
        func_ov146_02299c44(param, data_021f6c54, 1);
    } else {
        func_ov146_02299c34();
        func_ov002_02208098(param, 0);
    }
}
