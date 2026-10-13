/* func_0204d828 @ 0x0204d828, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;
extern Pair data_020cb764[];
extern int func_0204d8e4(int, int, int);
extern void func_02064828(int, int, int, int);

int func_0204d828(int a, int b, int c, int d, int e)
{
    int t;
    Pair *p;
    t = func_0204d8e4(a, c, d);
    p = &data_020cb764[c];
    func_02064828(p->b, b, e, t);
    return 1;
}
