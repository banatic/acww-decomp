/* func_ov004_022265c0 @ 0x022265c0, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c, d, e;
} BIG5;
void func_ov004_022265c0(int *self, BIG5 v)
{
    self[0] = v.a;
    self[1] = v.b;
    self[2] = v.c;
    self[3] = v.d;
    self[4] = v.e;
}
