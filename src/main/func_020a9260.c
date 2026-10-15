/* func_020a9260 @ 0x020a9260, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a941c(void *);

extern unsigned char data_020e3de4[];

void *func_020a9260(void *arg)
{
    *(void **) arg = (void *) data_020e3de4;
    func_020a941c(arg);
    return arg;
}
