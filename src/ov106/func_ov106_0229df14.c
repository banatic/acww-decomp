/* func_ov106_0229df14 @ 0x0229df14, 0x2c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(const void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov106_0229ce0c(const void *);

void func_ov106_0229df14(unsigned char *p)
{
    if (func_0208e484(p + 0x22a0) != 0) {
        func_ov002_02208098((void *) (p), p[0xbb]);
    }
    func_ov106_0229ce0c(p);
}
