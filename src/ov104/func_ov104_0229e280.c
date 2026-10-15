/* func_ov104_0229e280 @ 0x0229e280, 0x94 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(unsigned char *);
extern int func_ov002_0220b5ec(unsigned char *, int);
extern int func_ov002_0220b59c(unsigned char *, int);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov002_0220a374(unsigned char *, int);
extern int func_ov002_02208014(void *receiver);
extern void func_ov104_0229d378(unsigned char *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a1dc(unsigned char *);
extern unsigned short data_021fbe40[2];

void func_ov104_0229e280(unsigned char *p)
{
    int a;
    int b;

    if (func_0208e4bc(p + 0x24a0) == 0) {
        a = func_ov002_0220b5ec(p + 0x2d3c, 1);
        b = func_ov002_0220b59c(p + 0x2d3c, 1);
        func_ov002_0220a0b4(p + 0x24a0, a, b);
        func_ov002_0220a374(p + 0x24a0, 1);
    }

    if (func_ov002_02208014(p) != 0) {
        func_ov104_0229d378(p);
        func_ov002_02208098((void *) (p), 5);
    } else {
        if ((data_021fbe40[1] & 1) || (data_021fbe40[1] & 2)) {
            func_ov002_0220a1dc(p + 0x24a0);
            func_ov002_02208098((void *) (p), 10);
        }
    }
}
