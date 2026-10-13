/* func_ov053_02260a18 @ 0x02260a18, 0x4e bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222beb4(void);
extern void func_020984e8(void);
extern int func_02099670(void);
extern void func_02088bac(int, int);

void func_ov053_02260a18(unsigned char *p)
{
    unsigned char b = p[0x1e];
    if (b == 0xe || b == 0x37) {
        if ((b == 0xe && p[0xb9] == 1) || (b == 0x37 && p[0xb9] == 2)) {
            func_ov004_0222beb4();
            func_020984e8();
            func_02088bac(func_02099670(), 1);
        }
        p[0xb9]++;
    }
}
