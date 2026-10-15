/* func_ov102_0229da90 @ 0x0229da90, 0x50 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char);
extern void func_ov102_0229cf90(unsigned char *, unsigned char);
extern void func_ov102_0229e5b8(unsigned char *);
extern void func_ov102_0229cd38(unsigned char *);

void func_ov102_0229da90(unsigned char *a)
{
    if (func_ov002_02209f64(a + 0x2274) == 0) {
        func_ov002_02208098(a, a[0x25a7]);
        if ((unsigned char) (a[0x25a7] + 0xFD) <= 1) {
            func_ov102_0229cf90(a, a[0x25a5]);
        }
        func_ov102_0229e5b8(a);
    }
    func_ov102_0229cd38(a);
}
