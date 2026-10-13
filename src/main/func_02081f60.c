/* func_02081f60 @ 0x02081f60, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081f78(int, unsigned char, unsigned char);

struct Pair {
    unsigned int a;
    unsigned int b;
};

int func_02081f60(int a, struct Pair *p)
{
    return func_02081f78(a, (unsigned char) p->a, (unsigned char) p->b);
}
