/* func_020f2888 @ 0x020f2888, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *);
extern void func_020edb3c(void *);

extern unsigned char data_0213ee7c[];

void *func_020f2888(void *p)
{
    *(unsigned int *) p = (unsigned int) data_0213ee7c;
    func_020f4514(p);
    func_020edb3c(p);
    return p;
}
