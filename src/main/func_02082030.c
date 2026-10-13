/* func_02082030 @ 0x02082030, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *);
extern char data_020e191c;

void *func_02082030(void *arg)
{
    *(void **) arg = (void *) &data_020e191c;
    func_020a8c38(arg);
    return arg;
}
