/* func_ov088_02278cd8 @ 0x02278cd8, 0x20 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *);
extern void func_020edb3c(void *);
extern int data_ov088_02279c58;

void *func_ov088_02278cd8(void *self)
{
    *(void **) self = (void *) &data_ov088_02279c58;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
