/* func_ov094_0229b8b4 @ 0x0229b8b4, 0x22 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229b8d8(int *, int *, unsigned int);
extern int func_02066830(int, unsigned int);
extern int func_ov094_0229b154(int *, int *);

int func_ov094_0229b8b4(int *a0, int *a1, unsigned int a2)
{
    int v;
    v = func_ov094_0229b8d8(a0, a1, a2);
    func_02066830(v, a2);
    return func_ov094_0229b154(a0 + 2, a1);
}
