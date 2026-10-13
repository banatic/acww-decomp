/* func_ov101_0229d2fc @ 0x0229d2fc, 0x50 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(const void *ptr);
extern void func_ov002_02208098(const void *ptr, unsigned char val);
extern void func_ov101_0229cb60(const void *ptr, unsigned char val);
extern void func_ov101_0229dbb0(const void *ptr);
extern void func_ov101_0229ca00(const void *ptr);

void func_ov101_0229d2fc(void *p)
{
    if (func_ov002_02209f64((char *) p + 0x229c) == 0) {
        func_ov002_02208098(p, *(unsigned char *) ((char *) p + 0xb6));
        if ((unsigned char) (*(unsigned char *) ((char *) p + 0xb6) + 0xfa) <= 1) {
            func_ov101_0229cb60(p, *(unsigned char *) ((char *) p + 0xb3));
        }
        func_ov101_0229dbb0(p);
    }
    func_ov101_0229ca00(p);
}
