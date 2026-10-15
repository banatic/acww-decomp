/* func_ov107_0229c208 @ 0x0229c208, 0x8c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_0220afdc(void *p);
extern void *func_ov002_0220ba0c(void *p);
extern void *func_ov002_02209ac8(void *p);
extern void *func_ov002_02209cb4(void *p);
extern void func_ov002_02209e38(void *p);
extern void *func_ov002_02207e28(void *p);
extern void *func_ov094_0229a2d0(void *p);
extern void func_ov094_0229bc30(void *p);
extern void *func_ov094_0229afe0(void *p);
extern void *func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);
extern int data_ov107_0229e3b8;

void *func_ov107_0229c208(void *self)
{
    *(void **) self = (void *) &data_ov107_0229e3b8;
    func_ov002_0220afdc((char *) self + 0x2828);
    func_ov002_0220ba0c((char *) self + 0x270c);
    func_ov002_02209ac8((char *) self + 0x2318);
    func_ov002_02209cb4((char *) self + 0x22b4);
    func_ov002_02209e38((char *) self + 0x229c);
    func_ov002_02207e28((char *) self + 0x21cc);
    func_ov094_0229a2d0((char *) self + 0x0b94);
    func_ov094_0229bc30((char *) self + 0x0b6c);
    func_ov094_0229afe0((char *) self + 0x010c);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
