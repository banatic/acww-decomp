/* func_ov108_0229d620 @ 0x0229d620, 0x94 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov108_0229c96c(unsigned char *);
extern void func_ov108_0229cac8(unsigned char *);
extern int func_ov108_0229cd0c(unsigned char *, int, int, int);
extern int func_ov108_0229cb88(unsigned char *, int);
extern int func_ov108_0229ccc0(unsigned char *, int);
extern void func_ov108_0229ce00(unsigned char *, unsigned char, int);
extern void func_ov108_0229cf4c(unsigned char *);
extern void func_ov108_0229ca98(unsigned char *, int);
extern unsigned char data_021fbdd8;

void func_ov108_0229d620(unsigned char *self)
{
    int x;
    int y;

    func_ov108_0229c96c(self);
    func_ov108_0229cac8(self);
    x = func_ov108_0229cd0c(self, *(unsigned int *) (self + 0xa4) + 8, *(unsigned int *) (self + 0xa8) + 8, 0);

    if (x == 0x16) {
        goto x_eq;
    }

    if (data_021fbdd8 != 0) {
        goto flag_nonzero;
    }

    if (func_ov108_0229cb88(self, x) != 0) {
        goto call_ce00;
    }

    y = func_ov108_0229ccc0(self, x);
    if (y != 0) {
        goto ext_block;
    }

call_ce00:
    func_ov108_0229ce00(self, self[0x2af], 4);
    return;

ext_block:
    func_ov108_0229cf4c(self);
    return;

flag_nonzero:
    func_ov108_0229ca98(self, x);
    return;

x_eq:
    if (data_021fbdd8 != 0) {
        return;
    }
    func_ov108_0229ce00(self, self[0x2af], 4);
    return;
}
