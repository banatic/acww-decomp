/* func_ov079_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov079_0227a104[];
extern void func_ov079_02278d1c(void *p);
extern void func_0202ee5c(void *p);

void *func_ov079_02278a00(void *self)
{
    *(void **) self = data_ov079_0227a104;
    func_ov079_02278d1c((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
