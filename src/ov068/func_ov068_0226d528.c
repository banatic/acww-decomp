/* func_ov068_0226d528 @ 0x0226d528, 0x70 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02089cc0(void *, int);
extern void *func_02096190(int);
extern int func_0200322c(void *, void *);

int func_ov068_0226d528(void *p)
{
    void *q;
    short diff;

    if (((unsigned char *) p)[0x508] == 0) {
        goto fail;
    }
    if (func_02089cc0((unsigned char *) p + 0x4cc, 4) == 0) {
        goto fail;
    }
    q = func_02096190(4);
    if (q == 0) {
        goto fail;
    }
    if (*(int *) ((unsigned char *) q + 0x98) == 0) {
        goto fail;
    }

    diff = (short) (func_0200322c((unsigned char *) q + 0x5c, (unsigned char *) p + 0x5c) -
                    *(short *) ((unsigned char *) q + 0x94));
    if (diff < 0) {
        diff = -diff;
    }
    if (diff >= 0x31c6) {
        goto fail;
    }

    return 1;

fail:
    return 0;
}
