/* func_ov126_022a0c64 @ 0x022a0c64, 0x6c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(char *);
extern int func_0208e4bc(char *);
extern int func_ov002_0220a6e0(char *);
extern int func_ov002_0220a768(char *, int);
extern int func_ov002_0220a72c(char *, int);
extern void func_ov002_0220a0b4(char *, int, int);
extern void func_ov126_0229ffdc(char *);
extern void func_ov002_022080a0(char *, int);

void func_ov126_022a0c64(char *param)
{
    if (func_ov002_0220a700(param + 0x3dc4) != 0) {
        if (func_0208e4bc(param + 0x3f90) != 0) {
            int v4 = func_ov002_0220a6e0(param + 0x3dc4);
            int v6 = func_ov002_0220a768(param + 0x3dc4, -1);
            int v2 = func_ov002_0220a72c(param + 0x3dc4, -1);
            func_ov002_0220a0b4(param + 0x3f90, v4 + v6, v4 + v2);
        }
    } else {
        func_ov126_0229ffdc(param);
        func_ov002_022080a0(param, 1);
    }
}
