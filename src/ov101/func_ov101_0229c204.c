/* func_ov101_0229c204 @ 0x0229c204, 0x88 bytes, Thumb, module ov101
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

extern unsigned char data_ov101_0229e078[];

void *func_ov101_0229c204(void *self)
{
    *(void **) self = (void *) data_ov101_0229e078;
    func_ov002_0220afdc((char *) self + 0x2810);
    func_ov002_0220ba0c((char *) self + 0x26f4);
    func_ov002_02209ac8((char *) self + 0x2300);
    func_ov002_02209cb4((char *) self + 0x229c);
    func_ov002_02209e38((char *) self + 0x2284);
    func_ov002_02207e28((char *) self + 0x21b4);
    func_ov094_0229a2d0((char *) self + 0x0b7c);
    func_ov094_0229bc30((char *) self + 0x0b54);
    func_ov094_0229afe0((char *) self + 0xf4);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
