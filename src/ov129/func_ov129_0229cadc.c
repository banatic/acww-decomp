/* func_ov129_0229cadc @ 0x0229cadc, 0x2c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov129_0229c348(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov129_0229cadc(void *p)
{
    if (func_0208e484((char *) p + 0x3a0)) {
        func_ov129_0229c348(p);
        func_ov002_02208098((void *) (p), *(unsigned char *) ((char *) p + 0xac));
    }
}
