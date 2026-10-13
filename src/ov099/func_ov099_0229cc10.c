/* func_ov099_0229cc10 @ 0x0229cc10, 0x2e bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229cf30(void *p, void *q);
extern int func_ov099_0229cf04(void *p, void *q);
extern int func_ov094_0229aa84(void *p, int v);

int func_ov099_0229cc10(void *p, void *q)
{
    if (func_ov099_0229cf30(p, q) != 0) {
        return func_ov094_0229aa84((char *) p + 0xcc, func_ov099_0229cf04(p, q));
    } else {
        return 0xf1;
    }
}
