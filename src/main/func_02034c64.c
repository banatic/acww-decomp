/* func_02034c64 @ 0x02034c64, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_0209871c(int *, int);
extern void NNS_G3dAllocAnmObj(int, int, int);
extern int data_021dc7bc;

void func_02034c64(int a, int b)
{
    int tested_value0;
    int mask = b & 7;
    int result = 0;

    if ((tested_value0 = (int) (func_020984e8())) != 0) {
        int x = func_02099870(tested_value0);
        result = func_0209871c(&data_021dc7bc, x) & 3;
    }

    NNS_G3dAllocAnmObj(a, result, mask);
}
