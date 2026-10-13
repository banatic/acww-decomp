/* func_0207dfec @ 0x0207dfec, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0207dfec(unsigned short *base)
{
    unsigned short *p;
    int i;
    unsigned short v;
    p = (unsigned short *) ((unsigned char *) base + 0x7b0);
    v = 0xfff1;
    for (i = 0; i < 4; i++) {
        *p++ = v;
    }
}
