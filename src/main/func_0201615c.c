/* func_0201615c @ 0x0201615c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d8bd4;
extern void *func_02066994(void *);

void *func_0201615c(void *arg)
{
    *((void **) arg) = &data_020d8bd4;
    func_02066994(arg);
    return arg;
}
