/* func_ov108_0229d0a4 @ 0x0229d0a4, 0x50 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(char *);
extern void func_ov002_022096d8(char *, int);
extern void func_ov002_02207d24(char *, int);
extern int func_0208e4bc(char *);
extern void func_ov108_0229c5f4(char *);
extern void func_ov002_02208098(char *, int);

void func_ov108_0229d0a4(char *p)
{
    if (func_ov002_0220909c(p + 0x24FC)) {
        func_ov002_022096d8(p + 0x24FC, 0);
        func_ov002_02207d24(p + 0x23B0, 1);
        if (func_0208e4bc(p + 0x2498)) {
            func_ov108_0229c5f4(p);
        }
        func_ov002_02208098(p, 0x15);
    }
}
