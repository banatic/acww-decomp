/* func_ov096_0229c22c @ 0x0229c22c, 0xb0 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov096_022a23e8;
extern void func_02066688(void *);
extern void func_ov002_0220b464(void *);
extern void func_0206e35c(void *);
extern void func_ov002_0220ba0c(void *);
extern void func_ov002_02209ac8(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void func_ov002_02207e28(void *);
extern void func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void func_ov094_0229afe0(void *);
extern void func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

struct Big {
    void *vtable;
};

struct Big *func_ov096_0229c22c(struct Big *self)
{
    self->vtable = &data_ov096_022a23e8;
    func_02066688((char *) self + 0x2f28);
    func_02066688((char *) self + 0x2e28);
    func_ov002_0220b464((char *) self + 0x2d9c);
    func_0206e35c((char *) self + 0x2a74);
    func_ov002_0220ba0c((char *) self + 0x2958);
    func_ov002_02209ac8((char *) self + 0x2564);
    func_ov002_02209cb4((char *) self + 0x2500);
    func_ov002_02209e38((char *) self + 0x24e8);
    func_ov002_02207e28((char *) self + 0x2418);
    func_ov094_0229a2d0((char *) self + 0x0de0);
    func_ov094_0229bc30((char *) self + 0x0db8);
    func_ov094_0229afe0((char *) self + 0x0358);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
