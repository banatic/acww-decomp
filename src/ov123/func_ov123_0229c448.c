/* func_ov123_0229c448 @ 0x0229c448, 0x28 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *param, int value);
extern void func_ov002_022080a0(void *param, int value);
extern void func_ov123_0229b65c(void *param);
extern void func_ov123_0229c07c(void *param);

void func_ov123_0229c448(void *param)
{
    if (func_ov002_02207f48(param, 0)) {
        func_ov002_022080a0(param, 2);
        func_ov123_0229b65c(param);
    }
    func_ov123_0229c07c(param);
}
