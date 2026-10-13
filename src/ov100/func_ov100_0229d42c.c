/* func_ov100_0229d42c @ 0x0229d42c, 0x4a bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d630(void *, void *);
extern int func_ov100_0229d620(void *, void *);
extern int func_ov100_0229d5d4(void *, void *);
extern int func_ov100_0229d60c(void *, void *);
extern int func_ov094_0229aba4(void *, int);

int func_ov100_0229d42c(void *r0, void *r1)
{
    if (func_ov100_0229d630(r0, r1) != 0 || func_ov100_0229d620(r0, r1) != 0) {
        return func_ov094_0229aba4((char *) r0 + 0xcc, func_ov100_0229d5d4(r0, r1));
    } else {
        return func_ov100_0229d60c(r0, r1) != 0 ? 0xc4 : 0;
    }
}
