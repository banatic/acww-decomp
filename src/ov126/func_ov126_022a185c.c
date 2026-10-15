/* func_ov126_022a185c @ 0x022a185c, 0x4e bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov126_0229fc54(void);
extern int func_0206fc8c(void);
extern void *func_02077c3c(void *object);
extern void *func_02077d68(void *object);
extern int func_020eaf48(int, int);
extern void func_ov002_02207f04(int, int, int, int, int);
extern void func_ov126_022a16ac(int);
extern void func_ov002_02208090(int, int);

void func_ov126_022a185c(int arg0)
{
    int v4 = func_ov126_0229fc54();
    int v6 = func_0206fc8c();
    int v1 = (int) func_02077d68(func_02077c3c((void *) v4));
    if (func_020eaf48(v6, v1) != 0) {
        func_ov002_02207f04(arg0, 10, 0, 0, 0x30);
        func_ov126_022a16ac(arg0);
        func_ov002_02208090(arg0, 5);
    }
}
