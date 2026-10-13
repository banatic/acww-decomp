/* func_02084e68 @ 0x02084e68, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02084e68(unsigned short *arg0, unsigned int arg1, unsigned int arg2)
{
    if (arg1 < 16 && arg2 < 16) {
        arg0[arg2] |= (1u << arg1);
        return 1;
    } else {
        return 0;
    }
}
