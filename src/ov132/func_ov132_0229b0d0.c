/* func_ov132_0229b0d0 @ 0x0229b0d0, 0x34 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fc4c(int);
extern void *func_ov002_0220a720(unsigned char *, int);
extern void func_ov002_02208090(unsigned char *, int);
extern unsigned char *func_ov002_02208098(unsigned char *, unsigned char value);

void func_ov132_0229b0d0(unsigned char *p)
{
    p[0x1505] = 0x44;
    func_0206fc4c(0);
    func_ov002_0220a720(p + 0xf8, 6);
    func_ov002_02208090(p, 2);
    func_ov002_02208098(p, 5);
}
