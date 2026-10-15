/* func_020f5178 @ 0x020f5178, 0x4c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fd1bc[];
extern int func_020eed18(void *p, int n);

void func_020f5178(void *p)
{
    if (data_021fd1bc[0x4d] != 0) {
        func_020eed18((char *) p + 8, 0xf);
    } else {
        func_020eed18((char *) p + 8, 0);
    }
}
