/* func_ov072_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov072_02278d98(void *ptr);
extern void func_0202ee5c(void *ptr);
extern char data_ov072_02279b08;

void *func_ov072_02278a00(void *self)
{
    *(void **) self = &data_ov072_02279b08;
    func_ov072_02278d98((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
