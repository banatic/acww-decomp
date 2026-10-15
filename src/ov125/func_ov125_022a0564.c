/* func_ov125_022a0564 @ 0x022a0564, 0x30 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

int func_ov125_022a0564(void *p)
{
    int valueResult;

    func_ov002_02207e80(p, 6, 0, 0);
    func_ov002_02207e80(p, 4, 0, 0);
    valueResult = func_ov002_02207f60(p);
    *(int *) ((char *) p + 0x874) = valueResult;
    return valueResult;
}
