/* func_ov106_0229d9fc @ 0x0229d9fc, 0x84 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(char *p);
extern int func_0208e4bc(char *p);
extern int func_ov002_0220a6e0(char *p);
extern int func_ov002_0220a768(char *p, int x);
extern int func_ov002_0220a72c(char *p, int x);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov106_0229cc50(char *p);
extern void func_ov002_02208098(char *p, int x);
extern void func_ov002_02207e9c(char *p, int a, int b);
extern void func_ov002_0220b7ec(char *p);

void func_ov106_0229d9fc(char *param)
{
    if (func_ov002_0220a700(param + 0x3fb4) != 0) {
        int v4;
        int v6;
        int v2;

        if (func_0208e4bc(param + 0x22a0) == 0) {
            return;
        }
        v4 = func_ov002_0220a6e0(param + 0x3fb4);
        v6 = func_ov002_0220a768(param + 0x3fb4, -1);
        v2 = func_ov002_0220a72c(param + 0x3fb4, -1);
        func_ov002_0220a0b4(param + 0x22a0, v4 + v6, v4 + v2);
    } else {
        func_ov106_0229cc50(param);
        func_ov002_02208098(param, 0x20);
        func_ov002_02207e9c(param, 0, 0);
        func_ov002_0220b7ec(param + 0x26f8);
    }
}
