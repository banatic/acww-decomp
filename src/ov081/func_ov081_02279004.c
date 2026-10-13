/* func_ov081_02279004 @ 0x02279004, 0x20 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *);
extern void func_020edb3c(void *);
extern int data_ov081_0227972c;

void *func_ov081_02279004(void *arg)
{
    *(void **) arg = (void *) &data_ov081_0227972c;
    func_0202eb20(arg);
    func_020edb3c(arg);
    return arg;
}
