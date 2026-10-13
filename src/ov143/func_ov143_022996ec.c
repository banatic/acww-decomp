/* func_ov143_022996ec @ 0x022996ec, 0x7c bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov143_02299768(int a0, int a1, int a2);
extern int func_ov143_02299a64(int a0);
extern void func_0207094c(int a0, int a1);
extern void func_02070adc(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
extern void func_02070a04(int a0, int a1, int a2);
struct UnkStruct_022996ec {
    unsigned int low10 : 10;
    unsigned int high22 : 22;
};
extern struct UnkStruct_022996ec data_ov143_0229afc0[];
void func_ov143_022996ec(int param)
{
    int i;
    unsigned char cur = 0xc7;
    unsigned char reset = 0xc3;
    i = 0;
    while (i < 13) {
        func_ov143_02299768(param, cur, i);
        cur = (unsigned char) (cur + 1);
        if (cur > 0xc9) {
            cur = reset;
        }
        i++;
    }

    func_ov143_02299768(param, 0xca, 0xd);
    func_ov143_02299768(param, 0xcb, 0xe);
    {
        int handle = func_ov143_02299a64(param);
        func_0207094c(handle, 0x8d);
        func_02070adc(handle, 8, data_ov143_0229afc0[1].low10, 8, 15, 0 & 0xFFFFFFFFFFFFFFFF, 0);
        func_02070a04(handle, 1, 0);
    }
}
