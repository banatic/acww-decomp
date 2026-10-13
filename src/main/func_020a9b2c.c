/* func_020a9b2c @ 0x020a9b2c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *arg);

extern unsigned char data_020e3d24[];

void *func_020a9b2c(void *arg)
{
    void **pp = (void **) arg;
    *pp = (void *) data_020e3d24;
    func_020edb3c(arg);
    return arg;
}
