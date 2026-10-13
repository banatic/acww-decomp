/* func_ov101_0229c2c0 @ 0x0229c2c0, 0x70 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov101_0229c28c(unsigned char *, int);
extern int func_ov101_0229ce38(unsigned char *, unsigned char);
extern void func_ov101_0229c330(unsigned char *, int);
extern int func_ov002_022088cc(int);
extern void func_ov002_0220a2b4(unsigned char *);

int func_ov101_0229c2c0(unsigned char *p, int param1)
{
    unsigned char b = p[0xb3];
    func_ov101_0229c28c(p, 0x18);
    if (param1 == 0) {
        return 0;
    }
    if (func_ov101_0229ce38(p, p[0xb3]) != 0) {
        func_ov101_0229c330(p, param1);
    } else {
        if (p[0xb3] == 0xf) {
            if (func_ov002_022088cc(param1) != 0) {
                p[0xb3] = 0xe;
                func_ov002_0220a2b4(p + 0x229c);
            }
        }
    }
    if (b == p[0xb3]) {
        return 0;
    }
    return 1;
}
