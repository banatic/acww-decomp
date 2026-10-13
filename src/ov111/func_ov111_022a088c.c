/* func_ov111_022a088c @ 0x022a088c, 0x2e bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *param, int flag);
extern void func_ov002_022080a0(void *param, int flag);
extern void func_ov111_022a01bc(void *param);
extern void func_ov002_02207e80(void *param, int a, int b, int c);

void func_ov111_022a088c(void *param)
{
    if (func_ov002_02207f48(param, 0) != 0) {
        func_ov002_022080a0(param, 2);
        func_ov111_022a01bc(param);
    }
    func_ov002_02207e80(param, 6, 0, 0);
}
