/* func_ov084_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov084_02278fa4(void *);
extern void *func_0202ee5c(void *);
extern char data_ov084_022794ac;

void *func_ov084_02278a00(void *self)
{
    *(void **) self = &data_ov084_022794ac;
    func_ov084_02278fa4((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
