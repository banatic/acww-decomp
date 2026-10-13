/* func_ov122_022a1110 @ 0x022a1110, 0x5c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229cce0(void *p);
extern int func_ov095_0229c54c(void *p, unsigned char a, unsigned char b);
extern int func_ov095_0229c448(void *p, int v, int n);
extern int func_ov122_022a0be4(void *self, int v);
extern void func_ov095_0229c8e4(void *p, int v);
extern void func_ov095_0229bf3c(void *p);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

int func_ov122_022a1110(unsigned char *self)
{
    int r4, r6;

    func_ov095_0229cce0(self + 0xc0);

    r4 = func_ov095_0229c54c(self + 0xc0, data_021f6c58, data_021f6c54);

    if (r4 == -1) {
        return 0;
    }

    r6 = func_ov122_022a0be4(self, func_ov095_0229c448(self + 0xc0, r4, 9));
    func_ov095_0229c8e4(self + 0xc0, r4);
    self += 0xc0;
    func_ov095_0229bf3c(self);

    return r6;
}
