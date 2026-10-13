/* func_ov147_02299e2c @ 0x02299e2c, 0x2c bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov147_0229a614(void *ptr);
extern void func_0203ded0(void);
extern int func_020b5e10(void);
extern void func_020b6434(int a, int b, int c, int d);
extern void func_ov147_0229a01c(void *ptr);

void func_ov147_02299e2c(void *p)
{
    if (func_ov147_0229a614((char *) p + 0xb0)) {
        int v = 2;
        func_0203ded0();
        func_020b6434(func_020b5e10(), 0x2c, v, v);
        func_ov147_0229a01c(p);
    }
}
