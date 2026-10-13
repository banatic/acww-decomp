/* func_ov122_022a04ec @ 0x022a04ec, 0x50 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_ov002_022090b0(void *ptr, unsigned char b);
extern unsigned char func_ov002_02208a8c(void *ptr, unsigned char b1, unsigned char b2);
extern void func_ov002_02208098(void *ptr, int a);

void func_ov122_022a04ec(char *param)
{
    if (func_0208e484((void *) (param + 0x4058)) != 0) {
        func_ov002_022090b0((void *) (param + 0x42b0), *(unsigned char *) (param + 0xb6));
        *(unsigned char *) (param + 0xb6) = func_ov002_02208a8c((void *) (param + 0x42b0), *(unsigned char *) (param + 0xb7),
                                                                *(unsigned char *) (param + 0xb6));
        func_ov002_02208098((void *) param, 0x17);
    }
}
