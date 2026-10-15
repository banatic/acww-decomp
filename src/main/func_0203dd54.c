/* func_0203dd54 @ 0x0203dd54, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned int *func_0203dd54(unsigned int *p);
extern void *func_020a941c(unsigned int *p);
extern void func_020edb3c(unsigned int *p);

extern unsigned char data_020da9ac[];
extern unsigned char data_020e3e68[];

unsigned int *func_0203dd54(unsigned int *p)
{
    *p = (unsigned int) data_020da9ac;
    *p = (unsigned int) data_020e3e68;
    func_020a941c(p);
    func_020edb3c(p);
    return p;
}
