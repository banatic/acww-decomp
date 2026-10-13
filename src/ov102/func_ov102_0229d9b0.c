/* func_ov102_0229d9b0 @ 0x0229d9b0, 0x30 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(void *p);
extern void func_ov002_02208098(void *p, int n);
extern void func_ov102_0229d5e8(void *p, int n);

void func_ov102_0229d9b0(void *arg0)
{
    if (func_ov002_02209f9c((char *) arg0 + 0x2274)) {
        func_ov102_0229d5e8(arg0, ((unsigned char *) arg0)[0x25a5]);
        func_ov002_02208098(arg0, 9);
    }
}
