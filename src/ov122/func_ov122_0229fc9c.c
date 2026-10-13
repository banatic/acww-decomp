/* func_ov122_0229fc9c @ 0x0229fc9c, 0x60 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051d08(void *p, int n);
extern int func_ov095_0229bb34(void *dst, void *field, int n, int unused, int d, void *local);

int func_ov122_0229fc9c(char *p, int *out)
{
    unsigned char local;
    unsigned char a;
    int b, c;

    a = (unsigned char) (*out - 0x30);
    b = func_02051d08(*(char **) (p + 0xbc) + 0xd8, 0x10);
    c = 0xa0 - b;
    if (c > a) {
        local = 0;
        *out = c + 0x30;
    } else {
        unsigned char d = (unsigned char) (a - c);
        int e = func_ov095_0229bb34(p + 0xc0, *(char **) (p + 0xbc) + 0xd8, 0x10, 0xa0, d, &local);
        *out = c + (e + 0x30);
    }
    return local;
}
