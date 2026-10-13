/* func_ov140_02299f34 @ 0x02299f34, 0x5c bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov140_0229b404;
extern void func_02070be8(void);
extern void func_02138c48(void *a, int b, int c, void (*cb)(void));
extern void func_ov002_0220afdc(void *a);
extern void func_ov002_02209cb4(void *a);
extern void func_ov139_02299b30(void *a);
extern void func_ov002_0220826c(void *a);
extern void func_ov002_02207f6c(void *a);

void *func_ov140_02299f34(void *self)
{
    *(int **) self = &data_ov140_0229b404;
    func_02138c48((char *) self + 0x1abc, 3, 0x6c, func_02070be8);
    func_ov002_0220afdc((char *) self + 0x12f0);
    func_ov002_02209cb4((char *) self + 0x128c);
    func_ov139_02299b30((char *) self + 0x8e8);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
