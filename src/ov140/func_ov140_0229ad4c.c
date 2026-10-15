/* func_ov140_0229ad4c @ 0x0229ad4c, 0x1e bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(int, int, int, int);
extern int func_ov002_02207f60(int);

int func_ov140_0229ad4c(int param)
{
    int *ptr;
    int result;

    func_ov002_02207e80(param, 6, 0, 0);
    result = func_ov002_02207f60(param);
    ptr = (int *) (param + 0x94);
    *ptr = result;
    return result;
}
