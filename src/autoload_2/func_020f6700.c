/* func_020f6700 @ 0x020f6700, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f6f70(void *);

void func_020f6700(void *param)
{
    func_020f6f70((char *) param + 0x14);
    ((unsigned char *) param)[0x1e] = 0;
}
