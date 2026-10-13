/* func_ov102_0229d9e0 @ 0x0229d9e0, 0x40 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(char *);
extern void func_ov102_0229ca98(char *);
extern void func_ov002_02208098(char *, int);

void func_ov102_0229d9e0(char *ptr)
{
    if (func_0208e484(ptr + 0x2274) != 0) {
        func_ov102_0229ca98(ptr);
        if (*(unsigned char *) (ptr + 0x259f) == 1) {
            func_ov002_02208098(ptr, 4);
        } else {
            func_ov002_02208098(ptr, 3);
        }
    }
}
