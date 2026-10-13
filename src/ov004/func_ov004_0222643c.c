/* func_ov004_0222643c @ 0x0222643c, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} BIG3;
void func_ov004_0222643c(int *self, BIG3 v, int d)
{
    self[0] = v.a;
    self[1] = v.b;
    self[2] = v.c;
    self[3] = d;
    self[4] = d;
}
