/* func_ov105_0229df7c @ 0x0229df7c, 0x54 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern unsigned char *func_ov002_02208098(void *ptr, unsigned char val);
extern int func_ov002_02209f9c(void *ptr);
extern int func_ov105_0229c340(void *ptr, int arg);
extern void func_ov105_0229c320(void *ptr, int arg);
extern void func_ov094_022999c0(void);
extern void func_ov105_0229d17c(void *ptr);

void func_ov105_0229df7c(char *p)
{
    if (func_0208e484(p + 0x24a4)) {
        func_ov002_02208098(p, *((unsigned char *) (p + 0x2bd)));
    }
    if (func_ov002_02209f9c(p + 0x24a4)) {
        if (func_ov105_0229c340(p, 0x40)) {
            func_ov105_0229c320(p, 0x40);
            func_ov094_022999c0();
        }
        func_ov105_0229d17c(p);
    }
}
