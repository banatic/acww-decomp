/* func_ov004_02242fe8 @ 0x02242fe8, 0x5e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02244764(void *self);
extern void func_020550e4(void *p, int k);

int func_ov004_02242fe8(void *self)
{
    unsigned char *s;
    int k;

    s = (unsigned char *) ((char *) self + 0x50);
    k = *s;
    func_ov004_02244764(self);
    if (*(short *) ((char *) self + 0x9c) < *(short *) ((char *) self + 0x9e) && k < 2) {
        func_020550e4((char *) self + 0xb0, 1);
    } else {
        if (k == 0) {
            *((char *) self + 0x50) = 0x3c;
        } else if (k > 1) {
            *((char *) self + 0x50) = (char) (k - 1);
        }
        func_020550e4((char *) self + 0xb0, 0);
        return 0;
    }
    return 1;
}
