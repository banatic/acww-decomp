/* func_ov105_0229effc @ 0x0229effc, 0x68 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(unsigned int a, int b);
extern void func_020027f0(int a);
extern void func_ov105_0229c320(unsigned int a, int b);
extern void func_ov002_02207f04(unsigned int a, int b, int c, int d, int e);
extern void func_ov002_02208090(unsigned int a, int b);
extern void func_ov105_0229ef90(unsigned int a);
extern void func_ov002_0220ad0c(unsigned int a);
extern void func_ov105_0229ed78(unsigned int a);
extern int func_ov002_02207f54(unsigned int a);

void func_ov105_0229effc(unsigned int param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(4);
        func_ov105_0229c320(param, 0x200);
        func_ov002_02207f04(param, 8, 0, 0, 0x30);
        func_ov002_02208090(param, 6);
        func_ov105_0229ef90(param);
        func_ov002_0220ad0c(param + 0x5fb8);
    } else {
        func_ov105_0229ed78(param);
        *((int *) (param + 0x9c)) = -func_ov002_02207f54(param);
    }
}
