/* func_ov131_0229acf8 @ 0x0229acf8, 0x3c bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov130_0229a790(void *);
extern void func_ov002_0220afdc(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);
extern int data_ov131_0229b8f0;

void *func_ov131_0229acf8(void *self)
{
    *(int *) self = (int) &data_ov131_0229b8f0;
    func_ov130_0229a790((char *) self + 0x2c4);
    func_ov002_0220afdc((char *) self + 0xf8);
    func_ov002_02209cb4((char *) self + 0x94);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
