/* turtle: 2 functions, module ov080
 * mwccarm 1.2/base -O4,s
 * func_ov080_02278a28 @ 0x02278a28, 0x2c bytes, Thumb
 * func_ov080_02278a00 @ 0x02278a00, 0x28 bytes, Thumb
 */

extern int *func_ov080_02278e30(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern unsigned char data_ov080_022792ec[];

void *func_ov080_02278a28(void *obj)
{
    *(unsigned int *) obj = (unsigned int) data_ov080_022792ec;
    func_ov080_02278e30((char *) obj + 0x658);
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}

void *func_ov080_02278a00(void *self)
{
    *(int **) self = ((int *) data_ov080_022792ec);
    func_ov080_02278e30((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
