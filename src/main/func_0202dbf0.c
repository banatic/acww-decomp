/* func_0202dbf0 @ 0x0202dbf0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Pair {
    int x;
    int y;
} Pair;

void func_0202dbf0(int *p, Pair value)
{
    int a;
    int b;
    a = *(volatile int *) &value.x;
    b = *(volatile int *) &value.y;
    p[0x36] = a;
    p[0x37] = b;
}
