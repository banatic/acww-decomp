/* func_0201b420 @ 0x0201b420, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(int);
extern int func_02099734(int);
extern int func_02098a24(int, int, int);

int func_0201b420(int a, int b)
{
    int res;

    res = func_020984e8(a);
    res = func_02099734(res);
    return func_02098a24(res, -b, 1);
}
