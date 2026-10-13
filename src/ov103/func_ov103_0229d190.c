/* func_ov103_0229d190 @ 0x0229d190, 0x44 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(char *p);
extern void func_ov002_02208098(char *p, unsigned char c);
extern int func_ov002_02209f9c(char *p);
extern void func_ov103_0229c2d4(char *p, int x);
extern void func_ov103_0229c994(char *p);

void func_ov103_0229d190(char *p)
{
    if (func_0208e484(p + 0x2274) != 0) {
        func_ov002_02208098(p, *(unsigned char *) (p + 0x2da7));
    }
    if (func_ov002_02209f9c(p + 0x2274) != 0) {
        func_ov103_0229c2d4(p, 0x40);
        func_ov103_0229c994(p);
    }
}
