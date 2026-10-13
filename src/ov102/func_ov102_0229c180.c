/* func_ov102_0229c180 @ 0x0229c180, 0x80 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov102_0229ea60;
extern void func_02070be8(void);
extern void func_02138c48(void *ptr, int a, int b, void (*cb)(void));
extern void func_ov002_0220ba0c(void *ptr);
extern void func_ov002_02209cb4(void *ptr);
extern void func_ov002_02209e38(void *ptr);
extern void func_ov002_02207e28(void *ptr);
extern void func_ov094_0229a2d0(void *ptr);
extern void func_ov094_0229bc30(void *ptr);
extern void func_ov094_0229afe0(void *ptr);
extern void func_ov002_0220826c(void *ptr);

void *func_ov102_0229c180(void *self)
{
    *(void **) self = &data_ov102_0229ea60;

    func_02138c48((char *) self + 0x23f4, 2, 0x6c, &func_02070be8);
    func_ov002_0220ba0c((char *) self + 0x22d8);
    func_ov002_02209cb4((char *) self + 0x2274);
    func_ov002_02209e38((char *) self + 0x225c);
    func_ov002_02207e28((char *) self + 0x218c);
    func_ov094_0229a2d0((char *) self + 0x0b54);
    func_ov094_0229bc30((char *) self + 0x0b2c);
    func_ov094_0229afe0((char *) self + 0xcc);
    func_ov002_0220826c(self);

    return self;
}
