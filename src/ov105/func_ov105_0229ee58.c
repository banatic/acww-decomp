/* func_ov105_0229ee58 @ 0x0229ee58, 0x36 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int n);
extern void func_020027f0(int n);
extern void func_ov105_0229c320(void *p, int n);
extern void func_ov105_0229f1b4(void *p);
extern void func_ov105_0229edc4(void *p);

void func_ov105_0229ee58(void *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(3);
        func_020027f0(4);
        func_ov105_0229c320(param, 0x80);
        func_ov105_0229f1b4(param);
    } else {
        func_ov105_0229edc4(param);
    }
}
