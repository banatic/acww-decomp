/* func_ov126_0229f6a0 @ 0x0229f6a0, 0x80 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov126_022a20c8;
extern void func_ov002_0220ba0c(void *);
extern void func_020707b8(void *);
extern void func_02070be8(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_0220afdc(void *);
extern void func_02138c48(void *, int, int, void (*)(void *));
extern void func_ov124_0229f43c(void *);
extern void func_ov002_0220826c(void *);

void *func_ov126_0229f6a0(void *self)
{
    *(void **) self = &data_ov126_022a20c8;
    func_ov002_0220ba0c((char *) self + 0x412c);
    func_020707b8((char *) self + 0x40cc);
    func_02070be8((char *) self + 0x4060);
    func_02070be8((char *) self + 0x3ff4);
    func_ov002_02209cb4((char *) self + 0x3f90);
    func_ov002_0220afdc((char *) self + 0x3dc4);
    func_02138c48((char *) self + 0x24ec, 2, 0x6c, func_02070be8);
    func_ov124_0229f43c((char *) self + 0xb0);
    func_ov002_0220826c(self);
    return self;
}
