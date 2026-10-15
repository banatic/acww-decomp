/* func_0204f5a8 @ 0x0204f5a8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f828(int *a, int *b, int c);
extern void *func_0204f5e0(int a, int b, int c, int d, int e, int f);

void *func_0204f5a8(int a, int b, int c)
{
    int vals[4];
    vals[0] = 0;
    vals[1] = 0;
    vals[2] = 0;
    vals[3] = 0;
    func_0204f828(&vals[0], &vals[2], b);
    return func_0204f5e0(a, vals[0], vals[1], vals[2], vals[3], c);
}
