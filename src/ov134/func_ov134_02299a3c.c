/* func_ov134_02299a3c @ 0x02299a3c, 0x22 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_02299a00(void *);
extern int _s32_div_f(int, int);

void func_ov134_02299a3c(void *self)
{
    int r0;
    int r1;

    r0 = *(int *) self;
    r0 = r0 << 7;
    r1 = *(int *) ((char *) self + 0x8c);
    r0 = _s32_div_f(r0, r1);
    r0 += 0x20;
    *(int *) ((char *) self + 0x64) = r0;
    func_ov134_02299a00(self);
}
