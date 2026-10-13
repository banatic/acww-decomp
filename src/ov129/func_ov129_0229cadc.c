/* func_ov129_0229cadc @ 0x0229cadc, 0x2c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov129_0229c348(void *);
extern void func_ov002_02208098(void *, unsigned char);

void func_ov129_0229cadc(void *p)
{
    if (func_0208e484((char *) p + 0x3a0)) {
        func_ov129_0229c348(p);
        func_ov002_02208098(p, *(unsigned char *) ((char *) p + 0xac));
    }
}
