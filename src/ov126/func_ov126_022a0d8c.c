/* func_ov126_022a0d8c @ 0x022a0d8c, 0x28 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(const unsigned char *);
extern void func_ov126_0229fea0(const unsigned char *);
extern void func_ov002_02208098(const unsigned char *, int);

void func_ov126_022a0d8c(const unsigned char *p)
{
    if (func_0208e484(p + 0x3f90) != 0) {
        func_ov126_0229fea0(p);
        func_ov002_02208098(p, 4);
    }
}
