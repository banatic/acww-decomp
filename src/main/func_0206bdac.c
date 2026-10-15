/* func_0206bdac @ 0x0206bdac, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020defe4;
extern char data_020e3e68;
extern void *func_0206bfdc(void *);
extern void *func_020a941c(void *);

void *func_0206bdac(void *p)
{
    *(void **) p = &data_020defe4;
    func_0206bfdc((char *) p + 0x9c);
    func_0206bfdc((char *) p + 0x60);
    *(void **) p = &data_020e3e68;
    func_020a941c(p);
    return p;
}
