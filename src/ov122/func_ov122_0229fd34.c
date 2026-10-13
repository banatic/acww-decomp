/* func_ov122_0229fd34 @ 0x0229fd34, 0x54 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int *func_0206de7c(void *arg);
extern int func_ov095_0229bb34(void *a, void *b, int c, int d, unsigned char e, unsigned char *f);

unsigned char func_ov122_0229fd34(void *p, int n, int *v)
{
    int x = func_0206de7c((char *) p + 0x3ce8)[n];
    unsigned char temp;
    int r = func_ov095_0229bb34((char *) p + 0xc0, (char *) (*(void **) ((char *) p + 0xbc)) + 0x58 + x * 2, 0x28, 0xa0,
                                (unsigned char) (*v - 0x30), &temp);
    *v = r + 0x30;
    return (unsigned char) (temp + x);
}
