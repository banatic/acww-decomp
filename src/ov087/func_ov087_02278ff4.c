/* func_ov087_02278ff4 @ 0x02278ff4, 0x18 bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb70(void *p);
extern char data_ov087_0227945c;

void *func_ov087_02278ff4(void *arg)
{
    func_0202eb70(arg);
    *(void **) arg = (void *) &data_ov087_0227945c;
    return arg;
}
