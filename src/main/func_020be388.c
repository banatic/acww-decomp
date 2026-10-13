/* func_020be388 @ 0x020be388, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020bec70(char *arg0, int arg1);
extern void func_020bf064(char *arg0, int arg1);
extern void func_020bee9c(char *arg0, char *arg1);
extern void func_020bed64(char *arg0, char *arg1, int arg2);

void func_020be388(char *base)
{
    char *p;
    char *end;
    int val, ret;
    unsigned char b;

    end = base + 0x1b6c;
    for (p = base + 0x1b30; p < end; p += 12) {
        val = *(int *) p;
        if (val == 52) {
            continue;
        }
        b = *(unsigned char *) (p + 8);
        ret = func_020bec70(base + 0x2eb8, val);
        if (b == 0) {
            func_020bf064(base + 0x1b6c, val);
            func_020bee9c(p, base + 0x1b6c);
            *(unsigned char *) (p + 8) = 1;
            *(unsigned char *) (p + 9) = 0;
        }
        if (ret == 0) {
            func_020bed64(base + 0x2eb8, base + 0x1b6c, val);
        }
    }
}
