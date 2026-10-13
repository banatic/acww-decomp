/* func_02080684 @ 0x02080684, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081edc(char *p);
extern int func_02081e10(char *p);
extern int func_0209e3ac(int a, int b, int c);
extern int func_0209e350(int a, int b);

int func_02080684(char *a, int b)
{
    int min = 0x7fffffff;
    int locals[3];
    int i;
    locals[1] = 0;
    for (i = 0; i < 8; a += 0x80, i++) {
        int res;
        int candidate;
        if (!func_02081edc(a)) {
            continue;
        }
        locals[0] = func_02081e10(a);
        res = func_0209e3ac(b, locals[0], 0x3f);
        if (res == 1) {
            candidate = func_0209e350(locals[0], b);
            if (candidate < min) {
                min = candidate;
            }
        } else if (res == ~locals[1]) {
            candidate = func_0209e350(b, locals[0]);
            if (candidate < min) {
                min = candidate;
            }
        } else {
            return 0;
        }
    }
    return min;
}
