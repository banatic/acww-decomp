/* func_ov105_0229d5dc @ 0x0229d5dc, 0x74 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229d76c(void);
extern int func_ov105_0229d75c(unsigned char *, int);
extern int func_ov105_0229d718(unsigned char *, int);
extern int func_ov105_0229d73c(unsigned char *, int);
extern void func_ov094_0229b8b4(unsigned char *, int, int);
extern void func_02066830(unsigned char *, int);

void func_ov105_0229d5dc(unsigned char *a, int b, int c)
{
    if (func_ov105_0229d76c() != 0 || func_ov105_0229d75c(a, b) != 0) {
        func_ov094_0229b8b4(a + 0xd5c, func_ov105_0229d718(a, b), c);
    } else {
        if (func_ov105_0229d73c(a, b) != 0) {
            func_02066830(a + 0x2db8 + (((a[0x2b9] - 0x24) + 0x19 * a[0x2b8]) << 8), c);
        }
    }
}
