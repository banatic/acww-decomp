/* func_ov066_02266800 @ 0x02266800, 0x24 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov066_02266824(unsigned char *);

void func_ov066_02266800(unsigned char a, unsigned char b)
{
    unsigned char buf[2];
    buf[0] = a;
    buf[1] = b;
    func_ov066_02266824(buf);
}
