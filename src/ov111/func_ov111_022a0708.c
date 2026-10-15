/* func_ov111_022a0708 @ 0x022a0708, 0x54 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov095_0229bf0c(void *ptr);
extern int func_ov095_0229c548(void *ptr);
extern int func_ov095_0229c448(void *ptr, int a, int b);
extern void func_ov095_0229c8e4(void *ptr, int a);
extern int func_ov111_0229f730(void *self, int a);

void func_ov111_022a0708(void *self)
{
    int tmp;
    int r;

    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (self), 0);
        return;
    }
    if (func_ov095_0229bf0c((char *) self + 0xac) == 0) {
        return;
    }
    tmp = func_ov095_0229c548((char *) self + 0xac);
    r = func_ov095_0229c448((char *) self + 0xac, tmp, 9);
    func_ov111_0229f730(self, r);
    self = (char *) self + 0xac;
    func_ov095_0229c8e4(self, tmp);
}
