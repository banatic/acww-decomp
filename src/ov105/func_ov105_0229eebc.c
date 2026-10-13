/* func_ov105_0229eebc @ 0x0229eebc, 0x3e bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(int, int);
extern int func_ov002_022080a0(int, int);
extern int func_0206fe60(int);
extern void func_ov002_02208098(int, int);
extern void func_ov105_0229edc4(int);

void func_ov105_0229eebc(int a)
{
    if (func_ov002_02207f48(a, 0) != 0) {
        if (func_0206fe60(func_ov002_022080a0(a, 2)) != 0) {
            func_ov002_02208098(a, 5);
        } else {
            func_ov002_02208098(a, 9);
        }
    } else {
        func_ov105_0229edc4(a);
    }
}
