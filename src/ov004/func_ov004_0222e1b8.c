/* func_ov004_0222e1b8 @ 0x0222e1b8, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_022236a8(void);
extern unsigned short func_ov004_022236c4(void);
extern void func_ov004_0222db14(int argument0, int argument1, int argument2, int argument3, unsigned char argument4,
                                int argument5, unsigned short argument6, unsigned short argument7);

void func_ov004_0222e1b8(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    func_ov004_022236c4();
    v2 = func_ov004_022236a8();
    if (v2 == 0xf7) {
        func_ov004_0222db14((int) (self), (int) (0x5), (int) (self + 0x348), (int) (self + 0x9ac), (unsigned char) (0x0),
                            (int) (0x1000), (unsigned short) (0x0), (unsigned short) (0x0));
        func_ov004_0222db14((int) (self), (int) (0x3), (int) (self + 0x400), (int) (self + 0xa50), (unsigned char) (0x0),
                            (int) (0x1000), (unsigned short) (0x0), (unsigned short) (0x0));
    }
}
