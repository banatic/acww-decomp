/* func_ov122_022a0f78 @ 0x022a0f78, 0xb8 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov122_0229f980(void *self, int cmd);
extern void *func_ov095_0229bb9c(void *obj, void *value);
extern void *func_ov095_0229bb98(void *obj, void *value);
extern void *func_ov095_0229bb94(void *obj, void *value);
extern void *func_ov122_0229f5a0(void *self);
extern void *func_ov122_0229f5f8(void *self);
extern int func_ov122_0229f5c8(void *self);
extern int func_ov095_0229bba0(void *obj, void *a, void *b, void *c, int d, int e);
extern void func_ov122_022a15b8(void *self, int a, int b);
extern void func_ov122_0229f9a8(void *self);

int func_ov122_022a0f78(void *self, int cmd)
{
    void *r6;
    void *r4;
    void *r7;
    int x;

    r6 = func_ov122_0229f980(self, cmd);
    if (r6 == 0) {
        return 0;
    }

    switch (cmd) {
        case 0x103:
            r6 = func_ov095_0229bb9c((void *) ((char *) self + 0xc0), r6);
            break;
        case 0x104:
            r6 = func_ov095_0229bb98((void *) ((char *) self + 0xc0), r6);
            break;
        case 0x105:
            r6 = func_ov095_0229bb94((void *) ((char *) self + 0xc0), r6);
            break;
        default:
            break;
    }

    if (r6 == 0) {
        return 0;
    }

    r4 = func_ov122_0229f5a0(self);
    r7 = func_ov122_0229f5f8(self);
    x = func_ov122_0229f5c8(self);

    if (func_ov095_0229bba0((void *) ((char *) self + 0xc0), r7, r6, r4, x, 0x2710) == 0) {
        return 0;
    }

    func_ov122_022a15b8(self, 0, 1);
    func_ov122_0229f9a8(self);
    return 1;
}
