/* func_ov100_0229dc38 @ 0x0229dc38, 0x50 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern void func_ov002_02208098(void *, unsigned char);
extern void func_ov100_0229d068(void *, unsigned char);
extern void func_ov100_0229e7cc(void *);
extern void func_ov100_0229ce24(void *);

void func_ov100_0229dc38(void *base)
{
    if (func_ov002_02209f64((char *) base + 0x2274) == 0) {
        func_ov002_02208098(base, *(unsigned char *) ((char *) base + 0x2924));
        if ((unsigned char) (*(unsigned char *) ((char *) base + 0x2924) + 0xFC) <= 1) {
            func_ov100_0229d068(base, *(unsigned char *) ((char *) base + 0x2921));
        }
        func_ov100_0229e7cc(base);
    }
    func_ov100_0229ce24(base);
}
