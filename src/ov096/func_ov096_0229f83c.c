/* func_ov096_0229f83c @ 0x0229f83c, 0x24 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ccc(char *p);

void func_ov096_0229f83c(void *self)
{
    int i = 0;
    char *base = (char *) self + 0x2e8;
    do {
        func_020b9ccc(base + i * 0x38);
        i++;
    } while (i < 2);
}
