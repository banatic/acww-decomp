/* func_ov068_0227215c @ 0x0227215c, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_02272dc8(void *p);
extern void func_02055060(void *p, int a, int b, int c, int d, int e);
extern void func_ov009_02262ef0(void *p, int v);

int func_ov068_0227215c(void *obj)
{
    int v;

    v = func_ov068_02272dc8(obj);
    func_02055060((char *) obj + 0x13c, v, 1, 0x1000, 0, 0);
    func_ov009_02262ef0((char *) obj + 0x238, 0x88b);
    return 1;
}
