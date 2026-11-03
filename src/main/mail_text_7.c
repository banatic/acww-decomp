/* mail_text_7: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203dd7c @ 0x0203dd7c, 0x20 bytes, Thumb
 * func_0203dd54 @ 0x0203dd54, 0x28 bytes, Thumb
 */

extern void *func_020a941c(void *p);
extern void func_020edb3c(unsigned int *p);
extern unsigned char data_020da9ac[];
extern unsigned char data_020e3e68[];

void *func_0203dd7c(void **p)
{
    *p = (void *) ((char *) data_020da9ac);
    *p = (void *) ((char *) data_020e3e68);
    func_020a941c(p);
    return p;
}

unsigned int *func_0203dd54(unsigned int *p)
{
    *p = (unsigned int) data_020da9ac;
    *p = (unsigned int) data_020e3e68;
    func_020a941c((void *) p);
    func_020edb3c(p);
    return p;
}
