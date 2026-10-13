/* func_ov114_0229d148 @ 0x0229d148, 0x20 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern char data_ov114_0229daf0;

void *func_ov114_0229d148(void *self)
{
    func_020a8cac(self);
    *(void **) self = &data_ov114_0229daf0;
    func_020a8c1c(self);
    return self;
}
