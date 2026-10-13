/* func_ov146_02299b1c @ 0x02299b1c, 0x3c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov146_02299dec(void *, int);
extern int _s32_div_f(void *, int);

void func_ov146_02299b1c(void *self)
{
    int r0;
    int r4;
    int r5;
    int temp;

    r5 = (int) self;
    r0 = *(int *) (r5 + 0x98);
    r0 = r0 * 0x1a0;
    r4 = _s32_div_f((void *) r0, 0x50);
    if (r4 < 0) {
        r4 = 0;
    }
    if (r4 > 0x1a0) {
        r4 = 0x1a0;
    }
    func_ov146_02299dec((void *) r5, r4);
    *(int *) (r5 + 0xa8) = r4;
}
