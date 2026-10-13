/* func_02083050 @ 0x02083050, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083100(void *arg);
extern int data_020e1a18;

void *func_02083050(void *arg)
{
    func_02083100(arg);
    *((void **) arg) = (void *) &data_020e1a18;
    return arg;
}
