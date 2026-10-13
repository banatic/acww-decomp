/* func_ov106_0229eafc @ 0x0229eafc, 0x2c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(int, int, int, int);
extern int func_ov002_02207f60(int);

void func_ov106_0229eafc(int arg0)
{
    int local_0;
    int local_4;

    func_ov002_02207e80(arg0, 6, 0, ~0xf);
    local_0 = func_ov002_02207f60(arg0);
    *(int *) (arg0 + 0x98) = local_0;
    local_4 = func_ov002_02207f60(arg0);
    *(int *) (arg0 + 0xa0) = local_4;
}
