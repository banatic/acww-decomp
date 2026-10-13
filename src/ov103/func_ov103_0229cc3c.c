/* func_ov103_0229cc3c @ 0x0229cc3c, 0x34 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229cdfc(void *a, int b);
extern int func_ov103_0229cde8(void *a, int b);
extern int func_ov094_0229b788(void *p, int n);

int func_ov103_0229cc3c(void *a, int b)
{
    if (func_ov103_0229cdfc(a, b)) {
        return func_ov094_0229b788((char *) a + 0xb2c, func_ov103_0229cde8(a, b));
    }
    return 0;
}
