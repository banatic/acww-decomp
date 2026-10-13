/* func_ov110_0229dbf4 @ 0x0229dbf4, 0x4c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov002_02209114(void *, int, int);
extern void func_ov002_02208098(void *, int);

void func_ov110_0229dbf4(unsigned char *p)
{
    if (func_0208e484(p + 0x22e0) != 0) {
        func_ov002_02209114(p + 0x2344, p[0xfa], 1);
        {
            unsigned char *q = p + p[0xfa];
            p[0xf9] = q[0x2731];
        }
        func_ov002_02208098(p, 0x12);
    }
}
