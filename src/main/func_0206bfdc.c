/* func_0206bfdc @ 0x0206bfdc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a941c(void *p);
extern char data_020def9c;
extern char data_020e3e68;

void *func_0206bfdc(void *p)
{
    volatile unsigned int *vp = (volatile unsigned int *) p;
    *vp = (unsigned int) &data_020def9c;
    *vp = (unsigned int) &data_020e3e68;
    func_020a941c(p);
    return p;
}
