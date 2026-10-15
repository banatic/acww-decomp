/* func_ov109_0229c7b0 @ 0x0229c7b0, 0x78 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229c2ac(void *p, int n);
extern void func_ov109_0229c28c(void *p, int n);
extern int func_ov109_0229c85c(void *p);
extern int func_ov109_0229c84c(void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov109_0229c7b0(unsigned char *arg0)
{
    if (func_ov109_0229c2ac(arg0, 4)) {
        int a = func_ov109_0229c85c(arg0);
        int b = func_ov109_0229c84c(arg0);
        func_ov002_0220a0b4(arg0 + 0x2274, a, b);
        func_ov109_0229c28c(arg0, 4);
    } else {
        int a = func_ov109_0229c85c(arg0);
        int b = func_ov109_0229c84c(arg0);
        func_ov002_0220a05c(arg0 + 0x2274, a, b, 3, 1);
        arg0[0x29d6] = arg0[0x8d];
        func_ov002_02208098(arg0, 8);
    }
}
