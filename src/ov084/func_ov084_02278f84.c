/* func_ov084_02278f84 @ 0x02278f84, 0x20 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *p);
extern __arm void func_020edb3c(void *p);
extern int data_ov084_0227941c;

void *func_ov084_02278f84(void *self)
{
    *(void **) self = &data_ov084_0227941c;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
