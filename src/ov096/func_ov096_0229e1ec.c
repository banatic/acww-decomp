/* func_ov096_0229e1ec @ 0x0229e1ec, 0x6c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c878(void *);
extern int func_ov096_0229e0a8(void *, unsigned short);
extern void func_ov096_0229e6a0(void *);
extern void func_ov096_0229fb9c(void *);
extern void func_ov094_0229a99c(void *, unsigned short, unsigned char);
extern unsigned char *func_ov096_0229f90c(void *, unsigned char, int);

int func_ov096_0229e1ec(void *self)
{
    unsigned short tmp;
    int result;

    tmp = *(unsigned short *) ((char *) self + 0xac);
    func_0204c878(&tmp);
    result = func_ov096_0229e0a8(self, *(unsigned short *) ((char *) self + 0xac));
    if (result == 0xfff1) {
        func_ov096_0229e6a0(self);
        func_ov096_0229fb9c(self);
    } else {
        *(unsigned short *) ((char *) self + 0xac) = (unsigned short) result;
        func_ov094_0229a99c((char *) self + 0x358, *(unsigned short *) ((char *) self + 0xac),
                            *(unsigned char *) ((char *) self + 0xb0));
        func_ov096_0229f90c(self, *(unsigned char *) ((char *) self + 0xb4), 4);
    }
    return 1;
}
