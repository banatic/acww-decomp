/* func_0206bfb4 @ 0x0206bfb4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a941c(void *);
extern void func_020edb3c(void *);

extern unsigned char data_020def9c[];
extern unsigned char data_020e3e68[];

void *func_0206bfb4(void *obj)
{
    *(volatile unsigned int *) obj = (unsigned int) data_020def9c;
    *(volatile unsigned int *) obj = (unsigned int) data_020e3e68;
    func_020a941c(obj);
    func_020edb3c(obj);
    return obj;
}
