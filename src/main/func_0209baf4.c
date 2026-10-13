/* func_0209baf4 @ 0x0209baf4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209bd5c(void *);
extern void func_02095238(void *);

void func_0209baf4(void *arg)
{
    func_0209bd5c(arg);
    func_02095238((char *) arg + 0xc);
    *((unsigned char *) ((char *) arg + 0x2a)) = 7;
    *((unsigned short *) ((char *) arg + 0x2c)) = 0xfff1;
    *((unsigned char *) ((char *) arg + 0x2e)) = 0;
    *((unsigned char *) ((char *) arg + 0x2f)) = 0x18;
    *((unsigned char *) ((char *) arg + 0x30)) = 0;
}
