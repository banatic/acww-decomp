/* func_02045c60 @ 0x02045c60, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    unsigned int a;
    unsigned int b;
};

extern unsigned int func_02044858(unsigned int);
extern int func_02045c84(unsigned int, struct Pair *, unsigned int);

int func_02045c60(unsigned int p0, struct Pair *p1, unsigned int p2)
{
    struct Pair tmp;
    unsigned int d;

    d = func_02044858(p0);
    tmp.a = p1->a;
    tmp.b = p1->b;
    return func_02045c84(d, &tmp, p2);
}
