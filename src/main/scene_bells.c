/* scene_bells: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201b43c @ 0x0201b43c, 0x1c bytes, Thumb
 * func_0201b420 @ 0x0201b420, 0x1a bytes, Thumb
 * func_0201b3c0 @ 0x0201b3c0, 0x5e bytes, Thumb
 * func_0201b3a4 @ 0x0201b3a4, 0x1a bytes, Thumb
 */

extern int func_020984e8(void);
extern int func_02099734(int a);
extern int func_02098a6c(int a, int b, int c, int d);
extern void func_02098a24(int, int, int);
extern int func_02098cc0(int p1, int p2, int p3);

int func_0201b43c(int a, int b)
{
    int t1;
    int t2;
    t1 = func_020984e8();
    t2 = func_02099734(t1);
    return func_02098a6c(t2, -b, 1, 0);
}

void func_0201b420(int a, int b)
{
    int res;

    res = func_020984e8();
    res = func_02099734(res);
    func_02098a24(res, -b, 1);
}

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

void func_0201b3a4(int a, int b)
{
    func_02098a24(func_02099734((int) func_020984e8()), b, 1);
}
