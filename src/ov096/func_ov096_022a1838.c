/* func_ov096_022a1838 @ 0x022a1838, 0x34 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_022a1384(void *);
extern void func_ov002_02208090(void *, int);
extern int func_ov096_0229c2fc(void *, unsigned int);
extern void func_ov096_022a17cc(void *);
extern void func_ov096_0229c2dc(void *, unsigned int);

void func_ov096_022a1838(void *param)
{
    func_ov096_022a1384(param);
    func_ov002_02208090(param, 3);
    if (func_ov096_0229c2fc(param, 0x00080000) == 0) {
        func_ov096_022a17cc(param);
        func_ov096_0229c2dc(param, 0x00080000);
    }
}
