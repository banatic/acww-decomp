/* func_ov103_0229c180 @ 0x0229c180, 0xa8 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066688(void *);
extern void func_ov002_0220b464(void *);
extern void func_0206e35c(void *);
extern void func_ov002_0220ba0c(void *);
extern void func_ov002_02209ac8(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void func_ov002_02207e28(void *);
extern void func_ov094_0229a2d0(void *);
extern void func_ov128_0229bc30(void *);
extern void func_ov094_0229afe0(void *);
extern void func_ov002_0220826c(void *);

extern unsigned char data_ov103_0229e2e0[];

void *func_ov103_0229c180(void *self)
{
    *(unsigned int *) self = (unsigned int) data_ov103_0229e2e0;
    func_02066688((char *) self + 0x2ca0);
    func_02066688((char *) self + 0x2ba0);
    func_ov002_0220b464((char *) self + 0x2b10);
    func_0206e35c((char *) self + 0x27e8);
    func_ov002_0220ba0c((char *) self + 0x26cc);
    func_ov002_02209ac8((char *) self + 0x22d8);
    func_ov002_02209cb4((char *) self + 0x2274);
    func_ov002_02209e38((char *) self + 0x225c);
    func_ov002_02207e28((char *) self + 0x218c);
    func_ov094_0229a2d0((char *) self + 0x0b54);
    func_ov128_0229bc30((char *) self + 0x0b2c);
    func_ov094_0229afe0((char *) self + 0xcc);
    func_ov002_0220826c(self);
    return self;
}
