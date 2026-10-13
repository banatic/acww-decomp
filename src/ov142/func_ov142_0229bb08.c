/* func_ov142_0229bb08 @ 0x0229bb08, 0x4a bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);
extern void func_ov142_02299ab8(void *p);

void func_ov142_0229bb08(void *p)
{
    int *q;
    int v;
    func_ov002_02207e80(p, 6, 0, 0);
    q = (int *) ((char *) p + 0x9c);
    v = *q;
    func_ov002_02207e80(p, 4, 0, 0x20 - v);
    *(int *) ((char *) p + 0x94) = func_ov002_02207f60(p);
    *(int *) ((char *) p + 0x98) = *(int *) ((char *) p + 0x94);
    func_ov142_02299ab8(p);
}
