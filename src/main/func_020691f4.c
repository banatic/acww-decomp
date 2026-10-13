/* func_020691f4 @ 0x020691f4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a941c(void *obj);
extern void func_020edb3c(void *obj);

extern unsigned char data_020defc0[];
extern unsigned char data_020e3e68[];

void *func_020691f4(void *obj)
{
    ((volatile unsigned int *) obj)[0] = (unsigned int) data_020defc0;
    ((volatile unsigned int *) obj)[0] = (unsigned int) data_020e3e68;
    func_020a941c(obj);
    func_020edb3c(obj);
    return obj;
}
