/* func_ov129_0229cc08 @ 0x0229cc08, 0x44 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov129_0229c348(void *p);
extern int func_0208e484(void *p);
extern int func_ov127_02299b78(void *p);
extern void func_ov002_02208098(void *p, unsigned char c);

void func_ov129_0229cc08(void *p)
{
    if (func_ov127_02299b78((char *) p + 0x734)) {
        func_ov129_0229c348(p);
        func_ov002_02208098(p, *(unsigned char *) ((char *) p + 0xac));
    }
    if (func_0208e484((char *) p + 0x3a0)) {
        func_ov129_0229c348(p);
    }
}
