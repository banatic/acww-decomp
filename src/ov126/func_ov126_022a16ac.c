/* func_ov126_022a16ac @ 0x022a16ac, 0x2a bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

void func_ov126_022a16ac(void *p)
{
    func_ov002_02207e80(p, 4, 0, 0);
    func_ov002_02207e80(p, 6, 0, 0);
    *(int *) ((char *) p + 0x94) = func_ov002_02207f60(p);
}
