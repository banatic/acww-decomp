/* func_ov096_022a15d4 @ 0x022a15d4, 0x3c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207f04(int, int, int, int, int);
extern void func_ov002_02207e80(int, int, int, int);
extern void func_ov002_02208090(int, int);

void func_ov096_022a15d4(int param)
{
    int local;
    local = 0x30;
    func_ov002_02207f04(param, 3, 0, 0, local);
    func_ov002_02207e80(param, 3, 0, 0);
    func_ov002_02207e80(param, 4, 0, 0);
    func_ov002_02208090(param, 0xa);
}
