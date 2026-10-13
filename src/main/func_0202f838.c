/* func_0202f838 @ 0x0202f838, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Vec2 {
    int x;
    int y;
};

extern void func_0202f8fc(int *out, int a, int b);
extern int FX_MulFunc(int a, int b);

long long func_0202f838(struct Vec2 *a, struct Vec2 *b)
{
    int diffx, diffy;
    int local[2];
    int c, a2, result1, result2;

    diffx = a->x - b->x;
    diffy = a->y - b->y;
    func_0202f8fc(local, diffx, diffy);

    c = local[1];
    a2 = local[0];
    result1 = FX_MulFunc(a2, a2);
    result2 = FX_MulFunc(c, c);
    return result1 + result2;
}
