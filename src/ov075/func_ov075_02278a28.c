/* func_ov075_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov075_022799fc;
extern void *func_ov075_02278ba0(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);

void *func_ov075_02278a28(void *self)
{
    *(void **) self = &data_ov075_022799fc;
    func_ov075_02278ba0((char *) self + 0x658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
