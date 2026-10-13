/* func_ov077_022792e4 @ 0x022792e4, 0x34 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(int *ptr);
extern int func_ov077_02279358(int *ptr, int val);

int func_ov077_022792e4(int *self)
{
    int *base;
    int result;

    base = (int *) ((char *) self + 0x618);
    result = func_02014868(base);
    if (result != 0) {
        return 1;
    }

    base = (int *) ((char *) self + 0x618);
    result = func_02014868(base);
    if (result == 0) {
        func_ov077_02279358(self, 5);
    }

    return 1;
}
