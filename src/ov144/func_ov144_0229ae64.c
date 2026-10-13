/* func_ov144_0229ae64 @ 0x0229ae64, 0x3e bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);
extern void func_ov144_0229a3dc(void *p);

void func_ov144_0229ae64(void *p)
{
    int x;
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov002_02207e80(p, 4, 0, 0x18 - *(int *) ((char *) p + 0x9c));
    x = func_ov002_02207f60(p);
    *(int *) ((char *) p + 0x94) = x;
    func_ov144_0229a3dc(p);
}
