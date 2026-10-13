/* func_0200c89c @ 0x0200c89c, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_02077898(void *);

void func_0200c89c(void *a, unsigned short *b, unsigned char *c, unsigned char *d)
{
    unsigned short x;
    unsigned char y, z;

    x = func_02077898(a);
    *b = x;
    y = ((unsigned char *) a)[2];
    *c = y;
    z = ((unsigned char *) a)[3];
    *d = z;
}
