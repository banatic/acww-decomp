/* func_ov099_0229ccc8 @ 0x0229ccc8, 0x54 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229cf30(void *, void *);
extern int func_ov099_0229cf04(void *, void *);
extern int func_ov099_0229cf20(void *, void *);
extern int func_ov099_0229ce14(void *, void *);
extern int func_ov094_0229a8bc(void *, int);
extern int func_ov094_0229b788(void *, int);

int func_ov099_0229ccc8(void *p, void *q)
{
    if (func_ov099_0229cf30(p, q)) {
        int t = func_ov099_0229cf04(p, q);
        return func_ov094_0229a8bc((char *) p + 0xcc, t);
    } else if (func_ov099_0229cf20(p, q)) {
        int t2 = func_ov099_0229ce14(p, q);
        return func_ov094_0229b788((char *) p + 0xb2c, t2);
    } else {
        return 0;
    }
}
