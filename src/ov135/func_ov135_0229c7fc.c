/* func_ov135_0229c7fc @ 0x0229c7fc, 0x5c bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov135_0229c7a8(void *self);
extern int func_ov135_0229c754(void *self);
extern int func_ov135_0229c574(void *self, int a);
extern void func_ov135_0229c66c(void *self);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int a);

void func_ov135_0229c7fc(void *self)
{
    int v1, v2, b;
    v1 = func_ov135_0229c7a8(self);
    v2 = func_ov135_0229c754(self);
    func_ov002_0220a0b4((char *) self + 0x98, v1, v2);
    if (func_ov135_0229c574(self, 2) != 0) {
        goto call1;
    }
    b = ((unsigned char *) self)[0x95];
    if (b == 5) {
        goto call7;
    }
    if (b == 6) {
        goto call7;
    }
call1:
    func_ov002_0220a374((char *) self + 0x98, 1);
    goto end;
call7:
    func_ov002_0220a374((char *) self + 0x98, 7);
end:
    func_ov135_0229c66c(self);
}
