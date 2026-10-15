/* func_0201b3c0 @ 0x0201b3c0, 0x5e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098cc0(int p1, int p2, int p3);

int func_0201b3c0(int unused, int a, int b)
{
    int obj;
    int low;
    int temp;
    int result;

    if (func_020984e8() != 0) {
        obj = func_02099734((int) func_020984e8());
    } else {
        obj = 0;
    }

    if (obj != 0) {
        low = func_02098cc0(obj, 0, 0);
    } else {
        low = 0;
    }

    if (obj != 0) {
        temp = func_02098cc0(obj, 1, b);
    } else {
        temp = 0;
    }

    result = 2;
    if (a <= low) {
        result = 0;
    } else if (a <= temp) {
        result = 1;
    }
    return result;
}
