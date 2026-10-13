/* func_020672cc @ 0x020672cc, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm int strlen(const char *p);
extern __arm int strncmp(const char *s, const char *p, int n);
extern const char *data_020ccee8[];

const char *func_020672cc(void *a, const char *s)
{
    const char **ptr;
    const char *p;
    int n;

    ptr = data_020ccee8;
    while ((p = *ptr) != 0) {
        n = strlen(p);
        if (strncmp(s, p, n) == 0 && s[n] == '_') {
            break;
        }
        ptr++;
    }
    return p;
}
