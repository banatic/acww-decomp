/* func_ov102_0229c200 @ 0x0229c200, 0x88 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *, int, int, void *);
extern void func_ov002_0220ba0c(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void func_ov002_02207e28(void *);
extern void func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void func_ov094_0229afe0(void *);
extern void func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

extern unsigned char data_ov102_0229ea60[];
extern void func_02070be8(void);

void *func_ov102_0229c200(void *self)
{
    *(void **) self = (void *) data_ov102_0229ea60;
    func_02138c48((char *) self + 0x23f4, 2, 0x6c, (void *) func_02070be8);
    func_ov002_0220ba0c((char *) self + 0x22d8);
    func_ov002_02209cb4((char *) self + 0x2274);
    func_ov002_02209e38((char *) self + 0x225c);
    func_ov002_02207e28((char *) self + 0x218c);
    func_ov094_0229a2d0((char *) self + 0xb54);
    func_ov094_0229bc30((char *) self + 0xb2c);
    func_ov094_0229afe0((char *) self + 0xcc);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
