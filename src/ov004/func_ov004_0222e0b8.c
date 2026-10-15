/* func_ov004_0222e0b8 @ 0x0222e0b8, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_022236a8(void);
extern unsigned short func_ov004_022236c4(void);
extern void func_ov004_0222db14(int unused, int kind, int object, int resource, unsigned char mode, int scale,
                                unsigned short first, unsigned short second);

void func_ov004_0222e0b8(char *self)
{
    // DECLS
    unsigned short v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_022236c4();
    v2 = func_ov004_022236a8();
    if (v2 == 0xf8) {
        func_ov004_0222db14((int) self, 0x7, (int) (self + 0x348), (int) (self + 0x9ac), 0x3, 0x1000, v1, 0x0);
        func_ov004_0222db14((int) self, 0x5, (int) (self + 0x400), (int) (self + 0xa50), 0x3, 0x1000, v1, 0x0);
    }
}
