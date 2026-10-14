/* func_ov105_0229c24c @ 0x0229c24c, 0xd4 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220afdc(void *);
extern void __cxa_vec_cleanup(void *p, int a, int b, void (*cb)(void *));
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
extern char data_ov105_0229fad0;

void *func_ov105_0229c24c(void *self)
{
    *(void **) self = &data_ov105_0229fad0;
    func_ov002_0220afdc((unsigned char *) self + 0x5fb8);
    __cxa_vec_cleanup((unsigned char *) self + 0x2db8, 0x32, 0x100, func_02066688);
    func_ov002_0220b464((unsigned char *) self + 0x2d40);
    func_0206e35c((unsigned char *) self + 0x2a18);
    func_ov002_0220ba0c((unsigned char *) self + 0x28fc);
    func_ov002_02209ac8((unsigned char *) self + 0x2508);
    func_ov002_02209cb4((unsigned char *) self + 0x24a4);
    func_ov002_02209e38((unsigned char *) self + 0x248c);
    func_ov002_02207e28((unsigned char *) self + 0x23bc);
    func_ov094_0229a2d0((unsigned char *) self + 0x0d84);
    func_ov094_0229bc30((unsigned char *) self + 0x0d5c);
    func_ov094_0229afe0((unsigned char *) self + 0x02fc);
    func_02066688((unsigned char *) self + 0x01b4);
    func_02066688((unsigned char *) self + 0xb4);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
