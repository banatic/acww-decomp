/* func_ov068_0226a098 @ 0x0226a098, 0x42 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096190(int);
extern int func_0201ce50(int);
extern int func_0201c390(int, int);

int func_ov068_0226a098(int arg0, int arg1)
{
    int a, b, ret, t;

    ret = 0;
    a = func_02096190(4);
    b = func_0201ce50(arg1);
    if (a != 0 && b != 0) {
        ret = func_0201c390(arg1, a);
        t = func_0201c390(b, a);
        if (ret >= t) {
            ret = t;
        }
    }
    return ret;
}
