/* func_020a8d78 @ 0x020a8d78, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e3e04;
extern void *func_020a9260(void *);

void *func_020a8d78(void *arg)
{
    *(void **) arg = &data_020e3e04;
    func_020a9260(arg);
    return arg;
}
