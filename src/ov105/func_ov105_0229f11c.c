/* func_ov105_0229f11c @ 0x0229f11c, 0x34 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *arg, int zero);
extern void func_ov105_0229ed98(void *arg);
extern void func_ov105_0229e9d0(void *arg);
extern void func_ov105_0229c4cc(void *arg);
extern void func_ov002_02208090(void *arg, int num);

void func_ov105_0229f11c(void *arg)
{
    int r = func_ov002_02207f48(arg, 0);
    func_ov105_0229ed98(arg);
    if (r != 0) {
        func_ov105_0229e9d0(arg);
        func_ov105_0229c4cc(arg);
        func_ov002_02208090(arg, 3);
    }
}
