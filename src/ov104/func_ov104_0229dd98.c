/* func_ov104_0229dd98 @ 0x0229dd98, 0x6c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(unsigned char *p);
extern int func_0208e4bc(unsigned char *p);
extern int func_ov002_0220a6e0(unsigned char *p);
extern int func_ov002_0220a768(unsigned char *p, int a);
extern int func_ov002_0220a72c(unsigned char *p, int a);
extern void func_ov002_0220a0b4(unsigned char *p, int a, int b);
extern void func_ov104_0229d378(unsigned char *p);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);

void func_ov104_0229dd98(unsigned char *param)
{
    if (func_ov002_0220a700(param + 0x41b4)) {
        if (func_0208e4bc(param + 0x24a0)) {
            int a = func_ov002_0220a6e0(param + 0x41b4);
            int b = func_ov002_0220a768(param + 0x41b4, -1);
            int c = func_ov002_0220a72c(param + 0x41b4, -1);
            func_ov002_0220a0b4(param + 0x24a0, a + b, a + c);
        }
    } else {
        func_ov104_0229d378(param);
        func_ov002_022080a0((void *) (param), 1);
    }
}
