/* func_ov145_0229a458 @ 0x0229a458, 0x3e bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov145_0229a15c(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov145_02299e08(void *p);
extern int func_ov145_02299f30(void *p);
extern int func_ov145_02299eec(void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);

void func_ov145_0229a458(char *param)
{
    if (func_ov145_0229a15c(param)) {
        func_ov002_02208098((void *) (param), 3);
        func_ov145_02299e08(param);
    }
    {
        int v1 = func_ov145_02299f30(param);
        int v2 = func_ov145_02299eec(param);
        param += 0xc8;
        func_ov002_0220a0b4(param, v1, v2);
    }
}
