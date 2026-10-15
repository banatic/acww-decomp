/* func_ov002_0220826c @ 0x0220826c, 0x34 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int data_020da13c;
extern int data_ov002_0220bb24;
extern void func_020ee62c(void *);
extern void *func_ov002_022087bc(void *);
extern void func_ov002_022089d4(void *);

void *func_ov002_0220826c(void *self)
{
    *(int *) self = (int) &data_ov002_0220bb24;
    func_ov002_022087bc((void *) ((char *) self + 0x70));
    func_ov002_022089d4((void *) ((char *) self + 0x50));
    *(int *) self = (int) &data_020da13c;
    func_020ee62c(self);
    return self;
}
