/* func_02056548 @ 0x02056548, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_G3dAnmObjCalcSizeRequired__autoload_2_021055f8(int a, int b);
extern int func_020e9948(int a, int b);
extern int data_021fbe94;

int func_02056548(int a, int b, int c)
{
    int ret;
    if (a == 0) {
        return 0;
    }
    ret = NNS_G3dAnmObjCalcSizeRequired__autoload_2_021055f8(b, a);
    if (c == 0) {
        c = data_021fbe94;
    }
    return func_020e9948(c, ret);
}
