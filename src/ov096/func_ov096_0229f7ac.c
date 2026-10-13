/* func_ov096_0229f7ac @ 0x0229f7ac, 0x34 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(unsigned short, unsigned short);
extern int func_ov096_0229f800(unsigned short, unsigned short);

unsigned char func_ov096_0229f7ac(unsigned short a, unsigned short b)
{
    if (func_ov096_0229f830(a, b)) {
        return b;
    }
    if (func_ov096_0229f800(a, b)) {
        return b - 4;
    }
    return 0;
}
