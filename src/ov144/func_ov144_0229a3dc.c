/* func_ov144_0229a3dc @ 0x0229a3dc, 0x28 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208ea70(void *, int, int);

void func_ov144_0229a3dc(char *p)
{
    char *base;
    int a;
    int b;
    base = p + 0x128;
    a = *(int *) (p + 0x94);
    p += 0xa8;
    b = *(int *) p;
    func_0208ea70(base, 0x4f, a + (b - 0x4b));
}
