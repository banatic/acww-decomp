/* func_0206d780 @ 0x0206d780, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020ccf5c[];

int func_0206d780(unsigned short param)
{
    int i;
    for (i = 0; i < 7; i++) {
        if (param == data_020ccf5c[i]) {
            return 1;
        }
    }
    return 0;
}
