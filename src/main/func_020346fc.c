/* func_020346fc @ 0x020346fc, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020346fc(unsigned char *p)
{
    unsigned char *q;
    unsigned char fill = 0xff;
    *p = 0;
    q = p + 1;
    fill = 0xff;
    p = p + 5;
    while (q < p) {
        *q++ = fill;
    }
}
