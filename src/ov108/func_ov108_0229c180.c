/* func_ov108_0229c180 @ 0x0229c180, 0x9c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220afdc(void *);
extern void func_ov002_0220ba0c(void *);
extern void func_ov002_02209ac8(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void func_ov002_02207e28(void *);
extern void func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void func_ov094_0229afe0(void *);
extern void func_02066688(void *);
extern void func_ov002_0220826c(void *);
extern char data_ov108_0229e098;

void *func_ov108_0229c180(void *self)
{
    *(void **) self = &data_ov108_0229e098;
    func_ov002_0220afdc((char *) self + 0x2a0c);
    func_ov002_0220ba0c((char *) self + 0x28f0);
    func_ov002_02209ac8((char *) self + 0x24fc);
    func_ov002_02209cb4((char *) self + 0x2498);
    func_ov002_02209e38((char *) self + 0x2480);
    func_ov002_02207e28((char *) self + 0x23b0);
    func_ov094_0229a2d0((char *) self + 0x0d78);
    func_ov094_0229bc30((char *) self + 0x0d50);
    func_ov094_0229afe0((char *) self + 0x02f0);
    func_02066688((char *) self + 0x01ac);
    func_02066688((char *) self + 0xac);
    func_ov002_0220826c(self);
    return self;
}
