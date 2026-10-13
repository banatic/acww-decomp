/* func_0205712c @ 0x0205712c, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020574a0(void *p0);

#pragma opt_loop_invariants off

int func_0205712c(void *p0, u8 *p1, int p2)
{
    u8 *base;
    u8 *sec;
    u8 *tbl;
    u8 *ents;
    u8 *ent;
    u8 *names;
    u8 *found;
    u8 *s;
    u8 *ents2;
    u8 *elem;
    u8 *a;
    u8 *ep;
    unsigned int j;
    unsigned int k;
    int n;
    int off;
    int stride;
    int v;
    int w;
    int sum;
    int o2;
    int stride3;
    int idx;
    int off2;
    int stride2;

    if (func_020574a0(p0) == 0) {
        goto fail;
    }
    found = 0;
    if (p2 == -1) {
        goto fail;
    }
    base = *(u8 **) p0;
    sec = base + *(int *) (base + 8);
    tbl = sec + *(u16 *) (sec + 2);
    j = 0;
    n = tbl[1];
    for (; j < (unsigned int) n; j++) {
        off = *(u16 *) (tbl + 6);
        ents = tbl + off + 4;
        stride = *(u16 *) (tbl + off);
        ent = ents + stride * j;
        names = sec + *(u16 *) (ents + stride * j);
        k = 0;
        sum = ent[2];
        for (; k < (unsigned int) sum; k++) {
            if (*(signed char *) ((u8 *) p0 + 4) == names[k]) {
                found = ent;
                break;
            }
        }
        if (found != 0) {
            break;
        }
    }
    if (found == 0) {
        goto fail;
    }
    s = p1 + *(u16 *) (p1 + 0x34);
    off2 = *(u16 *) (s + 6);
    ents2 = s + off2 + 4;
    stride2 = *(u16 *) (s + off2);
    elem = ents2 + stride2 * p2;
    v = *(u16 *) (ents2 + stride2 * p2);
    w = (u16) * (int *) (p1 + 0x2c);
    if ((*(u16 *) (elem + 2) & 1) == 0) {
        v = (u16) (v >> 1);
        w = (u16) (w >> 1);
    }
    names = sec + *(u16 *) found;
    k = 0;
    sum = v + w;
    for (; k < (unsigned int) found[2]; k++) {
        a = sec + 4;
        o2 = *(u16 *) (sec + 0xa);
        stride3 = *(u16 *) (a + o2);
        idx = names[k];
        ep = sec + *(int *) (a + o2 + stride3 * idx + 4);
        *(u16 *) (ep + 0x1c) = (u16) sum;
    }
    found[3] |= 1;
    return 1;
fail:
    return 0;
}
