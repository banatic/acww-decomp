/* func_ov112_022a0710 @ 0x022a0710, 0x58 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_02299a00(void *self);
extern int func_ov095_0229c448(void *p, int r, int n);
extern void func_ov095_0229c8e4(void *p, int r);
extern void func_ov112_0229f29c(void *self);

typedef struct {
    unsigned short pad_00;
    unsigned short flag;
} Reg;

extern unsigned char data_021fbe40[];

int func_ov112_022a0710(void *self)
{
    int r;
    volatile Reg *reg = (volatile Reg *) data_021fbe40;
    if ((reg->flag & 1) == 0) {
        return 0;
    }
    r = func_ov095_02299a00((char *) self + 0x384);
    if (r == -1) {
        return 0;
    }
    func_ov095_0229c448((char *) self + 0x384, r, 9);
    func_ov095_0229c8e4((char *) self + 0x384, r);
    func_ov112_0229f29c(self);
    return 1;
}
