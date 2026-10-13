/* func_0207a4c0 @ 0x0207a4c0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf14(void *);
extern int func_0207cf74(int);

void func_0207a4c0(void *arg0)
{
    int r4 = func_0207cf14(arg0);
    if (func_0207cf74(r4) != 0) {
        unsigned short *p = (unsigned short *) ((char *) arg0 + 0x4078);
        *p |= 2;
        *p = (*p & ~0x1c) | (((unsigned char) r4 & 7) << 2);
    }
}
