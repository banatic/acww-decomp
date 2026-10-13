/* func_020a941c @ 0x020a941c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a94a4(void *p);
extern void func_020a9c98(void *p);
extern int data_020e3e24;

void *func_020a941c(void *p)
{
    *(void **) p = (void *) &data_020e3e24;
    func_020a94a4(p);
    func_020a9c98((char *) p + 8);
    return p;
}
