/* func_ov004_022254ac @ 0x022254ac, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02254888;
extern void *func_0201615c(void *);

void *func_ov004_022254ac(void *arg)
{
    *((void **) arg) = &data_ov004_02254888;
    func_0201615c(arg);
    return arg;
}
