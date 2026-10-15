/* func_ov103_0229d018 @ 0x0229d018, 0x68 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(char *);
extern int func_ov002_0220b57c(char *);
extern int func_ov002_0220b5ec(char *, int);
extern int func_ov002_0220b59c(char *, int);
extern void func_ov002_0220a0b4(char *, int, int);
extern void func_ov002_02208090(char *, int);
extern unsigned char *func_ov002_022080a0(char *, unsigned char value);
extern void func_ov103_0229c7ec(char *);

void func_ov103_0229d018(char *param)
{
    if (func_ov002_0220b57c(param + 0x2b10) != 0) {
        if (func_0208e4bc(param + 0x2274) != 0) {
            int v1, v2;
            v1 = func_ov002_0220b5ec(param + 0x2b10, 1);
            v2 = func_ov002_0220b59c(param + 0x2b10, 1);
            func_ov002_0220a0b4(param + 0x2274, v1, v2);
        }
    } else {
        func_ov103_0229c7ec(param);
        func_ov002_02208090(param, 7);
        func_ov002_022080a0(param, 1);
    }
}
