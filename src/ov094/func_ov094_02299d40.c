/* func_ov094_02299d40 @ 0x02299d40, 0x3c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_02299ac4(void *);
extern void func_ov094_02299acc(void *, unsigned char);

int func_ov094_02299d40(void *p)
{
    int rem;

    if (*(unsigned char *) ((char *) p + 0x12) == 0) {
        goto ret1;
    }
    *(unsigned char *) ((char *) p + 0x12) -= 1;
    rem = *(unsigned char *) ((char *) p + 0x12) % 5;
    switch (rem) {
        case 3:
            func_ov094_02299acc(p, *(unsigned char *) ((char *) p + 0x11));
            break;
        case 0:
            func_ov094_02299ac4(p);
            break;
    }
    goto ret0;
ret1:
    return 1;
ret0:
    return 0;
}
