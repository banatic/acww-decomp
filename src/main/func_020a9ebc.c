/* func_020a9ebc @ 0x020a9ebc, 0xe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020aad9c(char *);
extern int func_020aad3c(char *);
extern void func_020abd68(char *, int, int);
extern void func_020abd5c(char *, int);
extern int func_020aae88(char *);
extern int func_020aae78(char *);
extern int func_020abcc0(char *);
extern int func_020aad8c(char *);
extern int func_020abccc(char *);
extern void func_020abcb4(char *);
extern int func_020aad5c(char *);
extern void func_020abca8(char *);
extern void func_020abc9c(char *);
extern int func_020aad7c(char *);
extern int func_020abce4(char *);
extern void func_020abc90(char *);
extern void func_020abdc0(char *);
extern void func_020aae30(char *);
extern void func_020a9e8c(char *);
extern void func_020abc84(char *);

void func_020a9ebc(char *self)
{
    int r5, r0, cond;

    func_020aad9c(self + 0x154);
    cond = (func_020aad3c(self + 0x154) == 0);
    func_020abd68(self + 0xc, cond, 1);
    func_020abd5c(self + 0xc, func_020aae88(self + 0x154));
    r5 = func_020aae78(self + 0x154);
    r0 = func_020abcc0(self + 0xc);
    if (r5 < 0) {
        goto L_neg;
    }
    if (r0 != 0xb) {
        goto L_not11;
    }
    func_020abdc0(self + 0xc);
    func_020aae30(self + 0x154);
    func_020a9e8c(self);
    goto L_exit;
L_not11:
    func_020abc84(self + 0xc);
    goto L_exit;
L_neg:
    if (func_020aad8c(self + 0x154) == 0) {
        goto L_neg0;
    }
    if (func_020abccc(self + 0xc) != 0) {
        func_020abcb4(self + 0xc);
        goto L_exit;
    }
    if (func_020aad5c(self + 0x154) != 0) {
        func_020abca8(self + 0xc);
        goto L_exit;
    }
    func_020abc9c(self + 0xc);
    goto L_exit;
L_neg0:
    if (func_020aad7c(self + 0x154) != 0 && func_020abce4(self + 0xc) != 0) {
        func_020abc90(self + 0xc);
    }
L_exit:
    return;
}
