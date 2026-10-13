/* func_ov100_0229df98 @ 0x0229df98, 0x100 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov100_0229ce58(void *self);
extern void func_ov100_0229d04c(void *self);
extern int func_ov100_0229d550(void *self, int p, int extra, int zero);
extern int func_ov100_0229c2c0(void *self, int a);
extern int func_ov100_0229d620(void *self, int a);
extern int func_ov100_0229d630(void *self, int a);
extern int func_ov100_0229d118(void *self, int a);
extern int func_ov100_0229d194(void *self, int a);
extern int func_ov100_0229d4f4(void *self, int a);
extern void func_ov100_0229d6d8(void *self, int a, int b);
extern void func_ov100_0229d8b0(void *self);
extern void func_ov100_0229d014(void *self, int a);
extern void func_ov094_022999d8(void);
extern unsigned char data_021fbdd8;

void func_ov100_0229df98(void *self)
{
    int extra, p2, state;

    func_ov100_0229ce58(self);
    func_ov100_0229d04c(self);

    extra = *(int *) ((char *) self + 0x28d8) + 8;
    p2 = *(int *) ((char *) self + 0x28d4) + 8;
    state = func_ov100_0229d550(self, p2, extra, 0);

    if (!func_ov100_0229c2c0(self, 0x200)) {
        goto far;
    }
    if (func_ov100_0229d620(self, state) && func_ov100_0229d630(self, *(unsigned char *) ((char *) self + 0x2920))) {
        goto l2;
    }
    if (!func_ov100_0229d630(self, state)) {
        goto far;
    }
    if (!func_ov100_0229d620(self, *(unsigned char *) ((char *) self + 0x2920))) {
        goto far;
    }
l2:
    if (func_ov100_0229d118(self, state) == 0xfff1) {
        goto far;
    }
    state = 0x20;
far:
    if (state == 0x20) {
        goto bigend;
    }
    if (data_021fbdd8 != 0) {
        goto elsebranch;
    }
    if (func_ov100_0229d194(self, state)) {
        func_ov100_0229d6d8(self, *(unsigned char *) ((char *) self + 0x2920), extra);
        goto end;
    } else {
        if (func_ov100_0229d4f4(self, state)) {
            goto extblock;
        }
        func_ov100_0229d6d8(self, *(unsigned char *) ((char *) self + 0x2920), extra);
        goto end;
    extblock:
        func_ov094_022999d8();
        func_ov100_0229d8b0(self);
        goto end;
    }
elsebranch:
    func_ov100_0229d014(self, state);
    goto end;
bigend:
    if (data_021fbdd8 != 0) {
        goto end;
    }
    func_ov100_0229d6d8(self, *(unsigned char *) ((char *) self + 0x2920), extra);
end:
    return;
}
