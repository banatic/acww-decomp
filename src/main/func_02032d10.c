/* func_02032d10 @ 0x02032d10, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02032d10(unsigned char *p)
{
    int *a = (int *) (p + 8);
    int *b = (int *) (p + 0x10);
    short *h = (short *) p;
    int i;
    p[4] = 0;
    for (i = 0; i < 2; i++) {
        *h = 0;
        *a++ = 0;
        *b++ = 0;
        h++;
    }
}
