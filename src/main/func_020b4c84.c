/* func_020b4c84 @ 0x020b4c84, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e5254[];
extern char data_020e3e68[];
extern void func_020a941c(void *);

void *func_020b4c84(void *obj)
{
    volatile void **p = (volatile void **) obj;
    *p = (void *) data_020e5254;
    *p = (void *) data_020e3e68;
    func_020a941c(obj);
    return obj;
}
