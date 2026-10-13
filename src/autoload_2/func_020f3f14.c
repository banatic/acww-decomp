/* func_020f3f14 @ 0x020f3f14, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4514(void *p);

extern unsigned char data_0213ef80[];

void *func_020f3f14(void *p)
{
    *((unsigned int *) p) = (unsigned int) data_0213ef80;
    func_020f4514(p);
    return p;
}
