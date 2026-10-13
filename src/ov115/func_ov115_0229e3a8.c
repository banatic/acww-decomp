/* func_ov115_0229e3a8 @ 0x0229e3a8, 0x3c bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

void func_ov115_0229e3a8(void *p)
{
    func_ov002_02207e80(p, 3, 0, 0);
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov002_02207e80(p, 4, 0, 0);
    ((int *) p)[0x1424 / 4] = func_ov002_02207f60(p);
}
