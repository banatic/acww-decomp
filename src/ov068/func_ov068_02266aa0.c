/* func_ov068_02266aa0 @ 0x02266aa0, 0x64 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_02266b3c(void *a, int b, int c);
extern int func_ov068_02266bac(void *a, void *b, int c, void *d, int limit);
extern void func_0201ad78(void *a, void *b);
extern void func_ov068_02266c70(void *a, void *b);

void func_ov068_02266aa0(void *r5, void *r4)
{
    int r0;
    int r1;
    int r2;
    int r3;
    int sp[4];
    int *sp_ptr;

    r0 = func_ov068_02266b3c(r5, *(int *) ((char *) r5 + 0xc), *(int *) ((char *) r5 + 0x10));
    if (r0 != 0) {
        r0 = func_ov068_02266bac(r5, sp, *(int *) ((char *) r5 + 0xc), (char *) r4 + 0x5c, *(int *) ((char *) r4 + 0x40c));
        r1 = -1;
        if (r0 != r1) {
            r1 = *(int *) ((char *) r5 + 0x10);
            if (r0 == r1) {
                func_0201ad78((char *) r4 + 0x3b0, sp);
                goto done;
            }
        }
        func_ov068_02266c70(r5, r4);
    } else {
        func_ov068_02266c70(r5, r4);
    }
done:
    return;
}
