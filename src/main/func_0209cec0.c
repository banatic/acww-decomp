/* func_0209cec0 @ 0x0209cec0, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209cf80(void *self);
extern void func_0209c5b0(void *self, int val);
extern int func_0209c618(void *self);
extern int func_0209c80c(void *self);
extern int func_0209c988(void *self, int arg);
extern int func_0209ccd4(void *self);
extern int func_0209cc84(void *self);
extern unsigned int func_0209ce34(void *self);
extern void func_0209cf70(void *self);

int func_0209cec0(void *self, int arg2)
{
    int r4;
    int r6;
    int r7;

    r4 = 0;
    func_0209cf80(self);
    r7 = ~r4;
    goto outer_test;

outer_body:
    func_0209c5b0(self, r7);
    r4 = (func_0209c618(self) & 1) ? 1 : 0;
    r4 = (r4 & func_0209c80c(self)) ? 1 : 0;
    r4 = (r4 & func_0209c988(self, arg2)) ? 1 : 0;
    if (r4 == 0) {
        goto outer_test;
    }

    r6 = 0;
    goto inner_test;

inner_body:
    r6 = (func_0209ccd4(self) & 1) ? 1 : 0;
    r6 = (r6 & func_0209cc84(self)) ? 1 : 0;
    if (func_0209ce34(self) > 0x1ffb8u) {
        r4 = 0;
    }

inner_test:
    if (r6 == 0) {
        goto inner_body;
    }

outer_test:
    if (r4 == 0) {
        goto outer_body;
    }

    func_0209cf70(self);
    return 1;
}
