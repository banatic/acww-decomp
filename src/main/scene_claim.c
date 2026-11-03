/* scene_claim: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209d4c0 @ 0x0209d4c0, 0x5c bytes, Thumb
 * func_0209d498 @ 0x0209d498, 0x28 bytes, Thumb
 * func_0209d484 @ 0x0209d484, 0x14 bytes, Thumb
 */

extern unsigned int func_0209d8b0(unsigned char *a, unsigned char b, int c);
extern void func_0209d8e4(unsigned char *a, unsigned char b, int c);
extern void func_02073820(unsigned char *a);
extern void func_020737f0(unsigned char *a, unsigned char *b, int c);
extern void func_02073770(unsigned char *a, int b, int c);
extern unsigned char *data_020ccf94;
extern void func_0209d83c(void *data, int param);
extern unsigned char data_021dc6e8[];
extern void func_0209d8cc(unsigned char *ptr, unsigned char val, int arg);
extern unsigned char data_021dc70c[];

void func_0209d4c0(unsigned char *p, int idx)
{
    unsigned char c = p[0];
    unsigned char flag;
    unsigned char *base;

    if (func_0209d8b0(((unsigned char *) data_021dc70c), c, idx) <= 1) {
        func_0209d8e4(((unsigned char *) data_021dc70c), c, idx);
        flag = 1;
    } else {
        flag = 0;
    }

    base = data_020ccf94;
    func_02073820(base);
    func_020737f0(base, &flag, 1);
    func_02073770(base, 0x34, idx);
}

void func_0209d498(unsigned char *arg)
{
    if (*arg) {
        func_0209d83c((void *) data_021dc6e8, 2);
    } else {
        func_0209d83c((void *) data_021dc6e8, 1);
    }
}

void func_0209d484(const unsigned char *p, int arg1)
{
    func_0209d8cc((unsigned char *) data_021dc70c, *p, arg1);
}
