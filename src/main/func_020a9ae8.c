/* func_020a9ae8 @ 0x020a9ae8, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned int func_020a9ae8(unsigned int *p0)
{
    unsigned char buf[4];
    unsigned char *s;
    unsigned char *d;
    unsigned char *e;
    d = buf;
    s = (unsigned char *) p0 + 4;
    e = (unsigned char *) p0;
    while (s != e) {
        *d++ = *--s;
    }
    return *(unsigned int *) buf;
}
