/* func_ov105_0229de94 @ 0x0229de94, 0x50 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(unsigned char *);
extern void func_ov002_022096d8(unsigned char *, int);
extern int func_ov002_02207d24(unsigned char *, int);
extern int func_0208e4bc(unsigned char *);
extern void func_ov105_0229cdbc(unsigned char *);
extern unsigned char *func_ov002_02208098(unsigned char *, unsigned char value);

void func_ov105_0229de94(unsigned char *p)
{
    if (func_ov002_0220909c(p + 0x2508) != 0) {
        func_ov002_022096d8(p + 0x2508, 0);
        func_ov002_02207d24(p + 0x23bc, 1);
        if (func_0208e4bc(p + 0x24a4) != 0) {
            func_ov105_0229cdbc(p);
        }
        func_ov002_02208098(p, 0x18);
    }
}
