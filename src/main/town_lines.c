/* town_lines: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020497e4 @ 0x020497e4, 0x34 bytes, Thumb
 * func_020497b0 @ 0x020497b0, 0x34 bytes, Thumb
 */

typedef struct Pair {
    int a;
    int b;
} Pair;

extern void func_0204a198(int a, unsigned short b, int c, int d);
extern void func_02049818(int a, int b, unsigned short *c, Pair *d, int e, int f);

void func_020497e4(int p0, int p1, unsigned short *p2, Pair *p3, int arg5, int arg6)
{
    if (arg6 >= 0x30) {
        func_0204a198(p1, *p2, arg5, arg6);
    } else {
        Pair local_pair;
        local_pair.a = p3->a;
        local_pair.b = p3->b;
        func_02049818(p0, p1, p2, &local_pair, arg5, arg6);
    }
}

void func_020497b0(void *a, void *b, unsigned short *c, unsigned int *d, int e, int f)
{
    if (f < 64) {
        func_0204a198((int) b, *c, e, f);
    } else {
        unsigned int local[2];
        local[0] = d[0];
        local[1] = d[1];
        func_02049818((int) a, (int) b, c, (Pair *) local, e, f);
    }
}
