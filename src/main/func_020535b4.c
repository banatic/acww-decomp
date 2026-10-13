/* func_020535b4 @ 0x020535b4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020535f0(unsigned short *p);

int func_020535b4(int arg)
{
    int count = 0;
    unsigned int i = 0;
    unsigned short val;

    do {
        val = (unsigned short) ((i < 0x34) ? (0x450c + (i << 2)) : 0x450c);
        if (arg == func_020535f0(&val)) {
            count++;
        }
        i++;
    } while (i < 0x34);

    return count;
}
