/* func_ov143_02299768 @ 0x02299768, 0x48 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov143_02299a64(int);
extern void func_0207094c(int, int);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);

struct UnkStruct_02299768 {
    unsigned int value : 10;
};

extern struct UnkStruct_02299768 *data_ov143_0229b178[];

void func_ov143_02299768(int a0, int a1, int a2)
{
    struct UnkStruct_02299768 *p;
    int ret;
    p = data_ov143_0229b178[a2];
    ret = func_ov143_02299a64(a0);
    func_0207094c(ret, a1);
    func_02070adc(ret, 8, p[1].value, 3, 15, 0, 0);
    func_02070a04(ret, 1, 0);
}
