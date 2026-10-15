/* func_ov105_0229c180 @ 0x0229c180, 0xcc bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov105_0229fad0;
extern int func_ov002_0220afdc(void *);
extern int __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern int func_ov002_0220b464(void *);
extern int func_0206e35c(void *);
extern int func_ov002_0220ba0c(void *);
extern int func_ov002_02209ac8(void *);
extern int func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern int func_ov002_02207e28(void *);
extern int func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern int func_ov094_0229afe0(void *);
extern void func_02066688(void *);
extern int func_ov002_0220826c(void *);

#define DisposeElement_func_02066688 ((void (*)(void *)) func_02066688)

void *func_ov105_0229c180(void *self)
{
    *(int *) self = (int) &data_ov105_0229fad0;
    func_ov002_0220afdc((char *) self + 0x5fb8);
    __cxa_vec_cleanup((char *) self + 0x2db8, 0x32, 0x100, DisposeElement_func_02066688);
    func_ov002_0220b464((char *) self + 0x2d40);
    func_0206e35c((char *) self + 0x2a18);
    func_ov002_0220ba0c((char *) self + 0x28fc);
    func_ov002_02209ac8((char *) self + 0x2508);
    func_ov002_02209cb4((char *) self + 0x24a4);
    func_ov002_02209e38((char *) self + 0x248c);
    func_ov002_02207e28((char *) self + 0x23bc);
    func_ov094_0229a2d0((char *) self + 0xd84);
    func_ov094_0229bc30((char *) self + 0xd5c);
    func_ov094_0229afe0((char *) self + 0x2fc);
    func_02066688((char *) self + 0x1b4);
    func_02066688((char *) self + 0xb4);
    func_ov002_0220826c(self);
    return self;
}

#undef DisposeElement_func_02066688
