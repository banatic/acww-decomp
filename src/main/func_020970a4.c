/* func_020970a4 @ 0x020970a4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e307c[];
extern unsigned char data_020e3088[];
extern unsigned char data_020e3098[];

unsigned char *func_020970a4(int param)
{
    if (param >= 0 && param < 0x22) {
        return data_020e307c;
    }
    if (param >= 0x22 && param < 0x5a) {
        return data_020e3088;
    }
    return data_020e3098;
}
