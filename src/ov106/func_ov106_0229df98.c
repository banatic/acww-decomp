/* func_ov106_0229df98 @ 0x0229df98, 0x34 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_ov106_0229c378(void *ptr);
extern void func_ov106_0229c9fc(void *ptr);

void func_ov106_0229df98(void *p)
{
    if (func_0208e484((char *) p + 0x22a0) == 0) {
        return;
    }
    if (*(unsigned char *) ((char *) p + 0xb8) == 0x1f) {
        func_ov106_0229c378(p);
    } else {
        func_ov106_0229c9fc(p);
    }
}
