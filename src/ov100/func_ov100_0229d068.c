/* func_ov100_0229d068 @ 0x0229d068, 0x58 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d630(void *a, void *b);
extern int func_ov100_0229d620(void *a, void *b);
extern int func_ov100_0229d60c(void *a, void *b);
extern int func_ov100_0229d5d4(void *a, void *b);
extern void func_ov094_0229ab1c(void *p, int x);
extern void func_ov094_0229b98c(void *p);
extern void func_ov100_0229d0c0(void *a);

void func_ov100_0229d068(void *a, void *b)
{
    if (func_ov100_0229d630(a, b) || func_ov100_0229d620(a, b)) {
        int r = func_ov100_0229d5d4(a, b);
        func_ov094_0229ab1c((char *) a + 0xcc, r);
        func_ov094_0229b98c((char *) a + 0xb2c);
    } else if (func_ov100_0229d60c(a, b)) {
        func_ov100_0229d0c0(a);
    }
}
