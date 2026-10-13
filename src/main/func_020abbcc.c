/* func_020abbcc @ 0x020abbcc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020abbb8(unsigned char *);
extern void func_020aba5c(unsigned char *);

void func_020abbcc(unsigned char *arg0)
{
    if (arg0[0x141] != 0) {
        func_020abbb8(arg0);
    } else if (arg0[0x143] != 0) {
        func_020aba5c(arg0);
    }
}
