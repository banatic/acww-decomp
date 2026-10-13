/* func_0209f500 @ 0x0209f500, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066994(void *p);
extern void func_020edb3c(void *p);

extern unsigned char data_020e3758[];

void *func_0209f500(void *arg)
{
    *(void **) arg = (void *) data_020e3758;
    func_02066994(arg);
    func_020edb3c(arg);
    return arg;
}
