/* func_ov103_0229cc08 @ 0x0229cc08, 0x34 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229cdfc(void *a, void *b);
extern int func_ov103_0229cde8(void *a, void *b);
extern int func_ov094_0229b30c(void *a, int b);

int func_ov103_0229cc08(void *a, void *b)
{
    if (func_ov103_0229cdfc(a, b) != 0) {
        int tmp;
        tmp = func_ov103_0229cde8(a, b);
        return func_ov094_0229b30c((char *) a + 0xB2C, tmp);
    } else {
        return 1;
    }
}
