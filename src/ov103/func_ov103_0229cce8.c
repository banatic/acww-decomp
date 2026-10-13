/* func_ov103_0229cce8 @ 0x0229cce8, 0x34 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229cdfc(void *p, int n);
extern int func_ov103_0229cde8(void *p, int n);
extern int func_ov094_0229b8d8(char *p, int n);

int func_ov103_0229cce8(void *p, int n)
{
    if (func_ov103_0229cdfc(p, n) != 0) {
        return func_ov094_0229b8d8((char *) p + 0xb2c, func_ov103_0229cde8(p, n));
    }
    return 0;
}
