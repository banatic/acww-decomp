/* func_02075fc4 @ 0x02075fc4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a1350(int p0, int p1);
extern char *func_020a00fc(int x);
extern int func_02075ff8(int p0, int p1, char *p2, int p3, int p4);

int func_02075fc4(int p0, int p1)
{
    int a;
    char *b;
    char *c;
    a = func_020a1350(p0, p1);
    b = func_020a00fc(a);
    if (b == 0) {
        c = (char *) 0x17400;
    } else {
        c = b + 4;
    }
    return func_02075ff8(p0, a, c, 1, p1);
}
