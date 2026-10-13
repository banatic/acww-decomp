/* func_02051608 @ 0x02051608, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051608(void *r0, unsigned char r1, unsigned char r2, int r3, int r4);

void func_02051608(void *r0, unsigned char r1, unsigned char r2, int r3, int r4)
{
    unsigned char *p;
    int *q;

    p = (unsigned char *) r0 + 0x3a;
    *p = r1;
    p = (unsigned char *) r0 + 0x3b;
    *p = r2;
    q = (int *) r0 + 0x10;
    *q = r3;
    q = (int *) r0 + 0x11;
    *q = r4;
}
