/* func_ov128_0229ba54 @ 0x0229ba54, 0x54 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O1,s
 */

extern char *func_ov127_022998a8(char *);
extern int func_ov127_02299a50(char *, int, char *, int *, int *);
extern int func_ov127_02299804(int, int);
extern int func_ov127_02299680(unsigned short);

void func_ov128_0229ba54(char *self)
{
    int a;
    int b;
    char *p;
    char *q;
    int r;

    p = func_ov127_022998a8(self + 0x4a4);
    q = p + 0x60;
    if (func_ov127_02299a50(self + 0x4a4, 0x80, q, &a, &b)) {
        r = func_ov127_02299804(a, b);
        if (r != -1) {
            *(int *) (self + 0x2d5c) = func_ov127_02299680((unsigned short) r);
        }
    }
}
