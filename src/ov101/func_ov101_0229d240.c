/* func_ov101_0229d240 @ 0x0229d240, 0x2c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern unsigned char *func_ov002_02208098(void *obj, unsigned char c);
extern void func_ov101_0229ca00(void *obj);

void func_ov101_0229d240(void *p)
{
    if (func_0208e484((char *) p + 0x229c) != 0) {
        func_ov002_02208098(p, *((unsigned char *) ((char *) p + 0xb6)));
    }
    func_ov101_0229ca00(p);
}
