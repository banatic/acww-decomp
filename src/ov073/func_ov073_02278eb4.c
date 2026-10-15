/* func_ov073_02278eb4 @ 0x02278eb4, 0x18 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb70(void *arg);
extern char data_ov073_02279a70;

void *func_ov073_02278eb4(void *arg)
{
    func_0202eb70(arg);
    *(void **) arg = &data_ov073_02279a70;
    return arg;
}
