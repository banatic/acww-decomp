/* func_ov123_0229b56c @ 0x0229b56c, 0x2c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208090(unsigned int, unsigned int);
extern void *func_ov002_0220a720(unsigned int, unsigned int);
extern unsigned char *func_ov002_02208098(unsigned int, unsigned char value);

void func_ov123_0229b56c(unsigned int a, unsigned int b, unsigned int c)
{
    func_ov002_02208090(a, b);
    func_ov002_0220a720(a + 0x5030, c);
    func_ov002_02208098(a, 12);
}
