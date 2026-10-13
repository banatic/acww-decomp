/* func_ov102_0229cff8 @ 0x0229cff8, 0x3a bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d464(void *p, int q);
extern int func_ov102_0229d454(void *p, int q);
extern int func_ov102_0229d400(void *p, int q);
extern int func_ov094_0229aa84(void *p, int v);

int func_ov102_0229cff8(void *p, int q)
{
    if (func_ov102_0229d464(p, q) != 0 || func_ov102_0229d454(p, q) != 0) {
        return func_ov094_0229aa84((char *) p + 0xcc, func_ov102_0229d400(p, q));
    } else {
        return 0xf1;
    }
}
