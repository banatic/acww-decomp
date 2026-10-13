/* func_020b4ab4 @ 0x020b4ab4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a941c(void *);

extern unsigned char data_020e3e68[];
extern unsigned char data_020e5230[];

void *func_020b4ab4(void *p)
{
    volatile unsigned int *vp;
    vp = (volatile unsigned int *) p;
    *vp = (unsigned int) (unsigned int) data_020e5230;
    *vp = (unsigned int) (unsigned int) data_020e3e68;
    func_020a941c(p);
    return p;
}
