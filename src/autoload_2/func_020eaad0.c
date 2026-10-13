/* func_020eaad0 @ 0x020eaad0, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eaad0(void *dst, const void *src, int shift);

void func_020eaad0(void *dst, const void *src, int shift)
{
    int a, b, c;
    a = *(int *) src;
    b = *(int *) ((char *) src + 4);
    c = *(int *) ((char *) src + 8);
    *(int *) dst = a >> shift;
    *(int *) ((char *) dst + 4) = b >> shift;
    *(int *) ((char *) dst + 8) = c >> shift;
}
