/* func_ov138_0229c518 @ 0x0229c518, 0x3c bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229beb0(void *p);
extern void func_ov002_0220afdc(void *p);
extern void func_ov002_02209cb4(void *p);
extern void func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);
extern char data_ov138_0229d4e0;

void *func_ov138_0229c518(void *p)
{
    char *self = (char *) p;
    *(unsigned int *) self = (unsigned int) &data_ov138_0229d4e0;
    func_ov134_0229beb0(self + 0x2c8);
    func_ov002_0220afdc(self + 0xfc);
    func_ov002_02209cb4(self + 0x98);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
