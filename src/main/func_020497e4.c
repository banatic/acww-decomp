/* func_020497e4 @ 0x020497e4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Pair {
    int a;
    int b;
} Pair;

extern int func_0204a198(int a, unsigned short b, int c, int d);
extern int func_02049818(int a, int b, unsigned short *c, Pair *d, int e, int f);

int func_020497e4(int p0, int p1, unsigned short *p2, Pair *p3, int arg5, int arg6)
{
    if (arg6 >= 0x30) {
        return func_0204a198(p1, *p2, arg5, arg6);
    } else {
        Pair local_pair;
        local_pair.a = p3->a;
        local_pair.b = p3->b;
        return func_02049818(p0, p1, p2, &local_pair, arg5, arg6);
    }
}
