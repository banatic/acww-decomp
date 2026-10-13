/* func_ov101_0229c51c @ 0x0229c51c, 0x2c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov101_0229c6a0(void *);
extern void func_ov002_022096d8(void *, int);
extern void func_ov002_02208098(void *, int);

void func_ov101_0229c51c(unsigned char *base)
{
    base[0xb7] = 1;
    func_ov101_0229c6a0(base);
    func_ov002_022096d8(base + 0x2300, 0);
    func_ov002_02208098(base, 0x15);
}
