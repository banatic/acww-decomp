/* func_ov141_0229aa04 @ 0x0229aa04, 0x24 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

void func_ov141_0229aa04(void *p)
{
    func_ov002_02207e80(p, 6, 0, 0);
    *(int *) ((char *) p + 0x1268) = func_ov002_02207f60(p);
}
