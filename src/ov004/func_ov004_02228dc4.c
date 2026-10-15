/* func_ov004_02228dc4 @ 0x02228dc4, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109fc(void *self, int a, int b, int c);
void func_ov004_02228dc4(unsigned char *self, unsigned char *p, int previous)
{
    unsigned short *q;
    unsigned char *w;
    q = (unsigned short *) (p + 0xc);
    if (*(int *) (self + 0x704) != 0x24) {
        func_020109fc(self, 0x24, *q, 0);
    }
    w = self + 0x7d4;
    *(int *) w = *(int *) (self + 0xb0);
    *(unsigned char *) (w + 4) = 0;
}
