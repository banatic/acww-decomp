/* func_ov109_0229cf7c @ 0x0229cf7c, 0x38 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void *func_ov002_0220a720(void *ptr, unsigned int value);
extern unsigned char *func_ov002_02208098(void *ptr, unsigned char value);
extern void func_0200467c(unsigned int command);

void func_ov109_0229cf7c(void *p)
{
    if (func_0208e484((char *) p + 0x2274)) {
        func_ov002_0220a720((char *) p + 0x27e8, 9);
        func_ov002_02208098(p, 15);
        func_0200467c(0x28);
    }
}
