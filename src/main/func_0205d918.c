/* func_0205d918 @ 0x0205d918, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205daac(int a);
extern int func_0205d968(int a, int b, int c);

int func_0205d918(int arg0, int arg1)
{
    int result;
    int i;
    int ret;

    result = func_0205daac(arg1);
    for (i = 0; i < 9; i++) {
        ret = func_0205d968(arg0, i, result);
        if (ret == arg1) {
            return i;
        }
    }
    return 9;
}
