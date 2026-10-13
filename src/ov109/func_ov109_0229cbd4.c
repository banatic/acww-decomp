/* func_ov109_0229cbd4 @ 0x0229cbd4, 0x36 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229ccb4(int, int);
extern int func_ov109_0229cc98(int, int);
extern int func_ov094_0229aba4(void *, int);

int func_ov109_0229cbd4(int a, int b)
{
    if (func_ov109_0229ccb4(a, b)) {
        return func_ov094_0229aba4((void *) (a + 0xcc), func_ov109_0229cc98(a, b));
    } else {
        if (b == 15) {
            return 0xbc;
        } else {
            return 0;
        }
    }
}
