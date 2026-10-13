/* func_ov100_0229dbf8 @ 0x0229dbf8, 0x40 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov100_0229c3c0(void *);
extern void func_ov100_0229c4ec(void *);
extern void func_ov100_0229ca3c(void *);

void func_ov100_0229dbf8(void *p)
{
    if (func_0208e484((char *) p + 0x2274)) {
        unsigned char v = *(unsigned char *) ((char *) p + 0x2921);
        if (v == 0x1e) {
            func_ov100_0229c3c0(p);
        } else if (v == 0x1f) {
            func_ov100_0229c4ec(p);
        } else {
            func_ov100_0229ca3c(p);
        }
    }
}
