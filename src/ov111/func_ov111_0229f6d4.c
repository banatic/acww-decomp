/* func_ov111_0229f6d4 @ 0x0229f6d4, 0x5c bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229cce0(void *self);
extern int func_ov095_0229c54c(void *self, unsigned char a, unsigned char b);
extern int func_ov095_0229c448(void *self, int a, int b);
extern int func_ov111_0229f730(void *self, int a);
extern void func_ov095_0229c8e4(void *self, int a);
extern void func_ov095_0229bf3c(void *self);

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

int func_ov111_0229f6d4(void *self)
{
    int r4, r6;
    void *p;

    p = (char *) self + 0xac;
    func_ov095_0229cce0(p);

    r4 = func_ov095_0229c54c((char *) self + 0xac, data_021f6c58, data_021f6c54);

    if (r4 != -1) {
        r6 = func_ov111_0229f730(self, func_ov095_0229c448((char *) self + 0xac, r4, 9));
        func_ov095_0229c8e4((char *) self + 0xac, r4);
        func_ov095_0229bf3c((char *) self + 0xac);
        return r6;
    }
    return 0;
}
