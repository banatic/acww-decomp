/* func_ov101_0229d97c @ 0x0229d97c, 0x70 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229af40(unsigned char *p, int n);
extern void func_ov094_0229bbd8(unsigned char *p, int n);
extern void func_ov094_0229a2b0(unsigned char *p, int n);
extern void func_ov002_02209e18(unsigned char *p);
extern void func_ov002_02209984(unsigned char *p, int a, int b, int _x);

void func_ov101_0229d97c(unsigned char *self)
{
    *(unsigned int *) (self + 0x94) = 0;
    func_ov094_0229af40(self + 0xf4, 2);
    func_ov094_0229bbd8(self + 0xb54, 2);
    func_ov094_0229a2b0(self + 0xb7c, 6);
    *(unsigned char *) (self + 0xb1) = 0x10;
    func_ov002_02209e18(self + 0x2284);
    *(unsigned char *) (self + 0xaf) = 0;
    *(unsigned char *) (self + 0xb3) = 0;
    func_ov002_02209984(self + 0x2300, 3, 1, 0);
    *(unsigned char *) (self + 0xb9) = 0;
}