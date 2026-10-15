/* func_ov004_022265c0 @ 0x022265c0, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} Triple;
void func_ov004_022265c0(int *self, Triple v, int setting, int extent)
{
    self[0] = v.a;
    self[1] = v.b;
    self[2] = v.c;
    self[3] = setting;
    self[4] = extent;
}
