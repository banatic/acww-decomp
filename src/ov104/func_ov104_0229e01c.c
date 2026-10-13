/* func_ov104_0229e01c @ 0x0229e01c, 0x54 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(void *ptr);
extern void func_ov104_0229d528(void *ptr);
extern void func_ov104_0229d974(void *ptr);
extern void func_ov104_0229d5c0(void *ptr);
extern void func_ov002_02208098(void *ptr, int n);
extern void func_ov094_022999d8(void);
extern void func_ov104_0229db74(void *ptr, unsigned char byte, int n);

void func_ov104_0229e01c(void *arg)
{
    if (func_ov002_02209f9c((char *) arg + 0x24A0) == 0) {
        unsigned char b = ((unsigned char *) arg)[0xBA];
        if (((unsigned char *) arg)[0xB8] == b) {
            func_ov104_0229d974(arg);
            func_ov104_0229d5c0(arg);
            func_ov002_02208098(arg, 7);
            func_ov094_022999d8();
        } else {
            func_ov104_0229db74(arg, b, 4);
        }
    } else {
        func_ov104_0229d528(arg);
    }
}
