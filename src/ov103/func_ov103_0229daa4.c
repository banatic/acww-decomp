/* func_ov103_0229daa4 @ 0x0229daa4, 0x50 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(int, int);
extern void func_ov002_022080a0(int, int);
extern int func_0206fe60(void);
extern void func_ov002_02208098(int, int);
extern void func_ov002_02207e80(int, int, int, int);

void func_ov103_0229daa4(int p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        if (func_0206fe60()) {
            func_ov002_02208098(p, 3);
        } else {
            func_ov002_02208098(p, 7);
        }
    } else {
        func_ov002_02207e80(p, 3, 0, 0);
        func_ov002_02207e80(p, 4, 0, 0);
    }
}
