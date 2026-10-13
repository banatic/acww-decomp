/* func_020579c4 @ 0x020579c4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057ac0(int);
int func_020579c4(char *p, int n)
{
    char *q;
    unsigned short a;
    unsigned short b;
    if (n == (-1)) {
        return 0;
    }
    q = p + 60;
    a = *((unsigned short *) (p + 66));
    b = *((unsigned short *) (q + a));
    return func_02057ac0(*((int *) (((q + a) + (b * n)) + 4)));
}
