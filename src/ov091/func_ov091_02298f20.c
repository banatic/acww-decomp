/* func_ov091_02298f20 @ 0x02298f20, 0x3c bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov091_02299530;
extern void *func_ov002_02209c60(void *p);
extern void *func_ov002_0220b410(void *p);
extern void *func_0206e35c(void *p);
extern void *func_ov002_0220826c(void *p);

void *func_ov091_02298f20(void *self)
{
    *(int *) self = (int) &data_ov091_02299530;
    func_ov002_02209c60((char *) self + 0x434);
    func_ov002_0220b410((char *) self + 0x3bc);
    func_0206e35c((char *) self + 0x94);
    func_ov002_0220826c(self);
    return self;
}
