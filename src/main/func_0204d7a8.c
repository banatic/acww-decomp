/* func_0204d7a8 @ 0x0204d7a8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c80c8;
extern int func_0204d858(int, int);
extern int func_0204d708(int, int, int, int, int);
extern void func_020e993c(int, int);

int func_0204d7a8(int p1, int p2, int p3, int p4)
{
    int result = 0;
    if (data_021c80c8) {
        result = func_0204d858(p3, p4);
        if (result != 0) {
            if (func_0204d708(data_021c80c8, result, p1, p2, p3) == 0) {
                func_020e993c(p3, result);
                result = 0;
            }
        }
    }
    return result;
}
