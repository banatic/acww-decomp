/* func_02097fa4 @ 0x02097fa4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066650(void *p);

void func_02097fa4(void *p)
{
    int i;
    unsigned short *s;
    unsigned char *b;
    int j;

    for (i = 0; i < 10; i++) {
        func_02066650((char *) p + (i << 8));
    }

    s = (unsigned short *) ((char *) p + 0xa04);
    *s = 0;

    b = (unsigned char *) p + 0xa00;
    *b = 1;
    b = (unsigned char *) p + 0xa01;
    *b = 1;
    b = (unsigned char *) p + 0xa02;
    *b = 0;
    b = (unsigned char *) p + 0xa03;
    *b = 0;
}
