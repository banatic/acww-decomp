/* func_020833c0 @ 0x020833c0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205db4c(unsigned char *, unsigned char);

void func_020833c0(unsigned char *r4, unsigned char argument1)
{
    func_0205db4c(r4 + 1, (unsigned char) argument1);
    *r4 = 1;
}
