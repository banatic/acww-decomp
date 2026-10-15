/* func_ov099_0229c180 @ 0x0229c180, 0x84 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov099_0229e040;
extern void func_02066688(void *);
extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_02209ac8(void *);
extern void *func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void *func_ov002_02207e28(void *);
extern void *func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void *func_ov094_0229afe0(void *);
extern void *func_ov002_0220826c(void *);

void *func_ov099_0229c180(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_ov099_0229e040;
    func_02066688((char *) self + 0x2800);
    func_ov002_0220ba0c((char *) self + 0x26cc);
    func_ov002_02209ac8((char *) self + 0x22d8);
    func_ov002_02209cb4((char *) self + 0x2274);
    func_ov002_02209e38((char *) self + 0x225c);
    func_ov002_02207e28((char *) self + 0x218c);
    func_ov094_0229a2d0((char *) self + 0xb54);
    func_ov094_0229bc30((char *) self + 0xb2c);
    func_ov094_0229afe0((char *) self + 0xcc);
    func_ov002_0220826c(self);
    return self;
}
