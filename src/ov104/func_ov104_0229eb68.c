/* func_ov104_0229eb68 @ 0x0229eb68, 0x20 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(int, int, int, int);
extern int func_ov002_02207f60(int);

void func_ov104_0229eb68(int param)
{
    int *p;
    int result;

    func_ov002_02207e80(param, 6, 0, ~0xf);
    result = func_ov002_02207f60(param);
    p = (int *) (param + 0x98);
    *p = result;
}
