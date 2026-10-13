/* func_0202f10c @ 0x0202f10c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *obj);
extern void func_020edf54(void *obj);

extern unsigned char data_020da13c[];

void *func_0202f10c(void *obj)
{
    *(unsigned int *) obj = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}
