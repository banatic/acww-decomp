/* func_ov137_0229c4e0 @ 0x0229c4e0, 0x38 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov137_0229d440;
extern char *func_ov134_0229beb0(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);

void *func_ov137_0229c4e0(void *self)
{
    *(void **) self = &data_ov137_0229d440;
    func_ov134_0229beb0((char *) self + 0x2c4);
    func_ov002_0220afdc((char *) self + 0xf8);
    func_ov002_02209cb4((char *) self + 0x94);
    func_ov002_0220826c(self);
    return self;
}
