/* func_ov121_022999a0 @ 0x022999a0, 0x4c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov121_0229c3a8;
extern void func_ov002_02209ac8(void *);
extern void func_ov002_0220ba0c(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_02207e28(void *);
extern void func_ov002_0220826c(void *);

void *func_ov121_022999a0(void *self)
{
    *(void **) self = &data_ov121_0229c3a8;
    func_ov002_02209ac8((char *) self + 0x528);
    func_ov002_0220ba0c((char *) self + 0x40c);
    func_ov002_02209cb4((char *) self + 0x3a8);
    func_ov002_02207e28((char *) self + 0x2d8);
    func_ov002_0220826c(self);
    return self;
}
