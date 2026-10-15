/* func_ov099_0229d358 @ 0x0229d358, 0x30 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(char *ptr);
extern unsigned char *func_ov002_02208098(char *ptr, unsigned char val);
extern void func_ov099_0229c928(char *ptr);

void func_ov099_0229d358(char *arg)
{
    if (func_0208e484(arg + 0x2274) != 0) {
        func_ov002_02208098(arg, *(unsigned char *) (arg + 0x290a));
    }
    func_ov099_0229c928(arg);
}
