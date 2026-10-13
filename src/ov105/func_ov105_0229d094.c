/* func_ov105_0229d094 @ 0x0229d094, 0x40 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066830(void *dst, void *src);
extern void func_ov105_0229d0f8(void *a, void *b);
extern void func_ov105_0229d5dc(void *a, void *b, void *c);

void func_ov105_0229d094(void *r0, void *r1)
{
    unsigned char *p = (unsigned char *) r0;
    if (p[0x2b4] == 1) {
        func_02066830((char *) r0 + 0x1b4, (char *) r0 + 0xb4);
        func_ov105_0229d0f8(r0, r1);
        func_ov105_0229d5dc(r0, r1, (char *) r0 + 0x1b4);
    }
}
