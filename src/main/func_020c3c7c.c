/* func_020c3c7c @ 0x020c3c7c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020161ac(void *);
extern unsigned char data_020e86ec;

void *func_020c3c7c(void *obj)
{
    func_020161ac(obj);
    *(void **) obj = &data_020e86ec;
    return obj;
}
