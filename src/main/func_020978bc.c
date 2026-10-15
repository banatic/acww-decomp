/* func_020978bc @ 0x020978bc, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065ec0(unsigned char *p);
extern int func_02066830(unsigned char *dst, unsigned char *src);
extern void func_02066650(unsigned char *p);

int func_020978bc(unsigned char *base, int n)
{
    int i;
    int cnt;
    unsigned char *p;

    i = 0;
    cnt = i;
    for (; i < n; i++) {
        p = base + (i << 8);
        if (func_02065ec0(p)) {
            if (i != cnt) {
                func_02066830(base + (cnt << 8), p);
                func_02066650(p);
            }
            cnt++;
        }
    }
    return cnt;
}
