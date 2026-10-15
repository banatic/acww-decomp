/* func_020669e0 @ 0x020669e0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020df008[];
extern void *func_02066a84(void *p);
extern void func_020a8188(void *p);

void *func_020669e0(void *obj)
{
    *(void **) obj = data_020df008;
    func_02066a84((char *) obj + 0x20);
    func_020a8188(obj);
    return obj;
}
