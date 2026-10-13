/* func_0202f898 @ 0x0202f898, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202f8fc(int a, int b, int c);

struct Pair {
    int x;
    int y;
};

void func_0202f898(int a, struct Pair *p1, struct Pair *p2)
{
    func_0202f8fc(a, p1->x - p2->x, p1->y - p2->y);
}
