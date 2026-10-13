/* func_02082808 @ 0x02082808, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082854(void *p, void *q);

int func_02082808(void *base, int val, unsigned short *src)
{
    unsigned short local;
    int idx;

    if (func_02082854(base, src) != -1) {
        goto fail;
    }

    local = 0xfff1;
    idx = func_02082854(base, &local);
    if (idx < 0 || idx >= 4) {
        goto fail;
    }

    {
        char *p = (char *) base + (idx << 3);
        *(unsigned int *) (p + 0x40) = val;
        *(unsigned short *) (p + 0x44) = *src;
    }
    return 1;

fail:
    return 0;
}
