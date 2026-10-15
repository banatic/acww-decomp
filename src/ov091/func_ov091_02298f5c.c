/* func_ov091_02298f5c @ 0x02298f5c, 0x40 bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov091_02299530;

extern void *func_ov002_02209c60(void *ptr);
extern void *func_ov002_0220b410(void *ptr);
extern void *func_0206e35c(void *ptr);
extern void *func_ov002_0220826c(void *ptr);
extern void func_ov002_02207f6c(void *ptr);

void *func_ov091_02298f5c(void *self)
{
    ((int *) self)[0] = (int) &data_ov091_02299530;
    func_ov002_02209c60((char *) self + 0x434);
    func_ov002_0220b410((char *) self + 0x3bc);
    func_0206e35c((char *) self + 0x94);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
