/* func_ov106_0229ebcc @ 0x0229ebcc, 0x3e bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(int a, int b);
extern int func_ov002_022080a0(int a, int b);
extern int func_0206fe60(int a);
extern void func_ov002_02208098(int a, int b);
extern void func_ov106_0229eb28(int a);

void func_ov106_0229ebcc(int arg0)
{
    if (func_ov002_02207f48(arg0, 0) != 0) {
        if (func_0206fe60(func_ov002_022080a0(arg0, 2)) != 0) {
            func_ov002_02208098(arg0, 5);
        } else {
            func_ov002_02208098(arg0, 9);
        }
    } else {
        func_ov106_0229eb28(arg0);
    }
}
