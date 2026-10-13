/* func_ov109_0229ce14 @ 0x0229ce14, 0x64 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(void *p);
extern int func_0208e4bc(void *p);
extern int func_ov002_0220a6e0(void *p);
extern int func_ov002_0220a768(void *p, int x);
extern int func_ov002_0220a72c(void *p, int x);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov109_0229c498(unsigned int p);

void func_ov109_0229ce14(unsigned int p)
{
    if (func_ov002_0220a700((void *) (p + 0x27e8)) != 0) {
        if (func_0208e4bc((void *) (p + 0x2274)) != 0) {
            int a = func_ov002_0220a6e0((void *) (p + 0x27e8));
            int b = func_ov002_0220a768((void *) (p + 0x27e8), -1);
            int c = func_ov002_0220a72c((void *) (p + 0x27e8), -1);
            func_ov002_0220a0b4((void *) (p + 0x2274), a + b, a + c);
        }
    } else {
        func_ov109_0229c498(p);
    }
}
