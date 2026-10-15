/* func_02012a4c @ 0x02012a4c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c80bc;
extern int func_0204f704(int, int);
extern int func_02037e8c(int);
extern void func_020131dc(int *arg0, int arg1, int arg2, int arg3);

void func_02012a4c(int *out, int param2)
{
    int tested_value0;
    int r4 = data_021c80bc;
    int local[2];
    int result;

    out[0] = 0;
    out[1] = 0;

    if (r4 != 0) {
        if ((tested_value0 = (int) (func_0204f704(r4, 0x200))) != 0) {
            result = func_02037e8c(tested_value0);
            func_020131dc(local, param2, result, r4);
            out[0] = local[0];
            out[1] = local[1];
        }
    }
}
