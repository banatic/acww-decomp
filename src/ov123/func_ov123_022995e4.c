/* func_ov123_022995e4 @ 0x022995e4, 0x4c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220afdc(void *p);
extern void func_ov002_02209cb4(void *p);
extern void func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);
extern void func_02138c48(void *p, int a, int b, void (*f)(void));
extern void func_02070be8(void);
extern char data_ov123_0229d024;

void *func_ov123_022995e4(void *self)
{
    *(void **) self = &data_ov123_0229d024;
    func_ov002_0220afdc((char *) self + 0x5030);
    func_ov002_02209cb4((char *) self + 0x1cc);
    func_02138c48((char *) self + 0xb8, 1, 0x6c, func_02070be8);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
