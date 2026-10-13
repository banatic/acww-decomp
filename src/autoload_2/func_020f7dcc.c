/* func_020f7dcc @ 0x020f7dcc, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f7d4c(void *);

void func_020f7dcc(void *p)
{
    func_020f7d4c(p);
    *(unsigned short *) ((char *) p + 0xe) = 0;
    *(unsigned short *) ((char *) p + 0x10) = 0;
    *(unsigned short *) ((char *) p + 0x12) = 0;
}
