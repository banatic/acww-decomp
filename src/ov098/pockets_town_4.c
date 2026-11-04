/* pockets_town_4: 2 functions, module ov098
 * mwccarm 1.2/base -O4,s
 * func_ov098_022a2eb4 @ 0x022a2eb4, 0xc bytes, Thumb
 * func_ov098_022a2e9c @ 0x022a2e9c, 0x16 bytes, Thumb
 */

extern void func_ov098_022a2ec0(int a, int b, int c);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern int func_ov098_022a2df4(void *p);

void func_ov098_022a2eb4(int a, int b)
{
    func_ov098_022a2ec0(a, b, 2);
}

int func_ov098_022a2e9c(void *p)
{
    func_ov002_02208098(p, 0x2c);
    return func_ov098_022a2df4(p);
}
