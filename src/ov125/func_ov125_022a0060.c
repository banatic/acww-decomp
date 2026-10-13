/* func_ov125_022a0060 @ 0x022a0060, 0x4c bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_ov002_02209114(void *ptr, unsigned char val, int flag);
extern unsigned char func_ov125_0229fc84(void *ptr, unsigned char val);
extern void func_ov002_02208098(void *ptr, int val);

void func_ov125_022a0060(unsigned char *p)
{
    if (func_0208e484(p + 0x644)) {
        func_ov002_02209114(p + 0x180, *(p + 0x87e), 1);
        *(p + 0x87d) = func_ov125_0229fc84(p, *(p + 0x87e));
        func_ov002_02208098(p, 8);
    }
}
