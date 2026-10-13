/* func_020efa3c @ 0x020efa3c, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_0210b7e0(void *);

void func_020efa3c(void *p)
{
    func_0210b7e0(p);
    ((unsigned char *) p)[8] = 0;
    ((unsigned short *) ((char *) p + 6))[0] = 0;
    ((unsigned char *) p)[9] = 0;
    ((unsigned short *) ((char *) p + 4))[0] = 0;
    ((unsigned char *) p)[10] = 0x7f;
}
