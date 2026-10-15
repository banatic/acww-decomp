/* func_ov134_0229a918 @ 0x0229a918, 0x54 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229aa4c(int object, int index);
extern int func_ov134_0229aa78(unsigned char *p, int i);
extern void func_0206fdd4(unsigned char *p, int a, int b, int c, int d, int e);
extern void func_ov134_022995b0(unsigned char *p, int i);

void func_ov134_0229a918(unsigned char *p, int a1, int a2)
{
    int v1 = func_ov134_0229aa4c((int) p, a1) + 1;
    int v2 = func_ov134_0229aa78(p, a1);
    int v3;
    if (p[0xa0] == 0 && a1 == 3) {
        v3 = v1 + 1;
    } else {
        v3 = v1 + 2;
    }
    func_0206fdd4(p + 0x870, v1, v2, v3, v2 + 1, a2);
    func_ov134_022995b0(p, 2);
}
