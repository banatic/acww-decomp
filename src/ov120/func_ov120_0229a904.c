/* func_ov120_0229a904 @ 0x0229a904, 0x24 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov120_0229a438(void *p, int n);
extern void func_ov120_0229a428(void *p, int n);

void func_ov120_0229a904(void *p)
{
    func_ov120_0229a438(p, 0x40);
    func_ov120_0229a428(p, 0x100);
    ((unsigned char *) p)[0xa7] = 0xf;
}
