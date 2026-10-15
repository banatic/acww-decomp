/* func_ov135_0229c518 @ 0x0229c518, 0x3c bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern char *func_ov134_0229beb0(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);
extern char data_ov135_0229d610;

void *func_ov135_0229c518(void *self)
{
    *(void **) self = &data_ov135_0229d610;
    func_ov134_0229beb0((char *) self + 0x2C8);
    func_ov002_0220afdc((char *) self + 0xFC);
    func_ov002_02209cb4((char *) self + 0x98);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
