/* func_0208537c @ 0x0208537c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021d213c[];

int func_0208537c(unsigned short *p, unsigned char a, unsigned char b)
{
    unsigned int val = *p & 0x0fff;
    if (val < 8) {
        unsigned char *ptr = data_021d213c + val * 30;
        ptr[0] = 1;
        ptr[1] = a;
        ptr[2] = b;
        return 1;
    }
    return 0;
}
