/* func_0206bd74 @ 0x0206bd74, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206bfdc(void *);
extern void *func_020a941c(void *);
extern void func_020edb3c(void *);

extern unsigned char data_020defe4[];
extern unsigned char data_020e3e68[];

void *func_0206bd74(void *param)
{
    *(unsigned int *) param = (unsigned int) data_020defe4;
    func_0206bfdc((char *) param + 0x9c);
    func_0206bfdc((char *) param + 0x60);
    *(unsigned int *) param = (unsigned int) data_020e3e68;
    func_020a941c(param);
    func_020edb3c(param);
    return param;
}
