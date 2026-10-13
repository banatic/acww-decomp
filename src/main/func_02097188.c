/* func_02097188 @ 0x02097188, 0x7a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern int func_02098a0c(void);
extern int func_0209727c(int, int);
extern void func_02097204(int, int);
extern int func_020644cc(int);
extern int func_02097234(int, int, int);
extern int func_020970cc(int, int);
extern void func_02097d18(int, int);

int func_02097188(int a, int b, int c, int d)
{
    int w0, v1, v2, v3, v4;
    int flag = d;

    func_020984e8();
    w0 = func_02098a0c();
    v1 = func_0209727c(a, b);

    if (v1 != 0) {
        // no change
    } else {
        if (flag == 0) {
            return 0;
        }
        v1 = b;
        func_02097204(a, b);
        flag = 0;
    }

    v2 = func_020644cc(v1);
    v3 = func_02097234(a, b, v2);
    v4 = func_020970cc(v3, c);

    if (v4 != 0) {
        if (v1 == 1 && flag == 1) {
            func_02097204(a, b);
        } else {
            func_02097d18(w0, v3);
        }
    }
    return v4;
}
