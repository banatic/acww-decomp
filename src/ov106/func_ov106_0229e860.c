/* func_ov106_0229e860 @ 0x0229e860, 0x2c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a098(void *receiver);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_0220ab84(char *addr, int value);

void func_ov106_0229e860(char *p)
{
    func_ov094_0229a098((void *) ((char *) p + 0xb80));
    func_ov002_0220af94((void *) ((char *) p + 0x3fb4));
    func_ov002_0220ab84(p + 0x3fb4, 0x88);
}
