/* func_020b48b4 @ 0x020b48b4, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b4950_unk(unsigned char *, unsigned char *, int);
extern void func_020b4930(unsigned char *, unsigned char *, int, int);

void func_020b48b4(unsigned char *p, unsigned char *q, int n)
{
    int ret;
    int diff;
    int i;

    ret = func_020b4950_unk(p, q, n);
    diff = 2 * n - ret;
    func_020b4930(p, q, 0, diff);
    for (i = diff - 1; i >= 0; i -= 2) {
        p[i] = 0x20;
        p[i - 1] = 0;
    }
}
