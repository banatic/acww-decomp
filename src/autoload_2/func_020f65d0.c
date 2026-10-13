/* func_020f65d0 @ 0x020f65d0, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f69cc(void *);

void func_020f65d0(void *r0)
{
    int r1;
    r1 = (func_020f69cc(r0) >= 0) ? 1 : 0;
    *(unsigned char *) ((char *) r0 + 0x38) = r1;
    func_020f69cc((char *) r0 + 0x14);
}
