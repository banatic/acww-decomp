/* func_ov106_0229dfcc @ 0x0229dfcc, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *p);
extern void func_ov002_02208098(void *p, unsigned char b);
extern void func_ov106_0229d028(void *p, unsigned char b);
extern void func_ov106_0229ef8c(void *p);
extern void func_ov106_0229ce0c(void *p);

void func_ov106_0229dfcc(void *p)
{
    unsigned char *b = (unsigned char *) p;
    if (func_ov002_02209f64(b + 0x22a0) == 0) {
        func_ov002_02208098(p, b[0xbb]);
        if (b[0xbb] == 7) {
            func_ov106_0229d028(p, b[0xb8]);
        }
        func_ov106_0229ef8c(p);
    }
    func_ov106_0229ce0c(p);
}
