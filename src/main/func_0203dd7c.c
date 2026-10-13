/* func_0203dd7c @ 0x0203dd7c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a941c(void *p);
extern char data_020da9ac, data_020e3e68;

void *func_0203dd7c(void **p)
{
    *p = (void *) &data_020da9ac;
    *p = (void *) &data_020e3e68;
    func_020a941c(p);
    return p;
}
