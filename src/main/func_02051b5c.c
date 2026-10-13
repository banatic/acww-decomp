/* func_02051b5c @ 0x02051b5c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *obj);

extern unsigned char data_020da13c[];
extern unsigned char data_020dcf40[];

void *func_02051b5c(void *obj)
{
    volatile unsigned int *p = (volatile unsigned int *) obj;
    *p = (unsigned int) data_020dcf40;
    *p = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return obj;
}
