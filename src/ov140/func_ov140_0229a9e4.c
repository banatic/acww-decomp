/* func_ov140_0229a9e4 @ 0x0229a9e4, 0x68 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov140_0229ab28(void *p);
extern int func_ov002_02208014(void *p);
extern void func_ov140_0229a7e8(void *p);
extern int func_ov002_02208008(void *p);
extern int func_ov140_0229a4a0(void *p, int arg);
extern void func_ov140_0229a614(void *p);
extern void func_ov140_0229a570(void *p);
extern void func_ov140_0229a73c(void *p);
extern void func_ov140_0229a638(void *p);
extern unsigned short data_021fbe40[2];

void func_ov140_0229a9e4(void *p)
{
    func_ov140_0229ab28(p);
    if (func_ov002_02208014(p) != 0) {
        func_ov140_0229a7e8(p);
        return;
    } else {
        if (func_ov140_0229a4a0(p, func_ov002_02208008(p)) != 0) {
            func_ov140_0229a614(p);
            return;
        } else {
            if (data_021fbe40[1] & 1) {
                func_ov140_0229a570(p);
                return;
            } else if (data_021fbe40[1] & 2) {
                func_ov140_0229a73c(p);
                func_ov140_0229a638(p);
            }
        }
    }
}
