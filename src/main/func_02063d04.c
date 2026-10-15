/* func_02063d04 @ 0x02063d04, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02063eb0(void *, int);
extern int func_02063f3c(unsigned char *);

extern char data_021f3b7c[];

unsigned int func_02063d04(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned int v0;
    unsigned char v1;
    unsigned char v6;
    unsigned int v4;
    unsigned char v3;
    unsigned char v2;
    unsigned int r3;
    unsigned int r2;
    unsigned int r1;
    unsigned int r0;

    v0 = (unsigned char) func_02063f3c((unsigned char *) func_02063eb0(data_021f3b7c, 0));

    v4 = (unsigned int) func_02063f3c((unsigned char *) func_02063eb0(data_021f3b7c, 4)) << 24;

    v1 = (unsigned char) func_02063f3c((unsigned char *) func_02063eb0(data_021f3b7c, 1));

    v6 = (unsigned char) func_02063f3c((unsigned char *) func_02063eb0(data_021f3b7c, 6));

    v3 = (unsigned char) func_02063f3c((unsigned char *) func_02063eb0(data_021f3b7c, 3));

    v2 = (unsigned char) func_02063f3c((unsigned char *) func_02063eb0(data_021f3b7c, 2));

    a |= (c << 11) | (b << 7);
    b = c << 30;
    c = v2 << 25;
    r3 = v3 << 20;
    r2 = v6 << 15;
    r1 = v1 << 10;
    r0 = v4 >> 19;
    a |= a << 16;
    v0 ^= a;
    r0 ^= v0;
    r1 ^= r0;
    r2 ^= r1;
    r3 ^= r2;
    c ^= r3;
    b ^= c;

    return b;
}
