/* func_ov068_0226a0dc @ 0x0226a0dc, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0201ce50(void *);
extern int func_020ea990(void *, void *);

int func_ov068_0226a0dc(int unused, char *arg)
{
    char *result = func_0201ce50(arg);
    int r = 0;
    if (result) {
        arg += 0x5c;
        result += 0x5c;
        r = func_020ea990(arg, result);
    }
    if (r > 0 && r < 0x3c00) {
        return 1;
    }
    return 0;
}
