/* func_ov123_022995a0 @ 0x022995a0, 0x44 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov123_0229d024;
extern void func_ov002_0220afdc(void *p);
extern void func_ov002_02209cb4(void *p);
extern void func_02138c48(void *p, int a, int b, void (*func)(void));
extern void func_02070be8(void);
extern void func_ov002_0220826c(void *p);

void *func_ov123_022995a0(void *p)
{
    *(int **) p = &data_ov123_0229d024;
    func_ov002_0220afdc((char *) p + 0x5030);
    func_ov002_02209cb4((char *) p + 0x1cc);
    func_02138c48((char *) p + 0xb8, 1, 0x6c, func_02070be8);
    func_ov002_0220826c(p);
    return p;
}
