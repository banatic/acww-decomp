/* func_ov101_0229c5dc @ 0x0229c5dc, 0x48 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(void *p, int a);
extern void func_ov002_0220a374(void *p, int a);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov101_0229c5dc(unsigned char *base, unsigned char b)
{
    func_ov002_02207d24(base + 0x21b4, 1);
    base[0xb6] = base[0x8d];
    base[0xb5] = b;
    func_ov002_0220a374(base + 0x229c, 6);
    func_ov002_02208098(base, 0x10);
}
