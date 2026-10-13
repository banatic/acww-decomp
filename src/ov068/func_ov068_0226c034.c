/* func_ov068_0226c034 @ 0x0226c034, 0x70 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_0226cf8c(void *);
extern int func_ov068_0226c0a4(void *);
extern int func_0201c378(void *, unsigned int);
extern int func_0201ac28(void *, void *);
extern int func_0201a7fc(void *);

int func_ov068_0226c034(void *a0, void *a1)
{
    int call_res;

    call_res = func_ov068_0226cf8c(a1);
    if (*((unsigned char *) a0 + 0xE0) != 0) {
        goto fail;
    }
    if (call_res != 0 && call_res != 1) {
        goto fail;
    }
    if (func_ov068_0226c0a4(a0) == 0) {
        goto fail;
    }
    if (*((unsigned char *) a1 + 0x3B0) != 1) {
        goto fail;
    }
    if (func_0201c378(a1, 4) > 0x6000) {
        goto fail;
    }
    if (func_0201ac28((unsigned char *) a1 + 0x3B0, a1) == 0) {
        goto fail;
    }
    if (func_0201a7fc((unsigned char *) a1 + 0x3B0) == 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}
