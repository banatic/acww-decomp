/* func_ov096_022a1610 @ 0x022a1610, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int a);
extern int func_ov002_022080a0(void *p, int a);
extern int func_ov002_02208098(void *p, int a);
extern int func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_0206fe60(void);

void func_ov096_022a1610(void *p)
{
    if (func_ov002_02207f48(p, 0) != 0) {
        func_ov002_022080a0(p, 2);
        if (func_0206fe60() != 0) {
            func_ov002_02208098(p, 7);
        } else {
            func_ov002_02208098(p, 0x17);
        }
    } else {
        func_ov002_02207e80(p, 3, 0, 0);
        func_ov002_02207e80(p, 4, 0, 0);
    }
}
