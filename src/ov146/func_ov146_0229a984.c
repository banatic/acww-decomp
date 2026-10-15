/* func_ov146_0229a984 @ 0x0229a984, 0x34 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8; // 0x021fbdd8
extern unsigned char data_021f6c54; // 0x021f6c54
extern void func_ov146_02299c44(int, int, int);
extern void func_ov146_02299c34(int);
extern unsigned char *func_ov002_02208098(int, unsigned char value);

void func_ov146_0229a984(int arg)
{
    if (data_021fbdd8) {
        func_ov146_02299c44(arg, data_021f6c54, 0);
    } else {
        func_ov146_02299c34(arg);
        func_ov002_02208098(arg, 0);
    }
}
