/* func_ov103_0229c774 @ 0x0229c774, 0x78 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229c2f4(void *p, int a);
extern int func_ov103_0229c820(void *p);
extern int func_ov103_0229c810(void *p);
extern void func_ov103_0229c2d4(void *p, int a);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov103_0229c774(unsigned char *param)
{
    if (func_ov103_0229c2f4(param, 8) != 0) {
        int a;
        int b;
        a = func_ov103_0229c820(param);
        b = func_ov103_0229c810(param);
        func_ov002_0220a0b4((unsigned char *) param + 0x2274, a, b);
        func_ov103_0229c2d4(param, 8);
    } else {
        int a;
        int b;
        unsigned char *p;
        a = func_ov103_0229c820(param);
        b = func_ov103_0229c810(param);
        func_ov002_0220a05c((unsigned char *) param + 0x2274, a, b, 3, 1);
        p = param + 0x8d;
        param[0x2da7] = *p;
        func_ov002_02208098(param, 0xb);
    }
}
