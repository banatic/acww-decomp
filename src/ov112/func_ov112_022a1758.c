/* func_ov112_022a1758 @ 0x022a1758, 0x4e bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *a, int b);
extern void func_020027f0(int a);
extern void func_ov112_0229fe50(void *a, int b);
extern void func_ov002_02208090(void *a, int b);
extern void func_ov002_02207e80(void *a, int b, int c, int d);
extern int func_ov002_02207f60(void *a);

void func_ov112_022a1758(void *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_ov112_0229fe50(p, 1);
        func_ov002_02208090(p, 4);
    } else {
        func_ov002_02207e80(p, 6, 0, 0);
    }
    *((int *) ((char *) p + 0xa0)) = func_ov002_02207f60(p);
    *((int *) ((char *) p + 0xa8)) = *((int *) ((char *) p + 0xa0));
}
