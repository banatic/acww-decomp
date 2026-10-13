/* func_020ea970 @ 0x020ea970, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the identity inline on b makes the b load come before the a load; the plain expression loads a first */

struct S_020ea970 {
    int a;
    int pad_04;
    int b;
};

inline long long widen(int x)
{
    return (long long) x;
}

long long func_020ea970(struct S_020ea970 *p)
{
    int b = p->b;
    int a = p->a;

    return (widen(b) * b + (long long) a * a) >> 12;
}
