/* func_02057918 @ 0x02057918, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

int func_02057918(void *p, int i)
{
    unsigned short *addr;
    int j;
    char *q;
    char *r;
    unsigned char count;

    q = (char *) p + *(unsigned short *) ((char *) p + 0x34);
    if (i == -1) {
        return 0;
    }

    r = q + *(unsigned short *) (q + 6);
    addr = (unsigned short *) (r + 4 + *(unsigned short *) r * i);

    j = i + 1;
    count = *(unsigned char *) (q + 1);
test:
    if (j < count) {
        goto body;
    }
exit:
    return (*(unsigned short *) ((char *) p + 0x30) - *addr) << 3;
body: {
    char *q2 = (char *) p + *(unsigned short *) ((char *) p + 0x34);
    char *e = q2 + *(unsigned short *) (q2 + 6);
    unsigned short f = *(unsigned short *) (e + *(unsigned short *) e * j + 4);
    if (f > *addr) {
        return (f - *addr) << 3;
    }
}
    j++;
    goto test;
}
