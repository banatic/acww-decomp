/* func_ov144_0229aa30 @ 0x0229aa30, 0x3e bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov144_0229a404(void *p);
extern int func_ov144_0229a208(void *p);
extern int func_ov144_0229a198(void *p);
extern void func_ov144_0229a0a4(void *p);
extern void func_ov002_02208098(void *p, int n);
extern void func_ov002_0220a0b4(void *p, int a, int b);

void func_ov144_0229aa30(void *p)
{
    int a, b;

    if (func_ov144_0229a404(p)) {
        func_ov002_02208098(p, 3);
        func_ov144_0229a0a4(p);
    }

    a = func_ov144_0229a208(p);
    b = func_ov144_0229a198(p);
    func_ov002_0220a0b4((char *) p + 0xc4, a, b);
}
