/* func_ov102_0229d7f8 @ 0x0229d7f8, 0x38 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(void *ptr, int value);
extern void func_ov002_02208098(void *ptr, unsigned char byte);
extern void func_0208e5cc(void *ptr);

void func_ov102_0229d7f8(void *base)
{
    if (func_ov002_0220b8ac((char *) base + 0x22d8, 1)) {
        func_ov002_02208098(base, *(unsigned char *) ((char *) base + 0x25a7));
        func_0208e5cc((char *) base + 0x2274);
    }
}
