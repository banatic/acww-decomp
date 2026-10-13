/* func_ov111_022a0460 @ 0x022a0460, 0x4c bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(void *p, unsigned char b);
extern int func_ov095_0229bf0c(void *p);
extern void func_ov111_0229f730(void *p, int val);
extern int func_ov111_0229efd8(void *p, int val);
extern void func_ov111_0229f10c(void *p);

void func_ov111_022a0460(unsigned char *p)
{
    if ((data_021fbe40 & 2) == 0) {
        unsigned char *q;
        unsigned char b;
        q = p + 0x98;
        b = *q;
        func_ov002_02208098(p, b);
    } else {
        if (func_ov095_0229bf0c(p + 0xac)) {
            func_ov111_0229f730(p, 0x100);
            if (func_ov111_0229efd8(p, 2)) {
                func_ov111_0229f10c(p);
            }
        }
    }
}
