/* func_ov111_022a082c @ 0x022a082c, 0x30 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(int, int);
extern void func_0200277c(int);
extern void func_ov002_022080a0(int, int);
extern void func_ov002_02207e80(int, int, int, int);

void func_ov111_022a082c(int param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_0200277c(6);
        func_ov002_022080a0(param, 5);
    } else {
        func_ov002_02207e80(param, 6, 0, 0);
    }
}
