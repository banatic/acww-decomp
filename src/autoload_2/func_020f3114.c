/* func_020f3114 @ 0x020f3114, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f45c4(void *);

extern unsigned char data_0213ec74[];

void *func_020f3114(void *p)
{
    func_020f45c4(p);
    *(int *) p = (unsigned int) data_0213ec74;
    ((char *) p)[4] = 0x23;
    return p;
}
