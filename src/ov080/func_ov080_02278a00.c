/* func_ov080_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov080_02278e30(void *);
extern void func_0202ee5c(void *);
extern int data_ov080_022792ec;

void *func_ov080_02278a00(void *self)
{
    *(int **) self = &data_ov080_022792ec;
    func_ov080_02278e30((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
