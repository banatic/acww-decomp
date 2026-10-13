/* func_ov126_022a16fc @ 0x022a16fc, 0x2e bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int a);
extern void func_ov002_02207eb4(void *p, int a, int b);
extern void func_ov126_022a0054(void *p);
extern void func_ov002_02208090(void *p, int a);

void func_ov126_022a16fc(void *param)
{
    if (func_ov002_02207f3c(param, -1)) {
        func_ov002_02207eb4(param, 0, 0);
        func_ov126_022a0054(param);
        func_ov002_02208090(param, 11);
    }
}
