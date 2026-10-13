/* func_020adda8 @ 0x020adda8, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020adde4(int);
extern int func_020addd0(int);

unsigned short func_020adda8(unsigned short *param)
{
    int b;

    b = func_020adde4(*param);
    if (b != 4) {
        return (unsigned short) (func_020addd0(b + 1) - *param);
    } else {
        return 0;
    }
}
