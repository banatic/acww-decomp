/* func_020820c0 @ 0x020820c0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e18d4;
extern void *func_020a8c38(void *obj);
extern void func_020edb3c(void *obj);

void *func_020820c0(void *obj)
{
    *(void **) obj = (void *) &data_020e18d4;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}
