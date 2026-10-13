/* func_02079a88 @ 0x02079a88, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020808ec(int);
struct Pair {
    unsigned char a;
    unsigned char b;
};
extern struct Pair data_020cd464[];
extern struct Pair data_020cd434[];
int func_02079a88(int a, int b, int c)
{
    int x;
    int y;
    struct Pair *p;
    int i;
    x = func_020808ec(b);
    y = func_020808ec(c);
    if (x == y) {
        return 0x40;
    }
    p = data_020cd464;
    for (i = 0; i < 7; p++, i++) {
        if (((p->a == x) && (p->b == y)) || ((p->b == x) && (p->a == y))) {
            return 0x80;
        }
    }

    p = data_020cd434;
    for (i = 0; i < 4; p++, i++) {
        if (((p->a == x) && (p->b == y)) || ((p->b == x) && (p->a == y))) {
            return 0x00;
        }
    }

    return 0x20;
}
