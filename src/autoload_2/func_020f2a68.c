/* func_020f2a68 @ 0x020f2a68, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f45c4(void *);
extern unsigned char data_0213ee14;

void *func_020f2a68(void *p)
{
    func_020f45c4(p);
    *(unsigned int *) p = (unsigned int) &data_0213ee14;
    *((unsigned char *) p + 4) = 0x2f;
    return p;
}
