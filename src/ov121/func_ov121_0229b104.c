/* func_ov121_0229b104 @ 0x0229b104, 0x44 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(void *);
extern void func_ov002_022096d8(void *, int);
extern int func_0208e4bc(void *);
extern void func_ov121_0229a1b0(void *);
extern void func_ov002_02208098(void *, int);

void func_ov121_0229b104(char *p)
{
    if (func_ov002_0220909c(p + 0x528)) {
        func_ov002_022096d8(p + 0x528, 0);
        if (func_0208e4bc(p + 0x3a8)) {
            func_ov121_0229a1b0(p);
        }
        func_ov002_02208098(p, 0x10);
    }
}
