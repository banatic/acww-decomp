/* func_ov105_0229de3c @ 0x0229de3c, 0x38 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(void *p, int x);
extern unsigned char *func_ov002_02208098(void *p, unsigned char b);
extern void func_0208e5cc(void *p);

void func_ov105_0229de3c(unsigned char *p)
{
    if (func_ov002_0220b8ac(p + 0x28fc, 0)) {
        func_ov002_02208098(p, p[0x2bd]);
        func_0208e5cc(p + 0x24a4);
    }
}
