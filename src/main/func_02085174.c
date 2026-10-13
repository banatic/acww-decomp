/* func_02085174 @ 0x02085174, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208537c(unsigned short *p, int a, int b);
extern int func_02085244(unsigned short *p, int a, int b);

int func_02085174(unsigned short *p0, int a, int b)
{
    int nibble = (*p0 & 0xF000) >> 12;
    if (nibble == 14) {
        return func_0208537c(p0, a, b);
    }
    if (nibble == 13) {
        return func_02085244(p0, a, b);
    }
    return 0;
}
