/* func_02043d84 @ 0x02043d84, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02044858(void *);
extern int func_02043db4(void *, void *, int, int, unsigned short);

struct Pair {
    unsigned int a;
    unsigned int b;
};

int func_02043d84(void *a, struct Pair *src, int c, int d, unsigned short e)
{
    struct Pair local;
    void *p;

    p = func_02044858(a);
    local.a = src->a;
    local.b = src->b;
    return func_02043db4(p, &local, c, d, e);
}
