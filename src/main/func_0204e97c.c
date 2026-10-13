/* func_0204e97c @ 0x0204e97c, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    int x;
    int y;
};

extern int func_0204e9a8(int a, int b, int c);

int func_0204e97c(int a, struct Pair *p2, struct Pair *p3)
{
    int result = 0;
    if (func_0204e9a8(a, p3->x, p3->y)) {
        p2->x = p3->x - 1;
        p2->y = p3->y - 1;
        result = 1;
    }
    return result;
}
