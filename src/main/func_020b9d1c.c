/* func_020b9d1c @ 0x020b9d1c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ba1cc(void *);
extern void func_020ba108(void *);

extern unsigned char data_020e5934[];

void *func_020b9d1c(void *obj)
{
    func_020ba1cc(obj);
    *(void **) obj = (void *) data_020e5934;
    func_020ba108((void *) ((char *) obj + 0x10));
    return obj;
}
