/* func_ov003_02213178 @ 0x02213178, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov003_02213174(const unsigned char *p);
extern unsigned short func_ov003_02213168(const unsigned char *p);

void func_ov003_02213178(unsigned char *src, unsigned char *dst1, unsigned char *dst2, unsigned short *dst3)
{
    *dst1 = *src;
    *dst2 = func_ov003_02213174(src);
    *dst3 = func_ov003_02213168(src);
}
