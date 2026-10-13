/* func_ov120_0229ac8c @ 0x0229ac8c, 0x68 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned char *func_ov120_0229b188(int);
extern const unsigned char data_ov120_0229c508[];

unsigned char func_ov120_0229ac8c(int a, unsigned int b)
{
    unsigned char r1;
    const unsigned char *p;
    if (b >= 1 && b < 15) {
        return (unsigned char) (b - 1);
    }
    if (b >= 15 && b < 28) {
        p = func_ov120_0229b188(a);
        r1 = p[b - 15];
        if (r1 == 0) {
            return 14;
        }
        if (r1 == 1 || (r1 >= 2 && r1 < 6)) {
            return 8;
        }
        if (r1 >= 6 && r1 < 14) {
            return (unsigned char) (r1 - 6);
        }
        if (r1 >= 14 && r1 < 19) {
            return data_ov120_0229c508[r1 - 14];
        }
    }
    return 14;
}
