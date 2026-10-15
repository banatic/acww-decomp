/* func_ov075_02278b80 @ 0x02278b80, 0x20 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov075_0227996c[];
extern void *func_0202eb20(void *self);
extern void func_020edb3c(void *self);

void *func_ov075_02278b80(void *self)
{
    *(void **) self = data_ov075_0227996c;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
