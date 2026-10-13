/* func_ov104_0229ec0c @ 0x0229ec0c, 0x3e bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(int a, int b);
extern void func_ov002_022080a0(int a, int b);
extern int func_0206fe60(void);
extern void func_ov002_02208098(int a, int b);
extern void func_ov104_0229eb88(int a);

void func_ov104_0229ec0c(int arg)
{
    if (func_ov002_02207f48(arg, 0)) {
        func_ov002_022080a0(arg, 2);
        if (func_0206fe60()) {
            func_ov002_02208098(arg, 5);
        } else {
            func_ov002_02208098(arg, 9);
        }
    } else {
        func_ov104_0229eb88(arg);
    }
}
