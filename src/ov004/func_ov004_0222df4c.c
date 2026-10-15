/* func_ov004_0222df4c @ 0x0222df4c, 0x154 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02054ecc(void *);
extern int func_ov004_0222c3c4(void *, int);
extern int func_02056f94(void *);
extern void func_ov004_0222db14(void *, int, void *, void *, unsigned char, int, unsigned short, unsigned short);
extern void func_0203ab64(void);
extern void func_0203ae98(void);
void func_ov004_0222df4c(char *self)
{
    int current;
    current = func_02054ecc(self + 0x348);
    if (current == func_ov004_0222c3c4(self + 0x9ac, 6) && func_02056f94(self + 0x3e4)) {
        func_ov004_0222db14(self, 9, self + 0x348, self + 0x9ac, 1, 0x1000, 0, 0);
        func_ov004_0222db14(self, 7, self + 0x400, self + 0xa50, 1, 0x1000, 0, 0);
    } else {
        current = func_02054ecc(self + 0x348);
        if (current == func_ov004_0222c3c4(self + 0x9ac, 9) && func_02056f94(self + 0x3e4)) {
            func_ov004_0222db14(self, 10, self + 0x348, self + 0x9ac, 1, 0x1000, 0, 0);
            func_ov004_0222db14(self, 8, self + 0x400, self + 0xa50, 1, 0x1000, 0, 0);
        } else {
            current = func_02054ecc(self + 0x348);
            if (current == func_ov004_0222c3c4(self + 0x9ac, 10) && func_02056f94(self + 0x3e4)) {
                func_0203ab64();
                func_0203ae98();
                func_ov004_0222db14(self, 11, self + 0x348, self + 0x9ac, 1, 0x1000, 0, 0);
                func_ov004_0222db14(self, 9, self + 0x400, self + 0xa50, 1, 0x1000, 0, 0);
            }
        }
    }
}
