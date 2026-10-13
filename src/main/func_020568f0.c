/* func_020568f0 @ 0x020568f0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02057054(void *obj);
extern void func_020edb3c(void *obj);
extern unsigned char data_020dd164;

void *func_020568f0(void *obj)
{
    *(void **) obj = (void *) &data_020dd164;
    func_02057054(obj);
    func_020edb3c(obj);
    return obj;
}
