/* func_02057238 @ 0x02057238, 0x154 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern int func_020574a0(void *);
extern int FX_Div(int a, int b);
typedef struct {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 pad_04;
    u16 ofsEntry;
    u32 node;
} Dict;
typedef struct {
    u16 sizeUnit;
    u16 ofsName;
    u8 data[4];
} Entry;
inline static u8 *dict_data(const Dict *dict, u32 idx)
{
    Entry *hdr;
    hdr = (Entry *) (((u8 *) dict) + dict->ofsEntry);
    return (&hdr->data[0]) + (hdr->sizeUnit * idx);
}

int func_02057238(void *a0, void *a1, int a2)
{
    unsigned char *hdr;
    u32 off8;
    unsigned char *dir;
    unsigned char *tbl;
    u32 mask;
    unsigned char *sub;
    u32 blk;
    unsigned char *strbase;
    u32 hi;
    unsigned int cnt1;
    unsigned int cnt2;
    unsigned int i1;
    unsigned int i2;
    u32 hw;
    unsigned char *t1;
    unsigned char *p;
    unsigned char *match;
    unsigned char *r1p;
    unsigned char *blkbase;
    unsigned char *e2;
    u32 w;
    u32 lo;
    u32 r;
    u32 k;
    if (func_020574a0(a0) == 0) {
        goto fail;
    }
    if (a2 == (-1)) {
        goto fail;
    }
    hdr = *((unsigned char **) a0);
    off8 = *((u32 *) (hdr + 8));
    dir = hdr + off8;
    tbl = dir + (*((u16 *) dir));
    match = 0;
    i1 = 0;
    cnt1 = tbl[1];
    i2 = 0;
    for (; i1 < cnt1; i1++) {
        p = dict_data((const Dict *) tbl, i1);
        sub = dir + *(u16 *) p;
        i2 = 0;
        cnt2 = p[2];
        for (; i2 < cnt2; i2++) {
            if ((*((signed char *) (((char *) a0) + 4))) == sub[i2]) {
                match = p;
                break;
            }
        }
        if (match != 0) {
            break;
        }
    }
    if (match == 0) {
        goto fail;
    }
    blk = (u32) dict_data((const Dict *) ((u8 *) a1 + 0x3c), (u32) a2);
    w = *((u32 *) blk);
    if (((w >> 26) & 7) != 5) {
        mask = *((u32 *) (((char *) a1) + 8));
        mask &= 0xffff;
    } else {
        mask = *((u32 *) (((char *) a1) + 0x18));
        mask &= 0xffff;
    }
    strbase = dir + (*((u16 *) match));
    for (k = 0; k < match[2]; k++) {
        u32 cur;
        {
            Entry *h = (Entry *) ((dir + 4) + ((Dict *) (dir + 4))->ofsEntry);
            e2 = dir + (*((u32 *) ((&h->data[0]) + (h->sizeUnit * strbase[k]))));
        }
        *((u32 *) (e2 + 0x14)) &= 0xc00f0000u;
        *((u32 *) (e2 - -0x14)) |= (*((u32 *) blk)) + mask;
        w = *((u32 *) (blk + 4));
        lo = w & 0x7ffu;
        hi = (w >> 11) & 0x7ffu;
        cur = *((u16 *) (e2 + 0x20));
        if (lo != cur) {
            r = FX_Div(lo << 12, cur << 12);
        } else {
            r = 0x1000;
        }
        *((u32 *) (e2 + 0x24)) = r;
        cur = *((u16 *) (e2 + 0x22));
        if (hi != cur) {
            r = FX_Div(hi << 12, cur << 12);
        } else {
            r = 0x1000;
        }
        *((u32 *) (e2 + 0x28)) = r;
    }
    match[3] |= 1;
    return 1;
fail:
    return 0;
}
