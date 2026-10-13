/* func_0209e2d0 @ 0x0209e2d0, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e304(void *p, int n);

void func_0209e2d0(unsigned char *p, int add)
{
    int sum;
    sum = p[4] + add;
    if (sum > 12) {
        func_0209e304(p, sum / 12);
        sum = sum % 12;
    }
    p[4] = (unsigned char) sum;
}
