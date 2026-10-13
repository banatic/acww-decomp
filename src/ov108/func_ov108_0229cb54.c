/* func_ov108_0229cb54 @ 0x0229cb54, 0x34 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229cd70(void *, int);
extern int func_ov108_0229cd5c(void *, int);
extern int func_ov094_0229b30c(void *, int);

int func_ov108_0229cb54(void *a, int b)
{
    if (func_ov108_0229cd70(a, b) != 0) {
        int x = func_ov108_0229cd5c(a, b);
        return func_ov094_0229b30c((char *) a + 0xD50, x);
    }
    return 1;
}
