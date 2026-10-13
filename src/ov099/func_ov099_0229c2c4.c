/* func_ov099_0229c2c4 @ 0x0229c2c4, 0x48 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov099_0229c28c(unsigned char *p, int x);
extern int func_ov099_0229cf30(unsigned char *p, unsigned char x);
extern void func_ov099_0229c30c(unsigned char *p, int x);

int func_ov099_0229c2c4(unsigned char *p, int b)
{
    unsigned char v = p[0x2907];
    func_ov099_0229c28c(p, 0x30);
    if (b == 0) {
        return 0;
    }
    if (func_ov099_0229cf30(p, p[0x2907]) != 0) {
        func_ov099_0229c30c(p, b);
    }
    return (v == p[0x2907]) ? 0 : 1;
}
