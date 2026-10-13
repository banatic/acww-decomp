/* func_ov003_0222d6fc @ 0x0222d6fc, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df94(void *out);
extern int func_ov003_0222d6a8(void);
extern int func_ov003_0222d388(int a, int b, void *c);

int func_ov003_0222d6fc(void *self)
{
    unsigned char t[4];
    unsigned char m;
    func_0209df94(t);
    m = (unsigned char) (t[1] - 1);
    if (m > 0xb) {
        m = 0;
    }
    if (func_ov003_0222d388(m, func_ov003_0222d6a8(), self)) {
        return 1;
    }
    return 0;
}
