/* func_ov143_02299ad4 @ 0x02299ad4, 0x30 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov143_02299b70(void *p, int x);
extern void func_ov143_0229a014(void *p);
extern void func_ov002_02208090(void *p, int x);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_ov002_02207e9c(void *p, int x, int y);

void func_ov143_02299ad4(void *p)
{
    int zero;

    func_ov143_02299b70(p, 6);
    func_ov143_0229a014(p);
    func_ov002_02208090(p, 4);
    func_ov002_022080a0(p, 1);
    zero = 0;
    func_ov002_02207e9c(p, zero, zero);
}
