/* func_ov098_022a3060 @ 0x022a3060, 0x44 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229c2dc(void *, int);
extern int func_02073d90(int);
extern int func_ov098_022a2fc0(void *, int);
extern void func_ov002_02208d4c(void *, int, int);
extern void func_ov096_0229c2ec(void *, int);

extern int data_020ccf94;

void func_ov098_022a3060(void *param)
{
    func_ov096_0229c2dc(param, 8);
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    if (func_ov098_022a2fc0(param, 1) == 0) {
        return;
    }
    func_ov002_02208d4c((char *) param + 0x294c, 0x11, 0x19);
    func_ov096_0229c2ec(param, 8);
}
