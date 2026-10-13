/* func_020ea970 @ 0x020ea970, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct S_020ea970 {
    int a;
    int pad_04;
    int b;
};

long long func_020ea970(struct S_020ea970 *p)
{
    int a = p->a;
    int b = p->b;

    return ((long long) a * a + (long long) b * b) >> 12;
}
