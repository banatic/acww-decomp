/* func_020f53c8 @ 0x020f53c8, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f5914(void *p);
extern void func_020edb3c(void *p);

extern unsigned char data_020d8414[];
extern unsigned char data_0213f058[];

void *func_020f53c8(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) data_0213f058;
    *(volatile unsigned int *) p = (unsigned int) data_020d8414;
    func_020f5914(p);
    func_020edb3c(p);
    return p;
}
