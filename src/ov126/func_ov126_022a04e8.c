/* func_ov126_022a04e8 @ 0x022a04e8, 0x64 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229cce0(void *p);
extern int func_ov095_0229c54c(void *p, unsigned char a, unsigned char b);
extern void *func_ov095_0229c448(void *p, int idx, int n);
extern int func_ov095_0229c8e4(void *p, int idx);
extern void func_ov095_0229bf3c(void *p);
extern int func_ov126_022a03dc(void *p, void *q);

extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;

int func_ov126_022a04e8(void *self)
{
    int idx;
    int ret;
    func_ov095_0229cce0((char *) self + 0x19c);
    idx = func_ov095_0229c54c((char *) self + 0x19c, data_021f6c58, data_021f6c54);
    if (idx == -1) {
        return 0;
    }
    ret = func_ov126_022a03dc(self, func_ov095_0229c448((char *) self + 0x19c, idx, 9));
    func_ov095_0229c8e4((char *) self + 0x19c, idx);
    func_ov095_0229bf3c((char *) self + 0x19c);
    return ret;
}
