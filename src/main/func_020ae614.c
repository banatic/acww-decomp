/* func_020ae614 @ 0x020ae614, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b49d4(const char *a, const char *b, const void *c);
extern char data_020e41ac;

int func_020ae614(volatile signed char *p, const char *q)
{
    char local;
    if (p[4] == -1) {
        goto ret0;
    }
    local = (p[4] & 0x1f) << 1;
    return func_020b49d4(q, &local, &data_020e41ac);
ret0:
    return 0;
}
