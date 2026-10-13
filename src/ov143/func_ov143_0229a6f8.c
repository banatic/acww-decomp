/* func_ov143_0229a6f8 @ 0x0229a6f8, 0x74 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov143_0229a2e0(void *self);
extern int _s32_div_f(int diff, int b);
extern unsigned char func_ov143_022997b0(void *self, unsigned char clamp);
extern void func_0206e9ac(void);

void func_ov143_0229a6f8(unsigned char *self)
{
    int diff, r1;
    unsigned char idx;
    unsigned char *base;
    unsigned char old, cur;

    if (data_021fbdd8 == 0) {
        func_ov143_0229a2e0(self);
        return;
    }

    diff = *(int *) (self + 0xa8) - data_021f6c54;
    r1 = self[0xa5] + _s32_div_f(diff, 3);
    if (r1 < 0) {
        r1 = 0;
    } else if (r1 > 0xf) {
        r1 = 0xf;
    }

    idx = self[0xa4];
    base = *(unsigned char **) (self + 0xa0);
    old = base[idx];

    cur = func_ov143_022997b0(self, (unsigned char) r1);
    if (old == cur) {
        return;
    }

    func_0206e9ac();
    base = *(unsigned char **) (self + 0xa0);
    base[idx] = cur;
}
